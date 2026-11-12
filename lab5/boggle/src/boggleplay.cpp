// Wilhelm Malé (wilma870)
// Oscar Jansson (oscja211)

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"

using namespace std;
// TODO: include any other header files you need

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    // TODO: implement this function (and add any other functions you like to help you)
    cout<<"Do you want to generate a random board? ";
    string input;
    getline(cin, input);

    if(input == "n"){
        while (input.size() != 16){
            cout<< "create you board:" ;
            getline(cin, input);
        }
        boggle.make_board(input);
    }
    else {
         boggle.make_board("y");
    }

    // create input 16 char.



    while(true){
        clearConsole();

        boggle.print_board();
        cout << "Your words (" << boggle.get_guesses_size() << ") ";
        boggle.print_guesses();
        boggle.print_score();

        cout << "Type a word (or press enter to end your turn): ";
        getline(cin, input);

        if(input.empty()){
            cout << "ended your turn" << input << endl;
            break;
        }

        string guess;
        for (char c : input){
            guess.push_back(toupper(c));
        }

        if(boggle.word_valid(guess)){
            cout << "word valid" << endl;
            boggle.add_guess(guess);
        }
    }

    boggle.print_computer_words();
    boggle.print_computer_score();
    boggle.clear_game();
    // DATORNS TUR

}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
