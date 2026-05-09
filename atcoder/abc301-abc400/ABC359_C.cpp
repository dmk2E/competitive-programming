/*アルゴリズムと工夫点(Tile Distance 2/CPU: 1 ms Memory: 3900 KB  Length: 870 B)
始点が原点となるように始点と終点の平行移動を行ったり，対称性を利用して終点のyやxを対象移動させることで，進行方向を固定し，考えやすくする手法がきちんとできるよう，心がけていきたい．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

long long sx,sy,tx,ty;

int main(){
    int i,j;
    long long ans=0;
    scanf("%lld%lld%lld%lld",&sx,&sy,&tx,&ty);
    if(sx%2!=sy%2)
        sx-=1;
    if(tx%2!=ty%2)
        tx-=1;
    if(tx-sx<0){
        swap(sy,ty);
        swap(sx,tx);   
    }
    tx-=sx;ty-=sy;
    sx=sy=0;
    if(ty<0)ty=-ty;
    //printf("sy:%lld sx:%lld ty:%lld tx:%lld\n",sy,sx,ty,tx);
    if(abs(ty-sy)<abs(tx-sx)){
        if(abs(ty-sy)>0){
            ans+=abs(ty-sy);
            sx+=abs(ty-sy);
            sy+=abs(ty-sy);
        }
        ans+=abs(tx-sx)/2;
    }else{
        if(abs(tx-sx)>0){
            ans+=abs(tx-sx);
            sy+=abs(tx-sx);
            sx+=abs(tx-sx);
        }
        ans+=abs(ty-sy);
    }
    printf("%lld\n",ans);
    return 0;
}