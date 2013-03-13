#!/bin/sh
export CSDIFF="`readlink -f ../csdiff_build/csdiff`"
export CSSORT="`readlink -f ../csdiff_build/cssort`"

for i in diff*/; do (
    cd $i || exit $?
    basename "$PWD"
    set -x
    "$CSDIFF" -c 00-old.err 00-new.err > 00-add.err
    "$CSDIFF" -cz 00-old.err 00-new.err > 00-add-z.err
    "$CSDIFF" -cx 00-old.err 00-new.err > 00-fix.err
    "$CSDIFF" -cxz 00-old.err 00-new.err > 00-fix-z.err
    set +x
    echo
) done

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
