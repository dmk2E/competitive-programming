/*アルゴリズムと工夫点(Cross/CPU: 2 ms Memory: 3920 KB  Length: 2320 B)

*/
#include<iostream>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_H 100
#define MAX_W 100
using namespace std;

int h,w;
bool mmap[MAX_H][MAX_W],visited[MAX_H][MAX_W]={0};

bool judge(int a,int b,int n){
    if(mmap[a][b]==false)
        return false;
    int i;
    for(i=1;i<=n;i++){
        if(mmap[a+i][b+i]==false||mmap[a+i][b-i]==false||mmap[a-i][b+i]==false||mmap[a-i][b-i]==false)
            return false;
        visited[a+i][b+i]=visited[a+i][b-i]=visited[a-i][b+i]=visited[a-i][b-i]=true;
    }
    if(a+n+1>=h||b+n+1>=w||mmap[a+n+1][b+n+1]==false)
        return true;
    if(a+n+1>=h||b-n-1<0||mmap[a+n+1][b-n-1]==false)
        return true;
    if(a-n-1<0||b+n+1>=w||mmap[a-n-1][b+n+1]==false)
        return true;
    if(a-n-1<0||b-n-1<0||mmap[a-n-1][b-n-1]==false)
        return true;
    return false;
}

int main(){
    int i,j,k,s[MAX_H+1]={0};
    char c;
    scanf("%d%d",&h,&w);
    rep(i,h){
        getchar();
        rep(j,w){
            scanf("%c",&c);
            mmap[i][j]=c=='#';
        }
    }
    rep(i,h){
        rep(j,w){
            if(visited[i][j]==false&&mmap[i][j]){
                //printf("(%d,%d)\n",i,j);
                if(i+1<h){
                    if(j-1>=0&&mmap[i+1][j-1]){
                        k=0;
                        while(i+k<h&&j-k>=0&&mmap[i+k][j-k]){
                            visited[i+k][j-k]=true;
                            k++;
                        }
                        //printf("左斜めでk:%d\n",k);
                        if(k%2==1&&judge(i+k/2,j-k/2,k/2)){
                            s[k/2]++;
                        }
                    }else if(j+1<w&&mmap[i+1][j+1]){
                        k=0;
                        while(i+k<h&&j+k<w&&mmap[i+k][j+k]){
                            visited[i+k][j+k]=true;
                            k++;
                        }
                        //printf("右斜めでk:%d\n",k);
                        if(k%2==1&&judge(i+k/2,j+k/2,k/2)){
                            s[k/2]++;
                        }
                    }
                }   
            }
        }
    }
    for(i=1;i<=min(h,w)-1;i++)
        printf("%d ",s[i]);
    printf("%d\n",s[i]);
    return 0;
}