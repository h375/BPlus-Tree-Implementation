#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "BPlusTree.h"
using namespace std;



BPlusTree::BPlusTree(int key)
{
   root = new BPTreeNode();
   numKeys = key;
   isEmpty = true;

}


BPlusTree & BPlusTree:: operator = (const BPlusTree &tree)
{
   root = new BPTreeNode();
   numKeys = tree.numKeys;
   isEmpty = true;

   vector <BPTreeNode*> leaves;

   if(tree.root != NULL)
   {

      leaves = getLeaves(tree.root,leaves);
      for(int i =0; i < leaves.size(); i++)
      {
         for(int j = 0;j < leaves[i]->record.size();j++)
         {
            insert(leaves[i]->record[j].first,*leaves[i]->record[j].second);
         }

      }

   }



   return *this;

}


 BPlusTree::BPlusTree(const BPlusTree &tree)
 {

   root = new BPTreeNode();
   numKeys = tree.numKeys;
   isEmpty = true;

  vector <BPTreeNode*> leaves;

   if(tree.root != NULL)
   {

      leaves = getLeaves(tree.root,leaves);
      for(int i =0; i < leaves.size(); i++)
      {
         for(int j = 0;j < leaves[i]->record.size();j++)
         {
            insert(leaves[i]->record[j].first,*leaves[i]->record[j].second);
         }

      }

   }
 

 }

BPlusTree::~BPlusTree()
{
   delete root;
   numKeys = 0;
   isEmpty = true;
}

bool BPlusTree::checkDuplicates(BPTreeNode *node, int key)
{
      
   while(node->isLeaf == false)
   {
      node = getnextNode(node,key);

   }

   for(int i =0; i < node->record.size(); i++)
   {
      if(key == node->record[i].first)
      {
         return true;
      }
   }
   return false;
}


bool BPlusTree::insert(int key, string val)
{
   int firstN = 0;
   int remN = 0;
   int middleKey;
   BPTreeNode *current;

   // check if tree is empty
   if(isEmpty)
   {
      string* str = new string(val);
      root->record.push_back(std::make_pair(key,str));
      root->isLeaf = true;
      root->isRoot = true;
      isEmpty = false;
      return true;
      
   }
   else if(checkDuplicates(root,key) == true)
   {
      return false;
   }

   else if(root->isLeaf && root->isRoot) // fill root node first
   {
      if(root->record.size() == numKeys) // root is full
      { 
         
         firstN = ceil((numKeys + 1)/2);
         remN = floor((numKeys + 1)/2);
         string* str = new string(val);
         root->record.push_back(std::make_pair(key,str));

         sortKeys(root);
         BPTreeNode *newRoot = new BPTreeNode();
         BPTreeNode *newNode = new LeafNode(numKeys);
         BPTreeNode *origNode;
         origNode = root;
         origNode->isLeaf = true;
         origNode->isRoot = false;
         origNode->isInterior = false;

         if(root->record.size() % 2 != 0)
         {
            firstN = ceil(1.0*(numKeys + 1)/2);
            remN = floor(1.0*(numKeys + 1)/2);
            
         }

         //records
         for(int i =0; i < root->record.size();i++)
         {
            if(i >=firstN)
            {
               newNode->record.push_back(root->record[i]);
            }
            
         }

         for(int i=0 ; i < remN; i++)
         {
            origNode->record.pop_back();
         }



         newNode->nextLeaf = root->nextLeaf;
         origNode->nextLeaf = newNode; //chain leaf nodes
         newNode->rightSibling = origNode->rightSibling;
         newNode->leftSibling = origNode;
         origNode->rightSibling = newNode;
         
         
         newRoot->keys.push_back(newNode->record[0].first);
         newRoot->nextNode.push_back(origNode);
          newRoot->nextNode.push_back(newNode);
          root = newRoot;

         newNode->parent = root;
         origNode->parent = root;
         root->isRoot = true;
         root->isLeaf = false;

         return true;

      }
      else
      {
         string* str = new string(val);
         root->record.push_back(std::make_pair(key,str));
         sortKeys(root);

         return true;
      }


   } 
   else
   {
      current = root;
      while(current->isLeaf == false)
      {
         current = getnextNode(current,key);

      }
      // found a leaf node


      // check if it is full 
      if(current->record.size() == numKeys)// full split it
      {
         

         if(current->parent->keys.size() < numKeys) // parent not full
         {
            firstN = ceil((numKeys + 1)/2);
            remN = floor((numKeys + 1)/2);

            //split leaves
            string* str = new string(val);
            current->record.push_back(std::make_pair(key,str));

            sortKeys(current);

            if(current->record.size() % 2 != 0)
            {
               firstN = ceil(1.0*(numKeys + 1)/2);
               remN = floor(1.0*(numKeys + 1)/2);
            }
            
            BPTreeNode *newNode = new LeafNode(numKeys);
            BPTreeNode *origNode;
            origNode = current;
            origNode->isLeaf = true;
            origNode->isRoot = origNode->isInterior = false;

            

            for(int i =0; i < current->record.size();i++)
            {
               if(i >=firstN)
               {
                  newNode->record.push_back(current->record[i]);
               }
               
            }

            for(int i =0; i < remN;i++)
            {
               origNode->record.pop_back();
            }

            newNode->parent = current->parent;
            origNode->parent = current->parent;


            newNode->nextLeaf = current->nextLeaf;
            origNode->nextLeaf = newNode; //chain nodes
            newNode->rightSibling = origNode->rightSibling;
            newNode->leftSibling = origNode;
            origNode->rightSibling = newNode;
            
           
            current->parent->keys.push_back(newNode->record[0].first);

            sortKeys(current->parent);
            
            
            current->parent->nextNode.push_back(newNode);

            sortChildren(current->parent);
            
            
            return true;

         }
         else // parent is full
         {
            insertRecurse(current,key,val);
            return true;
           
         }
               
      }
      else
      {
         string* str = new string(val);
         current->record.push_back(std::make_pair(key,str));

         sortKeys(current);
         return true;
      }


   }
   return false;  

}




