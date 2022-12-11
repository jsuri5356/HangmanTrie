#include "hangman.h"
#include <fstream>
#include <ctime>

const int WORD_SIZE = 2315;
string loadWords(){
    string myArray[WORD_SIZE];
    string word;
    int counter = 0;
    ifstream myFile ("wordlist.txt");
    if(myFile.is_open()){
        while(myFile >> word && counter < WORD_SIZE){
            myArray[counter] = word;
            counter++;
        }
        cout << "Your file was imported!" << endl;
        cout << counter << " words were imported" << endl;
    }else{
        cout << "The word list doesn't exist! (make sure to have it in the same directory)" << endl;
    }
    myFile.close();
    string realWord;
    srand(time(NULL));
    realWord = myArray[rand() % WORD_SIZE];
    return realWord;
}



int main(){
    Hangman* hangman = new Hangman();
    string key, choice, letterToGuess, wordGuess;
    bool winBool = true;
    int win = 0;
    unsigned int loss = 0;
    cout << "\nWelcome to Hangman!\n";
    cout << "Would you like the computer to randomly pick a word for you to guess (y/n)? ";
    cin >> choice;
    cin.ignore();
    if(choice == "y"){
        key = loadWords();
    }else{
        cout << "Enter the word you would like to guess for yourself: ";
        cin >> key;
        cin.ignore();
    }
    hangman->insert(key);
    string letterArray[(int) key.length()];
    string emptyGraph[(int) key.length()];
    for(int i = 0; i < (int) key.length(); i++){
        emptyGraph[i] = "_";
        letterArray[i] = key[i];
    }
    string wrongLetterArray[26];
    while(win != (int) key.length()){
        cout << "Letters that you have guess that are right: ";
        for(int i = 0; i < (int) key.length(); i++){
            cout << emptyGraph[i];
        }
        cout << endl;
        cout << "Letters that you have guessed that are wrong: ";
        for(int i = 0; i < (int) key.length(); i++){
            cout << wrongLetterArray[i];
        }
        cout << endl;
        cout << "Guess a letter or press 2 to guess the word! ";
        getline(cin, letterToGuess);

        while(letterToGuess.length() > 1){
            cout << "Please only enter one letter! \n";
            cout << "Guess a letter or press 2 to guess the word! ";
            getline(cin, letterToGuess);
        }
        if(letterToGuess == "2"){
            cout << "What do you think the word is? ";
            getline(cin, wordGuess);
            if(wordGuess == key){
                cout << "You guessed correctly!\n";
                break;
            }else{
                cout << "That's not right! ";
                loss--;
            }
        }
        if(hangman->search(letterToGuess)){
            for(int i = 0; i < (int) key.length(); i++){
                if(letterArray[i] == letterToGuess){
                    emptyGraph[i] = letterArray[i];
                }
            }
            win++;
            cout << "Letter " << letterToGuess << " found!\n";
        }
        if(letterToGuess.length() == 1){
            if(hangman->search(letterToGuess) == false){
                cout << "That's the wrong letter!\n";
                hangman->printHangMan(loss);
                wrongLetterArray[loss] = letterToGuess;
                loss++;
            }
        }
        for(int i = 0; i < (int) key.length(); i++){
                if(emptyGraph[i] != letterArray[i]){
                    winBool = false;
                }
            }
        if(winBool){
            cout << "You guessed correctly!\n";
            break;
        }
        if(loss == 5){
            hangman->printHangMan(5);
            cout << "You ran out of guesses!\n";
            break;
        }
    }
    cout << "The word was " << key << endl;
    delete hangman;
    cout << "Thank you for playing!";
    return 0;
}