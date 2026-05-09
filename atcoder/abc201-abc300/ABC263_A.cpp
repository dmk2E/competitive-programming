/*アルゴリズムと工夫点(Full House/CPU: 1 ms Memory: 3836 KB  Length: 486 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_CNT 13
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int int2Cnt[MAX_CNT+1]={0};

int main(){
    int i,j;
    bool three=false,two=false;
    rep(i,5){
        scanf("%d",&j);
        int2Cnt[j]++;
    }
    rep(i,MAX_CNT+1){
        if(int2Cnt[i]==3)three=true;
        if(int2Cnt[i]==2)two=true;
    }
    printf("%s\n",three&&two?"Yes":"No");
    return 0;
}