#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libftxf/.libs/libftxf.1.dylib && test -f ./pyftxf/.libs/pyftxf.so;
then
	install_name_tool -change /usr/local/lib/libftxf.1.dylib ${PWD}/libftxf/.libs/libftxf.1.dylib ./pyftxf/.libs/pyftxf.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

