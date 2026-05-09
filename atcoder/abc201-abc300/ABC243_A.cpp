/*アルゴリズムと工夫点(Shampoo/CPU: 1 ms Memory: 3900 KB  Length: 348 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int v,a,b,c;

int main(){
    scanf("%d%d%d%d",&v,&a,&b,&c);
    v%=(a+b+c);
    if(v<a)puts("F");
    else{
        v-=a;
        if(v<b)puts("M");
        else puts("T");
    }
    return 0;
}