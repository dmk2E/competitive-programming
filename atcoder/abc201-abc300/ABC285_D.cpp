/*アルゴリズムと工夫点(Change Usernames/CPU: 153 ms Memory: 18152 KB  Length: 1838 B)
S->Tへの名前の変更を，名前それぞれを頂点とみなした時の有向辺と捉え，その有向重み無しグラフ上で閉路がないか判定すればよい．
最悪計算量はO(N*log2(N))<10^7 より，高速．
※初見4完!嬉しい
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

typedef pair<string,string> p;

typedef enum state{
    VISITED=1,
    NOTVISITED=0,
    COMPLETED=-1
}State;

int n;
vector<p> ipt;
vector<string> id2Name;
vector<int> adj;
vector<State> color;

int name2Id(string name){
    int left=0,mid,right=id2Name.size();
    while(left<right){
        mid=(left+right)/2;
        if(id2Name[mid]==name)
            return mid;
        else if(id2Name[mid]<name)
            left=mid+1;
        else
            right=mid;
    }
    return left;
}

bool dfs(int now){
    color[now]=VISITED;
    //printf("now:%d\n",now);
    if(color[adj[now]]==COMPLETED){
        color[now]=COMPLETED;
        //printf("finish:%d\n",now);
        return true;
    }else if(color[adj[now]]==NOTVISITED){
        if(dfs(adj[now])){
            color[now]=COMPLETED;
            //printf("finish:%d\n",now);
            return true;
        }
    }
    //printf("finish:%d\n",now);
    return false;
}

int main(){
    int i,j;
    scanf("%d",&n);
    ipt=vector<p>(n);
    rep(i,n){
        cin>>ipt[i].first>>ipt[i].second;
        id2Name.push_back(ipt[i].first);
        id2Name.push_back(ipt[i].second);
    }
    sort(id2Name.begin(),id2Name.end());
    id2Name.erase(unique(id2Name.begin(),id2Name.end()),id2Name.end());
    adj=vector<int>(id2Name.size());
    color=vector<State>(id2Name.size(),COMPLETED);
    rep(i,n){
        adj[j=name2Id(ipt[i].first)]=name2Id(ipt[i].second);
        color[j]=NOTVISITED;
    }
    rep(i,id2Name.size()){
        if(color[i]!=COMPLETED){
            if(!dfs(i))break;
        }
    }
    printf("%s\n",i==id2Name.size()?"Yes":"No");
    return 0;
}