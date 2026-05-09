/*アルゴリズムと工夫点(Max MEX/CPU: 61 ms Memory: 4620 KB  Length: 689 B)

*/
#include<iostream>
#include<algorithm>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

int n,k;

bool search(int x,vector<int>& a){
    int left=0,right=n,mid;
    while(left<right){
        mid=(left+right)/2;
        if(a[mid]==x)
            return true;
        else if(a[mid]<x)
            left=mid+1;
        else
            right=mid;
    }
    return left<n&&a[left]==x;
}

int main(){
    int i;
    scanf("%d%d",&n,&k);
    vector<int> a(n);
    rep(i,n)
        scanf("%d",&a[i]);
    sort(a.begin(),a.end());
    rep(i,k){
        if(!search(i,a))
            break;
    }
    printf("%d\n",i);
    return 0;
}