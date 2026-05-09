/*アルゴリズムと工夫点(Same Map in the RPG World/CPU: 1 ms Memory: 3900 KB  Length: 1693 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_H 30
#define MAX_W 30
using namespace std;

int h,w;
bool mmap[MAX_H][MAX_W],b[MAX_H][MAX_W];

void copy(bool a[][MAX_W],bool b[][MAX_W]){
    int i,j;
    rep(i,h){
        rep(j,w)
            b[i][j]=a[i][j];
    }
}

void tate(int s,bool mmap[][MAX_W]){
    int i,j;
    bool temp[MAX_H][MAX_W];
    rep(i,h){
        rep(j,w){
            temp[(h-s+i)%h][j]=mmap[i][j];
        }
    }
    copy(temp,mmap);
}

void yoko(int t,bool mmap[][MAX_W]){
    int i,j;
    bool temp[MAX_H][MAX_W];
    rep(i,h){
        rep(j,w){
            temp[i][(w-t+j)%w]=mmap[i][j];
        }
    }
    copy(temp,mmap);
}

bool judge(bool temp[][MAX_W]){
    int i,j;
    rep(i,h){
        rep(j,w){
            if(temp[i][j]!=b[i][j])
                return false;
        }
    }
    return true;
}

void showMap(bool mmap[][MAX_W]){
    int i,j;
    rep(i,h){
        rep(j,w)
            printf("%d",mmap[i][j]?1:0);
        puts("");
    }
}

int main(){
    int i,j;
    bool temp[MAX_H][MAX_W];
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
        getchar();
        rep(j,w){
            scanf("%c",&c);
            b[i][j]=c=='#';
        }
    }
    rep(i,h){
        rep(j,w){
            copy(mmap,temp);
            tate(i,temp);
            yoko(j,temp);
            if(judge(temp)){
                puts("Yes");
                return 0;
            }
        }
    }
    puts("No");
    return 0;
}