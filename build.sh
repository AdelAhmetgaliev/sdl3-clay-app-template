#!/usr/bin/env bash

TARGET_NAME="gui-app"

COMPILER="clang"
LINKER="lld"

# General target compiler flags
GCFLAGS="-std=c23 -Iinclude/ -Isrc/ \
    -D_REENTRANT -I/usr/include/libdecor-0"
# General target linker flags
GLFLAGS="-fuse-ld=${LINKER} -Llib/ -lSDL3 -lSDL3_image -lSDL3_ttf -Wl,-Rlib/"

# Release target compiler flags
RCFLAGS="-O2 -fstack-clash-protection -fstack-protector-all -fcf-protection=full \
    -fpie -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=2"
# Debug target compiler flags
DCFLAGS="-g3 -Wall -Wextra -Wshadow -Wdouble-promotion -Wformat=2 -Wundef \
    -Werror -Werror=format-security -Werror=implicit-function-declaration"

# Release target linker flags
RLFLAGS="-flto -s -pie -Wl,-z,nodlopen -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now -Wl,-z,defs"
# Debug target linker flags
DLFLAGS=""

CFLAGS="${GCFLAGS} ${DCFLAGS}"
LFLAGS="${GLFLAGS} ${DLFLAGS}"

TARGET_FOLDER="debug"

build_mode=true
run_mode=false
args_mode=false

declare -a args

COLOR_RED='\033[0;31m'
COLOR_GREEN='\033[0;32m'
COLOR_NO='\033[0m'

for arg in $@
do
    if $args_mode; then
        args+=($arg)
        continue
    fi

    if [ $arg = '--release' ]; then
        CFLAGS="${GCFLAGS} ${RCFLAGS}"
        LFLAGS="${GLFLAGS} ${RLFLAGS}"
        TARGET_FOLDER="release"
    fi

    if [ $arg = 'run' ]; then
        run_mode=true
    fi

    if [ $arg = 'run!' ]; then
        run_mode=true
        build_mode=false
    fi

    if [ $arg = '--' ]; then
        args_mode=true
    fi
done

if [ ! -d build ]; then
    mkdir build
fi

if [ ! -d build/$TARGET_FOLDER ]; then
    mkdir build/$TARGET_FOLDER
fi

if [ ! -d build/$TARGET_FOLDER/obj ]; then
    mkdir build/$TARGET_FOLDER/obj
fi

if [ ! -d build/$TARGET_FOLDER/bin ]; then
    mkdir build/$TARGET_FOLDER/bin
fi

if $build_mode; then
    if [ ! -f app.c ]; then
        echo -e "${COLOR_RED}The app.c file does not exist!${COLOR_NO}"
    else
        (set -x; $COMPILER -c app.c -o build/$TARGET_FOLDER/obj/app.o $CFLAGS)
        (
            set -x; $COMPILER -o build/$TARGET_FOLDER/bin/$TARGET_NAME $LFLAGS \
                build/$TARGET_FOLDER/obj/app.o
        )
    fi
fi

if $run_mode; then
    if [ ! -f build/$TARGET_FOLDER/bin/$TARGET_NAME ]; then
        echo -e "${COLOR_RED}Compile first!${COLOR_NO}"
    else
        (set -x; build/$TARGET_FOLDER/bin/$TARGET_NAME ${args[*]})
    fi
fi
