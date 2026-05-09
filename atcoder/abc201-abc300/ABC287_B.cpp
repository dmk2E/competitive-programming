/*アルゴリズムと工夫点(/CPU:  ms Memory:  KB  Length:  B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int n,m;
vector<string> s,t;

int main(){
    int i,cnt=0,j;
    string tmp;
    scanf("%d%d",&n,&m);
    rep(i,n){
        cin>>tmp;
        s.push_back(tmp);
    }
    rep(i,m){
        cin>>tmp;
        t.push_back(tmp);
    }
    rep(i,n){
        tmp=s[i].substr(s[i].length()-3,3);
        rep(j,m)
            if(t[j]==tmp)
                break;
        if(j<m)
            cnt++;
    }
    printf("%d\n",cnt);
    return 0;
}