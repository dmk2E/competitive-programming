'''アルゴリズムと工夫点(Three Cards/CPU: 97 ms Memory: 108408 KB  Length: 255 B)
余事象を考えるのが楽．
今回の場合，3つの条件全てを満たす，3つの整数の選び方の数 が余事象となる．
そこで，白色カードの整数値wを固定した時，他の2枚のカードの書き込める整数の範囲は，
[max(1, w - K + 1), min(n, w + K - 1)] となる．
ここで，K は最大でも5であるから，全探索しても，最悪計算量は O(N * K ^ 2) < 10 ^ 7 となり高速．

'''
n, k = map(int, input().split())

sum = 0
for w in range(1, n + 1):
   for b in range(max(1, w - k + 1), min(n, w + k - 1) + 1):
      for g in range(max(1, w - k + 1), min(n, w + k - 1) + 1):
         sum += abs(b - g) < k

print(n * n * n - sum)