#include "hangman.h"

Hangman::Hangman(){
        this->endOfWord = false;
        for(int i = 0; i < SIZE; i++){
            this->leaf[i] = nullptr;
        }
}

Hangman::~Hangman(){
    Hangman *temp = this;
    for(int i = 0; i < SIZE; i++){
        delete temp->leaf[i];
    }
}


// insert whole words as seperate nodes in the tree
bool Hangman::insert(string key){
    if(key == ""){
        return false;
    }
    int length = 0;
    length = (int) key.length();
    string charToString;
    string keys[length];
    for(int i = 0;  i < (int) key.length(); i++){
        charToString = key[i];
        keys[i] = charToString;
    }

    // I have no idea why sizeof(keys[0]) is needed, but seems to segfault without it
    int size = sizeof(keys)/sizeof(keys[0]);
    for (int i = 0; i < size; i++)
        insertArray(keys[i]);
    return true;
}


// actual insertion
void Hangman::insertArray(string theWord){
    Hangman *temp = this;
    for(int i = 0; i < (int) theWord.length(); i++){
        // without unsigned char, tends to give warnings
        unsigned char word = theWord[i];
        if(temp->leaf[word] == nullptr){
            temp->leaf[word] = new Hangman();
        }
        temp = temp->leaf[word];
    }
    temp->endOfWord = true;
}

// search the tree for the letter
bool Hangman::search(string wordSearch){
    Hangman *temp = this;
    for(int i = 0; i < (int) wordSearch.length(); i++){
        // without unsigned char, tends to give warnings
        unsigned char word = wordSearch[i];
        temp = temp->leaf[word];
        if(temp == nullptr){
            return false;
        }
    }

    return temp->endOfWord;
}

// check for multiples of the same letter in the word using sets
int Hangman::checkMultiples(string word){
    string charToString;
    set<string> keys;
    for(int i = 0;  i < (int) word.length(); i++){
        charToString = word[i];
        // ignore if there is a space in the word
        if(charToString != " "){
            keys.insert(charToString);
        }
    }
    return keys.size();
}



string Hangman::loadWords(){
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



void Hangman::program(){
    Hangman* hangman = new Hangman();
    string key, choice, letterToGuess, wordGuess;
    int win = 0;
    unsigned int loss = 0;
    string wrongLetterArray[26];

    cout << "\nWelcome to Hangman!\n";
    cout << "Would you like the computer to randomly pick a word for you to guess (y/n)? ";
    cin >> choice;
    cin.ignore();
    if(choice == "y"){
        key = loadWords();
    }else{
        cout << "Enter the word you would like to guess for yourself: ";
        getline(cin, key);
    }
    // insertion
    for(int i = 0; i < (int) key.length(); i++){
        key[i] = tolower(key[i]);
    }
    hangman->insert(key);

    string letterArray[(int) key.length()];    
    string emptyGraph[(int) key.length()];

    for(int i = 0; i < (int) key.length(); i++){
        emptyGraph[i] = "_";
        if(key[i] == ' '){
            emptyGraph[i] = ' ';
        }
        letterArray[i] = key[i];
    }

    while(win != hangman->checkMultiples(key)){
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
        for(int i = 0; i < (int) letterToGuess.length(); i++){
            letterToGuess[i] = tolower(letterToGuess[i]);
        }


        while(letterToGuess.length() > 1){
            cout << "Please only enter one letter! \n";
            cout << "Guess a letter or press 2 to guess the word! ";
            getline(cin, letterToGuess);
            for(int i = 0; i < (int) letterToGuess.length(); i++){
                letterToGuess[i] = tolower(letterToGuess[i]);
            }
        }

        if(letterToGuess == "2"){
            cout << "What do you think the word is? ";
            getline(cin, wordGuess);
            if(wordGuess == key){
                cout << "You guessed correctly!\n";
                break;
            }else{
                cout << "That's not right! \n";
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

        if(hangman->search(letterToGuess) == false && letterToGuess != "2"){
            hangman->printHangMan(loss);
            wrongLetterArray[loss] = letterToGuess;
            loss++;
            cout << "That's the wrong letter!\nYou have " << 5 - loss << " tries left\n\n";
        }

        if(win == hangman->checkMultiples(key)){
            cout << "You guessed correctly!\n";
            break;
        }

        if(loss == 5){
            hangman->printHangMan(5);
            cout << "You ran out of guesses!\n";
            break;
        }
    }

    cout << "The word was " << "\""<< key << "\""<< endl;
    delete hangman;
    cout << "Thank you for playing!\n";
}