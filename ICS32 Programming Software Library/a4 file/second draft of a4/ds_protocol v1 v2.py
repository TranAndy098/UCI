from Profile import Profile, Post
from NaClProfile import NaClProfile
import json
import nacl.utils
import nacl.secret
from nacl.public import PrivateKey, PublicKey, Box

def join(username, password, pub):
    """
    Will take in the username and password parameter.
    Then put it into the format of {"join": {"username": "ohhimark","password": "password123","token":"user_token"}}.
    """ 
    join = {}
    join['username'] = username
    join['password'] = password
    join['token'] = pub
    login = {}
    login['join'] = join
    logins = str(login).replace('\'',"\"")
    print(login)
    return logins


def post(token, message, privkey, pub):
    """
    Will take in the token parameter that the server returns and the message will include the post and timestamp.
    Then put it into the format of {"token":"user_token", "post": {"entry": "Hello World!","timestamp": "1603167689.3928561"}}.
    """
    boxes = Box(PrivateKey(privkey, nacl.encoding.Base64Encoder), PublicKey(token, nacl.encoding.Base64Encoder))
    message = message.encode('utf-8')
    message = boxes.encrypt(message, encoder=nacl.encoding.Base64Encoder)
    posting = {}
    posts = {}
    posting['token'] = pub
    message = message.decode('utf-8')
    posts['entry'] = message
    posts['timestamp'] = Post(message).timestamp
    posting['post'] = posts
    x = json.dumps(posting)
    print(x)
    return x


def bio(token, bio, privkey, pub):
    """
    Will take in the token parameter that the server returns and the bio dictionary will include the bio and a newly generated timestamp.
    Then put it into the format of {"token":"user_token", "bio": {"entry": "Hello World!","timestamp": "1603167689.3928561"}}.
    """
    bios = {}
    boxes = Box(PrivateKey(privkey, nacl.encoding.Base64Encoder), PublicKey(token, nacl.encoding.Base64Encoder))
    bio = bio.encode('utf-8')
    bio = boxes.encrypt(bio, encoder=nacl.encoding.Base64Encoder)
    bios['token'] = pub
    b = {}
    b['entry'] = bio
    b['timestamp'] = Post(bio).timestamp
    bios['bio'] = b
    bios = bios.replace(changed_bio,bio)
    return bios


def response(response):
    """
    This function will regulate the response the server gives.
    If the server gives the response trype of "ok", then it will return True to continue.
    If the server gives the response trype of "error", then it will return False to end the connection process.
    """
    print(response)
    if response[23] == 'o':
        step = True
    elif response[23] == 'e':
        step = False
    return step

