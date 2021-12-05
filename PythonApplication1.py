class Graph(object):

    def __init__(self):
        #instance fields found by C++ to Python Converter:
        self.__graph = {}


    #Using map structure from Aman slides
    # Graph ADJACENCY LIST data structure here 
    def insertEdge(self, from_keyword_conflict, to, weight):
        s = []
        x = ()
        x[0] = to
        x[1] = weight
        it = self.__graph.find(from_keyword_conflict)
        if it is not self.__graph.end():
            self.__graph[from_keyword_conflict].push_back(x)
            #it->second.push(arr[i])
        else:
            s.append(x)
            self.__graph.update({from_keyword_conflict: s})
        #graph.at(from) = graph.at(from).push_back(x)
        #
        #         TODO: insertEdge() adds a new edge between the from and to vertex.
        #         You will not know how many vertices there may be.
        #         insertEdge does not output or print anything
        #

    def getAdjacent(self, vertex):
        store = []
        #    for (auto it = graph.begin(); it != graph.end(); ++it) {
        #
        #        for (int i = 0; i < it->second.size(); i++) {
        #            if (it->second.at(i).first == vertex) {
        #                store.push_back(it->first)
        #            }
        #        }
        #    }
        it = self.__graph.find(vertex)
        if it is not self.__graph.end():

            #it->second.push(arr[i])

            i = 0
            while i < self.__graph[vertex].size():
                store.append(self.__graph[vertex].at(i).first)
                i += 1
            store.sort()
        #TODO: getAdjacent() returns a sorted vector of all vertices that are connected to a vertex
        return list(store)

    def getIndegree(self, vertex):
        #
        #        TODO: getIndegree() returns the indegree of vertex
        #
        count = 0
        it = graph.begin()
        while it is not self.__graph.end():

            i = 0
            while i < it.second.size():
                if it.second.at(i).first == vertex:
                    count += 1
                i += 1
            it += 1
        return count

    def getOutdegree(self, vertex):
        it = self.__graph.find(vertex)
        if it is self.__graph.end():

            #it->second.push(arr[i])

            return 0
        #
        #        TODO: getOutdegree() returns the outdegree of vertex
        #
        return self.__graph[vertex].size()

    def costliestEdge(self):
        its = self.__graph.begin()
        max = its.second.at(0).second
        it = graph.begin()
        while it is not self.__graph.end():

            i = 0
            while i < it.second.size():
                if it.second.at(i).second > max:
                    max = it.second.at(i).second
                i += 1
            it += 1
        return max
        #TODO: costliestEdge() returns the edge weight of the costliest edge


