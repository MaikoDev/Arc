#pragma once

#include <vector>

#include <mt/Task.h>

namespace MaikoDev {
    namespace Arc {
        namespace Tasks {
            /*class WaitForThreadTasks : public MT::Task {
            public:
                const unsigned int& getTaskCount() const& { return _tasks.size(); }
            protected:
                virtual void onRun() override final;
            private:
                WaitForThreadTasks(const MT::TaskPtr& task);
                WaitForThreadTasks(const std::vector<MT::TaskPtr>& tasks);
            private:
                std::vector<MT::TaskPtr> _tasks;
            };*/
        }
    }
}