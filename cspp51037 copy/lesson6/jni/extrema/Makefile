INCLUDE=/usr/lib/jvm/java-6-openjdk/include
JSRC=ArrUtils
CSRC=arrutils

run: ${CSRC}.so
	export LD_LIBRARY_PATH=.
	java ${JSRC}
${CSRC}.c : ${JSRC}.class
	javah ${JSRC}
${CSRC}.o : 
	cc -fpic -c  -I${INCLUDE} -I. ${CSRC}.c
${CSRC}.so : ${CSRC}.o
	cc -fpic -shared ${CSRC}.o -I${INCLUDE} -I. -o lib${CSRC}.so	
clean :
	\rm -f *~ *.o *.so *.class *#
