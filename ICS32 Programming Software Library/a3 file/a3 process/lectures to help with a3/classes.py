from Profile import Profile

p1 = Profile("", 'my title')
p1.username = "usr1"

p2 = Profile("")
p2.username = "usr2"

Profile.username = "usr3"

Profile.usernames = "usr4"

print(p1.username)
print(p2.username)
print(Profile.username)
print(Profile.usernames)

class Post:
            # Example of a minimal class constructor
        def __init__(self):
                pass

        # The Profile class constructor
        def __init__(self, dsuserver=None, username=None, password=None):
                self.dsuserver = dsuserver 
                self.username = username 
                self.password = password 
                self.bio = ''           
                self.__posts = []       

        # The Post class constructor
        def __init__(self, message = None, timestamp = None):
                if timestamp is None:
                        timestamp = time.time()

                self.timestamp = timestamp
                self.__entry = message
        
	#timestamp = time.time()
	entry = ""
	title = ""

p = Post()
p.title = 'Hello'

# Example of how the init constructor can be used to create attribute references for class instances.
p = Profile("a server address")
p.username = "usr1"

for post_obj in obj['_Profile__posts']:
	post = Post(post_obj['entry'], post_obj['timestamp'])
	post.timestamp = post_obj['timestamp']
	post.title = post_obj['title']
	self.add_post(post)

def get_posts(self) -> list:
	return self.__posts

def add_post(self, post: Post) -> None:
	self.__posts.append(post)
