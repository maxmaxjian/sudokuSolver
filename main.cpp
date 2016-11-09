#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <utility>
#include <unordered_set>

using std::vector;
using std::unordered_set;

class solution {
public:
  void solveSudoku(const std::vector<std::string> & board) {
    vector<vector<unordered_set<char>>> cands(9, vector<unordered_set<char>>(9, unordered_set<char>{'1','2','3','4','5','6','7','8','9'}));
    for (size_t i = 0; i < board.size(); i++) {
      for (size_t j = 0; j < board[0].size(); j++) {
	
      }
    }
  }
};

int main() {
  
}
