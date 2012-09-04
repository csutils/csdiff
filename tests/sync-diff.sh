#!/bin/sh
export CSDIFF="`readlink -f ../csdiff_build/csdiff`"

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
