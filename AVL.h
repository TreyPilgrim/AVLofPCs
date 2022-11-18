#pragma once
#include "Node.h"
#include <iostream>
#include <memory>
#include <string>

using namespace std;
using ptr = std::shared_ptr<Node>;

class AVL
{
private:
    ptr root;

    ptr find(ptr &node, string name);

    static int MAX (int a, int b);
    static int height(const ptr& node);
    static int BF (const ptr& node);

    bool insert(ptr& node, string& name);
    bool remove(ptr &node, string name);
    static bool peek(const ptr& node);

    static void rightRotate(ptr& node);
    static void leftRotate(ptr& node);
    static void balance(ptr& node);
    static void displayNode(const ptr& node, std::ostream &os);

    void scanTree(const ptr& node, std::string stat, const string& val);
    void scanTree(const ptr& node, int val);
    void preOrder(ptr &node, std::ostream &os);
    void inOrder(ptr &node, std::ostream &os);
    void postOrder(ptr &node, std::ostream &os);
    void balanceTree(ptr& node);
    void destroy (ptr &node);

    ptr find(string name);
public:
    AVL():
            root {nullptr} {}

    ~AVL();


    bool insert(string& name);
    bool remove(string name);
    bool peek();
    bool updateStat(const string& name, string stat, string val);
    bool updateStat(const string& name, int val);

    void scanTree (string stat, const string& val);
    void scanTree (int val);
    void inOrder(std::ostream &os);
    void preOrder(std::ostream &os);
    void postOrder(std::ostream &os);

    template <typename T>
    static T fixVal (T str);


};

