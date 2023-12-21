class BaseClass:
    def __init__(self):
        self.base_attr = "I am a base attribute!"
        self.data = 0
    
    def base_method(self):
        print("the base method number is: ",self.data)

class SubClass(BaseClass):
    def sub_method(self, data: int):
        self.data = data 

class AnotherSubClass(BaseClass):
    def base_method(self):
        print("the custom base method number is: ",self.data)

class MessageClass:
    def print_message(self, bc:BaseClass):
        bc.base_method()

sc = SubClass()
sc.base_method()
sc.sub_method(5)
sc.base_method()

ac = AnotherSubClass()
ac.base_method()

print(sc.base_attr)
print(type(sc))
print(isinstance(sc, BaseClass))

mc = MessageClass()

mc.print_message(sc)
mc.print_message(ac)
