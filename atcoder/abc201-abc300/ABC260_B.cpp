/*アルゴリズムと工夫点(Better Students Are Needed!/CPU: 2 ms Memory: 3900 KB  Length: 1001 B)

*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int n,x,y,z;

int main(){
    int i,j;
    scanf("%d%d%d%d",&n,&x,&y,&z);
    vector<int> a(n),b(n),num(n),ans;
    rep(i,n)scanf("%d",&a[i]);
    rep(i,n)scanf("%d",&b[i]);
    rep(i,n)num[i]=i;
    sort(num.begin(),num.end(),[&](int i,int j)->bool{
        return a[i]==a[j]?i<j:a[i]>a[j];
    });
    rep(i,x)ans.push_back(num[i]+1);
    j=i;
    sort(num.begin()+j,num.end(),[&](int i,int j)->bool{
        return b[i]==b[j]?i<j:b[i]>b[j];
    });
    rep(i,y)ans.push_back(num[j++]+1);
    sort(num.begin()+j,num.end(),[&](int i,int j)->bool{
        return a[i]+b[i]==a[j]+b[j]?i<j:a[i]+b[i]>a[j]+b[j];
    });
    rep(i,z)ans.push_back(num[j++]+1);
    sort(ans.begin(),ans.end());
    rep(i,ans.size())printf("%d\n",ans[i]);
    return 0;
}