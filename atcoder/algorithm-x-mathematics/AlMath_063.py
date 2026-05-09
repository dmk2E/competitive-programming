'''アルゴリズムと工夫点(Move on Squares 2/CPU: 59 ms Memory: 76704 KB  Length: 52 B)
偶奇で場合分けして考える．
Nが偶数の場合は必勝法が存在するが，Nが奇数の場合は必ず達成できないことが証明できる（参考書参照）．
'''
n = int(input())
print("Yes" if n%2 == 0 else "No")