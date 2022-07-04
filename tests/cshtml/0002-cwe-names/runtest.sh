#!/bin/bash
set -e
set -x

# run cshtml
"${CSHTML_BIN}" \
    --cwe-names "${TEST_SRC_DIR}/cwe-names.csv"         \
    "${TEST_SRC_DIR}/scan-results.json"                 \
    > scan-results.html 2>&1

diff -up "${TEST_SRC_DIR}/scan-results.html" "${PWD}/scan-results.html"
