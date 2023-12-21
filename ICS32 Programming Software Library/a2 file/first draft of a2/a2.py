from pathlib import Path
import os
from Profile import Profile, Post
import ds_client as dsc

def menu():
    """prints the user interface."""
    print('Select from the menu below:')
    print('L [INPUT]: prints all results from a directory')   
    print('L [INPUT] -f: prints files from a directory')
    print('L [INPUT] -s [INPUT]: prints file input from a directory')
    print('L [INPUT] -e [INPUT]: prints file input extension from a directory')
    print('L [INPUT] -r: prints from all directories and subdirectories')
    print('L [INPUT] -r -f: prints all files from all directories')
    print('L [INPUT] -r -s [INPUT]: prints file input from all directories')
    print('L [INPUT] -r -e [INPUT]: prints file input extension from all directories')
    print('C [INPUT] -n [INPUT]: creates file with profile inside')
    print('D [INPUT]: deletes file in directory')
    print('R [INPUT]: prints all file contents')
    print('P [INPUT]: loads file contents and offers information')
    print('P [INPUT] -a: adds post to profile')
    print('P [INPUT] -d: delete post from profile')
    print('P [INPUT] -g: prints all posts from profile')
    print('Q: quits the Program')

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
    """recursion through all directories and subdirectories to get a list of evey single directory and subdirectory."""
    for i in directorylist:
        if "." in str(i):
            print(i)
        else:
            print(i)
            subdirectories(i)

def files_in_directory(directorylist):
    """gets all of the files in a given directory."""
    for i in directorylist:
        if "." in str(i):
            print(i)

def search_in_all_directories(directorylist, word):
    """search all directories to find files matching the given name."""
    for i in directorylist:
        if "." in str(i):
            if word in str(i):
                print(i)
        else:
            subdirectories_search(i,word)

def search_in_directory(directorylist, word):
    """search in a given directory to get a file with the matching name."""
    for i in directorylist:
        if word in str(i):
            print(i)

def file_extension_in_all_directories(directorylist, word):
    """searches through all directories to find files with the same file extensionas the one given."""
    word = "." + word
    for i in directorylist:
        if "." in str(i):
            if word in str(i):
                print(i)
        else:
            subdirectories_search(i,word)

def files_in_all_directories(directorylist):
    """recursion through all directories and subdirectories to find files."""
    for i in directorylist:
        if "." in str(i):
            print(i)
        else:
            subdirectory_files(i)

def file_extension(directorylist, word):
    """searches through a specific directory to find files with the given file extension."""
    word = "." + word
    for i in directorylist:
        if word in str(i):
            print(i)

def delete_file(path):
    """delete the file with the given file path."""
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
    """creates a new file with the file extension .dsu in the path given."""
    path_road = Path(command[1])
    path_stop = command[3] + '.dsu'
    current_location = path_road / path_stop
    current_status = current_location.exists()
    if current_status is True:
        print('ERROR')
        current_location = 'ERROR'
    elif current_status is False:
        file_path = command[3] + '.dsu'
        file_name = os.path.join(command[1],file_path)
        path_road = open(file_name, 'w')
        path_road.write('')
        path_road.close()
        print(file_name)
    return current_location

def read_through_file(command):
    """with the given path, will read through the contents of the file at the end of the path."""
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
                    print(directorylistne, end='/n')
        elif current_status is False:
            print('ERROR')
    else:
        print('ERROR')

def profile_indicator(path):
    """ask for user profile information and then save profile"""
    p = Profile()
    p.dsuserver = input("What is the name of your dsuserver?")
    p.username = input("What is your username for the dsuserver?")
    p.password = input("What is you password for your username on the dsuserver?")
    bio = input("Would you like to set up a bio for your profile? (Y/N)")
    if bio == "Y":
        p.bio = input("What is the bio for your profile?")
    profilepost = input("Would you like to add a post at this time? (Y/N)")
    if profilepost == "Y":
        msg = input("What would you like in your post?")
        post = Post(msg)
        p.add_post(post)
        if bio == 'N':
            dsc.send(p.dsuserver,port,p.username,p.password,p.get_posts()[-1])
        elif bio == 'Y':
            dsc.send(p.dsuserver,port,p.username,p.password,p.get_posts()[-1],p.bio)
    p.save_profile(path)

