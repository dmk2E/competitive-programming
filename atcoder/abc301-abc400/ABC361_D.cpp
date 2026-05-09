/*アルゴリズムと工夫点(Go Stone Puzzle/CPU: 193 ms Memory: 10296 KB  Length: 1467 B)
全パターン数は，'W','B','.'の3種類の順列を考えて，log10(3^(14))=14*0.30..≒4.2<5となり，読み切れるため，幅優先探索で解ける．
※string型とchar型(1文字)の加算演算子は定義されているが，char型同士の加算演算子は定義されていないことに注意．
*/
#include<iostream>
#include<queue>
#include<map>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int n;
string s,t;

int bfs(string s,string t){
    int i,j;
    const int NIL=-1;
    string now;
    queue<string> que;
    map<string,int> visited;
    visited[s]=1;
    que.push(s);
    while(que.size()){
        //cout<<"now:"<<(string)que.front()<<endl;
        if(que.front()==t)
            return visited[t]-1;
        rep(i,que.front().length()-1){
            now="";
            if(que.front()[i]!='.'&&que.front()[i+1]!='.'){
                for(j=0;j<que.front().length();j++){
                    if(que.front()[j]=='.'){
                        now+=que.front()[i];
                        now+=que.front()[i+1];
                        j++;
                    }else if(j==i){
                        now+="..";
                        j++;
                    }
                    else{
                        now+=que.front()[j];
                    }
                }
                if(visited[now]==0){
                    //cout<<"new:"<<(string)now<<endl;
                    visited[now]=visited[que.front()]+1;
                    que.push(now);
                }
            }
        }
        que.pop();
    }
    return NIL;
}

int main(){
    int i;
    scanf("%d",&n);
    cin>>s>>t;
    printf("%d\n",bfs(s+"..",t+".."));    
    return 0;
}