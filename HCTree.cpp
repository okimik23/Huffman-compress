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
#include <utility>

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
  
  if( pq.size() == 0 ) {
    return;
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

void HCTree::encode(byte symbol, BitOutputStream& out) const {

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
//reverse(bits.begin(), bits.end()); //saves bits forward 
  //write bits to BitOutputStream
  while( !bits.empty() ) {
    out.writeBit(bits.back());
    bits.pop_back();
  }

}

int HCTree::decode(BitInputStream& in) const {

  HCNode* curr = root;
  int bit;
  
  //go down the tree
  while( curr->c0 || curr->c1 ) {
    //read bits from BitInputStream
    bit = in.readBit();

    //right node
    if( bit == 1 ) {
      curr = curr->c1;
    }
    //left node
    else if( bit == 0 ) {
      curr = curr->c0;
    }

  }
  
  return curr->symbol;
}


/** Function to write tree in the header using a 
  * preorder traversal
  */
void HCTree::write_tree(HCNode* curr, BitOutputStream& out){
  
  //curr is a leaf
  if( (curr->c0 == 0) && (curr->c1)) {
    out.writeBit(1);
    
    for( int i=0; i < 8; i++) {
      out.writeBit(((1 << (7-i)) & curr->symbol) >> (7-i));
    }
    
    return;
  }
  //curr is not an ascii node
  else {
    out.writeBit(0);
  }

}

/** Function to construct tree from the header
  * using preorder traversal
  */
void HCTree::construct_tree(HCNode* curr, int child, BitInputStream& in){

  int bit = in.readBit();

  //leaf node
  if( bit == 1) {
    //make node
    unsigned int sym = 0;
    for( int i=7; i >0; i--) {
      sym += in.readBit() << i;
    }

    HCNode* new_node = new HCNode(0, (char)sym);
    leaves[sym] = new_node;

    //connect new_node to trie
    new_node->p = curr;
    if( curr > new_node ) {  //change to curr > new_node?
      curr->c0 = new_node;
    }
    else{
      curr->c1 = new_node;
    }
  }
  //not a leaf
  else {
    HCNode* notaleaf = new HCNode(0,0);
    
    notaleaf->p = curr;
    if( curr > notaleaf ) {  //same as above?
      curr->c0 = notaleaf;
    }
    else{
      curr->c1 = notaleaf;
    }

    construct_tree(notaleaf, 0, in);  //left node
    construct_tree(notaleaf, 1, in);  //right node
  }
 
}

HCNode* HCTree::get_root() {
  return root;
}

void HCTree::set_root() {
  root = new HCNode(0,0);
}

