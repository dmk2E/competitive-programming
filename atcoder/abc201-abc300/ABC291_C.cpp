/*アルゴリズムと工夫点(LRUD Instructions 2/CPU: 66 ms Memory: 16408 KB  Length: 747 B)

*/
#include<iostream>
#include<map>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

typedef struct pair<int,int> p;

int n;

int main(){
    int i,y,x;
    char c;
    scanf("%d",&n);
    getchar();
    map<p,bool> v;
    y=x=0;
    v[p(y,x)]=true;
    rep(i,n){
        c=getchar();
        switch(c){
            case 'R':
                x++;
                break;
            case 'L':
                x--;
                break;
            case 'U':
                y++;
                break;
            default:
                y--;
                break;
        }
        if(v[p(y,x)])
            break;
        v[p(y,x)]=true;
    }
    printf("%s\n",i==n?"No":"Yes");
    return 0;
}