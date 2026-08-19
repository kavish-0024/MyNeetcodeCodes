class MinStack {
    stack<long long> stk;
    long long min_val;
public:
    MinStack() {}
    
    void push(int val) {
        if (stk.empty()) {
            stk.push(val);
            min_val = val;
        } else if (val >= min_val) {
            stk.push(val);
        } else {
            stk.push(2LL * val - min_val);
            min_val = val;
        }
    }
    
    void pop() {
        if (stk.empty()) return;
        
        if (stk.top() < min_val) {
            min_val = 2LL * min_val - stk.top();
        }
        stk.pop();
    }
    
    int top() {
        if (stk.top() < min_val) {
            return min_val; 
        }
        return stk.top();
    }
    
    int getMin() {
        return min_val;
    }
};