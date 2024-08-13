#!/bin/zsh
set -exo pipefail

# set path to project root
PROJECT_ROOT="../.."

# prefer the locally built csdiff binaries over the system-provided ones
export PATH="$PROJECT_ROOT/csdiff_build/src:$PATH"

# import ${JSFILTER_CMD}
. ../test-lib.sh

if [[ $# -eq 0 ]]; then
    tests=( *-args.txt )
else
    tests=( "$@" )
fi

for tst in "${tests[@]}"; do
    tst=${tst%-args.txt}
    cmd="$PROJECT_ROOT/src/csfilter-kfp $(<${tst}-args.txt)"
    test -e "${tst}-stdin.txt" && cmd="${cmd} ${tst}-stdin.txt"
    eval "$cmd" | eval "${JSFILTER_CMD}" > ${tst}-stdout.txt
done
