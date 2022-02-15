class Vertex:
    def __init__(self, id, name):
        self.id = id
        self.name = name
        self.edges = []
        self.minDistance = float('inf')
        self.previousVertex = None

class Edge:
    def __init__(self, source, target, weight):
        self.source = source
        self.target = target
        self.weight = weight

class Dijkstra:
    def __init__(self):
        self.vertexes = []
        self.sortedVertexes = []
        self.initialVertex = None

    def computePath(self, sourceId):
        self.initialVertex = self.vertexes[sourceId]
        self.initialVertex.minDistance = 0
        visitedVertexes = []
        currentVertex = self.initialVertex

        while currentVertex:
            for edge in currentVertex.edges:
                newWeight = currentVertex.minDistance + edge.weight
                targetVertex = self.getVertexById(edge.target)
                if newWeight < targetVertex.minDistance:
                    targetVertex.minDistance = newWeight
                    targetVertex.previousVertex = currentVertex

            self.sortVertexes()
            visitedVertexes.append(currentVertex)
            currentVertex = None

            for vertex in self.sortedVertexes:
                if vertex not in visitedVertexes:
                    currentVertex = vertex
                    break

    def getShortestPathTo(self, targetId):
        vertex = self.getVertexById(targetId)
        path = []
        path.append(vertex)

        prevVertex = vertex.previousVertex

        if not prevVertex and vertex != self.initialVertex:
            return []

        while prevVertex:
            path.append(prevVertex)
            prevVertex = prevVertex.previousVertex

        path.reverse()

        return path


    def createGraph(self, vertexes, edgesToVertexes):
        self.vertexes = vertexes
        self.sortedVertexes = self.vertexes.copy()

        for edge in edgesToVertexes:
            vertex = self.getVertexById(edge.source)
            vertex.edges.append(edge)

    def resetDijkstra(self):
        self.sortedVertexes = self.vertexes.copy()
        self.initialVertex = None

        for vertex in self.vertexes:
            vertex.minDistance = float('inf')
            vertex.previousVertex = None

    def getVertexes(self):
        return self.vertexes

    def getVertexById(self, id):
        for vertex in self.vertexes:
            if vertex.id == id:
                return vertex

    def sortVertexes(self):
        changes = True

        while changes:
            changes = False
            for i in range(0, len(self.sortedVertexes)):
                if not len(self.sortedVertexes) - 1 == i:
                    if self.sortedVertexes[i].minDistance > self.sortedVertexes[i + 1].minDistance:
                        first = self.sortedVertexes[i]
                        self.sortedVertexes[i] = self.sortedVertexes[i + 1]
                        self.sortedVertexes[i + 1] = first
                        changes = True