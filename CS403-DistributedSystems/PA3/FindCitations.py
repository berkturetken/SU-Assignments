from MapReduce import MapReduce 

class FindCitations(MapReduce):
    def Map(self, map_input, pid):
        result_dict = {}

        for i in range(len(map_input[0])):
            k = map_input[0][i].split()
            cited_one = k[1]
            
            # Modify the dictionary
            if (cited_one in result_dict.keys()):
                result_dict[str(cited_one)] += 1
            else:
                result_dict[str(cited_one)] = 1
        return result_dict        


    def Reduce(self, reduce_input):
        result_dict = {}
        for dictionary in reduce_input:
            result_dict = {k: result_dict.get(k, 0) + dictionary.get(k, 0) for k in set(result_dict) | set(dictionary)}

        return result_dict