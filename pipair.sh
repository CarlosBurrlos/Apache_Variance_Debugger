#!/bin/bash

# Call format
# ../pipair $SOURCE.bc $SUPPORT $CONFIDENCE > $TESTNAME_$SUPPORT_$CONFIDENCE.out 2>&1

# Vars
SRC=$1
SUP=$2
CONF=$3
CG=cg

# Generate callgraph and send it to raw format file
opt -f -print-callgraph $1 2> $(CG)

# Remove first 5 lines (message we do not want)
sed -e '1,5d' < $(CG) > $(CG).txt

# Run our debugger on it
Debugger $(CG).txt $(SUP) $(CONF)

