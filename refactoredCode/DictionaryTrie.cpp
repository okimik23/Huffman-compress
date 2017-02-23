/****************************************************************************

                                                Kimiko Yamamoto
                                                CSE 100, Winter Quarter
                                                2/9/17
                                                A13208241
                              Assignment 2

File Name:      DictionaryTrie.cpp
Description:    DictionaryTrie creates a dictionary using a ternary search trie.
                It has functions to insert a new word or to find a word.
                The function predictCompletions can find the most frequent words
                in the dictionary trie that start with a certain prefix.

****************************************************************************/


#include "util.h"
#include "DictionaryTrie.h"
#include <queue>
#include <algorithm>
#include <string>
#include <set>
#include <cstdlib>
#include <iostream>

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){
	root = NULL;
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */

bool DictionaryTrie::insert(std::string word, unsigned int freq) 
{

  unsigned int index = 0;
  bool already_there = false;

  //check if empty string
  if( word.length() == 0 ) {
    return false;
  }
  //already in tree
  if( find(word) ) {
    already_there = true;
  }

  //no root
  if( !root ) {
    root = new TSTNode(word[index]);
  }
  
  root = insert_help( root, word, index, already_there, freq );

  if( already_there ) {
    return false;
  }

  return true;

}

/* helper function for insert */
TSTNode* DictionaryTrie::insert_help( TSTNode* r, std::string word, unsigned int index, bool already_there, int freq ) {

  if( !r ) {
    if( already_there ) {
      return r;
    }
    r = new TSTNode(word[index]);
  }

  if( word[index] < r->letter ) {
    r->left = insert_help( r->left, word, index, already_there, freq);
  }
  else if( word[index] > r->letter ) {
    r->right = insert_help( r->right, word, index, already_there, freq );
  }
  else {
    if( index < word.length()-1 ) {
      r->middle = insert_help( r->middle, word, index+1, already_there, freq );
    }
    else {
      r->finish = true;
      r->frequency = freq;
      r->s_word = word;
    }
  }
  return r;
}

TSTNode* DictionaryTrie::find_help(TSTNode* curr, std::string word, unsigned int index ) const{
  if( !curr ) {
    return NULL;
  }
  if( curr->letter > word[index] ) {
    return find_help(curr->left, word, index);
  }
  if( curr->letter < word[index] ) {
    return find_help(curr->right, word, index);
  }
  if( index < word.length()-1 ) {
    return find_help(curr->middle, word, index+1);
  }
  return curr;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
 //check if tree exists
  if( !root ) {
    return false;
  } 
  unsigned int index = 0;
  TSTNode* curr = find_help(root, word, index);

  return curr && curr->finish;
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
  std::queue<TSTNode*> q;

  //empty prefix returns empty string
  if( prefix == "" ) {
    return words;
  }
  
  if( num_completions <= 0 ) {
    return words;
  }

  //check if tree exists
  if( !root ) {
    return words;
  }

  //look for prefix in the tree, same as find
  unsigned int index = 0;
  TSTNode* curr = root;

  curr = find_help(root, prefix, index);

  //prefix not in dictionary
  if( curr->letter != prefix[index] ) {
    std::cout << "Invalid Input. Please retry with correct input" 
      << std::endl;
    return words;
  }

  //start BFS
  q.push(curr);
  TSTNode* nodes[num_completions];
  for(unsigned int i=0; i < num_completions; i++ ) {
    nodes[i] = 0;
  }
  TSTNode* temp;
  TSTNode* original;
  bool first = true;
  // fill in queue
  while( !q.empty() ) {
    curr = q.front();
    q.pop();
    
    //visit node
    if( curr->finish ) { 
      temp = curr;
      original = curr;
      for(unsigned int i=0; i < num_completions; ++i)
      {
        if( nodes[i] == 0 ) {
	  nodes[i] = curr;
          break;
        }

        else if( nodes[i]->frequency < curr->frequency ) {
  	  temp = nodes[i];
          nodes[i] = curr;
          curr = temp;
        }
      }
        curr = original;
      }
    
    //add nodes to queue
    if( curr->middle != NULL ) {
      q.push(curr->middle);
    }
    if( !first ) {
      if( curr->left != NULL ) {
        q.push(curr->left);
      }
    
      if( curr->right != NULL ) {
        q.push(curr->right);
      }
    }
    first = false;

  }

  for(unsigned int j = 0; j < num_completions; ++j ) {
    if( nodes[j] != 0 ) {
      words.push_back(nodes[j]->s_word);
    }
  }

  return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){
	deleteAll(root);
}

void DictionaryTrie::deleteAll(TSTNode* n) {

  if( !n) {
    return;
  }
  
  if( n->left ) {
    deleteAll(n->left);
  }
  if( n->right) {
    deleteAll(n->right);
  }
  if( n->middle ) { 
   deleteAll(n->middle);
  }
 
  delete n;
}


