#!/bin/sh
export CSSORT="`readlink -f ../../csdiff_build/src/cssort`"

for dir in cssort*/; do (
    cd $dir || exit $?
    for input in ??-input.err; do
        bare_input=`basename $input -input.err`
        set -x
        "$CSSORT" --key=checker ${input} 2>/dev/null > ${bare_input}-by-checker.err
        "$CSSORT" --key=path    ${input} 2>/dev/null > ${bare_input}-by-path.err
        set +x
    done
    echo
) done
