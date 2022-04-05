# FIXME: copy-pasted from ../../CMakeLists.txt
export JSFILTER_CMD="sed -e ':a;N;\$!ba;s|:\\n *\\[|: [|g'"

# eliminate csdiff's version string in the output
JSFILTER_CMD="${JSFILTER_CMD} -e 's|\"version\": \"[^\"]*\"|\"version\": \"\"|g'"

# yet another conversion needed for scan properties on EPEL-7
JSFILTER_CMD="${JSFILTER_CMD}';s|:\\n *{|: {|g'"
