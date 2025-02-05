#!/bin/zsh
set -exo pipefail

TEST_ARGS=(-- /opt/cov-sa-2019.09/bin/cov-build --dir=/cov --append-log)

# set path to project root
PROJECT_ROOT="../.."

if [[ $# -eq 0 ]]; then
    tests=( *-stdin.txt )
else
    tests=( "$@" )
fi

TEST_BIN=${PROJECT_ROOT}/csdiff_build/src/cstrans-df-run

for tst in "${tests[@]}"; do
    tst=${tst%-stdin.txt}
    ${TEST_BIN} ${TEST_ARGS[@]} \
        < ${tst}-stdin.txt \
        > ${tst}-stdout.txt

    ${TEST_BIN} --shell-form ${TEST_ARGS[@]} \
        < ${tst}-stdin.txt \
        > ${tst}-sf-stdout.txt
done
