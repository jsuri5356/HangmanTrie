#include "hangman.h"

struct Tester{
    void testInsert();
    void testSearch();
    void testInsertEdge();
    void testSearchEdge();
};

int main(){
    Tester tester;
    tester.testInsert();
    tester.testSearch();
    tester.testInsertEdge();
    tester.testSearchEdge();
}

void Tester::testInsert(){
    cout << "1. Testing testInsert\n\n";
    Hangman* hangman = new Hangman();
    if(hangman->insert("Test"))
        cout << "testInsert passed!\n\n";
    else
        cout << "testInsert failed!\n\n";
    delete hangman;
}

void Tester::testSearch(){
    cout << "2. Testing testSearch\n\n";
    Hangman* hangman = new Hangman();
    hangman->insert("Test");
    if(hangman->search("T"))
        cout << "testSearch passed!\n\n";
    else
        cout << "testSearch failed!\n\n";
    delete hangman;
}

void Tester::testInsertEdge(){
    cout << "3. Testing testInsertEdge\n\n";
    Hangman* hangman = new Hangman();
    if(!(hangman->insert("")))
        cout << "testInsertEdge passed!\n\n";
    else
        cout << "testInsertEdge failed!\n\n";
    delete hangman;
}

void Tester::testSearchEdge(){
    cout << "4. Testing testSearchEdge\n\n";
    Hangman* hangman = new Hangman();
    hangman->insert("Test");
    if(!(hangman->search("n")))
        cout << "testSearchEdge passed!\n\n";
    else
        cout << "testSearchEdge failed!\n\n";
    delete hangman;
}

