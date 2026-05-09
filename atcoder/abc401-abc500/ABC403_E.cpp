/*アルゴリズムと工夫点(Forbidden Prefix/CPU: 103 ms Memory: 52820 KB  Length: 1567 B)
頂点間に「1文字アルファベットを重みとしてもたせる辺」を追加していく木をTrie木という．
ex) "atcoder"->"ata"->"wa" が与えられると...
・-a-・-t-・-c-・-o-・-d-・-e-・-r-・
│          └-a-・-t-・-a-・
└ -w-・-a-・
Trie木生成は，各頂点から出ている，辺の重み毎に，接続先の頂点番号を管理することで行う．
具体的には，(始点の頂点番号，辺の重み) -> (辺の接続先の頂点番号) となるデータ構造で管理する．これは辞書の一次元配列などで実現可能．
・根の頂点番号は0として，あらかじめ用意しておく．

先に全ての文字列を受け取り，Trie木を作成しておく．
その後，順にクエリを処理していき，頂点に，XかYのどちらの集合かをフラグを付けていく．
※Trie木かな?と思ったが作成したことがないので，断念．
*/
#include<iostream>
#include<vector>
#include<map>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

class Trie{
    vector<map<char,int> > to;
public:
    int ans;
    vector<bool> ng;
    vector<int> num_y;

    Trie():to(1){}
    /// @brief Trie木に文字列sを追加
    /// @param s 
    /// @return 文字列sに対応する頂点番号
    int add(const string& s){
        int now_v=0;
        for(char c:s){
            if(to[now_v].count(c)==0){
                int u=to.size();
                to[now_v][c]=u;
                to.push_back(map<char,int>());
            }
            now_v=to[now_v][c];
        }
        return now_v;
    }

    void init(){
        ans=0;
        int n=to.size();
        ng.resize(n,false);
        num_y.resize(n);
    }

    void addX(int v){
        if(ng[v])return ;
        ng[v]=true;
        ans-=num_y[v];
        for(auto[c,u]:to[v])addX(u);
    }

    void addY(int v){
        if(ng[v])return ;
        ans++;
        num_y[v]++;
    }
};

int q;

int main(){
    int i,j;
    string s;
    Trie tree;
    vector<P> ipt;
    scanf("%d",&q);
    while(q--){
        scanf("%d",&i);
        cin>>s;
        j=tree.add(s);
        ipt.push_back(P(i,j));
    }
    tree.init();
    for(auto [type,id]:ipt){
        if(type==1)tree.addX(id);
        else tree.addY(id);
        printf("%d\n",tree.ans);
    }
    return 0;
}