/***************************************************************************

                                                Kimiko Yamamoto
                                                CSE 100, Winter 2017
                                                2/15/17
                                                
                              Assignment 3

File Name:      HCNode.h
Description:    This header file creates a HCNode object to create the nodes
                of the Huffman tree.  It also has an overloaded operator in 
                which to order the nodes in terms of frequency or otherwise
                break ties.

***************************************************************************/

#ifndef HCNODE_H
#define HCNODE_H

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** A class, instances of which are nodes in an HCTree.
 */
class HCNode {

public:
    int count;
    byte symbol; // byte in the file we're keeping track of
    HCNode* c0;  // pointer to '0' child
    HCNode* c1;  // pointer to '1' child
    HCNode* p;   // pointer to parent

    HCNode(int count,
      byte symbol,
      HCNode* c0 = 0,
      HCNode* c1 = 0,
      HCNode* p = 0)
        : count(count), symbol(symbol), c0(c0), c1(c1), p(p) { }

    /** Less-than comparison, so HCNodes will work in std::priority_queue
     *  We want small counts to have high priority.
     *  And we want to break ties deterministically.
     */
    bool operator<(const HCNode& other);
};

/** For printing an HCNode to an ostream
 *  Possibly useful for debugging.
 */
ostream& operator<<(ostream&, const HCNode&) __attribute__((weak)); // shut the linker up
ostream& operator<<(ostream& stm, const HCNode& n) {
    stm << "[" << n.count << "," << (int) (n.symbol) << "]";
    return stm;
}


#endif // HCNODE_H
