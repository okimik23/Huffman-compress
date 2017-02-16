/***************************************************************************

                                                Kimiko Yamamoto
                                                CSE 100, Winter 2017
                                                2/15/17
                                                
                              Assignment 3

File Name:      HCTree.cpp
Description:    This program helps to create the Huffman coding tree for
                input files. This includes building, encoding, and decoding
                the tree.

***************************************************************************/


#include "HCTree.h"
#include "HCNode.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;


/** Default destructor. */
HCTree::~HCTree() {
  deleteAll(root);
  
}

/** helper for destructor */
void HCTree::deleteAll(HCNode* n) {
  if( !n ) {
    return;
  }

  deleteAll(n->c0);
  deleteAll(n->c1);
  delete n;
}

/** create the tree */
void HCTree::build( const vector<int>& freqs ) {
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

  //make forest of single-node trees for nonzero count symbols
  for(int i=0; i < freqs.size(); ++i) {
    if( freqs[i] != 0 ) {
      leaves[i] = new HCNode(freqs[i], i);
      pq.push(leaves[i]);
    }
  }
  
  if( pq.size() == 1) {
    pq.push(new HCNode(0, 0));
  }

  //Build Huffman Tree
  while(pq.size() > 1) {
    HCNode* parent = new HCNode(0, 0);

    //set right node
    parent->c1 = pq.top();
    parent->c1->p = parent;
    pq.pop();
    
    //set left node
    parent->c0 = pq.top();
    parent->c0->p = parent;
    pq.pop();

    parent->count = parent->c0->count + parent->c1->count;
    parent->symbol = parent->c0->symbol;

    pq.push(parent);
  }
  
  root = pq.top();

}

void HCTree::encode(byte symbol, ofstream& out) const {

  vector<int> bits;  //saves the bits to the char backwards

  HCNode* curr = leaves[symbol];
  //work up the tree
  while( curr != root ) {
    
    //was a left node
    if( curr == curr->p->c0 ) {
      bits.push_back(0);
    }
    //was a right node
    else if( curr == curr->p->c1 ) {
      bits.push_back(1);
    }

    curr = curr->p;
  }

  reverse(bits.begin(), bits.end()); //saves bits forward 

  for( int i=0; i < bits.size(); ++i) {
    out << bits[i];
  }
}

int HCTree::decode(ifstream& in) const {

  HCNode* curr = root;
  char b;

  //go down the tree
  while( curr->c0 || curr->c1 ) {
    in.get(b);

    //right node
    if( b == '1' ) {
      curr = curr->c1;
    }
    //left node
    else if( b == '0' ) {
      curr = curr->c0;
    }

  }
  
  return curr->symbol;
}
