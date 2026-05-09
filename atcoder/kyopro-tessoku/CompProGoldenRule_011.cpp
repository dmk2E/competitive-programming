/*アルゴリズムと工夫点(Binary Search 1/CPU: 10 ms Memory: 3940 KB  Length: 548 B)
標準ライブラリのlower_boundを使うとより短いコードで書ける．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,x;

int main(){
    int i,left,right,mid;
    scanf("%d%d",&n,&x);
    vector<int> a(n);
    rep(i,n)scanf("%d",&a[i]);
    left=0;right=n;
    while(left<right){
        mid=(left+right)/2;
        if(a[mid]==x)
            break;
        else if(a[mid]<x)
            left=mid+1;
        else
            right=mid;
    }
    printf("%d\n",mid+1);
    return 0;
}