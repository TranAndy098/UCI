import json, time
from collections import namedtuple
DataTuple = namedtuple('DataTuple', ['type','message'])


def send_directmessage(user_token, msg, recipient, time):
    """
    Takes in the message, recipient, and time and inserts it into the format the server is requesting.
    That message is the send message.
    Converts the send message into a json string.
    """
    json_directmessage = json.dumps({"token":user_token, "directmessage": {"entry": msg,"recipient": recipient, "timestamp": time}})
    return json_directmessage


def request_messages(user_token, msg):
    """
    Takes in the user_token and msg and inserts it into the format the server is requesting.
    That message is the request message.
    Converts the request message into a json string.
    """
    json_request = json.dumps({"token": user_token, "directmessage": msg})
    return json_request


def extract_json(json_msg:str) -> DataTuple:
    """
    Call the json.loads function on a json string and convert it to a DataTuple object and returns json message.
    """
    try:
        json_obj = json.loads(json_msg)
        server_response = json_obj['response']['type']
        message = json_obj['response']['messages']
        return message
    except json.JSONDecodeError:
        print("Json cannot be decoded.")
        return DataTuple(server_response, message)


def extract_response_typ(json_str:str) -> str:
    """
    Call the json.loads function on a json string and convert it to a DataTuple object and returns response type.
    This function will take the response type from the server's message, either 'ok' or 'error'.
    """
    typ = ''
    try:
        json_obj = json.loads(json_str)
        typ = json_obj['response']['type']
        return typ
    except json.JSONDecodeError:
        print('JSON cannot be decoded')
        return typ


def joinmsg(username:str, password:str) -> str:
    """
    Takes in the username and password and inserts it into the format the server is requesting.
    That message is the join message.
    Converts the join message into a json string.
    """
    msg = '{"join": {"username":"'+username+'", "password":"'+password+'", "token":"user_token"}}'
    return msg


def extract_token(json_str:str) -> str:
    """
    Call the json.loads function on a json string and convert it to a DataTuple object and returns response token.
    This function will take the response token, the server provided.
    This token is used to send messages to the server, to direct message, or to retrieve information.
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
