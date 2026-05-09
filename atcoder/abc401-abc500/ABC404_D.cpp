/*アルゴリズムと工夫点(Goin' to the Zoo/CPU: 3 ms Memory: 3900 KB  Length: 1302 B)
3^(N) 通り，動物園への行き方を試せばよい．
注意点として，数え上げの重複をなくす必要がある点．訪れた動物園の集合が同じであれば，訪れる順序は関係ない．
そのため，訪れる動物園の番号が昇順になるように数え上げると良い．
最悪計算量は O(3^(N)*N*M)<10^8 となり間に合う．
※実際は枝刈りを行うため，もっと早い．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_C (int)(1e9)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j,k,completed_count=0;
    ll ans;
    scanf("%d%d",&n,&m);
    vector<int> c(n),state(n,0),count(m,0);
    vector<vector<int> > zoo_to_animals(n);
    rep(i,n)scanf("%d",&c[i]);
    rep(k,m){
        scanf("%d",&j);
        while(j--){
            scanf("%d",&i);
            zoo_to_animals[i-1].push_back(k);
        }
    }
    ans=(ll)MAX_C*n*2+1;
    auto dfs=[&](auto& f,ll sum_c,int now)->void{
        if(completed_count==m){
            ans=min(ans,sum_c);
            return ;
        }
        int i,j;
        for(i=now;i<n;i++)if(state[i]<2&&sum_c+c[i]<ans){
            state[i]++;
            for(int animal:zoo_to_animals[i]){
                if(count[animal]==1)completed_count++;
                count[animal]++;
            }
            f(f,sum_c+c[i],i);
            for(int animal:zoo_to_animals[i]){
                if(count[animal]==2)completed_count--;
                count[animal]--;
            }
            state[i]--;
        }
    };
    dfs(dfs,0,0);
    printf("%lld\n",ans);
    return 0;
}