//
// Created by david on 07.04.20.
//
#include <cstdlib>
#include <iostream>
#include <vector>

#include "Command.h"
#include "readWrite.h"

// Values = 2^n, n is the nth bit
const size_t CONCEAL_VAL = 1,
             DESCRIPTION_VAL = 2,
             REMOVE_LAST_VAL = 4;

using CommandList = std::vector<Command>;
enum class Mode {ADD=1, REMOVE, PRINT, FIND, EXPORT};
std::string const DATAFILE = "/opt/memo-bash/memo.json";

/**
 * Adds a command in the datafile
 * @param[string] cmd
 * @param[string] desc
 * @param[bool] conceal : If the command has to be concealed
 */
void addCMD(std::string &cmd, std::string &desc, bool conceal);

/**
 * Removes a command in the datafile
 * @param[size_t] val : The index of the command in the datafile
 * @param[bool] remLast : If the index should be the last command of the datafile
 */
void removeCMD(std::string const &val, bool remLast);

/**
 * Prints all commands in the datafile
 */
void printCMD();

/**
 * Look for a key word/phrase in the datafile and prints all corresponding results
 * @param[string] key
 */
void findCMD(std::string const &key);

/**
 * Export the datafile to the given filepath
 * @param[bool] conceal : if all the commands have to be concealed in the exported file
 * @param[string] filepath
 */
void exportJSON(bool const conceal, std::string const &filepath);

int main(int argc, char* argv[])
{
    // Translating arguments
    size_t mode = std::stoi(argv[1]);
    std::string modeVal = argv[2];
    size_t options = std::stoi(argv[3]);
    std::string optionVal = argv[4];

    bool conceal = (options%DESCRIPTION_VAL);
    bool remove_last = (options/REMOVE_LAST_VAL);

    // Testing values
    /*
    size_t mode = 3;
    std::string modeVal = "Te";
    size_t options = 0;
    std::string optionVal;
    std::string description;
    bool conceal = (options%DESCRIPTION_VAL);
    bool remove_last = (options/REMOVE_LAST_VAL);*/

    // Redirecting to the associated function
    switch (Mode(mode))
    {
        case Mode::ADD:
            addCMD(modeVal, optionVal, conceal); break;
        case Mode::REMOVE:
            removeCMD(modeVal, remove_last); break;
        case Mode::PRINT:
            printCMD(); break;
        case Mode::FIND:
            findCMD(modeVal); break;
        case Mode::EXPORT:
            exportJSON(conceal, modeVal); break;
        default:
            std::cout << "Undefined mode" << std::endl ; break;
    }


    return EXIT_SUCCESS;
}

void addCMD(std::string &cmd, std::string &desc, bool conceal){

    Command c(cmd, desc);
    if (conceal)
        c.hidePrivateData();


    if(writeCommand(c, DATAFILE))
        std::cout << "Added " << c << " to the database" << std::endl;
}


void removeCMD(std::string const &val, bool remLast){

    size_t id = -1;
    if(remLast)
        id = getLastID(DATAFILE);
    else
    {
        try {
            id = std::stoi(val) - 1;
        }
        catch( std::exception& e)
        {
            std::cout << "Error: given ID can't be converted in integer" << std::endl;
            return;
        }
    }

    removeCommand(id, DATAFILE);

}


void printCMD(){

    CommandList list = readData(DATAFILE);

    if(! list.empty()) {
        std::cout << "\033[4m" << "ID\tCommand (description)\033[0m" << std::endl ;
        for (unsigned i = 0; i < list.size(); ++i)
            std::cout << i + 1 << '\t' << list.at(i) << std::endl;
    }

}


void findCMD(std::string const &key){


    CommandList list = readData(DATAFILE);
    CommandList matchingList;

    for ( auto const &cmd : list )
    {
        if(cmd.contains(key))
            matchingList.emplace_back(cmd);
    }

    if ( matchingList.empty() )
        std::cout << "No matching result." << std::endl << std::endl;
    else
    {
        std::cout << "Found " << matchingList.size() << " matching commands:" << std::endl;
        for (auto item : matchingList)
            std::cout << item << std::endl;
    }

}

void exportJSON(bool const conceal, std::string const &filepath){
    CommandList cList = readData(DATAFILE);
    if(conceal)
    {
        for( Command& item : cList)
            item.hidePrivateData();
    }

    exportData(cList, filepath);
}