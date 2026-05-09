/*アルゴリズムと工夫点(Four Points/CPU: 1 ms Memory: 3872 KB  Length: 651 B)

*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int main(){
    int i,j,vx,vy,wx,wy;
    vector<int> x(3),y(3);
    rep(i,3)scanf("%d%d",&x[i],&y[i]);
    auto dot=[](int x1,int y1,int x2,int y2)->int{
        return x1*x2+y1*y2;
    };
    rep(i,3){
        vx=x[(i+1)%3]-x[i];
        vy=y[(i+1)%3]-y[i];
        wx=x[(i+2)%3]-x[i];
        wy=y[(i+2)%3]-y[i];
        if(dot(vx,vy,wx,wy)==0){
            printf("%d %d\n",x[i]+vx+wx,y[i]+vy+wy);
            return 0;
        }
    }
    return 0;
}