from pathlib import Path
import os
def files_first(directorylist):
    """rearranges a list of directories to get files first in the list."""
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
    """recursion through directories and subdirectories to get all files and folders until none are left."""
    directory = Path(directories)
    for o in directory.iterdir():
        print(o)
        if "." not in str(o):
            subdirectories(o)

def subdirectories_search(directories, word):
    """recursion trhgouh all directories and subdirectories to find a file with the word as its name."""
    directory = Path(directories)
    for o in directory.iterdir():
        if "." not in str(o):
            subdirectories_search(o,word)
        else:
            if word in str(o):
                print(o)

def subdirectory_files(directories):
    """recursion through a directory to get all the files that are subdirectories of the given directory."""
    directory = Path(directories)
    for o in directory.iterdir():
        if "." not in str(o):
            subdirectory_files(o)
        else:
            print(o)

def list_of_contents(command):
    """goes through a directory and makes a list of all of the directories in the given location."""
    p = Path(command[1])
    directorylist = []
    for o in p.iterdir():
        directorylist.append(str(o))
    directorylist = files_first(directorylist)
    if len(command) == 3:
        if command[2] == "-r":
            for i in directorylist:
                if "." in str(i):
                    print(i)
                else:
                    print(i)
                    subdirectories(i)
        elif command[2] == "-f":
            for i in directorylist:
                if "." in str(i):
                    print(i)
    elif len(command) > 3:
        if command[2] == "-r":
            if command[3] == "-s":
                for i in directorylist:
                    if "." in str(i):
                        if command[4] in str(i):
                            print(i)
                    else:
                        subdirectories_search(i,command[4])
            if command[3] == "-e":
                word = "." + command[4]
                for i in directorylist:
                    if "." in str(i):
                        if word in str(i):
                            print(i)
                    else:
                        subdirectories_search(i,word)
            if command[3] == "-f":
                for i in directorylist:
                    if "." in str(i):
                        print(i)
                    else:
                        subdirectory_files(i)
        elif command[2] == "-s":
            for i in directorylist:
                if command[3] in str(i):
                    print(i)
        elif command[2] == "-e":
            word = "." + command[3]
            for i in directorylist:
                if word in str(i):
                    print(i)
    else:
        for i in directorylist:
            print(i)

def delete_file(path):
    """delete the file with the given file path."""
    current_location = Path(os.path.split(path)[0]) / os.path.split(path)[1]
    current_status = (Path(os.path.split(path)[0]) / os.path.split(path)[1]).exists()
    if '.dsu' in os.path.split(path)[1]:
        if current_status is True:
            os.remove(Path(path))
            print(path, 'DELETED')
        elif current_status is False:
            print('ERROR')
    else:
        print('ERROR')

def create_new_dsu_file(command):
    """creates a new file with the file extension .dsu in the path given."""
    #path_road = Path(command[1])
    #path_stop = command[3] + '.dsu'
    #current_location = Path(command[1]) / (command[3] + '.dsu')
    current_location = Path(command[1]) / (command[3] + '.dsu')
    current_status = current_location.exists()
    if current_status is True:
        print('ERROR')
        current_location = 'ERROR'
    elif current_status is False:
        file_name = os.path.join(command[1],(command[3] + '.dsu'))
        path_road = open(file_name, 'w')
        path_road.write('')
        path_road.close()
        print(file_name)

def read_through_file(command):
    """with the given path, will read through the contents of the file at the end of the path."""
    #path = command[1]
    #splited_path = os.path.split(path)
    #path_road = Path(splited_path[0])
    #path_stop = splited_path[1]
    #current_location = (Path(os.path.split(command[1])[0]) / os.path.split(command[1])[1])
    current_status = (Path(os.path.split(command[1])[0]) / os.path.split(command[1])[1]).exists()
    if '.dsu' in os.path.split(command[1])[1]:
        if current_status is True:
            if os.path.getsize(command[1]) == 0:
                print('EMPTY')
            else:
                path_road = open(command[1])
                for directorylistne in path_road:
                    print(directorylistne, end='')
        elif current_status is False:
            print('ERROR')
    else:
        print('ERROR')

def spacer(command):
    new_command = []
    full_path = ""
    for part_index in range(len(command)):
        if part_index > 0:
            if len(command[part_index]) != 2:
                if command[part_index][0] != '-':
                    if full_path == "":
                        full_path += str(command[part_index])
                        last_part_index = part_index
                    else:
                        full_path += ' ' + str(command[part_index])
                        last_part_index = part_index
            elif len(command[part_index]) == 2:
                if command[part_index][0] == '-':
                    break
    new_command.append(command[0])
    new_command.append(full_path)
    for ending_commands in range(len(command)):
        if ending_commands > last_part_index:
            new_command.append(command[ending_commands])
    return new_command

if __name__ == '__main__':
    command = input()
    while command != 'Q':
        try:
            if len(command) > 1:
                if type(command) == str:
                    commands = command.split(' ')
                    command = spacer(commands)
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
        except:
            print('ERROR')
        command = input()
