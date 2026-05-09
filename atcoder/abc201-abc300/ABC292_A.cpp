/*アルゴリズムと工夫点(CAPS LOCK/CPU: 1 ms Memory: 3680 KB  Length: 234 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

string s;

int main(){
    int i;
    cin>>s;
    rep(i,s.length()){
        printf("%c",toupper(s[i]));
    }
    puts("");
    return 0;
}