//
// Created by Yan on 10/2/2017.
//

#include "stdafx.h"
#include "EOpenSSL.hpp"

#pragma warning(disable : 4996)
#pragma warning(disable : 4267)

spider::EOpenSSL::EOpenSSL()
{
    publicKey = NULL;
}

spider::EOpenSSL::~EOpenSSL()
{
}

void            spider::EOpenSSL::init(std::string const & key)
{
   active = initRsaFromText(key);
}

bool            spider::EOpenSSL::initRsaFromText(const std::string & key)
{
    BIO         *keybio;

    keybio = BIO_new_mem_buf(key.c_str(), -1);
    if (keybio == NULL)
    {
        std::cout << "Failed to create key BIO" << std::endl;
        return (false);
    }
	publicKey = RSA_new();
    publicKey = PEM_read_bio_RSAPublicKey(keybio, &publicKey, NULL, NULL);
    return (true);
}

const std::string       spider::EOpenSSL::encrypt(std::string const & toEncrypt) const
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
        memset(encrypted, 0, sizeof(encrypted));
        RSA_public_encrypt(length, encrypt, encrypted, publicKey, RSA_PKCS1_PADDING);
        back.append(std::string(reinterpret_cast<char*>(encrypted), 256));
        data.erase(0, length);
    }
    return (back);
}

const std::string       spider::EOpenSSL::decrypt(std::string const & toDecrypt) const
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
		memset(encrypted, 0, sizeof(encrypted));
        decrypt_length = RSA_public_decrypt(256, encrypted, decrypted, publicKey, RSA_PKCS1_PADDING);
        back.append(std::string(reinterpret_cast<char*>(decrypted), decrypt_length));
        data.erase(0, 256);
    }
    return (back);
}