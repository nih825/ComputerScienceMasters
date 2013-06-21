INCLUDE=/usr/lib/jvm/java-6-openjdk/include
JSRC=Utils
CSRC=utils

run: ${JSRC}.class
	export LD_LIBRARY_PATH=.
	java ${JSRC}
${JSRC}.class : ${JSRC}.java ${CSRC}.so
	javac ${JSRC}.java
${CSRC}.o : ${CSRC}.c
	gcc -fpic -c  -I${INCLUDE} ${CSRC}.c
${CSRC}.so : ${CSRC}.o
	gcc -fpic -shared ${CSRC}.o -I${INCLUDE} -o lib${CSRC}.so	
clean :
	\rm -f *~ *.o *.so *.class *#
