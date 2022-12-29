#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include "BPTreeNode.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;


class BPlusTree{

    public:
        BPTreeNode *root;
        int numKeys;
        BPlusTree(int key);
        ~BPlusTree();
        BPlusTree & operator = (const BPlusTree &tree);
        BPlusTree(const BPlusTree &tree);
        bool insert(int key, string val);
        bool remove(int key);
        string find(int key);
        void printKeys();
        void printValues();
        bool isEmpty;
        
    private:
        BPTreeNode* getnextNode(BPTreeNode *node, int key);
        void traverse(BPTreeNode *node);
        void insertRecurse(BPTreeNode *node,int key,std::string val);
        bool checkDuplicates(BPTreeNode *node, int key);
        bool removeRecurse(BPTreeNode *node);
        void adjustnextLeaf();
        void adjustSiblings(BPTreeNode *node);
        void sortChildren(BPTreeNode *node);
        void sortKeys(BPTreeNode *node);
        void print(BPTreeNode *node,vector <BPTreeNode*> children);
        void printLeaves(BPTreeNode *leaf);
        vector <BPTreeNode*> getLeaves(BPTreeNode *node,vector <BPTreeNode*> children);
        

}; 
#endif