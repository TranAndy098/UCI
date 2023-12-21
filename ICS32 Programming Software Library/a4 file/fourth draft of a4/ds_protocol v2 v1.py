import json
from NaClProfile import NaClProfile

def extract_response_typ(json_str:str) -> str:
    typ = ''
    print(9)
    print(json_str)
    try:
        json_obj = json.loads(json_str)
        typ = json_obj['response']['type']
    except json.JSONDecodeError:
        print('JSON cannot be decoded')

    return typ


def extract_token(json_str:str) -> str:
    typ = ''
    msg = ''
    token = None
    print(json_str)
    try:
        json_obj = json.loads(json_str)
        typ = json_obj['response']['type']
        msg = json_obj['response']['message']
        if 'token' in json_obj['response']:
            token = json_obj['response']['token']
    except json.JSONDecodeError:
        print('JSON cannot be decoded')

    return token


def joinmsg(username:str, password:str, my_public_key:str) -> str:
    msg = '{"join": {"username":"'+username+'", "password":"'+password+'", "token":"'+my_public_key+'"}}'
    print(msg)
    return msg


def postmsg(my_public_key:str, my_private_key:str, server_public_key:str, message:str, timestamp:str) -> str:
    entry = NaClProfile().encrypt_entry(message, server_public_key, my_private_key)
    entry = entry.decode('utf-8')
    msg = '{"token":"'+my_public_key+'", "post": {"entry":"'+entry+'", "timestamp":"'+timestamp+'"}}'
    print(msg)
    return msg


def biomsg(token:str, bio:str, timestamp:str) -> str:
    msg = '{"token":"'+token+'", "bio": {"entry":"'+bio+'", "timestamp":"'+timestamp+'"}}'
    print(msg)
    return msg
