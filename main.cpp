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
        vector<vector<unordered_set<char>>> cands(9, vector<unordered_set<char>>(9, unordered_set<char>()));
        for (size_t i = 0; i < board.size(); i++) {
            for (size_t j = 0; j < board[0].size(); j++) {
                if (board[i][j] == '.') {
                    unordered_set<char> temp;
                    // get existing chars in the row
                    for (size_t k = 0; k < board[0].size(); k++)
                        if (board[i][k] != '.')
                            temp.insert(board[i][k]);
                    // get existing chars in the col
                    for (size_t k = 0; k < board.size(); k++)
                        if (board[k][j] != '.')
                            temp.insert(board[k][j]);
                    // get existing chars in the block
                    for (size_t s = i/3*3; s < (i/3+1)*3; s++)
                        for (size_t t = j/3*3; t < (j/3+1)*3; t++)
                            if (board[s][t] != '.')
                                temp.insert(board[s][t]);
              
                    // get missing chars
                    for (char ch = '1'; ch <= '9'; ch++)
                        if (temp.find(ch) == temp.end())
                            cands[i][j].insert(ch);
                }
                else
                    cands[i][j].insert(board[i][j]);
            }
        }
        // printSudoku(cands);
        // auto before = cands;
        // auto after = update(before);
        // printSudoku(after);
        // while (!equal(after, before)) {
        //     printSudoku(after);
        //     before = after;
        //     after = update(before);
        // }
        auto result = solve(cands);
        // int i = 1;
        for (auto temp : result) {
            // std::cout << "solution " << i << ":\n";
            printSudoku(temp);
            std::cout << std::endl;
        }
    }

  private:
    vector<vector<vector<unordered_set<char>>>> solve(const vector<vector<unordered_set<char>>> & board) {
        vector<vector<vector<unordered_set<char>>>> result;
        
        auto before = board;
        auto after = update(before);
        while (!equal(after, before)) {
            before = after;
            after = update(before);
        }
        if (isComplete(after)) {
            result.push_back(after);
            return result;
        }
        
        for (size_t i = 0; i < after.size(); i++) {
            for (size_t j = 0; j < after[0].size(); j++) {
                if (after[i][j].empty())
                    return result;
            }
        }

        auto idx = std::make_pair(-1,-1);
        for (size_t i = 0; i < after.size(); i++) {
            if (idx.first == -1 && idx.second == -1) {
                for (size_t j = 0; j < after[0].size(); j++) {
                    if (after[i][j].size() == 2) {
                        idx = std::make_pair(i,j);
                        break;
                    }
                }
            }
            else
                break;
        }

        for (auto it = after[idx.first][idx.second].begin(); it != after[idx.first][idx.second].end(); ++it) {
            auto cpy = after;
            cpy[idx.first][idx.second].clear();
            cpy[idx.first][idx.second].insert(*it);
            auto temp = solve(cpy);
            for (auto tmp : temp) {
                result.push_back(tmp);
            }
        }
        return result;
    }    
    
    void printSudoku(const vector<vector<unordered_set<char>>> & cands) {
        for (size_t i = 0; i < cands.size(); i++) {
            for (size_t j = 0; j < cands[i].size(); j++) {
                if (cands[i][j].size() == 1)
                    std::cout << *cands[i][j].begin() << " ";
                else
                    std::cout << ". ";
            }
            std::cout << std::endl;
        }
    }

    vector<vector<unordered_set<char>>> update(const vector<vector<unordered_set<char>>> & board) {
        auto result = board;
        for (size_t i = 0; i < result.size(); i++) {
            for (size_t j = 0; j < result[i].size(); j++) {
                if (result[i][j].size() > 1) {
                    unordered_set<char> temp;
                    for (size_t k = 0; k < result.size(); k++)
                        if (result[k][j].size() == 1)
                            temp.insert(*result[k][j].begin());
                    for (size_t k = 0; k < result[i].size(); k++)
                        if (result[i][k].size() == 1)
                            temp.insert(*result[i][k].begin());
                    for (size_t s = i/3*3; s < (i/3+1)*3; s++)
                        for (size_t t = j/3*3; t < (j/3+1)*3; t++)
                            if (result[s][t].size() == 1)
                                temp.insert(*result[s][t].begin());

                    result[i][j].clear();
                    for (char ch = '1'; ch <= '9'; ch++)
                        if (temp.find(ch) == temp.end())
                            result[i][j].insert(ch);
                }
            }
        }
        return result;
    }

    bool equal(const vector<vector<unordered_set<char>>> & brd1, const vector<vector<unordered_set<char>>> & brd2) {
        for (size_t i = 0; i < brd1.size(); i++) {
            for (size_t j = 0; j < brd1[0].size(); j++) {
                if (brd1[i][j].size() != brd2[i][j].size())
                    return false;
                else {
                    if (!std::equal(brd1.begin(), brd1.end(), brd2.begin()))
                        return false;
                }
            }
        }
        return true;
    }

    bool isComplete(const vector<vector<unordered_set<char>>> & board) {
        for (size_t i = 0; i < board.size(); i++)
            for (size_t j = 0; j < board[0].size(); j++)
                if (board[i][j].size() != 1)
                    return false;
        return true;
    }
};

int main() {
    // vector<std::string> board{
    //     {"53..7...."},
    //     {"6..195..."},
    //     {".98....6."},
    //     {"8...6...3"},
    //     {"4..8.3..1"},
    //     {"7...2...6"},
    //     {".6....28."},
    //     {"...419..5"},
    //     {"....8..79"}
    // };

    // vector<std::string> board{
    //     {"....8.7.."},
    //     {".7..1.86."},
    //     {"..94....5"},
    //     {"5....4.27"},
    //     {".2.....9."},
    //     {"79.2....8"},
    //     {"9....53.."},
    //     {".62.3..1."},
    //     {"..5.4...."}
    // };

    vector<std::string> board{
        {"....6..4."},
        {"4.27..6.."},
        {"1...9...7"},
        {"...6...81"},
        {"8.......5"},
        {"95...7..."},
        {"3...2...9"},
        {"..9..14.3"},
        {".7..8...."}
    };

    solution soln;
    soln.solveSudoku(board);
}
