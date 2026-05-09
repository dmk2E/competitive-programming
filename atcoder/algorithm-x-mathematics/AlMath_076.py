'''アルゴリズムと工夫点(Sum of difference/CPU: 113 ms Memory: 154588 KB  Length: 245 B)
累積和を用いて解く．
あり得る全ての2組について，差の絶対値の総和を求めればよい．
これは配列Aをソートして考えても問題なく，引く方の値を固定して，
足す方の値は区間和を利用して高速に値を求めればよい．
最悪計算量は，O(N * log2(N)) < 10 ^ 7 となり高速．
'''
n = int(input())
arr_a = list(map(int, input().split()))
arr_a.sort()

sum_a = [0]
for i, a in enumerate(arr_a):
    sum_a.append(sum_a[i] + a)

ans = 0
for i in range(n):
    ans += sum_a[n] - sum_a[i] - arr_a[i] * (n - i)
print(ans)