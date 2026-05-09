/*アルゴリズムと工夫点(Rectangle Detection/CPU: 1 ms Memory: 3816 KB  Length: 558 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int main(){
    const int MAX=10,MIN=0;
    int i,j,a,b,c,d;
    a=c=MAX+1;
    b=d=MIN-1;
    string ipt;
    rep(i,10){
        cin>>ipt;
        rep(j,ipt.size()){
            if(ipt[j]=='#'){
                a=min(a,i);
                b=max(b,i);
                c=min(c,j);
                d=max(d,j);
            }
        }
    }
    printf("%d %d\n%d %d\n",a+1,b+1,c+1,d+1);
    return 0;
}