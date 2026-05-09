/*アルゴリズムと工夫点(ABC Transform/CPU: 43 ms Memory: 4024 KB  Length: 744 B)
文字列などにN回の何らかの処理を施すことで，その大きさが2^(N)倍になる場合，文字列の変化を完全二分木に当てはめると考察がしやすくなることがある．
処理を1回も加えていない初期状態を，二分木の葉や根に割り当てて考えることが多い．
※完全二分木の重要な性質として，左側の葉から順番に0-indexで番号を振っていくと，2進数表記で(`0'の数)=(節点から左の子に進んだ回数),('1'の数)=(接点から右の子に進んだ回数) となる
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s;
int q;
ll t,k;

int main(){
    int i,j;
    const int MAX=60;
    vector<ll> pow2(MAX+1);
    pow2[0]=1;
    rep(i,MAX)pow2[i+1]=2*pow2[i];
    cin>>s;
    scanf("%d",&q);
    while(q--){
        scanf("%lld%lld",&t,&k);
        k--;
        i=0;
        if(t<=MAX){
            i=k/pow2[t];
            k%=pow2[t];
        }
        i=(int)s[i]-(int)'A';
        j=0;
        while(k>0){
            j+=k&1;
            k>>=1;
        }
        i=(i%3+2*(j%3)+(3+t%3-j%3)%3)%3;
        printf("%c\n",(char)(i+(int)'A'));
    }
    return 0;
}