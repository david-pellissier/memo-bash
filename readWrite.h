//
// Created by david on 07.04.20.
//

#ifndef MEMOBASH_READWRITE_H
#define MEMOBASH_READWRITE_H


#include "Command.h"
#include <vector>

#include "lib/json.hpp"
using json = nlohmann::json;

/**
 * Reads the JSON file given in parameter
 * @param[string] file
 * @return a vector of commands
 */
std::vector<Command> readData (std::string const& file);

/**
 * Writes a command in the given file
 * @param[Command] cmd : Command to write
 * @param[string] file
 * @return True if the command has been written successfully
 */
bool writeCommand (Command const& cmd, std::string const &file);

/**
 * Replace the content of a file with given JSON data
 * @param[json] jdata : JSON data to write
 * @param[string] file
 * @return True if operation was successful
 */
bool writeData (json const &jdata, std::string const& file);

/**
 * Removes a command from a JSON file
 * @param[unsigned] id : Position of the command in JSON list (starting from 0)
 * @param[string] file
 * @return True if operation was successful
 */
bool removeCommand (unsigned const id, std::string const &file);

/**
 * Exports a vector of commands as a JSON file
 * @param[vector<Command>] cmdList
 * @param[string] filename
 * @return True if operation was successful
 */
bool exportData (std::vector<Command> const &cmdList, std::string const& filename);

/**
 * Retrieves the index of the last item in a JSON file
 * @param[string] file
 * @return index of the last value
 */
unsigned getLastID (std::string const &file);

/**
 * Checks if a JSON command exists in another JSON
 * @param[json] jList : A JSON value containing a list <CMD_KEY>
 * @param[json] jItem : JSON command item
 * @return True if jItem exists in jList
 * @details The function only looks for the value of the item, not regarding of the other parameters
 */
bool existsInJSON (json const &jList, json const &jItem);

/**
 * Converts a Command in JSON
 * @param cmd
 * @return the converted value
 */
json cmdToJSON (Command const &cmd);

#endif //MEMOBASH_READWRITE_H
