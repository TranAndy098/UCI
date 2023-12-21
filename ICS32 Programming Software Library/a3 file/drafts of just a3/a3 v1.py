from pathlib import Path
import os
from Profile import Profile, Post
import ds_client as dsc
from ExtraCreditAPI import ExtraCreditAPI
from OpenWeather import OpenWeather
from LastFM import LastFM

def menu():
    """
    Prints the user interface for the user to know how and what inputs they can put in.
    Will only print this once at the beginning of the code.
    If user does not input a correct input, they will be prompted to input another input.
    """
    print('Select from the menu below:')
    print('L [INPUT]: prints all results from a directory')   
    print('L [INPUT] -f: prints files from a directory')
    print('L [INPUT] -s [INPUT]: prints file input from a directory')
    print('L [INPUT] -e [INPUT]: prints file input extension from a directory')
    print('L [INPUT] -r: prints from all directories and subdirectories')
    print('L [INPUT] -r -f: prints all files from all directories')
    print('L [INPUT] -r -s [INPUT]: prints file input from all directories')
    print('L [INPUT] -r -e [INPUT]: prints file input extension from all directories')
    print('C [INPUT] -n [INPUT]: creates file with a new profile inside and on server')
    print('D [INPUT]: deletes file in directory')
    print('R [INPUT]: prints all file contents')
    print('P [INPUT]: loads file contents and offers information')
    print('P [INPUT] -a: adds post to an existing profile')
    print('P [INPUT] -d: delete post from profile')
    print('P [INPUT] -g: prints all posts from profile')
    print('P [INPUT] -b: add or update bio of profile')
    print('P [INPUT] -u: update dsuserver, username, and/or password of profile')
    print('Supported shorcut keywords for post:')
    print('OpenWeather:')
    print('@weather - description of weather')
    print('@weather_description - description of weather')
    print('@weather_temperature - temperature today')
    print('@weather_high_temperature - highest temperature today')
    print('@weather_low_temperature - lowest temperature today')
    print('@weather_longitude - longitude of the weather location')
    print('@weather_latitude - latitude of the weather location')
    print('@weather_humidity - percetnage of humanity')
    print('@weather_sunset - time of sunset')
    print('@weather_sunrise - time of sunrise')
    print('@weather_windspeed - speed of wind today')
    print('@weather_cloudiness - percentage of cloudiness')
    print('@weather_city - city name for weather')
    print('LastFM:')
    print('@lastfm - top 5 artists of today')
    print('@lastfm_top_5artists - top 5 artists of today')
    print('@lastfm_top_5tracks - top 5 tracks of today')
    print('@lastfm_top_5albums - top 5 albums of today')
    print('@lastfm_top_5tags - top 5 tags of today')
    print('ExtraCreditAPI:')
    print('@extracredit - a random quote')
    print('Q: quits the Program')


def files_first(directorylist):
    """
    Will go through a directory and print the files first.
    Will create a second list of the folders.
    After all the files have been printed, the folders will then be printed.
    """
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
    """
    Will go through the user input's path and print every file.
    When it reaches a folder it will recursion through the folder's directories and repeat this funciton over and over again.
    """
    directory = Path(directories)
    for o in directory.iterdir():
        print(o)
        if "." not in str(o):
            subdirectories(o)


def subdirectories_search(directories, word):
    """
    Will go through all the directories and subdirectories from the path from the user's input.
    Will iterate through all of the elements of the directory list, and print the elements that have the matching file name from the user's input.
    if not found in that directory, will recustion through the elements that are folders and have subdirectories.
    The elements with the matching file name from the user's input indicate it is the file with the file name desired.
    """
    directory = Path(directories)
    for o in directory.iterdir():
        if "." not in str(o):
            subdirectories_search(o,word)
        else:
            if word in str(o):
                print(o)


def subdirectory_files(directories):
    """
    Will go though the user input's path's directory list.
    If the element is a file it will print the file name.
    If it is a folder, it will iterate through the folder and repeat this function over and over again.
    """
    directory = Path(directories)
    for o in directory.iterdir():
        if "." not in str(o):
            subdirectory_files(o)
        else:
            print(o)


