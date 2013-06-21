// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, the
// program clears the screen, i.e. writes "white" in every pixel.

// Put your code here.

(GO_TIME)
	@KBD
	D=M
	@TURN_BLACK
	D; JNE

(TURN_WHITE)
	@color
	M=0
	@INITIALIZE_LOOP
	0;JMP

(TURN_BLACK)
	@color
	M=-1	

(INITIALIZE_LOOP)
	@8192
	D=A
	@locationsleft
	M=D
	@SCREEN
	D=A
	@currentlocation
	M=D	

(START_COLORING)	
	@locationsleft
	D=M
	@GO_TIME
	D;JLE	
	@color
	D=M
	@currentlocation
	A=M
	M=D
	@locationsleft
	M=M-1	
	@currentlocation
	M=M+1	
	@START_COLORING
	0;JMP

