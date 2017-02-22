/***************************************************************************

                                                Kimiko Yamamoto
                                                CSE 100, Winter 2017
                                                2/15/17
                                                
                              Assignment 3

File Name:      BitOutputStream.cpp
Description:    This file has functions to write the bits to the ostream.

***************************************************************************/

#include "BitOutputStream.h"
#include <iostream>

/** Send the buffer to the output, and clear it */
void BitOutputStream::flush() {
  out.put(buf);
  out.flush();
  buf = nbits = 0;
}

/** Write the least significant bit of the argument to 
  * the bit buffer, and increment the bit buffer index.
  * But flush the buffer first, if it is full.
  */
void BitOutputStream::writeBit(int i) {

  //check if buffer is full
  if( nbits == 8 ) {
    flush();
  }

  //write the least significant bit
  buf = (buf & ~(1 << (7-nbits))) | (i << (7-nbits));
  nbits++;
}

