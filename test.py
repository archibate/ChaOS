def f(u, v):
    a, b = 0.1, 0.0
    return -v + a*u*u - b, u

print('\033[2J')

for u in range(-5, 5):
    for v in range(-5, 5):
        print('\033[1;3%dm' % ((u + v) % 8))
        for i in range(1):
            print('\033[%d;%dH#' % (u * 62 + 62, v * 20 + 20))
            u, v = f(u, v)

print('\033[0m')
print('KMGTPEZY')
