import pygame
from pygame.locals import *
from random import randint

pygame.init()
screen = pygame.display.set_mode((640, 480))

def f(u, v):
    a, b = 1, 1
    return -v + a*u*u - b, u

cols = [
    (255, 255, 255),
    (255, 255, 0),
    (0, 255, 255),
    (255, 0, 255),
]

for u0 in range(-8, 8):
    u0 *= 0.5
    for v0 in range(-8, 8):
        v0 *= 0.5 * 32 / 24
        u, v = u0, v0
        lastp = None
        for i in range(5):
            p = (int(u * 32) + 320, int(v * 24) + 240)
            #print(u, v)
            #screen.set_at(p, cols[i % len(cols)])
            if lastp is not None:
                color = (randint(0,255), randint(0,255), randint(0,255))
                pygame.draw.line(screen, color, lastp, p)
            lastp = p
            u, v = f(u, v)

pygame.display.update()

while True:
    e = pygame.event.wait()
    if e.type == QUIT or (e.type == KEYDOWN and e.key in [K_ESCAPE, K_SPACE]):
        exit()
