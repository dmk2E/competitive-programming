/*アルゴリズムと工夫点("redocta".swap(i,i+1)/CPU: 7 ms Memory: 4296 KB  Length: 844 B)
文字列Sの全状態数は，|S|! であり，今回は|S|=7 であるからBFSを用いた全探索で解く．
最悪計算量は O(|S|*|S|!)<10^7 となり高速．
*/
#include<iostream>
#include<queue>
#include<map>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s;
const string t="atcoder";

int main(){
    int i,j;
    cin>>s;
    auto bfs=[&](string now)->int{
        int i;
        string tmp;
        queue<string> que;
        map<string,int> vis;
        vis[now]=0;
        que.push(now);
        while(que.size()){
            now=que.front();que.pop();
            rep(i,s.length()-1){
                tmp=now;
                swap(tmp[i],tmp[i+1]);
                if(vis.find(tmp)==vis.end()){
                    que.push(tmp);
                    vis[tmp]=vis[now]+1;
                }
            }
        }
        return vis[t];
    };
    printf("%d\n",bfs(s));
    return 0;
}