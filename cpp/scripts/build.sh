#!/usr/bin/env bash
set -Eeuo pipefail
IFS=$'\n\t'

# magic line to ensure that we're always inside the root of our repo,
# no matter from which directory we'll run script
cd "${0%/*}/.."

mkdir -p build/ && cd build/
conan install .. --build=missing
cmake $@ ..
cmake --build .
cd ../
