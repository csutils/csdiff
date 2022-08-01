#!/bin/bash

# Copyright (C) 2014 - 2022 Red Hat, Inc.
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

SELF="$0"

PKG="csdiff"

die() {
    echo "$SELF: error: $1" >&2
    exit 1
}

match() {
    grep "$@" > /dev/null
}

DST="`readlink -f "$PWD"`"

REPO="`git rev-parse --show-toplevel`"
test -d "$REPO" || die "not in a git repo"

NV="`git describe --tags`"
echo "$NV" | match "^$PKG-" || die "release tag not found"

VER="`echo "$NV" | sed "s/^$PKG-//"`"

TIMESTAMP="`git log --pretty="%cd" --date=iso -1 \
    | tr -d ':-' | tr ' ' . | cut -d. -f 1,2`"

VER="`echo "$VER" | sed "s/-.*-/.$TIMESTAMP./"`"

BRANCH="`git rev-parse --abbrev-ref HEAD`"
test -n "$BRANCH" || die "failed to get current branch name"
test "main" = "${BRANCH}" || VER="${VER}.${BRANCH//[\/-]/_}"
test -z "`git diff HEAD`" || VER="${VER}.dirty"

NV="${PKG}-${VER}"
printf "\n%s: preparing a release of \033[1;32m%s\033[0m\n\n" "$SELF" "$NV"

if [[ "$1" != "--generate-spec" ]]; then
    TMP="`mktemp -d`"
    trap "rm -rf '$TMP'" EXIT
    cd "$TMP" >/dev/null || die "mktemp failed"

    # clone the repository
    git clone "$REPO" "$PKG"                || die "git clone failed"
    cd "$PKG"                               || die "git clone failed"
    make distcheck                          || die "'make distcheck' has failed"

    SRC_TAR="${NV}.tar"
    SRC="${SRC_TAR}.xz"
    git archive --prefix="$NV/" --format="tar" HEAD -- . > "$SRC_TAR" \
                                            || die "failed to export sources"

    xz -c "$SRC_TAR" > "$SRC"               || die "failed to compress sources"
fi

SPEC="./$PKG.spec"
cat > "$SPEC" << EOF
# disable in source builds on EPEL <9
%undefine __cmake_in_source_build
%undefine __cmake3_in_source_build

# python2 is not available on RHEL > 7 and Fedora
%if 0%{?rhel} > 7 || 0%{?fedora}
%bcond_with python2
%else
%bcond_without python2
%endif

# python3 support is optional
%bcond_without python3

Name:       $PKG
Version:    $VER
Release:    1%{?dist}
Summary:    Non-interactive tools for processing code scan results in plain-text

License:    GPLv3+
URL:        https://github.com/csutils/csdiff
Source0:    https://github.com/csutils/csdiff/releases/download/%{name}-%{version}/%{name}-%{version}.tar.xz

# the following upstream commit is needed to work with up2date csdiff/csgrep
# https://github.com/csutils/csmock/commit/48b09b3a
Conflicts:  csmock-plugin-shellcheck <= 2.5

BuildRequires: boost-devel
BuildRequires: cmake3
BuildRequires: gcc-c++
BuildRequires: help2man
BuildRequires: make

%if 0%{?rhel} && 0%{?rhel} < 9
Provides: bundled(boost_nowide)
%endif

%description
This package contains the csdiff tool for comparing code scan defect lists in
order to find out added or fixed defects, and the csgrep utility for filtering
defect lists using various filtering predicates. 

%if %{with python2}
%package -n python2-%{name}
Summary:        Python interface to csdiff for Python 2
%if 0%{?fedora}
BuildRequires:  boost-python2-devel
%endif
BuildRequires:  python2-devel
%{?python_provide:%python_provide python2-%{name}}

%description -n python2-%{name}
This package contains the Python 2 binding for the csdiff tool for comparing
code scan defect lists to find out added or fixed defects.
%endif

%if %{with python3}
%package -n python3-%{name}
Summary:        Python interface to csdiff for Python 3

# this packages redefines %%{python3_pkgversion} to 36 because there is
# no boost-python3-devel in epel-7 buildroot, only boost-python36-devel
%if 0%{?rhel} == 7
BuildRequires:  epel-rpm-macros
%endif
# in f33 boost-python3-devel was merged into boost-devel
%if 0%{?rhel} && 0%{?rhel} < 9
BuildRequires:  boost-python%{python3_pkgversion}-devel
%endif
BuildRequires:  python3-devel
%{?python_provide:%python_provide python3-%{name}}

%description -n python3-%{name}
This package contains the Python 3 binding for the csdiff tool for comparing
code scan defect lists to find out added or fixed defects.
%endif

%prep
%autosetup

%build
make version.cc
%cmake3                                    \\
    -DPYCSDIFF_PYTHON2=%{?with_python2:ON} \\
    -DPYCSDIFF_PYTHON3=%{?with_python3:ON}
%cmake3_build

%install
%cmake3_install

%check
%ctest3

%files
%doc README
%license COPYING
%{_bindir}/csdiff
%{_bindir}/csgrep
%{_bindir}/cshtml
%{_bindir}/cslinker
%{_bindir}/cssort
%{_bindir}/cstrans-df-run
%{_datadir}/%{name}
%{_mandir}/man1/csdiff.1*
%{_mandir}/man1/csgrep.1*
%{_mandir}/man1/cshtml.1*
%{_mandir}/man1/cslinker.1*
%{_mandir}/man1/cssort.1*
%{_mandir}/man1/cstrans-df-run.1*

%if %{with python2}
%files -n python2-%{name}
%license COPYING
%{python2_sitearch}/pycsdiff.so
%endif

%if %{with python3}
%files -n python3-%{name}
%license COPYING
%{python3_sitearch}/pycsdiff.so
%endif
EOF

if [[ "$1" != "--generate-spec" ]]; then
    rpmbuild -bs "$SPEC"                            \
        --define "_sourcedir ."                     \
        --define "_specdir ."                       \
        --define "_srcrpmdir $DST"
fi
