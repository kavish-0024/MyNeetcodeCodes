class MedianFinder {
   public:
    priority_queue<int> left;
    priority_queue<int, vector<int>, greater<int>> right;
    MedianFinder() {}

    void addNum(int num) {
        left.push(num);
        right.push(left.top());
        left.pop();
        if (right.size() > left.size()) {
            left.push(right.top());
            right.pop();
        }
    }

    double findMedian() {
        double ans=0;
        if(left.size()==0 && right.size()==0)
        return ans;
        if(left.size()==right.size())
        ans=(double)(left.top()+right.top())/2;
        else
        ans=left.top();

        return ans;
        
    }
};
