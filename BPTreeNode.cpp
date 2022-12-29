#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "BPTreeNode.h"
using namespace std;

BPTreeNode::BPTreeNode(){
    isRoot = true;
  

}

BPTreeNode::~BPTreeNode(){
    nextNode.clear();
    keys.clear();
    for(int i = 0; i < record.size();i++)
    {
       delete record[i].second;
    }
    record.clear();
    parent = NULL;
    nextLeaf = NULL;
    leftSibling = NULL;
    rightSibling = NULL;
}

LeafNode::LeafNode(int numKeys)
{
    
    isLeaf = true;
    isRoot = false;
    isInterior = false;
    

}

LeafNode::~LeafNode()
{
    nextNode.clear();
    keys.clear();
     for(int i = 0; i < record.size();i++)
    {
       delete record[i].second;
    }
    record.clear();
    
    parent = NULL;
    nextLeaf = NULL;
    leftSibling = NULL;
    rightSibling = NULL;

}

InteriorNode::InteriorNode(int numKeys)
{
    
    isInterior = true;
    isRoot = false;
    isLeaf = false;
   


}
InteriorNode::~InteriorNode()
{
    nextNode.clear();
    keys.clear();
    record.clear();
    parent = NULL;
    nextLeaf = NULL;
    leftSibling = NULL;
    rightSibling = NULL;

}

BPTreeNode & BPTreeNode:: operator = (const  BPTreeNode &node)
{
    
    keys.clear();
    for(int i =0; i < node.keys.size();i++)
    {
        keys.push_back(node.keys[i]);
    }
    nextNode.clear();
    for(int i =0; i < node.nextNode.size();i++)
    {
        nextNode.push_back(node.nextNode[i]);
    }
    record.clear();
    for(int i =0; i < node.record.size();i++)
    {
        record.push_back(node.record[i]);
    }

    parent = node.parent;
    nextLeaf = node.nextLeaf;
    isInterior = node.isInterior;
    isLeaf = node.isLeaf;
    isRoot = node.isRoot;
    leftSibling = node.leftSibling;
    rightSibling = node.rightSibling;

    return *this;
}

InteriorNode & InteriorNode:: operator = (const  InteriorNode &node)
{
    keys.clear();
    for(int i =0; i < node.keys.size();i++)
    {
        keys.push_back(node.keys[i]);
    }
    nextNode.clear();
    for(int i =0; i < node.nextNode.size();i++)
    {
        nextNode.push_back(node.nextNode[i]);
    }
    record.clear();
    for(int i =0; i < node.record.size();i++)
    {
        record.push_back(node.record[i]);
    }

    parent = node.parent;
    nextLeaf = node.nextLeaf;
    isInterior = node.isInterior;
    isLeaf = node.isLeaf;
    isRoot = node.isRoot;
    leftSibling = node.leftSibling;
    rightSibling = node.rightSibling;

    return *this;
}

LeafNode & LeafNode:: operator = (const  LeafNode &node)
{
    keys.clear();
    for(int i =0; i < node.keys.size();i++)
    {
        keys.push_back(node.keys[i]);
    }
    nextNode.clear();
    for(int i =0; i < node.nextNode.size();i++)
    {
        nextNode.push_back(node.nextNode[i]);
    }
    record.clear();
    for(int i =0; i < node.record.size();i++)
    {
        record.push_back(node.record[i]);
    }

    parent = node.parent;
    nextLeaf = node.nextLeaf;
    isInterior = node.isInterior;
    isLeaf = node.isLeaf;
    isRoot = node.isRoot;
    leftSibling = node.leftSibling;
    rightSibling = node.rightSibling;

    return *this;
}


BPTreeNode:: BPTreeNode(const BPTreeNode& node)
{
    keys.clear();
    for(int i =0; i < node.keys.size();i++)
    {
        keys.push_back(node.keys[i]);
    }
    nextNode.clear();
    for(int i =0; i < node.nextNode.size();i++)
    {
        nextNode.push_back(node.nextNode[i]);
    }
    record.clear();
    for(int i =0; i < node.record.size();i++)
    {
        record.push_back(node.record[i]);
    }

    parent = node.parent;
    nextLeaf = node.nextLeaf;
    isInterior = node.isInterior;
    isLeaf = node.isLeaf;
    isRoot = node.isRoot;
    leftSibling = node.leftSibling;
    rightSibling = node.rightSibling;
    

}

InteriorNode:: InteriorNode(const InteriorNode& node)
{


    keys.clear();
    for(int i =0; i < node.keys.size();i++)
    {
        keys.push_back(node.keys[i]);
    }
    nextNode.clear();
    for(int i =0; i < node.nextNode.size();i++)
    {
        nextNode.push_back(node.nextNode[i]);
    }
    record.clear();
    for(int i =0; i < node.record.size();i++)
    {
        record.push_back(node.record[i]);
    }

    parent = node.parent;
    nextLeaf = node.nextLeaf;
    isInterior = node.isInterior;
    isLeaf = node.isLeaf;
    isRoot = node.isRoot;
    leftSibling = node.leftSibling;
    rightSibling = node.rightSibling;

}

LeafNode:: LeafNode(const LeafNode& node)
{


    keys.clear();
    for(int i =0; i < node.keys.size();i++)
    {
        keys.push_back(node.keys[i]);
    }
    nextNode.clear();
    for(int i =0; i < node.nextNode.size();i++)
    {
        nextNode.push_back(node.nextNode[i]);
    }
    record.clear();
    for(int i =0; i < node.record.size();i++)
    {
        record.push_back(node.record[i]);
    }

    parent = node.parent;
    nextLeaf = node.nextLeaf;
    isInterior = node.isInterior;
    isLeaf = node.isLeaf;
    isRoot = node.isRoot;
    leftSibling = node.leftSibling;
    rightSibling = node.rightSibling;

}