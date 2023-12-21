from pathlib import Path

def filefirst(list):
    fl = []
    ll = []
    for i in li:
        if "." in i:
            fl.append(Path(i))
        else:
            ll.append(Path(i))
    nl = fl + ll
    return nl

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


command = input()
while command != 'Q':
    if command[0] == 'L':
        command = command.split(' ')
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
    command = input()
