#include "commands/CommandFactory.h"

#include <collections/CommandKeyDictionary.h>

#include <commands/AddCommand.h>
#include <commands/InitCommand.h>
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
                {"--help", Commands::CommandType::Help},
            };

            CommandFactory::CommandFactory(const fs::path& projectPath, const fs::path& arcPath) : _projectPath(projectPath), _arcPath(arcPath) {}

            inline const std::unique_ptr<CommandData> const extractCommand(int argc, char** args) throw(Exceptions::NonValidCommandException) {
                std::queue<std::unique_ptr<std::string>> argumentList;

                for (int i = 1; i < argc; i++) {
                    argumentList.push(std::move(std::make_unique<std::string>(args[i])));
                }

                std::unique_ptr<std::string> commandName = nullptr;

                if (argumentList.size() > 0) {
                    commandName = std::move(argumentList.front());
                    argumentList.pop();
                }
                else {
                    commandName = std::make_unique<std::string>("--help");
                }

                auto commandType = CommandMap.get(*commandName);
                if (commandType == CommandMap.end()) 
                    throw Exceptions::NonValidCommandException(std::move(commandName));

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
                std::vector<fs::path> debug;

                switch (data->Type) {
                case CommandType::Init:
                    command.reset(new InitCommand(_arcPath));
                    break;
                case CommandType::Add:
                    command.reset(new AddCommand(debug));
                    break;
                case CommandType::Move:
                    break;
                case CommandType::Restore:
                    break;
                case CommandType::Remove:
                    break;
                case CommandType::Bisect:
                    break;
                case CommandType::Diff:
                    break;
                case CommandType::Grep:
                    break;
                case CommandType::Log:
                    break;
                case CommandType::Show:
                    break;
                case CommandType::Status:
                    command.reset(new StatusCommand(_projectPath));
                    break;
                case CommandType::Branch:
                    break;
                case CommandType::Commit:
                    break;
                case CommandType::Merge:
                    break;
                case CommandType::Rebase:
                    break;
                case CommandType::Reset:
                    break;
                case CommandType::Switch:
                    break;
                case CommandType::Tag:
                    break;
                case CommandType::Fetch:
                    break;
                case CommandType::Pull:
                    break;
                case CommandType::Push:
                    break;
                case CommandType::Help:
                    break;
                }

                return command;
            }

            const fs::path& CommandFactory::getArcPath() const& { return _arcPath; }
        }
    }
}