class Solution {
public:
    bool checkInclusion(string s1, string s2) 
    {
        if(s1.size()>s2.size())
        return false;

        array<int,26>freq1={0};
        array<int,26>freq2={0};
        for(auto &it:s1)
        {
            freq1[it-'a']++;
        }
        for(int i=0;i<s1.size();i++)
        {
            freq2[s2[i]-'a']++;
        }
        if(freq1==freq2)
        return true;

        int i=0;
        for(int j=s1.size();j<s2.size();j++)
        {
            freq2[s2[i]-'a']--;
            freq2[s2[j]-'a']++;
            i++;

            if(freq1==freq2)
            return true;
        }
        return false;
    }
};
