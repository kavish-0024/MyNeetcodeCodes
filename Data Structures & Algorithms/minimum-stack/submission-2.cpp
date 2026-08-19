class MinStack {
public:
    stack<int>stk,minstk;
    MinStack() {
        
    }
    
    void push(int val) 
    {
        stk.push(val);
        if(minstk.empty() || minstk.top()>=val)
        minstk.push(val);
    }
    
    void pop() 
    {
        int x=stk.top();
        stk.pop();

        if(!minstk.empty() && minstk.top()==x)
        minstk.pop();
    }
    
    int top() {
        return stk.top();
    }
    
    int getMin() {
        return minstk.top();
    }
};
