#!/bin/zsh
set -x

if [[ $# -eq 0 ]]; then
    tests=( *-args.txt )
else
    tests=( "$@" )
fi

for tst in "${tests[@]}"; do
    tst=${tst%-args.txt}
    eval "../../csdiff_build/src/csgrep $(<${tst}-args.txt) ${tst}-stdin.txt" > ${tst}-stdout.txt
done
