# Copyright (C) 2011 - 2021 Red Hat, Inc.
#
# This file is part of csdiff.
#
# csdiff is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# csdiff is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with csdiff.  If not, see <http://www.gnu.org/licenses/>.

# a generic template for a csdiff test-case
macro(test_csdiff dir num)
    set(tst "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/${num}")

    set(cmd "${csdiff} -c ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${diffcmd} ${tst}-add.err -")
    add_test_wrap("${dir}-${num}-added" "${cmd}")

    set(cmd "${csdiff} -x ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${csjson} | ${csgrep}")
    set(cmd "${cmd} | ${diffcmd} ${tst}-fix.err -")
    add_test_wrap("${dir}-${num}-fixed" "${cmd}")

    set(cmd "${csdiff} -z ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${csjson} | ${csgrep}")
    set(cmd "${cmd} | ${diffcmd} ${tst}-add-z.err -")
    add_test_wrap("${dir}-${num}-added-with-z" "${cmd}")

    set(cmd "${csdiff} -xz ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${csjson} | ${csgrep}")
    set(cmd "${cmd} | ${diffcmd} ${tst}-fix-z.err -")
    add_test_wrap("${dir}-${num}-fixed-with-z" "${cmd}")

    set(cmd "${csdiff} -c ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${diffcmd} ${tst}-add.err -")
    add_test_wrap("${dir}-${num}-added-with-c" "${cmd}")

    set(cmd "${csdiff} -jx ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${csgrep}")
    set(cmd "${cmd} | ${diffcmd} ${tst}-fix.err -")
    add_test_wrap("${dir}-${num}-fixed-with-j" "${cmd}")
endmacro()

# csdiff tests
test_csdiff(diff5.9-kernel                          00)
test_csdiff(diff7.0-qt                              00)
test_csdiff(diff7.0-fftw                            00)
test_csdiff(diff7.0-sudo                            00)
test_csdiff(diff7.0-libssh                          00)
test_csdiff(diff7.0-icu                             00)
test_csdiff(diff7.0-virtuoso-opensource             00)
test_csdiff(diff5.8-kernel                          00)
test_csdiff(diff6.4-iok                             00)
test_csdiff(diff6.4-rpm                             00)
test_csdiff(diff6.4-ksh                             00)
test_csdiff(diff6.4-samba4                          00)
test_csdiff(diff6.4-papi                            00)
test_csdiff(diff6.4-kernel                          00)
test_csdiff(diff8.0-ModemManager                    00)
test_csdiff(diff-misc                               00)
test_csdiff(diff-misc                               01)
test_csdiff(diff-misc                               02)
test_csdiff(diff-misc                               03)
test_csdiff(diff-misc                               04)
test_csdiff(diff-misc                               05)
test_csdiff(diff-misc                               06)
test_csdiff(diff-misc                               07)
test_csdiff(diff-misc                               08)
test_csdiff(diff-misc 09-shellcheck-raw)
test_csdiff(diff-misc 10-pylint-copr)
test_csdiff(diff-misc 11-pylint-copr-json)
test_csdiff(diff-misc 12-shellcheck-sc222x)
test_csdiff(diff-misc 13-gcca-filt)
test_csdiff(diff-misc 14-gitleaks-paths)
test_csdiff(diff-misc 15-gcc-prof-filter)
test_csdiff(diff-misc 16-cov-parser-key-event)
test_csdiff(diff-misc 17-cov-parser-key-event)
test_csdiff(diff-misc 18-cov-parser-key-event)
test_csdiff(diff-misc 19-cov-parser-key-event)

add_subdirectory(filter-file)
