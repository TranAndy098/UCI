Project 1: Process and Resource Management


files:
+-main.py
|
+-pcb.py
|
+-rcb.py
|
+-rl.py


__________________________________________________
main.py:
__________________________________________________

Main will take in the "input.txt" and read it and carry out the functions that match the command. 

"in" = init
"cr <p>" = create process of priority p
"de <i>"= destroy process i and its descendents
"rq <r> <n>" = request n units of resource r
"rl <r> <n>" = release n units of resource r
"to" = timeout current process

Manager: Manage the PCBs, RCBs, and Ready List. All functions will return current process id or -1 if error occurs.

- init: Initialize an array of PCBs, starting with PCB 0. Initialize an RCB and Ready List, and add process 0 at priority 0. Store the current process, process 0. And have an array of the possible PCB ids.
- create: Given a priority, must be 1 or 2. And there must be a process id left that could be used. Create a new PCB that will be a child of the current process. The newly created process's parent is the current process, state is "ready", and added to the overall PCB array and Ready List. The process id will laso be removed from the possible id list to ensure it is not reused while this process exists. Then call scheduler because its priority may be higher than the currently running one.
- find: Find the process given the process number.
- is_descendent: Starting at the current process, and checking if the given process is either the current or a descendent so it can be deleted.
- destroy: Will check if the process given is a descendent, in order for it to be destroyed. Then starting at the process, delete it and its descendents. They all will be removed from the ready list, release any resources that are held, removed from waitlist of any resources, removed from overall PCB, its id is made available again, and remove from any children list. Then call scheduler.
- request: Given a resource and an amount, the resource must be 0, 1, 2, or 3. Then checks if that amount is available, if so allocate it the process and add the resoure to its resources list. If not, then the current process is "blocked" and taken off the ready list and added to the resource's waitlist and scheduler is called to have the next process start.
- release: Given a resource and an amount, the resource must be 0, 1, 2, or 3. Adn then check how much of that resource is held, if its holding less than the amount being released, then an error occurs. The process will remove that resource and that amount or only subtract the amount its holding. Will then go through that resource's waitlist to see if it can unblock any of the process that were waiting. Calls scheduler if one is found.
- timeout: Changes the current process back to ready and moves it to the end of its priority's ready list. Calls scheduler.
- scheduler: Finds the highest priority process and makes that the current process, if one does not exist an error occured.


__________________________________________________
pcb.py:
__________________________________________________

PCB: Process Control Block to represent a single PCB.

- init: Given a id (process number) and prioirty, stores that information. Start at state, None, that will be modified in the manager. Start with no parent, but could be changed if one exists. Other resources will be a LinkedList2 to store the resource number and the amount. Children will be a LinkedList to store the children that could be created by this process later on.
- repr: Print out "[{parent} -> PCB {id} -> {children}, with resources: {resources}]".

__________________________________________________
rcb.py:
__________________________________________________

single_RCB: Structure for a single resource.

- init: Given the amount of units of this resource, that is its state (amount of current has) and its inventory (the maximum it can ever have). And there will be a LinkedList2 as its waitlist, to store the process waiting and the amount it is asking for.


RCB: Resources Control Block to hold the different resources.

- init: Initialize an array of size 4 and store 4 reources matching the project specfication. Resource 0 has 1 unit, Resource 1 has 1 unit, Resource 2 has 2 unit, and Resource 3 has 3 unit.
- get: Given the index, return the resource associated with that index.


__________________________________________________
rl.py:
__________________________________________________

Node and LinkedList: Used to represent linked list of 1 stored element, mostly used by ready list and PCB's childrens.

Node2 and LinkedList2: Used to represent linked list of 2 stored elements, mostly used by PCB's chotother resources and RCB's resource waitlist.

- init: Initialize the LinkedList version head to None and the count to 0.
- repr: The LinkedList version would be printed as "{head} -> ... -> {tail}"
- add: Adds data (and amount if applicable) to LinkedList version if does not exist.
- remove: Removes data (and amount if applicable) from LinkedList version if it exists.


RL: Ready List to represent the 3 priority ready list

- init: Have an array of 3 Linked Lists, to represents the 3 levels of priority for the ready list.
- add: Given a process and priority, the process will be enter into the ready list of that priority.
- remove: Will go through all of the priority levels, and remove the process.
- find_highest: Will start at the highest priority and see if anything is in the ready list, and return that priority if there is something in that level else, decrement and repeat. Return None is nothing in ready list at any priority level.
- next_up: Using find_highest, get the highest priority and return the first process of that priority ready list.
