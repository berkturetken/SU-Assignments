class MySet:
    def __init__(self):
        self.items = {}
    
    def insert(self, elt):
        for item in self.items:
            if item == elt:
                self.items[item] = True
                return True
        self.items[elt] = True
    
    def pop(self):
        while True:
            for item in self.items:
                if (self.items[item] == True):
                    self.items[item] = False
                    return item
            print("Pop operation could find an element")
    
    def isEmpty(self):
        for item in self.items:
            if item is not None:
                return False
        return True

    #If all the elements are popped, then there will be no output for the print statement
    #In other words, all the keys have "False" as their value. We can see that if print the
    #dictionary (print(self.items))
    def printSet(self):
        for item in self.items:
            if self.items[item] == True:
                print(item)
        