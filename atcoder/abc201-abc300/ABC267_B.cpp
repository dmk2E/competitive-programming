/*アルゴリズムと工夫点(Split?/CPU: 1 ms Memory: 3668 KB  Length: 866 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int id2Row[]={3,2,4,1,3,5,0,2,4,6},MAX=10,MAX_ROW=7;
string s;

int main(){
    int i,j,cnt[MAX_ROW]={0},k;
    rep(i,MAX)cnt[id2Row[i]]++;
    rep(i,MAX){
        if(i==0){
            if(getchar()=='1'){
                puts("No");
                return 0;
            }
            cnt[id2Row[i]]--;
        }else
            cnt[id2Row[i]]-=(getchar()=='0');
    }
    //rep(i,MAX_ROW)printf("%d ",cnt[i]);puts("");
    rep(i,MAX_ROW)rep(j,i){
        if(cnt[i]>=1&&cnt[j]>=1){
            for(k=j+1;k<i;k++)if(cnt[k]==0){
                //printf("%d %d %d\n",j,k,i);
                puts("Yes");
                return 0;
            }
        }
    }
    puts("No");
    return 0;
}