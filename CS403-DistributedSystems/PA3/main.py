from FindCitations import FindCitations
from FindCyclicReferences import FindCyclicReferences
import sys

if __name__ == '__main__':
    processType = sys.argv[1]
    numWorkers = int(sys.argv[2])
    fileName = sys.argv[3]
   
    if processType == "COUNT":
        findCitation = FindCitations(numWorkers)
        findCitation.start(fileName)
    elif processType == "CYCLE":
        findCyclic = FindCyclicReferences(numWorkers)
        findCyclic.start(fileName)
    else:
        print("You input a wrong process type! It should be either \"COUNT\" or \"CYCLE\".")
