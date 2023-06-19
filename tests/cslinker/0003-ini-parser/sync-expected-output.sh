#!/bin/bash
set -e
set -x

# check whether we are invoked from the correct directory
test -d ../../cslinker/0003-ini-parser/

# find cslinker BINARY
export CSLINKER_BIN=../../../csdiff_build/src/cslinker
test -x $CSLINKER_BIN
CSLINKER_BIN=$(realpath $CSLINKER_BIN)

# run the test in the _source_ directory to overwrite the expected output
TEST_SRC_DIR="$PWD" ./runtest.sh
