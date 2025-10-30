#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

class Commands {
public:
    void execute(const std::string& query, const std::string& filename);
};

#endif