/*アルゴリズムと工夫点(Call the ID Number/CPU: 24 ms Memory: 4100 KB  Length: 678 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N (int)(2e5)
using namespace std;

int n;
bool a[MAX_N]={0};

int main(){
    int i,j,k;
    scanf("%d",&n);
    k=n;
    rep(i,n){
        scanf("%d",&j);j--;
        if(a[i]==false){
            if(a[j]==false)
                k--;
            a[j]=true;
        }
    }
    printf("%d\n",k);
    i=0;
    while(i<MAX_N&&k>1){
        if(a[i]==false){
            printf("%d ",i+1);
            k--;
        }
        i++;
    }
    while(i<MAX_N){
        if(a[i]==false){
            printf("%d\n",i+1);
            break;
        }
        i++;
    }
    return 0;
}