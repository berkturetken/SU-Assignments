import threading
import time
from SeqSet import MySet

class MyConSet:
    def __init__(self):
        self.seqS = MySet()
        self.cv = threading.Condition()

    def insert(self, elt):
        with self.cv:
            print("Entered insert operation")
            self.seqS.insert(elt)
            self.cv.notify()
    
    def pop(self):
        with self.cv:
            print("Entered pop operation")
            while self.seqS.isEmpty():
                print("Pop operation found no elements")
                self.cv.wait()
            retItem = self.seqS.pop()
        return retItem
    
    def printSet(self):
        with self.cv:
            print("Entered printDictionary")
            self.seqS.printSet()

ch = MyConSet()
ch.printSet()

t1 = threading.Thread(target=ch.pop)
t1.start()
t2 = threading.Thread(target=ch.insert, args=(2,))
t2.start()
t3 = threading.Thread(target=ch.insert, args=(5,))
t3.start()
t1.join()
t2.join()
t3.join()
ch.printSet()
