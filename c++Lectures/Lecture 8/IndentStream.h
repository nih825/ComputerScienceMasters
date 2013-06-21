#ifndef INDENT_STREAM_H
#define INDENT_STREAM_H

#include <streambuf>
#include <iostream>

using std::ostream;
using std::streambuf;

namespace cspp51044 {

using std::ostream;
using std::streambuf;
using std::cout;
using std::cin;
using std::endl;

class IndentStreamBuf : public streambuf
{
public:
    IndentStreamBuf(ostream &stream)
        : wrappedStream(stream), isLineStart(true), myIndent(0) {}
	virtual int overflow(int outputVal)
	{
        if(outputVal == '\n') {
            isLineStart = true;
        } else if(isLineStart) {
            for(size_t i = 0; i < myIndent; i++) {
               wrappedStream << ' ';
            }
            isLineStart = false;
        }
        wrappedStream << static_cast<char>(outputVal);
		return outputVal;
	}
protected:
    ostream &wrappedStream;
    bool isLineStart;
public:
    size_t myIndent;
};

class IndentStream : public ostream
{
public:
    IndentStream(ostream &wrappedStream)
      : ostream(new IndentStreamBuf(wrappedStream)) {
    }
    ~IndentStream() { delete this->rdbuf(); }
protected:
    IndentStreamBuf *indentStreambuf;
};


ostream &indent(ostream &ostr);

ostream &unindent(ostream &ostr);

}
#endif
