#include<stdio.h>
int main(){
     float fout;
    for(int i=0; i<9000; i++)
    {
    fout = 8000000.0 / ((7999 + 1)*(i + 1)); //ARR = 124 // PSC = 63999
    printf("for i = %d, fout = %f\n",i,fout);
    } //arr = 999 //psc = 7999
}
