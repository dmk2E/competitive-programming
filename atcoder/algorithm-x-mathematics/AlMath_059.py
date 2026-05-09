'''アルゴリズムと工夫点(Power of Two/CPU: 56 ms Memory: 76708 KB  Length: 51 B)
周期性を利用して高速化．
2 -> 4 -> 8 -> 6 -> 2 -> ... とループすることを利用する．
最悪計算量は，O(1) となり十分高速．
'''
n=int(input());n-=1
ans=[2,4,8,6]
print(ans[n%4])