#!/bin/sh
export CSDIFF="`readlink -f ../../csdiff_build/src/csdiff`"

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

(
    cd filter-file || exit $?
    basename "$PWD"
    for j in [0-9][0-9]*-old.err; do
        set -x
        tst=${j%-old.err}
        "$CSDIFF" -cf   ${tst}-filter.json ${tst}-old.err ${tst}-new.err > ${tst}-add.err
        "$CSDIFF" -czf  ${tst}-filter.json ${tst}-old.err ${tst}-new.err > ${tst}-add-z.err
        "$CSDIFF" -cxf  ${tst}-filter.json ${tst}-old.err ${tst}-new.err > ${tst}-fix.err
        "$CSDIFF" -cxzf ${tst}-filter.json ${tst}-old.err ${tst}-new.err > ${tst}-fix-z.err
        set +x
    done
    echo
)
