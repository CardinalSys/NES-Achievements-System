#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <string>

struct Achievement {
    int gameId;
    int id;
    std::string name;
    std::string description;
    std::string url;
    std::string offset;
    int value;
    int obtained;
};

#endif // ACHIEVEMENT_H
