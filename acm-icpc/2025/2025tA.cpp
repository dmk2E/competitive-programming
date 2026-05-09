/*アルゴリズムと工夫点(Mex Prize/CPU: ? ms Memory: ? KB  Length: - B)
aの初項が1でなければ1を出力する．
そうでなければ，前の要素から値が連続していない地点を見つけて，mex値を出力する．
1テストケース当たりの最悪計算量は，O(N)<10^6 となり十分高速．
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
        vector<int> a(n);
        rep(i,n)scanf("%d",&a[i]);
        if(a[0]!=1){
            puts("1");
        }else{
            rep(i,n-1)if(a[i+1]-a[i]>1)break;
            printf("%d\n",a[i]+1);
        }
    }
    return 0;
}