/*アルゴリズムと工夫点(Yellow and Red Card/CPU: 1 ms Memory: 3868 KB  Length: 663 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 100
using namespace std;

int n,q,yellow[MAX_N]={0},red[MAX_N]={0};

int main(){
    int i;
    scanf("%d%d",&n,&q);
    while(q--){
        scanf("%d",&i);
        switch(i){
            case 1:
                scanf("%d",&i);
                yellow[i-1]++;
                break;
            case 2:
                scanf("%d",&i);
                red[i-1]++;
                break;
            default:
                scanf("%d",&i);
                printf("%s\n",yellow[i-1]>=2||red[i-1]>=1?"Yes":"No");
                break;
        }
    }
    return 0;
}