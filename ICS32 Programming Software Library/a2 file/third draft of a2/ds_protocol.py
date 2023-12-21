from Profile import Profile, Post

def join(username, password):
    """
    Will take in the username and password parameter.
    Then put it into the format of {"join": {"username": "ohhimark","password": "password123","token":"user_token"}}.
    """ 
    join = {}
    join['username'] = username
    join['password'] = password
    join['token'] = 'user_token'
    login = {}
    login['join'] = join
    logins = str(login).replace('\'',"\"")
    return logins


def post(token, message):
    """
    Will take in the token parameter that the server returns and the message will include the post and timestamp.
    Then put it into the format of {"token":"user_token", "post": {"entry": "Hello World!","timestamp": "1603167689.3928561"}}.
    """
    posting = {}
    posting['token'] = token
    posting['post'] = message
    postings = str(posting).replace('\'',"\"")
    return postings


def bio(token, bio):
    """
    Will take in the token parameter that the server returns and the bio dictionary will include the bio and a newly generated timestamp.
    Then put it into the format of {"token":"user_token", "bio": {"entry": "Hello World!","timestamp": "1603167689.3928561"}}.
    """
    bios = {}
    bios['token'] = token
    b = {}
    b['entry'] = bio
    b['timestamp'] = Post(bio).timestamp
    bios['bio'] = b
    bio = str(bios).replace('\'',"\"")
    return bio


def response(response):
    """
    This function will regulate the response the server gives.
    If the server gives the response trype of "ok", then it will return True to continue.
    If the server gives the response trype of "error", then it will return False to end the connection process.
    """
    print(response)
    upload = response['response']['type']
    if upload == 'ok':
        step = True
    elif upload == 'error':
        step = False
    return step
