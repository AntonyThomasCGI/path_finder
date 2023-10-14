#ifndef A_STAR_HPP
#define A_STAR_HPP

#include <functional>
#include <vector>

#include "common.hpp"
#include "square.hpp"


struct Node
{
    unsigned int g, h;
    Vec2i coords;
    Node *parent;

    Node(Vec2i coords_, Node *parent_ = nullptr);
    unsigned int getScore();
};


typedef std::function<unsigned int(Vec2i, Vec2i)> HeuristicFunction;
typedef std::vector<Vec2i> CoordinateList;
typedef std::vector<Node*> NodeSet;



class Generator
{
    bool detectCollision(Vec2i coords_);
    Node* findNodeOnList(NodeSet &nodes_, Vec2i coords_);
    void releaseNodes(NodeSet &nodes_);
public:
    Generator();
    void setWorldSize(Vec2i worldSize_);
    void setDiagonalMovement(bool enable_);
    void setHeuristic(HeuristicFunction heuristic_);

    CoordinateList findPath(Vec2i source_, Vec2i target_);
    void addCollision(Vec2i coords_);
    void removeCollision(Vec2i coords_);
    void clearCollisions();

private:
    HeuristicFunction heuristic;
    CoordinateList direction, walls;
    Vec2i worldSize;
    unsigned int directions;
};


class Heuristic
{
    static Vec2i getDelta(Vec2i source_, Vec2i target_);

public:
    static unsigned int manhattan(Vec2i source_, Vec2i target_);
    static unsigned int euclidean(Vec2i source_, Vec2i target_);
    static unsigned int octagonal(Vec2i source_, Vec2i target_);
};


#endif
