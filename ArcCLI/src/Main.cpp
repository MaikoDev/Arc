#pragma comment(lib, "crypt32")
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <sstream>
#include <iomanip>
#include <queue>

#include <commands/CommandData.h>
#include <commands/CommandType.h>
#include <commands/CommandFactory.h>

#include <openssl/sha.h>

using namespace MaikoDev::Arc;

int main(int argc, char** args) {

    std::unique_ptr<Commands::CommandData> commandData = Commands::extractCommand(argc, args);
    if (!commandData) return 0;

    Commands::CommandFactory factory;
    {
        auto t = factory.getCommand(std::move(commandData));
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    std::string inputMessage = "Hello World";
    std::stringstream ss;

    std::unique_ptr<unsigned char*> testPtr = std::make_unique<unsigned char*>(new unsigned char[inputMessage.length() + 1]);
    memcpy(*testPtr, inputMessage.c_str(), inputMessage.length());
    (*testPtr.get())[inputMessage.length()] = (unsigned char)'\0';

    std::shared_ptr<unsigned char*> shared = std::move(testPtr);

    SHA256((unsigned char*)inputMessage.c_str(), inputMessage.length(), hash);

    for (unsigned int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)hash[i];

    std::cout << ss.str() << std::endl;
    std::cin >> inputMessage;

    return 0;
}