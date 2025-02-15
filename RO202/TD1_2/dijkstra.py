import graph
import sys
import numpy as np

def main():
    cities = []
    cities.append("Paris")
    cities.append("Hambourg")
    cities.append("Londres")
    cities.append("Amsterdam")
    cities.append("Edimbourg")
    cities.append("Berlin")
    cities.append("Stockholm")
    cities.append("Rana")
    cities.append("Oslo")

    g = graph.Graph(cities)
    
    g.addArc("Paris", "Hambourg", 7)
    g.addArc("Paris",  "Londres", 4)
    g.addArc("Paris",  "Amsterdam", 3)
    g.addArc("Hambourg",  "Stockholm", 1)
    g.addArc("Hambourg",  "Berlin", 1)
    g.addArc("Londres",  "Edimbourg", 2)
    g.addArc("Amsterdam",  "Hambourg", 2)
    g.addArc("Amsterdam",  "Oslo", 8)
    g.addArc("Stockholm",  "Oslo", 2)
    g.addArc("Stockholm",  "Rana", 5)
    g.addArc("Berlin",  "Amsterdam", 2)
    g.addArc("Berlin",  "Stockholm", 1)
    g.addArc("Berlin",  "Oslo", 3)
    g.addArc("Edimbourg",  "Oslo", 7)
    g.addArc("Edimbourg",  "Amsterdam", 3)
    g.addArc("Edimbourg",  "Rana", 6)
    g.addArc("Oslo",  "Rana", 2)
    
    # Applique l'algorithme de Dijkstra pour obtenir une arborescence
    tree = dijkstra(g, "Paris")
    print(tree)

def dijkstra(g, origin):
		
    # Get the index of the origin 
    r = g.indexOf(origin)

    # Next node considered 
    pivot = r
   
    # Liste qui contiendra les sommets ayant été considérés comme pivot
    v2 = []
    v2.append(r)
   
    pred = [0] * g.n
   
    # Les distances entre r et les autres sommets sont initialement infinies
    pi = [sys.float_info.max] * g.n
    pi[r] = 0

    # Détermination des prédécesseurs et des distances
    for j in range(1, g.n): # Parcourt des sommets
        for y in [i for i,val in enumerate(g.adjacency[pivot]) if val != 0]:
            if pi[pivot]+g.adjacency[pivot][y] < pi[y]: # On vérif si la distance de y est plus avantageuse en passant par pivot
                # Si plus court : maj de predecesseur et de la distance
                pi[y] = pi[pivot]+g.adjacency[pivot][y]
                pred[y] = pivot
        temp = np.array(pi)   # Liste avec les sommet déjà parcouru avec une distance infinie
        temp[v2] = sys.float_info.max
        pivot = np.argmin(temp)
        v2.append(pivot);

    # On créé ensuite l'arborescence
    tree = graph.Graph(g.nodes)
    nodesWithoutOrigin = list(range(g.n))
    nodesWithoutOrigin.pop(r)
    for i in nodesWithoutOrigin:
        tree.addArcByIndex(pred[i], i, g.adjacency[pred[i]][i])

    return tree

if __name__ == '__main__':
    main()
