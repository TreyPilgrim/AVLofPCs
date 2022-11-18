#include "AVL.h"
#include <iostream>
#include <memory>
#include <utility>

using namespace std;
using ptr = std::shared_ptr<Node>;

/*
 *                             Private Functions
 */



/*
 * Ptr Return Type
 */
// Return Node in AVL Func w/ name
ptr AVL::find(ptr &node, string name)
{
    if (node.use_count() == 0 || node->getName() == name)
        return node;
    else if (node->getName() > name)
        return find(node->lChild, std::move(name));
    else
        return find(node->rChild, std::move(name));
}


/*
 * Int return type
 */
// Return max height func
int AVL::MAX(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

// Return the height of node
int AVL::height(const ptr& node)
{
    if (node == nullptr)
        return 0;

    return node->height;
}

// Return Balance Factor
int AVL::BF(const ptr& node)
{
    if (node == nullptr)
        return 0;

    return (height(node->lChild) - height(node->rChild));
}

/*
 * Bool Return Type
 */
// Insert Func
bool AVL::insert(ptr& node, string& name)
{
    bool success;

    if (!isupper(name[0]))
    {
        cout << "Input upgraded from, '" << name <<"' to '";
        name = fixVal(name);
        cout << name << "'" << endl;
    }

    if (node.use_count() == 0)// if empty, create a new leaf
    {
        node = std::make_shared<Node>(name);
        cout << name << " added to the AVL" << endl;
        return true;
    }
    else if (node->getName() == name) // OR if data is a duplicate, return false
        return false;

    // recursively go down the tree to find next leaf
    success = (name < node->getName()) ?
              insert(node->lChild, name) : insert(node->rChild, name);

    // return false if duplicate is found
    if (!success)
        return false;

    // Update node's height
    node->height = MAX(height(node->lChild), height(node->rChild)) +1;

    // re-balance the tree then return true
    balance(node);
    return true;
}

// Remove Func
bool AVL::remove(ptr &node, string name)
{
    if (node.use_count() == 0)
        return false;
    if (name < node->getName())
        return remove(node->lChild, std::move(name));
    if (name > node->getName())
        return remove(node->rChild, std::move(name));

    // get degree of node
    int deg = node->degree();

    if (deg == 0) // No kids? delete node
        node = nullptr;
    else if (deg == 1) // 1 Kid? swap with kid then delete
        node = (node->lChild.use_count() != 0) ?
               node->lChild : node->rChild;
    else // 2 kids -> find predecessor and replace
    {
        // find predecessor
        ptr theReplacement = node->lChild;
        while (theReplacement->rChild.use_count() != 0)
        {
            theReplacement = theReplacement->rChild;
        }

        //

        node->coder = theReplacement->coder; // update the node w/ predecessor
        remove(node->lChild, node->getName()); // delete predecessor from tree
    }

    balanceTree(node);
    return true;
}

// Peek Func
bool AVL::peek(const ptr& node)
{
    if (node.use_count() == 0)
        return false;
    else
        return true;
}

/*
 * Void Return type
 */

// Right Rotate Func
void AVL::rightRotate(ptr& node)
{
    ptr left = std::make_shared<Node>();
    left = node->lChild;

    ptr hold = std::make_shared<Node>();
    hold = left->rChild;

    left->rChild = node;
    node->lChild = hold;

    node->height = MAX(height(node->lChild),
                       height(node->rChild)) +1;

    left->height = MAX(height(left->lChild),
                       height(left->rChild)) +1;

    node = left;

}

// Left rotate func
void AVL::leftRotate(ptr &node)
{
    ptr right = std::make_shared<Node>();
    right = node->rChild;

    ptr hold = std::make_shared<Node>();
    hold = right->lChild;

    right->lChild = node;
    node->rChild = hold;

    node->height = MAX(height(node->rChild),
                       height(node->lChild)) + 1;

    right->height = MAX(height(right->lChild),
                        height(right->rChild)) + 1;

    node = right;
}

// Balance the node
void AVL::balance(ptr& node)
{
    int balance = BF(node);

    if (balance > 1)
    {
        if (BF(node->lChild) < 0) // if lChild == -1, LR-Rotate
            leftRotate(node->lChild);

        rightRotate(node);
    }

    if (balance < -1)
    {
        if (BF(node->rChild) > 0) // if rChild == +1, RL-Rotate
            rightRotate(node->rChild);

        leftRotate(node);
    }
}

// Display Node
void AVL::displayNode(const ptr& node, std::ostream &os)
{
    os << "Player: " << node->getName() << endl;
    os << "Race: " << node->getRace() << endl;
    os << "Job: " << node->getJob() << endl;
    os << "Level: " << node->getLevel() << endl;
    os << "============================================================\n";

}

// Scan Tree for Job/Race/Level match
void AVL::scanTree(const ptr& node, string stat, const string& val)
{

    if(!this->peek())
    {
        cout << "The AVL is empty... \n"
                "Please create new data to save" << endl;
    }
    if (node == nullptr)
        return;

    scanTree(node->lChild, stat, val);

    stat = fixVal(stat);

    if (val == node->getJob() || val == node->getRace())
        displayNode(node, cout);

    scanTree(node->rChild, stat, val);
}

// Scan Tree for Level matches
void AVL::scanTree (const ptr& node, int val)
{
    if (node == nullptr)
        return;

    scanTree(node->lChild, val);

    if (node->getLevel() == val)
        displayNode(node, cout);

    scanTree(node->rChild, val);
}
// PreOrder
void AVL::preOrder(ptr &node, std::ostream &os)
{
    if (node == nullptr)
        return;

    this->displayNode(node, os);
    preOrder(node->lChild, os);
    preOrder(node->rChild, os);

}

// InOrder
void AVL::inOrder(ptr &node, std::ostream &os)
{
    // prevent infinite recursion
    if (node == nullptr)
        return;

    inOrder(node->lChild, os);
    this->displayNode(node, os);
    inOrder(node->rChild, os);
}

// PostOrder
void AVL::postOrder(ptr &node, std::ostream &os)
{
    if (node == nullptr)
        return;

    postOrder(node->lChild, os);
    postOrder(node->rChild, os);
    this->displayNode(node, os);

}

// Ensure the tree is balanced
void AVL::balanceTree(ptr &node)
{
    if (node == nullptr)
        return;

    balanceTree(node->lChild);
    node->height = MAX(height(node->lChild),
                       height(node->rChild)) +1;

    balanceTree(node->rChild);
    node->height = MAX(height(node->rChild),
                       height(node->lChild)) + 1;

    if (BF(node) == 2)
        balance(node);
}

// Destroyer
void AVL::destroy(ptr &node)
{
    bool deadTree {false};
    if (root.use_count() == 0)
    {
        cout << "\nOver 40% of Deforestation happens in Brazil.\n "
                "Make sure to recycle and all your trash finds a can, not the ground..." << endl;
        return;
    }
    while (!deadTree)
    {
        deadTree = remove(root, root->getName());
    }
    cout << "Over 40% of Deforestation happens in Brazil.\n "
            "Make sure to recycle and make sure all your trash finds a can, not the ground..." << endl;
}
/*
 *                                      Public Functions
 */
/*
 * Destructor
 */
AVL::~AVL()
{
    this->destroy(root);
}
/*
 * Ptr Return Type
 */
// Return Node w/ name
ptr AVL::find(string name)
{
    return find(root, std::move(name));
}

/*
 *  Bool Return Type
 */
// Insert func
bool AVL::insert(string& name)
{
    return insert(root, name);
}

// Remove func
bool AVL::remove(string name)
{
    return remove(root, std::move(name));
}

// Peek func
bool AVL::peek()
{
    return peek(root);
}

bool AVL::updateStat(const string& name, string stat, string val)
{
    ptr tmp = find(name);
    if (tmp == nullptr)
        return false;
    else if (stat == "Job")
        tmp->setJob(val);
    else
        tmp->setRace(val);

    cout << name << "'s ";
    stat[0] = tolower(stat[0]);
    cout << stat << " updated to " << val << endl;

    return true;

}

bool AVL::updateStat(const string& name,  int val)
{
    ptr tmp = find(name);
    if (tmp.use_count() == 0)
        return false;
    else
        tmp->setLevel(val);

    cout << name << "'s level updated to " << val << endl;
    return true;
}

/*
 * Void Return Type
 */
void AVL::scanTree(string stat, const string& val)
{
    return scanTree(root, std::move(stat), val);
}

void AVL::scanTree(int val)
{
    return scanTree(root, val);
}
void AVL::inOrder(std::ostream &os)
{
    inOrder(root, os);
}

void AVL::preOrder(std::ostream &os)
{
    preOrder(root, os);
}

void AVL::postOrder(std::ostream &os)
{
    postOrder(root, os);
}

/*
 * Templated Return Type
 */
// Return string with a capital first character
template <typename T>
T AVL::fixVal(T str)
{
    str[0] = toupper(str[0]);
    return str;
}