// Wilhelm Malé (wilma870)
// Oscar Jansson (oscja211)

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};


void Boggle::make_board (const string& s){

    //shuffle(CUBES)
    int counter = 0;
    for(int i = 0; i < BOARD_SIZE; i ++){
        for(int j = 0; j < BOARD_SIZE; j ++){
            if(s != "y"){
                board.set(i,j,s[counter]);
            }else{
                board.set(i,j,CUBES[counter][rand() % CUBE_SIDES]);
            }
            counter++;
        }
    }
     if(s == ""){
         shuffle(board);
     }
    std::cout<<board<< std::endl;
}


void Boggle::print_board()const{
    for(int i = 0; i < BOARD_SIZE; i ++){
        for(int j = 0; j < BOARD_SIZE; j ++){
            if(j == 0){
                cout <<  endl;
            }
            cout << board.get(i,j) << " " ;
        }
    }
    cout << endl;
}

bool Boggle::word_valid(const string& guess)const{
    if(guess.size() >= 4){
        if (guesses.find(guess) == guesses.end() ){
            if(lex.contains(guess) && word_on_board(guess)){
                return true;
            }
        }
    }
        return false;
}


bool Boggle::word_on_board(const string& guess)const{
    unordered_set<pair<int,int>, hash_pair> positions;
    bool result = false;
    for(int i = 0; i < BOARD_SIZE; i ++){
        for(int j = 0; j < BOARD_SIZE; j ++){
            char letter = board.get(i,j);
            if(letter == guess[0]){
                result = valid_letter(positions, guess, i, j);
                if (result){
                    return true;
                }
            }
        }
    }
    return false;
}


bool Boggle::valid_letter(unordered_set<pair<int,int>, hash_pair> positions, const string& guess, const int x, const int y)const{ // the recursive function

    positions.insert(pair(x,y));

    if (positions.size() == guess.size()){
        return true;
    }

    char letter = guess[positions.size()];
    bool result = false;

    for (int i = x-1; i <= x+1 ; i ++){
        for (int j = y-1; j <= y+1 ; j ++){
            if (board.inBounds(i,j)){

                if (!positions.contains(pair(i,j))){
                    if (board.get(i,j) == letter){
                        result = valid_letter(positions, guess, i, j);
                        if (result){
                            return result;
                        }
                    }
                }
            }
        }
    }
    return result;
}


void Boggle::add_guess(const string& guess){
    guesses.insert(guess);
}


void Boggle::print_guesses()const{

    bool first = true;
    for(const string& word : guesses){
        if (first){
            first = false;
            std::cout << word;
        }
        else{
            std::cout << "," << word;
        }
    }
    std::cout << std::endl;
}


int Boggle::get_guesses_size()const{
    return guesses.size();
}


void Boggle::print_score()const{
    int score = 0;
    for (const string& word : guesses){
        score += word.size()-3;
    }
    std::cout << "your score: " << score << std::endl;
}


void Boggle::computer_words(){
    unordered_set<pair<int,int>, hash_pair> positions;

    for(int i = 0; i < BOARD_SIZE; i ++){
        for(int j = 0; j < BOARD_SIZE; j ++){
            string letter = "";
            letter.push_back(board.get(i,j));
            computer_search(positions, letter, i, j);
        }
    }
}


void Boggle::computer_search(unordered_set<pair<int,int>, hash_pair> positions, string& guess, const int x, const int y){ // the recursive function

    positions.insert(pair(x,y));

    if (guess.size() >= 4
            && guesses.find(guess) == other_words.end()
            && other_words.find(guess) == other_words.end()
            && lex.contains(guess)){
        other_words.insert(guess);
    }

    for (int i = x-1; i <= x+1 ; i ++){
        for (int j = y-1; j <= y+1 ; j ++){
            if (board.inBounds(i,j)){

                if (!positions.contains(pair(i,j))){
                    string next_guess = guess;
                    next_guess.push_back(board.get(i,j));
                    if (lex.containsPrefix(next_guess)){
                        computer_search(positions, next_guess, i, j);
                    }
                }
            }
        }
    }
}


void Boggle::print_computer_words(){
    computer_words();

    bool first = true;
    for (const string& word : other_words){
        if (first){
            first = false;
            std::cout << word;
        }
        else{
            std::cout << "," << word;
        }
    }
    std::cout << std::endl;
}


void Boggle::print_computer_score()const{
    int score = 0;
    for (const string& word : other_words){
        score += word.size()-3;
    }
    std::cout << "My score: " << score << std::endl;
}


void Boggle::clear_game(){
    guesses.clear();
    other_words.clear();
}
