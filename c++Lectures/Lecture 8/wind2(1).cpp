#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stdexcept>

using namespace std;
enum UsefulConstants {
  maxline = 1000
};
ofstream output("output.txt");

template<class T1, class T2>
T2 second(pair<T1, T2> &p) {
    return p.second;
}

int
knotsToSaffirSimpson(int knots)
{
    if(knots < 64) {
        return 0;
    }
    if(knots < 83) {
        return 1;
    }
    if(knots < 96) {
        return 2;
    }
    if(knots < 114) {
        return 3;
    }
    if(knots < 136) {
        return 4;
    }
    return 5;
}

class YearEntry {
public:
    YearEntry() : ssDays(0) {}
    void addKnots(string str) {
        istringstream asStream(str);
        int num;
        asStream >> num;
        ssDays += knotsToSaffirSimpson(num)/4.0;
    }
    double ssDays;
};

void 
print_year(pair<int, YearEntry> year_entry_pair) 
{
    output << year_entry_pair.first << ", " << year_entry_pair.second.ssDays << endl;
}
int main()
{
    int first_year = numeric_limits<int>::max();
    int last_year = 0;
    map<int, YearEntry > ssMap;
    string line;
    YearEntry *currentYearEntry = 0;
    ifstream tracks(".\\tracks.txt");
    smatch what;
    regex headerRegex("(?:\\d{2}/){2}(\\d{4})");
	regex dayRegex(".{11}[*].{7}\\s+(\\d+).{13}\\s+(\\d+).{13}\\s+(\\d+).{13}\\s+(\\d+).*");
    while(getline(tracks, line)) {
        if(regex_search(line, what, headerRegex)) {
			cout << line;  // just so we can see progress...
            int currentYear;
            istringstream yearstream(what[1].str());
            yearstream >> currentYear;
            first_year = min(first_year, currentYear);
            last_year = max(last_year, currentYear);
            currentYearEntry = &ssMap[currentYear];
            continue;
        } else if ( regex_search( line, what, dayRegex ) ) {
			currentYearEntry->addKnots(what[1]);
			currentYearEntry->addKnots(what[2]);
			currentYearEntry->addKnots(what[3]);
			currentYearEntry->addKnots(what[4]);
		}
    }
    for(int i = first_year; i <= last_year; i++) {
        ssMap[i];
    }
    for_each(ssMap.begin(), ssMap.end(), print_year);
}
