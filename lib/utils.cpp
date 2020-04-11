//
// Created by david on 10.04.20.
//
#include "utils.h"

bool sameCaseInsChar(char const lhs, char const rhs) {
    return toupper(lhs) == toupper(rhs);
}

std::string removeLeadingSpaces(std::string str) {
    unsigned pos = 0;

    if(str.empty())
        return str;

    while ( (str.at(pos) == ' ' || str.at(pos) == '\t') && pos < str.size() )
        ++pos;

    return str.substr(pos, str.size());
}
