/*アルゴリズムと工夫点(Multi Test Cases/CPU: 2 ms Memory: 3812 KB  Length: 370 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int t,n;

int main(){
    int i,cnt;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        cnt=0;
        while(n--){
            scanf("%d",&i);
            cnt+=(i%2==1);
        }
        printf("%d\n",cnt);
    }
    return 0;
}