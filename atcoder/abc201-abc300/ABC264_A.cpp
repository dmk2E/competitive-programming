/*アルゴリズムと工夫点("atcoder".substr()/CPU: 2 ms Memory: 3896 KB  Length: 285 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int l,r;
string str="atcoder";

int main(){
    scanf("%d%d",&l,&r);
    for(l--;l<r;l++)putchar(str[l]);
    puts("");
    return 0;
}