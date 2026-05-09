/*アルゴリズムと工夫点(2025/CPU: ? ms Memory: ? KB  Length: - B)
九九を全て計算し，総和を求める．
最悪計算量は，O(n^2)≒10^4 となり十分高速．
*/
#include<iostream>
#include<cassert>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<list>
#include<algorithm>
// #include<bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    while(1){
        scanf("%d",&n);
        if(!n)break;
        int ans=0;
        rep(i,n)rep(j,n){
            ans+=(i+1)*(j+1);
        }
        printf("%d\n",ans);
    }
    return 0;
}