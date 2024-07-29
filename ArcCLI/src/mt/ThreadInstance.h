#pragma once

#include <mutex>
#include <memory>
#include <condition_variable>

#include "mt/Task.h"

namespace MaikoDev {
    namespace Arc {
        namespace MT {
            struct ThreadInstance {
                ThreadInstance(unsigned int threadIndex) : threadIndex(threadIndex) {}

                unsigned int threadIndex = 0;
                bool isThreadPoolAlive = true;
                std::mutex taskMutex;

                std::condition_variable isTaskAssigned;
                TaskPtr task = nullptr;
            };
        }
    }
}