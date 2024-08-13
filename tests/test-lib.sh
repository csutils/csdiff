# shellcheck shell=sh

# FIXME: copy-pasted from ../../CMakeLists.txt
# eliminate csdiff's version string in the output
export JSFILTER_CMD="sed \
    -e 's|\"version\": \"[^\"]*\"|\"version\": \"\"|g' \
    -e 's|$PROJECT_ROOT/tests/csfilter-kfp/|\$PROJECT_ROOT/tests/csfilter-kfp/|'"
