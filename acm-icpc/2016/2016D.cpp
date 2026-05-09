#include<iostream>
#include<vector>
#include<map>
#define rep(i,n)for(i=0;i<(int)n;i++)
#define NIL -1
using namespace std;

int n;
map<vector<bool>,bool> dic;

int dfs(vector<bool> state,int cnt,vector<int>& input){
    int i,j,mmax=cnt,now=NIL,nxt=NIL;
    dic[state]=true;
    rep(i,input.size()){
        if(state[i]==true)
            continue;
        if(now==NIL)
            now=i;
        else if(nxt==NIL){
            nxt=i;
            if(abs(input[now]-input[nxt])<=1){
                state[now]=state[nxt]=true;
                if(dic[state]==false&&(j=dfs(state,cnt+2,input))>mmax)
                    mmax=j;
                state[now]=state[nxt]=false;
            }
            now=nxt;
            nxt=NIL;
        }
    }
    return mmax;
}

int main(){
    int i,j;
    // printf("%d\n",300);
    // rep(i,300){
    //     printf("%d ",i+1);
    // }
    // puts("");
    // return 0;
    while(1){
        scanf("%d",&n);
        if(!n)
            break;
        vector<int> input(n);
        vector<bool> state(n,false);
        rep(i,n)
            scanf("%d",&input[i]);
        dic.clear();
        printf("%d\n",dfs(state,0,input));
    }
    return 0;
}