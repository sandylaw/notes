class Solution
{
    public:
        vector<string> res;
        void swap(char &a, char&b)
        {
            char temp = a;
            a = b;
            b = temp;
        }
        void search(int begin, string s)
        {
            if(begin >= s.size())
            {
                res.push_back(s);
                return;
            }
            for(int i=begin; i<s.size(); i++)
            {
                swap(s[begin], s[i]);
                search(begin+1,s);
                swap(s[begin], s[i]);
            }
        }
        vector<string> permutation(string S)
        {
            res.clear();
            search(0,S);
            return res;
        }
};
