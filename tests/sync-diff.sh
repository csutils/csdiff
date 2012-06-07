#!/bin/sh
export CSDIFF="`readlink -f ../../csdiff_build/csdiff`"

for i in diff*/; do (
    cd $i || exit $?
    basename "$PWD"
    set -x
    "$CSDIFF" 00-old.err 00-new.err > 00-add.err
    "$CSDIFF" -z 00-old.err 00-new.err > 00-add-z.err
    "$CSDIFF" -x 00-old.err 00-new.err > 00-fix.err
    "$CSDIFF" -xz 00-old.err 00-new.err > 00-fix-z.err
    set +x
    echo
) done
