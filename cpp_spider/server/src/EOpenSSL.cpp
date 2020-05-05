//
// Created by Yan on 10/2/2017.
//

#include <stdio.h>
#include <string.h>
#include "EOpenSSL.hpp"
#include "Tools.hpp"

spider::EOpenSSL::EOpenSSL()
{
    publicKey = NULL;
    privateKey = NULL;
    Tools::checkDir(DIR_KEYS);
}

spider::EOpenSSL::~EOpenSSL()
{
}

const std::string   spider::EOpenSSL::init(const std::string & ip)
{
    std::ifstream   checkprivate(DIR_KEYS + ip + "-private.pem");
    std::ifstream   checkpublic(DIR_KEYS + ip + "-public.pem");

    this->ip = ip;
    if (checkprivate.good() && checkpublic.good())
    {
        Tools::printServerLogClassic("Encryption : keys exist, checking validity", "Server");
        active = initRsaFromFile();
    }
    if (active == false)
    {
        Tools::printServerLogClassic("Encryption : generating keys", "Server");
        active = generate_keys();
        active = (active == false) ? false : initRsaFromFile();
    }
    if (active == false)
        Tools::printServerLogRed("Encryption : Error", "Server");
    else
        Tools::printServerLogGreen("Encryption : Successful", "Server");
    return (handShake());
}

bool                spider::EOpenSSL::initRsaFromFile()
{
    FILE            *publicFile;
    FILE            *privateFile;

    if ((publicFile = fopen(std::string(DIR_KEYS + this->ip + "-public.pem").c_str(), "rb")) == NULL)
        return (false);
    publicKey = RSA_new();
    publicKey = PEM_read_RSAPublicKey(publicFile, &publicKey, NULL, NULL);
    if ((privateFile = fopen(std::string(DIR_KEYS + this->ip + "-private.pem").c_str(), "rb")) == NULL)
        return (false);
    privateKey = RSA_new();
    privateKey = PEM_read_RSAPrivateKey(privateFile, &privateKey, NULL, NULL);
    if (privateKey == NULL || publicKey == NULL)
    {
        Tools::printServerLogRed("Encryption : failed RSA generation", "Server");
        return (false);
    }
    return (true);
}

bool                spider::EOpenSSL::generate_keys()
{
    BIO             *public_key;
    BIO             *private_key;
    RSA             *rsa;
    BIGNUM          *bignum;

    bignum = BN_new();
    if (BN_set_word(bignum, RSA_F4) != 1)
        return (false);
    rsa = RSA_new();
    if (RSA_generate_key_ex(rsa, BITS_KEY, bignum, NULL) != 1)
        return (false);
    public_key = BIO_new_file(std::string(DIR_KEYS + this->ip + "-public.pem").c_str(), "w+");
    if (PEM_write_bio_RSAPublicKey(public_key, rsa) != 1)
        return (false);
    private_key = BIO_new_file(std::string(DIR_KEYS + this->ip + "-private.pem").c_str(), "w+");
    if (PEM_write_bio_RSAPrivateKey(private_key, rsa, NULL, NULL, 0, NULL, NULL) != 1)
        return (false);
    BIO_free_all(public_key);
    BIO_free_all(private_key);
    RSA_free(rsa);
    BN_free(bignum);
    return (true);
}

const std::string       spider::EOpenSSL::handShake() const
{
    std::ifstream       reader(std::string(DIR_KEYS + this->ip + "-public.pem").c_str());
    std::string         back((std::istreambuf_iterator<char>(reader)), std::istreambuf_iterator<char>());

    return(back);
}

const std::string       spider::EOpenSSL::encrypt(const std::string & toEncrypt) const
{
    std::string         data;
    std::string         back;
    unsigned char       encrypt[245];
    unsigned char       encrypted[256];
    int                 length;

    data.assign(toEncrypt);
    if (active == false)
        return (data);
    while (data.size() > 0)
    {
        length = (data.length() < 245) ? data.length() : 245;
        data.copy(reinterpret_cast<char*>(encrypt), length);
        bzero(encrypted, 256);
        RSA_public_encrypt(length, encrypt, encrypted, publicKey, RSA_PKCS1_PADDING);
        back.append(std::string(reinterpret_cast<char*>(encrypted), 256));
        data.erase(0, length);
    }
    return (back);
}

const std::string       spider::EOpenSSL::decrypt(const std::string & toDecrypt) const
{
    std::string         data;
    std::string         back;
    unsigned char       encrypted[257];
    unsigned char       decrypted[245];
    int                 decrypt_length;

    data.assign(toDecrypt);
    if (active == false)
        return (data);
    while (data.size() > 0)
    {
        data.copy(reinterpret_cast<char*>(encrypted), 256);
        encrypted[256] = '\0';
        bzero(decrypted, 245);
        decrypt_length = RSA_private_decrypt(256, encrypted, decrypted, privateKey, RSA_PKCS1_PADDING);
        if (decrypted[0] == 0)
            return ("");
        back.append(std::string(reinterpret_cast<char*>(decrypted), decrypt_length));
        data.erase(0, 256);
    }
    return (back);
}
