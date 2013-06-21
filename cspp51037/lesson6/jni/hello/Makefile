INCLUDE=/usr/lib/jvm/java-6-openjdk/include

run: HelloWorld.class
	export LD_LIBRARY_PATH=.
	java HelloWorld
HelloWorld.class : HelloWorld.java libhello.so
	javac HelloWorld.java
hello.o : hello.c
	cc -fpic -c  -I${INCLUDE} hello.c	
libhello.so : hello.o
	cc -fpic -shared hello.o -I${INCLUDE} -o libhello.so	
clean :
	\rm -f *~ *.o *.so *.class *#
