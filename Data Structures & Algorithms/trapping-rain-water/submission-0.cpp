class Solution { 
public: 
    int trap(const vector<int>& height) { 
        int n=height.size();
        if(n==0) return 0;
        
        int x=height[0]; 
        vector<int>prev(n,0),next(n,0); 
        prev[0]=height[0]; 
        for(int i=1;i<n;i++) { 
            x=max(x,height[i]); 
            prev[i]=x; 
        } 
        
        next[n-1]=height[n-1]; 
        x=height[n-1]; 
        for(int i=n-2;i>=0;i--) { 
            x=max(x,height[i]); 
            next[i]=x; 
        } 
        
        int ans=0; 
        for(int i=1;i<n-1;i++) { 
            int h=min(prev[i],next[i]); 
            ans+=h-height[i]; 
        } 
        return ans; 
    } 
};
