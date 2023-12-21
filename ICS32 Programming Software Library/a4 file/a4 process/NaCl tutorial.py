import nacl.utils
from nacl.public import PrivateKey, PublicKey, Box

# Generate Bob's private key, which must be kept secret
skbob = PrivateKey.generate()

# Bob's public key can be given to anyone wishing to send
#   Bob an encrypted message
#pkbob = skbob.public_key
skbob = 'W7Yw7TsGuNd9mhTwQxa3m/FxFm4yTTqGqrvcSpi++3k='
# Alice does the same and then Alice and Bob exchange public keys
skalice = PrivateKey.generate()
#pkalice = skalice.public_key
print('codes')
print(skbob)
#print(pkalice)
#print(type(skbob), type(pkalice))
# Bob wishes to send Alice an encrypted message so Bob must make a Box with
#   his private key and Alice's public key
pkalice = 'KV5HKZaihq9P1PHAhk52tfGqFHGDLUfM9YAXNgpXA0M='
bob_box = Box(PrivateKey(skbob, nacl.encoding.Base64Encoder), PublicKey(pkalice, nacl.encoding.Base64Encoder))
print(bob_box)
print('bbbbb')
# This is our message to send, it must be a bytestring as Box will treat it
#   as just a binary blob of data.
message = b"Kill all humans"
encrypted = bob_box.encrypt(message,encoder=nacl.encoding.Base64Encoder)
print(encrypted)
print(type(encrypted))
print(encrypted.decode(encoding='utf-8'))
#alice_box = Box(skalice, pkbob)
print('codes')
print(skbob)
#print(skbob.public_key)
#print(pkbob)
#print(skbob.encode(encoder=nacl.encoding.Base64Encoder).decode(encoding = 'UTF-8'))
#print(skbob.public_key.encode(encoder=nacl.encoding.Base64Encoder).decode(encoding = 'UTF-8'))
#print(pkbob.encode(encoder=nacl.encoding.Base64Encoder).decode(encoding = 'UTF-8'))
print(skalice)
# Decrypt our message, an exception will be raised if the encryption was
#   tampered with or there was otherwise an error.
plaintext = bob_box.decrypt(encrypted,encoder=nacl.encoding.Base64Encoder)
print(bob_box)
print(plaintext)
print(plaintext.decode('utf-8'))
