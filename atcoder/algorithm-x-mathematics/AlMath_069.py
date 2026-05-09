'''アルゴリズムと工夫点(Product Max/CPU: 58 ms Memory: 80080 KB  Length: 88 B)
区間の端のみを用いて全探索．
最悪計算量は，O(1) となり十分高速．
'''
a, b, c, d = map(int, input().split())
print(max(max(a * c, a * d), max(b * c, b * d)))