
#include <iostream>
#include <algorithm>
#include <math.h>

#include "a_star.hpp"


AStar::Node::Node(Vec2i coords_, Node *parent_)
{
    parent = parent_;
    coords = coords_;
    h = h = 0;
}

unsigned int AStar::Node::getScore()
{
    return g + h;
}


AStar::Generator::Generator()
{
    setDiagonalMovement(false);
    setHeuristic(&Heuristic::manhattan);
    direction = {
        { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 },
        { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }
    };
}

void AStar::Generator::setDiagonalMovement(bool enable_)
{
    directions = (enable_ ? 8 : 4);
}

void AStar::Generator::setHeuristic(AStar::HeuristicFunction heuristic_)
{
    heuristic = std::bind(heuristic_, std::placeholders::_1, std::placeholders::_2);
}

void AStar::Generator::setGrid(Grid *grid_)
{
    this->grid = grid_;
}

AStar::CoordinateList AStar::Generator::findPath(Vec2i source_, Vec2i target_)
{
    AStar::Node *current = nullptr;
    AStar::NodeSet openSet, closedSet;
    openSet.reserve(10000);
    closedSet.reserve(10000);
    openSet.push_back(new Node(source_));

    while (!openSet.empty()) {
        auto current_it = openSet.begin();
        current = *current_it;

        for (auto it = openSet.begin(); it != openSet.end(); it++) {
            auto node = *it;
            if (node->getScore() <= current->getScore()) {
                current = node;
                current_it = it;
            }
        }

        if (current->coords == target_) {
            break;
        }

        closedSet.push_back(current);
        openSet.erase(current_it);

        for (unsigned int i = 0; i < directions; ++i) {
            Vec2i newcoords(current->coords + direction[i]);
            if (detectCollision(newcoords) ||
                findNodeOnList(closedSet, newcoords)) {
                continue;
            }

            unsigned int totalCost = current->g + ((i < 4) ? 10 : 14);

            AStar::Node *successor = findNodeOnList(openSet, newcoords);
            if (successor == nullptr) {
                successor = new Node(newcoords, current);
                successor->g = totalCost;
                successor->h = heuristic(successor->coords, target_);
                openSet.push_back(successor);
            }
            else if (totalCost < successor->g) {
                successor->parent = current;
                successor->g = totalCost;
            }
        }
    }

    AStar::CoordinateList path;
    while (current != nullptr) {
        path.push_back(current->coords);
        current = current->parent;
    }

    releaseNodes(openSet);
    releaseNodes(closedSet);

    return path;
}

AStar::Node* AStar::Generator::findNodeOnList(AStar::NodeSet& nodes_, Vec2i coords_)
{
    for (auto node : nodes_) {
        if (node->coords == coords_) {
            return node;
        }
    }
    return nullptr;
}

void AStar::Generator::releaseNodes(AStar::NodeSet& nodes_)
{
    for (auto it = nodes_.begin(); it != nodes_.end();) {
        delete *it;
        it = nodes_.erase(it);
    }
}

bool AStar::Generator::detectCollision(Vec2i coords_)
{
    if (coords_.x < 0 || coords_.x >= grid->width ||
        coords_.y < 0 || coords_.y >= grid->height ||
        grid->at(coords_.x, coords_.y)->type == WALL) {
        return true;
    }
    return false;
}

Vec2i AStar::Heuristic::getDelta(Vec2i source_, Vec2i target_)
{
    return{ abs(source_.x - target_.x),  abs(source_.y - target_.y) };
}

unsigned int AStar::Heuristic::manhattan(Vec2i source_, Vec2i target_)
{
    auto delta = std::move(getDelta(source_, target_));
    return static_cast<unsigned int>(10 * (delta.x + delta.y));
}

unsigned int AStar::Heuristic::euclidean(Vec2i source_, Vec2i target_)
{
    auto delta = std::move(getDelta(source_, target_));
    return static_cast<unsigned int>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
}

unsigned int AStar::Heuristic::octagonal(Vec2i source_, Vec2i target_)
{
    auto delta = std::move(getDelta(source_, target_));
    return 10 * (delta.x + delta.y) + (-6) * std::min(delta.x, delta.y);
}
