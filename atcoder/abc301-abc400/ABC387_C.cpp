/*アルゴリズムと工夫点(Snake Numbers/CPU: 1 ms Memory: 3872 KB  Length: 889 B)
L以上R以下の蛇数を数え上げる際，f(R)=(R以下の蛇数の総数)とし，f(R)-f(L-1)の形にすると楽．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll l,r;

ll power(ll x,int a){
    if(a==0)return 1;
    ll ans=power(x*x,a/2);
    if(a%2==1)ans*=x;
    return ans;
}

ll f(ll r){
    int i,j,k;
    ll ans=0;
    string rs=to_string(r);
    if(r<10)return 0;
    for(i=2;i<rs.size();i++)for(j=1;j<=9;j++)ans+=power(j,i-1);
    for(j=1;j<rs[0]-'0';j++)ans+=power(j,i-1);
    i--;
    for(k=1;k<rs.size();k++){
        if(rs[k]-'0'>=rs[0]-'0'){
            ans+=power(rs[0]-'0',i);
            break;
        }
        ans+=power(rs[0]-'0',i-1)*(rs[k]-'0');
        i--;
    }
    ans+=(k==rs.size());
    return ans;
}

int main(){
    int i;
    scanf("%lld%lld",&l,&r);
    //printf("%lld %lld\n",f(l),f(r));
    printf("%lld\n",f(r)-f(l-1));
    return 0;
}