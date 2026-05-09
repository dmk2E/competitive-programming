#include<bits/stdc++.h>
#define rep(i,n)for(i=0;i<(int)n;i++)
#define MAX_MIN (-(long long)(1e18))
using namespace std;

typedef struct game{
    int a,b;

    game(int aa=0,int bb=0):a(aa),b(bb){}

    bool operator<(const game& k)const{
        return a==k.a?b>k.b:a<k.a;
    }
}Game;

int n,d;

int main(){
    int i,j;
    Game first,second;
    long long now,mmax;
    while(1){
        scanf("%d%d",&n,&d);
        if(!(n||d))break;
        vector<Game> ipt(n);
        rep(i,n)
            scanf("%d%d",&ipt[i].a,&ipt[i].b);
        sort(ipt.begin(),ipt.end());
        first=ipt[n-1];
        if(n==1){
            printf("%lld\n",(long long)d*((long long)first.a+first.b)-(long long)d*(d+1)*first.b/2);
        }else{
            second=ipt[n-2];
            now=0;
            mmax=(long long)first.a*((d+1)/2)+(long long)second.a*(d/2);
            rep(i,d){
                //printf("i:%d now:%lld\n",i,now);
                j=d-i;
                if(i%2==0){
                    //printf("if(%lld<%lld)\n",(long long)first.a*((j+1)/2)+(long long)second.a*(j/2),(long long)j*((long long)first.a+first.b)-(long long)j*(j+1)*first.b/2);
                    if(mmax<now+(long long)j*((long long)first.a+first.b)-(long long)j*(j+1)*first.b/2){
                        mmax=now+(long long)j*((long long)first.a+first.b)-(long long)j*(j+1)*first.b/2;
                    }
                    now+=first.a;
                }else if(i%2==1){
                    if(mmax<now+(long long)j*((long long)first.a)-(long long)j*(j+1)*first.b/2){
                        mmax=now+(long long)j*((long long)first.a)-(long long)j*(j+1)*first.b/2;
                    }
                    now+=second.a;
                }
            }
            printf("%lld\n",mmax);
        }
    }
    return 0;
}