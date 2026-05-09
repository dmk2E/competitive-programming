'''アルゴリズムと工夫点(Sum of N Integers/CPU: 62 ms Memory: 76752 KB  Length: 92 B)
pythonだと，nの値は用いず，標準入力を正しく受け取れる．
'''
n=int(input())
a=list(map(int,input().split()))
sum=0
for x in a:
    sum+=x
print(sum)