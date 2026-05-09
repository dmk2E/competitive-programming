'''アルゴリズムと工夫点(Binary Search/CPU:  ms Memory:  KB  Length:  B)
質問が複数存在する場合，ソートして二分探索する方針が有効だが，今回は1回しか質問がないため，線形探索の方が計算量的に良い．
'''
n,x=map(int,input().split())
a=list(map(int,input().split()))
if x in a:
    print("Yes")
else :
    print("No")