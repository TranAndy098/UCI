import asyncio, time, json
import socket
from typing import TextIO
from collections import namedtuple
import ds_protocol
from NaClProfile import NaClProfile

class DSUConnectError(Exception):
  pass


class DSConnection:
  connection: socket = None
  send: TextIO = None
  recv: TextIO = None


def join(ds_conn:DSConnection, username:str, password:str, mpk:str) -> str:
  j_msg = ds_protocol.joinmsg(username, password, mpk)
  resp = write(ds_conn, j_msg)
  print(resp)

  return ds_protocol.extract_token(resp)


def post(ds_conn:DSConnection, mpk:str, mpvk:str, spk:str, message:str, timestamp:str) -> str:
  p_msg = ds_protocol.postmsg(mpk, mpvk, spk, message, timestamp)
  resp = write(ds_conn, p_msg)
  print(resp)

  return ds_protocol.extract_response_typ(resp)


def bios(ds_conn:DSConnection, mpk:str, message:str, timestamp:str) -> str:
  b_msg = ds_protocol.biomsg(mpk, message, timestamp)
  resp = write(ds_conn, b_msg)
  print(resp)

  return ds_protocol.extract_response_typ(resp)


def write(ds_conn:DSConnection, msg:str):
  ds_conn.send.write(msg + '\r\n')
  ds_conn.send.flush()
  resp = ds_conn.recv.readline()
  return resp


def close(ds_conn:DSConnection):
  ds_conn.connection.close()


def connect(server:str, port:int) -> DSConnection:
  try:
    ds_conn = DSConnection()
    ds_conn.connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    ds_conn.connection.connect((server,port))
    ds_conn.send = ds_conn.connection.makefile('w')
    ds_conn.recv = ds_conn.connection.makefile('r')
    return ds_conn
  except:
    return None


def send(server:str, port:int, username:str, password:str, message:str, bio:str=None):
  ds_conn = connect(server, port)

  if ds_conn is None:
    raise DSUConnectError("Unable to connect to server.")

  ncp = NaClProfile()
  my_public_key = ncp.public_key
  my_private_key = ncp.private_key
  print('pk')
  print(ncp.private_key)
  print('pk')
  print(my_private_key)
  
  server_public_key = join(ds_conn, username, password, my_public_key)
  print(server_public_key)

  if post != None:
    typ = post(ds_conn, my_public_key, my_private_key, server_public_key, message, str(time.time()))
    print(typ)

  if bio != None:
    print('im here')
    typ = bios(ds_conn, my_public_key, bio, str(time.time()))
    print(typ)
    


  close(ds_conn)
