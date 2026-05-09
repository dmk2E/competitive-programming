/*アルゴリズムと工夫点(Doukasen/CPU: 16 ms Memory: 7528 KB  Length: 1630 B)
「ある時刻tにおいて，2つの火がぶつかっているか」の判定は，前処理でaの累積和，各導線が燃えるにかかる時間の累積和それぞれを，逆Verも合わせて前処理で求めておけば，O(log2(N))で求めることができる．
また，ある時刻tにおいて2つの火がぶつかっていれば，時刻t以降ももう2つの火はぶつかっていることが確定し，ぶつかっていなければ時刻t以前もぶつかっていないことが確定する．つまり単調性がある．
従って，2つの火がぶつかっている時刻tを二分探索で求め，それを元にその時点での左側からの火の位置を求め，出力する．
最悪計算量はO(N+log2(sum(Ai/Bi))*log2(N))
※初見3完...
※2つの火がぶつかる時刻が，単純に時間の総和の半分だとは...
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define EPS (1e-7) //(1e-10)にするとTLEしてしまう
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
vector<int> a,aSum,b;

double t2X(double t,vector<int>& aSum,vector<int>& b,vector<double>& timeSum){
    //printf("t:%.5f ",t);
    int i,left,right,mid;
    double ans;
    left=0;right=n+1;
    while(left<right){
        mid=(left+right)/2;
        if(timeSum[mid]<=t)
            left=mid+1;
        else
            right=mid;
    }
    t-=timeSum[left-1];
    //printf("ans:%.5f\n",aSum[left-1]+(left-1<n?b[left-1]*t:0));
    return aSum[left-1]+(left-1<n?b[left-1]*t:0);
}

int main(){
    int i,j,k;
    scanf("%d",&n);
    a=vector<int>(n);
    b=vector<int>(n);
    aSum=vector<int>(n+1,0);
    vector<double> time(n);
    vector<int> aSumR(n),bRev(n);
    rep(i,n){
        scanf("%d%d",&a[i],&b[i]);
        time[i]=(double)a[i]/b[i];
        aSum[i+1]=a[i]+aSum[i];
        bRev[n-1-i]=b[i];
    }
    vector<double> timeSum(n+1,0),timeSumR(n+1,0);
    rep(i,n)
        timeSum[i+1]=time[i]+timeSum[i];
    rep(i,n){
        timeSumR[i+1]=time[n-1-i]+timeSumR[i];
        aSumR[i+1]=aSumR[i]+a[n-1-i];
    }
    //printf("time:");rep(i,n)printf("%.8f ",time[i]);puts("");
    double left=0,right=timeSum[n]+EPS,mid;
    while(right-left>EPS){
        mid=(left+right)/2;
        if(aSum[n]-t2X(mid,aSumR,bRev,timeSumR)-t2X(mid,aSum,b,timeSum)>EPS)
            left=mid+EPS;
        else
            right=mid;
    }
    printf("%.7f\n",t2X(left,aSum,b,timeSum));
    return 0;
}