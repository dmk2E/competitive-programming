/*アルゴリズムと工夫点(宇宙ヤシガニ/CPU: 10 ms  Memory: 3292 KB  Length: 806 B)
条件より、x,y,z>=0 かつ x+y+z=m かつ x+y^2+z^3=e となるから、xを消去して、m=e+y+z-y^2-z^3 となる。このmの最小値を求めればよい。
e<=10^6より、0<=y<=10^3,0<=z<=10^2 となり、zの値を固定した時、yに対してmは単調減少する(∵y-y^2はyの増加に対して単調減少)。また、x>=0より、x=e-y^2-z^3>=0 かつ e+y+z-y^2-z^3>=y+z(x=m-y-z>=0よりm>=y+z) を満たす必要があり、
zを固定している時、mもxの値もyの増加に対して単調に減少する。従って、全ての条件を満たすmの最小値は、二分探索で解くことができる。yとzどちらを固定してもよいが、固定する値は線形探索になるため、yより値域が狭いzを固定した方が
計算量は少ない。従って、最悪計算量は、O(z*log2(y))<10~4となり、十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_Y 1000
#define MAX_Z 100
#define ERROR -1
#define MAX_MIN 1001100
using namespace std;

int e;

int calM(int y,int z) {
	int tmp;
	if (e - y * y - z * z * z < 0 || (tmp = e + y + z - y * y - z * z * z) < y + z)
		return ERROR;
	return tmp;
}

int main() {
	int left, right, mid, z, min;
	while (1) {
		scanf("%d",&e);
		if (!e)
			break;
		min = MAX_MIN;
		rep(z, MAX_Z+1) {
			left = 0; right = MAX_Y + 1;
			while (left < right) {
				mid = (left + right) / 2;
				if (calM(mid, z) < 0)
					right = mid;
				else
					left = mid + 1;
			}
			if (left - 1 >= 0 && (mid = calM(left - 1, z)) >= 0 && mid < min) {   //midは一次的に値を退避するための変数として使った。
				min = mid;
				//printf("y:%d z:%d min:%d\n", left - 1, z, min);
			}
		}
		printf("%d\n", min);
	}
	return 0;
}