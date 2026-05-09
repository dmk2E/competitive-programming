/*アルゴリズムと工夫点(Chocolate Bar/CPU: 1 ms  Memory: 3952 KB  Length: 2755 B)
一辺がhまたはwである長方形の数が3個の時、求める最小値は、h%3=0またはw%3=0で「0」(∵hまたはwが3の倍数なら綺麗に三分割できる)。そうでなければmin(h,w)となる(3つの長方形のhまたはwでない方の辺を考えると、
n+n+(n+1)=3n+1,n+n+(n-1)=3n-1となり、全体の長方形の一辺が3の倍数でないなら必ずこのように分割できるから)。
一辺がhまたはwである長方形の数が1個の時、左上に詰めたh'*w'の長方形が存在するとき、他の2つの長方形の作り方は、h'*(w-'w),(h-h')*w または (h-h')*w',h*(w-w') となる(1<=h'<=h-1,1<=w'<=w-1)。
h'*(w-'w),(h-h')*w の場合を考えると、まずs1=h'*w',s2=h'*(w-'w),s3=(h-h')*w とすると、3つの長方形の面積がほぼ同じになるように考えるとw'=[w/2]とすればよいことが分かる。続いてh'の値を探索していく。
h'の値が増加するにつれて、s3は単調減少し、s2,s1は単調増加する。そのため、h'の値が増加するにつれて、s1<=s2<=s3 -①-> s1<=s3<=s2 -②-> s3<=s1<=s2 という風に大小関係が変化する。それぞれの大小関係における
Smax-Sminの最小値を出し、最も小さい値が求める最小値となる。より正確には min(「①の変化が起こる直前のs3-s1,「①の変化が起こった直後のs2-s1」,「②の変化が起こった直後のs2-s3」)となる。
(h-h')*w',h*(w-w') の場合も同様に考えればよい。大小関係が決まる前後のh',w'の値は二分探索により求めることができる。最悪計算量は O(log2(h)+log2(w))<10^2となり、十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_H 100000
#define MAX_W 100000
using namespace std;

int h, w;

void searchMin1(long long& min) {   //h'*(w-'w),(h-h')*w の場合
	int left, right, mid;
	long long s1, s2, s3;
	left = 1; right = h;
	while (left < right) {
		mid = (left + right) / 2;
		s2 = (long long)mid * (w - w / 2); s3 = (long long)(h - mid) * w;
		//printf("s2:%lld s3:%lld\n", s2, s3);
		if (s2 <= s3)
			left = mid + 1;
		else
			right = mid;
	}
	left--;
	s1 = (long long)left * (w / 2); s3 = (long long)(h - left) * w;
	if (min > s3 - s1)
		min = s3 - s1;
	//printf("min:%lld\n", s3 - s1);
	left++;
	if (left == h)
		return;
	s1 = (long long)left * (w / 2); s2 = (long long)left * (w - w / 2); s3 = (long long)(h - left) * w;
	if (s1 <= s3 && s3 <= s2) {
		right = h;
		if (min > s2 - s1)
			min = s2 - s1;
		//printf("min:%lld\n", s2 - s1);
		while (left < right) {
			mid = (left + right) / 2;
			s1 = (long long)mid * (w / 2); s3 = (long long)(h - mid) * w;
			if (s1 <= s3)
				left = mid + 1;
			else
				right = mid;
		}
		if (left == h)
			return;
	}
	s2 = (long long)left * (w - w / 2); s3 = (long long)(h - left) * w;
	if (min > s2 - s3)
		min = s2 - s3;
	//printf("min:%lld\n", s2 - s3);
}

void searchMin2(long long& min) {   //(h-h')*w',h*(w-w') の場合
	int left, right, mid;
	long long s1, s2, s3;
	left = 1; right = w;
	while (left < right) {
		mid = (left + right) / 2;
		s2 = (long long)mid * (h - h / 2); s3 = (long long)(w - mid) * h;
		//printf("s2:%lld s3:%lld\n", s2, s3);
		if (s2 <= s3)
			left = mid + 1;
		else
			right = mid;
	}
	left--;
	s1 = (long long)left * (h / 2); s3 = (long long)(w - left) * h;
	if (min > s3 - s1)
		min = s3 - s1;
	//printf("min:%lld\n", s3 - s1);
	left++;
	if (left == w)
		return;
	s1 = (long long)left * (h / 2); s2 = (long long)left * (h - h / 2); s3 = (long long)(w - left) * h;
	if (s1 <= s3 && s3 <= s2) {
		right = w;
		if (min > s2 - s1)
			min = s2 - s1;
		//printf("min:%lld\n", s2 - s1);
		while (left < right) {
			mid = (left + right) / 2;
			s1 = (long long)mid * (h / 2); s3 = (long long)(w - mid) * h;
			if (s1 <= s3)
				left = mid + 1;
			else
				right = mid;
		}
		if (left == w)
			return;
	}
	s2 = (long long)left * (h - h / 2);s3 = (long long)(w - left) * h;
	if (min > s2 - s3)
		min = s2 - s3;
	//printf("min:%lld\n", s2 - s3);
}

int main() {
	long long min = (long long)MAX_H * MAX_W + 1;
	scanf("%d%d", &h, &w);
	if (h >= 3) {   //一辺がhまたはwである長方形の数が3個の時
		if (h % 3 == 0)
			min = 0;
		else {
			if (min > w)
				min = w;
		}
	}
	if (w >= 3) {
		if (w % 3 == 0)
			min = 0;
		else {
			if (min > h)
				min = h;
		}
	}
	searchMin1(min);   //一辺がhまたはwである長方形の数が1個の時
	searchMin2(min);
	printf("%lld\n", min);
	return 0;
}