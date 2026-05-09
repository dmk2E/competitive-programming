/*アルゴリズムと工夫点(88888888/CPU: 1 ms Memory: 3856 KB  Length: 1005 B)
VN=N*(10^(k*N)-1)/(10^k -1) となるから，逆元の知識があれば解ける．が，unsigned long longの最大値を勘違いしていたり，積の途中でオーバーフローしていることに気づけず，解けなかった...悔しすぎる．
※そのため，hand_00.txtのn=1000000000000000000 のテストケースだけ上手くいかなかった...悔しい
※unsigned long long の最大値は1.8*10^19 であることに注意．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MOD 998244353
using namespace std;

long long n;

int rrep(unsigned long long x,unsigned long long a){
    unsigned long long sum=(unsigned long long)1;
    if(a==0)
        return 1;
    sum=((sum%MOD)*(rrep(((x%MOD)*(x%MOD))%MOD,a/2)%MOD))%MOD;
    if(a%2==1)
        sum=(sum*(x%MOD))%MOD;
    return sum;
}

long long rrrep(long long x,long long a){
    long long sum=(long long)1;
    if(a==0)
        return 1;
    sum*=rrep(x*x,a/2);
    if(a%2==1)
        sum=sum*x;
    return sum;
}

int count10(long long n){
    int i=0;
    unsigned long long now=1;
    while(now<=n){now*=10;i++;}
    return i-1;
}

int main(){
    int i,k;
    scanf("%lld",&n);
    k=count10(n)+1;
    //printf("%llu\n",(unsigned long long)k*n);
    printf("%d\n",(int)(((n%MOD)*(((((long long)rrep(rrep(10,n),k)%MOD-1+MOD)%MOD)*((long long)rrep((rrrep(10,k)%MOD-1+MOD)%MOD,MOD-2)%MOD))%MOD))%MOD));
    return 0;
}