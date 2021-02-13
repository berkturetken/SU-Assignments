import zmq
import random
import os
from multiprocessing import Process, Manager
import time
import threading
import sys

leaderMessage = False
terminate = False
mutex = threading.Lock()

def responder(nodeID, starterNodes,aliveNodes, globalDict):
    global leaderMessage
    global terminate
    respondedPairs = []

    print("RESPONDER STARTS:",nodeID)

    ctx = zmq.Context()
    sockets = []
    pollers = []

    for p in aliveNodes:
        if p is not nodeID:
            sock = ctx.socket(zmq.SUB)
            sock.connect("tcp://127.0.0.1:"+str(5500+p))
            sock.subscribe("") 
            sockets.append(sock)
            poller = zmq.Poller()
            poller.register(sock, zmq.POLLIN)
            pollers.append(poller)

    while True:
        count = 0 
        for s in sockets:
            p = pollers[count]
            count += 1
            evts = dict(p.poll(timeout=100))
            
            if s in evts:
                msg = s.recv_string()
                msgType, receivedID = msg.split("-")
                receivedID = int(receivedID)

                if(msgType == "LEADER"):
                    if receivedID < nodeID:
                        mutex.acquire()
                        leaderMessage = True
                        globalDict[receivedID] = True
                        mutex.release()
                        print("RESPONDER RESPONDS", nodeID, receivedID)
                    elif receivedID in starterNodes: # receiveID > nodeID
                        mutex.acquire()
                        leaderMessage = True
                        mutex.release()
                        globalDict[nodeID] = True
                    else: 
                        globalDict[nodeID] = True
                else:
                    mutex.acquire()
                    terminate = True
                    mutex.release()
                    break
                    
        if(terminate):
            break 
    

def leader(nodeID, isStarter,aliveNodes,starterNodes,globalDict):
    global leaderMessage
    global terminate

    pid = os.getpid()
    print("PROCESS STARTS", pid, nodeID, isStarter)

    listener = threading.Thread(target=responder,args=(nodeID,starterNodes,aliveNodes,globalDict,))
    listener.start()

    ctx = zmq.Context()
    sock = ctx.socket(zmq.PUB)
    sock.bind("tcp://127.0.0.1:"+str(5500+nodeID))
    time.sleep(1)

    while True:
        mutex.acquire()
        if((leaderMessage or isStarter)):
            message = "LEADER-"+str(nodeID)
            print("PROCESS MULTICASTS LEADER MSG:", nodeID)
            sock.send_string(message)
            mutex.release()
            time.sleep(1)
            break
        mutex.release()

    cntr = 0
    while True and cntr < 100000:
        if(globalDict[nodeID]):
            break
        cntr += 1

    if(globalDict[nodeID]):    
        while True:
            mutex.acquire()
            if(terminate):
                mutex.release()
                sock.close()
                ctx.term()
                break
            mutex.release()
    else:
        mutex.acquire()
        termMessage = "TERMINATE-" + str(nodeID)
        print("PROCESS BROADCASTS TERMINATE MSG:", nodeID)
        sock.send_string(termMessage)
        terminate = True
        mutex.release()
        time.sleep(2)
    
    listener.join()


if __name__ == '__main__':
    starterNodes = []
    aliveProcesses = []
    allNodes = []

    manager = Manager()
    globalDict = manager.dict()

    numProc = int(sys.argv[1])
    numAlive = int(sys.argv[2])
    numStarters = int(sys.argv[3])

    for num in range(numProc):
        allNodes.append(num+1)
        globalDict[num+1] = False
    
    aliveNodes = random.sample(allNodes,numAlive)
    starterNodes = random.sample(aliveNodes, numStarters)

    print("Alives:")
    print(aliveNodes)

    print("Starters:")
    print(starterNodes)    

    for node in aliveNodes:
        isStarter = False
        if node in starterNodes:
            isStarter = True
        
        p = Process(target = leader, args=(node,isStarter,aliveNodes,starterNodes,globalDict,))
        p.start()
        aliveProcesses.append(p)
    
    for process in aliveProcesses:
        process.join()