/***************************************************************************

                                                Kimiko Yamamoto
                                                CSE 100, Winter 2017
                                                2/15/17
                                                
                              Assignment 3

File Name:      HCTree.h
Description:    This header file creates the Huffman Tree object.  It also
                defines the functions necessary to build, encode, and decode 
                the tree.

***************************************************************************/

#ifndef HCTREE_H
#define HCTREE_H

#include <queue>
#include <vector>
#include <fstream>
#include "HCNode.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"

using namespace std;

/** A 'function class' for use as the Compare class in a
 *  priority_queue<HCNode*>.
 *  For this to work, operator< must be defined to
 *  do the right thing on HCNodes.
 */
class HCNodePtrComp {
public:
    bool operator()(HCNode*& lhs, HCNode*& rhs) const {
        return *lhs < *rhs;
    }
};

/** A Huffman Code Tree class.
 *  Not very generic:  Use only if alphabet consists
 *  of unsigned chars.
 */
class HCTree {
private:
    HCNode* root;
    vector<HCNode*> leaves;

    /* This is a helper for the destructor */
    static void deleteAll(HCNode* n);

public:
    // explicit keyword is used to avoid accidental implicit conversions
    explicit HCTree() : root(0) {
        leaves = vector<HCNode*>(256, (HCNode*) 0);
    }

    ~HCTree();
 
    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void build(const vector<int>& freqs);

    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void encode(byte symbol, BitOutputStream& out) const;

    /** Write to the given ofstream
     *  the sequence of bits (as ASCII) coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
     *  BE USED IN THE FINAL SUBMISSION.
     */
    void encode(byte symbol, ofstream& out) const;


    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    int decode(BitInputStream& in) const;

    /** Return the symbol coded in the next sequence of bits (represented as 
     *  ASCII text) from the ifstream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
     *  IN THE FINAL SUBMISSION.
     */
    int decode(ifstream& in) const;

    /** Function to write tree in the header using a 
      * preorder traversal
      */
    void write_tree(HCNode* curr, BitOutputStream& out);

    /** Function to construct tree from the header
      * using preorder traversal
      */
    void construct_tree(HCNode* curr, int child, BitInputStream& in);

    HCNode* get_root();

    void set_root();
    

};

#endif // HCTREE_H
