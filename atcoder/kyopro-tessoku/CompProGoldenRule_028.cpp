/*アルゴリズムと工夫点(Blackboard/CPU: 14 ms Memory: 3872 KB  Length: 676 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MOD 10000
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    char t;
    i=0;
    scanf("%d",&n);
    while(n--){
        getchar();
        t=getchar();
        scanf("%d",&j);
        switch(t){
            case '+':
                i=((i%MOD)+(j%MOD))%MOD;
                break;
            case '-':
                i=(MOD+(i%MOD)-(j%MOD))%MOD;
                break;
            default :
                i=((i%MOD)*(j%MOD))%MOD;
                break;
        }
        printf("%d\n",i);
    }
    return 0;
}