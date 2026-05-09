/*アルゴリズムと工夫点(Many A+B Problems/CPU: 1 ms Memory: 3876 KB  Length: 266 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    while(n--){
        scanf("%d%d",&i,&j);
        printf("%d\n",i+j);
    }
    return 0;
}