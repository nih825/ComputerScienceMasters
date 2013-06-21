#include <stdio.h>
#include <math.h>
void floatbit(float x ){
    int bit,totalbits,bitsymbol,mask;
    char* bit_pattern;
    int byteindex;
    
    totalbits=sizeof(x)*8-1;
    for(bit=totalbits;bit>= 0;bit--)
    {
        bit_pattern = (char*)&x ;
        byteindex = bit/8 ;
        mask = 0x01 << (bit%8) ;
        if((bit_pattern[byteindex]&mask)==0){
            bitsymbol=0;
        }
        else bitsymbol=1;
        /*print bitsymbol*/
        printf("%d ",bitsymbol);
    }
    printf("\n");
}

int main(int argc,char* argv[]){
  float a,b,c;
    a = pow(2,24);
    c = pow(2,24) + 1;
    b = pow(2,24) + 2;
    floatbit(a);
    floatbit(b);
    floatbit(c);
    return 0;
}
