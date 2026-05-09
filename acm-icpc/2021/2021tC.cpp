/*アルゴリズムと工夫点(引っ越し/CPU: 110 ms Memory: 3572 KB  Length: 2241 B)
「タイルで敷き詰めることができる」=「左上から右下へ，順次タイルを置くことができる置き方が存在する」ということだから，置き方を全て試す枝刈り全探索で解ける．
置くタイルの形状は4パターンあり，2*2マスのタイルの左上を固定して，置けるか判定していく．枝刈り条件だが，「一つでも空白を残してしまう場合」，「全てのマスが埋まった場合」となる．
最悪計算量は予測が難しいため割愛．
※解説は半分全列挙で解いていた．
*/
#include<iostream>
#define rep(i,n)for(i=0;i<n;i++)
#define MAX_H 8
#define MAX_W 8
using namespace std;

typedef struct data{
    int r,c,sum;
    char mmap[MAX_H+1][MAX_W+1];

    data(int rr=0,int cc=0,int ssum=0):r(rr),c(cc),sum(ssum){};
}Data;

int h,w;
char carpet[4][2][3]={{"##"
                      ,".#"},
                      {"##"
                      ,"#."},
                      {"#."
                      ,"##"},
                      {".#"
                      ,"##"}};

bool judge(int id,Data& now){
    int i,j;
    rep(i,2)
        rep(j,2){
            if(carpet[id][i][j]=='#'&&now.mmap[now.r+i][now.c+j]=='#')
                return false;
        }
    return true;
}

int res(Data now){
    if(now.r==h)return 1;
    int i,j,k,cnt=0;
    Data nnew;
    //printf("(%d,%d)\n",now.r,now.c);rep(i,h)printf("%s\n",now.mmap[i]);puts("\n");
    if(now.mmap[now.r][now.c]=='#'){
        if(now.r+1<h&&now.c+1<w&&judge(3,now)){//置く
            nnew=now;nnew.sum+=3;
            if(nnew.sum==h*w)return 1;
            nnew.r=now.c+1==w?now.r+1:now.r;nnew.c=(now.c+1)%w;
            rep(i,2)rep(j,2){if(carpet[3][i][j]=='#')nnew.mmap[now.r+i][now.c+j]=carpet[3][i][j];}
            cnt+=res(nnew);
        }
        nnew=now;nnew.r=now.c+1==w?now.r+1:now.r;nnew.c=(now.c+1)%w;
        cnt+=res(nnew);//置かない
    }else{//置くしかない
        rep(i,3){
            if(now.r+1>=h||now.c+1>=w)break;
            if(judge(i,now)){
                nnew=now;nnew.sum+=3;
                if(nnew.sum==h*w)return 1;
                nnew.r=now.c+1==w?now.r+1:now.r;nnew.c=(now.c+1)%w;
                rep(j,2)rep(k,2){if(carpet[i][j][k]=='#')nnew.mmap[now.r+j][now.c+k]=carpet[i][j][k];};
                cnt+=res(nnew);
            }
        }
    }
    return cnt;
}

int main(){
    int i,j,k;
    Data now;
    while(1){
        scanf("%d%d",&h,&w);
        if(!(h||w))
            break;
        rep(i,h)
            scanf("%s",now.mmap[i]);
        k=0;
        rep(i,h)
            rep(j,w)
                if(now.mmap[i][j]=='#')
                    k++;
        now.r=now.c=0;now.sum=k;
        //rep(i,4){rep(j,2)printf("%s\n",carpet[i][j]);puts("");}
        printf("%d\n",res(now));
    }
    return 0;
}