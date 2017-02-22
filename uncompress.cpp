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

  int value;
  int total;
  int f; //frequency
  int count; //num of freq elements
  ifs >> count;
  vector<int> freqs = vector<int>(256, 0);

  //read file header 
  for( int i=0; i < count; i++) {
    ifs >> value;
    if( ifs.eof() ) break;
    ifs >> f;
    if( ifs.eof() ) break;
    freqs[value] = f;
    total += f;
  }
  
  //reconstruct Huffman coding tree
  HCTree tree;
  tree.build(freqs);

  //open output file for writing
  ofstream ofs;
  ofs.open(argv[2], ios::binary);
  if( ofs.fail() ) {
    cout << "Error: Output file failed to open" << endl;
    return -1;
  }

  ifs.get();  //gets rid of newline from header
  BitInputStream in(ifs);
  //decode
  char sym;

  for( int i=0; i < total; ++i) {
    sym = tree.decode( in );
    ofs << sym;
  }

  ifs.close();
  ofs.close();

  return 0;
}
