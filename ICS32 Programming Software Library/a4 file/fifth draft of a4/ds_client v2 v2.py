import asyncio, time, json
import socket
from typing import TextIO
from collections import namedtuple
import ds_protocol
from NaClProfile import NaClProfile

class DSUConnectError(Exception):
  """
  The Error Excpetion that specficaly handles the connection errors.
  """
  pass


class DSConnection:
  """
  The Connection Profile for the connect socket, what to send, and what to receive.
  """
  connection: socket = None
  send: TextIO = None
  recv: TextIO = None


def join(ds_conn:DSConnection, username:str, password:str, mpk:str) -> str:
  """
  Takes in the parameter and uses the ds_protocol to make the join message.
  Takes the join message and puts it into the write function to be written to the server.
  """
  j_msg = ds_protocol.joinmsg(username, password, mpk)
  resp = write(ds_conn, j_msg)
  print(resp)
  return ds_protocol.extract_token(resp)


def post(ds_conn:DSConnection, mpk:str, mpvk:str, spk:str, message:str, timestamp:str) -> str:
  """
  Takes in the parameter and uses the ds_protocol to make the post message.
  Takes the post message and puts it into the write function to be written to the server.
  """
  p_msg = ds_protocol.postmsg(mpk, mpvk, spk, message, timestamp)
  resp = write(ds_conn, p_msg)
  print(resp)
  return ds_protocol.extract_response_typ(resp)


def bios(ds_conn:DSConnection, mpk:str, mpvk:str, spk:str, bio:str, timestamp:str) -> str:
  """
  Takes in the parameter and uses the ds_protocol to make the bio message.
  Takes the bio message and puts it into the write function to be written to the server.
  """
  b_msg = ds_protocol.biomsg(mpk, mpvk, spk, bio, timestamp)
  resp = write(ds_conn, b_msg)
  print(resp)
  return ds_protocol.extract_response_typ(resp)


def write(ds_conn:DSConnection, msg:str):
  """
  The function to send write the message down then flush it to the server.
  """
  ds_conn.send.write(msg + '\r\n')
  ds_conn.send.flush()
  resp = ds_conn.recv.readline()
  return resp


def close(ds_conn:DSConnection):
  """
  Used to close the connection after the server is done with what it needs to do.
  """
  ds_conn.connection.close()


def connect(server:str, port:int) -> DSConnection:
  """
  Connects to the dsuserver with the server and port.
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


def send(server:str, port:int, username:str, password:str, message:str, my_public_key:str, my_private_key:str, bio:str=None):
  """
  The function that is called in a4 to send information to the server.
  """
  ds_conn = connect(server, port)


  if ds_conn is None:
    raise DSUConnectError("Unable to connect to server.")


  ncp = NaClProfile()
  server_public_key = join(ds_conn, username, password, my_public_key)

  if ds_conn != None:
    if message != None:
      typ = post(ds_conn, my_public_key, my_private_key, server_public_key, message, str(time.time()))
      post_form = ds_protocol.postentry(my_public_key, my_private_key, my_public_key, message, str(time.time()))
      post_entry = json.loads(post_form)['post']


    if bio != None:
      typ = bios(ds_conn, my_public_key, my_private_key, server_public_key, bio, str(time.time()))
    

  close(ds_conn)
