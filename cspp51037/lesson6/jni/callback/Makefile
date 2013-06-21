INCLUDE=/usr/lib/jvm/java-6-openjdk/include
JSRC=Callbacks
CSRC=Callbacks

run: ${JSRC}.class
	export LD_LIBRARY_PATH=.
	java ${JSRC} 1000
${JSRC}.class : ${JSRC}.java ${CSRC}.so
	javac ${JSRC}.java
${CSRC}.o : ${CSRC}.c
	gcc -fpic -c  -I${INCLUDE} -I. ${CSRC}.c
${CSRC}.so : ${CSRC}.o
	gcc -fpic -shared ${CSRC}.o -I${INCLUDE} -I. -o lib${CSRC}.so	
clean :
	\rm -f *~ *.o *.so *.class *#
