#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<functional>
using namespace std;

struct maxlenftn {
	maxlenftn() { maxlen = 0; }
    void operator()(string s) {
		maxlen = max(maxlen,s.size());
	}
	string::size_type maxlen;
};

char const *na[] = {
    "Spertus", "Lemon", "Golden", "Melhus"
};

void wrong() {
	vector<string> names(na, na + sizeof(na)/sizeof(const char *));
	maxlenftn maxf;
	for_each(names.begin(),names.end(),maxf);
	cout << maxf.maxlen << endl;
}

void better() {
	vector<string> names(na, na + sizeof(na)/sizeof(const char *));
	maxlenftn maxf;
	for_each(names.begin(),names.end(), ref(maxf));
	cout << maxf.maxlen << endl;
}

void best() {
	vector<string> names(na, na + sizeof(na)/sizeof(const char *));
	maxlenftn maxf;
	maxf = for_each(names.begin(),names.end(),maxf);
	cout << maxf.maxlen << endl;
}

struct maxlenftn2 {
	maxlenftn2() { maxlen = 0; }
    void operator()(string s) {
		maxlen = max(maxlen,s.size());
	}
	static string::size_type maxlen;
};

string::size_type maxlenftn2::maxlen;

void bad() {
	vector<string> names(na, na + sizeof(na)/sizeof(const char *));
	maxlenftn2 maxf;
	maxf = for_each(names.begin(),names.end(),maxf);
	cout << maxf.maxlen << endl;
}

int main()
{
  wrong();
  bad();
  better();
  best();
  return 0;
}