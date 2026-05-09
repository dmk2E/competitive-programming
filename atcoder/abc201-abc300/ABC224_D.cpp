/*アルゴリズムと工夫点(8 Puzzle on Graph/CPU: 1100 ms Memory: 34772 KB  Length: 1468 B)
頂点番号を0~8，コマ番号を0~7とする．コマがおかれていない頂点に置かれているコマを「空コマ」と定義し，コマ8とする．
文字列Stateとして，頂点iに置かれているコマがjである時，state[i]=jとすると，state=012345678 とするための最小の移動回数を求めればよい．
あり得るstateの状態数NはN=9!<10^6 通りしかないため，幅優先探索で高速に解くことができる．
生成済みの状態記録に連想配列を用いるため，最悪計算量はO((N+M)*|state|*log2(N))<10^8 となり，間に合う．
※初見4完!嬉しい!
*/
#include<iostream>
#include<vector>
#include<queue>
#include<map>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_V 9
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<string,int> p;//(どの頂点にどのコマがあるか表した文字列state,コマがおかれていない頂点番号)

int m;

int main(){
    int i,j;
    vector<vector<int> > adj(MAX_V,vector<int>(0));
    string state="";
    rep(i,MAX_V)
        state+='8';
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&i,&j);
        i--;j--;
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    rep(i,MAX_V-1){
        scanf("%d",&j);
        state[j-1]=(char)((int)'0'+i);
    }
    const int NIL=-1;
    auto bfs=[&](string state)->int{
        int i;
        p now;
        string tmp;
        queue<p> que;
        map<string,int> visited;
        rep(i,state.length())if(state[i]=='8')break;
        que.push(p(state,i));
        visited[state]=1;
        while(que.size()){
            now=que.front();que.pop();
            if(now.first=="012345678")return visited[now.first]-1;
            rep(i,adj[now.second].size()){
                tmp=now.first;
                swap(tmp[adj[now.second][i]],tmp[now.second]);
                if(visited[tmp]==0){
                    visited[tmp]=visited[now.first]+1;
                    que.push(p(tmp,adj[now.second][i]));
                }
            }
        }
        return NIL;
    };
    printf("%d\n",bfs(state));
    return 0;
}