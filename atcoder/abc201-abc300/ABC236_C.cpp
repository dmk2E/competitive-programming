/*アルゴリズムと工夫点(Route Map/CPU: 147 ms Memory: 14352 KB  Length: 555 B)

*/
#include<iostream>
#include<vector>
#include<map>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;
string ipt;

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    map<string,bool> isStop;
    vector<string> s;
    rep(i,n){
        cin>>ipt;
        isStop[ipt]=false;
        s.push_back(ipt);
    }
    rep(i,m){
        cin>>ipt;
        isStop[ipt]=true;
    }
    rep(i,n){
        printf("%s\n",isStop[s[i]]?"Yes":"No");
    }
    return 0;
}