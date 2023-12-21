from zipzip_tree import Rank, ZipZipTree, Node
from dataclasses import dataclass
from CFloat import CFloat

@dataclass
class BFValue:
    bin: list[int]
    best_remaining_capacity: CFloat



class BFZipZipTree(ZipZipTree):
    def update_node(self, node: Node):
        l_cap = 0.0
        if node.left != None:
            l_cap = node.left.val.best_remaining_capacity.val
        r_cap = 0.0
        if node.right != None:
            r_cap = node.right.val.best_remaining_capacity.val
        node.val.best_remaining_capacity = CFloat(max(node.key.val, l_cap, r_cap))

    def insert(self, bin, capacity, rank: Rank = None):
        bf = BFValue(bin, CFloat(capacity))
        super().insert(CFloat(capacity), bf, rank)
    
    def find_best(self, capacity):
        c_key = CFloat(capacity)
        cur = self.root
        while cur != None:
            if cur.left != None and (c_key <= cur.left.val.best_remaining_capacity):
                cur = cur.left
            elif c_key <= cur.key:
                break
            else:
                cur = cur.right
        return cur



    
