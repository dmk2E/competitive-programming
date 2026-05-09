/*アルゴリズムと工夫点(All Free/CPU: 1 ms Memory: 3908 KB  Length: 696 B)
買うことのできる商品の集合をビットで管理するbitDPで解ける．
dp[i][j]:1～i+1番目までのクーポン券を使うことで，集合jに含まれる商品を買うことができる最小のクーポンの使用枚数
とする動的計画法で解ける．
最悪計算量は，O(M*2^(N))<10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j,k;
    scanf("%d%d",&n,&m);
    vector<int> voucher(m,0);
    rep(i,m){
        rep(j,n){
            scanf("%d",&k);
            voucher[i]*=2;
            voucher[i]+=(k==1);
        }
    }
    const int INF=m+1;
    vector<int> last(1<<n,INF);
    last[0]=0;
    rep(i,m){
        vector<int> now=last;
        rep(j,1<<n)now[j|voucher[i]]=min(last[j]+1,now[j|voucher[i]]);
        swap(last,now);
    }
    printf("%d\n",last[(1<<n)-1]==INF?-1:last[(1<<n)-1]);
    return 0;
}