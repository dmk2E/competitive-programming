/*アルゴリズムと工夫点(AtCoder Magics/CPU: 78 ms Memory: 10236 KB  Length: 1684 B)

*/
#include<iostream>
#include<algorithm>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 200000
using namespace std;

typedef struct data{
    int id,a,c;

    data(int iid=0,int aa=0,int cc=0):id(iid),a(aa),c(cc){}

    bool operator<(const data& k)const{
        return a>k.a;
    }
}Data;

typedef struct ddata{
    int id,a,c;

    ddata(int iid=0,int aa=0,int cc=0):id(iid),a(aa),c(cc){}

    bool operator<(const ddata& k)const{
        return c<k.c;
    }
}DData;

bool flag[MAX_N]={0};
int n,id2C[MAX_N];
Data a[MAX_N];
DData c[MAX_N];
priority_queue<int> PQ;

int main(){
    int i,j;
    bool fflag[MAX_N]={0};
    scanf("%d",&n);
    rep(i,n){
        scanf("%d%d",&a[i].a,&a[i].c);
        c[i].a=a[i].a;
        c[i].c=a[i].c;
        a[i].id=c[i].id=i;
    }
    sort(a,a+n);
    sort(c,c+n);
    rep(i,n)
        id2C[c[i].id]=i;
    //rep(i,n)printf("%d %d\n",a[i].a,a[i].c);rep(i,n)printf("%d %d\n",c[i].a,c[i].c);rep(i,n)printf("%d ",id2C[i]);puts("");
    rep(i,n){
        j=id2C[a[i].id];
        flag[c[j].id]=true;
        j++;
        while(j<n&&flag[c[j].id]==false){
            flag[c[j].id]=true;
            PQ.push(c[j].id);
            //printf("j:%d\n",c[j].id);
            j++;
        }
    }
    while(PQ.size()>0){
        fflag[PQ.top()]=true;
        PQ.pop();
    }
    rep(i,n){
        if(fflag[i]==false)
            PQ.push(-i);
    }
    printf("%d\n",(int)PQ.size());
    if(PQ.size()>0){
        while(PQ.size()>1){
            printf("%d ",1-PQ.top());
            PQ.pop();
        }
        printf("%d\n",1-PQ.top());
    }
    return 0;
}