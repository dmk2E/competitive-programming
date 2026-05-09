/*アルゴリズムと工夫点(Add and Mex/CPU: 87 ms Memory: 27236 KB  Length: 812 B)
Mex:補集合の最小値 であり，全体集合が非負整数であるから，Aiにおける負の数は無視していい．
また，Mexの値がNより大きい値になることはない．なぜならば，Aiの長さがNであり，0,1,...と順に入れていった場合のMexが最大で，それがNとなるからだ．
よって解に影響を及ぼす値の範囲は，0~N となる．また，操作を通じて0<=Ai<N となるような範囲は，┌N/i┐ となり，合計は N*log2(N) 個しかない．
これを利用すると，最悪計算量はO(N*log2(N)+M)<10^7 となり十分高速．
※非負整数を全体集合とする時，ある集合AのMexの最大値は，size(A)となる．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j,k;
    scanf("%d%d",&n,&m);
    vector<int> a(n+1);
    vector<vector<int> > sa(m);
    rep(i,n)scanf("%d",&a[i+1]);
    for(i=1;i<=n;i++){
        a[i]+=i;
        j=a[i]>=0?0:((-a[i]+i-1)/i);
        k=a[i]>=n?0:(((n-a[i])+i-1)/i);
        k=min(k,m);
        for(;j<k;j++){
            sa[j].push_back(a[i]+i*j);
        }
    }
    rep(i,m){
        vector<bool> flag(sa[i].size()+1,false);
        rep(j,sa[i].size())if(sa[i][j]<flag.size())flag[sa[i][j]]=true;
        k=0;
        while(k<(int)flag.size()&&flag[k])k++;
        printf("%d\n",k);
    }
    return 0;
}