#pragma once
#include <memory>
#include "PC.h"

class Node;
using ptr = std::shared_ptr<Node>;

class Node : public PC
{
public:

    PC coder;

    int height;

    ptr lChild;
    ptr rChild;

    Node() :
    PC(),
    height{1}, lChild{nullptr}, rChild{nullptr}
    {}

    Node(string nameStr) :
    PC(nameStr),
    height(1), lChild(nullptr), rChild(nullptr)
    {}


    Node(string nameStr, string raceStr, string jobStr, int levelInt) :
    PC(nameStr, raceStr, jobStr, levelInt),
    height {1}, lChild{nullptr}, rChild{nullptr}
    {}

    ~Node() {}

    int degree()const;
};