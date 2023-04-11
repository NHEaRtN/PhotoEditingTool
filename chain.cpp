#include "chain.h"
#include <cmath>
#include <iostream>


// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
  
  clear();
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The  data to be inserted.
 */
Chain::Node * Chain::insertAfter(Node * p, const Block &ndata) {

  Node* newNode = new Node(ndata);

  if(p == NULL) {

    if(head_ == NULL) {
    //  newNode->next = head_;
     head_ = newNode;
    
    }

   else {
      //Node* temp = head_;
      newNode->next = head_; 
      head_->prev = newNode;
      newNode->prev = NULL;
      head_ = newNode;

    }
  }
  else  {

    if(p->next != NULL) {

  Node* nodeNext = p->next;
  newNode->prev = p;
  newNode->next = nodeNext;
  p->next = newNode;
  nodeNext->prev = newNode;
  

    }

    else {
      
  // Node* nodeNext = p->next;
  newNode->prev = p;
  // newNode->next = nodeNext;
  p->next = newNode;
  newNode->next = NULL;
    }


    }
    length_++;

  return newNode;
}

/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::swap(Node *p, Node *q) {
    if(p == NULL || q == NULL || p == q) {
      return;
    }

    if(p->next == q) {
      Node* pPrev = p->prev;
      Node* qNext = q->next;
      q->prev = pPrev;
      p->prev = q;
      p->next = qNext;
      q->next = p;
      
    }
    else if(q->next == p) {
      Node* qPrev = q->prev;
      Node* pNext = p->next;
      
      q->prev = p;
      q->next = pNext;
      p->prev = qPrev;
      p->next = q; 

      
    //}
  }
   else { 

    // Node* qPrev = p->prev;
    // Node* qNext = p->next;
    Node* pPrev = q->prev;
    Node* pNext = q->next;
  

    q->prev = p->prev;
    q->next = p->next;
    p->prev = pPrev;
    p->next = pNext;

  
    // 11/14
    // Node* qPrev = q->prev;
    // Node* qNext = q->next;
    // Node* pPrev = p->prev;
    // Node* pNext = p->next;
  
  
    // q->prev = pPrev;
    // q->next = pNext;
    // p->prev = qPrev;
    // p->next = qNext;

    // 13/14
    // Node* qPrev = p->prev;
    // Node* qNext = p->next;
    // Node* pPrev = q->prev;
    // Node* pNext = q->next;
  
  
    // q->prev = pPrev;
    // q->next = pNext;
    // p->prev = qPrev;
    // p->next = qNext;
   

  
  }

   if(p->prev != NULL) {
    p->prev->next = p;
    }
    if(p->next != NULL) {
    p->next->prev = p;
    }
     if(q->prev != NULL) {
    q->prev->next = q;
    }
 

    if(q->next != NULL) {
    q->next->prev = q;
    }
  
  
   if(p->prev == NULL) {
    head_ = p;
   
  } else if(q->prev == NULL) {
    head_ = q;

  }
}





/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
void Chain::clear() {
  
  Node* temp;
  Node* nextNode = head_;

  while(nextNode != NULL) {

    temp = nextNode->next; 
    delete nextNode;
    nextNode = temp;
    
  }
    head_ = NULL;

  length_ = 0;
  // delete head_;
  }
  


/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other) {
clear();
Node* otherHead = other.head_;
// head_ = NULL;
Node* curr = head_;

if(otherHead == NULL) {
  return;
}
while(otherHead != NULL) { 
   curr = insertAfter(curr,otherHead->data);
  otherHead = otherHead->next;
 }

}

   






/* Modifies the current chain:
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this block
 *	is big for all other blocks.

 *	For each block B, find the distanceTo B from every other block
 *	and take the minimum of these distances as B's "value".
 *	Choose the block B with the maximum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::unscramble() {

Node* blockB;
double maxMinDistanceAccumulator = 0;
Node* unMutatedHead = head_;

// Find block B
if(head_ == NULL) {
  return;
}
for(Node* curr = head_; curr != NULL; curr = curr->next) {
  Node* curr2 = unMutatedHead;     // we always want to start the comparison on the unmutated head
  double minimumDistance = 66666; // keeps track of the minimum distance for one block, updates everytime we switch the "comparitent"
  
  while(curr2 != NULL) {
      if(curr2 != curr) {     // because we always start at the head, we want to make sure that our "comparitent" does get compared
      double dist = curr2->data.distanceTo(curr->data); // to itself
      if(dist < minimumDistance) {
        minimumDistance = dist;
      }
      }
      curr2 = curr2->next;
  }
  if(minimumDistance > maxMinDistanceAccumulator) {
    maxMinDistanceAccumulator = minimumDistance;
    blockB = curr;
  }
  }
  swap(head_,blockB);

for(Node* curr = head_; curr->next != NULL; curr = curr->next) {
  Node* curr2 = curr->next; 
  double MinDistAcc = 66666;
  Node* currentMin = NULL;
  while(curr2 != NULL) {
      double distance = head_->data.distanceTo(curr2->data);
      if(distance < MinDistAcc) {
        MinDistAcc = distance;
        currentMin = curr2;
      }
      curr2 = curr2->next;
  }
  swap(curr->next,currentMin);
}
}






