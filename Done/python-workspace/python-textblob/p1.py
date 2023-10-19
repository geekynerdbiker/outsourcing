import networkx as nx

g = nx.Graph()

g.add_nodes_from(['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O'])
g.add_edges_from(
    [('D', 'A'), ('E', 'A'), ('F', 'A'), ('G', 'A'), ('H', 'A'), ('A', 'B'), ('B', 'C'), ('M', 'C'), ('L', 'C'),
     ('K', 'C'), ('J', 'C'), ('I', 'C'), ('O', 'I'), ('N', 'I')])

nx.draw(g, with_labels=True)
