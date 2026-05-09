/*アルゴリズムと工夫点(Counting Squares/CPU: 4 ms Memory: 3808 KB  Length: 1552 B)
まず4点を被りが無いよう全探索し，その後その4点が正方形を表すかを判定し，数え上げる．
※初見で解けたが，実装に時間がかかりすぎた...
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef struct point{
    int y,x;

    point(int yy=0,int xx=0):y(yy),x(xx){}

    point operator-(const point& k)const{
        return point(y-k.y,x-k.x);
    }

    bool operator<(const point& k)const{
        return y==k.y?x<k.x:y<k.y;
    }

    int norm(){
        return y*y+x*x;
    }

    int dot(const point& k)const{
        return y*k.y+x*k.x;
    }
}p;

vector<string> s;

int main(){
    int i,j,k,l,ans=0;
    p v1,v2;
    s=vector<string>(9);
    vector<p> ipt;
    rep(i,9)cin>>s[i];
    rep(i,9)rep(j,9){
        if(s[i][j]=='#'){
            ipt.push_back(p(i,j));
        }
    }
    rep(i,ipt.size())rep(j,i)rep(k,j)rep(l,k){
        //ijkl
        v1=ipt[j]-ipt[i];
        v2=ipt[k]-ipt[i];
        if(v1.norm()==v2.norm()&&v1.dot(v2)==0&&ipt[l].y==ipt[k].y+v1.y&&ipt[l].x==ipt[k].x+v1.x){
            ans++;
            break;
        }
        //ijlk
        v1=ipt[j]-ipt[i];
        v2=ipt[l]-ipt[i];
        if(v1.norm()==v2.norm()&&v1.dot(v2)==0&&ipt[k].y==ipt[l].y+v1.y&&ipt[k].x==ipt[l].x+v1.x){
            ans++;
            break;
        }
        //iklj
        v1=ipt[k]-ipt[i];
        v2=ipt[l]-ipt[i];
        if(v1.norm()==v2.norm()&&v1.dot(v2)==0&&ipt[j].y==ipt[l].y+v1.y&&ipt[j].x==ipt[l].x+v1.x){
            ans++;
            break;
        }
    }
    printf("%d\n",ans);
    return 0;
}