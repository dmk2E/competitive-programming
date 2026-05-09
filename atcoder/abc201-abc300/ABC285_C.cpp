/*アルゴリズムと工夫点(abc285_brutmhyhiizp/CPU: 3 ms Memory: 3832 KB  Length: 464 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_S 13
using namespace std;
typedef long long ll;

ll count[MAX_S];
string s;

int main(){
    int i,j;
    ll sum=0;
    count[0]=1;
    for(i=1;i<MAX_S;i++)
        count[i]=26*count[i-1];
    cin>>s;
    rep(i,s.length())
        sum+=count[i];

    rep(i,s.length()){
        sum+=(s[i]-'A')*count[s.length()-i-1];
    }
    printf("%lld\n",sum);
    return 0;
}