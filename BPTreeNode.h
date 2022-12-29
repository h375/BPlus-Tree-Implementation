#ifndef BPTREENODE_H
#define BPTREENODE_H
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
class BPTreeNode
{

    public:
        BPTreeNode *parent;
        BPTreeNode *leftSibling;
        BPTreeNode *rightSibling;
        bool isLeaf;
        bool isRoot;
        bool isInterior;
        vector <pair<int,std::string*>> record;
        vector <BPTreeNode*> nextNode;
        BPTreeNode *nextLeaf;
        BPTreeNode();
        ~BPTreeNode();
        vector<int> keys;
        BPTreeNode & operator = (const  BPTreeNode &node);
        BPTreeNode(const BPTreeNode& node);

};

class InteriorNode: public BPTreeNode
{

    public:
        
        InteriorNode(int numKeys);
        ~InteriorNode();
        InteriorNode & operator = (const  InteriorNode &node);
        InteriorNode(const InteriorNode& node);

};

class LeafNode: public BPTreeNode
{

    public:
        
        LeafNode(int numKeys);
        ~LeafNode();
        LeafNode & operator = (const  LeafNode &node);
        LeafNode(const  LeafNode& node);


};




#endif