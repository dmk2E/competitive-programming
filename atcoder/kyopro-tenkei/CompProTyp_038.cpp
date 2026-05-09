/*アルゴリズムと工夫点(Large LCM/CPU: 1 ms Memory: 3892 KB  Length: 408 B)
浮動小数点が出てくるのを防ぐためだけでなく，型のオーバーフローを避けるためにも，不等式の式変形は行われる．
*/
#include<iostream>
#include<cmath>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define POW18 (long long)(1e18)
using namespace std;

long long a,b;

long long gcd(long long a,long long b){
    return b==0?a:gcd(b,a%b);
}

int main(){
    scanf("%lld%lld",&a,&b);
    if(a/gcd(a,b)<=POW18/b)
        printf("%lld\n",a<b?b/gcd(a,b)*a:a/gcd(a,b)*b);
    else
        puts("Large");
    return 0;
}
/*2WAver:浮動小数点数が絡むせいで，正常に動作してくれなかった...
#include<iostream>
#include<cmath>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define EPS (1e-18)
#define EEPS (1e-10)
using namespace std;

typedef pair<int,double> p;

long long a,b;

long long gcd(long long a,long long b){
    return b==0?a:gcd(b,a%b);
}

p value2Ten(long long x){
    int i=0;
    long long ten=1;
    while(ten<=x&&i<=18){i++;if(i<19)ten*=10;}
    if(i<19)ten/=10;
    return p(i-1,(double)x/ten);
}

bool judge(p a,p b,p g){
    int ten=a.first+b.first-g.first;
    double base=a.second*b.second/g.second;
    printf("%d %d\n",base>10?1:0,base-10>EPS&&fabs(base-10)<EEPS?1:0);
    while(base>10.0||(base-10>EPS&&fabs(base-10)<EEPS)){
        ten++;
        base/=10;
    }
    printf("base:%f,ten:%d\n",base,ten);
    return ten>18?false:ten==18?fabs(base-1)<EPS:true;
}

int main(){
    p aa,bb,g;
    scanf("%lld%lld",&a,&b);
    aa=value2Ten(a);bb=value2Ten(b);
    g=value2Ten(gcd(a,b));
    if(judge(aa,bb,g))
        printf("%lld\n",a<b?b/gcd(a,b)*a:a/gcd(a,b)*b);
    else
        puts("Large");
    return 0;
}
*/