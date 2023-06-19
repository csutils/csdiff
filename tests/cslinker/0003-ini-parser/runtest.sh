#!/bin/bash
set -e
set -x

# run cslinker
"${CSLINKER_BIN}" --inifile "${TEST_SRC_DIR}/scan.ini" <() > scan-results.json

# compare the results with the expected results
diff -up "${TEST_SRC_DIR}/scan-results.json" "${PWD}/scan-results.json"
