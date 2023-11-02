# helper class

class Graph:
    __access = 0  # total number of accessment to the graph data, which is used to evaluate your efficiency
    __access_norm = 10000

    __required_jobs = 3  # required number of different jobs in invitees

    __node_num = 0  # number of nodes (friends) in the graph
    __edge_num = 0  # number of edges (conflict relationships) in the graph
    __jobs = []  # __jobs[n] denotes the job of node n
    __job_num = 0  # number of different jobs in the graph
    __edge_list = []  # __edge_list[n][i] denotes the i-th neighbor of node n

    __invitees = []  # __invitees[n] == True: friend n is invited to the party

    def __init__(self, dataset: str):  # reading test case files and initialization
        with open(dataset, 'r') as f:
            nnum = int(f.readline())
            enum = 0

            self.__node_num = nnum

            job_line = f.readline()
            job_line = job_line.split(' ')
            for i in range(nnum):
                self.__jobs.append(int(job_line[i]))

            for i in range(nnum):
                self.__edge_list.append([])

            eline = f.readline()
            while eline:
                if ' ' in eline:
                    eline = eline.split(' ')
                    node0 = int(eline[0])
                    node1 = int(eline[1])
                    self.__edge_list[node0].append(node1)
                    self.__edge_list[node1].append(node0)
                    enum += 1
                eline = f.readline()

        for i in range(nnum):
            self.__edge_list[i].sort()
        self.__invitees = [False for _ in range(nnum)]

        self.__edge_num = enum
        self.__job_num = max(self.__jobs) + 1

    def getNodeNum(self):
        return self.__node_num

    def getEdgeNum(self):
        return self.__edge_num

    def getJobNum(self):
        return self.__job_num

    def getJobs(self, node: int):
        self.__access += 1
        return self.__jobs[node]

    def getDegree(self, node: int):
        self.__access += 1
        return len(self.__edge_list[node])

    def getEdge(self, node: int, index: int):
        self.__access += 1
        return self.__edge_list[node][index]

    def getInvitee(self):
        return self.__invitees

    def setInvitee(self, node: int):  # invite friend represented by "node"
        self.__invitees[node] = True

    def setInviteeFromList(self, node_list):
        for ni in node_list:
            # each element in node_list should be an integer in the range [0, node_num-1]
            if isinstance(ni, int) and ni >= 0 and ni < self.getNodeNum():
                self.setInvitee(ni)

    def isIndependentSet(self):  # check wether the current result is an independent set
        invitee_array = []
        for n in range(len(self.__invitees)):
            if self.__invitees[n]:
                invitee_array.append(n)

        for n in invitee_array:
            for nbr in self.__edge_list[n]:
                if self.__invitees[nbr]:
                    print("error: not a independent set")
                    return False
        return True

    def enoughJobs(self):
        selected_jobs = set()
        for n in range(len(self.__invitees)):
            if self.__invitees[n]:
                selected_jobs.add(self.__jobs[n])
        if len(selected_jobs) >= self.__required_jobs:
            return True
        else:
            print("error: not enough jobs")
            return False

    def score(self):  # the function used for evaluation
        invitee_num = 0
        for n in range(len(self.__invitees)):
            if self.__invitees[n]:
                invitee_num += 1

        is_independent_set = self.isIndependentSet()
        enough_job = self.enoughJobs()
        print("Number of invitees: " + str(invitee_num) + "\n")
        print("Self access:" + str(self.__access) + "\n")
        grades = invitee_num - (self.__access / self.__access_norm)
        if is_independent_set and enough_job:
            return grades
        else:
            if is_independent_set:
                if self.getNodeNum() < 500:
                    return max(grades - 2, 0)
                else:
                    return max(grades - 4, 0)
            else:
                return 0

    def clear(self):
        self.__edge_list.clear()
        self.__jobs.clear()
        self.__invitees.clear()

        self.__access = 0
        self.__node_num = 0
        self.__edge_num = 0
        self.__job_num = 0


def Invitees(g: Graph):
    '''
      return list "results" # including the list of node index recommended
      e.g., results = [0, 1] denotes that friends 0 and 1 will be invited
    '''
    results = []
    # do not change the code above

    # ******************** implement your code here ***********************
    for node in range(g.getNodeNum()): # O(N)
        results.append(node)
    for node in range(g.getNodeNum()): # O(N)
        if node in results:
            for i in range(g.getDegree(node)): # O(M)
                edge = g.getEdge(node, i)
                conflicts = edge
                if conflicts in results:
                    results[conflicts] = -1

    index = 0
    while -1 in results: # O(N)
        if results[index] == -1:
            del results[index]
        else:
            index += 1
    # Time Complexity = O(NxM)
    # *********************************************************************

    # do not change the code below
    return results


# Test case
import time

if __name__ == '__main__':
    dataset = "0Graph_6_1.txt"  # <---- CHANGE txt FILE NAME HERE to use a different network!!!!!!

    # (1) ----- prepare data ------
    print("(1) Reading data from " + dataset + " now...\n")
    g = Graph(dataset)

    # (2) ----- run the test case ------
    print("(2) Starting timer...")
    print("Calling your function now using the network read from " + dataset)
    start_time = time.time()

    results = Invitees(g)
    time_taken = time.time() - start_time
    print("Stopping timer...")
    print("Execution time " + str(time_taken) + " seconds.\n")  # display time lapsed
    # if you see "e" in your execution time, that's scientific notation.
    # e.g. 1e-5 seconds means 1 × 10^(−5) or 0.00001 seconds
    # e.g. 7.8e-05 seconds means 7.8 x 10^(-5) seconds

    # (3) ----- correctness testing code ------
    print("(3) Checking your answer...")
    g.setInviteeFromList(results)
    print(g.getInvitee())
    print("Your score:" + str(g.score()))

    g.clear()
