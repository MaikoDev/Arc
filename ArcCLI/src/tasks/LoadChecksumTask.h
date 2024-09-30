#pragma once

#include "mt/Task.h"
#include "objects/BlobObject.h"

namespace MaikoDev {
    namespace Arc {
        namespace Tasks {
            class LoadChecksumTask : public MT::Task {
            public:
                LoadChecksumTask(std::shared_ptr<Objects::BlobObject> blob) : _blob(blob) {}
            protected:
                virtual void onTaskRun() override final {
                    
                }
            private:
                std::shared_ptr<Objects::BlobObject> _blob;
            };
        }
    }
}