#!/bin/bash
set -e
set -x

# import ${JSFILTER_CMD}
. ${TEST_SRC_DIR}/../test-lib-cslinker.sh

# run cshtml
"${CSLINKER_BIN}" \
    --cwelist "${TEST_SRC_DIR}/cwe-map.csv"             \
    --implist "${TEST_SRC_DIR}/scan-results-imp.js"     \
    --inifile "${TEST_SRC_DIR}/scan.ini"                \
    --reapply-parsing-rules                             \
    --quiet                                             \
    "${TEST_SRC_DIR}/uni-results"/*                     \
    | eval "${JSFILTER_CMD}"                            \
    > scan-results.js

diff -up "${TEST_SRC_DIR}/scan-results.js" "${PWD}/scan-results.js"
