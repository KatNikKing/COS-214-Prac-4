#ifndef ROLE
#define ROLE

enum class Role {
    DRIVER,
    FIRST_AIDER,
    NAVIGATOR,
    CARRIER,
    LEADER, 
    RESPONDER
};

std::string roleToString(Role role) {
    switch (role) {
        case Role::DRIVER: return "Driver";
        case Role::CARRIER: return "Carrier";
        case Role::FIRST_AIDER: return "First-Aider";
        case Role::LEADER: return "Leader";
        case Role::NAVIGATOR: return "Navigator";
        case Role::RESPONDER: return "Responder";
    }

    return "";
}

#endif