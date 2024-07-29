#pragma once

#include <memory>

#include "mt/IRunnable.h"

namespace MaikoDev {
    namespace Arc {
        namespace MT {
            class Task : public IRunnable {
            public:
                virtual void run() override final {
                    _isTaskRunning = true;
                    onRun();

                    _isTaskRunning = false;
                    _isComplete = true;
                }

                void reset() { onReset(); _isComplete = false; }

                const unsigned int& getTaskId() const& { return _taskId; }
                const bool& isTaskRunning() const& { return _isTaskRunning; }
                const bool& isComplete() const& { return _isComplete; }
            protected:
                virtual void onRun() = 0;
                virtual void onReset() {};
            private:
                const unsigned int _taskId;
                bool _isTaskRunning = false;
                bool _isComplete = false;
            };

            typedef std::shared_ptr<Task> TaskPtr;
        }
    }
}