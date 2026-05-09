/*アルゴリズムと工夫点(Lacked Number/CPU: 1 ms Memory: 3760 KB  Length: 363 B)

*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s;

int main(){
    int i;
    bool flag[10]={0};
    cin>>s;
    rep(i,s.length())flag[s[i]-'0']=true;
    rep(i,10)if(flag[i]==false){
        printf("%d\n",i);
    }
    return 0;
}