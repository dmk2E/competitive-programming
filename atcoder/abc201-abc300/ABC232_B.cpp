/*アルゴリズムと工夫点(Caesar Cipher/CPU: 3 ms Memory: 3780 KB  Length: 509 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s,t;

int main(){
    int i,j;
    const int ALFA=26;
    cin>>s>>t;
    string ss=s;
    rep(i,ALFA){
        rep(j,s.length()){
            ss[j]=((s[j]-'a'+i)%ALFA)+'a';
            if(ss[j]!=t[j])break;
        }
        if(j==(int)s.length()){
            puts("Yes");
            return 0;
        }
    }
    puts("No");
    return 0;
}