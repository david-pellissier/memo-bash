# DEFAULT VALUES
PROGRAM_PATH="cmake-build-debug/MemoBash"

# bash 4.0 is required for this to work
declare -A RESERVED_VALUES=( [--new]=1 [-n]=1 [--remove]=1 [-r]=1 [--find]=1 [-f]=1 [--export]=1 [-e]=1
                            [--last]=1 [-l]=1 [--conceal]=1 [-c]=1 [--description]=1 [-d]=1 [--print]=1 [-p]=1)
declare -A MAINCOMMANDS=( [--new]=1 [-n]=1 [--remove]=1 [-r]=1 [--find]=1 [-f]=1 [--export]=1 [-e]=1 [--print]=1 [-p]=1)
DEFAULT_EXPORTFILE="memo.json"
HELPFILE="help.txt"
mode=0
options=00
optionsVal=""
val=""
args=("$@")
lastArg="$(($# - 1))"
isValue=false


# FUNCTIONS

function print_help()
{
  cat $HELPFILE
  exit 1
}

function getLastUsedCommand()
{
  modeVal="$(fc -ln | tail -2 | head -1)"
  modeVal="${modeVal:2}"
}

function processArg()
{
  getValue "$2"

  case $1 in

    --new | -n)
      setMode 1
      if [ ! "$val" = "" ]
      then
        modeVal="$val"
        isValue=true
      else
        getLastUsedCommand
      fi ;;

    --remove | -r)
      setMode 2
      if [ ! "$val" = "" ]
      then
        modeVal="$val"
        isValue=true
      fi ;;

    --print | -p)
      setMode 3 ;;

    --find | -f)
      setMode 4
      if [ ! "$val" = "" ]
      then
        modeVal="$val"
        isValue=true
      else
        echo Error: No ID has been given
        print_help
      fi ;;

    --export | -e)
      setMode 5
      if [ ! "$val" = "" ]
      then
        modeVal="$val"
        isValue=true
      else
        modeVal="$DEFAULT_EXPORTFILE"
      fi ;;


    --last | -l)
      ((options+=4))
      getLastUsedCommand
      ;;

    --conceal | -c)
      ((options+=1)) ;;

    --description | -d)
      ((options+=2))
      if [ ! "$val" = "" ]
      then
        optionsVal="$val"
        isValue=true
      else
        print_help
      fi ;;

    --help)
      print_help ;;
    *)
      print_help ;;

    esac
}

function getValue()
{
  # Prevents error: bad array subscript
  if [ "$1" = "" ] ; then
    val=""
    return
  fi

  if [[ ! ${RESERVED_VALUES["$1"]} ]]
  then
    val="$1"
  else
    val=""
  fi
}

function setMode()
{
  if [ ! $mode -eq 0 ] && [ ! $mode -eq "$1" ] ; then

    echo Error: You must choose only one main parameter, placed as the first argument
    print_help

  fi

  mode="$1"
}

# If no main argument is given, run the --new mode
if [ $# -eq 0 ] || [[ ! ${MAINCOMMANDS["$1"]} ]]; then
  mode=1
  getLastUsedCommand
fi

# Main loop on all arguments, while skipping values
for i in $(seq 0 ${lastArg}) ; do

  if ! $isValue
  then
    processArg "${args["${i}"]}" "${args["${i}"+1]}"
  else
    isValue=false
  fi

done

# Uncomment for debug
#echo Mode: $mode ; echo ModeVal: $modeVal ; echo Options: $options ; echo OptionsVal: $optionsVal

${PROGRAM_PATH} $mode "$modeVal" $options "$optionsVal"