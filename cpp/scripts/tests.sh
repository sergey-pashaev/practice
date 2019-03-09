#!/usr/bin/env bash
set -Eeuo pipefail
IFS=$'\n\t'

./scripts/build.sh $@
cd build/
ctest -V .
