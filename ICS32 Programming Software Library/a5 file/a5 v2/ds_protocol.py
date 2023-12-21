import json
from NaClProfile import NaClProfile

def extract_response_typ(json_str:str) -> str:
    """
    This function will take in the server's response, and return the response type for the ds_client to proceed.
    """
    typ = ''
    try:
        json_obj = json.loads(json_str)
        typ = json_obj['response']['type']
    except json.JSONDecodeError:
        print('JSON cannot be decoded')
    return typ


def extract_token(json_str:str) -> str:
    """
    This function will take in the server's response, and return the server's public key for the ds_client to proceed.
    """
    typ = ''
    msg = ''
    token = None
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
    """
    This function will take in the parameters and create the join message.
    """
    msg = '{"join": {"username":"'+username+'", "password":"'+password+'", "token":"'+my_public_key+'"}}'
    print(msg)
    return msg


def postmsg(my_public_key:str, my_private_key:str, server_public_key:str, message:str, timestamp:str) -> str:
    """
    This function will take in the parameters and create the post message.
    """
    entry = NaClProfile().encrypt_entry(message, server_public_key, my_private_key)
    entry = entry.decode('utf-8')
    msg = '{"token":"'+my_public_key+'", "post": {"entry":"'+entry+'", "timestamp":"'+timestamp+'"}}'
    print(msg)
    return msg


def biomsg(my_public_key:str, my_private_key:str, server_public_key:str, bio:str, timestamp:str) -> str:
    """
    This function will take in the parameters and create the bio message.
    """
    entry = NaClProfile().encrypt_entry(bio, server_public_key, my_private_key)
    entry = entry.decode('utf-8')
    msg = '{"token":"'+my_public_key+'", "bio": {"entry":"'+entry+'", "timestamp":"'+timestamp+'"}}'
    print(msg)
    return msg


def postentry(my_public_key:str, my_private_key:str, server_public_key:str, message:str, timestamp:str) -> str:
    """
    This function will take in the parameters and create the post message.
    """
    entry = NaClProfile().encrypt_entry(message, server_public_key, my_private_key)
    entry = entry.decode('utf-8')
    msg = '{"token":"'+my_public_key+'", "post": {"entry":"'+entry+'", "timestamp":"'+timestamp+'"}}'
    return msg
