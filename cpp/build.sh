#!/bin/bash

script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
build_dir="${script_dir}/build"

export CC=clang
export CXX=clang++

mkdir -p ${build_dir}
cd ${build_dir}
cmake -G Ninja ..

cd ${script_dir}
cmake --build ${build_dir}

