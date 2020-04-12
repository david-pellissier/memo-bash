#!/bin/bash

DIR_SUFFIX="memo-bash"
OPT_DIR="/opt/$DIR_SUFFIX/"
COMMANDNAME="memo"
INSTALL_LINK="/usr/bin/$COMMANDNAME"
HELP_FILE=$OPT_DIR"help.txt"
INIT_SCRIPT=$OPT_DIR"init.sh"
EMPTY_JSON=$OPT_DIR"memo.json"
APP_BIN=$OPT_DIR"MemoBash"

function removeFile()
{
  rm $1
  if [ ! -f $1 ] ; then
    echo Removed "$1"
  else
    echo Could not remove $1
    exit 1
  fi
}

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run with root privileges"
   exit 1
fi

removeFile $INSTALL_LINK
removeFile $HELP_FILE
removeFile $INIT_SCRIPT
removeFile $EMPTY_JSON
removeFile $APP_BIN
rm -rf "$OPT_DIR"

echo ...
echo Done !