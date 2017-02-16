/***************************************************************************

                                                Kimiko Yamamoto
                                                CSE 100, Winter 2017
                                                2/15/17
                                                
                              Assignment 3

File Name:      uncompress.cpp
Description:    This program opens a file to read. The contents of this file
                recreate the Huffman tree which is then decoded.  The 
                decoded contents are written to an output file.

***************************************************************************/

#include "HCNode.h"
#include "HCTree.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{

  //open file to read
  ifstream ifs;
  ifs.open(argv[1]);
  if( ifs.fail() ) {
    cout << "Error: Input file failed to open" << endl;
    return -1;
  }

  int value;
  int total;
  vector<int> freqs = vector<int>(256, 0);

  //read file header 
  for( int i=0; i < freqs.size(); ++i ) {
    ifs >> value;
    if( ifs.eof() ) break;
    freqs[i] = value;
    total += value;
  }
  
  //reconstruct Huffman coding tree
  HCTree tree;
  tree.build(freqs);

  //open output file for writing
  ofstream ofs;
  ofs.open(argv[2]);
  if( ofs.fail() ) {
    cout << "Error: Output file failed to open" << endl;
    return -1;
  }

  //decode
  char sym;
  for( int i=0; i < total; ++i) {
    sym = tree.decode( ifs );
    ofs << sym;
  }

  ifs.close();
  ofs.close();

  return 0;
}
