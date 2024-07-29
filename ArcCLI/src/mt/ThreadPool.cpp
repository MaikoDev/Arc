#include "ThreadPool.h"

namespace MaikoDev{
    namespace Arc {
        namespace MT {
            ThreadPool::ThreadPool(const unsigned int maxThreads) {
                _numberOfThreads = std::min<unsigned int>(maxThreads, std::thread::hardware_concurrency());

                _threadPtrs = new std::thread[_numberOfThreads];
                for (unsigned int i = 0; i < _numberOfThreads; i++) {
                    auto threadResources = std::make_shared<ThreadInstance>(i);

                    _instancesResources.push_back(threadResources);
                    _threadPtrs[i] = std::thread(&ThreadPool::threadRoutine, this, threadResources);
                }
            }

            ThreadPool::~ThreadPool() {
                for (unsigned int i = 0; i < _numberOfThreads; i++) {
                    auto& instance = _instancesResources[i];

                    instance->task = nullptr;
                    instance->isThreadPoolAlive = false;

                    instance->isTaskAssigned.notify_one();
                    _threadPtrs[i].join();
                }

                _instancesResources.clear();

                delete[] _threadPtrs;
            }

            void ThreadPool::complete(const TaskPtr& task) {
                if (task == nullptr) return;
                std::unique_lock<std::mutex> completeLock(_completeMutex);

                _taskBuffer.push_back(task);
                _isTasksComplete.wait(completeLock, task->isComplete());
            }

            void ThreadPool::complete(const std::vector<TaskPtr>& tasks) {
                if (tasks.size() == 0) return;
                std::unique_lock<std::mutex> completeLock(_completeMutex);

                for (auto& task : tasks) {
                    _taskBuffer.push_back(task);
                }

                _isTasksComplete.wait(completeLock, [=]() {
                    tasks
                    })
            }

            void ThreadPool::run(const TaskPtr& task) {
                
            }

            void ThreadPool::run(const std::vector<TaskPtr>& tasks) {

            }

            void ThreadPool::threadRoutine(std::shared_ptr<ThreadInstance> instance) {
                std::unique_lock<std::mutex> taskLock(instance->taskMutex);
                while (instance->isThreadPoolAlive) {
                    instance->isTaskAssigned.wait(taskLock, [=]() { return instance->task != nullptr || !instance->isThreadPoolAlive; });
                    if (!instance->isThreadPoolAlive) return;

                    instance->task->run();
                    instance->task = nullptr;

                    _isTasksComplete.notify_one();

                    //Callback function to add the next task if possible//
                    if (!_taskBuffer.empty()) nextTask(instance);
                }
            }

            inline void ThreadPool::nextTask(const std::shared_ptr<ThreadInstance>& instance) {
                instance->task = _taskBuffer.back();
                _taskBuffer.pop_back();
            }
        }
    }
}