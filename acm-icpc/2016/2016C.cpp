#include<iostream>
#define rep(i,n)for(i=0;i<(int)n;i++)
#define MAX_B (int)(1e7)
using namespace std;

int m,n;

int judge(){
    int i,j;
    bool isBloom[MAX_B]={0};
    for(i=m;i<MAX_B;i++){
        if(isBloom[i]==false){
            if(n>0)
                n--;
            else
                return i;
            isBloom[i]=true;
            j=2*i;
            while(j<MAX_B){
                isBloom[j]=true;
                j+=i;
            }
        }
    }
    return -1;
}

int main(){
    int i,j;
    while(1){
        scanf("%d%d",&m,&n);
        if(!(m||n))
            break;
        printf("%d\n",judge());
    }
    return 0;
}