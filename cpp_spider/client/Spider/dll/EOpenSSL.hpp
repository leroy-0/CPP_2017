//
// Created by Yan on 10/2/2017.
//

#ifndef PROJECT_EOPENSSL_HPP
#define PROJECT_EOPENSSL_HPP

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "AEncryption.hpp"

# define BITS_KEY (2048)
# define DIR_KEYS "./OpenSSL/"


namespace spider {
    class EOpenSSL : public AEncryption{
    public:
        EOpenSSL();
        virtual ~EOpenSSL();
        void                init(std::string const & key);
		bool                initRsaFromText(const std::string & key);
        const std::string   encrypt(std::string const & ) const;
        const std::string   decrypt(std::string const & ) const;

    private:
        RSA                 * publicKey;
    };
}

#endif //PROJECT_EOPENSSL_HPP
