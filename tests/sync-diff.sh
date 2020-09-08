#!/bin/sh
export CSDIFF="`readlink -f ../csdiff_build/csdiff`"
export CSSORT="`readlink -f ../csdiff_build/cssort`"

for i in diff*/; do (
    cd $i || exit $?
    basename "$PWD"
    for j in [0-9][0-9]*-old.err; do
        set -x
        tst=${j%-old.err}
        "$CSDIFF" -c   ${tst}-old.err ${tst}-new.err > ${tst}-add.err
        "$CSDIFF" -cz  ${tst}-old.err ${tst}-new.err > ${tst}-add-z.err
        "$CSDIFF" -cx  ${tst}-old.err ${tst}-new.err > ${tst}-fix.err
        "$CSDIFF" -cxz ${tst}-old.err ${tst}-new.err > ${tst}-fix-z.err
        set +x
    done
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
