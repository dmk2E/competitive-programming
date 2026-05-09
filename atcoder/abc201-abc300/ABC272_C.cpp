/*アルゴリズムと工夫点(Max Even/CPU: 36 ms Memory: 4612 KB  Length: 712 B)

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
    vector<int> even,odd;
    rep(i,n){
        scanf("%d",&j);
        if(j%2==0)even.push_back(j);
        else odd.push_back(j);
    }
    sort(even.begin(),even.end());
    sort(odd.begin(),odd.end());
    if(even.size()==1&&odd.size()==1){
        puts("-1");
        return 0;
    }
    if(even.size()>=2)i=even.back()+even[even.size()-2];
    else i=-1;
    if(odd.size()>=2)i=max(i,odd.back()+odd[odd.size()-2]);
    printf("%d\n",i);
    return 0;
}