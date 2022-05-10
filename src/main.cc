#include "graph.h"
#include <iostream>
#include <string>
#include <functional>
#include <initializer_list>


using std::string;
using std::cin;
using std::cout;
using std::endl;

// typedef string (*Function)(string, int); // function pointer type

// typedef std::string (*)()

string help() {
     cout << endl;
     cout << "OPTIONS: " << endl;
     cout << "To pull up this menu:\t\t\t\t\t\"0\"" << endl;
     cout << "To generate the highest weight sentence(**):\t\t\"1 [start word]  [length]\"" << endl;
     cout << "To generate a greedy highest-weight sentence:\t\t\"2 [start word]  [length]\"" << endl;
     cout << "To generate a greedy lowest-weight sentence:\t\t\"3 [start word]  [length]\"" << endl;
     cout << "To generate a probabilistic sentence:\t\t\t\"4 [start word]  [length]\"" << endl;
     cout << "To generate a completely random sentence:\t\t\"5 [start word]  [length]\"" << endl;
     cout << "To view words that are n-degrees away (BFS):\t\t\"6 [output file] [start word]\"" << endl;
     cout << "To view the graph as adjacency lists:\t\t\t\"7 [output file]\"" << endl;
     cout << "To leave the program:\t\t\t\t\t\"8\"" << endl;
     cout << "\n\n\n**: This function is computationally-heavy." << endl;
     return "";
}


int main (int argc, char** argv) {
    int inputChoice;
    string file_path = argc > 1 ? argv[1] : "processing/parsed_book.txt";


    Graph* g = new Graph(file_path);
    help();

    while (true) {
        cout << "Enter a number corresponding to your query: ";
        cin >> inputChoice;
        if(cin.bad()) { 
            throw std::runtime_error("stream failed");
        } 
        else if (cin.fail()) { 
            cin.clear();
            cin.ignore( 1, '\n' );
        } 
        else {
            if (inputChoice == 0) {
                help();
                continue;
            }

            if (inputChoice == 8) {
                cout << "Finished.";
                delete g;
                std::exit(0);
            }

            if (0 > inputChoice || inputChoice > 8) {
                cout << "Input is invalid" << endl;
                continue;
            }

            int length;
            string start_word;
            string filepath;

            if (1 <= inputChoice && inputChoice <= 5) {
                cout << "Starting word in your query: " ;
                cin >> start_word;
                cout << endl << "Words in your traversal: ";
                cin >> length;
            } else if (inputChoice == 7) {
                cout << "Filepath for output file: " ;
                cin >> filepath;
            } else {
                cout << "Filepath for output file: " ;
                cin >> filepath;
                cout << endl << "Starting word in your query: ";
                cin >> start_word;
                
            }
            
            if(cin.bad()) { 
                throw std::runtime_error("stream failed");
            } 
            else if (cin.fail()) { 
                cin.clear();
                cin.ignore( 1, '\n' );
                cout << "invalid input! please try again!" << endl;
                continue;
            } 
            

            switch (inputChoice) {
                case 1:
                    cout << g->HighestWeightSentence(start_word, length) << endl;
                    break;
                case 2:
                    cout << g->HighestGreedySentence(start_word, length) << endl;
                    break;
                case 3:
                    cout << g->LowestGreedySentence(start_word, length) << endl;
                    break;
                case 4:
                    cout << g->ProbabilisticSentence(start_word, length) << endl;
                    break;
                case 5:
                    cout << g->RandomSentence(start_word, length) << endl;
                    break;
                case 6:
                    g->WriteAsBFS(filepath, start_word);
                    break;
                case 7:
                    g->WriteToTXT(filepath);
                    break;
            } 
        }
    }
}