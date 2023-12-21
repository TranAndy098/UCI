import socket
import json
import ds_client as dsc
from NaClProfile import NaClProfile

PORT = 2021
HOST = "168.235.86.101"

ncp = NaClProfile()
keypair = ncp.keypair
my_public_key = ncp.public_key
my_private_key = ncp.private_key
   
dsc.send(HOST,PORT,'newclienatprotocol1','dasdassfdgdf', 'not a 76ghost', my_public_key, my_private_key, 'i listen to music')

nc = NaClProfile()
nc.load_profile('C:/Users/Andy/Desktop/file.dsu')
posts = nc.get_posts()
print(posts)

