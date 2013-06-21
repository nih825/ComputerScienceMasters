map={"local":"LCL","argument":"ARG", "this": "THIS","that":"THAT"}

def push(arg1, arg2):
    
    hackInstructions=[]
    if arg1=="constant":
        hackInstructions.append("@"+arg2)
        hackInstructions.append("D=A")    
    elif arg1 in map.keys():
        hackInstructions.append("@"+map[arg1])
        hackInstructions.append("D=M")
        hackInstructions.append("@"+arg2)
        hackInstructions.append("A=D+A")
        hackInstructions.append("D=M")
    elif arg1=="temp" or arg1=="pointer":
        start=5
        if(arg1=="pointer"):
            start=3
        hackInstructions.append("@"+str(start+int(arg2)))
        hackInstructions.append("D=M")
    elif arg1=="static":
        hackInstructions.append("@"+filehandle+"."+str(arg2))
        hackInstructions.append("D=M")
    hackInstructions.append("@SP")
    hackInstructions.append("A=M")
    hackInstructions.append("M=D")
    hackInstructions.append("@SP")
    hackInstructions.append("M=M+1")
    return hackInstructions

def pop(arg1, arg2):
    hackInstructions=[]
    if arg1 in map.keys():
        hackInstructions.append("@"+map[arg1])
        hackInstructions.append("D=M")
        hackInstructions.append("@"+arg2)
        hackInstructions.append("D=D+A")
        hackInstructions.append("@R13")
        hackInstructions.append("M=D")
        hackInstructions.append("@SP")
        hackInstructions.append("M=M-1")
        hackInstructions.append("A=M")
        hackInstructions.append("D=M")
        hackInstructions.append("@R13")
        hackInstructions.append("A=M")
        hackInstructions.append("M=D")
    elif arg1=="temp" or arg1=="pointer":
        start=5
        if(arg1=="pointer"):
            start=3
        hackInstructions.append("@SP")
        hackInstructions.append("M=M-1")
        hackInstructions.append("A=M")
        hackInstructions.append("D=M")
        hackInstructions.append("@"+str(start+int(arg2)))
        hackInstructions.append("M=D")
    elif arg1=="static":
        hackInstructions.append("@SP")
        hackInstructions.append("M=M-1")
        hackInstructions.append("A=M")
        hackInstructions.append("D=M")
        hackInstructions.append("@"+filehandle+"."+str(arg2))
        hackInstructions.append("M=D")
    return hackInstructions

def AddSub(symbol):
    hackInstructions=[]
    hackInstructions.append("@SP")
    hackInstructions.append("M=M-1")
    hackInstructions.append("A=M")
    hackInstructions.append("D=M")
    hackInstructions.append("@SP")
    hackInstructions.append("M=M-1")
    hackInstructions.append("A=M")
    hackInstructions.append("D=M"+symbol+"D")
    hackInstructions.append("@SP")
    hackInstructions.append("A=M")
    hackInstructions.append("M=D")
    hackInstructions.append("@SP")
    hackInstructions.append("M=M+1")
    return hackInstructions

def NegateNot(symbol):
    hackInstructions=[]
    hackInstructions.append("@SP")
    hackInstructions.append("M=M-1")
    hackInstructions.append("A=M")
    hackInstructions.append("D=M")
    if symbol=="neg":
        hackInstructions.append("@0")
        hackInstructions.append("D=A-D")    
    elif symbol=="!":
        hackInstructions.append("D=!D")
    hackInstructions.append("@SP")
    hackInstructions.append("A=M")
    hackInstructions.append("M=D")
    hackInstructions.append("@SP")
    hackInstructions.append("M=M+1")
    return hackInstructions

def comparison(symbol, comparisonCounter):
    hackInstructions=[]
    hackInstructions.append("@SP")
    hackInstructions.append("M=M-1")
    hackInstructions.append("A=M")
    hackInstructions.append("D=M")
    hackInstructions.append("@SP")
    hackInstructions.append("M=M-1")
    hackInstructions.append("A=M")
    hackInstructions.append("D=M-D")
    hackInstructions.append("@ELSE"+str(comparisonCounter))
    if symbol=="gt":
        hackInstructions.append("D;JLE")
    elif symbol=="lt":
        hackInstructions.append("D;JGE")
    elif symbol=="eq":
        hackInstructions.append("D;JNE")
    hackInstructions.append("@SP")
    hackInstructions.append("A=M")
    hackInstructions.append("M=-1")
    hackInstructions.append("@SP")
    hackInstructions.append("M=M+1")
    hackInstructions.append("@CONTINUE"+str(comparisonCounter))
    hackInstructions.append("0;JMP")
    hackInstructions.append("(ELSE"+str(comparisonCounter)+")")
    hackInstructions.append("@SP")
    hackInstructions.append("A=M")
    hackInstructions.append("M=0")
    hackInstructions.append("@SP")
    hackInstructions.append("M=M+1")
    hackInstructions.append("(CONTINUE"+str(comparisonCounter)+")")
    comparisonCounter+=1
    return hackInstructions

