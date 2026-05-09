'''アルゴリズムと工夫点(All Zero/CPU: 51 ms Memory: 79828 KB  Length: 158 B)
全要素の総和sum とすると，全要素を0にするのに必要な操作回数はsumとなる．
そのため残った回数，k - sum が2で割り切れるのであれば，+1 と -1 する操作を任意の一つの要素について繰り返せば条件を満たす．
最悪計算量は，O(N) < 10 ^ 3 となり十分高速．
'''
n, k = map(int, input().split())
a = list(map(int, input().split()))
sum = 0

for x in a:
    k -= x

print("Yes" if (k >= 0 and k % 2 == 0) else "No")