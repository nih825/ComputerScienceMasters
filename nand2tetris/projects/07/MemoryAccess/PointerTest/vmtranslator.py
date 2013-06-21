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



filename=raw_input("Enter filename: ")
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

hackInstructions=[]
comparisonCounter=0
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
print hackInstructions    

outputfile=filehandle+".asm"
f=open(outputfile,"w")

for line in hackInstructions:
    f.write(line+"\n")
f.close()
    
    

