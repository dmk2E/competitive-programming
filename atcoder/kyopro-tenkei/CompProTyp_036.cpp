/*アルゴリズムと工夫点(/CPU: 40 ms Memory: 4588 KB  Length: 785 B)
マンハッタン距離がK以下の領域はひし形になっており,扱いにくい.そこで,45度回転を行う.こうすると,ある点(x,y)からのマンハッタン距離がk以下の領域は,x,y軸それぞれに平行な正方形になる.つまり,点(x,y)を中心とした正方形の線上
に存在する点は全て,(x,y)と同じ距離の点となる.この事から,2点(x1,y1),(x2,y2)間のマンハッタン距離は,45度回転した世界での2点(x1',x2'),(y1',y2')を用いて,max(|x1'-x2'|,|y1'-y2'|)となる.
※複素数の考えで,(x,y)->(1/√2)(x-y,x+y)とすることで,45度回転できるが,マンハッタン距離を出すだけなら,1/√2の部分は無視してよい.
*/
#include<iostream>
#include<climits>
#define MAX_N 100000
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

int n,q,x[MAX_N],y[MAX_N];

int main(){
    int i,j,minX=INT_MAX,minY=INT_MAX,maxX=INT_MIN,maxY=INT_MIN;
    scanf("%d%d",&n,&q);
    rep(i,n){
        scanf("%d%d",&x[i],&y[i]);
        j=x[i];
        x[i]=x[i]-y[i];
        y[i]=j+y[i];
        if(minX>x[i])
            minX=x[i];
        if(minY>y[i])
            minY=y[i];
        if(maxX<x[i])
            maxX=x[i];
        if(maxY<y[i])
            maxY=y[i];
    }
    while(q--){
        scanf("%d",&i);i--;
        printf("%lld\n",max(max(abs(maxX-(long long)x[i]),abs((long long)minX-x[i])),max(abs((long long)minY-y[i]),abs((long long)maxY-y[i]))));
    }
    return 0;
}