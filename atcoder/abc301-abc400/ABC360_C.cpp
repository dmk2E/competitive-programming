/*アルゴリズムと工夫点(Move It/CPU: 29 ms Memory: 10252 KB  Length: 1105 B)
各箱aiに入っている荷物の中で，重さの昇順に荷物をsize(ai)-1個取り出していき，取り出した中で最も軽い荷物を任意の空の箱の中に動かせばよい．
空の箱の数nとすると，昇順に前からn個の荷物の重さの総和が答えとなる．
最悪計算量はO(N*log2(N))<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N (int)(1e5)
using namespace std;

typedef struct data{
    int id,w;

    data(int iid=0,int ww=0):id(iid),w(ww){}

    bool operator<(const data& k)const{
        return w<k.w;
    }
}Data;

int n,a[MAX_N];
bool flag[MAX_N]={false};
Data ipt[MAX_N];

int main(){
    int i,j=0,k,ans=0;
    vector<Data> temp[MAX_N];
    priority_queue<int> PQ;
    scanf("%d",&n);
    rep(i,n){
        scanf("%d",&a[i]);
        a[i]--;
        if(flag[a[i]]==false){
            flag[a[i]]=true;
            j++;
        }
    }
    j=n-j;
    rep(i,n){
        scanf("%d",&ipt[i].w);
        ipt[i].id=i;
        temp[a[i]].push_back(ipt[i]);
    }
    rep(i,n)
        sort(temp[i].begin(),temp[i].end());
    rep(i,n){
        if(temp[i].size()>1){
            rep(k,temp[i].size()-1)    
                PQ.push(-temp[i][k].w);
        }
    }
    while(j--){
        ans-=PQ.top();PQ.pop();
    }
    printf("%d\n",ans);
    return 0;
}