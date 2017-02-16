/***************************************************************************

                                                Kimiko Yamamoto
                                                CSE 100, Winter 2017
                                                2/15/17
                                                
                              Assignment 3

File Name:      HCNode.cpp
Description:    This file defines the < operator for the HCNodes. This will
                help in creating the Huffman tree and will also break ties 
                between nodes with the same frequencies.

***************************************************************************/

#include "HCNode.h"
using namespace std;

/** Less-than comparison */
bool HCNode::operator<(const HCNode& other) {
    if( count != other.count) {
      return count > other.count;
    }  

    return symbol > other.symbol;
}


