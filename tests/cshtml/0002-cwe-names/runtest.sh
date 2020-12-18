#!/bin/bash
set -e
set -x

# run cshtml
"${CSHTML_BIN}" \
    --cwe-names "${TEST_SRC_DIR}/cwe-names.csv"         \
    "${TEST_SRC_DIR}/scan-results.js"                   \
    > scan-results.html

diff -up "${TEST_SRC_DIR}/scan-results.html" "${PWD}/scan-results.html"
