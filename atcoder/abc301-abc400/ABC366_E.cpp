/*アルゴリズムと工夫点(Manhattan Multifocal Ellipse/CPU: 787 ms Memory: 85360 KB  Length: 1300 B)
シグマの分配により，x,yそれぞれ独立に考えることができるから，考えるべきx,yの範囲-2e6~2e6より，範囲の内の全てのx,yに対して，(a,b)=(Σ|x-xi|,Σ|y-yi|)の値を計算し，a[i]+b[j]<=dとなる(i,j)の組を数え上げる問題に帰着させる．
※複数の変数があると考えずらい→変数をそれぞれ独立にできないか考えてみる
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_X (int)(2e6)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,d;
vector<int> x,y;

int count(int x,vector<int>& a){
    int left=0,mid,right=a.size();
    while(left<right){
        mid=(left+right)/2;
        if(a[mid]<=x)
            left=mid+1;
        else
            right=mid;
    }
    return left-(a.size()-left);
}

vector<ll> f(vector<int>& x){
    int i;
    ll ans=0;
    vector<ll> a;
    rep(i,x.size())
        ans+=x[i];
    a.push_back(ans);
    for(i=1;i<=2*MAX_X;i++){
        //printf("%d:%lld\n",i-1,ans);
        ans+=count(i-1,x);
        a.push_back(ans);
    }
    return a;
}

int main(){
    int i,j;
    ll ans=0;
    scanf("%d%d",&n,&d);
    x=vector<int>(n);
    y=vector<int>(n);
    rep(i,n){
        scanf("%d%d",&x[i],&y[i]);
        x[i]+=MAX_X;
        y[i]+=MAX_X;
    }
    sort(x.begin(),x.end());
    sort(y.begin(),y.end());
    vector<ll> a=f(x),b=f(y);
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    j=b.size()-1;
    rep(i,a.size()){
        while(j>=0&&a[i]+b[j]>d)j--;
        ans+=j+1;
    }
    printf("%lld\n",ans);
    return 0;
}