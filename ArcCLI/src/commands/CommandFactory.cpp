#include "commands/CommandFactory.h"

#include <commands/StatusCommand.h>

namespace MaikoDev {
    namespace Arc {
        namespace Commands {
            static std::unordered_map<std::string, CommandType> CommandMap = {
                {"status", CommandType::Status},
                {"fetch", CommandType::Fetch},
                {"pull", CommandType::Pull},
                {"add", CommandType::Add},
                {"commit", CommandType::Commit},
            };

            inline const std::unique_ptr<CommandData> const extractCommand(int argc, char** args) {
                std::queue<std::unique_ptr<std::string>> argumentList;

                for (int i = 1; i < argc; i++) {
                    argumentList.push(std::move(std::make_unique<std::string>(args[i])));
                }

                std::unique_ptr<std::string> commandType = std::move(argumentList.front());
                argumentList.pop();

                auto commandTemplate = CommandMap.find(*commandType);
                if (commandTemplate == CommandMap.end()) return nullptr;

                std::unique_ptr<CommandData> dataPtr = std::make_unique<CommandData>();
                dataPtr->Type = commandTemplate->second;

                for (int i = 0, totalArguments = argumentList.size(); i < totalArguments; i++) {
                    dataPtr->Arguments.push(std::move(argumentList.front()));
                    argumentList.pop();
                }

                return dataPtr;
            }

            std::shared_ptr<ICommand> CommandFactory::getCommand(std::unique_ptr<CommandData> data) {
                std::shared_ptr<ICommand> command;

                switch (data->Type) {
                case CommandType::Status:
                    command.reset(new StatusCommand());

                    break;
                case CommandType::Fetch:
                    break;
                case CommandType::Pull:
                    break;
                case CommandType::Add:
                    break;
                case CommandType::Commit:
                    break;
                default:
                    command = nullptr;

                    break;
                }

                return command;
            }
        }
    }
}