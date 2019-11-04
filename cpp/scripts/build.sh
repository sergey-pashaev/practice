#!/usr/bin/env bash
set -Eeuo pipefail
IFS=$'\n\t'

# magic line to ensure that we're always inside the root of our repo,
# no matter from which directory we'll run script
cd "${0%/*}/.."

mkdir -p build/ && cd build/
export CC=clang
export CXX=clang++
conan install .. --build=missing --profile=../conan/clang9
cmake $@ ..
cmake --build .
cd ../
