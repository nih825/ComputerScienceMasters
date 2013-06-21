import time

filename=raw_input("Enter filename: ")
f=open(filename)
start=time.time()
filehandle=filename.split(".")[0]

lines = f.readlines()
[line.strip() for line in lines]
lines = [ line.strip() for line in [ li for li in lines ] ]
for line in lines:
    if line=='':
        lines.remove(line)

for i in range(0,len(lines)):
    lines[i]="".join(lines[i].split())
    if "//" in lines[i]:
        lines[i]=lines[i].split("//", 1)[0]

lines = filter(lambda x : len(x) > 0, lines)

def RepresentsInt(s):
    try: 
        int(s)
        return True
    except ValueError:
        return False
def decToBin(n):
    if n==0: return ''
    else:
        return decToBin(n/2) + str(n%2)
def make16bits(n):
    a=decToBin(n)
    diff=16-len(a)
    pre=""
    for i in range(0,diff):
        pre=pre+"0"
    return pre+a

symbols = {"SP":"0000000000000000","LCL":"0000000000000001","ARG":"0000000000000010","THIS":"0000000000000011",
           "THAT":"0000000000000100","SCREEN": "0100000000000000","KBD":"0101111111110111",
           "R0":"0000000000000000","R1":"0000000000000001","R2":"0000000000000010",
           "R3":"0000000000000011","R4":"0000000000000100","R5":"0000000000000101",
           "R6":"0000000000000110","R7":"0000000000000111","R8":"0000000000001000",
           "R9":"0000000000001001","R10":"0000000000001010","R11":"0000000000001011",
           "R12":"0000000000001100","R13":"0000000000001101","R14":"0000000000001110",
           "R15":"0000000000001111"}

lTable={}
dest={"null":"000","AMD":"111","AM":"101","MD":"011","AD":"110","M":"001","D":"010","A":"100"}
jump={"null":"000","JGT":"001","JEQ":"010","JGE":"011","JLT":"100","JNE":"101","JLE":"110","JMP":"111"}
compA0={"0":"101010","1":"111111","-1":"111010","D":"001100","A":"110000","!D":"001101","!A":"110001","-D":"001111",
        "-A":"110011","D+1":"011111","A+1":"110111","D-1":"001110","A-1":"110010","D+A":"000010","D-A":"010011",
        "A-D":"000111","D&A":"000000","D|A":"010101"}
compA1={"M":"110000","!M":"110001","-M":"110011","M+1":"110111","M-1":"110010","D+M":"000010","D-M":"010011",
        "M-D":"000111","D&M":"000000","D|M":"010101"}

def computeCInstruction(line):
    jumpinst="000"
    destinst="000"
    compinst="000000"
    a="0"
    jumpKeys=jump.keys()
    for key in jumpKeys:
        if key in line:
            jumpinst=jump[key]
    if "=" in line:
        tokenized=line.split("=")
        destside=tokenized[0]
        compside=tokenized[1]
        compside=compside.split(";")[0]
        comp0Keys=compA0.keys()
        comp1Keys=compA1.keys()
        for key in comp0Keys:
            if key == compside:
                a="0"
                compinst=compA0[key]
        for key in comp1Keys:
            if key == compside:
                a="1"
                compinst=compA1[key]
        destKeys=dest.keys()
        for key in destKeys:
            if key == destside:
                destinst=dest[key]   
    else:
        compKeys=compA0.keys()
        for key in compKeys:
            if key in line:
                compinst=compA0[key]   
    return "111"+a+compinst+destinst+jumpinst

currentRamCounter=16
lineNumber=0
for line in lines:
    if line[0]=="(":
        i=1;
        while line[i]!=")":
            i+=1
        varname=line[1:i]
        if varname not in lTable.keys():
            lTable[varname]=make16bits(lineNumber)
    else:
        lineNumber+=1

for line in lines:
    if line[0]=="@":
        tokenized=line.split()
        varname=tokenized[0][1::]
        if(RepresentsInt(line[1:len(line)])==False):
            if(varname not in symbols.keys() and varname not in lTable.keys()):
                symbols[varname]=make16bits(currentRamCounter)
                currentRamCounter+=1

                
finalInstructions=[]
for line in lines:
    if line[0]=="@":
        if(RepresentsInt(line[1:len(line)])==True):
            finalInstructions.append(make16bits(int(line[1:len(line)])))
        else:
            tokenized=line.split()
            varname=tokenized[0][1::]
            if varname in lTable.keys():
                finalInstructions.append(lTable[varname])
            else:
                finalInstructions.append(symbols[varname])
    elif line[0]=="(":
        continue
    else:
        finalInstructions.append(computeCInstruction(line))             
outputfile=filehandle+".hack"
f=open(outputfile,"w")

for line in finalInstructions:
    f.write(line+"\n")
f.close()
                
print time.time()-start                

