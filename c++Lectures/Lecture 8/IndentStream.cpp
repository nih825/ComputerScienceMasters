#include "IndentStream.h"

using std::cout;
using std::endl;

namespace cspp51044 {
ostream &indent(ostream &ostr)
{
    IndentStreamBuf *out = dynamic_cast<IndentStreamBuf *>(ostr.rdbuf());
    if(0 != out) {
        out->myIndent += 4;
    }
    return ostr;
}

ostream &unindent(ostream &ostr)
{
    IndentStreamBuf *out = dynamic_cast<IndentStreamBuf *>(ostr.rdbuf());
    out->myIndent -= 4;
    return ostr;
}
}


int main()
{
    cspp51044::IndentStream is(cout);
	is << 5 << endl;
	is << 5 << endl;
	is << 5 << endl;
	is << 5 << endl;
	is << cspp51044::indent;
	is << 5 << endl;
	is << 5 << endl;
	is << 5 << endl;
	is << 5;
//	cout << "31 hexadecimal: "
//    << std::hex << 31 << std::endl;
	return 0;
}


