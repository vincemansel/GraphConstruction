//
//  wordLadder.cpp
//  graphConstruction
//
//  Created by Vince Mansel on 10/30/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "set.h"
#include "map.h"
#include "stack.h"
#include "lexicon.h"
#include "vector.h"
#include "strutils.h"

#include "shortestPathFirst.h"


const int Word_Size = 5;

void ConstructGraph(graphT & graph, Lexicon & lex, int &count, int &connections);
nodeT * GetGraphNode(graphT & graph, string word);

Stack<nodeT *> FindShortestLaddder(graphT & graph, nodeT * &start, nodeT * &end);
Stack<nodeT *> FindLongestLadder(graphT & graph, nodeT * &word);
void ShowAllConnectedWords(nodeT * word);

string GetWordFromUser(string message, Lexicon & lex);
void GetSizedLetterWords(string word, Lexicon & wordLex);
void PrintLex(Lexicon &lex);

int main() {
    
    cout << "Welcome to the Word Ladder" << endl;
    cout << " -- making connections, please wait --" << endl;

    graphT graph;
    Lexicon bigLex("lexicon.dat");
    Lexicon lex;
    bigLex.mapAll<Lexicon>(GetSizedLetterWords, lex);
    //PrintLex(lex);
    
    int count = 0;
    int connections = 0;
    
    ConstructGraph(graph, lex, count, connections);
    
    bool timeToQuit = false;
    
    cout << "There are " << count << " words with " << connections << " connections!" << endl;
    
    while (true) {
        
        cout << "Your options are:" << endl;
        cout << "(1) Find the shortest word ladder between two " << Word_Size << " letter words (BFS)" << endl;
        cout << "(2) Find the longest word ladder of a " << Word_Size << " letter word (DFS)" << endl;
        cout << "(3) Show all words connected to a " << Word_Size << " letter word" << endl;
        cout << "(4) Quit" << endl;
        cout << "Enter choice: ";
        
        int choice = GetInteger();
        
        string startWord;
        string endWord;
        string wordToGet;
        nodeT *start;
        nodeT *end;
        nodeT *word;
        Stack<nodeT *> ladder;
        
        switch (choice) {
            case 1:
                startWord = GetWordFromUser("Enter the starting " + IntegerToString(Word_Size) + " letter word: ", lex);
                endWord = GetWordFromUser("Enter the ending " + IntegerToString(Word_Size) + " letter word: ", lex);
                start = GetGraphNode(graph, startWord);
                end = GetGraphNode(graph, endWord);
                ladder = FindShortestLaddder(graph, start, end);
                break;
            case 2:
                startWord = GetWordFromUser("Enter a " + IntegerToString(Word_Size) + " letter word: ", lex);
                word = GetGraphNode(graph, startWord);
                ladder = FindLongestLadder(graph, word);
                break;
            case 3:
                startWord = GetWordFromUser("Enter a " + IntegerToString(Word_Size) + " letter word: ", lex);
                word = GetGraphNode(graph, startWord);
                ShowAllConnectedWords(word);
                break;
            case 4:
                cout << "Thanks for playing with the Word Ladder. Bye!" << endl;
                timeToQuit = true;
                break;    
            default:
                cout << "Invalid choice" << endl;
                break;
        }
        
        if (timeToQuit) break;
        
    }
    return (0);
}

string GetWordFromUser(string message, Lexicon & lex) {
    string word;
    while (true) {
        cout << message;
        word = GetLine();
        if (word.size() != Word_Size) {
            cout << Word_Size << "  letters please... " << endl;
        }
        else if (!lex.containsWord(word)) {
            cout << " Unknown word. Enter another word... " << endl;
        }
        else
            break;
    }
    
    return word;
}

void GetSizedLetterWords(string word, Lexicon & wordLex) {
    if (word.size() == Word_Size)
        wordLex.add(word);
}

void PrintLex(Lexicon &lex) {
    Lexicon::Iterator itr = lex.iterator();
    int i = 0;
    while (itr.hasNext()) {
        string word = itr.next();
        cout << i++ << ": " << word << endl;
    }
}

void PutWordInGraph(graphT & graph, Map<nodeT *> & graphMap, string word) {
    if (!graphMap.containsKey(word)) {
        nodeT *node = new nodeT;
        node->name = word;
        graphMap.add(word,node);
        graph.allNodes.add(node);
    }
}

void RecFindConnections(Lexicon & lex, graphT & graph, Map<nodeT *> & graphMap, string currentWord, string prefix, string subLetter, string postfix, int index, int &connections) {    
    if (prefix.size() == Word_Size)
        return;
    
    for (char ch = 'a'; ch <= 'z'; ch++) {
        string chString;
        chString += ch;
        if (chString != subLetter) {
            string word = prefix + chString + postfix;
            if (lex.containsWord(word)) {
                PutWordInGraph(graph, graphMap, word);
                arcT * arc = new arcT;
                arc->start = graphMap[currentWord];
                arc->end = graphMap[word];
                graphMap[currentWord]->connected.add(arc);
                connections++;
            }
        }
    }
    prefix = graphMap[currentWord]->name.substr(0,index);
    subLetter = postfix.substr(0,1);
    if (index < Word_Size)
        postfix = graphMap[currentWord]->name.substr(index+1);
    RecFindConnections(lex, graph, graphMap, currentWord, prefix, subLetter, postfix, index+1, connections);
}

void ConstructGraph(graphT & graph, Lexicon & lex, int &count, int &connections) {
    Lexicon::Iterator itr = lex.iterator();
    Map<nodeT *> graphMap;
    while (itr.hasNext()) {
        string word = itr.next();
        PutWordInGraph(graph, graphMap, word);
        string prefix = "";
        string subLetter = word.substr(0,1);
        string postfix = word.substr(1);
        RecFindConnections(lex, graph, graphMap, word, prefix, subLetter, postfix, 1, connections);
        count++;
    }
}

void PrintLadder(Stack<nodeT *> ladder) {
    
    while (!ladder.isEmpty()) {
        cout << ladder.pop()->name << endl;
    }
}

Stack<nodeT *> FindShortestLaddder(graphT & graph, nodeT * &start, nodeT * &end) { 
    Stack<nodeT *> ladder = ShortestPathFirst(start, end);
    
    PrintLadder(ladder);
    
    return ladder;
}

Stack<nodeT *> FindLongestLadder(graphT & graph, nodeT * &word) {    
    Stack<nodeT *> ladder;
    
    return ladder;  
}

nodeT * GetGraphNode(graphT & graph, string word) {
    Set<nodeT *>::Iterator itr = graph.allNodes.iterator();
    
    while (itr.hasNext()) {
        nodeT * node = itr.next();
        if (word == node->name) {
            return node;
        }
    }
    
    return NULL;
}

void ShowAllConnectedWords(nodeT * word) {    
    
    Set<arcT *>::Iterator itr = word->connected.iterator();
    
    cout << "WORD: " << word->name << endl;
    
    while (itr.hasNext()) {
        arcT * arc = itr.next();
        cout << arc->start->name << " <-> " << arc->end->name << endl;
    }
    
    
    
}




