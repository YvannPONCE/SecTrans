#include <algorithm>

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

std::string EncryptionManager::getServerPublicKey(){
    BIO* bio = BIO_new(BIO_s_mem());

    if (!bio) {
        throw std::runtime_error("Failed to create BIO");
    }

    if (PEM_write_bio_PUBKEY(bio, _serverKeyPair) != 1) {
        throw std::runtime_error("Failed to print public key");
    }
    size_t bioLength = BIO_ctrl_pending(bio);

    std::string publicKeyString(bioLength, '\0');
    BIO_read(bio, publicKeyString.data(), bioLength);

    return publicKeyString;
}

// ENREGISTRE LA CLE PUBLIQUE DE SON INTERLOCUTEUR
void EncryptionManager::setServerPublicKey(std::string serverPublicKey){
    BIO* bio = BIO_new_mem_buf(serverPublicKey.data(), serverPublicKey.size()), BIO_Deleter();

    if (!bio) {
        throw std::runtime_error("Failed to create BIO from public key string");
    }

    // Read the public key from the BIO
    _serverKeyPair =  PEM_read_bio_PUBKEY(bio, nullptr, nullptr, nullptr);

    if (!_serverKeyPair) {
        throw std::runtime_error("Failed to create EVP_PKEY from public key string");
    }

    //std::cout << "Server public key saved" << std::endl;
}


char* EncryptionManager::encrypt(const std::string& plaintext){
    setServerPublicKey(getPublicKey());
    unsigned char encryptedData[EVP_PKEY_size(_serverKeyPair)];
    EVP_PKEY_CTX *ctx;
    if(!(ctx = EVP_PKEY_CTX_new(_keyPair, nullptr))) {
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

    std::cout << std::endl;
    for(int i=0; i< EVP_PKEY_size(_serverKeyPair); ++i){
        std::cout << static_cast<int>(encryptedData[i]) << " "; 
    }
    std::cout << std::endl;
    

    char charArray[EVP_PKEY_size(_serverKeyPair)];
    unsignedCharToChar(encryptedData, charArray, EVP_PKEY_size(_serverKeyPair));
    decrypt(charArray);
    return nullptr;
}

std::string EncryptionManager::decrypt(char* cypherText){
    unsigned char cypherTextUnsignedChar[EVP_PKEY_size(_keyPair)];
    charToUnsignedChar(cypherText, cypherTextUnsignedChar, EVP_PKEY_size(_keyPair));

    std::vector<unsigned char> decryptedData(EVP_PKEY_size(_keyPair));
    EVP_PKEY_CTX *ctx;
    if(!(ctx = EVP_PKEY_CTX_new(_keyPair, nullptr))) {
        std::cerr << "Error creating context" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (EVP_PKEY_decrypt_init(ctx) != 1) {
        throw std::runtime_error("Failed to initialize encryption");
    }
    size_t outlen;

    if (EVP_PKEY_decrypt(ctx, decryptedData.data(), &outlen, cypherTextUnsignedChar, EVP_PKEY_size(_keyPair)) <= 0){
        std::cerr << "Error decrypting" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << std::endl;
    for(int i=0; i< EVP_PKEY_size(_serverKeyPair); ++i){
        std::cout << static_cast<int>(decryptedData[i]) << " "; 
    }
    std::cout << std::endl;

    std::string decryptedStr(decryptedData.begin(), decryptedData.end());
    std::cout << decryptedStr << std::endl;


    return decryptedStr;
}



void EncryptionManager::unsignedCharToChar(unsigned char* encryptedData, char* charArray, int len){
    for (int i = 0; i < len; ++i) {
        charArray[i] = static_cast<char>(encryptedData[i] - 127);
    }
}

void EncryptionManager::charToUnsignedChar(char* data,unsigned char* unsignedCharArray, int len){
    for (int i = 0; i < len; ++i) {
        unsignedCharArray[i] = static_cast<unsigned char>(data[i] + 127);
    }
}