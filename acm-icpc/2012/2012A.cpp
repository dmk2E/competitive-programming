/*アルゴリズムと工夫点(ミレニアム/CPU: 0 ms Memory: 3396 KB  Length: 483 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define NORMAL 195
#define THREE 200
using namespace std;

int n,y,m,d;

int main(){
    int cnt,sum,mil=(999-333)*NORMAL+333*THREE+1;
    scanf("%d",&n);
    while(n--){
        scanf("%d%d%d",&y,&m,&d);
        cnt=(y-1)/3;
        sum=(y-1-cnt)*NORMAL+cnt*THREE+d;
        if(y%3==0)
            sum+=(m-1)*20;
        else
            sum+=(m-1)/2*19+(m-1-(m-1)/2)*20;
        printf("%d\n",mil-sum);
    }
    return 0;
}