/*アルゴリズムと工夫点(Manga/CPU: 49 ms Memory: 4560 KB  Length: 872 B)
かなり考察を求められる，見た目以上に難しい問題だった...
※1WAで撃沈...(2,2,3,4)みたいなケースで落ちた?
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,nxt,cnt;
    scanf("%d",&n);
    vector<int> a(n);
    rep(i,n)scanf("%d",&a[i]);
    sort(a.begin(),a.end());
    nxt=a[i=0];
    cnt=-1;
    while(i<n){
        if(nxt==a[i])cnt++;
        else nxt=a[i];
        i++;
    }
    i=0;
    nxt=1;
    a.erase(unique(a.begin(),a.end()),a.end());
    n=a.size();
    while(i<n){
        if(a[i]==nxt)
            i++;
        else if(cnt>=2)
            cnt-=2;
        else if(cnt==1){
            cnt-=1;
            n--;
        }else if(n-i>=2)
            n-=2;
        else
            break;
        nxt++;
    }
    printf("%d\n",nxt-1+cnt/2);
    return 0;
}