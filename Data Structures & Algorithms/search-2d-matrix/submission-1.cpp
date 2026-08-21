class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) 
    {
        int n=matrix.size();
        int m=matrix[0].size();
        int l=0,r=n*m-1;
        while(l<r)
        {
            int mid=l+(r-l)/2;
            int row=mid/m;
            int c=mid%m;
            if(target>matrix[row][c])
            l=mid+1;
            else
            r=mid;
        }
        return matrix[l/m][l%m]==target?true:false;
    }
};
