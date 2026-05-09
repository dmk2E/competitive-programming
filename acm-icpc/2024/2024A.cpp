/*アルゴリズムと工夫点(おやつは 300 円以内/CPU: 0 ms Memory: 3448 KB  Length: 407 B)
言われたとおりにシミュレーションする．
最悪計算量は，O(n)<10^3 となり十分高速．
※問題URL：https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1672&lang=ja
*/
//#include<iostream>
//#include<cassert>
#include<bits/stdc++.h>
#define rep(i,n)for(i=0;i<(int)(n);i++)
#define MAX_MONEY 300
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    while(1){
        scanf("%d",&n);
        if(!n)break;
        j=0;
        while(n--){
            scanf("%d",&i);
            if(j+i<=MAX_MONEY)j+=i;
        }
        printf("%d\n",j);
    }
    return 0;
}