def label(symbol):
    hackInstructions=[]
    hackInstructions.append("("+filehandle.upper()+symbol+")")
    return hackInstructions

def goto(symbol):
    hackInstructions=[]
    hackInstructions.append("@"+filehandle.upper()+symbol)
    hackInstructions.append("0; JMP")
    return hackInstructions

def if_goto(symbol):
    hackInstructions=[]
    hackInstructions.append("@SP")
    hackInstructions.append("AM=M-1")
    hackInstructions.append("D=M")
    hackInstructions.append("@"+filehandle.upper()+symbol)
    hackInstructions.append("D; JNE")
    return hackInstructions

def function(arg1, arg2):
    hackInstructions=[]
    hackInstructions.append("("+arg1+")")
    tempInstructions=push("constant","0")
    for i in range(0,int(arg2)):
        for line in tempInstructions:
            hackInstructions.append(line)
        i+=1
    return hackInstructions
# 'call Main.fibonacci 1'
def call(arg1, arg2, functCount):
    hackInstructions=[]
    hackInstructions.append("@RETURNADDR"+str(functCount))
    hackInstructions.append("D=A")
    hackInstructions.append("@SP")
    hackInstructions.append("A=M")
    hackInstructions.append("M=D")
    hackInstructions.append("@SP")
    #hackInstructions.append("A=M")
    hackInstructions.append("M=M+1")
#    pushLoc=push("local","0")
#    for line in pushLoc:
#        hackInstructions.append(line)
#    pushArg=push("argument","0")
#    for line in pushArg:
#        hackInstructions.append(line)
#    pushThis=push("this","0")
#    for line in pushThis:
#        hackInstructions.append(line)
#    pushThat=push("that","0")
#    for line in pushThat:
#        hackInstructions.append(line)
    hackInstructions.append("@LCL")
    hackInstructions.append("D=M")
    hackInstructions.append("@SP")
    hackInstructions.append("A=M")
    hackInstructions.append("M=D")
    hackInstructions.append("@SP")
    hackInstructions.append("M=M+1")

    hackInstructions.append("@ARG")
    hackInstructions.append("D=M")
    hackInstructions.append("@SP")
    hackInstructions.append("A=M")
    hackInstructions.append("M=D")
    hackInstructions.append("@SP")
    hackInstructions.append("M=M+1")
    
    hackInstructions.append("@THIS")
    hackInstructions.append("D=M")
    hackInstructions.append("@SP")
    hackInstructions.append("A=M")
    hackInstructions.append("M=D")
    hackInstructions.append("@SP")
    hackInstructions.append("M=M+1")
    
    hackInstructions.append("@THAT")
    hackInstructions.append("D=M")
    hackInstructions.append("@SP")
    hackInstructions.append("A=M")
    hackInstructions.append("M=D")
    hackInstructions.append("@SP")
    hackInstructions.append("M=M+1")
    
    
    hackInstructions.append("@SP")
    hackInstructions.append("D=M")
    hackInstructions.append("@5")
    hackInstructions.append("D=D-A")
    hackInstructions.append("@"+str(arg2))
    hackInstructions.append("D=D-A")
    hackInstructions.append("@ARG")
    hackInstructions.append("M=D")
    hackInstructions.append("@SP")
    hackInstructions.append("D=M")
    hackInstructions.append("@LCL")
    hackInstructions.append("M=D")
    hackInstructions.append("@"+arg1)
    hackInstructions.append("0; JMP")  
    hackInstructions.append("(RETURNADDR"+str(functCount)+")")
    return hackInstructions
    
