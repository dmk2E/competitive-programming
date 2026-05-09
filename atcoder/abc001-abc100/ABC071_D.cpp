/*アルゴリズムと工夫点(Coloring Dominoes/CPU: 1 ms Memory: 3924 KB  Length: 892 B)
数え上げ方にミスがあり、初見ACができなかった、、、、。アルゴリズム自体の正当性を確かめる癖をつけていきたい。
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 52
#define MOD 1000000007
using namespace std;

int n;
char mmap[2][MAX_N+1];

int main(){
    int i,j,sum;
    bool left;
    scanf("%d",&n);
    rep(i,2)
        scanf("%s",mmap[i]);
    rep(j,n){
        if(j==0){
            if(mmap[0][j]==mmap[1][j]){
                left=true;
                sum=3;
            }else{
                left=false;
                sum=6;
                j++;
            }
        }else{
            if(mmap[0][j]==mmap[1][j]){
                sum=(int)(((long long)sum*(left?2:1))%MOD);
                left=true;
            }else{
                sum=(int)(((long long)sum*(left?2:3))%MOD);
                left=false;
                j++;
            }
        }
        //printf("%d\n",sum);
    }
    printf("%d\n",sum);
    return 0;
}

/*数え上げ方間違えたやつ(反省点:アルゴリズムの正当性を確かめること)
#include<iostream>
#include<map>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 52
#define NIL (int)'.'
#define MOD 1000000007
using namespace std;

int n;
char mmap[2][MAX_N+1];
map<char,int> cnt;

int main(){
    int i,j,temp,sum=1;
    scanf("%d",&n);
    rep(i,2)
        scanf("%s",mmap[i]);
    rep(i,26){
        cnt[(char)(i+(int)'a')]=3;
        cnt[(char)(i+(int)'A')]=3;
    }
    rep(j,n){
        rep(i,2){
            if(mmap[i][j]!=(char)NIL){
                if(j+1<n&&mmap[i][j]==mmap[i][j+1]){
                    printf("%c:",mmap[i][j]);
                    temp=cnt[mmap[i][j]];
                    mmap[i][j]=mmap[i][j+1]=(char)NIL;
                    if(j+2<n&&mmap[i][j+2]!=(char)NIL)
                        cnt[mmap[i][j+2]]--;
                    if(i+1<2&&mmap[i+1][j]!=(char)NIL)
                        cnt[mmap[i+1][j]]--;
                    sum=(int)(((unsigned long long)sum*temp)%MOD);
                    if(i==2)
                }else if(i+1<2&&mmap[i][j]==mmap[i+1][j]){
                    printf("%c:",mmap[i][j]);
                    temp=cnt[mmap[i][j]];
                    mmap[i][j]=mmap[i+1][j]=(char)NIL;
                    if(j+1<n&&mmap[i][j+1]!=(char)NIL){
                        cnt[mmap[i][j+1]]--;
                        if(j+2<n&&mmap[i][j+1]==mmap[i][j+2])
                            cnt[mmap[i+1][j+1]]--;
                    }
                    sum=(int)(((unsigned long long)sum*temp)%MOD);
                }
                printf("%d\n",sum);
            }
        }
    }
    printf("%d\n",sum);
    return 0;
}
*/