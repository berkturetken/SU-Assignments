from MapReduce import MapReduce 

class FindCyclicReferences(MapReduce):
    def Map(self, map_input, pid):
        result_dict = {}
        traverse = map_input[0]

        for line in traverse:
            line = line.split("\t")
            line[1] = line[1].strip("\n")
            A = int(line[0])
            B = int(line[1])
            key = ()
            if A > B:
                key = str((B, A))
            else:
                key = str((A, B))

            if key in result_dict:
                result_dict[key] = result_dict[key] + 1
            else :
                result_dict[key] = 1
        return result_dict


    def Reduce(self, reduce_input):
        result_dict = {}
        for dictionary in reduce_input:
            result_dict = {k: result_dict.get(k, 0) + dictionary.get(k, 0) for k in set(result_dict) | set(dictionary)}
        
        final_dict = {}
        for key in result_dict:
            if result_dict[key] == 2:
                final_dict[key] = 1

        return final_dict