#!/bin/bash

script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

if ! docker volume ls -q | grep -q mikado-workspace ; then
  docker volume create mikado-workspace
fi

WORKSPACE="--mount source=mikado-workspace,target=/workspace"
SOURCE="--mount type=bind,source=${script_dir},target=/source,readonly"
VOLUMES="${WORKSPACE} ${SOURCE}"

docker run --rm -t ${VOLUMES} \
  -w /workspace \
  raphaelmeyer/cmake3.10-clang6.0-runner:1.1.0 \
  cmake -G Ninja /source

docker run --rm -t ${VOLUMES} \
  -w /workspace \
  raphaelmeyer/cmake3.10-clang6.0-runner:1.1.0 \
  cmake --build /workspace

