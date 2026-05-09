/*アルゴリズムと工夫点(Gravity/CPU: 86 ms Memory: 17940 KB  Length: 1121 B)
状況の整理を求められる問題．
難しい...
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,w,q,t,a;

int main(){
    int i,j;
    scanf("%d%d",&n,&w);
    vector<int> x(n),y(n);
    rep(i,n){
        scanf("%d%d",&x[i],&y[i]);
        x[i]--;
    }
    vector<int> idx(n);
    rep(i,n)idx[i]=i;
    sort(idx.begin(),idx.end(),[&](int i,int j)->bool{
        return y[i]<y[j];
    });
    vector<int> r(n),num(w,0);
    for(int i:idx){
        r[i]=num[x[i]];
        num[x[i]]++;
    }
    const int INF=(int)(1e9)+1;
    vector<int> d(n,INF);
    {
        vector<vector<int> > blocks(n);
        rep(i,n)blocks[r[i]].push_back(i);
        rep(i,n){
            if(blocks[i].size()!=w)continue;
            int mx=0;
            for(int j:blocks[i])mx=max(mx,y[j]-1);
            d[i]=mx+1;
        }
    }
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&t,&a);
        a--;
        if(d[r[a]]>t)puts("Yes");
        else puts("No");
    }
    return 0;
}