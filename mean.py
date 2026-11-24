T = int(input())
for _ in range(T):
    N = int(input())
    if N == 1:
        print("Yes")
        print(1)
        continue
    if N == 2:
        print("No")
        continue
    A = []
    for i in range(0, N - 3):
        A.append(2 ** (i + 1))
    f = A[-1] if A else 1
    A.extend([f * 2, f * 3, f * 6])
    ok = True
    for x in A:
        if 10**9 < x:
            ok = False
            break
    if ok:
        print("Yes")
        print(*A)
    else:
        print("No")
