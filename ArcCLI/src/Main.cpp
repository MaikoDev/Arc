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

#include <MT/ThreadPool.h>
#include <tasks/CountingTask.h>

#include <objects/TreeObject.h>

#include <ArcCLI.h>

#include <openssl/sha.h>

using namespace MaikoDev::Arc;

int main(int argc, char** args) {
    std::string input;

    fs::path workingDirectory = fs::current_path();

    fs::path arc = fs::proximate(".arc");

    std::shared_ptr<uint8_t> test = std::make_shared<uint8_t>(5);

    MT::ThreadPool pool;
    std::mutex printingMutex;

    std::deque<std::shared_ptr<MT::Task>> testTasks;
    for (unsigned int i = 0; i < 100; i += 10) {
        std::shared_ptr<MT::Task> task;
        task.reset(new Tasks::CountingTask(i, i + 9, printingMutex));

        testTasks.push_back(task);
    }

    std::cout << fs::absolute(arc) << std::endl;
    pool.complete(testTasks, []() {
        std::cout << "Completed!" << std::endl;
    });
    
    try {
        ArcCLI app(workingDirectory, argc, args);
    }
    catch (Exceptions::NonValidCommandException& ex) {
        printf("arc: '%s' is not a arc command. See 'arc --help'.\n", ex.what());
    }
    catch (Exceptions::ArcRuntimeException& ex) {
        printf("%s\n", ex.what());
    }

    return 0;
}