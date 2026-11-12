// Wilhelm Malé (wilma870)
// Oscar jansson (oscja211)

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

const char ALPHABET[]  = "abcdefghijklmnopqrstuvwxyz";


// creates a unorderd set of all words with the same lenght as the words we are trying to convert
unordered_set<string> save_compatible_words(ifstream& dictionary, const size_t word_length){
    unordered_set<string> dict;
    string some, read;
    while(true) {
        getline(dictionary, some);
        if (some == read){
            break;
        }
        if (some.size() == word_length){
            dict.insert(some);
        }
        read = some;
    }
    return dict;
}

// creates and writes the string to show the progression of evolution
void finished (stack<string>& stack){
    string transformation;
    while (!stack.empty()){
        if (stack.size()==1){
            transformation = stack.top() + transformation;
        }
        else {
            transformation = " -> " + stack.top() + transformation;
        }
        stack.pop();
    }
    cout << transformation << endl;
}

int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";

    string word1, word2;

    cin >> word1 >> word2;
    ifstream dictionary;
    dictionary.open("dictionary.txt");

    unordered_set<string>dict = save_compatible_words(dictionary,word1.size());

    queue<stack<string>>stack_queue;

    stack<string>evolution;
    evolution.push(word1);
    stack_queue.push(evolution);

    unordered_set<string>found_words;
    found_words.insert(word1);

    while (!stack_queue.empty()){
        stack<string>current_stack = stack_queue.front();
        stack_queue.pop();

        for (size_t i =0; i < word1.size(); i++){

            for (size_t j =0; j< sizeof(ALPHABET); j++){
                char letter = ALPHABET[j];
                string new_word = current_stack.top();
                new_word[i]=letter;

                if (dict.contains(new_word) && !found_words.contains(new_word)){
                    found_words.insert(new_word);

                    stack<string>new_stack = current_stack;
                    new_stack.push(new_word);

                    if (new_word == word2){
                        finished(new_stack);
                        return 0;
                    }

                    stack_queue.push(new_stack);
                }
            }
        }
    }
    cout << "there was no possible way to get from " << word1 << " to " << word2 << endl;
    return 0;
}
