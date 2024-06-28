#include "commands/CommandFactory.h"

#include <collections/CommandKeyDictionary.h>
#include <commands/StatusCommand.h>

namespace MaikoDev {
    namespace Arc {
        namespace Commands {
            static Collections::CommandKeyMap CommandMap = {
                {"init", Commands::CommandType::Init},
                {"add", Commands::CommandType::Add},
                {"mv", Commands::CommandType::Move},
                {"restore", Commands::CommandType::Restore},
                {"rm", Commands::CommandType::Remove},
                {"bisect", Commands::CommandType::Bisect},
                {"diff", Commands::CommandType::Diff},
                {"grep", Commands::CommandType::Grep},
                {"log", Commands::CommandType::Log},
                {"show", Commands::CommandType::Show},
                {"status", Commands::CommandType::Status},
                {"branch", Commands::CommandType::Branch},
                {"commit", Commands::CommandType::Commit},
                {"merge", Commands::CommandType::Merge},
                {"rebase", Commands::CommandType::Rebase},
                {"reset", Commands::CommandType::Reset},
                {"switch", Commands::CommandType::Switch},
                {"tag", Commands::CommandType::Tag},
                {"fetch", Commands::CommandType::Fetch},
                {"pull", Commands::CommandType::Pull},
                {"push", Commands::CommandType::Push},
            };

            inline const std::unique_ptr<CommandData> const extractCommand(int argc, char** args) {
                std::queue<std::unique_ptr<std::string>> argumentList;

                for (int i = 1; i < argc; i++) {
                    argumentList.push(std::move(std::make_unique<std::string>(args[i])));
                }

                std::unique_ptr<std::string> commandName = std::move(argumentList.front());
                argumentList.pop();

                auto commandType = CommandMap.get(*commandName);
                if (commandType == CommandMap.end()) return nullptr;

                std::unique_ptr<CommandData> dataPtr = std::make_unique<CommandData>();
                dataPtr->Type = commandType;

                for (int i = 0, totalArguments = argumentList.size(); i < totalArguments; i++) {
                    dataPtr->Arguments.push(std::move(argumentList.front()));
                    argumentList.pop();
                }

                return dataPtr;
            }

            std::shared_ptr<ICommand> CommandFactory::getCommand(std::unique_ptr<CommandData> data) {
                std::shared_ptr<ICommand> command;

                switch (data->Type) {
                case CommandType::Init:
                    //command.reset(new InitCommand());
                    break;
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