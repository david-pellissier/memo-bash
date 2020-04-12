//
// Created by david on 07.04.20.
//

#include "readWrite.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <algorithm>

const char* CMD_KEY = "commands";

std::vector<Command> readData(std::string const& file){
    std::ifstream open(file);
    std::vector<Command> v ;

    if(! open.is_open())
    {
        std::cout << "Error: Could not open the data file" << std::endl;
        return v;
    }

    json j = json::parse(open);

    if(j[CMD_KEY].empty())
        std::cout << "The datafile contains no saved command" << std::endl;
    else
    {
        for (json jItem : j[CMD_KEY]) {

            time_t timedate = jItem["datetime"].get<long>();
            std::string value = jItem["value"];
            std::string description = jItem["description"].get<std::string>();
            bool isConcealed = jItem["isConcealed"].get<bool>();

            Command c{
                    timedate,
                    value,
                    description,
                    isConcealed
            };

            v.emplace_back(c);

        }
    }

    return v;
}


bool writeCommand(Command const& cmd, std::string const &file){

    std::ifstream open(file);

    if( ! open.is_open())
    {
        std::cout << "Error: Could not open the data file" << std::endl;
        return false;
    }

    json j = json::parse(open);

    json j_cmd = std::move(cmdToJSON(cmd));

    if (existsInJSON(j[CMD_KEY], j_cmd))
    {
        std::cout << "Error: The given command already exists in the database" << std::endl;
        return false;
    }

    j[CMD_KEY].emplace_back(j_cmd);



    return writeData(j , file);
}


bool writeData(json const &jdata, std::string const& file){
    std::ofstream write(file);

    if( ! write.is_open()){
        std::cout << "Error: Could not write in the file" << std::endl;
        return false;
    }


    write << std::setw(4) << jdata << std::endl;

    return true;
}

bool removeCommand(unsigned const id, std::string const &file){
    std::ifstream open(file);

    if( ! open.is_open())
    {
        std::cout << "Error: Could not open the data file" << std::endl;
        return false;
    }

    json j = json::parse(open);

    if( id >= j[CMD_KEY].size())
    {
        std::cout << "Error: The given ID does not exist" << std::endl;
        return false;
    }

    std::string remValue = j[CMD_KEY][id]["value"];
    j[CMD_KEY].erase(id);

    if( writeData(j, file) )
        std::cout << "Removed command: " << remValue << std::endl;

    return true;
}



bool exportData(std::vector<Command> const &cmdList, std::string const& filename)
{
    json j;
    j[CMD_KEY] = {};

    for( const Command &cmd : cmdList)
    {
        j[CMD_KEY].emplace_back(cmdToJSON(cmd));
    }

    if( ! writeData(j, filename))
    {
        std::cout << "Error: There was a problem while exporting the file..." << std::endl;
        return false;
    }

    std::cout << "Data exported to: " << filename << std::endl;
    return true;
}

unsigned getLastID(std::string const &file){
    std::ifstream open(file);
    json j = json::parse(open);

    return j[CMD_KEY].size() - 1;
}

bool existsInJSON(json const &jList, json const &jItem){
    std::string sToFind = jItem["value"];
    std::string sNull;
    Command cToFind(sToFind, sNull);

    for ( json current : jList)
    {
        std::string sCurrent = current["value"];
        if(cToFind == Command(sCurrent, sNull))
            return true;
    }

    return false;
}

json cmdToJSON(Command const &cmd){
    return json {
            { "datetime" , cmd.getDatetime() } ,
            { "value" , cmd.getCmd()},
            { "description" , cmd.getDescription()},
            { "isConcealed" , cmd.isConcealed()}
    };
}