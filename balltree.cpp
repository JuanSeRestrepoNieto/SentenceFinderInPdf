#include "ball_tree.h"
#include <cmath>
#include <limits>
#include <algorithm>

struct Node {
    std::vector<double> point;
    Node* left;
    Node* right;
};

Node* root;
std::vector<std::vector<double>> data;

double euclidean_distance(const std::vector<double>& a, const std::vector<double>& b) {
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return std::sqrt(sum);
}

Node* build_tree(int left, int right, int depth) {
    if (left > right) return nullptr;

    int mid = (left + right) / 2;
    std::nth_element(data.begin() + left, data.begin() + mid, data.begin() + right + 1,
                     [depth](const std::vector<double>& a, const std::vector<double>& b) {
                         return a[depth % a.size()] < b[depth % a.size()];
                     });

    Node* node = new Node{data[mid], nullptr, nullptr};
    node->left = build_tree(left, mid - 1, depth + 1);
    node->right = build_tree(mid + 1, right, depth + 1);
    return node;
}

void nearest_neighbor(Node* node, const std::vector<double>& target, Node*& best, double& best_dist, int depth) {
    if (!node) return;

    double dist = euclidean_distance(target, node->point);
    if (dist < best_dist) {
        best_dist = dist;
        best = node;
    }

    int axis = depth % target.size();
    Node* next = target[axis] < node->point[axis] ? node->left : node->right;
    Node* other = next == node->left ? node->right : node->left;

    nearest_neighbor(next, target, best, best_dist, depth + 1);

    if (std::abs(target[axis] - node->point[axis]) < best_dist) {
        nearest_neighbor(other, target, best, best_dist, depth + 1);
    }
}

BallTree::BallTree() : root(nullptr) {}

void BallTree::build(const std::vector<std::vector<double>>& points) {
    data = points;
    root = build_tree(0, data.size() - 1, 0);
}

std::vector<double> BallTree::find_nearest(const std::vector<double>& target) {
    Node* best = nullptr;
    double best_dist = std::numeric_limits<double>::max();
    nearest_neighbor(root, target, best, best_dist, 0);
    return best ? best->point : std::vector<double>();
}
