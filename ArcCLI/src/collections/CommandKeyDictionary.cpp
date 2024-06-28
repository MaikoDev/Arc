#include "collections/CommandKeyDictionary.h"

#include <iostream>
#include <memory>

namespace MaikoDev {
    namespace Arc {
        namespace Collections {
            static Commands::CommandType EMPTY = Commands::CommandType::UNDEFINED;

            CommandKeyMap::CommandKeyMap() {
                _bufferLength = USHRT_MAX;
                _commandBindBuffer = (Commands::CommandType*)calloc(_bufferLength, sizeof(Commands::CommandType));
            }

            CommandKeyMap::CommandKeyMap(const std::initializer_list<std::pair<std::string, Commands::CommandType>>& args) {
                _bufferLength = USHRT_MAX;
                _commandBindBuffer = (Commands::CommandType*)calloc(_bufferLength, sizeof(Commands::CommandType));

                for (auto& arg : args) {
#ifdef _DEBUG
                    unsigned int index = getIndex(arg.first);
                    printf("%i: %i\n", index, index % _bufferLength);

                    if (_commandBindBuffer[index % _bufferLength] != Commands::CommandType::UNDEFINED) {
                        std::cout << "COLLISION" << std::endl;
                    }

                    _commandBindBuffer[index % _bufferLength] = arg.second;
#else
                    _commandBindBuffer[getIndex(arg.first) % _bufferLength] = arg.second;
#endif
                }
            }

            CommandKeyMap::~CommandKeyMap() {
                free(_commandBindBuffer);
            }

            const inline unsigned int CommandKeyMap::getIndex(std::string key) const {
                const char* keyString = key.c_str();
                size_t keySize = key.size();

                unsigned int hash = ((keyString[0] ^ keyString[1 % keySize]) ^ keyString[keySize - 1]) << 8;

                hash |= (keyString[keySize - 2] ^ keyString[keySize - 1]) ^ keyString[0];
                hash -= 8224;

                return hash;
            }

            const Commands::CommandType& CommandKeyMap::get(std::string key) const& {
                unsigned int index = getIndex(key);
                if (index >= _bufferLength) return EMPTY;

                return _commandBindBuffer[index];
            }

            const Commands::CommandType& CommandKeyMap::end() const& { return EMPTY; }
        }
    }
}