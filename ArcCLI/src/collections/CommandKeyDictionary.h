#pragma once

#include <string>
#include <tuple>

#include <commands/CommandType.h>

namespace MaikoDev {
    namespace Arc {
        namespace Collections {
            class CommandKeyMap {
            public:
                CommandKeyMap();
                CommandKeyMap(const std::initializer_list<std::pair<std::string, Commands::CommandType>>& args);
                ~CommandKeyMap();

                const Commands::CommandType& get(std::string key) const&;
                const Commands::CommandType& end() const&;
            private:
                const unsigned int getIndex(std::string key) const;
            private:
                unsigned short _bufferLength;
                Commands::CommandType* _commandBindBuffer;
            };
        }
    }
}