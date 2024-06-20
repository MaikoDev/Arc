#pragma comment(lib, "crypt32")
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <sstream>
#include <iomanip>

#include <openssl/sha.h>

int main(int argc, char** args) {

    unsigned char hash[SHA256_DIGEST_LENGTH];
    std::string inputMessage = "Hello World";
    std::stringstream ss;

    SHA256((unsigned char*)inputMessage.c_str(), inputMessage.length(), hash);

    for (unsigned int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)hash[i];

    std::cout << ss.str() << std::endl;
    std::cin >> inputMessage;

    return 0;
}