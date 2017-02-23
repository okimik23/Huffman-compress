/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 *  Student: Kimiko Yamamoto
 */

#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <vector>
#include <string>

/**
 *  The class for a node in the ternary search trie
 */ 
class TSTNode {
public: 
	TSTNode* left;
	TSTNode* middle;
	TSTNode* right;
	char letter;
	unsigned int frequency;
	bool finish;  //if it is the last char in the word
        std::string s_word;

	/** Constructor.  Initialize a TSTNode with the given 
 	 *  letter, no parent, no children.
 	 */
	TSTNode(char l) : left(0), middle(0), right(0), 
			letter(l), frequency(0), finish(false), s_word(""){};
};


/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /** Helper function for insert */
  TSTNode* insert_help( TSTNode* r, std::string word, unsigned int index, bool already_there, int freq );

  /** Helper function for find */
  TSTNode* find_help( TSTNode* curr, std::string word, unsigned int index) const;  

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

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
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();

private:

  /** Pointer to the root of this TST, or 0 if the BST is empty */
  TSTNode* root;

  /** This is a helper for the destructor */
  static void deleteAll(TSTNode* n);

};

#endif // DICTIONARY_TRIE_H
