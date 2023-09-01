from svgref import *
from copy import deepcopy



addTitle("15 Puzzle")
boardbg = rectangle(320, 200, 320, 320, class_=["bg"])
boardbg.draw()

board = []
moves = []
with open("task5B.dat", "r") as f:
    inp = []
    for line in f:
        inp.append(line.strip().split())
    for i in range(4):
        board.append(inp[i])
    moves = inp[-1]

locations = {}
blankpos = (0, 0)
for i in range(4):
    for j in range(4):
        locations[board[i][j]] = (j, i)
        if (board[i][j] == "*"):
            blankpos = (j, i)

sx = 80
sy = 80
ox = 320
oy = 200

tiles = {}

# generating tiles for each position
for i in range(1, 16):
    x, y = locations[str(i)]
    tile = rectangle(x*sx+ox, y*sy+oy, sx, sy, class_=["shuffled"], filter="url(#bevel)")
    if (i < 10):
        tex = text(x*sx+ox+sx/2-10, y*sy+oy+sy/2+10, str(i), class_=["tex"])
    else:
        tex = text(x*sx+ox+sx/2-18, y*sy+oy+sy/2+10, str(i), class_=["tex"])
    tiles[i] = deepcopy(group(0, 0, shapes=[tile, tex]))

def neighbours(i, j):
    n = []
    if (i > 0):
        n.append((i-1, j))
    if (i < 3):
        n.append((i+1, j))
    if (j > 0):
        n.append((i, j-1))
    if (j < 3):
        n.append((i, j+1))
    return n

t = 0.2

def isPossible(i):
    return blankpos in neighbours(locations[str(i)][0], locations[str(i)][1])

transformations = {}
for i in range(1, 16):
    transformations[i] = (0, 0)

def isInCorrectPos(i):
    x = locations[str(i)][0]
    y = locations[str(i)][1]
    return i == x+ y*4 + 1

def mov(i):
    curLoc = locations[str(i)]
    global blankpos
    temp = blankpos
    y, x = temp
    blankpos = curLoc
    locations[str(i)] = (y, x)
    locations["*"] = (curLoc[0], curLoc[1])
    board[curLoc[0]][curLoc[1]] = "*"
    board[x][y] = str(i)
    dx = x - curLoc[1]
    dx *= sx
    dy = y - curLoc[0]
    dy *= sy
    anim = animateTransform("transform", "translate", t, 2, f"{transformations[i][0]} {transformations[i][1]}", f"{transformations[i][0]+dy} {transformations[i][1]+dx}")
    transformations[i] = (transformations[i][0]+dy, transformations[i][1]+dx)
    tiles[i].addAnimation(anim)

def changeState(i, t):
    if isInCorrectPos(i):
        anim = animation('fill', t, 2, '#DEE7BE')
        tiles[i].shapes[0].addAnimation(anim)
    else:
        tiles[i].shapes[0].addAnimation(animation('fill', t, 2, '#E7CACA'))

def drawAll():
    for i in range(1, 16):
        tiles[i].draw()

for i in range(1, 16):
    if (isInCorrectPos(i)):
        tiles[i].shapes[0].addAnimation(animation('fill', t, 2, '#DEE7BE'))


for move in moves:
    if (isPossible(int(move))):
        tiles[int(move)].shapes[0].addAnimation(animation('fill', t, 2, '#FFFF66'))
        t += 2
        mov(int(move))
        changeState(int(move), t)
        t += 2
    else:
        tiles[int(move)].shapes[0].addAnimation(animation('fill', t, 2, '#F72424'))
        drawAll()
        conclude()
        exit()

drawAll() 
conclude()
        



