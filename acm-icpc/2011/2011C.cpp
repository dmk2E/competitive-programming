/*アルゴリズムと工夫点(同色パネル結合/CPU: 80 ms Memory: 3544 KB  Length: 2408 B)
色は最大5回変えることができ、変更後の色の種類は左上角の色を除いた5種類となる。色を変更する回数が多い方がより大きなパネルを作ることができるから、最大回数である「5」回色を変更する。ただし、最後は指定された色に変更する
ようにする。全パターン数は5^4(=M とする)しかなく、色の変更や最終的に結合されたパネル数を数えるのはbfsで実現できるため、再帰を用いたバックトラック、つまり全探索で解く。最悪計算量は O(M*(h*w*4))<10^5 となり、十分高速。
*/
#include<iostream>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_H 8
#define MAX_W 8
#define MAX_C 6
#define MAX_SHOCK 5
#define MAX_D 4
using namespace std;

typedef struct data{
    int color[MAX_H][MAX_W];
}Data;

int h,w,c,dy[]={-1,0,1,0},dx[]={0,1,0,-1};

void paint(int c,Data& d){
    int i,y,x,prev=d.color[0][0];
    bool color[MAX_H][MAX_W]={0};
    queue<int> que;
    que.push(0);
    color[0][0]=true;
    d.color[0][0]=c;
    while(que.size()){
        y=que.front()/w;x=que.front()%w;
        que.pop();
        rep(i,MAX_D){
            if(y+dy[i]>=0&&y+dy[i]<h&&x+dx[i]>=0&&x+dx[i]<w&&d.color[y+dy[i]][x+dx[i]]==prev&&color[y+dy[i]][x+dx[i]]==false){
                color[y+dy[i]][x+dx[i]]=true;
                d.color[y+dy[i]][x+dx[i]]=c;
                que.push((y+dy[i])*w+x+dx[i]);
            }
        }
    }
}

int count(const Data& d){
    int i,y,x,cnt=1;
    bool color[MAX_H][MAX_W]={0};
    queue<int> que;
    que.push(0);
    color[0][0]=true;
    while(que.size()){
        y=que.front()/w;x=que.front()%w;
        que.pop();
        rep(i,MAX_D){
            if(y+dy[i]>=0&&y+dy[i]<h&&x+dx[i]>=0&&x+dx[i]<w&&d.color[y+dy[i]][x+dx[i]]==d.color[0][0]&&color[y+dy[i]][x+dx[i]]==false){
                color[y+dy[i]][x+dx[i]]=true;
                cnt++;
                que.push((y+dy[i])*w+x+dx[i]);
            }
        }
    }
    return cnt;
}

void showColor(const Data& d){
    int i,j;
    rep(i,h){
        rep(j,w)
            printf("%d",d.color[i][j]);
        puts("");
    }
}

int dfs(Data now,int cnt){
    //printf("%d:\n",cnt);showColor(now);puts("");
    if(cnt==MAX_SHOCK-1){
        int temp;
        paint(c,now);
        temp=count(now);
        //printf("final:\n");showColor(now);printf("cnt:%d\n",temp);puts("");
        return temp;
    }
    int i,max=-1,temp;
    Data next;
    rep(i,MAX_C){
        if(i!=now.color[0][0]){
            next=now;
            paint(i,next);
            if((temp=dfs(next,cnt+1))>max)
                max=temp;
        }
    }
    return max;
}

int main(){
    int i,j,k;
    while(1){
        scanf("%d%d%d",&h,&w,&c);
        if(!(h||w||c))
            break;
        c--;
        Data first;
        rep(i,h)
            rep(j,w){
                scanf("%d",&first.color[i][j]);
                first.color[i][j]--;
            }
        printf("%d\n",dfs(first,0));
    }
    return 0;
}