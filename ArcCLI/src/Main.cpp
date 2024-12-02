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

#include "reflective/FunctionParams.h";
#include "memory/ByteContainer.h"

using namespace MaikoDev::Arc;

int main(int argc, char** args) {
    std::string input;

    fs::path workingDirectory = fs::current_path();

    fs::path arc = fs::proximate(".arc");
    std::string arcName = typeid(arcName).name();

    /*std::byte* exampleData = static_cast<std::byte*>(calloc(4, 1));
    memset(exampleData, 42, 4);

    Memory::ByteContainer container;
    uint32_t testNum = 43;

    container
        .append(&testNum, sizeof(uint32_t))
        .append(exampleData, 4)
        .append(arcName);

    free(exampleData);

    auto rawNumberData = container.getData(4, 8);
    auto rawData = container.getData(8, container.dataSize() - 1);

    auto numberData = Memory::ByteContainer::ConvertData<uint32_t>(std::move(rawNumberData));
    auto testData = Memory::ByteContainer::ConvertData<std::string>(std::move(rawData));
    
    std::cout << *numberData << std::endl;
    std::cout << *testData << std::endl;

    auto otherContainer = container.subrange(8, container.dataSize());
    auto otherNumberData = Memory::ByteContainer::ConvertData<std::string>(otherContainer->getData());
    otherContainer->append(container);

    std::cout << *otherNumberData << std::endl;*/

    Reflective::FunctionParams testParams;
    Reflective::FunctionParams emptyParams;
    Reflective::FunctionParams altParams;
    Reflective::FunctionParams closeParams;

    altParams.registerParam("xpos", 4.32f);
    altParams.registerParam("xvel", 54.23);
    altParams.registerParam("name", std::string("alvin"));
    altParams.registerParam("health", 42);

    closeParams.registerParam("xpos", 5.32f);
    closeParams.registerParam("xvel", 2345.32);
    closeParams.registerParam("name", std::string("victor"));
    closeParams.registerParam("health", 28);

    std::cout << testParams.registerParam("arcPath", arc) << std::endl;
    std::cout << testParams.registerParam("secretCount", 42) << std::endl;

    std::cout << *testParams.getParameter<fs::path>("arcPath") << std::endl;
    std::cout << *testParams.getParameter<int>("secretCount") << std::endl;

    std::cout << *altParams.getParameter<float>("xpos") << std::endl;
    std::cout << *altParams.getParameter<double>("xvel") << std::endl;
    std::cout << *altParams.getParameter<std::string>("name") << std::endl;

    std::cout << testParams.matches(altParams) << std::endl;
    std::cout << altParams.matches(closeParams) << std::endl;
    std::cout << closeParams.matches(altParams) << std::endl;

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