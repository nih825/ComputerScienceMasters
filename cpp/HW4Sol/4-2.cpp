//
//  4-2.cpp
//  HW4
//
//  Created by Rukmaiah Bhupalam on 2/1/13.
//  Copyright (c) 2013 Nihar Bhupalam. All rights reserved.
//
using namespace std;
#include <iostream>
int main()
{
    int i;
    int *ip = new int[10];
    delete [] ip;
    cout<<"I removed the first deletion as delete should only be used for pointers there is no need to delete i.  The delete of ip needs to be changed to include the bracket as the memory was dynamically allocated";
}