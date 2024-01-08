#include <algorithm>
#include <unistd.h>
#include <cstring>

#include "./../header/encryptionManager.h"

// CRE UNE NOUVELLE CLE RSA 2048
EncryptionManager::EncryptionManager(){
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr); 
    if (!ctx || EVP_PKEY_keygen_init(ctx) <= 0 ||
        EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0) {
        std::cerr << "Error initializing RSA key generation context" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (EVP_PKEY_keygen(ctx, &_keyPair) <= 0) {
        std::cerr << "Error generating RSA key pair" << std::endl;
        exit(EXIT_FAILURE);
    }

    EVP_PKEY_CTX_free(ctx);
}

EncryptionManager::~EncryptionManager(){
    // Clean up
    EVP_PKEY_free(_keyPair);
    CRYPTO_cleanup_all_ex_data();
    ERR_free_strings();
}

// RECUPERE SA CLE PUBLIQUE POUR LA PARTAGER EN FORMAT PEM (--- PUB KEY --- 'àtçr'à"'jg'ijfoippjirvojS --- END PUB KEY ---)
std::string EncryptionManager::getPublicKey(){
    BIO* bio = BIO_new(BIO_s_mem());

    if (!bio) {
        throw std::runtime_error("Failed to create BIO");
    }

    if (PEM_write_bio_PUBKEY(bio, _keyPair) != 1) {
        throw std::runtime_error("Failed to print public key");
    }
    size_t bioLength = BIO_ctrl_pending(bio);

    std::string publicKeyString(bioLength, '\0');
    BIO_read(bio, publicKeyString.data(), bioLength);

    return publicKeyString;
}

std::string EncryptionManager::getClientPublicKey(){
    BIO* bio = BIO_new(BIO_s_mem());

    if (!bio) {
        throw std::runtime_error("Failed to create BIO");
    }

    if (PEM_write_bio_PUBKEY(bio, _clientKeyPair) != 1) {
        throw std::runtime_error("Failed to print public key");
    }
    size_t bioLength = BIO_ctrl_pending(bio);

    std::string publicKeyString(bioLength, '\0');
    BIO_read(bio, publicKeyString.data(), bioLength);

    return publicKeyString;
}

// ENREGISTRE LA CLE PUBLIQUE DE SON INTERLOCUTEUR
void EncryptionManager::setClientPublicKey(std::string clientPublicKey){
    BIO* bio = BIO_new_mem_buf(clientPublicKey.data(), clientPublicKey.size()), BIO_Deleter();

    if (!bio) {
        throw std::runtime_error("Failed to create BIO from public key string");
    }

    // Read the public key from the BIO
    _clientKeyPair =  PEM_read_bio_PUBKEY(bio, nullptr, nullptr, nullptr);

    if (!_clientKeyPair) {
        throw std::runtime_error("Failed to create EVP_PKEY from public key string");
    }

    //std::cout << "Client public key saved" << std::endl;
}


std::string EncryptionManager::encrypt(const std::string &plaintext){

    unsigned char encryptedData[EVP_PKEY_size(_clientKeyPair)];
    EVP_PKEY_CTX *ctx;
    if(!(ctx = EVP_PKEY_CTX_new(_clientKeyPair, nullptr))) {
        std::cerr << "Error creating context" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (EVP_PKEY_encrypt_init(ctx) != 1) {
        throw std::runtime_error("Failed to initialize encryption");
    }
    size_t outlen;
    if (EVP_PKEY_encrypt(ctx, encryptedData, &outlen, reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length()) != 1) {
        throw std::runtime_error("Encryption failed");
    }

    return unsignedCharToString(encryptedData, EVP_PKEY_size(_clientKeyPair));
}

std::string EncryptionManager::decrypt(std::string cypherText){
    unsigned char cypherTextUnsignedChar[EVP_PKEY_size(_keyPair)];
    charToUnsignedChar(cypherText, cypherTextUnsignedChar, EVP_PKEY_size(_keyPair));

    unsigned char decryptedData[EVP_PKEY_size(_keyPair)];
    EVP_PKEY_CTX *ctx;
    if(!(ctx = EVP_PKEY_CTX_new(_keyPair, nullptr))) {
        std::cerr << "Error creating context" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (EVP_PKEY_decrypt_init(ctx) != 1) {
        throw std::runtime_error("Failed to initialize encryption");
    }
    size_t outlen;

    if (EVP_PKEY_decrypt(ctx, decryptedData, &outlen, cypherTextUnsignedChar, EVP_PKEY_size(_keyPair)) <= 0){
        std::cerr << "Error decrypting" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string decryptedStr = unsignedCharToReadableString(decryptedData, EVP_PKEY_size(_keyPair));
    return decryptedStr;
}



std::string EncryptionManager::unsignedCharToString(unsigned char* encryptedData, int len){

    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, encryptedData, len);
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bufferPtr);
    char base64Ciphertext[1024];
    memcpy(base64Ciphertext, bufferPtr->data, bufferPtr->length - 1);
    (base64Ciphertext)[bufferPtr->length - 1] = '\0'; // Null-terminate the string

    // Clean up
    BIO_free_all(bio);
    return std::string(base64Ciphertext);

    //for (int i = 0; i < len; ++i) {
    //    charArray[i] = static_cast<char>(encryptedData[i] - 127);
    //}
}

std::string EncryptionManager::unsignedCharToReadableString(unsigned char* decryptedData, int len){
    return std::string(reinterpret_cast<char*>(decryptedData));
}

void EncryptionManager::charToUnsignedChar(std::string base64Ciphertext,unsigned char* decodedCiphertext, int len){
    BIO *bio, *b64;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new_mem_buf(base64Ciphertext.c_str(), -1); // -1 means null-terminated string
    bio = BIO_push(b64, bio);

    int decodedLength = BIO_read(bio, decodedCiphertext, base64Ciphertext.size());
    if (decodedLength <= 0) {
        BIO_free_all(bio);
        std::cout << "Error decoding Base64" << std::endl;
    }

    // Clean up
    BIO_free_all(bio);
    

    //for (int i = 0; i < len; ++i) {
    //    unsignedCharArray[i] = static_cast<unsigned char>(data[i] + 127);
    //}
}