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
cd "$PKG"                               || die "git clone failed"

make -j5 distcheck CTEST='ctest -j5'    || die "'make distcheck' has failed"

NV="${PKG}-$VER"
SRC="${PKG}.tar.xz"
git archive --prefix="$NV/" --format="tar" HEAD -- . | xz -c > "$SRC"

SPEC="./$PKG.spec"
cat > "$SPEC" << EOF
%{!?python_sitearch: %define python_sitearch %(%{__python} -c "from distutils.sysconfig import get_python_lib; print get_python_lib(1)")}

Name:       $PKG
Version:    $VER
Release:    1%{?dist}
Summary:    Non-interactive tools for processing code scan results in plain-text

Group:      Applications/Text
License:    GPLv3+
URL:        http://git.fedorahosted.org/cgit/codescan-diff.git
Source0:    $SRC
BuildRoot:  %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires: boost-devel
BuildRequires: cmake
BuildRequires: flex
BuildRequires: python-devel

%description
This package contains the csdiff tool for comparing code scan defect lists in
order to find out added or fixed defects, and the csgrep utility for filtering
defect lists using various filtering predicates. 

%prep
%setup -q

%build
make %{?_smp_mflags} CMAKE='cmake -D CMAKE_INSTALL_PREFIX=/usr' VERBOSE=yes

%install
rm -rf "\$RPM_BUILD_ROOT"
make install DESTDIR="\$RPM_BUILD_ROOT"
install -d "\$RPM_BUILD_ROOT%{python_sitearch}/"
mv -v "\$RPM_BUILD_ROOT/usr/lib/libpycsdiff.so" \
    "\$RPM_BUILD_ROOT%{python_sitearch}/pycsdiff.so"

%check
make check CTEST='ctest %{?_smp_mflags}'

%clean
rm -rf "\$RPM_BUILD_ROOT"

%files
%defattr(-,root,root,-)
%{_bindir}/csannot
%{_bindir}/csdiff
%{_bindir}/csgrep
%{_bindir}/cshtml
%{_bindir}/csjson
%{_bindir}/cslinker
%{_bindir}/cssort
%{_bindir}/cstat
%{python_sitearch}/pycsdiff.so
%doc COPYING README
EOF

set -v
rpmbuild -bs "$SPEC"                            \
    --define "_sourcedir ."                     \
    --define "_specdir ."                       \
    --define "_srcrpmdir $DST"                  \
    --define "_source_filedigest_algorithm md5" \
    --define "_binary_filedigest_algorithm md5"
