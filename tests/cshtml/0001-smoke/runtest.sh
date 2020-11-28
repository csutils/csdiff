#!/bin/bash
set -e
set -x

# run cshtml
"${CSHTML_BIN}" \
    --diff-base "${TEST_SRC_DIR}/old/scan-results.js"   \
    --diff-base-ignore-checkers "SHELLCHECK_WARNING"    \
    --plain-text-url "scan-results.err"                 \
    "${TEST_SRC_DIR}/scan-results.js"                   \
    > scan-results.html

diff -up "${TEST_SRC_DIR}/scan-results.html" "${PWD}/scan-results.html"