void BPlusTree::printKeys()
{
   vector <BPTreeNode*> children;
   print(root,children);

}


BPTreeNode* BPlusTree::getnextNode(BPTreeNode *node, int key)
{
   for(int i = 0; i < node->keys.size();i++)
   {
      if(key < node->keys[0])
      {
         return node->nextNode[0];
      }
      else if(i >= 1 && i < node->keys.size())
      {
         if(key >= node->keys[i-1] && key < node->keys[i])
         {
            return node->nextNode[i];
         }

      }
      else if(key >= node->keys.back())
      {
         return node->nextNode[node->keys.size()];
         
      }
   }
   return NULL;
}


string BPlusTree::find(int key)
{
   BPTreeNode *current = root;
   while(current->isLeaf == false)
   {
      current = getnextNode(current,key);

   }
   for(int i = 0; i < current->record.size();i++)
   {
      if(key == current->record[i].first)
      {
         return *current->record[i].second;
      }
   }


   return " ";
}






void BPlusTree::insertRecurse(BPTreeNode *current,int key,string val)
{
   int firstN = 0;
   int remN = 0;
   int middleKey;

   BPTreeNode *newRoot = new BPTreeNode();
   BPTreeNode *newParOrig;
   BPTreeNode *newParNew = new InteriorNode(numKeys);
   
  if(current->isLeaf)
  {
      // split the leaves first
      firstN = ceil((numKeys + 1)/2);
      remN = floor((numKeys + 1)/2);
      string* str = new string(val);
      current->record.push_back(std::make_pair(key,str));

      sortKeys(current);

      if(current->record.size() % 2 != 0){
         firstN = ceil(1.0*(numKeys + 1)/2);
         remN = floor(1.0*(numKeys + 1)/2);
      }

      BPTreeNode *newNode = new LeafNode(numKeys);
      BPTreeNode *origNode;
      origNode = current;
      origNode->isLeaf = true;
      origNode->isRoot = false;
      origNode->isInterior = false;
         
   
   for(int i =0; i < current->record.size();i++)
   {
      if(i>=firstN)
      {
         newNode->record.push_back(current->record[i]);
      }
      
   }
   for(int i =0; i < remN;i++)
   {
      origNode->record.pop_back();

   }

   newNode->nextLeaf = current->nextLeaf;
   origNode->nextLeaf = newNode; 
   newNode->rightSibling = origNode->rightSibling;
   newNode->leftSibling = origNode;
   origNode->rightSibling = newNode;
   

   current->parent->nextNode.push_back(newNode);

   sortChildren(current->parent);

      // push the key to parent
   current->parent->keys.push_back(newNode->record[0].first);

   sortKeys(current->parent);

   if(current->parent->keys.size() > numKeys)
   {
      
      insertRecurse(current->parent,key,val);

      return;
   }
   else
   {
      newNode->parent = current->parent;
      origNode->parent = current->parent;

   }

  }
  else
  {
   //interior nodes splitting
      firstN = ceil((numKeys + 2)/2);
      remN = floor((numKeys + 2)/2);
       if(current->nextNode.size() % 2 != 0){
            firstN = ceil(1.0*(numKeys + 2)/2);
            remN = floor(1.0*(numKeys + 2)/2);
         }

         newParOrig = current;
        newParOrig->isLeaf = false;
         newParOrig->isInterior = true;
      for(int i =0; i < current->nextNode.size();i++)
      {
         if(i>=firstN)
         {
            newParNew->nextNode.push_back(current->nextNode[i]);
         }
      }
      for(int i =0; i < remN;i++)
      {

         newParOrig->nextNode.pop_back();
      }

      
      adjustSiblings(newParOrig);
      adjustSiblings(newParNew);
      newParNew->rightSibling = newParOrig->rightSibling;
      newParNew->leftSibling =newParOrig;
      newParOrig->rightSibling = newParNew;
         


      firstN = ceil((numKeys)/2);
      remN = floor((numKeys)/2);

       if(current->keys.size() % 2 != 0){
            firstN = ceil(1.0*(numKeys)/2);
            remN = floor(1.0*(numKeys)/2);
         }
     
      vector <int> copy = current->keys;
         for(int i =0; i < remN;i++)
      {
         newParNew->keys.push_back(copy.back());
         copy.pop_back();

      }


      int  temp1;
      for(int i =0; i < newParNew->keys.size(); i++)
      {
         for(int j =i + 1; j < newParNew->keys.size(); j++)
         {
            if (newParNew->keys[i] > newParNew->keys[j]) 
            {

               temp1 = newParNew->keys[i];
               newParNew->keys[i] = newParNew->keys[j];
               newParNew->keys[j] = temp1;
            }
         } 
      } 




      for(int i =0; i <= firstN;i++)
      {
            newParOrig->keys.pop_back();

         
      }

      
      middleKey = copy.back();

      if(current->isRoot)
      {
         
         newParOrig->isRoot = false;
      
         newRoot->keys.push_back(middleKey);
         newRoot->nextNode.push_back(newParOrig);
         newRoot->nextNode.push_back(newParNew);
           root = newRoot;

         root->isRoot = true;

         newParNew->parent = root;
         newParOrig->parent = root;
         
         
         newParOrig->rightSibling = newParNew;
         newParNew->leftSibling = newParOrig;
         newParNew->rightSibling = NULL;
         newParOrig->leftSibling = NULL;
         
         return;

      }


      else
      {



      newParOrig->isRoot = false;
      
      current->parent->nextNode.push_back(newParNew);
   
      sortChildren(current->parent);

         current->parent->keys.push_back(middleKey);

         sortKeys(current->parent);


         if(current->parent->keys.size() > numKeys)
         {

            
            insertRecurse(current->parent,key,val);

            
         }
         else
         {
            newParNew->parent = current->parent;
            newParOrig->parent = current->parent;

         }
       
      return;
      }


  }


   
}



