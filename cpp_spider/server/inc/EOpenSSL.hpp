//
// Created by Yan on 10/2/2017.
//

#ifndef PROJECT_EOPENSSL_HPP
#define PROJECT_EOPENSSL_HPP

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <fstream>
#include <iostream>
#include "AEncryption.hpp"

# define BITS_KEY (2048)
# define DIR_KEYS "./OpenSSL/"

namespace spider {
    class EOpenSSL : public AEncryption{
    public:
        EOpenSSL();
        virtual ~EOpenSSL();
        const std::string   init(std::string const & ip);
        bool                generate_keys();
        bool                initRsaFromFile();
        const std::string   handShake() const;
        const std::string   encrypt(std::string const & ) const;
        const std::string   decrypt(std::string const & ) const;

    private:
        RSA                 * publicKey;
        RSA                 * privateKey;
    };
}

#endif //PROJECT_EOPENSSL_HPP
