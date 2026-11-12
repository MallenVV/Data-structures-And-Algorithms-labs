// Wilhelm Malé (wilma870)
// Oscar Jansson (oscja211)

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>
#include <map>

using namespace std;

// saves an unordered set of all available words with the prompt to later search through.
unordered_set<string> save_compatible_words(ifstream& dictionary, const int word_length){
    unordered_set<string> dict;
    string some, read;
    while(true) {
        getline(dictionary, some);
        if (some == read){
            break;
        }

        if ((int)some.size() == word_length){
            dict.insert(some);
        }
        read = some;
    }
    return dict;
}

// sorts through our unordered set to construct new word families
map <string,unordered_set<string>> word_familie_sort(const unordered_set<string>& word_list, const char guess){
    map<string,unordered_set<string>> new_families;
    for (string word: word_list){
        string familiy;
        for (char letter: word){
            if (letter == guess){

                familiy += guess;
            }
            else {
                familiy += "-";
            }
        }
        new_families[familiy].insert(word);
    }

    return new_families;
}

// finds the biggest word_familie and returnes the biggest
pair<string, unordered_set<string>> find_biggest(const map<string,unordered_set<string>>& families){

    unordered_set<string> biggest;
    string biggest_key;
    for (auto const& [key, value]: families){   // StackOverflow för lopa igenom map: https://stackoverflow.com/questions/26281979/how-do-you-loop-through-a-stdmap
        if(value.size() > biggest.size()){
            biggest = value;
            biggest_key = key;
        }
    }
    return pair(biggest_key, biggest);
}


int main() {

    while(true){
        ifstream dictionary;
        dictionary.open("dictionary.txt");

        cout << "Welcome to Hangman." << endl;
        cout << "Enter number of letters" << endl;
        int guesses,letters;
        string guessed_word;
        unordered_set<char> guessed_letters;
        while(true){
             cin >> letters;

             if(letters > 1){
                 for (int i =0; i<letters; i++){
                     guessed_word += "-";
                 }
                 break;
             }
        }
        unordered_set<string>dict = save_compatible_words(dictionary,letters);
        if (dict.size() == 0){
            cout << "There exists no word with " << letters << " letters" << endl;
            cout << endl;
            continue;
        }
        cout << "Enter number of guesses" << endl;

        while(true){
               cin >> guesses;

             if(letters > 0){
                 break;
             }
        }
        string answer;
        bool reveal;
        cout << "Do you want to see the remaining words after every guess? y/n (lower case)" << endl;

        while(true){
            cin >> answer;

            if(answer == "y" || answer == "Y"){
                reveal = true;
                break;
            }else if(answer == "n" || answer == "N"){
                reveal = false;
                break;
            }
        }

        map <string,unordered_set<string>> word_families;

        while(guesses > 0 && guessed_word.find('-') != string::npos){   // Cplusplus.com för returvärde med find: cplusplus.com/reference/string/string/find/

            cout << endl;
            cout << "You have " << guesses << " guesses left" << endl;
            guesses --;
            string guess;

            for (char letter: guessed_letters){
                cout << letter << ",";
            }
            cout << endl;

            if(reveal){
                cout << "There exists " << dict.size() << " matching words"<< endl;
            }
            cout << "current: " << guessed_word << endl;

            while (true){
                cout << "Guess a letter: ";
                cin >>guess;
                if (guessed_letters.contains(guess[0])){
                    cout << "You hve already guessed this letter try another" << endl;
                }
                else if (guess.size() == 1){
                    guessed_letters.insert(guess[0]);
                    break;
                }
                else {
                    cout << "Not a valid guess" << endl;
                }
            }

            map <string,unordered_set<string>> word_families = word_familie_sort(dict, guess[0]);
            pair<string, unordered_set<string>> group = find_biggest(word_families);

            dict = group.second;
            string guess_result = group.first;

            for (size_t i = 0; i<guessed_word.size();i++){
                if (guessed_word[i] == '-'){
                    guessed_word[i] = guess_result[i];
                }
            }
        }

        if(guessed_word.find('-') == string::npos){
             cout << "You guessed the word! YOU WIN!!! the word was: " << guessed_word <<  endl;

        }

        else if(guesses == 0){
            cout << "You ran out of guesses. YOU LOSE the word was: " << *dict.begin() << endl;
        }
        string play_again;
        cout << "Would you like to play again? y/n" << endl;
        cin >> play_again;

        if (play_again != "y"){
            break;
        }
    }
    return 0;
}
