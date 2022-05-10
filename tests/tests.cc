#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "graph.h"
#include <iostream>
#include <string>

TEST_CASE("Highest Weight Sentence - easy", "[easy]") {
  string test;
  Graph g ("tests/non_greedy1.txt");
  
  test = g.HighestWeightSentence("hello", 1);
  REQUIRE(test == "hello.");
  
  test = g.HighestWeightSentence("my", 1);
  REQUIRE(test == "my.");

  test = g.HighestWeightSentence("dear", 1);
  REQUIRE(test == "dear.");

}
TEST_CASE("Highest Weight Sentence - normal", "[normal]"){
  string test;
  Graph g ("tests/non_greedy1.txt");
  
  test = g.HighestWeightSentence("hello", 2);
  REQUIRE(test == "hello my.\n");
 
  test = g.HighestWeightSentence("lovely", 2);
  REQUIRE(test == "lovely people.\n");

  //Test Case in which sentence of size 3 cannot be created
  test = g.HighestWeightSentence("lovely", 3);
  REQUIRE(test == "No sentence of length 3 could be generated from word: lovely");
  
  std::cout << __LINE__ << std::endl;
  test = g.HighestWeightSentence("hello", 3);
  REQUIRE(test == "hello lovely people.\n");
}

TEST_CASE("Highest Greedy Sentence - easy", "[easy]"){
  string test;
  Graph g ("tests/non_greedy1.txt");
  
  test = g.HighestWeightSentence("hello", 1);
  REQUIRE(test == "hello.");
  
  test = g.HighestWeightSentence("my", 1);
  REQUIRE(test == "my.");
  
  test = g.HighestWeightSentence("dear", 1);
  REQUIRE(test == "dear.");
}

TEST_CASE("Highest Greedy Sentence - normal", "[normal]"){
  string test;
  Graph g ("tests/non_greedy1.txt");

  test = g.HighestGreedySentence("lovely", 3);
  REQUIRE(test == "lovely people lovely.\n");

  test = g.HighestGreedySentence("lovely", 4);
  REQUIRE(test == "lovely people lovely people.\n");
  
  test = g.HighestGreedySentence("people", 3);
  REQUIRE(test == "people lovely people.\n");

  test = g.HighestGreedySentence("people", 4);
  REQUIRE(test == "people lovely people lovely.\n");
}

TEST_CASE("Highest Greedy Sentence 2 - normal", "[normal]"){
  string test;
  Graph g2 ("tests/non_greedy2.txt");

  test = g2.HighestGreedySentence("cow", 3);
  REQUIRE(test == "cow sleep cow.\n");

  test = g2.HighestGreedySentence("cow", 4);
  REQUIRE(test == "cow sleep cow sleep.\n");

  test = g2.HighestGreedySentence("rabbit", 3);
  REQUIRE(test == "rabbit sleep cow.\n");

  test = g2.HighestGreedySentence("rabbit", 4);
  REQUIRE(test == "rabbit sleep cow sleep.\n");
}


TEST_CASE("Lowest Greedy Sentence - normal", "[normal]"){
  string test;
  Graph g ("tests/non_greedy1.txt");

  test =  g.LowestGreedySentence("hello", 3);
  REQUIRE(test == "hello lovely people.\n");
  
  test =  g.LowestGreedySentence("my", 4);
  REQUIRE(test == "my dear hello lovely.\n");
  
  test =  g.LowestGreedySentence("dear", 5);
  REQUIRE(test == "dear hello lovely people lovely.\n");
}

// TEST_CASE("Random Sentence", "[normal]"){
//   string test;
//   Graph g("tests/non_greedy1.txt");
//   int size = 4;
//   test = g.RandomSentence("hello", size);
//   REQUIRE(test.size() == size);
//   //Check if each successive element is part of the prior adjacency list
//   for(unsigned int i = 0; i < size -1 ; ++i){
    
//     //word = test[i].
//   }
// }