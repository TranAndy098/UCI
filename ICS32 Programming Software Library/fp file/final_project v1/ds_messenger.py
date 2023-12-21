import socket
import ds_protocol
from typing import TextIO
import asyncio, time, json
from collections import namedtuple

port = 3021

class MessengerException(Exception):
    """
    An exception that is raised when the message fails to send to the server/recipient.
    """
    pass


class ConnectionException(Exception):
    """
    An exception that is raised when a connection can not be established.
    """
    pass


class DSConnection:
    """
    A class that is used to store the connection socket, send, and recieve informaiton, for the user to use at a future time.
    Also used to reduce redundancy in the send, write, and retrieve functions.
    """
    connection: socket = None
    send: TextIO = None
    recv: TextIO = None


class DirectMessage:
    """
    A class that is used to store the recipient, message, and time data for the program to use it through reference.
    """
    def __init__(self):
        """
        Initliazes the class to all the outside program or class to use the variables recipient, message, and timestamp to store informaiton.
        """
        self.recipient = None
        self.message = None
        self.timestamp = None


class DirectMessenger:
    """
    A class that is used to handle all of the sending and retrieving of data, that a client program or the GUI would need to preform.
    """
    def __init__(self, dsuserver=None, username=None, password=None):
        """
        Initliazes the class by assigning the dsuserver, username, and password to the classes variable set to be store and refrenced in other functions.
        Self.token is None becasue it will be assigned with the token from the server when connected.
        """
        self.token = None
        self.dsuserver = dsuserver
        self.username = username
        self.password = password


    def connection(self, server:str, port:int):
        """
        Establishes a connection to the server so messages can be sent.
        If unable to, will return None so functions will stop and inform the user.
        """
        try:
            ds_conn = DSConnection()
            ds_conn.connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            ds_conn.connection.connect((server,port))
            ds_conn.send = ds_conn.connection.makefile('w')
            ds_conn.recv = ds_conn.connection.makefile('r')
            return ds_conn
        except:
            return None


    def join(self, ds_conn:DSConnection, username:str, password:str) -> str:
      """
      Takes in the parameter and uses the ds_protocol to make the join message.
      Takes the join message and puts it into the write function to be written to the server.
      """
      j_msg = ds_protocol.joinmsg(username, password)
      resp = self.write(ds_conn, j_msg)
      return ds_protocol.extract_token(resp)


    def write(self, ds_conn:DSConnection, message:str):
        """
        Takes in the message to be sent to the server.
        Will write it then flush it to the server.
        Will return the response the server provides, to be further analyze.
        """
        ds_conn.send.write(message + '\r\n')
        ds_conn.send.flush()
        resp = ds_conn.recv.readline()
        return resp

    def send(self, message:str, recipient:str) -> bool:
        """
        This function will use its fellow classes and functions to send a message to a recipient.
        Will store the information of the message and recipient.
        Establish a connection to the server.
        Will then send the message to the recipient that is passed in.
        If unable to connect or send, an exception will be raised depending on which kind it is.
        If successful, will return True, else it will return False.
        """
        connect = self.connection(self.dsuserver, port)
        dm = DirectMessage()
        dm.recipient = recipient
        dm.message = message
        dm.timestamp = str(time.time())
        try:
            if connect == None:
                raise ConnectionException()
                return False
            else:
                self.token = self.join(connect, self.username, self.password)
                msg = ds_protocol.send_directmessage(self.token, dm.message, dm.recipient, dm.timestamp)
                resp = self.write(connect, msg)
                resps = ds_protocol.extract_response_typ(resp)
                return resps
            if resps == 'ok':
                print('Direct Message Sent')
                return True
            else:
                raise MessengerException()
                return False
        
        except ConnectionException:
            print("Cannot Connect. Please Check Connection")
            return False
        
        except MessengerException:
            print('Direct Message Unable to be Sent')
            return False


    def retrieve_new(self) -> list:
        """
        Will connect to the server.
        Will retrieve of new messages that were sent to the user.
        Returns a list of DirectMessage objects containing new messages.
        Returns none if something did not connect or can not be retrieved.
        """
        connect = self.connection(self.dsuserver, port)
        try:
            if connect == None:
                raise ConnectionException()
                return None
            else:
                try:
                    self.token = self.join(connect, self.username, self.password)
                    if self.token != None:
                        new_msg = ds_protocol.request_messages(self.token,'new')
                        resp = self.write(connect, new_msg)
                        resps = ds_protocol.extract_response_typ(resp)
                        messages = ds_protocol.extract_json(resp)
                        return messages
                    else:
                        raise ConnectionException
                        return None
                except:
                    print('ERROR')
                    return None
        except ConnectionException:
            print("Connection Error")


    def retrieve_all(self) -> list:
        """
        Will connect to the server.
        Will retrieve of all messages that were sent to the user.
        Returns a list of DirectMessage objects containing all messages.
        Returns none if something did not connect or can not be retrieved.
        """
        connect = self.connection(self.dsuserver, port)    
        try:
            if connect == None:
                raise ConnectionException()
                return None
            else:
                try:
                    self.token = self.join(connect, self.username, self.password)
                    if self.token != None:
                        new_msg = ds_protocol.request_messages(self.token,'all')
                        resp = self.write(connect, new_msg)
                        resps = ds_protocol.extract_response_typ(resp)
                        messages = ds_protocol.extract_json(resp)
                        return messages
                    else:
                        raise ConnectionException
                        return None
                except:
                    print('ERROR')
                    return None
        except ConnectionException:
            print("Connection Error")
