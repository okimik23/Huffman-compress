/***************************************************************************

                                                Kimiko Yamamoto
                                                CSE 100, Winter 2017
                                                2/15/17
                                                
                              Assignment 3

File Name:      BitIntputStream.cpp
Description:    This file has functions to read the bits from the istream.

***************************************************************************/

#include "BitInputStream.h"
#include <iostream>

/** Fill the buffer from the input */
void BitInputStream::fill() {
  buf = in.get();
  nbits = 0;
}

/** Read the next bit from the bit buffer.
  * Fill the buffer from the input stream first if needed.
  * Return 1 if the bit read is 1.
  * Return 0 if the bit read is 0.
  */
int BitInputStream::readBit() {

  //check if buffer is already read
  if( nbits == 8 ) {
    fill();
  }
  //read next bit
  nbits++;
  return ((buf >> (8-nbits)) & 1);
}
