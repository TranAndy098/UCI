class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

    def __repr__(self):
        return self.data

class LinkedList:
    def __init__(self):
        self.head = None
        self.count = 0
    
    def __repr__(self):
        node = self.head
        nodes = []
        while node is not None:
            nodes.append(str(node.data))
            node = node.next
        nodes.append("None")
        return " -> ".join(nodes)
    
    def all_list(self):
        l = []
        node = self.head
        nodes = []
        while node is not None:
            l.append(node.data)
            node = node.next
        return l
    
    def add(self, j):
        if self.head is None:
            self.head = Node(j)
            self.count += 1
            return
        current_node = self.head
        if current_node.data == j:
            return
        while current_node.next != None:
            if current_node.data == j:
                return
            current_node = current_node.next
        new_node = Node(j)
        current_node.next = new_node
        self.count += 1
    
    def remove(self,j=None):
        if j == None or (self.head != None and j == self.head.data):
            self.head = self.head.next
            self.count -= 1
            return
        current = self.head
        while current != None:
            if current.data == j:
                break
            previous = current
            current = current.next
        if current == None:
            return
        previous.next = current.next
        self.count -= 1

class Node2:
    def __init__(self, data, amount):
        self.data = data
        self.amount = amount
        self.next = None

    def __repr__(self):
        return f"({self.data}, {self.amount})"

class LinkedList2:
    def __init__(self):
        self.head = None
        self.count = 0
    
    def __repr__(self):
        node = self.head
        nodes = []
        while node is not None:
            nodes.append(str(node.data))
            node = node.next
        nodes.append("None")
        return " -> ".join(nodes)
    
    def add(self, i, amount):
        if self.head is None:
            self.head = Node2(i, amount)
            self.count += 1
            return
        current_node = self.head
        if current_node.data == i:
            return
        while current_node.next != None:
            if current_node.data == i:
                return
            current_node = current_node.next
        new_node = Node2(i, amount)
        current_node.next = new_node
        self.count += 1
    
    def remove(self, j=None, units=None):
        if j == None or (self.head != None and j == self.head.data):
            if units != None and units < self.head.amount:
                self.head.amount -= units
            else:
                self.head = self.head.next
                self.count -= 1
                return
                
        current = self.head
        while current != None:
            if current.data == j:
                break
            previous = current
            current = current.next
        if current == None:
            return
        if units != None and current.amount == units:
            previous.next = current.next
        else:
            current.amount -= units
        self.count -= 1


class RL:
    def __init__(self) -> None:
        self.rl = [LinkedList(), LinkedList(), LinkedList()]

    def add(self, i, priority):
        self.rl[priority].add(i)


    def remove(self, i):
        self.rl[0].remove(i)
        self.rl[1].remove(i)
        self.rl[2].remove(i)

    def find_highest(self):
        start = 2
        while start >= 0:
            if self.rl[start].count > 0:
                return start
            start -= 1

        return None

    def next_up(self):
        high = self.find_highest()
        return self.rl[high].head.data
