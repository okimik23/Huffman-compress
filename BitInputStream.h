/***************************************************************************

                                                Kimiko Yamamoto
                                                CSE 100, Winter 2017
                                                2/15/17
                                                
                              Assignment 3

File Name:      BitInputStream.h
Description:    This header file allows the file to be read into a buffer
                as bits.

***************************************************************************/

#ifndef BITINPUTSTREAM_H
#define BITINPUTSTREAM_H

#include <iostream>

using namespace std;

class BitInputStream {

private:
  char buf;	  // one byte buffer of bits
  int nbits;	  // how many bits have been read from buf
  istream & in;   // the input stream to use

public:

  /** Initialize a BitinputStream that will use
    * the given istream for input.
    */
  BitInputStream(std::istream & is) : in(is) {
    buf = 0;  //clear buffer
    nbits = 8;   //initialize bit index
  }

  /** Fill the buffer from the input */
  void fill();

  /** Read the next bit from the bit buffer.
    * Fill the buffer from the input stream first if needed.
    * Return 1 if the bit read is 1.
    * Return 0 if the bit read is 0.
    */
  int readBit();

};


#endif //BITINPUTSTREAM_H
