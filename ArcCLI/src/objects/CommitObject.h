#pragma once

#include <objects/TrackedObject.h>
#include <objects/TreeObject.h>

namespace MaikoDev {
    namespace Arc {
        namespace Objects {
            typedef std::shared_ptr<CommitObject> ParentRef;

            class CommitObject : public TrackedObject {
            public:
                virtual void deserialize(const char*) override;
            protected:
                virtual const std::string const& getChecksum() override;
                virtual const std::string const& getContent() override;
                virtual const TrackedType& const getType() override;
                virtual const std::string& const getTypeStr() override;
            private:
                std::shared_ptr<TreeObject> _fileStructure;
                std::pair<ParentRef, ParentRef> _parents;

                std::string _author;
                std::string _commiter;

                std::string _message;
            };
        }
    }
}