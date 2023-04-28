#!/bin/bash

CC="g++"
SOURCE="main.cpp functions.cpp interface.cpp"
OUTPUT="Analysis"


build_all() {
    echo -e "\033[1;33mCompiling...\033[0m"
    $CC -o $OUTPUT $SOURCE
    echo -e "\033[1;32mDone. \033[0m "
    echo -e "\033[1;32mEnter the prompt \033[0m\033[1;36m./$OUTPUT\033[0m\033[1;32m or \033[0m\033[1;36m./build.sh run\033[0m\033[1;32m to execute the program. \033[0m"
}


run() {
    ./"$OUTPUT"
}


clean() {
    rm -rf $OUTPUT
    echo -e "\033[1;31m$OUTPUT is deleted. \033[0m"
}


build_again() {
    rm -rf $OUTPUT
    $CC -o $OUTPUT $SOURCE
}


if [ "$1" == "all" ]; then
    build_all
elif [ "$1" == "run" ]; then
    run
elif [ "$1" == "clean" ]; then
    clean
elif [ "$1" == "again" ]; then
    build_again
else
    echo "Invalid target. Available targets: all, run, clean, again."
fi
