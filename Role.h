#ifndef ROLE
#define ROLE

#include <string>

enum class Role {
    DRIVER,
    FIRST_AIDER,
    NAVIGATOR,
    CARRIER,
    LEADER, 
    RESPONDER
};

std::string roleToString(Role role);

#endif