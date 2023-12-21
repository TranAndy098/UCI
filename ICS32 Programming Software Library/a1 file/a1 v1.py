from pathlib import Path
import os
def files_first(directorylist):
    firsthalf = []
    lasthalf = []
    for i in directorylist:
        if "." in i:
            firsthalf.append(Path(i))
        else:
            lasthalf.append(Path(i))
    newlist = firsthalf + lasthalf
    return newlist

def subdirectories(directories):
    directory = Path(directories)
    for o in directory.iterdir():
        print(o)
        if "." not in str(o):
            subdirectories(o)

def subdirectories_search(directories, word):
    directory = Path(directories)
    for o in directory.iterdir():
        if "." not in str(o):
            subdirectories_search(o,word)
        else:
            if word in str(o):
                print(o)

def subdirectory_files(directories):
    directory = Path(directories)
    for o in directory.iterdir():
        if "." not in str(o):
            subdirectory_files(o)
        else:
            print(o)

def list_of_contents(command):
    p = Path(command[1])
    directorylist = []
    for o in p.iterdir():
        directorylist.append(str(o))
    directorylist = files_first(directorylist)
    if len(command) == 3:
        if command[2] == "-r":
            recursive_in_all_directories(directorylist)
        elif command[2] == "-f":
            files_in_directory(directorylist)
    elif len(command) > 3:
        if command[2] == "-r":
            if command[3] == "-s":
                    search_in_all_directories(directorylist, command[4])
            if command[3] == "-e":
                file_extension_in_all_directories(directorylist, command[4])
            if command[3] == "-f":
                files_in_all_directories(directorylist)
        elif command[2] == "-s":
            search_in_directory(directorylist,command[3])
        elif command[2] == "-e":
            file_extension(directorylist,command[3])
    else:
        for i in directorylist:
            print(i)

def recursive_in_all_directories(directorylist):
    for i in directorylist:
        if "." in str(i):
            print(i)
        else:
            print(i)
            subdirectories(i)

def files_in_directory(directorylist):
    for i in directorylist:
        if "." in str(i):
            print(i)

def search_in_all_directories(directorylist, word):
    for i in directorylist:
        if "." in str(i):
            if word in str(i):
                print(i)
        else:
            subdirectories_search(i,word)

def search_in_directory(directorylist, word):
    for i in directorylist:
        if word in str(i):
            print(i)

def file_extension_in_all_directories(directorylist, word):
    word = "." + word
    for i in directorylist:
        if "." in str(i):
            if word in str(i):
                print(i)
        else:
            subdirectories_search(i,word)

def files_in_all_directories(directorylist):
    for i in directorylist:
        if "." in str(i):
            print(i)
        else:
            subdirectory_files(i)

def file_extension(directorylist, word):
    word = "." + word
    for i in directorylist:
        if word in str(i):
            print(i)

def delete_file(path):
    splited_path = os.path.split(path)
    path_road = Path(splited_path[0])
    path_stop = splited_path[1]
    current_location = path_road / path_stop
    current_status = current_location.exists()
    if '.dsu' in path_stop:
        if current_status is True:
            os.remove(Path(path))
            print(path, 'DELETED')
        elif current_status is False:
            print('ERROR')
    else:
        print('ERROR')

def create_new_dsu_file(command):
    path_road = Path(command[1])
    path_stop = command[3] + '.dsu'
    current_location = path_road / path_stop
    current_status = current_location.exists()
    if current_status is True:
        print('ERROR')
    elif current_status is False:
        file_path = command[3] + '.dsu'
        file_name = os.path.join(command[1],file_path)
        path_road = open(file_name, 'w')
        path_road.write('')
        path_road.close()
        print(file_name)

def read_through_file(command):
    path = command[1]
    splited_path = os.path.split(path)
    path_road = Path(splited_path[0])
    path_stop = splited_path[1]
    current_location = path_road / path_stop
    current_status = current_location.exists()
    if '.dsu' in path_stop:
        if current_status is True:
            if os.path.getsize(path) == 0:
                print('EMPTY')
            else:
                path_road = open(path)
                for directorylistne in path_road:
                    print(directorylistne, end='')
        elif current_status is False:
            print('ERROR')
    else:
        print('ERROR')

command = input()
while command != 'Q':
    command = command.split(' ')
    if len(command) == 1:
        print('ERROR')
    elif command[0] == 'L':
        list_of_contents(command)
    elif command[0] == 'C':
        if command[2] == '-n':
            create_new_dsu_file(command)
    elif command[0] == 'D':
        path = command[1]
        delete_file(path)
    elif command[0] == 'R':
        read_through_file(command)
    else:
        print('ERROR')
        
    command = input()
