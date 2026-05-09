/*アルゴリズムと工夫点(X-Ray Screening System/CPU: 0 ms  Memory: 3208 KB  Length: 3241 B)
材質が同じ物質は同一の物質とみなし、その物質は長方形で表される。従って、重ね合わされた複数の長方形の位置関係に矛盾がないか、そして長方形以外の形ではないかを判定すればよい。
位置関係は、αの物質がβの物質より前にあることを、「26*(αに対応する配列alfa上の添え字)+(βに対応する配列alfa上の添え字)」の整数で表す。説明のため、このことを「α>β」とする。
新しい位置関係「α>β」が生まれる度に、既に存在する位置関係「β>γ」があれば、「α>γ」も新しく生成する。新しく位置関係を生成する度に、「α>β」と「β>α」が同時に存在しないかを判定する。
この同時に存在しないかの判定にUnion-find木を用いたが、一次元配列で済むため、コード長はさらに短くできると考えられる。
最悪計算量は、O(h*w(h*w+676))=O(h^2*w^2)<10^7 より、高速に動作する。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX 675+1
#define MAX_H 50
#define MAX_W 50
#define MAX_ALFA 26
#define NIL -1
using namespace std;

typedef struct union_find {
	int par[MAX], rank[MAX];

	union_find() {
		int i, j;
		rep(i, MAX) {
			par[i] = i;
			rank[i] = 0;
		}
	}

	int find(int x) {
		if (par[x] == x)
			return x;
		return par[x] = find(par[x]);
	}

	void unit(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y) return;
		if (rank[x] < rank[y])
			par[x] = y;
		else {
			par[y] = x;
			if(rank[x]==rank[y])
				rank[x]++;
		}
	}

	bool isSame(int x,int y) {
		return find(x) == find(y);
	}

}UF;

typedef struct pairing {
	int minX, minY, maxX, maxY;
}P;

int n, h, w;
char d[MAX_H][MAX_W+1],alfa[MAX_ALFA+1]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
vector<int> v;

int toNum(char z) {
	int i;
	rep(i, MAX_ALFA)
		if ((int)z == (int)alfa[i])
			return i;
	return NIL;
}

P calHW(char c,int y,int x,P max,bool flag[][MAX_W]) {   //アルファベットcの長方形の左上の点と右下の点をそれぞれ求める。
	int i, j;
	for(i=y;i<h;i++)
		for(j=0;j<w;j++)
			if (d[i][j] == c) {
				if (max.maxY < i)
					max.maxY = i;
				if (max.maxX < j)
					max.maxX = j;
				if (max.minY > i)
					max.minY = i;
				if (max.minX > j)
					max.minX = j;
				flag[i][j] = true;
			}
	return max;
}

bool isSafe(char c,UF& u,int sy,int sx,int ey,int ex) {
	int a = toNum(c), b, j;
	bool check[MAX_ALFA] = {0};
	//printf("%c:\n",c);
	for(;sy<=ey;sy++)
		for (j=sx; j <= ex; j++) {
			//printf("%c(%d,%d)\n", d[sy][j],sy,j);
			if (d[sy][j] == '.')
				return false;
			if (d[sy][j] != c&&check[(b = toNum(d[sy][j]))]==false) {
				check[b] = true;
				u.unit(MAX_ALFA * b + a, 0);
				v.push_back(MAX_ALFA * b + a);
				//printf("%c>%c b:%d a:%d\n", alfa[b], alfa[a],b,a);
				for (int i : v) {
					if (i / MAX_ALFA == a&&!u.isSame(MAX_ALFA * b + i % MAX_ALFA, 0)) {
						u.unit(MAX_ALFA*b+i%MAX_ALFA,0);
						if (u.isSame(MAX_ALFA * b + i % MAX_ALFA, MAX_ALFA * (i % MAX_ALFA) + b))
							return false;
						v.push_back(MAX_ALFA * b + i % MAX_ALFA);
					}
				}
				if (u.isSame(MAX_ALFA * b + a, MAX_ALFA * a + b))
					return false;
			}
		}
	return true;
}

void showD() {
	int i;
	rep(i, h)
		printf("%s\n", d[i]);
}

void showF(bool flag[][MAX_W]) {
	int i, j;
	rep(i, h) {
		rep(j, w)
			printf("%d", flag[i][j] ? 1 : 0);
		puts("");
	}
}

bool judge() {
	int i,j;
	bool flag[MAX_H][MAX_W] = { 0 };   //一度調べた長方形をスルーするための、dと対応した配列。
	UF u;
	P tmp;
	rep(i, h) {
		rep(j, w) {
			if (d[i][j] != '.'&&flag[i][j]==false) {
				//printf("c:%c\n",d[i][j]);
				tmp.minY = i;
				tmp.minX = j;
				tmp.maxX = tmp.maxY = -1;
				//printf("minY:%d minX:%d maxY:%d maxX:%d\n", tmp.minY, tmp.minX, tmp.maxY, tmp.maxX);
				tmp = calHW(d[i][j], i, j, tmp,flag);
				//printf("minY:%d minX:%d maxY:%d maxX:%d\n",tmp.minY,tmp.minX,tmp.maxY,tmp.maxX);
				//showF(flag);
				if (!isSafe(d[i][j],u,tmp.minY,tmp.minX,tmp.maxY,tmp.maxX))
					return false;
			}
		}
	}
	return true;
}

int main() {
	int i;
	scanf("%d",&n);
	while (n--) {
		scanf("%d%d",&h,&w);
		rep(i, h)
			scanf("%s",d[i]);
		//printf("%d %d\n",h,w);
		//showD();
		if (judge())
			cout << "SAFE" << endl;
		else
			cout << "SUSPICIOUS" << endl;
		/*
		for (int j : v) {
			printf("%c>%c\n",alfa[j/MAX_ALFA],alfa[j%MAX_ALFA]);
		}
		*/
		v.clear();
	}
	return 0;
}