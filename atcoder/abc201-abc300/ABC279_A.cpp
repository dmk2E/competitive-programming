/*アルゴリズムと工夫点(wwwvvvvvv/CPU: 1 ms Memory: 3732 KB  Length: 348 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s;

int main(){
    int i,cnt=0;
    cin>>s;
    rep(i,s.length()){
        if(s[i]=='w')
            cnt+=2;
        else
            cnt+=1;
    }
    printf("%d\n",cnt);
    return 0;
}