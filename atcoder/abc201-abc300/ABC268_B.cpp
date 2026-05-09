/*アルゴリズムと工夫点(Prefix?/CPU: 1 ms Memory: 3648 KB  Length: 392 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s,t;

int main(){
    int i,j,ss=0,tt=0;
    cin>>s>>t;
    if(s.length()>t.length()){
        puts("No");
        return 0;
    }
    rep(i,s.length())if(s[i]!=t[i])break;
    printf("%s\n",i==s.length()?"Yes":"No");
    return 0;
}