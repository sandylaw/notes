class Solution
{
public:
    set<string> res;
    void swap(char &a, char &b)
    {
        char temp = a;
        a = b;
        b = temp;
    }
    void search(int begin, string s)
    {
        if (begin >= s.size())
        {
            res.insert(s);
            return;
        }
        for (int i = begin; i < s.size(); i++)
        {
            swap(s[begin], s[i]);
            search(begin + 1, s);
            swap(s[begin], s[i]);
        }
    }
    set<string> permutation(string S)
    {
        res.clear();
        search(0, S);
        return res;
    }
};
