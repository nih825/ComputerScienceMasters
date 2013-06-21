INCLUDE=/usr/lib/jvm/java-6-openjdk/include
JSRC=ArrayManip
CSRC=arraymanip

run: ${JSRC}.class
	export LD_LIBRARY_PATH=.
	java ${JSRC}
${JSRC}.class : ${JSRC}.java ${CSRC}.so
	javac ${JSRC}.java
${CSRC}.o : ${CSRC}.cc
	g++ -fpic -c  -I${INCLUDE} ${CSRC}.cc
${CSRC}.so : ${CSRC}.o
	g++ -fpic -shared ${CSRC}.o -I${INCLUDE} -o ${CSRC}.so	
clean :
	\rm -f *~ *.o *.so *.class *#
