'''アルゴリズムと工夫点(Bill Changing Problem/CPU: 52 ms Memory: 80036 KB  Length: 132 B)
貪欲法で解く．
現実世界で流通している紙幣・硬貨は，値段が大きい順に用意していけば，最小枚数となる．
最悪計算量は，O(1) となり十分高速．
'''
n = int(input())
MONEY = [10000, 5000, 1000]
ans = 0

for money in MONEY:    
    ans += n // money
    n %= money
print(ans)