void BPlusTree::printValues()
{
   BPTreeNode* current;
   current = root;
   while(!current->isLeaf)
   {

      current = current->nextNode[0];

   }
   while(true)
   {
      for(int i = 0; i < current->record.size(); i++)
      {
         
            cout<<*current->record[i].second<<endl;
         
      }
      if(current->nextLeaf == NULL)
      {
         break;
      }
      else
      {
         current = current->nextLeaf;
      }
      
   }

}






bool BPlusTree::remove(int key)
{

   int minKeys = floor((numKeys+1)*1.0/2);
   int minPtrs = ceil((numKeys+1)*1.0/2);
   BPTreeNode *current = root;
   int keyIndex = 0;
   int parIndex = 0;
   bool found = false;

   
   while(current->isLeaf == false)
   {
      current = getnextNode(current,key);

   }
   
   
   for(int i =0; i < current->parent->nextNode.size(); i++)
   {
      for(int j = 0; j < current->parent->nextNode[i]->record.size();j++)
         {
            
            if(key == current->parent->nextNode[i]->record[j].first)
            {
               
               keyIndex = i;
               break;
            }
            
            
         }

   }





   // erase key
   for(int i = 0; i < current->record.size();i++)
   {
      if(key == current->record[i].first)
      {
         
         current->record.erase( current->record.begin() + i); 
         found = true;
         break;
      }
      
      
   }
   
   if(found == false)
   {
      // key not found
      return false;
   }
   if(current->isLeaf && current->isRoot)
   {
      
      if(current->record.size() == 0 )
      {
         current = new BPTreeNode();
         isEmpty = true;
      }
      return true;
      
   }
   
  
   //1. Redistribute values from the left sibling
      // 2. Redistribute values from the right sibling
      // 3. Coalesce with the left sibling
      // 4. Coalesce with the right sibling
   if((current->record.size() >= minKeys))
   {
      return true;
   }
   else
   {
   // check left sibling
      if(current->leftSibling != NULL && current->leftSibling->record.size() > minKeys)
      {
            //redistribute
         // take value from left 
         current->record.push_back(current->leftSibling->record.back());

         sortKeys(current);
         // change parent value
      
         if(keyIndex == 0 || keyIndex == 1)
         {
            current->parent->keys.erase(current->parent->keys.begin());
         }
         else
         {
            current->parent->keys.erase(current->parent->keys.begin() + (keyIndex-1));
         }

         current->parent->keys.push_back(current->record[0].first);

         sortKeys(current->parent);
         
         current->leftSibling->record.pop_back();
         return true;



      }
      
      //check right
      else if(current->rightSibling != NULL && current->rightSibling->record.size() > minKeys)
      {
         //redistribute

         // take value from right
         current->record.push_back(current->rightSibling->record.front());
         sortKeys(current);
         // change parent value
         current->parent->keys.erase(current->parent->keys.begin() + keyIndex);
         current->rightSibling->record.erase(current->rightSibling->record.begin());
         current->parent->keys.push_back(current->rightSibling->record.front().first);
         sortKeys(current->parent);
         return true;

      }
      
      //coalesce from left sibling
      else if(current->leftSibling != NULL)
      {
         for(int i = 0; i < current->record.size(); i++)
         {
            if(key == current->record[i].first)
            {
               current->record.erase( current->record.begin() + i); 
            }
            else
            {
               current->leftSibling->record.push_back(current->record[i]);
               current->record.erase(current->record.begin() + i);
            }

         }
         sortKeys(current->leftSibling);
         // delete leaf and parent entry/pointer
         if(keyIndex == 0 || keyIndex == 1)
         {
            current->parent->keys.erase(current->parent->keys.begin()+0);
         }
         else
         {
            current->parent->keys.erase(current->parent->keys.begin() + (keyIndex - 1));
         }
         current->parent->nextNode.erase(current->parent->nextNode.begin() + keyIndex);
         
         adjustSiblings(current->parent);
         adjustnextLeaf();
         
         if(current->parent->nextNode.size() < minPtrs)
         {

            if(current->parent->isRoot) //root is empty
            {
               root = current->leftSibling;
               root->isRoot = true;
               root->isLeaf = true;
            }
            else
            {
               removeRecurse(current->parent);
               adjustnextLeaf();
            }
            // delete current;
            current = NULL;
            return true;

         }
          // delete current;
          current = NULL;
         return true;


      }
      else if(current->rightSibling != NULL)
      {
            //coalesce from right sibling
         for(int i = 0; i < current->record.size(); i++)
         {
            if(key == current->record[i].first)
            {
               current->record.erase( current->record.begin() + i); 
            }
            else
            {
               current->rightSibling->record.push_back(current->record[i]);
               current->record.erase(current->record.begin() + i);
            }

         }

         sortKeys(current->rightSibling);
         
         // delete leaf and parent entry/pointer
         current->parent->keys.erase(current->parent->keys.begin() + keyIndex);
         current->parent->nextNode.erase(current->parent->nextNode.begin() + keyIndex);
         adjustSiblings(current->parent);
         adjustnextLeaf();
         
         if(current->parent->nextNode.size() < minPtrs)
         {
            if(current->parent->isRoot) //root is empty
            {
               root = current->rightSibling;
               root->isRoot = true;
               root->isLeaf = true;
            }
            else
            {
               removeRecurse(current->parent);
               adjustnextLeaf();
            }
            // delete current;
            current = NULL;
               return true;



         }
         // delete current;
         current = NULL;
         return true;

      }

   }
   return false;
}

