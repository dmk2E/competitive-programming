/*アルゴリズムと工夫点(A Reverse/CPU: 5 ms Memory: 4048 KB  Length: 395 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int l,r;
string s;

int main(){
    int i,j;
    scanf("%d%d",&l,&r);
    cin>>s;
    l--;
    rep(i,l)printf("%c",s[i]);
    for(i=0;i<r-l;i++)printf("%c",s[r-1-i]);
    for(i=r;i<s.size();i++)printf("%c",s[i]);
    puts("");
    return 0;
}