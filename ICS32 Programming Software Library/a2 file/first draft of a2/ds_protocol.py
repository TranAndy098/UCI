from Profile import Profile, Post

def join(username, password):
#{"join": {"username": "ohhimark","password": "password123","token":"user_token"}}
    join = {}
    join['username'] = username
    join['password'] = password
    join['token'] = 'user_token'
    login = {}
    login['join'] = join
    logins = str(login).replace('\'',"\"")
    return logins

# timestamp is generate automatically in the Profile module using Python's 
# time.time() function
#{"token":"user_token", "post": {"entry": "Hello World!","timestamp": "1603167689.3928561"}}
def post(token, message):
    posting = {}
    posting['token'] = token
    posting['post'] = message
    postings = str(posting).replace('\'',"\"")
    return postings

def bio(token, bio):
# for bio, you will have to generate the timestamp yourself or leave it empty.
#{"token":"user_token", "bio": {"entry": "Hello World!","timestamp": "1603167689.3928561"}}
    bios = {}
    bios['token'] = token
    b = {}
    b['entry'] = bio
    b['timestamp'] = Post(bio).timestamp
    bios['bio'] = b
    bio = str(bios).replace('\'',"\"")
    return bio

# Error messages will primarily be received when a user has not been 
# established for the active session. For example, sending 'bio' or 'post' 
# before 'join'
#{"response": {"type": "error", "message": "An error message will be contained here."}}

# Ok messages will be receieved after every successful send command. 
# They likely will not be accompanied by a message.
#{"response": {"type": "ok", "message": "", "token":"user_token"}}
def response(response):
    print(response)
    upload = response['response']['type']
    if upload == 'ok':
        step = True
    elif upload == 'error':
        step = False
    return step