bool BPlusTree::removeRecurse(BPTreeNode *current)
{
   int minKeys = floor((numKeys+1)*1.0/2);
   int minPtrs = ceil((numKeys+1)*1.0/2);
   int parIndex = 0;

   for(int i =0 ; i < current->parent->nextNode.size(); i++)
   {

      if(current->parent->nextNode[i]->nextNode.size() < minPtrs)
      {
         parIndex = i;
         
      }
   } 
   //1. Redistribute values from the left sibling
   // 2. Redistribute values from the right sibling
   // 3. Coalesce with the left sibling
   // 4. Coalesce with the right sibling

   if(current->leftSibling != NULL && current->leftSibling->nextNode.size() > minPtrs)
   {
      if(parIndex == 0 || parIndex == 1)
      {
         current->keys.push_back(current->parent->keys[0] );
         current->parent->keys[0] = current->leftSibling->keys.back();
      }
      else
      {

         current->keys.push_back(current->parent->keys[(parIndex-1)] );
         current->parent->keys[(parIndex-1)] = current->leftSibling->keys.back();
      }
         
      current->nextNode.push_back(current->leftSibling->nextNode.back());

      //sort

      sortChildren(current);
      sortKeys(current);
      current->leftSibling->keys.pop_back();
      current->leftSibling->nextNode.pop_back();
      current->leftSibling->nextNode.back()->rightSibling= NULL;
      adjustSiblings(current->parent);
      adjustSiblings(current->leftSibling);
      adjustSiblings(current);
      return true;


   }
   else if(current->rightSibling != NULL && current->rightSibling->nextNode.size() > minPtrs)
   {
      current->keys.push_back(current->parent->keys[parIndex] );
      current->parent->keys[parIndex] = current->rightSibling->keys[0];
      current->nextNode.push_back(current->rightSibling->nextNode[0]);
      current->rightSibling->keys.erase(current->rightSibling->keys.begin() + 0);
      current->rightSibling->nextNode.erase(current->rightSibling->nextNode.begin() + 0);
      adjustSiblings(current->parent);
      adjustSiblings(current->rightSibling);
      adjustSiblings(current);
      return true;

   }

   else if (current->leftSibling != NULL)
   {
      if(parIndex == 0 || parIndex== 1)
      {
         current->keys.push_back(current->parent->keys[0]);
         current->parent->keys.erase(current->parent->keys.begin()+0);
      }
      else
      {
         
         current->keys.push_back(current->parent->keys[(parIndex-1)]);
         current->parent->keys.erase(current->parent->keys.begin() + (parIndex - 1));
      }
      for(int i = 0; i < current->keys.size(); i++)
      {
         current->leftSibling->keys.push_back(current->keys[i]);

      }

      for(int i = 0; i < current->nextNode.size(); i++)
      {
         current->leftSibling->nextNode.push_back(current->nextNode[i]);

      }

      sortChildren(current->leftSibling);
      sortKeys(current->leftSibling);
      
      current->parent->nextNode.erase(current->parent->nextNode.begin() + parIndex);
      
      adjustSiblings(current->leftSibling);
      adjustSiblings(current->parent);
      
      if(current->parent->nextNode.size() < minPtrs)
      {
         if(current->parent->isRoot) //root is empty
         {
            root = current->leftSibling;
            root->isRoot = true;
           
         }
         else
         {
            removeRecurse(current->parent);
         }

            // delete current;
            current = NULL;
            return true;



      }
      // delete current;
      current = NULL;
      return true;

   }

   else if(current->rightSibling != NULL)
   {
      current->keys.push_back(current->parent->keys[parIndex]);
      for(int i = 0; i < current->keys.size(); i++)
      {
         current->rightSibling->keys.push_back(current->keys[i]);

      }

      for(int i = 0; i < current->nextNode.size(); i++)
      {
         current->rightSibling->nextNode.push_back(current->nextNode[i]);

      }

      sortChildren(current->rightSibling);
      sortKeys(current->rightSibling);

      // delete leaf and parent entry/pointer
      current->parent->keys.erase(current->parent->keys.begin() + parIndex);
      current->parent->nextNode.erase(current->parent->nextNode.begin() + parIndex);
      
      adjustSiblings(current->rightSibling);
      adjustSiblings(current->parent);
     
      if(current->parent->nextNode.size() < minPtrs )
      {
         if(current->parent->isRoot) //root is empty
         {
            root = current->rightSibling;
            root->isRoot = true;
         }
         else
         {
            removeRecurse(current->parent);
         }
            // delete current;
            current = NULL;
            return true;



      }
      
      // delete current;
      current = NULL;
      return true;

   }

   return true;


}


 void BPlusTree::adjustnextLeaf()
 {
   vector <BPTreeNode*> child;
   child = getLeaves(root,child);
   for(int i =0; i < child.size();i++)
   {
      if(i < child.size()-1)
      {
         child[i]->nextLeaf = child[i+1];
      }
      else if(i == child.size()-1)
      {
         child[i]->nextLeaf = NULL;
      }
   }

 }  
   


