/*アルゴリズムと工夫点(Pond/CPU: 93 ms Memory: 8916 KB  Length: 1141 B)
多分,二分探索で解ける最高難易度の問題.
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 800
using namespace std;

int n,k,a[MAX_N][MAX_N];

int f(int ly,int lx,int ry,int rx,int sum[][MAX_N+1]){
    return sum[ry+1][rx+1]-sum[ry+1][lx]-sum[ly][rx+1]+sum[ly][lx];
}

bool judge(int x){
    //printf("%d\n",x);
    int i,j,sum[MAX_N+1][MAX_N+1]={0};
    rep(i,n)
        rep(j,n)
            sum[i+1][j+1]=sum[i+1][j]+sum[i][j+1]-sum[i][j]+(a[i][j]>x?1:0);
    for(i=0;i+k-1<n;i++){
        for(j=0;j+k-1<n;j++){
            //printf("f(%d,%d,%d,%d)=%d\n",i,j,i+k-1,j+k-1,f(i,j,i+k-1,j+k-1,sum));
            if(f(i,j,i+k-1,j+k-1,sum)<=k*k/2)
                return true;
        }
    }
    return false;
}

int main(){
    int i,j,left,right,mid=-1;
    scanf("%d%d",&n,&k);
    rep(i,n)
        rep(j,n){
            scanf("%d",&a[i][j]);
            if(mid<a[i][j])
                mid=a[i][j];
        }
    left=0;right=mid+1;
    while(left<right){
        mid=(left+right)/2;
        if(judge(mid))
            right=mid;
        else
            left=mid+1;
    }
    printf("%d\n",left);
    return 0;
}