from zipzip_tree import Rank, ZipZipTree, Node
from dataclasses import dataclass
from CFloat import CFloat

@dataclass
class FFValue:
    capacity: CFloat
    best_remaining_capacity: CFloat

class FFZipZipTree(ZipZipTree):
    def update_node(self, node: Node):
        l_cap = 0.0
        if node.left != None:
            l_cap = node.left.val.best_remaining_capacity.val
        r_cap = 0.0
        if node.right != None:
            r_cap = node.right.val.best_remaining_capacity.val
        node.val.best_remaining_capacity = CFloat(max(node.val.capacity.val, l_cap, r_cap))

    def insert(self, key, capacity, rank: Rank = None):
        ff = FFValue(CFloat(capacity), CFloat(capacity))
        super().insert(key, ff, rank)
    
    def find_first(self, value):
        c_val = CFloat(value)
        cur = self.root
        while cur != None:
            if cur.left != None and (c_val <= cur.left.val.best_remaining_capacity):
                cur = cur.left
            elif c_val <= cur.val.capacity:
                break
            else:
                cur = cur.right
        return cur
