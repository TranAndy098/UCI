#using list make the path string \
command = input()
command = command.split(' ')
print(type(command))
print(command)
f = []
p = ""
for i in range(len(command)):
    print(i)
    if i > 0:
        print(command[i])
        if len(command[i]) != 2:
            if command[i][0] != '-':
                if p == "":
                    p += str(command[i])
                    o = i
                else:
                    p += ' ' + str(command[i])
                    o = i
        elif len(command[i]) == 2:
            if command[i][0] == '-':
                break
print(o)
print(p)
f.append(command[0])
f.append(p)
for i in range(len(command)):
    if i > o:
        f.append(command[i])
print(f)
        
         
