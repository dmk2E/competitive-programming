/*アルゴリズムと工夫点(Qualification Contest/CPU: 1 ms Memory: 3852 KB  Length: 418 B)

*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int n,k;

int main(){
    int i,j;
    string str;
    vector<string> tmp;
    scanf("%d%d",&n,&k);
    rep(i,k){
        cin>>str;
        tmp.push_back(str);
    }
    sort(tmp.begin(),tmp.end());
    rep(i,k)
        cout<<tmp[i]<<endl;
    return 0;
}