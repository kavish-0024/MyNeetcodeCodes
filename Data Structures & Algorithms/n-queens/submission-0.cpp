// class Solution {
// public:
//     int dx[8]={1,-1,2,2,1,-1,-2,-2};
//     int dy[8]={2,2,1,-1,-2,-2,1,-1};
//     void f(int i,int j,vector<string>temp,vector<vector<string>>&ans,int cnt)
//     {
//         int n=temp.size();
//         if(cnt==0)
//         {
//             ans.push_back(temp);
//             return;
//         }
//         for(int k=0;k<8;k++)
//         {
//             int nr=i+dx[k];
//             int nc=j+dy[k];

//             if(nr>=n || nc>=n || nr<0 || nc<0 || temp[nr][nc]=='Q')
//             continue;

//             temp[nr][nc]='Q';
//             cnt--;
//             f(nr,nc,temp,ans,cnt);
//             cnt++;
//             temp[nr][nc]='.';
//         }
//         return;
//     }
//     vector<vector<string>> solveNQueens(int n) 
//     {
//         vector<vector<string>>ans;
//         string s="";
//         for(int i=0;i<n;i++)
//         s+='.';
//         vector<string>temp(n,s);
//         for(int i=0;i<n;i++)
//         {
//             for(int j=0;j<n;j++)
//             {
//                 f(i,j,temp,ans,n);
//             }
//         }
//         return ans;
//     }
// };

class Solution {
public:
    bool isSafe(int row, int col, const vector<string>& board, int n) {
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') return false;
        }
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') return false;
        }
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') return false;
        }
        return true;
    }

    void solve(int row, vector<string>& board, vector<vector<string>>& ans, int n) {
        if (row == n) {
            ans.push_back(board);
            return;
        }
        
        for (int col = 0; col < n; col++) {
            if (isSafe(row, col, board, n)) {
                board[row][col] = 'Q';          
                solve(row + 1, board, ans, n);  
                board[row][col] = '.';          
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> board(n, string(n, '.')); 
        solve(0, board, ans, n);
        return ans;
    }
};
