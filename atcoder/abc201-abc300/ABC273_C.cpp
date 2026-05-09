/*アルゴリズムと工夫点((K+1)-th Largest Number/CPU: 65 ms Memory: 5704 KB  Length: 550 B)

*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> a(n);
    rep(i,n)scanf("%d",&a[i]);
    vector<int> b=a;
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    vector<int> k2Cnt(n,0);
    rep(i,n)k2Cnt[(int)(b.end()-upper_bound(b.begin(),b.end(),a[i]))]++;
    rep(i,n)printf("%d\n",k2Cnt[i]);
    return 0;
}