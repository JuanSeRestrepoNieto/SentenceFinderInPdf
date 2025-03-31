
#ifndef BALL_TREE_H
#define BALL_TREE_H

#include <vector>

class BallTree {
private:
    struct Compare {
        int depth;
        Compare(int d) : depth(d) {}

        bool operator()(const std::vector<double>& a, const std::vector<double>& b) const {
            return a[depth % a.size()] < b[depth % a.size()];
        }
    };

    struct Node {
        std::vector<double> point;
        Node* left;
        Node* right;
    };

    Node* root;
    std::vector<std::vector<double> > data;

    // Función auxiliar para construir el árbol
    Node* build_tree(int left, int right, int depth);

    // Función auxiliar para encontrar el vecino más cercano
    void nearest_neighbor(Node* node, const std::vector<double>& target, Node*& best, double& best_dist, int depth);

public:
    BallTree(); // Constructor

    // Construye el árbol a partir de un conjunto de puntos
    void build(const std::vector<std::vector<double> >& points);

    // Encuentra el punto más cercano en el árbol
    std::vector<double> find_nearest(const std::vector<double>& target);
};

#endif // BALL_TREE_H
