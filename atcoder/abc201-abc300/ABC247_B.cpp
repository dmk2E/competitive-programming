/*アルゴリズムと工夫点(Unique Nicknames/CPU: 1 ms Memory: 3788 KB  Length: 687 B)

*/
#include<iostream>
#include<vector>
#include<map>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    map<string,int> dicS,dicT;
    vector<string> s(n),t(n);
    rep(i,n){
        cin>>s[i]>>t[i];
        dicS[s[i]]++;
        dicT[t[i]]++;
    }
    rep(i,n){
        if(s[i]!=t[i]&&((dicS[s[i]]+dicT[s[i]]<=1)||(dicS[t[i]]+dicT[t[i]]<=1)))continue;
        if(s[i]==t[i]&&((dicS[s[i]]+dicT[s[i]]<=2)||(dicS[t[i]]+dicT[t[i]]<=2)))continue;
        puts("No");
        return 0;
    }
    puts("Yes");
    return 0;
}