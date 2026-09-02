// class Solution {
// public:
//     int dx[4]={0,1,0,-1};
//     int dy[4]={1,0,-1,0};
    
//     bool f(int r, int c, vector<vector<char>>& board, string &word, string& temp, vector<vector<int>>& vis)
//     {
//         temp += board[r][c];
//         vis[r][c] = 1;
        
//         if(word == temp) return true;
        
//         if(temp.size() > word.size() || temp.back() != word[temp.size()-1]) {
//             vis[r][c] = 0;
//             temp.pop_back();
//             return false;
//         }

//         for(int i=0; i<4; i++)
//         {
//             int nr = r + dx[i];
//             int nc = c + dy[i];

//             if(nr<0 || nc<0 || nr>=board.size() || nc>=board[0].size() || vis[nr][nc])
//                 continue;
//             else
//                 if (f(nr, nc, board, word, temp, vis)) return true; 
//         }
        
//         vis[r][c] = 0;
//         temp.pop_back();
        
//         return false;
//     }
    
//     bool exist(vector<vector<char>>& board, string word) 
//     {
//         int n = board.size();
//         int m = board[0].size();
//         vector<vector<int>> vis(n, vector<int>(m, 0));
        
//         for(int i=0; i<n; i++)
//         {
//             for(int j=0; j<m; j++)
//             {
//                 if(board[i][j] == word[0]) 
//                 {
//                     string temp = "";
//                     if(f(i, j, board, word, temp, vis)) return true;
//                 }
//             }
//         }
//         return false;
//     }
// };

class Solution {
public:
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    
    bool f(int r, int c, vector<vector<char>>& board, const string& word, int idx) {
        if (idx == word.size()) return true;
        
        if (r < 0 || c < 0 || r >= board.size() || c >= board[0].size() || board[r][c] != word[idx]) {
            return false;
        }
        
        char originalChar = board[r][c];
        board[r][c] = '*';
        for (int i = 0; i < 4; i++) {
            if (f(r + dx[i], c + dy[i], board, word, idx + 1)) {
                return true;
            }
        }
        board[r][c] = originalChar;
        
        return false;
    }
    
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        int m = board[0].size();
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == word[0]) {
                    if (f(i, j, board, word, 0)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};