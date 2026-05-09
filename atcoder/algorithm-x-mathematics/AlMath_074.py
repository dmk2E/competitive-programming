'''アルゴリズムと工夫点(Sum of difference Easy/CPU: 107 ms Memory: 146460 KB  Length: 223 B)
累積和を用いて解く．
求める値を式変形すると，Σ(i ∈ [1, N]) (Σ(j ∈ [i + 1, N]) Aj - Ai * (N - i) ) となる．
このことから，Ai を固定し，累積和を用いて Σ(j ∈ [i + 1, N]) Aj - Ai * (N - i) の部分を高速に計算すればよい．
最悪計算量は，O(N) < 10 ^ 6 となり十分高速．
※ Ai の値は (-N + 2 * i - 1)回足されることを導ければ，累積和を使わずとも解ける
'''
n = int(input())
a = list(map(int, input().split()))

sum_a = [0]
for i in range(n):
    sum_a.append(a[i] + sum_a[i])

ans = 0
for i in range(n):
    ans += sum_a[n] - sum_a[i + 1] - a[i] * (n - i - 1)
print(ans)