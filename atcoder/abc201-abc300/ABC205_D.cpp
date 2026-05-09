/*アルゴリズムと工夫点(Kth Excluded/CPU: 128 ms Memory: 8432 KB  Length: 1327 B)
以下のアルゴリズムで解ける。
<i>現在のkの値に対して、0~kまでに含まれる正整数列Aの要素の数がxである時、kをk+xに更新する。
<ii>更新されたkの値に対して、更新前後の0~kまでに含まれる正整数列Aの要素の数に変化が起こらなくなるまで、kの値を更新し続ける。
このアルゴリズムを用いるためには、0~xに含まれる正整数列Aの要素の数の累積和sumを保持しておく必要がある。しかし、aの要素の値は最大で10^18となり、メモリが足りなくなってしまう。そこで、sumの座標を圧縮した上で保持し、
0~xに含まれる正整数列Aの要素の数はsum上で二分探索を用いることで求める。最悪計算量は、O(N+Q*log2(N))<10^7 となり、高速。
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 100000
using namespace std;

int n,q,nxt=0;
long long a,k,i2A[3*MAX_N+1],sum[3*MAX_N+1];

long long a2Sum(long long x){//0~xまでの範囲に何個の正整数列Aの値が存在するか
    int left,right,mid;
    left=0;right=nxt-1;
    while(left<right){
        mid=(left+right)/2;
        if(i2A[mid]<=x)
            left=mid+1;
        else
            right=mid;
    }
    return sum[left];
}

int main(){
    int i,j;
    long long temp;
    scanf("%d%d",&n,&q);
    scanf("%lld",&a);
    i2A[nxt]=a-1;
    sum[nxt++]=0;
    i2A[nxt]=a;
    sum[nxt++]=0;
    i2A[nxt]=a+1;
    sum[nxt++]=1;
    rep(i,n-1){
        scanf("%lld",&a);
        if(i2A[nxt-1]<a-1){
            i2A[nxt]=a-1;
            sum[nxt++]=0;
        }
        if(i2A[nxt-1]<a){
            i2A[nxt]=a;
            sum[nxt++]=0;
        }
        i2A[nxt]=a+1;
        sum[nxt++]=1;
    }
    rep(i,nxt)
        sum[i+1]+=sum[i];
    //rep(i,nxt-1)printf("%lld ",i2A[i]);printf("%lld\n",i2A[i]);
    //rep(i,nxt-1)printf("%lld ",sum[i]);printf("%lld\n",sum[i]);
    while(q--){
        scanf("%lld",&k);
        k+=(a=a2Sum(k));
        while(a2Sum(k)-a>0){
            temp=a;
            a=a2Sum(k);
            k+=a-temp;
        }
        printf("%lld\n",k);
    }
    return 0;
}