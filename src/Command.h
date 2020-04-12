//
// Created by david on 07.04.20.
//

#ifndef MEMOBASH_COMMAND_H
#define MEMOBASH_COMMAND_H

#include <string>
#include <ctime>

#include "lib/utils.h"

class Command {

    time_t datetime;
    std::string cmd, description;
    bool concealed;

public:

    /**
     * Check if either the command or its description contains the given key
     * @param[string] key
     * @return true if the given key is contained in the Command
     * @details The comparison is case insensitive, and does not count leading spaces
     */
    bool contains(std::string key) const;

    /**
     * Remove all sensitive information in the command and replace it by <xyz>
     * @return *this
     * @details Private data are : Filenames and paths, IP adresses
     */
    Command hidePrivateData();

    /**
     *
     * @param[time_t] _dt : time of saving command
     * @param[string] _cmd : command
     * @param[string] _desc : description of the command
     * @param[bool] _conc : true if the command is concealed
     */
    Command(time_t _dt, std::string _cmd, std::string _desc, bool _conc);

    /**
     *
     * @param[string] _cmd : command
     * @param[string] _desc : description of the command
     */
    Command(std::string _cmd, std::string  _desc);

    /**
     * Displays the command
     * @param lhs
     * @param rhs
     * @return
     */
    friend std::ostream &operator<< (std::ostream &lhs, Command& rhs);

    /**
     * Compares if the command is the same as the other
     * @param other
     * @return
     */
    bool operator==(Command other) const;

    time_t getDatetime() const;

    const std::string &getCmd() const;

    const std::string &getDescription() const;

    bool isConcealed() const;

private:

};

#endif //MEMOBASH_COMMAND_H
