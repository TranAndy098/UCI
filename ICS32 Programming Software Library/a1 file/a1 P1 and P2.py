from pathlib import Path
import os
def filefirst(list):
    fl = []
    ll = []
    for i in list:
        if "." in i:
            fl.append(Path(i))
        else:
            ll.append(Path(i))
    nl = fl + ll
    return nl

def l(command):
    p = Path(command[1])
    li = []
    for o in p.iterdir():
        li.append(str(o))
    li = filefirst(li)
    if len(command) == 3:
        if command[2] == "-r":
            r(li)
        elif command[2] == "-f":
            f(li)
    elif len(command) > 3:
        if command[2] == "-r":
            if command[3] == "-s":
                rs(li, command[4])
            if command[3] == "-e":
                re(li, command[4])
            if command[3] == "-f":
                rf(li)
        elif command[2] == "-s":
            s(li,command[3])
        elif command[2] == "-e":
            e(li,command[3])
    else:
        for i in li:
            print(i)

def sub(dir):
    dir = Path(dir)
    for o in dir.iterdir():
        print(o)
        if "." not in str(o):
            sub(o)

def subs(dir, word):
    dir = Path(dir)
    for o in dir.iterdir():
        if "." not in str(o):
            subs(o,word)
        else:
            if word in str(o):
                print(o)
def subf(dir):
    dir = Path(dir)
    for o in dir.iterdir():
        if "." not in str(o):
            subf(o)
        else:
            print(o)

def r(list):
    for i in list:
        if "." in str(i):
            print(i)
        else:
            print(i)
            sub(i)

def f(list):
    for i in list:
        if "." in str(i):
            print(i)

def rs(list, word):
    for i in list:
        if "." in str(i):
            if word in str(i):
                print(i)
        else:
            subs(i,word)

def s(list, word):
    for i in list:
        if word in str(i):
            print(i)

def re(list, word):
    word = "." + word
    for i in list:
        if "." in str(i):
            if word in str(i):
                print(i)
        else:
            subs(i,word)

def rf(list):
    for i in list:
        if "." in str(i):
            print(i)
        else:
            subf(i)

def e(list, word):
    word = "." + word
    for i in list:
        if word in str(i):
            print(i)

def d(path):
    n = os.path.split(path)
    f = Path(n[0])
    l = n[1]
    g = f / l
    h = g.exists()
    if '.dsu' in l:
        if h is True:
            os.remove(Path(path))
            print(path, 'DELETED')
        elif h is False:
            print('ERROR')
    else:
        print('ERROR')

def cn(command):
    f = Path(command[1])
    l = command[3] + '.dsu'
    g = f / l
    h = g.exists()
    if h is True:
        print('ERROR')
    elif h is False:
        y = command[3] + '.dsu'
        x = os.path.join(command[1],y)
        f = open(x, 'w')
        f.write('')
        f.close()
        print(x)

def r2(command):
    path = command[1]
    n = os.path.split(path)
    f = Path(n[0])
    l = n[1]
    g = f / l
    h = g.exists()
    if '.dsu' in l:
        if h is True:
            if os.path.getsize(path) == 0:
                print('EMPTY')
            else:
                f = open(path)
                for line in f:
                    print(line,end='')
        elif h is False:
            print('ERROR')
    else:
        print('ERROR')

command = input()
while command != 'Q':
    command = command.split(' ')
    if len(command) == 1:
        print('ERROR')
    elif command[0] == 'L':
        l(command)
    elif command[0] == 'C':
        if command[2] == '-n':
            cn(command)
    elif command[0] == 'D':
        path = command[1]
        d(path)
    elif command[0] == 'R':
        r2(command)
    command = input()
