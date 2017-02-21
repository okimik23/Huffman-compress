/***************************************************************************

                                                Kimiko Yamamoto
                                                CSE 100, Winter 2017
                                                2/15/17
                                                
                              Assignment 3

File Name:      compress.cpp
Description:    This program opens a file to read. The contents of this file
                are made into a Huffman tree which is then encoded.  The 
                encoded contents are written to an output file.

***************************************************************************/


#include "HCNode.h"
#include "HCTree.h"
#include "BitOutputStream.h"
#include "BitInputStream.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) 
{
  
  //open file to read
  ifstream ifs;
  ifs.open(argv[1], ios::binary);
  if( ifs.fail() ) {
    cout << "Error: Input file failed to open" << endl;
    return -1;
  }

  char value;
  vector<int> freq = vector<int>(256, 0);

  //count number of occurrences of each byte value
  while( ifs.get(value) ) {
    if( ifs.eof() ) break;
    freq[value]++;
  }
  
  ifs.close();

  //Create Huffman tree
  HCTree tree;
  tree.build(freq);

  //open file to write
  ofstream ofs;
  ofs.open(argv[2], ios::binary);
  if( ofs.fail() ) {
    cout << "Error: Output file failed to open" << endl;
    return -1;
  }

  //"file header"
  for( int i = 0; i < freq.size(); ++i) {
    ofs << freq[i] << endl;
  }

  //open input file again
  ifs.open(argv[1]);

  BitOutputStream out(ofs);
  //encode 
  while( ifs.get(value) ) {
    if( ifs.eof() )break;
    tree.encode( value, out );
  }
  out.flush();

  ifs.close();
  ofs.close();

  return 0;
}