def list_of_contents(command):
    """
    Will execute this function if the user's input has the "L" command in it.
    Will take in the user's command input, then determine which function to do.
    """
    p = Path(command[1])
    directorylist = []
    try:
        for o in p.iterdir():
            directorylist.append(str(o))
        directorylist = files_first(directorylist)
        if len(command) == 3:
            if command[2] == "-r":
                recursive_in_all_directories(directorylist)
            elif command[2] == "-f":
                files_in_directory(directorylist)
            else:
                print('ERROR')
        elif len(command) > 3:
            if command[2] == "-r":
                if command[3] == "-s":
                        search_in_all_directories(directorylist, command[4])
                elif command[3] == "-e":
                    file_extension_in_all_directories(directorylist, command[4])
                elif command[3] == "-f":
                    files_in_all_directories(directorylist)
                else:
                    print('ERROR')
            elif command[2] == "-s":
                search_in_directory(directorylist,command[3])
            elif command[2] == "-e":
                file_extension(directorylist,command[3])
            else:
                print('ERROR')
        else:
            for i in directorylist:
                print(i)
    except:
        print('ERROR')


def recursive_in_all_directories(directorylist):
    """
    This function will go through a directory list.
    If the element is a file or with "." then it will print the file.
    If it does not then it will recursion through that path or folder and repeat this whole function over and over again until it can no longer.
    """
    for i in directorylist:
        if "." in str(i):
            print(i)
        else:
            print(i)
            subdirectories(i)


def files_in_directory(directorylist):
    """
    Will take in the list of the items in the specfic directory desired by the user.
    Will iterate through the list and print the elements with ".".
    The elements with the "." indicate that they are files.
    """
    for i in directorylist:
        if "." in str(i):
            print(i)


def search_in_all_directories(directorylist, word):
    """
    Will go through all the directories and subdirectories from the path from the user's input.
    Will recursion through all of the elements of the directory list, and print the elements that have the matching file name from the user's input.
    The elements with the matching file name from the user's input indicate it is the file with the file name desired.
    """
    for i in directorylist:
        if "." in str(i):
            if word in str(i):
                print(i)
        else:
            subdirectories_search(i,word)


def search_in_directory(directorylist, word):
    """
    Will go through all the elements in the directory from the path from the user's input.
    Will then iterate through the elements and print the file with the matching name that the user desires in their input.
    """
    for i in directorylist:
        if word in str(i):
            print(i)


def file_extension_in_all_directories(directorylist, word):
    """
    Will go through all the directories and subdirectories from the path from the user's input.
    Will recursion through all of the elements of the directory list, and print the elements that have the matching file extension from the user's input.
    The elements with the matching file extension from the user's input indicate that those are files with the file extension desired.
    """
    if '.' not in word:
        word = "." + word
    for i in directorylist:
        if "." in str(i):
            if word in str(i):
                print(i)
        else:
            subdirectories_search(i,word)


def files_in_all_directories(directorylist):
    """
    Will go through all the directories and subdirectories from the path from the user's input.
    Will recursion through all of the elements of the directory list, and print the elements that have ".".
    The elements with the "." indicate that they are files.
    """
    for i in directorylist:
        if "." in str(i):
            print(i)
        else:
            subdirectory_files(i)


def file_extension(directorylist, word):
    """
    Will take in the list of the items in the specfic directory desired by the user.
    Will iterate through the list and print the elements with the matching file extension from the user's input.
    """
    if '.' not in word:
        word = "." + word
    for i in directorylist:
        if word in str(i):
            print(i)


def delete_file(path):
    """
    Will use the user input's path to locate the file.
    If the file exists then it will delete the file and print "DELETED".
    If the file does not exist then it will print "ERROR".
    """
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
    """
    Creates a new file with the file extension .dsu in the path given.
    Will create a new dsu file with the name desired in the user's input.
    Will create it in the user's deired path from the user's input.
    Will only create if the file does not already exist, it doe exist then it will print "ERROR".
    """
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
    return current_location


