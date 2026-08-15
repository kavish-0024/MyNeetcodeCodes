class Solution {
   public:
    bool isValidSudoku(const vector<vector<char>>& board) {
        bool row[9][9] = {false};
        bool col[9][9] = {false};
        bool box[9][9] = {false};

        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (board[r][c] == '.') continue;

                int num = board[r][c] - '1';
                int boxIndex = (r / 3) * 3 + (c / 3);

                if (row[r][num] || col[c][num] || box[boxIndex][num]) return false;

                row[r][num] = true;
                col[c][num] = true;
                box[boxIndex][num] = true;
            }
        }

        return true;
    }
};