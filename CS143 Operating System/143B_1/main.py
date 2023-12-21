import pcb, rcb, rl

class Manager:
    def __init__(self) -> None:
        new_process = pcb.PCB(0, 0)
        new_process.state = "ready"
        self.pcbs = [new_process]
        self.rcb = rcb.RCB()
        self.rl = rl.RL()
        self.rl.add(0,0)
        self.current_process = new_process
        self.possible_process = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]

    def create(self, priority):
        if priority not in [1,2]:
            return -1
        if len(self.possible_process) == 0:
            return -1 
        j = self.possible_process[0]
        new_child = pcb.PCB(j, priority)
        new_child.process_state = "ready"
        self.current_process.children.add(j)
        new_child.parent = self.current_process.id
        self.pcbs.append(new_child)
        self.rl.add(j, priority)
        self.possible_process = self.possible_process[1:]
        self.scheduler()
        return self.current_process.id
    

    def find(self, j):
        if type(j) == pcb.PCB:
            j = j.id
        for p in self.pcbs:
            if p.id == j:
                return p
        return None
    

    def is_descendent(self, i):
        descendents = []
        to_search = [self.current_process.id]
        while len(to_search) > 0 and i not in descendents:
            current = self.find(to_search[0])
            if current is None:
                return False
            to_search += current.children.all_list()
            descendents.append(to_search[0])
            to_search = to_search[1:]
        return i in descendents


    def destroy(self, i): 
        original = self.current_process
        first_process = self.find(i)
        if first_process == None:
            return -1
        if not self.is_descendent(i): #i is not a descendent
            return -1
        delete_processes = [first_process]
        while len(delete_processes) > 0:
            process = delete_processes[0]
            children = []
            process_children = process.children
            while process_children.head != None:
                children.append(process_children.head.data)
                process_children.head = process_children.head.next
            for c in children:
                dc = self.find(c)
                if dc != None and dc not in delete_processes:
                    delete_processes.append(self.find(c))
            
            self.current_process = process
            if self.current_process.state == "ready" or self.current_process.state == "running":
                self.rl.remove(self.current_process.id)
            while self.current_process.other_resources.head != None:
                o = self.current_process
                self.release(self.current_process.other_resources.head.data, self.current_process.other_resources.head.amount)
                self.current_process = o

            for r in self.rcb.rcb:
                r.waitlist.remove(process.id)
            
            self.pcbs.remove(process)
            self.rl.remove(process.id)
            if delete_processes[0].id not in self.possible_process:
                self.possible_process.append(delete_processes[0].id)
            for i in self.pcbs:
                i.children.remove(delete_processes[0].id)
            delete_processes = delete_processes[1:]
            
        
        if original.id in self.possible_process:
            self.current_process = None
        else:
            self.current_process = original
        self.possible_process = sorted(self.possible_process)
        
        if len(self.possible_process) == 16:
            return -1
        self.scheduler()
        return self.current_process.id
        

    def request(self, resource, units):
        if resource not in [0,1,2,3]:
            return -1
        if self.rcb.get(resource).state >= units:
            self.rcb.get(resource).state -= units
            self.current_process.other_resources.add(resource, units)
        else:
            self.current_process.state = "blocked"
            self.rl.remove(self.current_process.id)
            self.rcb.get(resource).waitlist.add(self.current_process.id, units)
            self.current_process = None
            self.scheduler()
        return self.current_process.id
        

    def release(self, resource, units):
        if resource not in [0,1,2,3]:
            return -1
        amount = 0
        run_thru = self.current_process.other_resources.head
        while run_thru != None:
            if run_thru.data == resource:
                amount = run_thru.amount
                break
            run_thru = run_thru.next
        if amount < units:
            return -1 #cant release more than it has
        
        self.current_process.other_resources.remove(resource, units)
        self.rcb.get(resource).state += units
        while self.rcb.get(resource).waitlist.count != 0 and self.rcb.get(resource).state >= self.rcb.get(resource).waitlist.head.amount:
            next_up = self.rcb.get(resource).waitlist.head
            if next_up != None and next_up.data != self.current_process.id:
                if self.rcb.get(resource).state >= next_up.amount:
                    self.rcb.get(resource).state -= next_up.amount
                    process = self.find(next_up.data)
                    process.other_resources.add(resource, next_up.amount)
                    process.state = "ready"
                    self.rcb.get(resource).waitlist.remove()
                    self.rl.add(next_up.data, process.priority)
                    self.scheduler()
        return self.current_process.id


    def timeout(self, s = False):
        self.current_process.state = "ready"
        self.rl.remove(self.current_process.id)
        self.rl.add(self.current_process.id, self.current_process.priority)
        self.scheduler()
        return self.current_process.id


    def scheduler(self):
        cur = -1
        if self.current_process != None:
            cur = self.current_process.priority 
        highest = self.rl.find_highest()
        if highest == None:
            return -1
        next_up = self.rl.next_up()
        if highest > cur or next_up != self.current_process.id:
            self.current_process = self.find(next_up)
            self.current_process.state = "running"
        return self.current_process.id

def main(m, command):
    if len(command) == 0:
        return "\n"
    if command[0] == "in":
       m.__init__()
       return m.current_process.id
    elif command[0] == "cr":
        return m.create(int(command[1]))
    elif command[0] == "de":
        return m.destroy(int(command[1]))
    elif command[0] == "rq":
        return m.request(int(command[1]), int(command[2]))
    elif command[0] == "rl":
        return m.release(int(command[1]), int(command[2]))
    elif command[0] == "to":
        return m.timeout()
    return -1
    

if __name__ == "__main__":
    m = Manager()
    f = open("input.txt", "r")
    o = ""
    for x in f:
        r = str(main(m, x.split()))
        o += r
        if r != "\n":
            o += " "
    f.close()
    print(o) #instead needs to be put in output.txt