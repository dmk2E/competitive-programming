/*アルゴリズムと工夫点(National Railway/CPU: 119 ms Memory: 19544 KB  Length: 1718 B)
f=Aij+Akl+C*(|i-k|+|j-l|)の最小値を求める必要がある.ここで,i<=k,j<=lと条件を固定すると,絶対値が外れて,f=[Aij-C*(i+j)]+[Akl+C*(k+l)] となり,(i,j)と(k,l)それぞれ独立に考えることができる.
ただし,これだけでは左斜め方向に位置する場合に対応できないから,90度回転させてからもう一度行うようにする.
Aklを固定した時の,最小の[Aij+C*(i+j)]を求める.これは矩形区間の最小値を求める作業ととなるが,これは累積和のようなDPで対応できる.
*/
#include<iostream>
#include<climits>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_H 1000
#define MAX_W 1000
#define MAX_MIN ((long long)(1e13))
using namespace std;

int h,w,c,a[MAX_H][MAX_W];
long long dp[MAX_H+1][MAX_W+1]={0};

void rotate(int a[MAX_H][MAX_W]){
    int i,j,b[MAX_H][MAX_W];
    if(h<=w){
        rep(i,h)
            rep(j,w)
                b[j][w-1-i]=a[i][j];
        rep(i,w)
            rep(j,h)
                a[i][j]=b[i][j+w-h];
    }else{
        rep(i,h)
            rep(j,w)
                b[h-1-j][i]=a[i][j];
        rep(i,w)
            rep(j,h)
                a[i][j]=b[i+h-w][j];
    }
    swap(h,w);
}

long long Min(long long a,long long b){
    return a<b?a:b;
}

long long ans(){
    int i,j;
    long long mmin=MAX_MIN,temp;
    rep(i,h+1)
        dp[i][0]=MAX_MIN;
    rep(j,w+1)
        dp[0][j]=MAX_MIN;
    rep(i,h)
        rep(j,w)
            dp[i+1][j+1]=min(a[i][j]-(long long)c*(i+j),min(dp[i][j+1],dp[i+1][j]));
    //rep(i,h){rep(j,w)printf("%lld ",dp[i+1][j+1]);puts("");}
    rep(i,h)
        rep(j,w){
            if(mmin>(temp=a[i][j]+(long long)c*(i+j)+min(dp[i][j+1],dp[i+1][j])))
                mmin=temp;
            //printf("%lld\n",temp);
        }
    return mmin;
}

void show(){
    int i,j;
    rep(i,h){
        rep(j,w)
            printf("%d ",a[i][j]);
        puts("");
    }
}

int main(){
    int i,j;
    long long mmin;
    scanf("%d%d%d",&h,&w,&c);
    rep(i,h)
        rep(j,w)
            scanf("%d",&a[i][j]);
    //show();
    mmin=ans();
    //printf("%lld\n",mmin);
    rotate(a);
    //show();
    printf("%lld\n",min(mmin,ans()));
    return 0;
}