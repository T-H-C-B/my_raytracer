#!/bin/bash

BUILD_DIR=".build"
PLUGIN_DIR="plugins"

function make_project() {
    # shellcheck disable=SC2164
    cd ${BUILD_DIR}
    make -j8
    # shellcheck disable=SC2103
    cd ..
}

function clean_project() {
    # shellcheck disable=SC2164
    cd ${BUILD_DIR}
    make clean
    # shellcheck disable=SC2103
    cd ..
}

function fclean_project() {
    rm -rf ${BUILD_DIR}
    rm -rf ${PLUGIN_DIR}
    rm -rf raytracer
    rm -rf libraytracer_lib.a
}

function re_project() {
    fclean_project
    mkdir -p ${BUILD_DIR}
    # shellcheck disable=SC2164
    cd ${BUILD_DIR}
    if [ "$1" == "debug" ]; then
        cmake -DCMAKE_BUILD_TYPE=Debug ..
    else
        cmake ..
    fi
    make -j8
    # shellcheck disable=SC2103
    cd ..
}

function re_and_run() {
    re_project "$1"
    ./raytracer
}

if [ "$1" == "make" ]; then
    make_project
elif [ "$1" == "re" ]; then
    re_project "$2"
elif [ "$1" == "fclean" ]; then
    fclean_project
elif [ "$1" == "clean" ]; then
    clean_project
elif [ "$1" == "rerun" ]; then
    re_and_run "$2"
else
    echo "Usage: $0 [make | re | fclean | clean | rerun] [debug]"
fi