void BPlusTree:: adjustSiblings(BPTreeNode *current)
{
         for(int i =0; i < current->nextNode.size();i++)
      {
         current->nextNode[i]->parent = current;
         if(i == 0 && current->nextNode.size() > 1) 
         {
            current->nextNode[i]->leftSibling = NULL;
            current->nextNode[i]->rightSibling = current->nextNode[i + 1];

         }
         else if(i == 0 && current->nextNode.size() == 1)
         {
            current->nextNode[i]->leftSibling = NULL;
            current->nextNode[i]->rightSibling = NULL;

         }
         else if( i > 0 && i < current->nextNode.size()-1)
         {

            current->nextNode[i]->leftSibling = current->nextNode[i - 1];
           current->nextNode[i]->rightSibling = current->nextNode[i + 1];

         }
         else if( i == current->nextNode.size() - 1)
         {
            current->nextNode[i]->leftSibling = current->nextNode[i - 1];
            current->nextNode[i]->rightSibling = NULL;
         }
      }
}


void BPlusTree::sortChildren(BPTreeNode  *current)
{
   BPTreeNode *temp;
      for(int i =0; i < current->nextNode.size(); i++)
      {
         current->nextNode[i]->parent = current;
         for(int j =i + 1; j < current->nextNode.size(); j++)
         {

            if(!current->nextNode[i]->isLeaf)
            {
               if (current->nextNode[i]->keys[0] > current->nextNode[j]->keys[0]) 
               {

                  temp = current->nextNode[i];
                  current->nextNode[i] = current->nextNode[j];
                  current->nextNode[j] = temp;
               }
            }
            else
            {
               if (current->nextNode[i]->record[0].first > current->nextNode[j]->record[0].first) 
               {

                  temp = current->nextNode[i];
                  current->nextNode[i] = current->nextNode[j];
                  current->nextNode[j] = temp;
               }
            }




         } 
      }




}


