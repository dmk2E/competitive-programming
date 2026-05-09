/*アルゴリズムと工夫点(Election/CPU: 1 ms Memory: 3784 KB  Length: 525 B)

*/
#include<iostream>
#include<map>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    string tmp;
    scanf("%d",&n);
    map<string,int> v;
    rep(i,n){
        cin>>tmp;
        if(v.find(tmp)==v.end())v[tmp]=1;
        else v[tmp]++;
    }
    j=-1;
    for(auto d:v){
        if(j<d.second){
            tmp=d.first;
            j=d.second;
        }
    }
    cout<<tmp<<'\n';
    return 0;
}