/*アルゴリズムと工夫点(Shapes/CPU: 2 ms Memory: 3976 KB  Length: 1813 B)
1回の90度回転はO(N^2),平行移動してSとTが一致するかの判定は，S,Tそれぞれが存在する範囲をあらかじめ調べて置き，その中で全成分が一致するか調べればよく，最悪計算量はO(N^2)
よって全体の最悪計算量はO(4*(N^2+N^2))=O(N^2)<10^5 となり，十分高速．
*/
#include<iostream>
#define MAX_N 200
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int n;
bool s[MAX_N][MAX_N],t[MAX_N][MAX_N];

void rotate(){
    int i,j;
    bool tmp[MAX_N][MAX_N];
    rep(i,n){
        rep(j,n)
            tmp[i][j]=s[j][n-i-1];
    }
    rep(i,n){
        rep(j,n)
            s[i][j]=tmp[i][j];
    }
}

bool judge(int sx,int tx,int sy,int ty){
    int minX=MAX_N,maxX=-1,minY=MAX_N,maxY=-1,i,j;
    rep(i,n){
        rep(j,n){
            if(s[i][j]){
                if(i<minY)
                    minY=i;
                if(i>maxY)
                    maxY=i;
                if(j<minX)
                    minX=j;
                if(j>maxX)
                    maxX=j;
            }
        }
    }
    if(ty-sy!=maxY-minY||tx-sx!=maxX-minX)
        return false;
    for(i=0;i<=ty-sy;i++){
        for(j=0;j<=tx-sx;j++){
            if(t[i+sy][j+sx]!=s[minY+i][minX+j])
                return false;
        }
    }
    return true;
}

void show(){
    int i,j;
    rep(i,n){
        rep(j,n)
            printf("%c",s[i][j]?'#':'.');
        puts("");
    }
}

int main(){
    int i,j,minX=MAX_N,maxX=-1,minY=MAX_N,maxY=-1;
    scanf("%d",&n);
    rep(i,n){getchar();rep(j,n){s[i][j]=getchar()=='#';}}
    rep(i,n){getchar();rep(j,n){
        t[i][j]=getchar()=='#';
        if(t[i][j]){
            if(i<minY)
                minY=i;
            if(i>maxY)
                maxY=i;
            if(j<minX)
                minX=j;
            if(j>maxX)
                maxX=j;
        }
        }}
    rep(i,4){
        if(judge(minX,maxX,minY,maxY))break;
        rotate();
    }
    //show();printf("%d\n",i);
    printf("%s\n",i==4?"No":"Yes");
    return 0;
}