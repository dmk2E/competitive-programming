/*アルゴリズムと工夫点(Conflict 2/CPU: 98 ms Memory: 69952 KB  Length: 1717 B)
Trie木+DFSで解く．
文字列を追加していく性質を活かし，どの文字列かはTrie木上の頂点番号で管理する．
解は，サーバーの頂点番号をTrie木上のDFSで探索し出力する．
最悪計算量は，O(N+Q+Σ|S|)<10^7 となり高速．
※↑Trie木の実装にハッシュ法を用いた連想配列（unorederd_map）を用いた場合
※本実装ではmapを用いているため，実際はO(N+(Q+Σ|S|)*log2(max(S)))≒10^7
*/
#include<iostream>
#include<vector>
#include<map>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

class Trie{
public:
    vector<map<string,int> > to;

    Trie():to(1){}
    /// @brief Trie木上の頂点に文字列sを重みにもつ辺を追加
    /// @param id Trie木上の頂点番号
    /// @param s 文字列
    /// @return 追加した辺の接続先の頂点番号
    int add(int id,const string& s){
        if(to[id].count(s)==0){
            int u=to.size();
            to[id][s]=u;
            to.push_back(map<string,int>());
        }
        return to[id][s];
    }
};

int n,q;

int main(){
    int i,j,k,server_id=0;
    scanf("%d%d",&n,&q);
    vector<int> pc_to_id(n,0);
    Trie tree;
    while(q--){
        scanf("%d",&i);
        if(i==1){
            scanf("%d",&j);
            pc_to_id[j-1]=server_id;
        }else if(i==2){
            scanf("%d",&i);
            string s;
            cin>>s;
            pc_to_id[i-1]=tree.add(pc_to_id[i-1],s);
        }else{
            scanf("%d",&i);
            server_id=pc_to_id[i-1];
        }
    }
    if(server_id!=0){
        string str="";
        auto dfs=[&](auto& func,int now)->bool{
            if(now==server_id){
                cout<<str<<'\n';
                return true;
            }
            for(pair<string,int> d:tree.to[now]){
                str+=d.first;
                if(func(func,d.second))return true;
                int i;rep(i,d.first.size())str.pop_back();
            }
            return false;
        };
        dfs(dfs,0);
    }
    return 0;
}