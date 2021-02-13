import threading
import time
import random
from ConSet import MyConSet

ServerMailbox = [MyConSet(), MyConSet(), MyConSet()]
votes = []

def nodeWork(id, n):
    individualVote = random.randint(1, n*n)
    tup = (id, individualVote)
    votes.append(tup)
    for i in range(len(ServerMailbox)):
        ServerMailbox[i].insert(tup)
    print(ServerMailbox)
        

def server(n):
    counter = 0
    while counter != n:
        for i in range(len(ServerMailbox)):
            receivedMsg = ServerMailbox[i].pop()
            identifier = receivedMsg[0]
            vote = receivedMsg[1]
            print(str(identifier) + ' ' + str(vote))
        counter = counter + 1



t1 = threading.Thread(target=nodeWork, args=(0, 3))
t2 = threading.Thread(target=nodeWork, args=(1, 3))
t3 = threading.Thread(target=nodeWork, args=(2, 3))
t4 = threading.Thread(target=server,   args=(3,))

t1.start()
t2.start()
t3.start()
t4.start()

t1.join()
t2.join()
t3.join()
t4.join()