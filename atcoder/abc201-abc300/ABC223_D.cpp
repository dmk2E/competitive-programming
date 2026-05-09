/*アルゴリズムと工夫点(Restricted Permutation/CPU: 86 ms Memory: 13992 KB  Length: 1113 B)
大小関係等は，有向グラフで表現し，トポロジカルソートする．この時，用いるキューは優先度付きキューとする．
※グラフで関係を表現するのは気づいていたが，「トポロジカルソート」だとは気づけなかった...
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;
vector<vector<int> > adj;
vector<int> indeg;

bool topological(vector<int>& ans){
    int i,now;
    priority_queue<int> PQ;
    rep(i,n)if(indeg[i]==0)PQ.push(-i);
    while(PQ.size()){
        now=-PQ.top();PQ.pop();
        ans.push_back(now);
        rep(i,adj[now].size()){
            if(indeg[adj[now][i]]>0){
                indeg[adj[now][i]]--;
                if(indeg[adj[now][i]]==0)
                    PQ.push(-adj[now][i]);
            }
        }
    }
    return ans.size()==n;
}

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    adj=vector<vector<int> >(n,vector<int>(0));
    indeg=vector<int>(n,0);
    vector<int> ans;
    while(m--){
        scanf("%d%d",&i,&j);
        adj[i-1].push_back(j-1);
        indeg[j-1]++;
    }
    if(topological(ans)){
        rep(i,n-1)printf("%d ",ans[i]+1);printf("%d\n",ans[i]+1);
    }else
        puts("-1");
    return 0;
}