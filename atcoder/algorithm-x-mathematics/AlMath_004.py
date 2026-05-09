'''アルゴリズムと工夫点(Product of 3 Integers/CPU: 57 ms Memory: 76852 KB  Length: 44 B)
今回の制約が小さいので問題ないが，整数型の積はオーバーフローに注意．
'''
a,b,c=map(int,input().split())
print(a*b*c)