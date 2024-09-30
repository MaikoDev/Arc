#include "ThreadPool.h"

namespace MaikoDev{
    namespace Arc {
        namespace MT {
            ThreadPool::ThreadPool(const unsigned int maxThreads) {
                _numberOfThreads = std::min<unsigned int>(maxThreads, std::thread::hardware_concurrency());

                /* Create coordinator thread */
                auto coordinatorResources = std::make_shared<ThreadInstance>(0);

                _threadPtrs = new std::thread[_numberOfThreads + 1];

                _instancesResources.push_back(coordinatorResources);
                _threadPtrs[0] = std::thread(&ThreadPool::coordinatorRoutine, this, coordinatorResources);

                /* Create worker threads */
                for (unsigned int i = 1; i <= _numberOfThreads; i++) {
                    auto threadResources = std::make_shared<ThreadInstance>(i);

                    _threadPtrs[i] = std::thread(&ThreadPool::workerRoutine, this, threadResources);

                    _instancesResources.push_back(threadResources);
                    _availableWorkers.push_back(threadResources);
                }
            }

            ThreadPool::~ThreadPool() {
                for (unsigned int i = 0; i <= _numberOfThreads; i++) {
                    auto& instance = _instancesResources[i];

                    instance->task = nullptr;
                    instance->isThreadPoolAlive = false;

                    instance->isTaskAssigned.notify_one();
                    _threadPtrs[i].join();
                }

                _instancesResources.clear();

                delete[] _threadPtrs;
            }

            void ThreadPool::complete(const TaskPtr& task, void(*callbackFunc)()) {
                std::unique_lock completeLock(_completeMutex);

                this->run(task);
                _isTasksComplete.wait(completeLock, [&]{
                    return task->isComplete();
                });

                if (callbackFunc) callbackFunc();
            }

            void ThreadPool::complete(const std::deque<TaskPtr>& tasks, void(*callbackFunc)()) {
                std::unique_lock completeLock(_completeMutex);

                this->run(tasks);
                _isTasksComplete.wait(completeLock, [&]{ 
                    bool isComplete = true;
                    for (auto& task : tasks) {
                        isComplete &= task->isComplete();

                        if (!isComplete) {
                            _instancesResources.front()->isTaskAssigned.notify_one();
                            break;
                        }
                    }

                    return isComplete;
                });

                if (callbackFunc) callbackFunc();
            }

            void ThreadPool::run(const TaskPtr& task) {
                if (task == nullptr) return;

                _taskQueue.push_back(task);
                _instancesResources.front()->isTaskAssigned.notify_one();
            }

            void ThreadPool::run(const std::deque<TaskPtr>& tasks) {
                if (tasks.size() == 0) return;

                for (auto& task : tasks) {
                    _taskQueue.push_back(task);
                }

                _instancesResources.front()->isTaskAssigned.notify_one();
            }

            void ThreadPool::coordinatorRoutine(std::shared_ptr<ThreadInstance> instance) {
                std::unique_lock taskLock(instance->taskMutex);

                while (instance->isThreadPoolAlive) {
                    instance->isTaskAssigned.wait(taskLock, [=]() { 
                        return (!_taskQueue.empty() || !instance->isThreadPoolAlive) && !_availableWorkers.empty();
                    });

                    if (!instance->isThreadPoolAlive) return;

                    /* Assign a thread instance a new task if available */
                    {
                        std::unique_lock availableLock(_availableMutex);

                        // assign instances
                        while (!_taskQueue.empty() && !_availableWorkers.empty()) {
                            std::shared_ptr<ThreadInstance> availableWorker = _availableWorkers.back();

                            availableWorker->task = _taskQueue.front();

                            _availableWorkers.pop_back();
                            _taskQueue.pop_front();

                            availableWorker->isTaskAssigned.notify_one();
                        }
                    }
                }
            }

            void ThreadPool::workerRoutine(std::shared_ptr<ThreadInstance> instance) {
                std::unique_lock taskLock(instance->taskMutex);

                while (instance->isThreadPoolAlive) {
                    instance->isTaskAssigned.wait(taskLock, [=]() {
                        return instance->task != nullptr || !instance->isThreadPoolAlive;
                    });

                    if (!instance->isThreadPoolAlive) return;

                    instance->task->run();
                    instance->task = nullptr;

                    // Add current worker back to available list //
                    {
                        std::unique_lock availableLock(_availableMutex);
                        _availableWorkers.push_back(instance);
                    }

                    _isTasksComplete.notify_one();
                }
            }
        }
    }
}