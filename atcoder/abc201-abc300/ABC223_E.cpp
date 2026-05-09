/*アルゴリズムと工夫点(Placing Rectangles/CPU: 2 ms Memory: 3856 KB  Length: 728 B)
・n個の長方形の配置の種類は以下のように分類できる:
<i>n=2の時，x軸またはy軸と平行な1本の直線で分けられた2つの領域それぞれに長方形が存在するように配置できる．
<ii>n=3の時，
・x軸またはy軸のどちらかと平行な2本の直線で分けられた2つの領域それぞれに長方形が存在するように配置できる(1|2|3)．
・x軸に平行な直線1本と，y軸に平行な直線1本を組み合わせてT字型に分けた3つの領域それぞれに長方形が存在するように配置できる．
<iii>n>=4の時，例外があって難しい．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int x,y;
ll a,b,c;

bool parallelJudge(int h,int w,ll a,ll b,ll c){
    return (a+w-1)/w+(b+w-1)/w+(c+w-1)/w<=h;
}

bool tJudge(int h,int w,ll a,ll b,ll c){
    if((a+h-1)/h>=w)return false;
    ll ww=w-(a+h-1)/h;
    return (b+ww-1)/ww+(c+ww-1)/ww<=h;
}

int main(){
    int i,j;
    scanf("%d%d%lld%lld%lld",&x,&y,&a,&b,&c);
    if(parallelJudge(x,y,a,b,c)||parallelJudge(y,x,a,b,c)||tJudge(x,y,a,b,c)||tJudge(x,y,b,c,a)||tJudge(x,y,c,a,b)||tJudge(y,x,a,b,c)||tJudge(y,x,b,c,a)||tJudge(y,x,c,a,b))
        puts("Yes");
    else
        puts("No");
    return 0;
}