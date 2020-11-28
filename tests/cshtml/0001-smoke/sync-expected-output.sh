#!/bin/bash
set -e
set -x

# check whether we are invoked from the correct directory
test -d ../../cshtml/0001-smoke

# find cshtml BINARY
export CSHTML_BIN=../../../csdiff_build/src/cshtml
test -x $CSHTML_BIN
CSHTML_BIN=$(realpath $CSHTML_BIN)

# run the test in the _source_ directory to overwrite the expected output
TEST_SRC_DIR="$PWD" ./runtest.sh
