import glob




class Token:
    def __init__(self,symbol,category):
        self.symbol=symbol
        self.category=category
    def printTok(self):
        if self.symbol=="<":
            return "<"+self.category+"> "+"&lt;"+" </"+self.category+">"
        elif self.symbol==">":
            return "<"+self.category+"> "+"&gt;"+" </"+self.category+">"
        elif self.symbol=="&":
            return "<"+self.category+"> "+"&amp;"+" </"+self.category+">"
        elif self.category=="StringConstant":
            return "<stringConstant> "+self.symbol[1:-1]+" </stringConstant>"
        else:
            return "<"+self.category+"> "+self.symbol+" </"+self.category+">" 
    
class Variable:
    def __init__(self,name,typeOf, kind, number):
        self.name=name
        self.typeOf=typeOf
        self.kind=kind
        self.number=number
    def printVar(self):
        print self.name +" "+self.typeOf+" "+self.kind
     
def is_number(s):
    try:
        int(s)
        return True
    except ValueError:
        return False

def validIdentifier(s):
    for c in s:
        if c=="_" or is_number(c) or c in lowercase or c in uppercase:
            continue
        else:
            return False
    return True

lowercase="abcdefghijklmnopqrstuvwxyz"
uppercase="ABCDEFGHIJKLMNOPQRSTUVWXYZ"    
#filename=raw_input("Enter filename: ")
filePaths=glob.glob("*.jack")
for file1 in filePaths:
    filename=file1

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
    lines = [ line.strip() for line in [ li for li in lines ] ]    
        
    lines = filter(lambda x : len(x) > 0, lines)
    totalFile=""
    for line in lines:
        totalFile+=line
        totalFile+="\n"
    
    whiteSpace=[" ","\t","\n"]
    
    keyword=["class", "constructor", "function", "method", "field", "static", "var","int","char","boolean",
              "void","true","false","null","this","let","do","if","else","while","return"]
    
    symbol=["{","}","(",")","[","]",".",",",";","+","-","*","/","&","|","<",">","=","~"]
    
    KeywordConstant=["true","false","null","this"]
    
    statements=["let","if","else","while","do","return"]
    classScopeVariables=[]
    subroutineVariables=[]
    classVars=["static", "field"]
    op=['+','-','*','/','&','|','<','>','=']
    opMap={'+':"add",'-':"sub",'*':"call Math.multiply 2",'/':"call Math.divide 2",">":"gt","<":"lt","&":"and"
           ,"=":"eq","|":"or"}
    unaryOp=['-','~']
    prev=""
    current=""
    currentToken=""
    allTokens=[]
    tokenObjects=[]
    done=False
    for c in totalFile:
        prev=current
        current=current+c
        if current in keyword:
            currentToken="keyword"
        elif current in symbol:
            currentToken="symbol"
        elif is_number(current):
            currentToken="integerConstant"
        elif validIdentifier(current):
            currentToken="identifier"
        elif current=="/*":
            currentToken="commentPart"
        elif currentToken=="commentPart" and current[len(current)-1]=="/"and current[len(current)-2]=="*":
            currentToken="comment"
        elif c=='"' and currentToken=="":
            currentToken="stringPart"
        elif c=='"' and currentToken=="stringPart":
            currentToken="StringConstant"
        elif currentToken !="" and currentToken != "commentPart" and currentToken != "stringPart":
            allTokens.append("<"+currentToken+">"+prev+"</"+currentToken+">")
            currTok=Token(prev,currentToken)
            if currentToken != "comment":
                tokenObjects.append(currTok)
            currentToken=""
            prev=""
            if c==" " or c=="\t" or c=="\n" or c=="\r":
                current=""
            else:
                current=c
                if current in keyword:
                    currentToken="keyword"
                elif current in symbol:
                    currentToken="symbol"
                elif is_number(current):
                    currentToken="integerConstant"
                elif validIdentifier(current):
                    currentToken="identifier"
                elif c=='"':
                    currentToken="stringPart"
