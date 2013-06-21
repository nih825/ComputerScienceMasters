//
//  Pascal.cpp
//  HW2
//
//  Created by Rukmaiah Bhupalam on 1/19/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//

#include <vector>
#include <numeric>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
using namespace std;



class TriangleClass{
    typedef vector<int> Row;
    typedef vector<Row> Triangle;

public:
    int size;
    Triangle triangle;
    
    void initializeTriangle(int n){
        size=n;
        Row previousRow;
        previousRow.push_back(1);
        for(int i = 0; i < size; i++) {
            triangle.push_back(previousRow);
            previousRow = nextRow(previousRow);
        }
    }
    

Row
nextRow(Row row)
{
    Row result;
    int previous = 0;
    for (auto it = row.begin(); it != row.end(); it++) {
        result.push_back(previous + *it);
        previous = *it;
    }
    result.push_back(previous);
    return result;
}



int
numDigits(int i)
{
    int digits = 1;
    while((i/=10) != 0) {
        digits++;
    }
    return digits;
}

int
numDigits_alternate(int i)
{
	ostringstream os;
	os << i;
	return os.str().size();
}

int eltSize;

string
centeredInt(int i)
{
    ostringstream os;
    os << i;
    string str = os.str();
    return string((eltSize - str.size())/2, ' ') + str;
}

void
printRow(Row row)
{
    for(auto it = row.begin(); it != row.end(); it++) {
        cout << left << setw(eltSize) << centeredInt(*it) << " ";
    }
    cout << endl;
}

void
printTriangle()
{
    Row lastRow = triangle[size - 1];
    // g++ doesn't like the following code because it defines extra std::max functions
    // It's actually surprising the Visual C++ accepts it
    //
    // int maxElement = accumulate(lastRow.begin(), lastRow.end(), 0, max<int>);
    //
    // use this instead
    int maxElement = *max_element(lastRow.begin(), lastRow.end());
    eltSize = numDigits(maxElement);
    for(int i = 0; i < size; i++) {
        string spaces((size - i - 1) * (eltSize + 1) / 2, ' ');
        cout << spaces;
        printRow(triangle[i]);
    }
}
};

int
main()
{
    TriangleClass triangle;
    triangle.initializeTriangle(8);
    triangle.printTriangle();
    return 0;
}