def desired_profile(profile):
    """ask the user if they want any of the profile information regarding the proifle identiy."""
    dsuserver = input("Do you want your dsuserver from your profile? (Y/N)")
    while dsuserver != "N":
        if dsuserver == 'Y':
            print(profile.dsuserver)
            break
        else:
            print('Incorrect Response Format')
            dsuserver = input("Do you want your dsuserver from your profile? (Y/N)")
    username = input("Do you want your username from your profile? (Y/N)")
    while username != "N":
        if username == 'Y':
            print(profile.username)
            break
        else:
            print('Incorrect Response Format')
            username = input("Do you want your username from your profile? (Y/N)")
    password = input("Do you want your password from your profile? (Y/N)")
    while password != "N":
        if password == 'Y':
            print(profile.password)
            break
        else:
            print('Incorrect Response Format')
            password = input("Do you want your password from your profile? (Y/N)")
    bio = input("Do you want your bio from your profile? (Y/N)")
    while bio != "N":
        if bio == 'Y':
            print(profile.bio)
            break
        else:
            print('Incorrect Response Format')
            bio = input("Do you want your bio from your profile? (Y/N)")

def deleting_post(profile, path):
    """deletes a post if the index exists."""
    index = int(input("What index of your posts would you like to delete? (Integers Only)"))
    posts = profile.get_posts()
    if index <= len(posts) - 1:
        profile.del_post(index)
        profile.save_profile(path)
    else:
        print('ERROR')
        

def adding_post(profile, path):
    """adds a post to the user profile."""
    msg = input("What would you like in your post?")
    post = Post(msg)
    profile.add_post(post)
    profile.save_profile(path)
    dsc.send(profile.dsuserver,port,profile.username,profile.password,profile.get_posts()[-1])

def getting_post(profile):
    """gets a list of all posts and prints them."""
    posts = profile.get_posts()
    if len(posts) > 0:
        for post in posts:
            print('{} at {}'.format(post['entry'], post['timestamp']))
    else:
        print('EMPTY')

def load(command):
    """make sure profile can be loaded and it also exists."""
    path = command[1]
    splited_path = os.path.split(path)
    path_road = Path(splited_path[0])
    path_stop = splited_path[1]
    current_location = path_road / path_stop
    path = current_location
    current_status = current_location.exists()
    if current_status == True:
        if os.path.getsize(path) == 0:
            print('EMPTY')
        else:
            p2 = Profile()
            p2.load_profile(path)
            if len(command) == 2:
                desired_profile(p2)
            if len(command) == 3:
                if command[2] == '-a':
                    adding_post(p2, path)
                elif command[2] == '-d':
                    deleting_post(p2, path)
                elif command[2] == '-g':
                    getting_post(p2)
                else:
                    print('ERROR')
    elif current_status is False:
        print('ERROR')
    
menu()
command = input()
port = 2021
while command != 'Q':
    command = command.split(' ')
    if len(command) == 1:
            print('ERROR')
    elif os.path.exists(command[1]) == True:
        if command[0] == 'L':
            if len(command) == 2:
                list_of_contents(command)
            else:
                print('ERROR')
        elif command[0] == 'C':
            if command[2] == '-n':
                dsupath = create_new_dsu_file(command)
                if dsupath != 'ERROR':
                    profile_indicator(dsupath)
            else:
                print('ERROR')
        elif command[0] == 'D':
            path = command[1]
            delete_file(path)
        elif command[0] == 'R':
            read_through_file(command)
        elif command[0] == 'P':
            load(command)
        else:
            print('ERROR')
    else:
        print('ERROR')
    command = input()
