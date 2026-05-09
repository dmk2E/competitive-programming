/*アルゴリズムと工夫点(Swap Hats/CPU: 1 ms Memory: 3620 KB  Length: 1767 B)

*/
#include<iostream>
#include<queue>
#include<map>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int s,t;

int c2Id(char c){
    switch(c){
        case 'R':
            return 0;
        case 'G':
            return 1;
        default:
            break;
    }
    return 2;
}

int str2Int(string str){
    int i,ans=0;
    rep(i,str.length()){
        ans*=10;
        ans+=str[i]-'0';
    }
    return ans;
}

int main(){
    int i,j;
    char c;
    s=t=0;
    rep(i,3){
        c=getchar();
        s*=10;
        s+=c2Id(c);
        getchar();
    }
    rep(i,3){
        c=getchar();
        t*=10;
        t+=c2Id(c);
        getchar();
    }
    auto bfs=[&](int s,int t)->bool{
        int i,j,nxt;
        string str,tmp;
        queue<int> que;
        map<int,int> vis;
        vis[s]=0;
        que.push(s);
        while(que.size()){
            s=que.front();que.pop();
            str="";
            i=3;
            j=s;
            while(i--){
                str+=(char)((j%10)+'0');
                j/=10;
            }
            reverse(str.begin(),str.end());
            //printf("%s\n",str.c_str());
            rep(i,3)rep(j,i){
                tmp=str;
                swap(tmp[j],tmp[i]);
                nxt=str2Int(tmp);
                //printf("%d\n",nxt);
                if(vis.find(nxt)==vis.end()){
                    vis[nxt]=vis[s]+1;
                    que.push(nxt);
                }
            }
        }
        //printf("%d\n",vis[t]);
        return vis[t]%2==0;
    };
    printf("%s\n",bfs(s,t)?"Yes":"No");
    return 0;
}