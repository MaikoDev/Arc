#pragma once

#include <iostream>
#include <string>

#include "Task.h"

namespace MaikoDev {
    namespace Arc {
        namespace MT {
            class CountingTask : public Task {
            public:
                CountingTask(const unsigned int minRange, const unsigned int maxRange, std::mutex& printMutex) : _minRange(minRange), _maxRange(maxRange), _printMutex(printMutex) {}
            protected:
                virtual void onTaskRun() override final {
                    std::string countMessage = "";
                    for (unsigned int count = _minRange; count <= _maxRange; count++) {
                        countMessage.append(std::to_string(count));
                        countMessage.append(",");
                    }

                    {
                        std::unique_lock consoleLock(_printMutex);
                        std::cout << countMessage << std::endl;
                    }
                }
            private:
                unsigned int _minRange;
                unsigned int _maxRange;

                std::mutex& _printMutex;
            };
        }
    }
}