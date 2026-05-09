/*アルゴリズムと工夫点(Sort Arrays/CPU: 166 ms Memory: 85296 KB  Length: 1706 B)
Trie木 + DFS で解く．
数列を対象としたTrie木を作る．
この時，木の頂点それぞれには配列Aの添え字を可変長配列の形で保持しておく．
作成した木上で，辺の値（= 数列の値）の小さいものから優先的に探索を行うDFSを実行する．
その過程で訪れた頂点に含まれる，配列Aの添え字を順次出力すればよい．
最悪計算量は，O(N * log2(N)) < 10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Node{
    vector<int> a_ids;
    map<int,int> edge_to_node;

    Node(){}
};

struct Trie{
    vector<Node> nodes;

    Trie(){
        nodes.push_back(Node());
    }

    int add(int node_id, int val, int a_id){
        int nxt_node;
        if(nodes[node_id].edge_to_node.find(val) == nodes[node_id].edge_to_node.end()){
            nxt_node = nodes[node_id].edge_to_node[val] = nodes.size();
            nodes.push_back(Node());
            nodes.back().a_ids.push_back(a_id);
            return nxt_node;
        }else{
            nxt_node = nodes[node_id].edge_to_node[val];
            nodes[nxt_node].a_ids.push_back(a_id);
            return nxt_node;
        }
    }
};

int n;

int main(){
    int i,j;
    const int NIL = -1;
    scanf("%d", &n);
    Trie tree;
    vector<int> a_to_node(n + 1, NIL), ans;
    tree.nodes[0].a_ids.push_back(0);
    a_to_node[0] = 0;
    rep(i,n){
        int x,y;
        scanf("%d%d", &x, &y);
        int node_id = tree.add(a_to_node[x], y, i + 1);
        a_to_node[i + 1] = node_id;
    }
    auto dfs = [&](auto& func, int now) -> void{
        vector<int>& a_ids = tree.nodes[now].a_ids;
        sort(a_ids.begin(), a_ids.end());
        for(int a_id : a_ids)ans.push_back(a_id);
        for(auto [val, nxt] : tree.nodes[now].edge_to_node)func(func, nxt);
    };
    dfs(dfs, 0);
    rep(i, ans.size() - 2)printf("%d ",ans[i + 1]);
    printf("%d\n",ans[i + 1]);
    return 0;
}