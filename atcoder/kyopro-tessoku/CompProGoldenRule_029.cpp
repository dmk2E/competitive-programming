/*アルゴリズムと工夫点(Power/CPU: 2 ms Memory: 3832 KB  Length: 412 B)
繰り返し自乗法は応用範囲が広いので覚えておこう．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MOD ((int)(1e9)+7)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int a,b;

ll power(ll a,ll b){
    if(b==0)return 1;
    ll res=power((a%MOD)*(a%MOD),b/2);
    if(b%2==1)res=res*(a%MOD);
    return res%MOD;
}

int main(){
    scanf("%d%d",&a,&b);
    printf("%lld\n",power(a,b));
    return 0;
}