'''アルゴリズムと工夫点(Interval Scheduling Problem/CPU: 599 ms Memory: 136856 KB  Length: 303 B)
区間スケジューリング問題．
有名な貪欲法であるため覚えておこう．
'''
import heapq

n = int(input())
pq = []

while n > 0:
    l, r = map(int, input().split())
    heapq.heappush(pq, (r, l))
    n -= 1

min_last = 0
ans = 0
while len(pq) > 0:
    last, first = heapq.heappop(pq)
    if min_last <= first:
        ans += 1
        min_last = last
print(ans)