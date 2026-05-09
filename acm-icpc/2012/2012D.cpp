/*アルゴリズムと工夫点(鉄道乗り継ぎ/CPU:  ms Memory:  KB  Length:  B)

*/
#include<iostream>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 100
#define MAX_C 20
#define MAX_P 50
#define MAX_Q 10001
#define INF ((int)(1e7)+1)
using namespace std;

typedef struct train{
    int s,d,c;

    train(int ss=0,int dd=0,int cc=0):s(ss),d(dd),c(cc){}
}Train;

typedef struct company{//距離q以下で,距離1に対する運賃r
    int q,r,sum;

    company(int qq=0,int rr=0,int ssum=0):q(qq),r(rr),sum(ssum){}
}Company;

typedef struct data{
    int x,c,d,sum;

    data(int xx=0,int cc=0,int dd=0,int ssum=0):x(xx),c(cc),d(dd),sum(ssum){}

    bool operator<(const data& k)const{
        return sum<k.sum;
    }
}Data;

int n,m,c,s,g,p[MAX_C];
Company info[MAX_C][MAX_P+1];

int search(int d,int c){
    int left=0,right=p[c],mid;
    while(left<right){
        mid=(left+right)/2;
        if(info[c][mid].q<=d)
            left=mid+1;
        else
            right=mid;
    }
    return left;
}

int solve(){
    
}

int main(){
    int i,j,k,l;
    while(1){
        scanf("%d%d%d%d%d",&n,&m,&c,&s,&g);
        if(!(n||m||c||s||g))
            break;
        s--;g--;
        vector<Train> adj[MAX_N];
        while(m--){
            scanf("%d%d%d%d",&i,&j,&k,&l);
            i--;j--;l--;
            adj[i].push_back(Train(j,k,l));
            adj[j].push_back(Train(i,k,l));
        }
        rep(i,c)
            scanf("%d",&p[i]);
        rep(i,c){
            rep(j,p[i]-1){
                scanf("%d",&info[i][j].q);
                info[i][j].sum=0;
            }
            info[i][j].q=INF;
            info[i][j].sum=0;
            info[i][j+1].sum=0;
            rep(j,p[i]){
                scanf("%d",&info[i][j].r);
                info[i][j+1].sum=info[i][j].sum+info[i][j].q*info[i][j].r;
            }
        }
        printf("%d\n",solve());
    }
    return 0;
}
/*ダイクストラ法で解こうとして答えが合わなかった
#include<iostream>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 100
#define MAX_C 20
#define MAX_P 50
#define MAX_Q 10001
#define INF ((int)(1e7)+1)
using namespace std;

typedef struct train{
    int s,d,c;

    train(int ss=0,int dd=0,int cc=0):s(ss),d(dd),c(cc){}
}Train;

typedef struct company{//距離q以下で,距離1に対する運賃r
    int q,r,sum;

    company(int qq=0,int rr=0,int ssum=0):q(qq),r(rr),sum(ssum){}
}Company;

typedef struct data{
    int x,c,d,sum;

    data(int xx=0,int cc=0,int dd=0,int ssum=0):x(xx),c(cc),d(dd),sum(ssum){}

    bool operator<(const data& k)const{
        return sum<k.sum;
    }
}Data;

int n,m,c,s,g,p[MAX_C];
Company info[MAX_C][MAX_P+1];

int search(int d,int c){
    int left=0,right=p[c],mid;
    while(left<right){
        mid=(left+right)/2;
        if(info[c][mid].q<=d)
            left=mid+1;
        else
            right=mid;
    }
    return left;
}

int dijk(vector<Train> adj[MAX_N]){
    int i,j,k,l;
    Data now;
    bool color[MAX_N][MAX_C][MAX_Q+1]={0};
    priority_queue<Data> PQ;
    rep(i,n)
        rep(j,c)
            color[i][j][0]=true;
    for(Train nxt:adj[s]){
        j=search(nxt.d,nxt.c);
        //printf("j:%d\n",j);
        k=0;
        k+=info[nxt.c][j].sum;
        k+=(nxt.d-(j-1>=0?info[nxt.c][j-1].q:0))*info[nxt.c][j].r;
        PQ.push(Data(nxt.s,nxt.c,nxt.d,-k));
        now=PQ.top();
        //printf("New:(%d %d %d %d)\n",nxt.s,nxt.c,nxt.d,k);
    }
    while(PQ.size()){
        do{
            now=PQ.top();PQ.pop();
        }while(PQ.size()&&color[now.x][now.c][now.d>=MAX_Q?MAX_Q:now.d]);
        if(color[now.x][now.c][now.d])
            break;
        //printf("Now:(%d %d %d %d)\n",now.x,now.c,now.d,-now.sum);
        if(now.x==g)
            return -now.sum;
        color[now.x][now.c][now.d>=MAX_Q?MAX_Q:now.d]=true;
        for(Train nxt:adj[now.x]){
            if(now.c==nxt.c){
                if(color[nxt.s][nxt.c][((now.d+nxt.d)>=MAX_Q?MAX_Q:now.d+nxt.d)])
                    continue;
                j=search(nxt.d+now.d,nxt.c);
                k=0;
                i=search(now.d,nxt.c);
                if(i==j)
                    k+=nxt.d*info[nxt.c][j].r;
                else{
                    k+=(info[nxt.c][i].q-now.d)*info[nxt.c][i].r;
                    i++;
                    k+=info[nxt.c][j].sum-info[nxt.c][i].sum;
                    k+=(nxt.d+now.d-info[nxt.c][j-1].q)*info[nxt.c][j].r;
                }
                PQ.push(Data(nxt.s,nxt.c,now.d+nxt.d,now.sum-k));
                //printf("New:(%d %d %d %d)\n",nxt.s,nxt.c,now.d+nxt.d,-now.sum+k);
            }else{
                if(color[nxt.s][nxt.c][nxt.d>=MAX_Q?MAX_Q:nxt.d])
                    continue;
                j=search(nxt.d,nxt.c);
                k=0;
                k+=info[nxt.c][j].sum;
                k+=(nxt.d-(j-1>=0?info[nxt.c][j-1].q:0))*info[nxt.c][j].r;
                PQ.push(Data(nxt.s,nxt.c,nxt.d,now.sum-k));
                //printf("New:(%d %d %d %d)\n",nxt.s,nxt.c,nxt.d,-now.sum+k);
            }
        }
    }
    return -1;
}

int main(){
    int i,j,k,l;
    while(1){
        scanf("%d%d%d%d%d",&n,&m,&c,&s,&g);
        if(!(n||m||c||s||g))
            break;
        s--;g--;
        vector<Train> adj[MAX_N];
        while(m--){
            scanf("%d%d%d%d",&i,&j,&k,&l);
            i--;j--;l--;
            adj[i].push_back(Train(j,k,l));
            adj[j].push_back(Train(i,k,l));
        }
        rep(i,c)
            scanf("%d",&p[i]);
        rep(i,c){
            rep(j,p[i]-1){
                scanf("%d",&info[i][j].q);
                info[i][j].sum=0;
            }
            info[i][j].q=INF;
            info[i][j].sum=0;
            info[i][j+1].sum=0;
            rep(j,p[i]){
                scanf("%d",&info[i][j].r);
                info[i][j+1].sum=info[i][j].sum+info[i][j].q*info[i][j].r;
            }
        }
        printf("%d\n",dijk(adj));
    }
    return 0;
}
*/