/*アルゴリズムと工夫点(Ideal Holidays/CPU: 30 ms Memory: 4516 KB  Length: 541 B)
「ある範囲Aに複数の点を収めることが可能か」は「ある範囲A'に複数の点を収めないことは可能か」と同値であり、「これは隣り合う2点間にA'をはめることは可能か」と言い換えることができる。
最悪計算量は、O(N*log2(N))≒10^6 となり、十分高速。
*/
#include<iostream>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 200000
using namespace std;

int n,a,b,d[MAX_N];

bool judge(){
    int i,j;
    rep(i,n-1)
        if(d[i+1]-d[i]-1>=b)
            return true;
    if(d[0]+a+b-d[i]-1>=b)
        return true;
    return false;
}

int main(){
    int i,j;
    scanf("%d%d%d",&n,&a,&b);
    rep(i,n){
        scanf("%d",&j);
        j--;
        d[i]=j%(a+b);
    }
    sort(d,d+n);
    printf("%s\n",judge()?"Yes":"No");
    return 0;
}