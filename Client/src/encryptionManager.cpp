#include <algorithm>

#include "./../header/encryptionManager.h"

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

    if (EVP_PKEY_print_public(bio, _serverKeyPair, 0, nullptr) != 1) {
        throw std::runtime_error("Failed to print public key");
    }
    size_t bioLength = BIO_ctrl_pending(bio);

    std::string publicKeyString(bioLength, '\0');
    BIO_read_ex(bio, publicKeyString.data(), bioLength, &bioLength);

    return publicKeyString;
}

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
}


std::string EncryptionManager::encrypt(const std::string& plaintext){
    std::vector<unsigned char> encryptedData(EVP_PKEY_size(_serverKeyPair));
    EVP_PKEY_CTX *ctx;
    if(!(ctx = EVP_PKEY_CTX_new(_serverKeyPair, nullptr))) {
        std::cerr << "Error creating context" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (EVP_PKEY_encrypt_init(ctx) != 1) {
        throw std::runtime_error("Failed to initialize encryption");
    }
    size_t outlen;
    if (EVP_PKEY_encrypt(ctx, encryptedData.data(), &outlen, reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length()) != 1) {
        throw std::runtime_error("Encryption failed");
    }

    std::string encryptedStr(encryptedData.begin(), encryptedData.end());

    return encryptedStr;
}

std::string EncryptionManager::decrypt(std::string cypherText){
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

    if (EVP_PKEY_decrypt(ctx, decryptedData.data(), &outlen, reinterpret_cast<const unsigned char*>(cypherText.c_str()), cypherText.length()) <= 0){
        std::cerr << "Error decrypting" << std::endl;
        exit(EXIT_FAILURE);
    }


    std::string decryptedStr(decryptedData.begin(), decryptedData.end());

    return decryptedStr;
}
