#!/bin/bash

#WORKINGDIR="install/v0.1/"
WORKINGDIR="$PWD"/
DIR_SUFFIX="memo-bash"
OPT_DIR="/opt/"$DIR_SUFFIX
COMMANDNAME="memo"
INSTALL_LINK="/usr/bin/"$COMMANDNAME

HELP_FILE=$WORKINGDIR"help.txt"
INIT_SCRIPT=$WORKINGDIR"init.sh"
EMPTY_JSON=$WORKINGDIR"memo.json"
APP_BIN=$WORKINGDIR"MemoBash"
UNINS_SCRIPT=$WORKINGDIR"uninstall.sh"
ERROR=false

function missingFile()
{
  echo - Missing installation file: "$1"
  ERROR=true
}

function copyFile() # $1=source file, $2=destination
{
  cp $1 $2
  if [ -f $2 ] ; then
    echo Copied "$1" to "$2"
  else
    echo
    echo Error: Could not copy "$1"
    exit 1
  fi


}

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run with root privileges"
   exit 1
fi

# Check if all files exist
echo Checking prerequisites...
if [ ! -f "$HELP_FILE" ] ; then missingFile "$HELP_FILE" ; fi
if [ ! -f "$INIT_SCRIPT" ] ; then missingFile "$INIT_SCRIPT"; fi
if [ ! -f "$EMPTY_JSON" ] ; then missingFile "$EMPTY_JSON" ; fi
if [ ! -f "$APP_BIN" ]; then missingFile "$APP_BIN" ; fi
if [ ! -f "$UNINS_SCRIPT" ]; then missingFile "$UNINS_SCRIPT" ; fi

# If no error, proceed installation
if $ERROR ; then exit 1 ; fi

echo Everything looks fine, now proceeding to install ...

# Prepare structure
mkdir $OPT_DIR
if [ ! -d "$OPT_DIR" ] ; then echo Could not create "$OPT_DIR" ; exit 1; fi
echo Created $OPT_DIR

# Copy files

copyFile $HELP_FILE $OPT_DIR/help.txt
copyFile $INIT_SCRIPT $OPT_DIR/init.sh
copyFile $EMPTY_JSON $OPT_DIR/memo.json
copyFile $APP_BIN $OPT_DIR/MemoBash
copyFile $UNINS_SCRIPT $OPT_DIR/uninstall.sh
echo ... Copied files

ln -s  $OPT_DIR/init.sh $INSTALL_LINK
if [ ! -f $INSTALL_LINK ] ; then echo Could not create $INSTALL_LINK ; exit 1; fi
echo Created symbolic link

echo ...
echo DONE !

