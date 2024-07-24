#pragma comment(lib, "crypt32")
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <sstream>
#include <iomanip>
#include <queue>
#include <filesystem>>

#include <commands/CommandData.h>
#include <commands/CommandType.h>
#include <commands/CommandFactory.h>

#include <collections/CommandKeyDictionary.h>
#include <exceptions/UninitializedRepoException.h>
#include <exceptions/CommandRuntimeException.h>

#include <ArcCLI.h>

#include <openssl/sha.h>

using namespace MaikoDev::Arc;

int main(int argc, char** args) {
    std::string input;

    fs::path workingDirectory = fs::current_path();

    fs::path arc = fs::proximate(".arc");

    std::cout << fs::absolute(arc) << std::endl;
    
    try {
        ArcCLI app(workingDirectory, argc, args);
    }
    catch (Exceptions::NonValidCommandException& ex) {
        printf("arc: '%s' is not a arc command. See 'arc --help'.\n", ex.what());
    }
    catch (Exceptions::ArcRuntimeException& ex) {
        printf("%s\n", ex.what());
    }

    /*for (auto const& dir : fs::recursive_directory_iterator(fs::current_path())) {
        std::cout << dir << std::endl;
    }*/

    std::cin >> input;

    return 0;
}