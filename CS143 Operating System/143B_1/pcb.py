from rl import LinkedList, LinkedList2

class PCB:
    def __init__(self, id, priority) -> None:
        self.id = id
        self.state = None
        #self.memory = None
        #self.scheduling_information = None
        #self.accounting_information = None
        #self.open_files = None
        self.other_resources = LinkedList2()
        self.parent = None
        self.children = LinkedList()
        self.priority = priority

    def __repr__(self):
        return f"[{self.parent} -> PCB {self.id} -> {self.children}, with resources: {self.other_resources}]"
