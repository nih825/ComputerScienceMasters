include <iostream>
using namespace std;
int main()
{
    for(int x=0;x<=8;x++)
    {
        int num=1;
        for(int y=0;y<=x;y++)
        {
            cout << num;
            cout<<" ";
            num= num * (x-y) / (y+1);
        }
        cout << endl;
    }
    return 0;
}
