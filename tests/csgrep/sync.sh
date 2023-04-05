#!/bin/zsh
set -exo pipefail

# set path to project root
PROJECT_ROOT="../.."

# import ${JSFILTER_CMD}
. ../test-lib.sh

if [[ $# -eq 0 ]]; then
    tests=( *-args.txt )
else
    tests=( "$@" )
fi

for tst in "${tests[@]}"; do
    tst=${tst%-args.txt}
    eval "$PROJECT_ROOT/csdiff_build/src/csgrep $(<${tst}-args.txt) ${tst}-stdin.txt" \
        | eval "${JSFILTER_CMD}" \
        > ${tst}-stdout.txt
done
