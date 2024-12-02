#pragma once
#pragma comment(lib, "crypt32")
#pragma comment(lib, "ws2_32.lib")

#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "openssl/evp.h"

namespace MaikoDev::Arc::Utils {
    /*void makeSHA1evp(const unsigned char text[]) {
        EVP_MD_CTX* mdctx;
        const EVP_MD* md;
        unsigned char md_value[EVP_MAX_MD_SIZE];
        unsigned int md_len;

        md = EVP_sha1();
        mdctx = EVP_MD_CTX_create();
        EVP_DigestInit_ex(mdctx, md, NULL);
        EVP_DigestUpdate(mdctx, text, sizeof(text) - 1);

        EVP_DigestFinal_ex(mdctx, md_value, &md_len);
        EVP_MD_CTX_destroy(mdctx);
        printf("Digest is: ");
        for (int i = 0; i < md_len; i++) {
            printf("%02x", md_value[i]);
        }
        printf("\\n");
        EVP_cleanup();
    }*/

    std::string SHA1Hash(std::unique_ptr<std::vector<std::byte>> data) {
        EVP_MD_CTX* mdctx;
        const EVP_MD* md;
        unsigned char md_value[EVP_MAX_MD_SIZE];
        unsigned int md_len;

        md = EVP_sha1();
        mdctx = EVP_MD_CTX_create();
        EVP_DigestInit_ex(mdctx, md, NULL);
        EVP_DigestUpdate(mdctx, data->data(), data->size());

        EVP_DigestFinal_ex(mdctx, md_value, &md_len);
        EVP_MD_CTX_destroy(mdctx);

        /* Convert hex of the hash to string */
        std::stringstream ss;
        for (unsigned int index = 0; index < md_len; index++) {
            const unsigned char& currentByte = md_value[index];
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(currentByte);
        }

        EVP_cleanup();

        return ss.str();
    }
}