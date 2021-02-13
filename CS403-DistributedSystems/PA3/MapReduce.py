from abc import ABC, abstractmethod
import os
from multiprocessing import Process, Value
import zmq
import time

class MapReduce(ABC):
    def __init__(self, numWorker):   
        self.mappers = numWorker


    @abstractmethod
    def Map(self, map_input, pid):
        pass


    @abstractmethod
    def Reduce(self, reduce_input):
        pass


    def _Producer(self, producer_input):
        pid = os.getpid()
        context = zmq.Context()

        producer_receiver = context.socket(zmq.PULL)

        for worker in range(self.mappers):
            producer_receiver.connect("tcp://127.0.0.1:"+str(5700+worker))
            message = producer_receiver.recv_json()

        zmq_socket = context.socket(zmq.PUSH)
       
        chunks = []
        for i in range(self.mappers):
            chunks.append([])

        k = 0
        for i in range(len(producer_input)):
            chunks[k % self.mappers].append(producer_input[i])
            k += 1

        for i in range(self.mappers):
            zmq_socket.bind("tcp://127.0.0.1:"+str(5500+i))
            zmq_socket.send_json([chunks[i]])
            time.sleep(0.7)
        

    def _Consumer(self, i):
        pid = os.getpid()
        context = zmq.Context()

        consumer_notifier = context.socket(zmq.PUSH)
        consumer_notifier.bind("tcp://127.0.0.1:" + str(5700+i))
        consumer_notifier.send_json([pid,"I'm here"])

        consumer_receiver = context.socket(zmq.PULL)
        consumer_receiver.connect("tcp://127.0.0.1:" + str(5500+i))
        
        message = consumer_receiver.recv_json()
        result_dict = self.Map(message, pid)

        consumer_sender = context.socket(zmq.PUSH)
        consumer_sender.bind("tcp://127.0.0.1:" + str(5600+i))
        consumer_sender.send_json([pid, result_dict])

        
    def _ResultCollector(self):
        pid = os.getpid()
        context = zmq.Context()

        collector_reciever = context.socket(zmq.PULL)

        result_list = []
        for i in range(self.mappers):
            port_no = 5600 + i
            collector_reciever.connect("tcp://127.0.0.1:" + str(port_no))
            message = collector_reciever.recv_json()
            result_list.append(message[1])

        result_dict = self.Reduce(result_list)

        f = open("results.txt", "w")
        f.write(str(result_dict))


    def start(self, filename):
        file = open(filename, "r", encoding="utf-8")
        text = file.readlines()
        file.close()

        consumers = []
        consumer_count = self.mappers
        
        producer = Process(target = self._Producer, args = (text,))
        producer.start()

        collector = Process(target = self._ResultCollector, args= ())
        collector.start()
        
        for i in range(consumer_count):
            p = Process(target = self._Consumer, args=(i,))
            p.start()
            consumers.append(p)
        
        producer.join()

        for p in consumers:
            p.terminate()
            p.join()

        collector.terminate()
        collector.join()