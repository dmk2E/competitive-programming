/*アルゴリズムと工夫点(Subarray Sum Divisibility/CPU: 217 ms Memory: 4852 KB  Length: 809 B)
動的計画法で解く．
以下の2つの条件を満たすまでの，最小操作回数を求めればよい．
・Ai = Ai+l (mod m)
・A[0,l)の総和 = 0 (mod m)
lで割った余りの値の添え字のグループiごとに，どの値を割り当てるかを順に決めていけばよく，
dp[i][j] = (グループiの値まで決めた時，総和がj (mod M)である時の最小操作回数)
という動的計画法を解けばよい．
最悪計算量は，O(N*M^(2)) < 10^8 
※ 区間和=>一旦累積和で考察してもよいかも
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

template<typename T>
void chMin(T& a,T b){a=min(a,b);}

int n,m,l;

int main(){
    int i,j,k;
    scanf("%d%d%d",&n,&m,&l);
    vector<int> a(n);
    rep(i,n){
        scanf("%d",&a[i]);
        a[i]%=m;
    }
    vector<vector<int> > count(l,vector<int>(m,0));
    rep(i,n){
        int g=i%l;
        rep(j,m)count[g][j]+=(j-a[i]+m)%m;
    }
    const int INF=(1e9);
    vector<int> dp(m,INF);
    dp[0]=0;
    rep(i,l){
        vector<int> nxt(m,INF);
        rep(j,m)if(dp[j]!=INF)rep(k,m)chMin(nxt[(j+k)%m],dp[j]+count[i][k]);
        swap(dp,nxt);
    }
    printf("%d\n",dp[0]);
    return 0;
}