def read_through_file(command):
    """with the given path, will read through the contents of the file at the end of the path.
    Will use the user given path to find the dsu file.
    If the file exists and is not empty then it will print the contents of the dsu file.
    If the file exists but is empty then it will print "EMPTY".
    If the file does not exists then it will print "ERROR" and quit the funciton.
    """
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


def change_message(message):
    """
    Will take in the message and transclude through it and ask user if for the required data or use the presets.
    """
    print('Message before possible changes:{}'.format(message))
    if '@e' in message:
        ec = ExtraCreditAPI()
        message = ec.transclude(message)
    if '@w' in message:
        location_choice = input('Do you want to use Irvine, CA as the location for the weather? (Y/N)')
        while location_choice != 'Y':
            if location_choice == 'N':
                zipcode = str(input('What is your 5 digit zip code?'))
                ccode = str(input('What is your country code?'))
                if (len(zipcode) == 5) and ((ccode.isspace() == False) and (ccode != '')):
                    break
                else:
                    print('invalid zipcode and/or country code format')
            else:
                print('Please input correct format')
                location_choice = input('Do you want to use Irvine, CA as the location for the weather? (Y/N)')
        if location_choice == 'Y':
            zipcode = "92697"
            ccode = "US"
        apikey_choice = input('Do you want to use your own OpenWeather apikey? (Y/N)')
        while apikey_choice != 'N':
            if apikey_choice == 'Y':
                apikey = str(input('What is your OpenWeather apikey?'))
                if (apikey.isspace() == False) and (apikey != ''):
                    break
                else:
                    print('invalid apikey format')
            else:
                print('Please input correct format')
                apikey_choice = input('Do you want to use your own OpenWeather apikey? (Y/N)')
        if apikey_choice == 'N':
            apikey = "824eab18432eee3e404cff1e4df28b87"
        open_weather = OpenWeather(zipcode,ccode,apikey)
        message = open_weather.transclude(message)
    if '@l' in message:
        apikey_choice = input('Do you want to use your own LastFM apikey? (Y/N)')
        while apikey_choice != 'N':
            if apikey_choice == 'Y':
                apikey = str(input('What is your LastFM apikey?'))
                if (apikey.isspace() == False) and (apikey != ''):
                    break
                else:
                    print('invalid apikey format')
            else:
                print('Please input correct format')
                apikey_choice = input('Do you want to use your own LastFM apikey? (Y/N)')
        if apikey_choice == 'N':
            apikey = "8725d482c1ff93a7147673296a1f4144"
        lf = LastFM(apikey)
        message = lf.transclude(message)
    print('Message after possible changes:{}'.format(message))
    return message


