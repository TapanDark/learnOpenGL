#!/bin/bash

# This script is meant to prepare build directories for each of the sub-programs
# that I am developing to learn openGL. I have no idea what I'm doing. Don't count
# on this to work at all. If stuck, Google is your friend. Happy coding!

# get script path and dir. Seriously dude, go learn bash
SCRIPTPATH=`readlink -f $0`
SCRIPTDIR=`dirname "$SCRIPTPATH"`

 # Hope ya got cmake, cuz I sure as hell won't provide it. TODO: Provide cmake with project
CMAKE_EXE=`which cmake`
if [[ -z "$CMAKE_EXE" ]]; then
    >&2 echo "Cmake is not installed. Aborting"
    exit 1
fi
# ^ Well That was a bash nightmare. :(

# You know, in case I decide to port this to a something like a fridge or toaster some day.
PLATFORM=x86_64

# I mean, why would you ever want to release this?
CONFIG=debug

# Now generate a build output directory for each build configuration specified
echo "Using PLATFORM=<${PLATFORM}>"

#Branch? Will we have more branches? Answer: Probably not.
BRANCH_PATH=`pwd`

CONFIG_DIR=all_builds/build-${CONFIG}-${PLATFORM}

# If the directory already exists prompt the user to see if they want to recreate it. This will blow away their build.
if [ -d "$CONFIG_DIR" ]; then
    read -p "WARNING: Directory <${CONFIG_DIR}> already exists. Do you want to recreate it? (yes|no) " RECREATE
    case "$RECREATE" in
        y|Y|Yes|yes)
        echo "Removing existing config directory..."
        rm -rf ${CONFIG_DIR}
        ;;
        *)
        echo "Skipping configuration..."
        continue
        ;;
    esac
fi

echo "Generating build output for configuration ${config}..."

#Finally build our tree. Whelp.
${CMAKE_EXE} ${BRANCH_PATH} -B${CONFIG_DIR} -DCMAKE_BUILD_TYPE=$CONFIG ${@:1}

echo "Finished!"
