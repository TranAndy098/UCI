# NaClProfile.py
# An encrypted version of the Profile class provided by the Profile.py module
# 
# for ICS 32
# by Mark S. Baldwin


# TODO: Install the pynacl library so that the following modules are available
# to your program.:done
import nacl.utils
from nacl.public import PrivateKey, PublicKey, Box

# TODO: Import the Profile and Post classes:done
from Profile import Profile, Post
# TODO: Import the NaClDSEncoder module: done
from NaClDSEncoder import NaClDSEncoder
# TODO: Subclass the Profile class: done
from pathlib import Path
import os
import copy
class NaClProfile(Profile):
    def __init__(self):
        """
        TODO: Complete the initializer method. Your initializer should create the follow three 
        public data attributes:

        public_key:str
        private_key:str
        keypair:str

        Whether you include them in your parameter list is up to you. Your decision will frame 
        how you expect your class to be used though, so think it through.
        """
        self.keypair = self.generate_keypair()
        self.public_key = self.keypair[0:44]
        self.private_key = self.keypair[44:88]

    def generate_keypair(self) -> str:
        """
        Generates a new public encryption key using NaClDSEncoder.

        TODO: Complete the generate_keypair method.

        This method should use the NaClDSEncoder module to generate a new keypair and populate
        the public data attributes created in the initializer.

        :return: str    
        """
        x = NaClDSEncoder()
        x.generate()
        y = x.keypair
        self.keypair = y
        self.public_key = self.keypair[0:44]
        self.private_key = self.keypair[44:88]
        return y

    def import_keypair(self, keypair: str):
        """
        Imports an existing keypair. Useful when keeping encryption keys in a location other than the
        dsu file created by this class.

        TODO: Complete the import_keypair method.

        This method should use the keypair parameter to populate the public data attributes created by
        the initializer. 
        
        NOTE: you can determine how to split a keypair by comparing the associated data attributes generated
        by the NaClDSEncoder
        """
        self.keypair = keypair
        self.public_key = self.keypair[0:44]
        self.private_key = self.keypair[44:88]

    """
    TODO: Override the add_post method to encrypt post entries.

    Before a post is added to the profile, it should be encrypted. Remember to take advantage of the
    code that is already written in the parent class.

    NOTE: To call the method you are overriding as it exists in the parent class, you can use the built-in super keyword:
    
    super().add_post(...)
    """
    def add_post(self, message):
        phrase = message['entry']
        encrypted_msg = self.encrypt_entry(phrase,self.public_key)
        encrypted_msg = str(encrypted_msg)[2:len(str(encrypted_msg))-1]
        encrypted_msg = str(encrypted_msg).encode('ISO-8859-1')
        encrypted_msg = encrypted_msg.decode('ISO-8859-1')
        message['entry'] = encrypted_msg
        super().__init__()
        super().add_post(message)
        
    """
    TODO: Override the get_posts method to decrypt post entries.

    Since posts will be encrypted when the add_post method is used, you will need to ensure they are 
    decrypted before returning them to the calling code.

    :return: Post
    
    NOTE: To call the method you are overriding as it exists in the parent class you can use the built-in super keyword:
    super().get_posts()
    """
    def get_posts(self):
        posts = super().get_posts()
        message = posts[0]['entry']
        decrypt_msg = message.encode('ISO-8859-1')
        decrypt_msg = decrypt_msg.decode('unicode-escape').encode('ISO-8859-1')
        boxes = Box(PrivateKey(self.private_key, nacl.encoding.Base64Encoder), PublicKey(self.public_key, nacl.encoding.Base64Encoder))
        decrypt_posts = copy.deepcopy(posts)
        encrypt_decrypt_msg = boxes.decrypt(decrypt_msg)
        encrypt_decrypt_msg = encrypt_decrypt_msg.decode('ISO-8859-1')
        decrypt_posts[0]['entry'] = encrypt_decrypt_msg
        return decrypt_posts
    """
    TODO: Override the load_profile method to add support for storing a keypair.

    Since the DS Server is now making use of encryption keys rather than username/password attributes, you will 
    need to add support for storing a keypair in a dsu file. The best way to do this is to override the 
    load_profile module and add any new attributes you wish to support.

    NOTE: The Profile class implementation of load_profile contains everything you need to complete this TODO. Just add
    support for your new attributes.
    """
    def load_profile(self, path):
        path = Path(path)
        current_status = path.exists()
        if current_status == True:
            if os.path.getsize(path) == 0:
                print('EMPTY')
            else:
                super().__init__()
                s = super().load_profile(path)
                return s
        elif current_status is False:
            print('ERROR')


    def encrypt_entry(self, entry:str, public_key:str) -> bytes:
        """
        Used to encrypt messages using a 3rd party public key, such as the one that
        the DS server provides.
        
        TODO: Complete the encrypt_entry method.

        NOTE: A good design approach might be to create private encrypt and decrypt methods that your add_post, 
        get_posts and this method can call.
        
        :return: bytes 
        """
    
        boxes = Box(PrivateKey(self.private_key, nacl.encoding.Base64Encoder), PublicKey(self.public_key, nacl.encoding.Base64Encoder))
        message = bytes(entry, 'ISO-8859-1')
        encrypted_msg = boxes.encrypt(message)
        return encrypted_msg

