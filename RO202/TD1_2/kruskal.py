import numpy as np
import graph
import sys

def main():
    
    # Créer un graphe contenant les sommets a, b, c, d, e, f, g 
    g = graph.Graph(np.array(["a", "b", "c", "d", "e", "f", "g"]))

    # Ajouter les arêtes
    g.addEdge("a", "b",  1.0)
    g.addEdge("a", "c",  3.0)
    g.addEdge("b", "c",  2.0)
    g.addEdge("b", "d",  5.0)
    g.addEdge("b", "e",  7.0)
    g.addEdge("b", "f",  9.0)
    g.addEdge("c", "d",  4.0)
    g.addEdge("d", "e",  6.0)
    g.addEdge("d", "g", 12.0)
    g.addEdge("e", "f",  8.0)
    g.addEdge("e", "g", 11.0)
    g.addEdge("f", "g", 10.0)
    
    # Obtenir un arbre couvrant de poids minimal du graphe
    tree = kruskal(g, True)
    
    # S'il existe un tel arbre (i.e., si le graphe est connexe)
    if tree != None:
        
        # L'afficher
        print(tree)
    
    else:
        print("Pas d'arbre couvrant")


    print("\nGraphe 1 de la figure 1 : ")
    graph1(False)
    print("\nGraphe 2 de la figure 1 : ")
    graph2(False)

def graph1(computeMin):
    # Créer un graphe contenant les sommets a, b, c, d, e, f, g et h
    g = graph.Graph(np.array(["a", "b", "c", "d", "e", "f", "g","h"]))
    # Ajouter les arêtes
    g.addEdge("a", "b",  9.0)
    g.addEdge("a", "f",  6.0)
    g.addEdge("a", "h",  9.0)
    g.addEdge("f", "e", 1.0)
    g.addEdge("b", "e", 5.0)
    g.addEdge("b", "c", 5.0)
    g.addEdge("b", "d", 8.0)
    g.addEdge("e", "g", 3.0)
    g.addEdge("c", "g", 5.0)
    g.addEdge("c", "d", 2.0)
    g.addEdge("g", "d", 8.0)
    g.addEdge("g", "h", 5.0)
    g.addEdge("d", "h", 7.0)

    tree = kruskal(g, computeMin)
    if tree != None:
        print(tree)
    else:
        print("Pas d'arbre couvrant")


def graph2(computeMin):
    # Créer un graphe contenant les sommets a, b, c, d, e, f, g et h
    g = graph.Graph(np.array(["a", "b", "c", "d", "e", "f"]))
    # Ajouter les arêtes
    g.addEdge("a", "b",  4.0)
    g.addEdge("a", "c",  3.0)
    g.addEdge("b", "c",  5.0)
    g.addEdge("b", "f", 2.0)
    g.addEdge("c", "f", 5.0)
    g.addEdge("c", "d", 2.0)
    g.addEdge("f", "d", 3.0)
    g.addEdge("f", "e", 3.0)
    g.addEdge("d", "e", 4.0)

    tree = kruskal(g, computeMin)
    if tree != None:
        print(tree)
    else:
        print("Pas d'arbre couvrant")

# Applique l'algorithme de Kruskal pour trouver un arbre couvrant de poids minimal d'un graphe
# Retourne: Un arbre couvrant de poids minimal du graphe ou None s'il n'en existe pas
def kruskal(g, computeMin):
    
    # Créer un nouveau graphe contenant les mêmes sommets que g
    tree = graph.Graph(g.nodes)
    
    # Nombre d'arêtes dans l'arbre
    addedEdges = 0
    
    # Récupérer toutes les arêtes de g
    edges = g.getEdges()
    
    # Trier les arêtes par poids croissant
    edges.sort()
    if not computeMin:
        edges.reverse() # Si on veut l'arbre de poids maximal, il suffit de trier dans l'ordre décroissant : on "retourne" la liste triée
        
    # Lancer le parcours des arêtes triées
    for edge in edges:
        if not tree.createACycle(edge):
            tree.addCopyOfEdge(edge)
    
    # Vérification si l'arbre est connexe
    if len(tree.getEdges()) == len(tree.nodes)-1:
        return tree
    else:
        return None


if __name__ == '__main__':
    main()
