/*アルゴリズムと工夫点(Make 2-Regular Graph/CPU: 45 ms Memory: 3880 KB  Length: 1752 B)
円順列列挙+分割の仕方全列挙で解く．
全頂点の次数が2となる単純無向グラフは，円の形に繋がったグラフの集合となっている必要がある．
そこで，N個の頂点を「3個以上の頂点で構成されるグループ」の集合へ分け方を再帰を用いて全列挙しておく．
例）N=8 の場合，"3+5"，"4+4"，"8" の3パターンのみ
その後，順列全列挙を用いて，円上での頂点の並べ方を全探索し，1パターンに対して分け方を全て試せばよい．
最悪計算量は O(N^(2)*N!)<10^7 となり高速（グループの分け方全列挙は，順列全列挙より小さいと仮定）．
※バーチャル参加
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j,ans;
    scanf("%d%d",&n,&m);
    vector<vector<bool> > adj(n,vector<bool>(n,false));
    while(m--){
        scanf("%d%d",&i,&j);
        i--;j--;
        adj[i][j]=adj[j][i]=true;
    }
    vector<vector<int> > div;
    vector<int> temp;
    auto rec=[&](auto& func,int last,int rest)->void{
        if(rest==0){
            div.push_back(temp);
            return ;
        }
        int i;
        for(i=last;i<=rest;i++){
            temp.push_back(i);
            func(func,i,rest-i);
            temp.pop_back();
        }
    };
    rec(rec,3,n);
    //printf("cnt:%ld\n",div.size());rep(i,div.size()){rep(j,div[i].size()-1)printf("%d ",div[i][j]);printf("%d\n",div[i][j]);}
    const int INF=n*n*n*n*n;
    auto calc=[&](string& perm)->int{
        int i,j,k,ii,min_cnt=INF;
        rep(k,div.size()){
            int cnt=0;
            vector<vector<bool> > t_adj(n,vector<bool>(n,false));
            j=0;
            rep(ii,div[k].size()){
                rep(i,div[k][ii])t_adj[perm[j+((i+1)%div[k][ii])]-'0'][perm[j+i]-'0']=t_adj[perm[j+i]-'0'][perm[j+((i+1)%div[k][ii])]-'0']=true;
                j=div[k][ii];
            }
            rep(i,n)rep(j,n)cnt+=t_adj[i][j]!=adj[i][j];
            min_cnt=min(min_cnt,cnt);
        }
        return min_cnt/2;
    };
    string tmp="";
    rep(i,n)tmp+='0'+i;
    ans=INF;
    do{
        ans=min(ans,calc(tmp));
    }while(next_permutation(tmp.begin(),tmp.end()));
    printf("%d\n",ans);
    return 0;
}