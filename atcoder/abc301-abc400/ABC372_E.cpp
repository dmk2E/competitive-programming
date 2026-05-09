/*アルゴリズムと工夫点(K-th Largest Connected Components/CPU: 301 ms Memory: 101368 KB  Length: 1610 B)
マージテク:要素数N個の全体集合において，2つの部分集合が存在し，それぞれA,B(|A|<|B|)とする．この時，集合Aの要素を一つずつ集合Bに入れていくようにすると，計算量はO(|A|)<=O(log2(|N|)) に抑えることができる．
つまり，要素数が少ない方を多い方に入れていけばよい．
よってUnion-Find木を用いて，最悪計算量はO(Q*(log2(N))^2+Q*K)≒10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<set>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class UnionFindTree{
    vector<int> rank,par;
    vector<set<int> > s;
public:
    UnionFindTree(int n=0){
        rank=vector<int>(n,0);
        par=vector<int>(0);
        s=vector<set<int> >(n,set<int>());
        int i;
        rep(i,n){
            par.push_back(i);
            s[i].insert(i);
        }
    }

    int root(int x){
        return par[x]==x?x:par[x]=root(par[x]);
    }

    void unite(int y,int x){
        y=root(y);
        x=root(x);
        if(y==x)return ;
        if(rank[y]<rank[x]){
            par[y]=x;
            for(int yy:s[y])s[x].insert(yy);
        }else{
            par[x]=y;
            if(rank[y]==rank[x])rank[y]++;
            for(int xx:s[x])s[y].insert(xx);
        }
    }

    bool isSame(int y,int x){
        return root(y)==root(x);
    }

    int query(int id,int k){
        set<int>::iterator it=s[root(id)].end();
        while(k--){
            if(it==s[root(id)].begin())return -1;
            it--;
        }
        return (*it)+1;
    }
}UF;

int n,q;

int main(){
    int i,j;
    scanf("%d%d",&n,&q);
    UF tree(n);
    while(q--){
        scanf("%d",&i);
        if(i==1){
            scanf("%d%d",&i,&j);
            i--;j--;
            tree.unite(i,j);
        }else{
            scanf("%d%d",&i,&j);
            i--;
            printf("%d\n",tree.query(i,j));
        }
    }
    return 0;
}