#include "graph.h"
#include <iostream>
#include <fstream>
#include <time.h> 
#include <stdlib.h>
#include <stdexcept>

Graph::Graph(string filename) {
    std::ifstream text(filename);

    if(!text.is_open()){
        throw std::runtime_error("Cannot be opened");
    }

    string prev;
    string curr;
    text >> prev; // Skip the first element
    while(text >> curr){
        if(!graph.count(prev)){ // key does not exist in map
            graph[prev] = Word();
            graph[prev].word = prev;  
        }
        
        vector< std::pair<string, size_t> >& adj = graph[prev].adjacents;

        //Return an iterator pointing to the element in the adjacents such that the word is equal to current 
        auto word_iter = std::find_if(adj.begin(), adj.end(), 
                                    [curr](std::pair<string, size_t> p) {return p.first == curr;});
        
        if (word_iter == adj.end()) {
            adj.push_back(std::make_pair(curr, 1));
        } else {
            word_iter->second += 1;
        }
        prev = curr;
    }

    // Sort each individual vector in the adjacency list by frequency
    for (auto &it : graph) {
        vector<pair<string, size_t>>& v = it.second.adjacents;
        std::stable_sort(v.begin(), v.end(), 
            [](const pair<string, size_t> & a, const pair<string, size_t> & b){ 
            return a.second > b.second; 
        });
    }

    for(auto &it: graph){
        it.second.buckets = it.second.adjacents;
        size_t running_sum = 0;
        for(auto &i: it.second.buckets){
            i.second += running_sum;
            running_sum = i.second;
        }
    }

    text.close();
}


string Graph::HighestWeightSentence(string word, size_t length) {
    if (length == 1) return word + ".";
    vector<string> initial = {word};
    vector<string> sentence = initial;
    size_t best_weight = 0;
    
    BacktrackHelper(word, initial, best_weight, length, sentence, best_weight);

    visited.clear();

    if (sentence.size() != length) return "No sentence of length " + std::to_string(length) + " could be generated from word: " + word;
    return SentenceDecoder(sentence);
}

void Graph::BacktrackHelper(const string& word, vector<string>& sentence,size_t weight, size_t length, vector<string>& best_sentence, size_t& best_weight) {
    if (visited.count(word)) {
        visited.erase(word);
        return;
    }

    visited.insert(word);
    if (sentence.size() == length) {
         if(weight >= best_weight) {
             best_weight = weight;
             best_sentence = sentence;
         }
         visited.erase(word);
         return;
     }

    Word& info = graph[word];
    for (const auto& pair : info.adjacents) {
        string new_word = pair.first;
        size_t delta_weight = pair.second;

        sentence.push_back(new_word);
        BacktrackHelper(new_word, sentence, weight + delta_weight, length, best_sentence, best_weight);
        sentence.pop_back();
    }
    
    if (visited.count(word)) {
        visited.erase(word);
        return;
    }
    
}

void Graph::WriteToTXT(string filename){
     std::ofstream text;
     text.open(filename);
     for(auto i: graph){
        text << "element: " << i.first << "\n";
        for(auto& pair : graph[i.first].adjacents){
            text << pair.first << ": " <<  pair.second << " " ;
        }
        text << "\n";
     }
}

void Graph::WriteAsBFS(string filename, string start) {
    std::ofstream text;
    text.open(filename);

    Word curr = graph[start];
    unordered_set < string > visited;
    
    queue< std::pair< Word, size_t> > to_visit;

    to_visit.push({curr, 0});

    size_t curr_depth = 1;

    while (!to_visit.empty()) {
        std::pair<Word, size_t> p = to_visit.front();

        curr = p.first;
        size_t d = p.second;
        
        to_visit.pop();

        if (d != curr_depth) {
            text << std::endl;
            text << "\nThe following words first appear at depth " << d+1 << ": \n";
            curr_depth = d;
        }

        if (visited.count(curr.word)) {
            continue;
        } else {
            visited.insert(curr.word);
            text << curr.word << " ";
        }

        for (pair<string, size_t>& word_and_weight : curr.adjacents) {
            string w = word_and_weight.first;
            to_visit.push({graph[w], d + 1});
        }
    }
    visited.clear();
}

string Graph::SentenceDecoder(const vector<string>& words){
    string sentence = "";
    for (const auto& i : words){
        sentence += i + " ";
    }
    sentence.pop_back();
    sentence.push_back('.');
    sentence.push_back('\n');
    return sentence;
}

string Graph::ProbabilisticSentence(string word, size_t length){
    vector<string> sentence;
    sentence.push_back(word);

    for(size_t count = 0; count < length - 1; ++count){
        Word& curr_word = graph[word];
        vector< pair<string, size_t> >& curr_buckets = curr_word.buckets;

        int bucket_length = curr_buckets.back().second; // size of cumulative sum of frequencies
        unsigned long bucket = (rand() % bucket_length)+1;
        for(unsigned int i = 0; i < curr_buckets.size(); ++i){
            if (curr_buckets[i].second >= bucket){
                word = curr_buckets[i].first;
                sentence.push_back(word);
                break;
            }
        }
        
    }
    if (sentence.size() != length) return "No sentence of length " + std::to_string(length) + " could be generated from word: " + word;
    return SentenceDecoder(sentence);
}

string Graph::HighestGreedySentence(string word, size_t length) {
	string curr = word;
	std::vector<string> sentence;
    size_t num_left = length;

	while (!graph[curr].adjacents.empty() && num_left--) {
		sentence.push_back(curr);
		curr = graph[curr].adjacents.front().first;
	}

    if (sentence.size() != length) return "No sentence of length " + std::to_string(length) + " could be generated from word: " + word;
	return SentenceDecoder(sentence);
}

string Graph::LowestGreedySentence(string word, size_t length) {
	string curr = word;
	std::vector<string> sentence;
    size_t num_left = length;

	while (!graph[curr].adjacents.empty() && num_left--) {
		sentence.push_back(curr);
		curr = graph[curr].adjacents.back().first;
	}
    if (sentence.size() != length) return "No sentence of length " + std::to_string(length) + " could be generated from word: " + word;
	return SentenceDecoder(sentence);
}

string Graph::RandomSentence(string word, size_t length) {
	string curr = word;
	std::vector<string> sentence;
    size_t num_left = length;

	while (!graph[curr].adjacents.empty() && num_left--) {
		sentence.push_back(curr);
        int index = rand() % graph[curr].adjacents.size();
		curr = graph[curr].adjacents[index].first;
	}
    
    if (sentence.size() != length) return "No sentence of length " + std::to_string(length) + " could be generated from word: " + word;
	return SentenceDecoder(sentence);
}
