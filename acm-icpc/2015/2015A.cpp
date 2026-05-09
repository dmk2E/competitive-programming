/*アルゴリズムと工夫点(入学試験/CPU: 0 ms Memory: 3556 KB  Length: 591 B)
合格者数を決め，その時のギャップを計算し，解を求めればよい．
点数が降順に整列された状態で渡されるため，最悪計算量 O(M) < 10^3 となり十分高速．

※問題URL：https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1600
*/
//#include<iostream>
//#include<cassert>
#include<bits/stdc++.h>
#define rep(i,n)for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int m,n_min,n_max;

int main(){
    int i,j;
    while(1){
        scanf("%d%d%d",&m,&n_min,&n_max);
        if(!(m||n_min||n_max))break;
        vector<int> p(m);
        rep(i,m)scanf("%d",&p[i]);
        int max_diff=-1,ans=-1;
        for(i=n_max;i>=n_min;i--){
            if(max_diff<p[i-1]-p[i]){
                ans=i;
                max_diff=max(max_diff,p[i-1]-p[i]);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}