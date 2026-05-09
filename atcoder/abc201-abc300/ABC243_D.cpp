/*アルゴリズムと工夫点(Moves on Binary Tree/CPU: 17 ms Memory: 5508 KB  Length: 769 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
ll x;
string s;

int main(){
    int i;
    scanf("%d%lld",&n,&x);
    cin>>s;
    vector<char> sta;
    rep(i,n){
        if(s[i]=='U'){
            if(sta.size()==0)x/=2;
            else sta.pop_back();
        }else
            sta.push_back(s[i]);      
    }
    rep(i,sta.size()){
        switch(sta[i]){
            case 'U':
                x/=2;
                break;
            case 'L':
                x=2*x;
                break;
            default:
                x=2*x+1;
                break;
        }
    }
    printf("%lld\n",x);
    return 0;
}