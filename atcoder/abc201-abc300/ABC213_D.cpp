/*アルゴリズムと工夫点(Cutting Woods/CPU: 227 ms Memory: 23664 KB  Length: 3394 B)
最小の都市番号の探索時間を削減するため，隣接リストの都市のリストをその都市番号の昇順にソートしておく．この処理にかかる計算量だが，i番目の都市と隣接している都市の数をNiとすると，
O(N1log2(N1)+N2log2(N2)+...+NNlog2(NN))<O(Nlog2(N1)+Nlog2(N2)+...)=O(N*log2(N1*N2*...*NN))<10^7 となるから，十分高速．この状態で，深さ優先探索しつつ，訪れた都市を記録していく．
したがって，最悪計算量はO(N*log2(...))<10^7となり，高速． 
※初見4完!嬉しい!
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N (int)(2e5)
using namespace std;

int n;
vector<int> adj[MAX_N],sta;
bool visited[MAX_N]={0};

void dfs(int now){
    visited[now]=true;
    sta.push_back(now+1);
    int i;
    rep(i,adj[now].size()){
        if(visited[adj[now][i]]==false){
            dfs(adj[now][i]);
            sta.push_back(now+1);
        }
    }
}

int main(){
    int i,j,k;
    scanf("%d",&n);
    rep(i,n-1){
        scanf("%d%d",&j,&k);
        adj[--j].push_back(--k);
        adj[k].push_back(j);
    }
    rep(i,n)
        sort(adj[i].begin(),adj[i].end());
    dfs(0);
    rep(i,sta.size()-1)
        printf("%d ",sta[i]);
    printf("%d\n",sta[i]);
    return 0;
}