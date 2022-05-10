#include <unordered_map>
#include <unordered_set>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using std::unordered_map;
using std::unordered_set;
using std::map;
using std::string;
using std::pair;
using std::queue;


/*
Our predecessor-successor sequence can be represented as the graph shown below
"second" comes after "first" in a phrase
{
    "first": ["second": freq, "second2": freq2...]
    "first1": ["second": freq, "second2", freq2]
}
*/

struct Word {
    string word; // represents the current word
    vector<pair<string, size_t>> adjacents;

    //buckets is calculated through prefix sum + Binary Search
    vector<pair<string, size_t>> buckets;
};

class Graph {
public:
    /*
    Graph:
    Generates the graph object given a filename
    */
    Graph(std::string filename);
    /*
    HighestWeightSentence: 
    Takes a given length and returns most likely sentence for said given length
    */
    string HighestWeightSentence(string word, size_t length);
    /* 
    ProbabilisticSentence:
    Takes a given length and uses a random to dictate which word to go to next in a phrase using weighted probability
    */
    string ProbabilisticSentence(string word, size_t length);
    /*
    HighestGreedySentence:
    For each word it takes the word with the highest edge weight and chooses that as the next word until it creates a sentence of length, length
    In case of a tie with edge weights, the word that appears in the text first is chosen.
    */
    string HighestGreedySentence(string word, size_t length);
    /*
    LowestGreedySentence:
    For each word it takes the word with the least edge weight and chooses the next woord until it creates a sentence of length, length
    In case of a tie with edge weights, the word that appears in the text last  is chosen
    */
    string LowestGreedySentence(string word, size_t length);
    /*
    Random Sentence:
    Choses words randomly from the adjacency list disregarding the given edge weights until a sentence of length, length, is created
    */
    string RandomSentence(string word, size_t length);

    /*
    WriteToTXT:
    Creates a TXT that displays each word in the form of"element: " and below each word displays its respective adjancency list sorted from larger
    to lower frequency 
    */
    void WriteToTXT(string filename);
    /*
    Uses a BFS to display the entire graph
    */
    void WriteAsBFS(string filename, string start);

private:
    void BacktrackHelper(const string& word, vector<string>& sentence,size_t weight, size_t length, vector<string>& best_sentence, size_t& best_weight);
    unordered_map< string, Word> graph;
    std::unordered_set<string> visited;
    string SentenceDecoder(const vector<string>& words);
};
