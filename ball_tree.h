
#ifndef BALL_TREE_H
#define BALL_TREE_H

#include <vector>

class BallTree {
public:
    BallTree();
    void build(const std::vector<std::vector<double> >& points);
    std::vector<double> find_nearest(const std::vector<double>& target);
};

#endif // BALL_TREE_H
