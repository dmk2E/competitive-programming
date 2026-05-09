/*アルゴリズムと工夫点(Min Difference/CPU: 77 ms Memory: 5700 KB  Length: 973 B)
絶対値の最小値は，絶対値の中身の値の正負が逆転する瞬間に着目すればよい．
数列A,Bは，それぞれ昇順にソートしておけば，Aiを固定した時の|Ai-Bj|は，二分探索で求めることができる．
したがって，最悪計算量はO(M*log2(M)+N*log2(M))<10^7 となり，十分高速．
*/
#include<iostream>
#include<algorithm>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_MIN (int)(1e9)
using namespace std;

int n,m;

int search(int a,vector<int>& b){
    int left=0,right=b.size(),mid;
    while(left<right){
        mid=(left+right)/2;
        if(a-b[mid]>=0)
            left=mid+1;
        else
            right=mid;
    }
    mid=MAX_MIN;
    if(left<b.size())
        mid=abs(a-b[left]);
    if(left-1>=0&&mid>abs(a-b[left-1]))
        mid=abs(a-b[left-1]);
    return mid;
}

int main(){
    int i,j,mmin;
    scanf("%d%d",&n,&m);
    vector<int> a,b;
    rep(i,n){
        scanf("%d",&j);
        a.push_back(j);
    }
    rep(i,m){
        scanf("%d",&j);
        b.push_back(j);
    }
    //sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    mmin=MAX_MIN;
    rep(i,n){
        if((j=search(a[i],b))<mmin)
            mmin=j;
    }
    printf("%d\n",mmin);
    return 0;
}