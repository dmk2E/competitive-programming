/*アルゴリズムと工夫点(Cables and Servers/CPU: 127 ms Memory: 18436 KB  Length: 1984 B)
連結成分ごとに分けた後，辺の繋ぎ変えを行えばよい．
特定の要素以外の要素を求める時，setが便利で，特定の要素を削除してから先頭の要素のなどを取得すればよい．
*/
#include<iostream>
#include<vector>
#include<set>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class UnionFindTree{
    vector<int> rank,par,cnt;
public:
    UnionFindTree(int n=0){
        rank=vector<int>(n,0);
        par=vector<int>(0);
        cnt=vector<int>(n,1);
        int i;
        rep(i,n)
            par.push_back(i);
    }

    int root(int x){
        return par[x]==x?x:par[x]=root(par[x]);
    }

    int unite(int y,int x){
        y=root(y);
        x=root(x);
        if(y==x)return -1;
        if(rank[y]<rank[x]){
            par[y]=x;
            cnt[x]+=cnt[y];
            return x;
        }else{
            par[x]=y;
            cnt[y]+=cnt[x];
            if(rank[y]==rank[x])rank[y]++;
            return y;
        }
    }

    bool isSame(int y,int x){
        return root(y)==root(x);
    }

    int count(int x){
        return cnt[root(x)];
    }

    void show(){
        int i;
        printf("par:");rep(i,rank.size())printf("%d ",par[i]);puts("");
        printf("cnt:");rep(i,rank.size())printf("%d ",cnt[root(i)]);puts("");
    }
}UF;

struct Data{
    int id,a,b;

    Data(int iid=0,int aa=0,int bb=0):id(iid),a(aa),b(bb){}
};

int n,m;

int main(){
    int i,j,k;
    scanf("%d%d",&n,&m);
    UF tree(n);
    vector<Data> temp;
    Data tmp;
    rep(k,m){
        scanf("%d%d",&i,&j);
        i--;j--;
        if(tree.isSame(i,j)==false)tree.unite(i,j);
        else temp.push_back(Data(k+1,i,j));
    }
    set<int> us;
    rep(i,n)if(tree.root(i)==i)us.insert(i);
    printf("%d\n",(int)us.size()-1);
    while(us.size()>1){
        tmp=temp.back();temp.pop_back();
        i=tree.root(tmp.a);us.erase(i);
        j=*us.begin();us.erase(j);
        printf("%d %d %d\n",tmp.id,tmp.a+1,j+1);
        i=tree.unite(i,j);us.insert(i);
    }
    return 0;
}