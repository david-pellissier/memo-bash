//
// Created by david on 07.04.20.
//

#include "Command.h"

#include <utility>
#include <algorithm>


//// CLASS FUNCTIONS ////
/// Public
Command Command::hidePrivateData()
{
    if(! concealed)
    {

        // TODO this function
        // Remove filepaths

        // Remove IPs

        this->concealed = true;
    }

    return *this;
}

bool Command::contains(std::string key) const {
    key = std::move(removeLeadingSpaces(key));

    auto posCmd = std::search(this->cmd.begin(), this->cmd.end(), key.begin(), key.end(), sameCaseInsChar);
    auto posDesc = std::search(this->description.begin(), this->description.end(), key.begin(), key.end(), sameCaseInsChar);

    if (posCmd != this->cmd.end())
        return true;

    return (posDesc != this->description.end());
}

/// Private


//// CONSTRUCTORS AND OPERATORS ////

Command::Command(time_t _dt, std::string &_cmd, std::string &_desc, bool _conc) : datetime(_dt), concealed(_conc) {
    description = std::move(removeLeadingSpaces(_desc));
    cmd = std::move(removeLeadingSpaces(_cmd));
}

Command::Command(std::string &_cmd, std::string &_desc) : cmd(std::move(_cmd)), description(std::move(_desc)) {
    this->datetime = time(nullptr);
    this->concealed = false;
}

std::ostream &operator<<(std::ostream &lhs, Command &rhs) {
    std::string summary = rhs.getCmd();
    if (! rhs.getDescription().empty())
    {
        summary += "\t (";
        summary += rhs.getDescription();
        summary += ')';
    }

    return lhs << summary;
}

bool Command::operator==(Command other) const {
    Command thisConcealed = *this;

    if (! thisConcealed.isConcealed() )
        thisConcealed.hidePrivateData();
    if (! other.isConcealed() )
        other.hidePrivateData();

    return thisConcealed.cmd == other.cmd;
}

//// GETTERS AND SETTERS (if needed) ////

time_t Command::getDatetime() const {
    return datetime;
}

const std::string &Command::getCmd() const {
    return cmd;
}

const std::string &Command::getDescription() const {
    return description;
}

bool Command::isConcealed() const {
    return concealed;
}






