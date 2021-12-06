#!/bin/bash
set -e
set -x

# import ${JSFILTER_CMD}
. ${TEST_SRC_DIR}/../../test-lib.sh

# run cshtml
"${CSLINKER_BIN}" --quiet                                       \
    "${TEST_SRC_DIR}/raw-results"/{pid-690565-2,xxx{2,}}.xml    \
    | eval "${JSFILTER_CMD}"                                    \
    > scan-results.json

diff -up "${TEST_SRC_DIR}/scan-results.json" "${PWD}/scan-results.json"
