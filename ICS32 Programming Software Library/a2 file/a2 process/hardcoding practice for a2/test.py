import ds_client as dsc
from Profile import Profile, Post

ser = '168.235.86.101'
port = 2021

username = input('what is your username?\n')
password = input('what is your password?\n')
m = {}
m['entry'] = input('what is your post?\n')
m['timestamp'] = Post(m['entry']).timestamp
mess = m


dsc.send(ser,port,username,password,mess)








