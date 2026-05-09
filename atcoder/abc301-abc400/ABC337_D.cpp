/*アルゴリズムと工夫点(Cheating Gomoku Narabe/CPU: 34 ms  Memory: 11808 KB  Length: 1268 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_H 200000
using namespace std;

int h, w, k;
string mmap[MAX_H];

int searchMinH(int hh) {
	int i, min;
	vector<int> sumX, sumO;
	sumX.push_back(0);
	sumO.push_back(0);
	rep(i, w) {
		sumO.push_back(sumO[i] + (mmap[hh][i] == '.' ? 1 : 0));
		sumX.push_back(sumX[i] + (mmap[hh][i] == 'x' ? 1 : 0));
	}
	for (i = 0, min = MAX_H+1; i + k - 1 < w; i++)
		if (sumX[i + k] - sumX[i] == 0 && sumO[i + k] - sumO[i] < min)
			min = sumO[i + k] - sumO[i];
	return min;
}

int searchMinW(int ww) {
	int i, min;
	vector<int> sumX, sumO;
	sumX.push_back(0);
	sumO.push_back(0);
	rep(i, h) {
		sumO.push_back(sumO[i] + (mmap[i][ww] == '.' ? 1 : 0));
		sumX.push_back(sumX[i] + (mmap[i][ww] == 'x' ? 1 : 0));
	}
	for (i = 0, min = MAX_H+1; i + k - 1 < h; i++)
		if (sumX[i + k] - sumX[i] == 0 && sumO[i + k] - sumO[i] < min)
			min = sumO[i + k] - sumO[i];
	return min;
}

int main() {
	int i, min = MAX_H + 1, j;
	scanf("%d%d%d", &h, &w, &k);
	rep(i, h)
		cin >> mmap[i];
	rep(i, h) {
		if ((j = searchMinH(i)) < min)
			min = j;
	}
	rep(i, w) {
		if ((j = searchMinW(i)) < min)
			min = j;
	}
	printf("%d\n", min == MAX_H + 1 ? -1 : min);
	return 0;
}