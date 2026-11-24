from collections import defaultdict
N = int(input())
d = defaultdict(int)
for _ in range(N):
    s = input()
    d[s.lower()] += 1
ans = 0
for k in d:
    ans = max(ans, d[k])
print(ans)
