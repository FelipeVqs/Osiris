#pragma once

#include <string_view>
#include <stdexcept>

#include <Features/Features.h>
#include <Helpers/UnloadFlag.h>
#include <Utils/StringParser.h>

void handlePanoramaCommand(const std::string_view& command, StringParser& parser, Features& features, UnloadFlag& unloadFlag);

struct PanoramaCommandDispatcher {
    PanoramaCommandDispatcher(const char* commandline, Features features, UnloadFlag& unloadFlag) noexcept
        : parser{commandline}
        , features{features}
        , unloadFlag{unloadFlag}
    {
    }

    void execute() noexcept {
        std::string_view command{ parseNextCommand() };
        while (!command.empty()) {
            try {
                handlePanoramaCommand(command, parser, features, unloadFlag);
            } catch (const std::runtime_error& e) {
                // Log or print the error message
                // Example: std::cerr << "Error: " << e.what() << '\n';
            }
            command = parseNextCommand();
        }
    }

private:
    [[nodiscard]] std::string_view parseNextCommand() noexcept {
        return parser.getLine(' ');
    }

    StringParser parser;
    Features features;
    UnloadFlag& unloadFlag;
};

void handlePanoramaCommand(const std::string_view& command, StringParser& parser, Features& features, UnloadFlag& unloadFlag) {
    if (command == "unload") {
        unloadFlag.set();
    } else if (command == "set") {
        SetCommandHandler{parser, features}();
    } else {
        throw std::runtime_error("Invalid command: " + std::string(command));
    }
}
