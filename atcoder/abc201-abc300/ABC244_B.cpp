/*アルゴリズムと工夫点(Go Straight and Turn Right/CPU: 2 ms Memory: 4048 KB  Length: 504 B)

*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
string t;

int main(){
    int i,now,y,x;
    scanf("%d",&n);
    cin>>t;
    const int dx[]={1,0,-1,0},dy[]={0,-1,0,1},MAX_D=4;
    y=x=now=0;
    rep(i,n){
        if(t[i]=='R')now=(now+1)%MAX_D;
        else{
            y+=dy[now];
            x+=dx[now];
        }
    }
    printf("%d %d\n",x,y);
    return 0;
}