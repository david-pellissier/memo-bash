
# MemoBash
MemoBash is a simple Shell tool that can register commands to use them later. It can memorize last-used command or specific ones.

### Table of contents:
 - [Getting started](https://github.com/david-pellissier/memo-bash#getting-started)
     - [Prerequisites](https://github.com/david-pellissier/memo-bash#prerequisites)
     - [Install](https://github.com/david-pellissier/memo-bash#install)
     - [Uninstall](https://github.com/david-pellissier/memo-bash#uninstall)
-  [Usage](https://github.com/david-pellissier/memo-bash#usage)
- [Known issues](https://github.com/david-pellissier/memo-bash#known-issues)
- [About the future of this project](https://github.com/david-pellissier/memo-bash#about-the-future-of-this-project)

## Getting started
### Requirements
Bash v4.0 or higher.
### Install
You can either install the [last stable version](https://github.com/david-pellissier/memo-bash/raw/master/install/v0.1/memo-bashv0.1.tar.gz) (0.1) or build it from the source files.

To install from the last stable version:

First, extract the archive in a new directory:

    tar -xf memo-bashv0.1.tar.gz --one-top-level
   
Then run /install.sh script as root

    sudo memo-bashv0.1/install.sh

If you can't run this script, make sure the file has execute permissions:    `chmod +x install.sh`

If no error has occurred, you can now use MemoBash.

### Uninstall
Just run :

    sudo /opt/memo-bash/uninstall.sh
And all the files should be removed from the computer.

## Usage
Use the `memo` command to run MemoBash.
There are five operation modes:
|Argument|Description  |
|--|--|
| `--print` | Display all registered commands
|`--new`  | Register a new command.  You can either specify a command or tell the program to use the last executed command by giving no value or using `--last`. You can give it a description with the `--description` argument.| 
| `--remove` |Remove a command from the list of registered commands. You can give an ID or use `--last` option. |
| `--find` | Look for a key value in all the registered commands and their descriptions.
| `--export` | Export all registered commands to a new `.JSON` file. If you give no value, the default exported file is `./exported_memo.json`|

If you specify no operation mode, then `--new` is executed.
You can use a shortened version of all arguments.

In the future, the option `--conceal` will be able to be used to hide potential private data in a command. Will work with `--new` and `export` commands. *The function already exists, but the algorithm does nothing at all.*

Examples:
 - `memo -d "This was le last command I used"` 
 - `memo -n "echo Hello, World!" -d "Test"` 
 -  `memo -r -l`
 - `memo -f "Test"`

If you need more information, use `memo --help`.
## Known issues

 - All bash shells may not work with this project: This may be due to the way memo gets the last used command It has been such a mess to do it, but this was the only way I could make it work.
 - `--conceal` has no effect: I haven't started working on the algorithm, so the function is already there but does nothing. 

## About the future of this project
This project was made in 3 days, starting from 09.04.2020. Now that it does everything I wanted it to do (except --conceal), I cannot guarantee I will work anymore on it. 

