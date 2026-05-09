/*アルゴリズムと工夫点(Coverage/CPU: 2 ms Memory: 3932 KB  Length: 748 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

int n,m;
vector<int> a;

bool judge(int s){
    int now=0,tmp=0;
    while((1<<now)<=s){
        //printf("now:%d s:%d %d\n",now,s,tmp);
        if((1<<now)&s)
            tmp|=a[now];
        now++;
    }
    //printf("now:%d s:%d %d\n",now,s,tmp);
    return tmp==(1<<n)-1;
}

int main(){
    int i,j,k;
    scanf("%d%d",&n,&m);
    a=vector<int>(m,0);
    rep(i,m){
        scanf("%d",&j);
        while(j--){
            scanf("%d",&k);
            a[i]|=1<<(k-1);
        }
        //printf("%d:%d\n",i,a[i]);
    }
    k=0;
    rep(i,1<<m){
        k+=judge(i);
    }
    printf("%d\n",k);
    return 0;
}