/*アルゴリズムと工夫点(Keep Distance/CPU: 196 ms Memory: 36700 KB  Length: 893 B)
再帰を用いて条件を満たす整数列を辞書順に列挙する．
※枝刈り条件を入れなかったせいで，TLEを2回出してしまった...今度からは入れるようにしたい．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j,x=0;
    scanf("%d%d",&n,&m);
    vector<int> ans(n);
    vector<vector<int> > aans;
    auto rec=[&](auto& f,int id)->void{
        int i;
        if(id==n){
            aans.push_back(ans);
            // rep(i,n-1)printf("%d ",ans[i]);
            // printf("%d\n",ans[i]);
            return ;
        }
        for(i=ans[id-1]+10;i<=m;i++){
            if(i+(n-id-1)*10>m)break;
            ans[id]=i;
            f(f,id+1);
        }
    };
    rep(i,m+1){
        ans[0]=i+1;
        rec(rec,1);
    }
    printf("%d\n",(int)aans.size());
    rep(i,aans.size()){
        rep(j,n-1)printf("%d ",aans[i][j]);
        printf("%d\n",aans[i][j]);
    }
    return 0;
}