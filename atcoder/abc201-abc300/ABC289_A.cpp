/*アルゴリズムと工夫点(flip/CPU: 1 ms Memory: 3624 KB  Length: 288 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

string s;

int main(){
    int i;
    cin>>s;
    rep(i,s.length()){
        if(s[i]=='0')
            putchar('1');
        else
            putchar('0');
    }
    puts("");
    return 0;
}