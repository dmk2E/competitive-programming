/*アルゴリズムと工夫点(KAIBUNsyo/CPU: 22 ms Memory: 6772 KB  Length: 1283 B)
先頭と末端から回文になっているか判定していく。違う値になったら、両者の値のどちらかを一方の値に変更することを繰り返し、その個数を出力すればよい。ただし、その数字が現在どんな数値になっているかは、Union-Find木を用いて
高速に判定させた。こうすることで最悪計算量はO(n)<10^6 より、十分高速。
※初見4完達成!
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 200000
using namespace std;

typedef class UnionFind{
    vector<int> par,rank,num;
public:
    UnionFind(int n=0){
        int i;
        rep(i,n){
            par.push_back(i);
            num.push_back(i);
            rank.push_back(0);
        }
    }

    int root(int x){
        return par[x]==x?x:par[x]=root(par[x]);
    }

    void unite(int x,int y,int nnum){
        x=root(x);
        y=root(y);
        if(x==y)return ;
        if(rank[x]<rank[y]){
            par[x]=y;
            num[y]=nnum;
        }else{
            par[y]=x;
            num[x]=nnum;
            if(rank[x]==rank[y])
                rank[y]++;
        }
    }

    bool isSame(int x,int y){
        return root(x)==root(y);
    }

    int a2Num(int x){
        return num[root(x)];
    }
}UF;

int n,a[MAX_N];

int main(){
    int i,cnt=0;
    UF tree(MAX_N+1);
    scanf("%d",&n);
    rep(i,n){
        scanf("%d",&a[i]);
    }
    i=0;
    while(i<n-1-i){
        if(tree.a2Num(a[i])!=tree.a2Num(a[n-1-i])){
            cnt++;
            tree.unite(a[i],a[n-1-i],a[i]);
        }
        i++;
    }
    printf("%d\n",cnt);
    return 0;
}