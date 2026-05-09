/*アルゴリズムと工夫点(kasaka/CPU: 14 ms Memory: 5404 KB  Length: 530 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s;

int main(){
    int i,j,l,r;
    cin>>s;
    rep(l,s.length())if(s[l]!='a')break;
    rep(i,s.length())if(s[(int)s.length()-1-i]!='a')break;
    if(l>i){
        puts("No");
        return 0;
    }
    r=s.length()-1-i;
    while(l<=r){
        if(s[l++]!=s[r--]){
            puts("No");
            return 0;
        }
    }
    puts("Yes");
    return 0;
}