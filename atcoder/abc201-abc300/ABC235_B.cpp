/*アルゴリズムと工夫点(Climbing Takahashi/CPU: 11 ms Memory: 3952 KB  Length: 395 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> h(n);
    rep(i,n)scanf("%d",&h[i]);
    i=0;
    while(i<n-1){
        if(h[i]>=h[i+1])break;
        i++;
    }
    printf("%d\n",h[i]);
    return 0;
}