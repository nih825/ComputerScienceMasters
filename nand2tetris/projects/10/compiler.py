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
    
    op=['+','-','*','/','&','|','<','>','=']
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
    for tok in tokenObjects:
        print tok.printTok()
    
    print totalFile
    print len(tokenObjects)
    
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
            printXml(tokenObjects[currentTok].printTok())
            currentTok+=1
            compileTerm()
        indent-=1
        printXml("</expression>")
        
    
    def compileTerm():
        global currentTok
        global indent
        printXml("<term>")
        indent+=1
        category=tokenObjects[currentTok].category
        if category=="integerConstant" or category=="StringConstant":
            printXml(tokenObjects[currentTok].printTok())
            currentTok+=1
        elif category=="keyword" and tokenObjects[currentTok].symbol in KeywordConstant:
            printXml(tokenObjects[currentTok].printTok())
            currentTok+=1
        elif tokenObjects[currentTok].symbol in unaryOp:
            printXml(tokenObjects[currentTok].printTok())
            currentTok+=1
            compileTerm()
        elif category=="identifier":
            nextTok=tokenObjects[currentTok+1]
            if nextTok.symbol=='[':
                printXml(tokenObjects[currentTok].printTok())
                printXml(nextTok.printTok())
                currentTok+=2
                compileExpression()
                if tokenObjects[currentTok].symbol==']':
                    printXml(tokenObjects[currentTok].printTok())
                    currentTok+=1
                else:
                    raise Exception("Missing ]")
            elif nextTok.symbol=="(" or nextTok.symbol==".":
                    print "got here"
                    compileSubroutine()
            else:
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
        printXml(tokenObjects[currentTok].printTok())
        currentTok+=1
        if tokenObjects[currentTok].symbol=="(":
            printXml(tokenObjects[currentTok].printTok())
            currentTok+=1
            compileExpressionList()
            demand(")")
        else:
            demand(".")
            print xml
            if tokenObjects[currentTok].category=="identifier":
                printXml(tokenObjects[currentTok].printTok())
                currentTok+=1
                demand("(")
                compileExpressionList()
                demand(")")
            else:
                raise Exception("Missing method name")
            
    
    
    def compileExpressionList():
        global currentTok
        global indent
        printXml("<expressionList>")
        indent+=1
        continueLoop=True
        if tokenObjects[currentTok].symbol==")":
            continueLoop=False
        
        while continueLoop:
            compileExpression()
            print tokenObjects[currentTok].category
            if tokenObjects[currentTok].symbol==",":
                printXml(tokenObjects[currentTok].printTok())
                currentTok+=1
            else:
                continueLoop=False
        indent-=1
        printXml("</expressionList>")
        
    
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
        printXml("<ifStatement>")
        indent+=1
        demand("if")
        demand("(")
        compileExpression()
        demand(")")
        demand("{")
        compileStatement()
        demand("}")
        indent-=1
        printXml("</ifStatement>")
                 
        if tokenObjects[currentTok].symbol=="else":
            demand("else")
            demand("{")
            compileStatement()
            demand("}")
            
    def compileReturn():
        global indent
        global currentTok
        printXml("<returnStatement>")
        indent+=1
        demand("return")
        if tokenObjects[currentTok].symbol!=";":
            compileExpression()
        print xml
        demand(";")
        indent-=1
        printXml("</returnStatement>")
        
    
    def compileDo():
        global indent
        global currentTok
        printXml("<doStatement>")
        indent+=1
        printXml(tokenObjects[currentTok].printTok())
        currentTok+=1
        compileSubroutine()
        demand(";")
        indent-=1
        printXml("</doStatement>")
        
    
    def compileWhile():
        global indent
        global currentTok
        printXml("<whileStatement>")
        indent+=1
        printXml(tokenObjects[currentTok].printTok())
        currentTok+=1
        demand("(")
        compileExpression()
        
        demand(")")
        demand("{")
        compileStatement()
        print xml
        demand("}")
        indent-=1
        printXml("</whileStatement>")
        
    
    
        
    def compileLet():
        global indent
        global currentTok
        printXml("<letStatement>")
        indent+=1
        printXml(tokenObjects[currentTok].printTok())
        currentTok+=1
        printXml(tokenObjects[currentTok].printTok())
        currentTok+=1
        
        if tokenObjects[currentTok].symbol=="[":
            printXml(tokenObjects[currentTok].printTok())
            currentTok+=1
            compileExpression()
            if tokenObjects[currentTok].symbol=="]":
                printXml(tokenObjects[currentTok].printTok())
                currentTok+=1
            else:
                raise Exception("Missing ]")
        if tokenObjects[currentTok].symbol=="=":
            printXml(tokenObjects[currentTok].printTok())
            currentTok+=1
        else:
            raise Exception("Missing =")
        compileExpression()
        if tokenObjects[currentTok].symbol==";":
            printXml(tokenObjects[currentTok].printTok())
            currentTok+=1
        else:
            raise Exception("Missing ;")
        indent-=1
        printXml("</letStatement>")
        
        
    def compileClass():
        global indent
        global currentTok
        printXml("<class>")
        indent+=1
        demand("class")
        classname=tokenObjects[currentTok].symbol
        printXml(tokenObjects[currentTok].printTok())
        currentTok+=1
        demand("{")
        while currentTok<len(tokenObjects) and (tokenObjects[currentTok].symbol=="static" or tokenObjects[currentTok].symbol=="field"):
            compileClassVarDec()
        while currentTok<len(tokenObjects) and (compareCurrentTok("constructor") or compareCurrentTok("function") or compareCurrentTok("method")):
            compileSubroutineDec()     
        demand("}")
        indent-=1
        printXml("</class>")
        
    
    def compileSubroutineDec():
        global indent
        global currentTok
        printXml("<subroutineDec>")
        indent+=1
        printCurrentTok()
        printCurrentTok()
        printCurrentTok()
        demand("(")
        compileParameterList()
        demand(")")
        compileSubroutineBody()
        indent-=1
        printXml("</subroutineDec>")
        
    
    def compileParameterList():
        global indent
        global currentTok
        printXml("<parameterList>")
        indent+=1
        while compareCurrentTok(")")==False:
            printCurrentTok()
            printCurrentTok()
            if compareCurrentTok(","):
                printCurrentTok()
        indent-=1
        printXml("</parameterList>")
        
    
    def compileSubroutineBody():
        global indent
        global currentTok
        printXml("<subroutineBody>")
        indent+=1    
        demand("{")
        while compareCurrentTok("var"):
            compileVarDec()
        while tokenObjects[currentTok].symbol in statements:
            compileStatement()
        demand("}")
        indent-=1
        printXml("</subroutineBody>")
        
    
    def compileVarDec():
        global indent
        global currentTok
        printXml("<varDec>")
        indent+=1        
        printCurrentTok()
        printCurrentTok()
        printCurrentTok()
        while compareCurrentTok(";")==False:
            printCurrentTok()
            printCurrentTok()
        demand(";")
        indent-=1
        printXml("</varDec>")
        
        
    
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
        
    def compileClassVarDec():
        global indent
        global currentTok
        printXml("<classVarDec>")
        indent+=1
        printCurrentTok()
        printCurrentTok()
        printCurrentTok()
       
        while compareCurrentTok(","):
            
            printCurrentTok()
            printCurrentTok()
        
        demand(";")
        indent-=1
        printXml("</classVarDec>")
                 
        
         
    compileClass()
    print xml
    outputFile=filehandle+".xml"
    f=open(outputFile,"w")
    for line in xml:
        f.write(line+"\n")
    f.close()
