#!/bin/bash
set -e
set -x

# import ${JSFILTER_CMD}
. ${TEST_SRC_DIR}/../test-lib-cslinker.sh

# run cshtml
"${CSLINKER_BIN}" --quiet                                       \
    "${TEST_SRC_DIR}/raw-results"/{pid-690565-2,xxx{2,}}.xml    \
    | eval "${JSFILTER_CMD}"                                    \
    > scan-results.js

diff -up "${TEST_SRC_DIR}/scan-results.js" "${PWD}/scan-results.js"
