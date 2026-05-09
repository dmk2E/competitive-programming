/*アルゴリズムと工夫点(Count Sequences 2/CPU: 271 ms Memory: 101588 KB  Length: 949 B)
パスカルの三角形を用いた，DP的解法で解く．
解は，ΣC/(c1!*c2!*...*cN) である．
「iがci個存在する」という条件は，どのiから適用させても問題ないため，i = 1 から順番に適用させる．
※ 繰り返し自乗法で nCr を求める場合は逆元が必要であり，mod M のMの値によっては求めることが不可能である
※ しかし，パスカルの三角形を用いると，逆元が不要になるので，覚えておく
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_SUM_C 5000
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t,m,pascal[MAX_SUM_C + 1][MAX_SUM_C + 1] = {0};

void init(){
    int i,j;
    pascal[0][0] = 1;
    rep(i,MAX_SUM_C + 1)rep(j,MAX_SUM_C){
        pascal[i][j + 1] = (pascal[i][j + 1] + pascal[i][j]) % m;
        if(i + 1 < MAX_SUM_C + 1)pascal[i + 1][j] = (pascal[i + 1][j] + pascal[i][j]) % m;
    }
}

int comb(int n,int r){
    assert(n >= r);
    return pascal[n - r][r];
}

int solve(){
    int i,n,now_sum = 0,c;
    ll ans = 1;
    scanf("%d",&n);
    rep(i,n){
        scanf("%d",&c);
        ans = (ans * comb(now_sum + c,c)) % m;
        now_sum += c;
    }
    return (int)ans;
}

int main(){
    int i,j;
    scanf("%d%d",&t,&m);
    init();
    while(t--)printf("%d\n",solve());
    return 0;
}