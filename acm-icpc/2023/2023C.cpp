/*アルゴリズムと工夫点(席替え/CPU: 20 ms Memory: 3924 KB  Length: 1772 B)
左上から右下の席にかけて順番に，条件を満たすように生徒を配置していく．条件を満たすように配置できなくなったらその時点で直前に生徒を配置した席に，別の生徒を配置する，再帰を用いたバックトラックで実装する．
ここで，どのような順番で生徒を見ていくかだが，左から1列ずつ，奇数行目の生徒を見る．その後，偶数行目の生徒を同様に見るようにする．こうすることで，再帰呼び出しの回数を削減し，十分高速に解が求まる．
最悪計算量は計算不可．
*/
#include<iostream>
#include<vector>
#define rep(i,n)for(i=0;i<(int)n;i++)
#define MAX_N 50
#define NIL (int)(1e8)
using namespace std;

typedef pair<int,int> p;

int n,where[MAX_N][MAX_N],ans[MAX_N][MAX_N];
p dic[MAX_N*MAX_N],ddic[MAX_N*MAX_N];

bool judge(int num,int y,int x){
	int i;
	for(i=-1;i<2;i+=2){
		if(0<=dic[num].first+i&&dic[num].first+i<n&&abs(ddic[where[dic[num].first+i][dic[num].second]].first-y)+abs(ddic[where[dic[num].first+i][dic[num].second]].second-x)<n/2)
			break;
	}
	if(i<2)return false;
	for(i=-1;i<2;i+=2){
		if(0<=dic[num].second+i&&dic[num].second+i<n&&abs(ddic[where[dic[num].first][dic[num].second+i]].first-y)+abs(ddic[where[dic[num].first][dic[num].second+i]].second-x)<n/2)
			break;
	}
	return i>=2;
}

bool res(int y,int x,vector<int>& order){
	int i,j;
	//rep(i,n){rep(j,n-1)printf("%d ",ans[i][j]);printf("%d\n",ans[i][j]);}
	if(y==n)
		return true;
	rep(i,order.size()){
		if(ddic[order[i]].first==NIL&&judge(order[i],y,x)){
			ans[y][x]=order[i];
			ddic[order[i]]=p(y,x);
			if(res((x+1==n)?y+1:y,(x+1)%n,order))
				return true;
			ans[y][x]=-1;
			ddic[order[i]]=p(NIL,NIL);
		}
	}
	return false;
}

int main(){
	int i,j;
	while(1){
		scanf("%d",&n);
		if(!n)
			break;
		rep(i,n){
			rep(j,n){
				scanf("%d",&where[i][j]);
				where[i][j]--;
				dic[where[i][j]]=p(i,j);
				ddic[where[i][j]]=p(NIL,NIL);
				ans[i][j]=-1;
			}
		}
		//rep(i,n){rep(j,n){printf("%d ",where[i][j]);}puts("");}
		vector<int> order;
		rep(j,n)
			for(i=0;i<n;i+=2)
				order.push_back(where[i][j]);
		rep(j,n)
			for(i=1;i<n;i+=2)
				order.push_back(where[i][j]);
		//rep(i,order.size())printf("%d ",order[i]);puts("");
		res(0,0,order);
		rep(i,n){
			rep(j,n-1)
				printf("%d ",ans[i][j]+1);
			printf("%d\n",ans[i][j]+1);
		}
	}
	return 0;
}