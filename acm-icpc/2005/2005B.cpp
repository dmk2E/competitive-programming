/*アルゴリズムと工夫点(Polygonal Line Search/CPU: 0 ms  Memory: 3112 KB  Length: 1488 B)
平行移動しても一致することを簡単に検証できるように、折れ線をベクトルで保持する。折れ線0をv1に保持し、折れ線1～nをv2に保持し、v2を0,90,180,270度回転させたものとv1を比較する。この時、頂点が逆順に指定されているものを同じと見なす
ための処理も忘れずにやる。計算量はO(n*m)=5*10^2 となり、十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define swap(a,b,t){t=a,a=b,b=c}
#define MAX_M 10
using namespace std;

typedef struct v {
	int y, x;
}Vector;

int n,m;
Vector v1[MAX_M-1], v2[MAX_M - 1];

void rotate90() {
	int i;
	Vector temp;
	rep(i, m - 1) {
		temp = v2[i];
		v2[i].y = temp.x;
		v2[i].x = -temp.y;
	}
}

bool judge() {
	int i,j;
	rep(i, 4) {
		rep(j, m - 1)
			if (v1[j].y != v2[j].y || v1[j].x != v2[j].x)
				break;
		if (j == m - 1)
			break;
		rotate90();
	}
	if (i < 4) 
		return true;
	rep(i, 4) {   //逆順に頂点が指定されている場合、ベクトルの向きも逆になることに注意。
		rep(j,m-1)
			if (v1[j].y != -v2[m-2-j].y || v1[j].x != -v2[m-2-j].x)
				break;
		if (j == m-1)
			break;
		rotate90();
	}
	if (i < 4) 
		return true;
	return false;
}

int main() {
	int i, j, py, px, ny, nx,m1;
	Vector temp;
	while (1) {
		//scanf_s("%d",&n);
		scanf("%d", &n);
		if (n == 0)
			break;
		//scanf_s("%d", &m);
		scanf("%d", &m);
		//scanf_s("%d%d", &px, &py);
		scanf("%d%d", &px, &py);
		m1 = m;
		rep(j, m - 1) {
			//scanf_s("%d%d", &nx, &ny);
			scanf("%d%d", &nx, &ny);
			temp.y = ny - py;
			temp.x = nx - px;
			v1[j] = temp;
			px = nx;
			py = ny;
		}
		rep(i,n) {
			//scanf_s("%d", &m);
			scanf("%d", &m);
			//scanf_s("%d%d", &px, &py);
			scanf("%d%d",&px,&py);
			rep(j,m-1) {
				//scanf_s("%d%d",&nx,&ny);
				scanf("%d%d", &nx, &ny);
				temp.y = ny - py;
				temp.x = nx - px;
				v2[j] = temp;
				px = nx;
				py = ny;
			}
			if (m==m1&&judge()) 
				printf("%d\n", i + 1);
		}
		puts("+++++");
	}
	return 0;
}