void BPlusTree::sortKeys(BPTreeNode *current)
{

   int temp;
   if(!current->isLeaf)
   {
      for(int i =0; i < current->keys.size(); i++)
      {
         for(int j =i + 1; j <current->keys.size(); j++)
         {
         
               if (current->keys[i] > current->keys[j]) 
               {
                  temp = current->keys[i];
                  current->keys[i] = current->keys[j];
                  current->keys[j] = temp;
               }

         } 
      }
   }
   else
   {

      pair<int,string*>  temp2;
      for(int i =0; i < current->record.size(); i++)
      {
         for(int j =i + 1; j <current->record.size(); j++)
         {
         
               if (current->record[i].first > current->record[j].first) 
               {
                  temp2 = current->record[i];
                  current->record[i] = current->record[j];
                  current->record[j] = temp2;
               }

         } 
      }

   }


}




void BPlusTree::print(BPTreeNode *node,vector <BPTreeNode*> children)
{
   if(node->isLeaf && node->isRoot)
   {
      if(node->record.size() > 0)
      {
         cout<<"[";
         for(int i = 0; i < node->record.size(); i++)
         {

            if(i == 0)
            {
               cout <<node->record[i].first;
            }
            else
            {
               cout <<","<<node->record[i].first;
            }
            
         }
         cout<<"]"<<endl;
      }
   }
      
   else if(node->isRoot)
   {
      
      if(node->keys.size() > 0)
      {
         cout << "[";
         for(int i = 0; i < node->keys.size(); i++)
         {
            if(i==0)
            {
               cout << node->keys[i];
            }
            else{
               cout << ","<<node->keys[i];
            }

         }
         cout << "]"<<endl;
      }

      if(node->nextNode.size() > 0)
      {
         for(int i = 0; i < node->nextNode.size(); i++)
         {

            children.push_back(node->nextNode[i]);
         }
         node = children[0];
         print(node,children);

      }

      return;

      
      
      
   }

   else if(node->isInterior)
   {
      
      if(node->keys.size() > 0)
      {
         cout << "[";
         for(int i = 0; i < node->keys.size(); i++)
         {
            if(i==0)
            {
               cout << node->keys[i];
            }
            else{
               cout << ","<<node->keys[i];
            }

         }
         cout << "]";
      }
         if(node->nextNode.size() > 0)
      {
         for(int i = 0; i < node->nextNode.size(); i++)
         {

            children.push_back(node->nextNode[i]);
         }
         
         if(node->rightSibling == NULL)
         {
            if(children[1]->isLeaf)
            {
               if(node->keys.back() >  children[1]->record[0].first)
               {
            
                     cout<<""<<endl;
               }
            }
            else
            {
               if(node->keys.back() >  children[1]->keys[0])

                  cout<<""<<endl;
            }
         }
         
         children.erase(children.begin() + 0);
         node = children[0];
         print(node,children);

      }

      return;
      
      

      
   }

   else if(node->isLeaf)
   {
   
      printLeaves(node);
      return;

   }
return;
}


