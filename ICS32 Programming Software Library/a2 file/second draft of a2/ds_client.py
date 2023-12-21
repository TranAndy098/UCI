import socket
import ds_protocol as dsp

def send(server:str, port:int, username:str, password:str, message:str, bio:str=None):
  '''
  The send function joins a ds server and sends a message, bio, or both

  :param server: The ip address for the ICS 32 DS server.
  :param port: The port where the ICS 32 DS server is accepting connections.
  :param username: The user name to be assigned to the message.
  :param password: The password associated with the username.
  :param message: The message to be sent to the server.
  :param bio: Optional, a bio for the user.
  Will connect to the server that is given, if no connection is found then this module is done executing, but if connection is found then it will proceed.
  This module will then create the join dictionary, if the request is denied then the module ends, but if it is accepted then it will proceed.
  It will send the post to the server and if it works it will proceed, and if it fails it will tell the user and end the module.
  If there is not bio given then it ends after the post is sent, if it there is a bio it will do the saem as it did with the post.
  Then it will edn after this and close the connection.
  '''
  with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client:
        try:
            client.connect((server, port))
        except:
            print('No Connection was Found')
            first = False
        else:
            send = client.makefile('w')
            recv = client.makefile('r')
            print("Client connected to {} on {}".format(server, port))
            first = True
        while first is True:
            login = dsp.join(username, password)
            send.write(login + '\r\n')
            send.flush()
            srv_login = recv.readline()
            srv_login = eval(srv_login)
            second = dsp.response(srv_login)
            if second is False:
                first = False
                print('Login Unsuccessful')
                break
            while second is True:
                print('Login Successful')
                token = srv_login['response']['token']
                posting = dsp.post(token, message)
                send.write(posting)
                send.flush()
                srv_posting = recv.readline()
                third = dsp.response(eval(srv_posting))
                if third is False:
                    print('Post Unsuccessful')
                    if bio != None:
                        bios = dsp.bio(token, bio)
                        send.write(posting)
                        send.flush()
                        srv_bios = recv.readline()
                        fourth = dsp.response(eval(srv_bios))
                        if fourth is True:
                            print('Bios Successful')
                        if fourth is False:
                            print('Bios Unsccessful')
                    first = False
                    second = False
                    break
                elif third is True:
                    print('Post Successful')
                    if bio != None:
                          bios = dsp.bio(token, bio)
                          send.write(posting)
                          send.flush()
                          srv_bios = recv.readline()
                          fourth = dsp.response(eval(srv_bios))
                          if fourth is True:
                              print('Bio Successful')
                          if fourth is False:
                              print('Bio Unsccessful')
                    first = False
                    second = False
                    break
                                        
