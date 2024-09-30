#pragma once

#include <memory>

#include "mt/IRunnable.h"

namespace MaikoDev {
    namespace Arc {
        namespace MT {
            class Task : public IRunnable {
            public:
                Task() {}
                virtual void run() override final {
                    _isTaskRunning = true;
                    onTaskRun();

                    _isTaskRunning = false;
                    _isComplete = true;

                    onTaskFinish();
                }

                void reset() { onTaskReset(); _isComplete = false; }

                const unsigned int& getTaskId() const& { return _taskId; }
                const bool& isTaskRunning() const& { return _isTaskRunning; }
                const bool& isComplete() const& { return _isComplete; }
            protected:
                virtual void onTaskRun() = 0;
                virtual void onTaskFinish() {};
                virtual void onTaskReset() {};
            private:
                const unsigned int _taskId = 0;
                bool _isTaskRunning = false;
                bool _isComplete = false;
            };

            typedef std::shared_ptr<Task> TaskPtr;
        }
    }
}