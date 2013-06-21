
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

//Saffir-Simpson
//Category	Maximum sustained wind speed
//mph	m/s	kts
//1	74-95	33-42	64-82
//2	96-110	43-49	83-95
//3	111-130	50-58	96-113
//4	131-155	59-69	114-135
//5	156+	70+	    136+


vector<string> tokenize(string s) {
	istringstream iss(s);
	vector<string> tokens;
	copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter<vector<string> >(tokens));
	return tokens;
}

int getYear(string yearToken){
    return atoi(yearToken.substr(yearToken.length()-4).c_str());
}

int getKnots(vector<string> line){
    //3,6,9,12
    int knotsum=atoi(line[3].c_str())+atoi(line[6].c_str())+atoi(line[9].c_str())+atoi(line[12].c_str());
    double knotsum1=(double)knotsum/4;
    if(knotsum1>=64&&knotsum1<=82)
       return 1;
    else if(knotsum1>=83&&knotsum1<=95)
        return 2;
    else if(knotsum1>=96&&knotsum1<=113)
        return 3;
    else if(knotsum1>=114&&knotsum1<=135)
        return 4;
    else if(knotsum1>=136)
        return 5;
    else
        return 0;
}

int main(void){
    // columns 3,6,9,12
    vector<int> yearly(161);
    for(int i=0; i<yearly.size(); i++){
        yearly[i]=0;
    }
    string currentLine;
    vector<string> lines;
    vector<int> magnitude;
    ifstream in;
    string filename="data.txt";
	in.open(filename.c_str());
    if (in.is_open()) {
    while(in.good()) {
        getline(in, currentLine);
        lines.push_back(currentLine);
    }
    }
    in.close();
    int currentYear=1851;
    for(int i=0; i<lines.size(); i++){
        string line=lines[i];
        vector<string> tokenized=tokenize(lines[i]);
        if(tokenized.size()>=3 && tokenized[2][0]=='M'&&tokenized[2][1]=='='){
            currentYear=getYear(tokenized[1]);
        }
        else if(tokenized.size()>=13){
            int scale=getKnots(tokenized);
            yearly[currentYear-1851]+=scale;
            
        }
    }
    for(int i=0; i< yearly.size(); i++){
        cout<<1851+i<<"   "<<yearly[i]<<endl;
    }
    
	return 0;
    
    
}