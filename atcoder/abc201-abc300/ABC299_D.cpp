/*アルゴリズムと工夫点(Find by Query/CPU: 6 ms Memory: 4732 KB  Length: 917 B)
S1=0,SN=1が確定しているから、ある値i(1<i<N)についてSi=0なら、1<=j<iよりi<j<=Nの範囲の方が、0から1へ変化する可能性は高い。Si=1なら、i<j<=Nより1<=j<iの範囲の方が0から1へ変化する可能性は高い。この事を利用して、
二分探索的に着目する範囲を狭めていく。狭めていく途中で、(着目する範囲の大きさ)<=(その時点でクエリを行える回数)となった瞬間、線型的に調べていけばよい。
範囲を狭めていく最悪計算量は,クエリを行える最大回数となるから、O(20)=O(1)で十分高速。全体の最悪計算量は、文字列の入力の関係で、O(N)となる。
※一発AC嬉しい!
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 200000
#define MAX_Q 4
#define NIL -1
using namespace std;

int n,s[MAX_N];

int main(){
    int i,left,right,mid,cnt;
    scanf("%d",&n);
    rep(i,n)
        s[i]=NIL;
    cnt=MAX_Q;
    s[0]=0;s[n-1]=1;
    left=0;right=n;
    while(right-left>cnt){
        mid=(left+right)/2;
        if(s[mid]==NIL){
            printf("? %d\n",mid+1);
            cout<<flush;
            scanf("%d",&s[mid]);
            cnt--;
        }
        if(s[mid]==0)
            left=mid+1;
        else
            right=mid;
    }
    for(i=left;cnt>0&&i<right;i++){
        if(s[i]==NIL){
            printf("? %d\n",i+1);
            cout<<flush;
            scanf("%d",&s[i]);
            cnt--;
        }
        if(s[i-1]!=s[i])
            break;
    }
    printf("! %d\n",i);
    cout<<flush;
    return 0;
}