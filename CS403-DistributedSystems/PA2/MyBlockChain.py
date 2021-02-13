import Pyro4
import threading

class MyBlock:
    def __init__(self, transaction, nextp):
        self.transaction = transaction  
        self.next = nextp
          
@Pyro4.expose
class MyBlockChain:
    def __init__(self, chainName):
        self.head = None
        self.chainName = chainName
        self.mutex = threading.Lock()
        print(chainName)
        
        daemon = Pyro4.Daemon()
        ns = Pyro4.locateNS()

        uri = daemon.register(self)
        ns.register(chainName, uri)

        print('Ready')
        daemon.requestLoop()
    
    
    def getChainName(self):
        return self.chainName
    

    def createAccount(self, amount):
        if amount < 0:
            return -1

        if self.head == None:
            newTransaction = ("CREATEACCOUNT",(1,amount))
            newBlock = MyBlock(newTransaction,None)
            self.head = newBlock
            return 1

        newAccountNumber = self.getMaxAccountNumber()+1
        newTransaction = ("CREATEACCOUNT",(newAccountNumber,amount))
        newBlock=MyBlock(newTransaction,self.head)
        self.head=newBlock
        return newAccountNumber


    def getMaxAccountNumber(self):
        temp = self.head

        while temp != None:
            if(temp.transaction[0] == "CREATEACCOUNT"):
                return temp.transaction[1][0]
            temp=temp.next
        
    
    def transfer(self, From, to, amount):
        self.mutex.acquire()
        if (self.isAccountExist(From) and self.isAccountExist(to)):
            # Money flow: From --> to
            if (amount > 0):
                if (self.calculateBalance(From) >= amount):
                    newTransfer = ("TRANSFER", (From, to, amount))
                else:
                    return -1
            # Money flow: to --> From
            elif (amount < 0):
                if (self.calculateBalance(to) >= abs(amount)):
                    newTransfer = ("TRANSFER", (From, to, amount))
                else:
                    return -1
            # Amount = 0
            else:
                newTransfer = ("TRANSFER", (From, to, amount))
        else:
            return -1
        
        newBlock = MyBlock(newTransfer, self.head)
        self.head = newBlock
        self.mutex.release()
        return 1


    def isAccountExist(self, accountNo):
        temp = self.head
        while temp != None:
            if (temp.transaction[0] == "CREATEACCOUNT" and temp.transaction[1][0] == accountNo):
                return True
            temp = temp.next
        return False

    
    def exchange(self, From, to, toChain, amount):
        self.mutex.acquire()
        if(self.isAccountExist(From) and toChain.isAccountExist(to)):
            # Money flow: From (host chain) --> to (to Chain)
            if(amount > 0):
                if(self.calculateBalance(From) >= amount):
                    hostnewExchange = ("EXCHANGE", (From, to, toChain.getChainName(), amount))
                    destinationNewExchange = ("EXCHANGE", (to, From, self.chainName, amount*-1))
                else:
                    return -1
            # Money flow: to (to Chain) --> From (host chain)
            elif (amount < 0):
                if(toChain.calculateBalance(to) >= abs(amount)):
                    hostnewExchange = ("EXCHANGE", (From, to, toChain.getChainName(), amount))
                    destinationNewExchange = ("EXCHANGE", (to, From, self.chainName, amount*-1))
                else:
                    return -1
            # Amount = 0
            else:
                hostnewExchange = ("EXCHANGE", (From, to, toChain.getChainName(), amount))
                destinationNewExchange = ("EXCHANGE", (to, From, self.chainName, amount*-1))
        else:
            return -1
        
        self.addBlockToChain(hostnewExchange)
        toChain.addBlockToChain(destinationNewExchange)
        self.mutex.release()
        return 1


    def addBlockToChain(self, transaction):
        newBlock = MyBlock(transaction, self.head)
        self.head = newBlock


    def calculateBalance(self, accountNo):
        temp=self.head
        accountBalance=self.calculateInitialAccountBalance(accountNo)
        if accountBalance==None:
            return "No account exist with this number!"

        while temp!=None:
            transType=temp.transaction[0]
            transArgs=temp.transaction[1]
            if transType == "TRANSFER":
                if transArgs[0]==accountNo:
                    accountBalance-=transArgs[2]
                if transArgs[1]==accountNo:
                    accountBalance+=transArgs[2]
            elif transType == "EXCHANGE":
                if transArgs[0]==accountNo:
                    accountBalance-=transArgs[3]
                elif transArgs[1]==accountNo:
                    accountBalance+=transArgs[3]
            temp=temp.next

        return accountBalance

    
    def calculateInitialAccountBalance(self,accountNo):
        temp=self.head

        while temp!=None:
            if temp.transaction[0]=="CREATEACCOUNT" and temp.transaction[1][0]==accountNo:
                return temp.transaction[1][1]
            temp=temp.next
        return None
        

    def printChain(self):
        result=""
        temp = self.head
        while temp != None:
            print(temp.transaction)
            result+=str(temp.transaction)+"\n"
            temp = temp.next
        return result
