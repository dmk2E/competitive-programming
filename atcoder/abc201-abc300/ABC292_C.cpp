/*アルゴリズムと工夫点(Four Variables/CPU: 3 ms Memory: 4648 KB  Length: 582 B)
A,B,C,Dはそれぞれ独立で考えることができる．そこで，まず ccnt[x]:x=A*B となる(A,B)の組の数 として，ccntを求める．
ここで，N=AB+CD>AB A<Bとすると，N>A^2 よって A<√N となる．したがって，1<=A<=√N とし，数えあげる．この時，最悪計算量はO(N√N)となる．
ccntが求まれば，後はO(N)で解を導ける．よって，全体の最悪計算量はO(N√N)<10^8 となり，高速．実際は，途中で処理を終了するため，より高速に動作する．
*/
#include<iostream>
#include<cmath>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N (int)(2e5)
using namespace std;

int n,ccnt[MAX_N+1]={0};

int main(){
    int i,j,k,l,maxI,maxK;
    long long cnt=0,temp;
    scanf("%d",&n);
    maxI=sqrt(n)+1;
    for(i=1;i<maxI;i++){
        for(j=1;j<n;j++){
            if(i*j>=n)
                break;
            if(j<maxI)
                ccnt[i*j]+=1;
            else
                ccnt[i*j]+=2;
        }
    }
    for(i=1;i<n;i++)
        cnt+=(long long)ccnt[i]*ccnt[n-i];
    printf("%lld\n",cnt);
}