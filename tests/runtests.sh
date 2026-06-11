#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libftxf/.libs/libftxf.1.dylib && test -f ./pyftxf/.libs/pyftxf.so
then
	install_name_tool -change /usr/local/lib/libftxf.1.dylib ${PWD}/libftxf/.libs/libftxf.1.dylib ./pyftxf/.libs/pyftxf.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

