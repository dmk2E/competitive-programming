/*アルゴリズムと工夫点(A Unique Letter/CPU: 7 ms Memory: 3676 KB  Length: 446 B)

*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_ALFA 26
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s;
int alfa[MAX_ALFA]={0};

int main(){
    int i;
    cin>>s;
    rep(i,s.length())alfa[s[i]-'a']++;
    rep(i,MAX_ALFA)
        if(alfa[i]==1){
            printf("%c\n",'a'+i);
            return 0;
        }
    puts("-1");
    return 0;
}