void BPlusTree::printLeaves(BPTreeNode *current)
{
   while(true)
   {
      if(current->record.size() > 0)
      {
         cout <<"[";
         for(int i = 0; i < current->record.size();i++)
         {
            if(i == 0)
            {
               cout <<current->record[i].first;
            }
            else
            {
               cout <<","<<current->record[i].first;
            }
         }
         cout << "]";
      }
      if(current->nextLeaf == NULL)
      {
         cout<<""<<endl;
         return;
      }
      current = current->nextLeaf;
   }

}
   
   



vector <BPTreeNode*>  BPlusTree::getLeaves(BPTreeNode *node,vector <BPTreeNode*> children)
{
   vector <BPTreeNode*> child;

   if(node->isLeaf && node->isRoot)
   {
      return children;
   }
   
   else if(node->isRoot)
   {
      if(node->nextNode.size() > 0)
      {
         for(int i = 0; i < node->nextNode.size(); i++)
         {

            children.push_back(node->nextNode[i]);
         }
         node = children[0];
         return getLeaves(node,children);

      }
   }

   else if(node->isInterior)
   {
         if(node->nextNode.size() > 0)
      {
         for(int i = 0; i < node->nextNode.size(); i++)
         {

            children.push_back(node->nextNode[i]);
         }
         children.erase(children.begin() + 0);
         node = children[0];
         return getLeaves(node,children);

      }
      
   }

   else if(node->isLeaf)
   {
      
      return children;

   }
return children;
}