#    for tok in tokenObjects:
 #       print tok.printTok()
    
   # print totalFile
 #   print len(tokenObjects)
    
    print "\n\n\n"         
    xml=[]       
    currentTok=0                     
    indent=0
    def printXml(term):
        s=""
        for i in range(0,indent):
            s+=" "
            s+=" "
        s+=term
        xml.append(s)     
          
    def demand(s):
        global currentTok
        if tokenObjects[currentTok].symbol==s:
            printXml(tokenObjects[currentTok].printTok())
            currentTok+=1
        else:
            raise Exception("Missing " +s)
    
    def compileExpression():
        global currentTok
        global indent
        printXml("<expression>")
        indent+=1
        compileTerm()
        while currentTok<len(tokenObjects) and tokenObjects[currentTok].symbol in op:
            symb=tokenObjects[currentTok].symbol
            printXml(tokenObjects[currentTok].printTok())
            currentTok+=1
            compileTerm()
            vmInstructions.append(opMap[symb])
        indent-=1
        printXml("</expression>")
        
    
    def compileTerm():
        global currentTok
        global indent
        global vmInstructions
        printXml("<term>")
        indent+=1
        category=tokenObjects[currentTok].category
        if category=="integerConstant" or category=="StringConstant":
            if(category=="integerConstant"):
                if int(tokenObjects[currentTok].symbol)<0:
                    vmInstructions.append("push constant "+str(int(tokenObjects[currentTok].symbol)*-1))
                    vmInstructions.append("neg")
                else:
                    vmInstructions.append("push constant "+tokenObjects[currentTok].symbol)
            else:
                vmInstructions.append("push constant "+str(len(tokenObjects[currentTok].symbol)-2))
                vmInstructions.append("call String.new 1")
                for char in tokenObjects[currentTok].symbol[1:-1]:
                    vmInstructions.append("push constant "+str(ord(char)))
                    vmInstructions.append("call String.appendChar 2")
            printXml(tokenObjects[currentTok].printTok())
            currentTok+=1
        elif category=="keyword" and tokenObjects[currentTok].symbol in KeywordConstant:
            if tokenObjects[currentTok].symbol=="true":
                vmInstructions.append("push constant 0")
                vmInstructions.append("not")
            elif tokenObjects[currentTok].symbol=="false":
                vmInstructions.append("push constant 0")
            elif tokenObjects[currentTok].symbol=="this":
                vmInstructions.append("push pointer 0")
            elif tokenObjects[currentTok].symbol=="null":
                vmInstructions.append("push constant 0")
            printXml(tokenObjects[currentTok].printTok())
            currentTok+=1
        elif tokenObjects[currentTok].symbol in unaryOp:
            if tokenObjects[currentTok].symbol=="~":
                temp="not"
            else:
                temp="neg"
            printXml(tokenObjects[currentTok].printTok())
            currentTok+=1
            compileTerm()
            vmInstructions.append(temp)
        elif category=="identifier":
            nextTok=tokenObjects[currentTok+1]
            if nextTok.symbol=='[':
                outside=tokenObjects[currentTok].symbol
                printXml(tokenObjects[currentTok].printTok()) 
                printXml(nextTok.printTok())
                currentTok+=2
                compileExpression()
                for var in subroutineVariables:
                    if outside==var.name:
                        if var.kind=="argument":
                            vmInstructions.append("push argument "+str(var.number))
                        else:
                            vmInstructions.append("push local "+str(var.number))
                        break
                for var in classScopeVariables:
                    if outside==var.name:
                        if var.kind=="field":
                            vmInstructions.append("push this "+str(var.number))
                        elif var.kind=="static":
                            vmInstructions.append("push static "+str(var.number))
                        break
                if tokenObjects[currentTok].symbol==']':
                    printXml(tokenObjects[currentTok].printTok())
                    currentTok+=1
                else:
                    raise Exception("Missing ]")
                vmInstructions.append("add")
                vmInstructions.append("pop pointer 1")
                vmInstructions.append("push that 0")
            elif nextTok.symbol=="(" or nextTok.symbol==".":
                    compileSubroutine()
            else:
                for var in subroutineVariables:
                    if tokenObjects[currentTok].symbol==var.name:
                        if var.kind=="argument":
                            vmInstructions.append("push argument "+str(var.number))
                        else:
                            vmInstructions.append("push local "+str(var.number))
                        break
                for var in classScopeVariables:
                    if tokenObjects[currentTok].symbol==var.name:
                        if var.kind=="field":
                            vmInstructions.append("push this "+str(var.number))
                        elif var.kind=="static":
                            vmInstructions.append("push static "+str(var.number))
                        break
                printXml(tokenObjects[currentTok].printTok())
                currentTok+=1
        elif tokenObjects[currentTok].symbol=="(":
            printXml(tokenObjects[currentTok].printTok())
            currentTok+=1
            compileExpression()
            if tokenObjects[currentTok].symbol==")":
                printXml(tokenObjects[currentTok].printTok())
                currentTok+=1
            else:
                raise Exception("Missing )")
        indent-=1
        printXml("</term>")
        
    
    def compileSubroutine():
        global currentTok
        global indent
        global methodArguments
        local=0
        methodName=tokenObjects[currentTok].symbol
        printXml(tokenObjects[currentTok].printTok())
        currentTok+=1
        if tokenObjects[currentTok].symbol=="(":
            printXml(tokenObjects[currentTok].printTok())
            currentTok+=1
            vmInstructions.append("push pointer 0")
            numArgs=compileExpressionList()
            numArgs+=1
            demand(")")
            methodName=filehandle+"."+methodName
            if firstPass==False:
                vmInstructions.append("call "+methodName+" "+str(methodArguments[methodName][1]))
        else:
            varName=methodName
            method=tokenObjects[currentTok+1].symbol
            methodName=methodName+"."+tokenObjects[currentTok+1].symbol
            demand(".")
            if tokenObjects[currentTok].category=="identifier":
                printXml(tokenObjects[currentTok].printTok())
                currentTok+=1
                demand("(")
                for var in classScopeVariables:
                    if var.name==varName:
                        if var.kind=="field":
                            vmInstructions.append("push this "+str(var.number))    
                        elif var.kind=="static":
                            vmInstructions.append("push static "+str(var.number))
                        break            
                numArgs=compileExpressionList()
                
                found=False 
                for var in subroutineVariables:
                    if var.name==varName:
                        found=True
                        methodName=var.typeOf+"."+method
                        numArgs+=1
                        if var.kind=="argument":
                            vmInstructions.append("push argument "+str(var.number))
                        else:
                            vmInstructions.append("push local "+str(var.number))
                        if firstPass==False:
                            vmInstructions.append("call "+methodName+" "+str(methodArguments[methodName][1]))
                        break
                for var in classScopeVariables:
                    if var.name==varName:
                        found=True
                        if firstPass==False:
                            vmInstructions.append("call "+var.typeOf+"."+method+" "+str(methodArguments[methodName][1]+1))
                        break
                if found==False and methodName in methodArguments.keys():
                    vmInstructions.append("call "+methodName+" "+str(methodArguments[methodName][1]))
                
                
                demand(")")
            else:
                raise Exception("Missing method name")
        
        if firstPass:
            methodArguments[methodName]=[local,numArgs]   

    
    
    def compileExpressionList():
        global currentTok
        global indent
        printXml("<expressionList>")
        numArgs=0
        indent+=1
        continueLoop=True
        if tokenObjects[currentTok].symbol==")":
            continueLoop=False
        
        while continueLoop:
            compileExpression()
            numArgs+=1
            if tokenObjects[currentTok].symbol==",":
                printXml(tokenObjects[currentTok].printTok())
                currentTok+=1
            else:
                continueLoop=False
        indent-=1
        printXml("</expressionList>")
        return numArgs
        
    
    def compileStatement():
        global currentTok
        global indent
        printXml("<statements>")
        indent+=1
        while currentTok<len(tokenObjects) and tokenObjects[currentTok].symbol in statements: 
            if tokenObjects[currentTok].symbol=="let":
                compileLet()
            elif tokenObjects[currentTok].symbol=="while":
                compileWhile()
            elif tokenObjects[currentTok].symbol=="do":
                compileDo()
            elif tokenObjects[currentTok].symbol=="return":
                compileReturn()
            elif tokenObjects[currentTok].symbol=="if":
                compileIf()
        indent-=1
        printXml("</statements>")
        
    
    def compileIf():
        global indent
        global currentTok
        global vmInstructions
        global ifCounter
        printXml("<ifStatement>")
        indent+=1
        thisLabel=ifCounter
        demand("if")
        demand("(")
        compileExpression()
        
        vmInstructions.append("if-goto IF_TRUE"+str(ifCounter))
        vmInstructions.append("goto IF_FALSE"+str(ifCounter))
        vmInstructions.append("label IF_TRUE"+str(ifCounter))
        ifCounter+=1
        demand(")")
        demand("{")
        compileStatement()
        demand("}")
        
        vmInstructions.append("label IF_FALSE"+str(thisLabel))
        
        indent-=1
        printXml("</ifStatement>")
                 
        if tokenObjects[currentTok].symbol=="else":
            vmInstructions.pop()
            vmInstructions.append("goto IF_END"+str(thisLabel))
            vmInstructions.append("label IF_FALSE"+str(thisLabel))
            demand("else")
            demand("{")
            compileStatement()
            demand("}")
            vmInstructions.append("label IF_END"+str(thisLabel))
        
            
    def compileReturn():
        global indent
        global currentTok
        global vmInstructions
        printXml("<returnStatement>")
        indent+=1
        demand("return")
        if tokenObjects[currentTok].symbol!=";":
            compileExpression()
        else:
            vmInstructions.append("push constant 0")
        vmInstructions.append("return")
        demand(";")
        indent-=1
        printXml("</returnStatement>")
        
    
    def compileDo():
        global indent
        global currentTok
        global vmInstructions
        printXml("<doStatement>")
        indent+=1
        printXml(tokenObjects[currentTok].printTok())
        currentTok+=1
        compileSubroutine()
        demand(";")
        vmInstructions.append("pop temp 0")
        indent-=1
        printXml("</doStatement>")
        
    
    def compileWhile():
        global indent
        global currentTok
        global loopCounter
        global vmInstructions
        printXml("<whileStatement>")
        indent+=1
        printXml(tokenObjects[currentTok].printTok())
        currentTok+=1
        vmInstructions.append("label WHILE_EXP"+str(loopCounter))
        thisIt=loopCounter
        loopCounter+=1
        demand("(")
        compileExpression()
        vmInstructions.append("not")
        vmInstructions.append("if-goto WHILE_END"+str(thisIt))
        demand(")")
        demand("{")
        compileStatement()
        demand("}")
        vmInstructions.append("goto WHILE_EXP"+str(thisIt))
        vmInstructions.append("label WHILE_END"+str(thisIt))
        
        indent-=1
        printXml("</whileStatement>")
        
    
    
        
    def compileLet():
        global indent
        global currentTok
        global vmInstructions
        printXml("<letStatement>")
        indent+=1
        printXml(tokenObjects[currentTok].printTok())
        currentTok+=1
        var=tokenObjects[currentTok].symbol
        printXml(tokenObjects[currentTok].printTok())
        currentTok+=1
        bool=False
        if tokenObjects[currentTok].symbol=="[":
            bool=True
            printXml(tokenObjects[currentTok].printTok())
            currentTok+=1
            compileExpression()
            for var1 in subroutineVariables:
                if var==var1.name:
                    if var1.kind=="argument":
                        vmInstructions.append("push argument "+str(var1.number))
                    else:
                        vmInstructions.append("push local "+str(var1.number))
                    break
            for var1 in classScopeVariables:
                if var==var1.name:
                    if var.kind=="field":
                        vmInstructions.append("push this "+str(var1.number))
                    elif var.kind=="static":
                        vmInstructions.append("push static "+str(var.number))
                    break            
            
            
            if tokenObjects[currentTok].symbol=="]":
                printXml(tokenObjects[currentTok].printTok())
                currentTok+=1
            else:
                raise Exception("Missing ]")
            vmInstructions.append("add")
        if tokenObjects[currentTok].symbol=="=":
            printXml(tokenObjects[currentTok].printTok())
            currentTok+=1
        else:
            raise Exception("Missing =")
        
        if tokenObjects[currentTok+1].symbol==".":
            compileSubroutine()
        else:
            compileExpression()
        if tokenObjects[currentTok].symbol==";":
            printXml(tokenObjects[currentTok].printTok())
            currentTok+=1
        else:
            raise Exception("Missing ;")
        if bool:
            vmInstructions.append("pop temp 0")
            vmInstructions.append("pop pointer 1")
            vmInstructions.append("push temp 0")
            vmInstructions.append("pop that 0")
        else: 
            for variab in subroutineVariables:
                if variab.name==var:
                    if variab.kind=="argument":
                        vmInstructions.append("pop "+variab.kind+" "+str(variab.number))
                    else:
                        vmInstructions.append("pop local "+str(variab.number))
            for variab in classScopeVariables:
                if variab.name==var:
                    if variab.kind=="field":
                        vmInstructions.append("pop this "+str(variab.number))
                    elif variab.kind=="static":
                        vmInstructions.append("pop static "+str(variab.number))
                    break
        indent-=1
        printXml("</letStatement>")
        
        
    def compileClass():
        global indent
        global currentTok
        printXml("<class>")
        indent+=1
        demand("class")
        printXml(tokenObjects[currentTok].printTok())
        currentTok+=1
        demand("{")
        num=0
        static=0
        while currentTok<len(tokenObjects) and (tokenObjects[currentTok].symbol=="static" or tokenObjects[currentTok].symbol=="field"):
            [num1,static1]=compileClassVarDec(num, static)
            num+=num1
            static+=static1
        while currentTok<len(tokenObjects) and (compareCurrentTok("constructor") or compareCurrentTok("function") or compareCurrentTok("method")):
            compileSubroutineDec()     
        demand("}")
        indent-=1
        printXml("</class>")
        
    
    def compileSubroutineDec():
        global indent
        global currentTok
        global vmInstruction
        global firstPass
        global subroutineVariables
        global loopCounter
        global ifCounter
        loopCounter=0
        ifCounter=0
        subroutineVariables=[]
        printXml("<subroutineDec>")
        indent+=1
        methodType=tokenObjects[currentTok].symbol
        methodName=tokenObjects[currentTok+2].symbol
        bool=True
        if firstPass==False:
            vmInstructions.append("function "+filehandle+"."+methodName+" "+str(methodArguments[methodName][0]))
        if methodType=="constructor":
            counter=0
            for var in classScopeVariables:
                if var.kind=="field":
                    counter+=1
            vmInstructions.append("push constant "+str(counter/2))
            vmInstructions.append("call Memory.alloc 1")
            vmInstructions.append("pop pointer 0")
        elif methodType=="method":
            bool=False
            vmInstructions.append("push argument 0")
            vmInstructions.append("pop pointer 0")
        printCurrentTok()
        printCurrentTok()
        printCurrentTok()
        demand("(")
        args=compileParameterList(bool)
        demand(")")
        locVar=compileSubroutineBody()
        if methodType=="method":
            args+=1
        methodArguments[methodName]=[locVar,args]
        indent-=1
        printXml("</subroutineDec>")
    
    def compileParameterList(bool):
        global indent
        global currentTok
        global subroutineVariables
        printXml("<parameterList>")
        
        args=0
        indent+=1
        if bool:
            number=0
        else:
            number=1
        while compareCurrentTok(")")==False:
            args+=1
            kind="argument"
            typeOf=tokenObjects[currentTok].symbol
            name=tokenObjects[currentTok+1].symbol
            subroutineVariables.append(Variable(name,typeOf,kind,number))
            number+=1
            printCurrentTok()
            printCurrentTok()
            if compareCurrentTok(","):
                printCurrentTok()
        indent-=1
        printXml("</parameterList>")
        return args
        
    
    def compileSubroutineBody():
        global indent
        global currentTok
        printXml("<subroutineBody>")
        indent+=1    
        demand("{")
        numVar=0
        while compareCurrentTok("var"):
            numVar+=1
            numVar+=compileVarDec(numVar)
        while tokenObjects[currentTok].symbol in statements:
            compileStatement()
        demand("}")
        indent-=1
        printXml("</subroutineBody>")
        return numVar
        
    
    def compileVarDec(numVar):
        global indent
        global currentTok
        global subroutineVariables
        printXml("<varDec>")
        indent+=1  
        varAddtl=0
        kind=tokenObjects[currentTok].symbol
        typeOf=tokenObjects[currentTok+1].symbol
        name=tokenObjects[currentTok+2].symbol
        number=0
        subroutineVariables.append(Variable(name,typeOf,kind,numVar-1)) 
            
        printCurrentTok()
        printCurrentTok()
        printCurrentTok()
        while compareCurrentTok(";")==False:
            varAddtl+=1
            numVar+=1 
            number+=1
            name=tokenObjects[currentTok+1].symbol
            subroutineVariables.append(Variable(name,typeOf,kind,numVar-1))  
            printCurrentTok()
            printCurrentTok()
        demand(";")
        indent-=1
        printXml("</varDec>")
        return varAddtl
        
        
    
    def printCurrentTok():
        global currentTok
        printXml(tokenObjects[currentTok].printTok())
        currentTok+=1
    
    def compareCurrentTok(s):
        global currentTok
        if tokenObjects[currentTok].symbol==s:
            return True
        else:
            return False
        
    def compileClassVarDec(num, stat):
        global indent
        global currentTok
        global classScopeVariables
        printXml("<classVarDec>")
        indent+=1
        kind=tokenObjects[currentTok].symbol;
        typeOf=tokenObjects[currentTok+1].symbol;
        name=tokenObjects[currentTok+2].symbol;
        number=0
        static=0
        boolStat=True
        if kind=="static":
            classScopeVariables.append(Variable(name,typeOf,kind,stat))
            static+=1
            stat+=1
        else:
            boolStat=False
            classScopeVariables.append(Variable(name,typeOf,kind,num))
            number+=1
            num+=1
        printCurrentTok()
        printCurrentTok()
        printCurrentTok()
        
        while compareCurrentTok(","):
            
            name=tokenObjects[currentTok+1].symbol
            if boolStat:
                classScopeVariables.append(Variable(name,typeOf,kind,stat))
                static+=1
                stat+=1
            else:
                classScopeVariables.append(Variable(name,typeOf,kind,num))
                num+=1
                number+=1
            printCurrentTok()
            printCurrentTok()
        
        demand(";")
        indent-=1
        printXml("</classVarDec>")
        return [number, static]
                 
   
    loopCounter=0
    ifCounter=0
    vmInstructions=[]    
    methodArguments={}
    firstPass=True    
    classScopeVariables=[]
    compileClass()
    print methodArguments.keys()
    for var in classScopeVariables:
        print var.name +" "+var.kind+" "+var.typeOf+" "+str(var.number)
    firstPass=False
    vmInstructions=[]
    subroutineVariables=[]
    currentTok=0
    indent=0
    compileClass()
    f=open(filehandle+".vm","w")
    print vmInstructions
    for line in vmInstructions:
        f.write(line+"\n")
    f.close()