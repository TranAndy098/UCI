from NaClProfile import NaClProfile
from Profile import Profile, Post

np = NaClProfile()
kp = np.generate_keypair()

print('np.public_key')
print(np.public_key)
print()
print('np.private_key')
print(np.private_key)
print()
print('np.keypair')
print(np.keypair)
print()

# Test encryption with 3rd party public key
ds_pubkey = "jIqYIh2EDibk84rTp0yJcghTPxMWjtrt5NW4yPZk3Cw="
ee = np.encrypt_entry("Encrypted Message for DS Server", ds_pubkey)
print('ee')
print(ee)
print()
# Add a post to the profile and check that it is decrypted.
np.add_post(Post("Hello Salted World!"))
np.add_post(Post("i like monkeys"))
np.add_post(Post("dont want to watch the end with someone else"))
p_list = np.get_posts()
print('p_list[0].get_entry()')
print(p_list[0].get_entry())
print()

# Save the profile
np.save_profile('C:/users/andy/desktop/aaa.dsu')

print("Open DSU file to check if message is encrypted.")
print()
#input("Press Enter to Continue")

# Create a new NaClProfile object and load the dsu file.
np2 = NaClProfile()
np2.load_profile('C:/users/andy/desktop/aaa.dsu')
# Import the keys
np2.import_keypair(kp)

# Verify the post decrypts properly
p_list = np2.get_posts()
print('p_list[0].get_entry()')
print(p_list[0].get_entry())

