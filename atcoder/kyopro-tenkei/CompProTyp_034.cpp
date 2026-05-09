/*アルゴリズムと工夫点(There are few types of elements/CPU: 84 ms Memory: 9004 KB  Length: 790 B)
左端の位置が大きければ大きいほど,条件を満たす区間の右端の位置は大きくなるという単調性を利用した尺取り法で解ける。
*/
#include<iostream>
#include<map>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 100000
using namespace std;

int n,k,a[MAX_N];
map<int,int> cnt;

int main(){
    int i,left,right,max=-1;
    scanf("%d%d",&n,&k);
    rep(i,n)
        scanf("%d",&a[i]);
    for(left=right=i=0;left<n;left++){
        while(right<n&&(cnt[a[right]]>0||i+1<=k)){
            if(cnt[a[right]]==0)
                i++;
            cnt[a[right]]++;
            right++;
        }
        //printf("[%d,%d)\n",left,right);
        if(max<right-left)
            max=right-left;
        if(left==right){
            right++;
        }else{
            cnt[a[left]]--;
            if(cnt[a[left]]==0)
                i--;
        }
    }
    printf("%d\n",max);
    return 0;
}