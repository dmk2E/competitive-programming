/*アルゴリズムと工夫点(木変形パズル/CPU: 930 ms Memory: 41248 KB  Length: 4447 B)
構文解析により，与式を隣接リスト表現に直して，次の木DPを考える．dp[i]:節点番号iを根とする部分木の最大値と最小値
このdp[i]の値は，この根に到達する前の接点によって変わるため，(部分木の根,その親の接点)でメモ化しておく．任意の部分木における最大値と最小値が求まれば，それより大きい木における最大値と最小値をO(1)で求めることができる．
したがって，最悪計算量は木の頂点数Nとして，O(N)程度になる．
※任意の接点が根になれるとは見抜けなかった...悔しい
*/
#include<iostream>
#include<vector>
#include<map>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_S (int)(5e5)
#define PLUS -1
#define MINUS -2
#define NIL -(int)(1e9)
using namespace std;

typedef pair<int,int> p;

typedef struct data{
    int max,min;

    data(int mmax=NIL,int mmin=NIL):max(mmax),min(mmin){}
}Data;

string s;

void makeTree(int l,int r,int now,vector<vector<int> >& adj,int& nxt,vector<int>& id2X,vector<int>& nodes){
    nodes.push_back(now);
    int cnt=0,start;
    //printf("makeTree(%d,%d,%d,%d)={",l,r,now,nxt);
    while(l<r){
        if(s[l]=='('){
            if(cnt==0)start=l;
            cnt++;
        }else if(s[l]==')'){
            cnt--;
            if(cnt==0){
                adj[now].push_back(nxt);
                adj.push_back(vector<int>(0));
                adj[nxt].push_back(now);
                id2X.push_back(0);
                nxt++;
                makeTree(start+1,l,nxt-1,adj,nxt,id2X,nodes);
            }
        }else if(cnt==0){
            if((int)'0'<=(int)s[l]&&(int)s[l]<=(int)'9'){
                adj[now].push_back(nxt);
                adj.push_back(vector<int>(0));
                adj[nxt].push_back(now);
                id2X.push_back(0);
                id2X[nxt++]=s[l]-'0';
            }else if(s[l]=='+'){
                id2X[now]=PLUS;
            }else if(s[l]=='-')
                id2X[now]=MINUS;
        }
        l++;
        //printf("%d ",l);
    }
    //printf("}");
}

void showAdj(vector<vector<int> >& adj,vector<int>& id2X){
    int i,j;
    rep(i,adj.size()){
        printf("%d(%d):",i,id2X[i]);
        rep(j,adj[i].size()){
            printf("%d(%d)->",adj[i][j],id2X[adj[i][j]]);
        }
        puts("");
    }
    puts("");
}

void search(int now,vector<int>& temp,vector<int>& values,const int& root,const int& par,map<p,Data>& memo){
    if(now==temp.size()){
        int i,tmp=0,maxI=0,minI=0;
        rep(i,values.size()){
            tmp+=values[i];
            if(values[maxI]<values[i])
                maxI=i;
            if(values[minI]>values[i])
                minI=i;
        }
        if(memo[p(root,par)].max<2*values[maxI]-tmp)
            memo[p(root,par)].max=2*values[maxI]-tmp;
        if(memo[p(root,par)].min>2*values[minI]-tmp)
            memo[p(root,par)].min=2*values[minI]-tmp;
        return ;
    }
    values[now]=memo[p(temp[now],root)].max;
    search(now+1,temp,values,root,par,memo);
    values[now]=memo[p(temp[now],root)].min;
    search(now+1,temp,values,root,par,memo);
}

void dfs(int root,int par,vector<vector<int> >& adj,vector<int>& id2X,map<p,Data>& memo){
    int i,j;
    vector<int> temp;
    rep(i,adj[root].size()){
        if(adj[root][i]==par)continue;
        temp.push_back(adj[root][i]);
        if(memo[p(adj[root][i],root)].max!=NIL)continue;
        if(id2X[adj[root][i]]<0){
            dfs(adj[root][i],root,adj,id2X,memo);
        }else
            memo[p(adj[root][i],root)].max=memo[p(adj[root][i],root)].min=id2X[adj[root][i]];
        //printf("dp[(%d,%d)]=(%d,%d)\n",adj[root][i],root,memo[p(adj[root][i],root)].max,memo[p(adj[root][i],root)].min);
    }
    if(id2X[root]==PLUS){
        memo[p(root,par)].max=memo[p(root,par)].min=0;
        rep(i,temp.size()){
            memo[p(root,par)].max+=memo[p(temp[i],root)].max;
            memo[p(root,par)].min+=memo[p(temp[i],root)].min;
            //if(par==NIL)printf("%d,",temp[i]);
        }
        //if(par==NIL)puts("");
    }else{
        memo[p(root,par)].max=NIL;
        memo[p(root,par)].min=-NIL;
        vector<int> values(temp.size(),0);
        search(0,temp,values,root,par,memo);
        //printf("memo[p(%d,%d)] max:%d min:%d\n",root,par,memo[p(root,par)].max,memo[p(root,par)].min);
    }
    //if(par==NIL){printf("%d\n",memo[p(root,par)].max);puts("");}
}

int main(){
    int i,mmax;
    while(1){
        cin>>s;
        if(s[0]=='-')
            break;
        vector<vector<int> > adj;
        vector<int> id2X,nodes;
        adj.push_back(vector<int>(0));
        i=1;id2X.push_back(0);
        makeTree(0,s.length(),0,adj,i,id2X,nodes);
        //puts("");showAdj(adj,id2X);rep(i,nodes.size())printf("%d ",nodes[i]);puts("");
        map<p,Data> memo;
        mmax=NIL;
        rep(i,nodes.size()){
            dfs(nodes[i],NIL,adj,id2X,memo);
            if(mmax<memo[p(nodes[i],NIL)].max)
                mmax=memo[p(nodes[i],NIL)].max;
        }
        printf("%d\n",mmax);
    }
    return 0;
}