class Solution {
public:
    bool f(const vector<vector<char>>& board,int r,int c)
    {
        char x=board[r][c];
        for(int i=0;i<9;i++)
        {
            if(board[r][i]==x && i!=c)
            return false;
            if(board[i][c]==x && i!=r)
            return false;
            if(board[3*(r/3)+i/3][3*(c/3)+i%3]==x && (3*(r/3)+i/3)!=r && 
                                                    (3*(c/3)+i%3)!=c)
            return false;
        }
        return true;
    }
    bool isValidSudoku(const vector<vector<char>>& board) 
    {
        int n =board.size();
        int m=board[0].size();
        for(int r=0;r<n;r++)
        {
            for(int c=0;c<m;c++)
            {
                if(board[r][c]!='.')
                {
                    if(f(board,r,c)==false)
                    return false;
                }
            }
        }
        return true;
    }
};
