#!/bin/zsh
set -x

for tst in $@; do
    tst=${tst#csgrep-}
    eval "../../csdiff_build/csgrep $(<${tst}-args.txt) ${tst}-stdin.txt > ${tst}-stdout.txt"
done
