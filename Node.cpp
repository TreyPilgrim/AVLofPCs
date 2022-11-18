#include "Node.h"

int Node::degree() const
{
    if (this->lChild != nullptr && this->rChild != nullptr)
        return 2;
    else if (this->lChild != nullptr || this->rChild != nullptr)
        return 1;
    else
        return 0;
}