def profile_indicator(path):
    """
    ask for user profile information and then save profile
    Will ask the user for the information to create a new profile in a new dsu file.
    Will ask for the server, username, and password.
    Will ask if the user wants to input a bio for the profile.
    Will ask if the user wants to input a post.
    If the user puts in a post then it will send the post to the server using the server module.
    If there is a bio then it will send it, if not then it will not send it.
    If there is a bio and no post then, the bio will be sent on its own, but you won't be able to send it until you send a post.
    """
    p = Profile()
    p.dsuserver = input("What is the name of your dsuserver?")
    while (p.dsuserver.isspace() == True) or (p.dsuserver == ''):
            p.dsuserver = input("Cannot have only white space in bio, What is the name of your dsuserver? (Y/N)")
    p.username = input("What is your username for the dsuserver?")
    while (p.username.isspace() == True) or (p.username == ''):
            p.username = input("Cannot have only white space in bio, What is your username for the dsuserver? (Y/N)")
    p.password = input("What is your password for your username on the dsuserver?")
    while (p.password.isspace() == True) or (p.password == ''):
            p.password = input("Cannot have only white space in bio, What is your password for your username on the dsuserver? (Y/N)")
    while p.password == p.username:
        print('Password must be diffrent than Username')
        p.password = input("What is you new password for your username on the dsuserver?")
    bio = input("Would you like to set up a bio for your profile? (Y/N)")
    while bio != "N":
        if bio == 'Y':
            p.bio = input("What is the bio for your profile?")
            if (p.bio.isspace() == True) or (p.bio == ''):
                bio = input("Cannot have only white space in bio, Would you like to set up a bio for your profile? (Y/N)")
                del p.bio
            else:
                if '\"' in p.bio:
                    p.bio = p.bio.replace('\"','\'\'')
                p.bio = change_message(p.bio)
                break
        else:
            print('Please input the correct answer format')
            bio = input("Would you like to set up a bio for your profile? (Y/N)")
    profilepost = input("Would you like to add a post at this time? (Y/N)")
    while profilepost != "N":
        if profilepost == 'Y':
            msg = input("What would you like in your post?")
            if (msg.isspace() == True) or (msg == ''):
                profilepost = input("Cannot have only white space in post, Would you like to add a post at this time? (Y/N)")
                del msg
            else:
                if '\"' in msg:
                    msg = msg.replace('\"','\'\'')
                break
        else:
            print('Please input the correct answer format')
            profilepost = input("Would you like to add a post at this time? (Y/N)")
    if profilepost == "Y":
        msg = change_message(msg)
        post = Post(msg)
        p.add_post(post)
        if bio == 'N':
            dsc.send(p.dsuserver,port,p.username,p.password,p.get_posts()[-1])
        elif bio == 'Y':
            dsc.send(p.dsuserver,port,p.username,p.password,p.get_posts()[-1],p.bio)
    if profilepost == 'N' and bio == 'Y':
        dsc.send(p.dsuserver,port,p.username,p.password,None,p.bio)
    p.save_profile(path)


def desired_profile(profile):
    """
    After loading the profile and making sure it exists.
    This function will run through the information of the profile.
    It will asks the user whether they want to know the information that is being asked.
    If they do then the system will print it.
    If they don't then the system will proceed to the next information.
    """
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
    """
    Will take in the user profile from the input path's dsu file.
    The user wil input the index for the post they want to delete in their profile.
    Then search for the post matching the user's input index.
    It will delete the post if the index exists.
    Then save the profile after the post is deleted.
    """
    posts = profile.get_posts()
    if len(posts) > 0:
        for i in range(len(posts)):
            print('Post {}: {} at {}'.format(i + 1, posts[i]['entry'], posts[i]['timestamp']))
    else:
        print('EMPTY')
    if len(posts) > 0:
        index = int(input("Which of your posts would you like to delete? (Integers Only)"))
        index = index - 1
        posts = profile.get_posts()
        if index <= len(posts) - 1:
            profile.del_post(index)
            profile.save_profile(path)
            print("Post {} Deleted".format(index+1))
        else:
            print('ERROR')
        

def adding_post(profile, path):
    """
    Will take in the user profile from the input path's dsu file, and then add a new post.
    The user wil input the message for the post they want to add to their profile.
    After it is added, this function will use the client module and send this new post to the server.
    """
    msg = str(input("What would you like in your post?"))
    while (msg.isspace() == True) or (msg == ''):
        msg = str(input("Post can not only be whitespace, What would you like in your post?"))
    if '\"' in msg:
        msg = msg.replace('\"','\'\'')
    msg = change_message(msg)
    post = Post(msg)
    profile.add_post(post)
    profile.save_profile(path)
    dsc.send(profile.dsuserver,port,profile.username,profile.password,profile.get_posts()[-1])


def getting_post(profile):
    """
    Will load the file and then create a list of all of the posts in the file and its timestamps.
    The elements in the list will have the format of "entry" at "timestamp".
    """
    posts = profile.get_posts()
    if len(posts) > 0:
        for i in range(len(posts)):
            print('Post {}: {} at {}'.format(i + 1, posts[i]['entry'], posts[i]['timestamp']))
    else:
        print('EMPTY')


