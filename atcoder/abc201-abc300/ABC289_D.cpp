/*アルゴリズムと工夫点(Step Up Robot/CPU: 8 ms Memory: 4020 KB  Length: 1012 B)
0~xまでの段数を頂点とし，各頂点xiからn本の辺が，各頂点xi+a[i]に繋がっているグラフ上での，幅優先探索を行うことを考える．この時，餅の影響を考慮して，餅がおいてある階段から伸びる辺の数は0とする．
最悪計算量はO(x*n)<10^7 となり，十分高速．
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_M (int)(1e5)
using namespace std;

int n,m;
vector<int> a;
vector<bool> x;
bool b[MAX_M+1]={0};

bool bfs(int s){
    queue<int> que;
    x[s]=true;
    que.push(s);
    while(que.size()){
        //cout<<que.front()<<endl;
        if(que.front()==x.size()-1)
            return true;
        rep(s,n){
            if(b[que.front()])break;
            if(que.front()+a[s]<=x.size()&&x[que.front()+a[s]]==false){
                x[que.front()+a[s]]=true;
                que.push(que.front()+a[s]);
            }
        }
        que.pop();
    }
    return false;
}

int main(){
    int i;
    scanf("%d",&n);
    a=vector<int>(n);
    rep(i,n)
        scanf("%d",&a[i]);
    scanf("%d",&m);
    while(m--){
        scanf("%d",&i);
        b[i]=true;
    }
    scanf("%d",&i);
    x=vector<bool>(i+1,false);
    printf("%s\n",bfs(0)?"Yes":"No");
    return 0;
}