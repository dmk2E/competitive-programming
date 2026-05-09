/*アルゴリズムと工夫点(Remembering the Days/CPU: 102 ms Memory: 3904 KB  Length: 1032 B)
順列全列挙で解く．
Nが小さいため，訪れる町の順序を全て試す．
しかし，ある順序の内，先頭からの部分順序の時点でどの町への移動も不可能である場合，それ以降の部分の列挙は無駄である．
そこで再帰を用いた実装にすることで枝刈りを行うことができ，より高速に動作する．
最悪計算量は，O(N*N!) < 10^8 となり間に合う．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j;
    const int NIL = -1;
    scanf("%d%d",&n,&m);
    vector<vector<int> > adj(n,vector<int>(n,NIL));
    while(m--){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        a--;b--;
        adj[a][b] = adj[b][a] = c;
    }
    auto rec = [&](auto& func,int now,int state,int sum)->int{
        int i,ans = sum;
        if(state == (1<<n)-1){
            // First Pick Up
            rep(i,n)ans = max(ans,func(func,i,state^(1<<i),sum));
        }else{
            rep(i,n)
                if(
                    ((state>>i) & 1) && 
                    adj[now][i] != NIL
                ){
                    ans = max(ans,func(func,i,state^(1<<i),sum+adj[now][i]));
                }
        }
        return ans;
    };
    printf("%d\n",rec(rec,0,(1<<n)-1,0));
    return 0;
}