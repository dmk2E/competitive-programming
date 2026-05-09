/*アルゴリズムと工夫点(Knight Fork/CPU: 1 ms Memory: 3888 KB  Length: 533 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

ll x1,yy1,x2,y2;

int main(){
    ll x,y;
    scanf("%lld%lld%lld%lld",&x1,&yy1,&x2,&y2);
    for(x=x1-5;x<x1+6;x++){
        for(y=yy1-5;y<yy1+6;y++){
            if((x1-x)*(x1-x)+(yy1-y)*(yy1-y)==5&&(x2-x)*(x2-x)+(y2-y)*(y2-y)==5){
                puts("Yes");
                return 0;
            }
        }
    }
    puts("No");
    return 0;
}