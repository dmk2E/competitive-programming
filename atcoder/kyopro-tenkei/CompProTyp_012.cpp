/*アルゴリズムと工夫点(Red Painting/CPU: 58 ms  Memory: 35232 KB  Length: 1487 B)
「連結判定はUnion-Find」である。ただし、各座標の範囲を0<=x<=w-1,0<=y<=h-1 とし、点(x,y)を「w*y+x」という整数値一つで表すことにする。辺の情報が変わらないのであればbfsによる色付けで連結情報を保持することはできるが、
今回のように辺の情報が毎回の操作で変化し、かつ保持したい集合が複数ある場合、Union-Find木が有効。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_H 2000
#define MAX_W 2000
using namespace std;

typedef class UnionFindTree{
	vector<int> par,rank;
public:
	UnionFindTree(int size=0){
		int i;
		rank.resize(size,0);
		par.resize(size);
		rep(i,size){
			par[i]=i;
		}
	}

	void renew(int size=0){
		int i;
		rank.resize(size,0);
		par.resize(size);
		rep(i,size){
			par[i]=i;
		}
	}

	int root(int x){
		return par[x]==x?x:par[x]=root(par[x]);
	}

	bool isSame(int x,int y){
		return root(x)==root(y);
	}

	void unite(int x,int y){
		x=root(x);
		y=root(y);
		if(x==y)
			return ;
		if(rank[x]<rank[y]){
			par[x]=y;
		}else{
			par[y]=x;
			if(rank[x]==rank[y])
				rank[x]++;
		}
	}
}UF;

int h,w,q;

int main() {
	int i,j,k,l;
	vector<vector<bool> > painted;
	UF tree;
	scanf("%d%d",&h,&w);
	tree.renew(h*w);
	scanf("%d",&q);
	painted.resize(h,vector<bool>(w,false));
	while(q--){
		scanf("%d",&i);
		if(i==1){
			scanf("%d%d",&i,&j);
			i--;j--;
			painted[i][j]=true;
			if(i-1>=0&&painted[i-1][j])
				tree.unite(w*i+j,w*(i-1)+j);
			if(i+1<h&&painted[i+1][j])
				tree.unite(w*i+j,w*(i+1)+j);
			if(j-1>=0&&painted[i][j-1])
				tree.unite(w*i+j,w*i+j-1);
			if(j+1<w&&painted[i][j+1])
				tree.unite(w*i+j,w*i+j+1);
		}else{
			scanf("%d%d%d%d",&i,&j,&k,&l);
			i--;j--;k--;l--;
			printf("%s\n",tree.isSame(w*i+j,w*k+l)&&painted[i][j]?"Yes":"No");
		}
	}
	return 0;
}