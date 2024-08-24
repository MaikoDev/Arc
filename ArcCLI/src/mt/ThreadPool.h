#pragma once

#include <thread>
#include <mutex>
#include <vector>
#include <deque>

#include "mt/ThreadInstance.h"

namespace MaikoDev {
    namespace Arc {
        namespace MT {
            class ThreadPool {
            public:
                ThreadPool(const unsigned int maxThreads = std::thread::hardware_concurrency());
                ~ThreadPool();

                void complete(const TaskPtr& task, void(*callbackFunc)() = nullptr);
                void complete(const std::deque<TaskPtr>& tasks, void(*callbackFunc)() = nullptr);

                void run(const TaskPtr& task);
                void run(const std::deque<TaskPtr>& tasks);

                const unsigned int& getThreadCount() const& { return _numberOfThreads; }
            private:
                void coordinatorRoutine(std::shared_ptr<ThreadInstance> instance);
                void workerRoutine(std::shared_ptr<ThreadInstance> instance);
                inline void nextTask(const std::shared_ptr<ThreadInstance>& instance);
            private:
                std::thread* _threadPtrs;
                unsigned int _numberOfThreads;

                std::deque<TaskPtr> _taskQueue;
                /*std::vector<TaskPtr> _taskBuffer;*/
                std::vector<std::shared_ptr<ThreadInstance>> _instancesResources;
                std::vector<std::shared_ptr<ThreadInstance>> _availableWorkers;

                std::mutex _availableMutex;
                std::condition_variable _isTaskAvailable;

                std::mutex _completeMutex;
                std::condition_variable _isTasksComplete;
            };
        }
    }
}