def load(command):
    """
    Will make sure the dsu file can be loaded.
    If it can then it will proceed to use either the desired_profile, adding_post, deleting_post, or getting_post functions depending on the users input.
    If it doesnt exists then it will print "ERROR" and inform the user.
    """
    current_location = (Path(os.path.split(command[1])[0])) / (os.path.split(command[1])[1])
    path = current_location
    current_status = current_location.exists()
    if current_status == True:
        if os.path.getsize(path) == 0:
            print('EMPTY')
        else:
            pro = Profile()
            pro.load_profile(path)
            if len(command) == 2:
                desired_profile(pro)
            if len(command) == 3:
                if command[2] == '-a':
                    adding_post(pro, path)
                elif command[2] == '-d':
                    deleting_post(pro, path)
                elif command[2] == '-g':
                    getting_post(pro)
                elif command[2] == '-b':
                    update_bio(pro, path)
                elif command[2] == '-u':
                    update_account(pro, path) 
                else:
                    print('ERROR')
    elif current_status is False:
        print(1, 'ERROR')


def update_bio(profile, path):
    """
    Will update the profile's bio on the file and server.
    """
    profile.bio = input("What is the bio for your profile?")
    while (profile.bio.isspace() == True) or (profile.bio == ''):
        profile.bio = str(input("Bio can not only be whitespace, What would you like in your bio?"))
    if '\"' in profile.bio:
        profile.bio = profile.bio.replace('\"','\'\'')
    profile.bio = change_message(profile.bio)
    dsc.send(profile.dsuserver,port,profile.username,profile.password,None,profile.bio)
    profile.save_profile(path)


def update_account(profile, path):
    """
    Will update the profile's server, username and'or password on the file and server.
    """
    dsuserver = input("Do you want to change the dsuserver from your profile? (Y/N)")
    while dsuserver != "N":
        if dsuserver == 'Y':
            profile.dsuserver = input("What is the new name of your dsuserver?")
            if (profile.dsuserver.isspace() == True) or (profile.dsuserver == ''):
                profile.dsuserver = input("Cannot have only white space in bio, What is the name of your dsuserver?")
            else:
                print('Your new dsuserver is', profile.dsuserver)
                break
        else:
            print('Incorrect Response Format')
            dsuserver = input("Do you want to change the dsuserver from your profile? (Y/N)")
    username = input("Do you want to change the username from your profile? (Y/N)")
    while username != "N":
        if username == 'Y':
            profile.username = input("What is your new username for the dsuserver?")
            if (profile.username.isspace() == True) or (profile.username == ''):
                profile.username = input("Cannot have only white space in bio, What is your new username for the dsuserver?")
            else:
                print('Your new username is', profile.username)
                break
        else:
            print('Incorrect Response Format')
            username = input("Do you want to change the username from your profile? (Y/N)")
    password = input("Do you want to change the password from your profile? (Y/N)")
    while password != "N":
        if password == 'Y':
            profile.password = input("What is your new password for your username on the dsuserver?")
            if (profile.password.isspace() == True) or (profile.password == ''):
                profile.password = input("Cannot have only white space in bio, What is your new password for your username on the dsuserver?")
            else:
                print('Your new password is', profile.password)
            break
        else:
            print('Incorrect Response Format')
            password = input("Do you want to change the password from your profile? (Y/N)")
    if (dsuserver != 'N') or (username != 'N') or (password != 'N'):
        dsc.send(profile.dsuserver,port,profile.username,profile.password,None)
    profile.save_profile(path)


def spacer(command):
    """
    This spacer function will take in the raw input and if there are spaces within the path for the directory, it will correct it to just be one element instead of seperate elements.
    """
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
    if last_part_index + 1 != len(command):
        for ending_commands in range(len(command)):
            if ending_commands > last_part_index:
                new_command.append(command[ending_commands])
    return new_command


if __name__ == '__main__':
    menu()
    command = input()
    port = 2021
    while command != 'Q':
        try:
            if len(command) > 1:
                if type(command) == str:
                    commands = command.split(' ')
                    command = spacer(commands)
            if len(command) == 1:
                    print('ERROR')
            elif os.path.exists(command[1]) == True:
                if command[0] == 'L':
                    list_of_contents(command)
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
        except:
                print('ERROR')
        command = input()
