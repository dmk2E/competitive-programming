/*アルゴリズムと工夫点(XNOR Operation/CPU: 4 ms Memory: 4048 KB  Length: 497 B)
累積和を利用して解く．
0の個数という不変量に着目して解くことができ，最悪計算量は，O(N)<10^6 となり十分高速．
※「どのように操作しても結果は変わらない」という所までは考察できていた。
※ XORの性質から考えて，「0の個数の偶奇」に着目することがポイントだった...
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
string t;

int main(){
    int i,j,last_sum=0,sum_to_cnt[2]={1,0};
    ll ans=0;
    scanf("%d",&n);
    cin>>t;
    rep(i,n){
        int now=((t[i]=='0')+last_sum)%2;
        ans+=sum_to_cnt[now];
        sum_to_cnt[now]++;
        last_sum=now;
    }
    printf("%lld\n",ans);
    return 0;
}