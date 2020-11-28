#!/bin/bash
set -e
set -x

# FIXME: copy-pasted from ../../CMakeLists.txt
export JSFILTER_CMD="sed -e ':a;N;\$!ba;s|:\\n *\\[|: [|g'"

# yet another conversion needed for scan properties on EPEL-7
JSFILTER_CMD="${JSFILTER_CMD}';s|:\\n *{|: {|g'"

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
