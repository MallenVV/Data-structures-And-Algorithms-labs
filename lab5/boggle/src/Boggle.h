// Wilhelm Malé (wilma870)
// Oscar Jansson (oscja211)

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <grid.h>
#include <unordered_set>
#include <lexicon.h>
using namespace std;

struct hash_pair {      // reference: https://www.geeksforgeeks.org/cpp/how-to-create-an-unordered_map-of-pairs-in-c/
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        // Hash the first element
        size_t hash1 = hash<T1>{}(p.first);
        // Hash the second element
        size_t hash2 = hash<T2>{}(p.second);
        // Combine the two hash values
        return hash1
               ^ (hash2 + 0x9e3779b9 + (hash1 << 6)
                  + (hash1 >> 2));
    }
};

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    constexpr static int BOARD_SIZE{4};

    // create a board to play on
    void make_board(const string& s);

    //print the board in the console in a grid
    void print_board()const;

    // check if word is >= 4 letters, not in previous guesses, in lexicon and starts search on board
    bool word_valid(const string& guess)const;

    // look for first letter in guessed word and start recursion for rest of word
    bool word_on_board(const string& guess)const;

    // recursivly searches neighbors for next letter in word.
    bool valid_letter (unordered_set<pair<int,int>,hash_pair> positions, const string& guess, const int x, const int y)const;

    // insert word into guesses
    void add_guess(const string& guess);

    // print the guesses you have made so far
    void print_guesses()const;

    // returns the amount of words you have guessed
    int get_guesses_size()const;

    //calculates the score based on the guessed words
    void print_score()const;


    // the computer starts the search for all words in lexicon
    void computer_words();

    // recursive search for a next valid letter on the board
    void computer_search(unordered_set<pair<int,int>,hash_pair> positions, string& guess, const int x, const int y);

    // prints the words the computer has found
    void print_computer_words();

    // calculates and prints the score of the computer
    void print_computer_score()const;

    // set the private values of the game to start values
    void clear_game();


private:
     Grid<char> board{BOARD_SIZE,BOARD_SIZE};
     unordered_set<string> guesses = {};
     unordered_set<string> other_words = {};
     Lexicon lex{DICTIONARY_FILE};
};

#endif
