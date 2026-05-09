'''アルゴリズムと工夫点(Answer Exam Randomly/CPU:  ms Memory:  KB  Length:  B)
参考書に記述してある通り，期待値の線型性を用いることで，2^N 通りの組み合わせ列挙を回避できる．
'''
ans=0.0
n=int(input())
while n>0:
    p,q=map(int,input().split())
    ans+=q/p
    n-=1
print(ans)