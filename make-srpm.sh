#/bin/bash
SELF="$0"

PKG="csdiff"

die(){
    echo "$SELF: error: $1" >&2
    exit 1
}

DST="`readlink -f "$PWD"`"

REPO="`git rev-parse --show-toplevel`" \
    || die "not in a git repo"

printf "%s: considering release of %s using %s...\n" \
    "$SELF" "$PKG" "$REPO"

branch="`git status | head -1 | sed 's/^#.* //'`" \
    || die "unable to read git branch"

test xmaster = "x$branch" \
    || die "not in master branch"

test -z "`git diff HEAD`" \
    || die "HEAD dirty"

test -z "`git diff origin/master`" \
    || die "not synced with origin/master"

VER="0.`git log --pretty="%cd_%h" --date=short -1 | tr -d -`" \
    || die "git log failed"

TMP="`mktemp -d`"
trap "echo --- $SELF: removing $TMP... 2>&1; rm -rf '$TMP'" EXIT
cd "$TMP" >/dev/null || die "mktemp failed"

# clone the repository
git clone "$REPO" "$PKG"                || die "git clone failed"
cd "$PKG/$PKG"                          || die "git clone failed"

make -j5 distcheck CTEST='ctest -j5'    || die "'make distcheck' has failed"

NV="${PKG}-$VER"
SRC="${PKG}.tar.xz"
git archive --prefix="$NV/$PKG/" --format="tar" HEAD -- . | xz -c > "$SRC"
tar tf "$SRC"

SPEC="./$PKG.spec"
cat > "$SPEC" << EOF
Name:       $PKG
Version:    $VER
Release:    1%{?dist}
Summary:    Non-interactive tools for processing Coverity results in plain-text

Group:      CoverityScan
License:    GPLv3+
URL:        https://engineering.redhat.com/trac/CoverityScan
Source0:    $SRC

BuildRequires: cmake
BuildRequires: flex
BuildRequires: boost-devel

%description
This package contains the csdiff tool for comparing Coverity plain-text defect
lists in order to find out added or fixed defects.  There is also the csgrep
utility for filtering defect lists using various filtering predicates.  It can
also be used for summarizing the results and exporting them to a JSON-based
data format.

%prep
%setup -q

%build
make %{?_smp_mflags} -C $PKG                    \
    CMAKE='cmake -D CMAKE_INSTALL_PREFIX=/usr'  \
    VERBOSE=yes

%install
make -C $PKG install DESTDIR="\$RPM_BUILD_ROOT"

%check
make -C $PKG check CTEST='ctest %{?_smp_mflags}'

%files
%defattr(-,root,root,-)
%{_bindir}/csannot
%{_bindir}/csdiff
%{_bindir}/csgrep
%{_bindir}/cstat
%{_bindir}/linkify
EOF

set -v
rpmbuild -bs "$SPEC"            \
    --define "_sourcedir ."     \
    --define "_specdir ."       \
    --define "_srcrpmdir $DST"
