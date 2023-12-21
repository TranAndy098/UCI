from rl import LinkedList2

class single_RCB:
    def __init__(self, units) -> None:
        #self.resource_description = None
        self.state = units
        self.waitlist = LinkedList2()
        self.inventory = units


class RCB:
    def __init__(self) -> None:
        self.rcb = []
        self.rcb.append(single_RCB(1))
        self.rcb.append(single_RCB(1))
        self.rcb.append(single_RCB(2))
        self.rcb.append(single_RCB(3))
    
    def get(self, index):
        return self.rcb[index]
