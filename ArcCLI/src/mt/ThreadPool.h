#pragma once

#include <thread>
#include <vector>

#include "mt/ThreadInstance.h"

namespace MaikoDev {
    namespace Arc {
        namespace MT {
            class ThreadPool {
            public:
                ThreadPool(const unsigned int maxThreads = std::thread::hardware_concurrency());
                ~ThreadPool();

                void complete(const TaskPtr& task);
                void complete(const std::vector<TaskPtr>& tasks);

                void run(const TaskPtr& task);
                void run(const std::vector<TaskPtr>& tasks);

                const unsigned int& getThreadCount() const& { return _numberOfThreads; }
            private:
                void threadRoutine(std::shared_ptr<ThreadInstance> instance);
                inline void nextTask(const std::shared_ptr<ThreadInstance>& instance);
            private:
                std::thread* _threadPtrs;
                unsigned int _numberOfThreads;

                std::vector<TaskPtr> _taskBuffer;
                std::vector<std::shared_ptr<ThreadInstance>> _instancesResources;

                std::mutex _completeMutex;
                std::condition_variable _isTasksComplete;
            };
        }
    }
}