def return_call():
    hackInstructions=[]
    hackInstructions.append("@LCL")
    hackInstructions.append("D=M")
    hackInstructions.append("@FRAME")
    hackInstructions.append("M=D")
    hackInstructions.append("@5")
    hackInstructions.append("D=D-A")
    hackInstructions.append("A=D")
    hackInstructions.append("D=M")
    hackInstructions.append("@RET")
    hackInstructions.append("M=D")
    hackInstructions.append("@SP")
    hackInstructions.append("AM=M-1")
    hackInstructions.append("D=M")
    hackInstructions.append("@ARG")
    hackInstructions.append("A=M")
    hackInstructions.append("M=D")
    hackInstructions.append("@ARG")
    hackInstructions.append("D=M+1")
    hackInstructions.append("@SP")
    hackInstructions.append("M=D")
    hackInstructions.append("@FRAME")
    hackInstructions.append("M=M-1")
    hackInstructions.append("A=M")
    hackInstructions.append("D=M")
    hackInstructions.append("@THAT")
    hackInstructions.append("M=D")
    hackInstructions.append("@FRAME")
    hackInstructions.append("M=M-1")
    hackInstructions.append("A=M")
    hackInstructions.append("D=M")
    hackInstructions.append("@THIS")
    hackInstructions.append("M=D")
    hackInstructions.append("@FRAME")
    hackInstructions.append("M=M-1")
    hackInstructions.append("A=M")
    hackInstructions.append("D=M")
    hackInstructions.append("@ARG")
    hackInstructions.append("M=D")
    hackInstructions.append("@FRAME")
    hackInstructions.append("M=M-1")
    hackInstructions.append("A=M")
    hackInstructions.append("D=M")
    hackInstructions.append("@LCL")
    hackInstructions.append("M=D")
    hackInstructions.append("@RET")
    hackInstructions.append("A=M")
    hackInstructions.append("0;JMP")    
    return hackInstructions

hackInstructions=[]
functCounter=0
"""hackInstructions.append("@256")
hackInstructions.append("D=A")
hackInstructions.append("@SP")
hackInstructions.append("M=D")
startupInst=call("Sys.init","0", functCounter)
for line in startupInst:
    hackInstructions.append(line)"""
comparisonCounter=0
#functCounter=1


filename=raw_input("Enter filename: ")
while filename.lower() !="done":
    f=open(filename)
    filehandle=filename.split(".")[0]
    lines = f.readlines()
    lines = [ line.strip() for line in [ li for li in lines ] ]
    for line in lines:
        if line=='':
            lines.remove(line)
    
    for i in range(0,len(lines)):
        if "//" in lines[i]:
            lines[i]=lines[i].split("//", 1)[0]
    
    lines = filter(lambda x : len(x) > 0, lines)
    
    line_tokens=[line.split() for line in lines]
    
    for line in line_tokens:
        if line[0]=="push":
            intermediateIns=push(line[1],line[2])
            for line in intermediateIns:
                hackInstructions.append(line)
        elif line[0]=="pop":
            intermediateIns=pop(line[1], line[2])
            for line in intermediateIns:
                hackInstructions.append(line)
        elif line[0]=="add":
            intermediateIns=AddSub("+")
            for line in intermediateIns:
                hackInstructions.append(line)
        elif line[0]=="sub":
            intermediateIns=AddSub("-")
            for line in intermediateIns:
                hackInstructions.append(line)
        elif line[0]=="and":
            intermediateIns=AddSub("&")
            for line in intermediateIns:
                hackInstructions.append(line)
        elif line[0]=="or":
            intermediateIns=AddSub("|")
            for line in intermediateIns:
                hackInstructions.append(line)
        elif line[0]=="neg":
            intermediateIns=NegateNot("neg")
            for line in intermediateIns:
                hackInstructions.append(line)
        elif line[0]=="not":
            intermediateIns=NegateNot("!")
            for line in intermediateIns:
                hackInstructions.append(line)
        elif line[0]=="gt":
            intermediateIns=comparison("gt",comparisonCounter)
            comparisonCounter+=1
            for line in intermediateIns:
                hackInstructions.append(line)
        elif line[0]=="lt":
            intermediateIns=comparison("lt",comparisonCounter)
            comparisonCounter+=1
            for line in intermediateIns:
                hackInstructions.append(line)
        elif line[0]=="eq":
            intermediateIns=comparison("eq",comparisonCounter)
            comparisonCounter+=1
            for line in intermediateIns:
                hackInstructions.append(line)
        elif line[0]=="label":
            intermediateIns=label(line[1])
            for line in intermediateIns:
                hackInstructions.append(line)
        elif line[0]=="goto":
            intermediateIns=goto(line[1])
            for line in intermediateIns:
                hackInstructions.append(line)
        elif line[0]=="if-goto":
            intermediateIns=if_goto(line[1])
            for line in intermediateIns:
                hackInstructions.append(line)
        elif line[0]=="call":
            hackInstructions.append("//Function Call")
            intermediateIns=call(line[1],line[2],functCounter)
            for line in intermediateIns:
                hackInstructions.append(line)
            functCounter+=1
        elif line[0]=="return":
            hackInstructions.append("//Return call")
            intermediateIns=return_call()
            for line in intermediateIns:
                hackInstructions.append(line)
        elif line[0]=="function":
            hackInstructions.append("//Function def")
            intermediateIns=function(line[1],line[2])
            for line in intermediateIns:
                hackInstructions.append(line) 
    filename=raw_input("Enter another filename or enter done if there are no more files: ")

output=raw_input("Enter output filename: ")
f=open(output,"w")
print hackInstructions 
for line in hackInstructions:
    f.write(line+"\n")
f.close()
    
    

