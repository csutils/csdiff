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

for tst in "${tests[@]}"; do
    tst=${tst%-stdin.txt}
    ${PROJECT_ROOT}/csdiff_build/src/cstrans-df-run \
        ${TEST_ARGS[@]} \
        < ${tst}-stdin.txt \
        > ${tst}-stdout.txt
done
