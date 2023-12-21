import nacl.utils
import nacl.secret
from nacl.public import PrivateKey, PublicKey, Box
from Profile import Profile, Post, DsuProfileError, DsuFileError
from NaClDSEncoder import NaClDSEncoder
from pathlib import Path
import os
import copy
import json
class NaClProfile(Profile):
    def __init__(self):
        """
        This is used to initalize the NaClProfile class.
        The super init is used to initilatzed the other modules so we have their self variables.
        The keypair is created with the generate function, which will also create they public key and private key.

        TODO: Complete the initializer method. Your initializer should create the follow three 
        public data attributes:

        public_key:str
        private_key:str
        keypair:str

        Whether you include them in your parameter list is up to you. Your decision will frame 
        how you expect your class to be used though, so think it through.
        """
        super().__init__()
        self.keypair = self.generate_keypair()

    def generate_keypair(self) -> str:
        """
        This function will use the NaClDSEncoder to get a keypair for the specific profile.
        Then this function will use the keypair to get the public key and private key.

        Generates a new public encryption key using NaClDSEncoder.

        TODO: Complete the generate_keypair method.

        This method should use the NaClDSEncoder module to generate a new keypair and populate
        the public data attributes created in the initializer.

        :return: str    
        """
        NCE = NaClDSEncoder()
        NCE.generate()
        keypair = NCE.keypair
        self.keypair = keypair
        self.public_key = NCE.public_key
        self.private_key = NCE.private_key
        return keypair

    def import_keypair(self, keypair: str):
        """
        Will take the key pair that is passed in and assign it to the other needed variables.
        
        Imports an existing keypair. Useful when keeping encryption keys in a location other than the
        dsu file created by this class.

        TODO: Complete the import_keypair method.

        This method should use the keypair parameter to populate the public data attributes created by
        the initializer. 
        
        NOTE: you can determine how to split a keypair by comparing the associated data attributes generated
        by the NaClDSEncoder
        """
        if len(keypair) == 88:
            self.keypair = keypair
            self.public_key = self.keypair[0:44]
            self.private_key = self.keypair[44:88]
        else:
            print('Keypair is not long enough or invalid')

    
    def add_post(self, message):
        """
        Will override or build upon the add_post function from Profile.
        This will take a message, make it into bytes, then put it through the encrypt function.
        Will use what returns and switch the encrypted message and the original message.
        Then add it to the posts in the file that belong to the account.

        TODO: Override the add_post method to encrypt post entries.

        Before a post is added to the profile, it should be encrypted. Remember to take advantage of the
        code that is already written in the parent class.

        NOTE: To call the method you are overriding as it exists in the parent class, you can use the built-in super keyword:
        
        super().add_post(...)
        """
        phrase = message['entry']
        encrypted_msg = self.encrypt_entry(phrase,self.public_key)
        encrypted_msg = encrypted_msg.decode('utf-8')
        message['entry'] = encrypted_msg
        super().add_post(message)
        

    def get_posts(self):
        """
        Will override or build upon the get_posts function from Profile.
        This will retrieve the post from the profile and create a copy of the list.
        Will iteriate through the list and decrypt the entry to get their english version.
        Will return a list of all decrypted messages.

        TODO: Override the get_posts method to decrypt post entries.

        Since posts will be encrypted when the add_post method is used, you will need to ensure they are 
        decrypted before returning them to the calling code.

        :return: Post
        
        NOTE: To call the method you are overriding as it exists in the parent class you can use the built-in super keyword:
        super().get_posts()
        """
        posts = super().get_posts()
        decrypt_posts = copy.deepcopy(posts)
        try:
            for i in range(len(decrypt_posts)):
                decrypt_msg = decrypt_posts[i]['entry']
                boxes = Box(PrivateKey(self.private_key, nacl.encoding.Base64Encoder), PublicKey(self.public_key, nacl.encoding.Base64Encoder))
                encrypt_decrypt_msg = boxes.decrypt(decrypt_msg, encoder=nacl.encoding.Base64Encoder)
                decrypt_posts[i].set_entry(encrypt_decrypt_msg.decode('utf-8'))
        except:
            print('Unable to decrypt, Invalid keypairs in file or imported.')
        return decrypt_posts


    def load_profile(self, path):
        """
        Will take the path information and load the profile from it.
        Then will assign the variables to the appropriate variables.

        TODO: Override the load_profile method to add support for storing a keypair.

        Since the DS Server is now making use of encryption keys rather than username/password attributes, you will 
        need to add support for storing a keypair in a dsu file. The best way to do this is to override the 
        load_profile module and add any new attributes you wish to support.

        NOTE: The Profile class implementation of load_profile contains everything you need to complete this TODO. Just add
        support for your new attributes.
        """
        p = Path(path)
        if os.path.exists(p) and p.suffix == '.dsu':
            try:
                f = open(p, 'r')
                obj = json.load(f)
                self.keypair = obj['keypair']
                self.private_key = obj['private_key']
                self.public_key = obj['public_key']
                self.username = obj['username']
                self.password = obj['password']
                self.dsuserver = obj['dsuserver']
                self.bio = obj['bio']
                for post_obj in obj['_posts']:
                    post = Post(post_obj['entry'], post_obj['timestamp'])
                    self._posts.append(post)
                f.close()
            except Exception as ex:
                raise DsuProfileError(ex)
        else:
            print("Invalid DSU file path or type")



    def encrypt_entry(self, entry:str, public_key:str, private_key:str=None) -> bytes:
        """
        Will be called to encrypt messages.
        Will use the public key that is passed in, the profile's or the server's.
        Will use the private key provided or if not provided will use the one from the profile.
        Will encrypt the message and send it back as a byte.

        Used to encrypt messages using a 3rd party public key, such as the one that
        the DS server provides.
        
        TODO: Complete the encrypt_entry method.

        NOTE: A good design approach might be to create private encrypt and decrypt methods that your add_post, 
        get_posts and this method can call.
        
        :return: bytes 
        """
        if private_key == None:
            private_key = self.private_key
        boxes = Box(PrivateKey(private_key, nacl.encoding.Base64Encoder), PublicKey(public_key, nacl.encoding.Base64Encoder))
        entry = entry.encode('utf-8')
        encrypted_msg = boxes.encrypt(entry, encoder=nacl.encoding.Base64Encoder)
        return encrypted_msg


