#!/bin/zsh
set -x

csdiff=$(realpath ../../csdiff_build/csdiff)
test -x "$csdiff" || exit $?

for old in *-old.err; do
    test=${old%-old.err}
    new=${test}-new.err
    for args in "" "-z"; do
        $csdiff $args $old $new | csgrep > ${test}-add${args}.err
        $csdiff $args $new $old | csgrep > ${test}-fix${args}.err
    done
done
