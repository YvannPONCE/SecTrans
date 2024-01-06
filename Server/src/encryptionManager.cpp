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
    unsigned char* buffer = nullptr;
    int length = i2d_PUBKEY(_keyPair, &buffer);
    if (length <= 0 || buffer == nullptr) {
        std::cerr << "Error converting public key to string" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string public_key_str(reinterpret_cast<const char*>(buffer), length);
    OPENSSL_free(buffer);

    return public_key_str;
}

std::string EncryptionManager::getClientPublicKey(){
    unsigned char* buffer = nullptr;
    int length = i2d_PUBKEY(_clientKeyPair, &buffer);
    if (length <= 0 || buffer == nullptr) {
        std::cerr << "Error converting public key to string" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string public_key_str(reinterpret_cast<const char*>(buffer), length);
    OPENSSL_free(buffer);

    return public_key_str;
}

void EncryptionManager::setClientPublicKey(std::string serverPublicKey){
    const unsigned char* data = reinterpret_cast<const unsigned char*>(serverPublicKey.c_str());
    _clientKeyPair = d2i_PUBKEY(nullptr, &data, serverPublicKey.length());
    if (!_clientKeyPair) {
        std::cerr << "Error recreating public key from string" << std::endl;
        exit(EXIT_FAILURE);
    }
}


std::string EncryptionManager::encrypt(const std::string& plaintext){
    std::vector<unsigned char> encryptedData(EVP_PKEY_size(_clientKeyPair));
    EVP_PKEY_CTX *ctx;
    if(!(ctx = EVP_PKEY_CTX_new(_clientKeyPair, nullptr))) {
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
