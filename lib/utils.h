//
// Created by david on 10.04.20.
//

#ifndef MEMOBASH_UTILS_H
#define MEMOBASH_UTILS_H

#include <string>

/**
 * Case-insensitive comparison of two chars
 * @param[char] lhs
 * @param[char] rhs
 * @return true if the uppercase chars are the same
 */
bool sameCaseInsChar(char const lhs, char const rhs);

/**
 * Remove spaces and tabulations in the front of given string
 * @param[string] str
 * @return Trimmed string
 */
std::string removeLeadingSpaces(std::string str);

#endif //MEMOBASH_UTILS_H
