#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sstream>
#include <fstream>
using namespace std;
class Desktopfile
{
public:
    Desktopfile() {}
    ~Desktopfile() {}
    int run_Paramter();
    void set_desktopfile_path(const string &file_path)
    {
        m_desktopfile = file_path;
        m_bsetDesktop = true;
    }
    void set_desktop_exec_paramter(string subpara);
    void set_bNodeName(bool bNodeName)
    {
        m_bNodeName = bNodeName;
    }
    void set_bNodeicon(bool bNodeicon)
    {
        m_bNodeicon = bNodeicon;
    }
    void set_bNodeexec(bool bNodeexec)
    {
        m_bNodeexec = bNodeexec;
    }

private:
    bool print_desktopname();
    bool print_desktopicon();
    bool check_desktopfile();
    bool exec_desktop();
    vector<string> split(const string &str, const char delim);
    bool m_bsetDesktop = false;
    bool m_bNodeName = false;
    bool m_bNodeicon = false;
    bool m_bNodeexec = false;
    string m_desktopname;
    string m_desktopfile;
    string m_desktopicon;
    string m_desktopexec;
    vector<string> m_allname;
    vector<string> m_supar;
};
int Desktopfile::run_Paramter()
{
    if (m_bsetDesktop)
    {
        if (!check_desktopfile())
            return 1;
    }
    if (m_bNodeName)
    {
        if (!print_desktopname())
            return 1;
    }
    if (m_bNodeicon)
    {
        if (!print_desktopicon())
            return 1;
    }
    if (m_bNodeexec)
    {
        exec_desktop();
    }
    return 0;
}
void Desktopfile::set_desktop_exec_paramter(string subpara)
{
    m_supar.push_back(subpara);
    m_bNodeexec = true;
}
bool Desktopfile::check_desktopfile()
{
    string suffixstr = m_desktopfile.substr(m_desktopfile.find_last_of('.') + 1); //获取文件后缀
    if (suffixstr != "desktop")
    {
        cout << "It's not a desktop file" << endl;
        return false;
    }
    ifstream fin(m_desktopfile);
    if (!fin)
    {
        cout << "The desktop file don't exist." << endl;
        return false;
    }
    string line;
    while (getline(fin, line))
    {
        if (line.find("Name") == 0)
        {
            auto right_value = split(line, '=').back();
            m_allname.push_back(right_value);
        }
        if (line.find("Exec") == 0)
        {
            m_desktopexec = split(line, '=').back();
            m_desktopexec = split(m_desktopexec, ' ').front();
            m_supar.emplace(m_supar.begin(), m_desktopexec);
        }
        if (line.find("Icon") == 0)
        {
            m_desktopicon = split(line, '=').back();
        }
    }
    m_bsetDesktop = true;
    return true;
}
bool Desktopfile::print_desktopname()
{

    if (!m_allname.empty())
    {
        for (auto rowName : m_allname)
        {
            string resname;
            for (auto tmp : rowName)
            {
                if (tmp == '"' || tmp == ';') //去除不合法字符
                    continue;
                resname.push_back(tmp);
            }
            cout << resname << endl;
        }
    }
    else
    {
        cout << "Desktop file do not have Name info" << endl;
        return false;
    }
    return true;
}
bool Desktopfile::print_desktopicon()
{
    if (!m_desktopicon.empty())
    {
        cout << m_desktopicon << endl;
    }
    else
    {
        cout << "The desktop file do not have icon info" << endl;
        return false;
    }
    return true;
}
bool Desktopfile::exec_desktop()
{
    vector<char *> temp;
    for (auto const &a : m_supar)
    {
        temp.emplace_back(const_cast<char *>(a.c_str()));
    }
    temp.emplace_back(nullptr);
    int result = execvp(m_desktopexec.data(), temp.data());
    if (result == -1)
    {
        cout << "Exec program failed" << endl;
        return false;
    }
    return true;
}
//拆分字符串
vector<string> Desktopfile::split(const string &str, const char delim)
{
    vector<string> res;
    istringstream iss(str); //从string对象str中读取字符
    string temp;
    while (getline(iss, temp, delim))
    //     istream& getline ( istream &is , string &str , char delim );
    // 其中，istream &is 表示一个输入流，譬如cin；
    // string&str表示把从输入流读入的字符串存放在这个字符串中（可以自己随便命名，str什么的都可以）；
    // char delim表示遇到这个字符停止读入，在不设置的情况下系统默认该字符为'\n'，也就是回车换行符（遇到回车停止读入）。
    {
        res.emplace_back(temp);
    }
    return res;
}

int main(int argc, char *argv[])
{
    Desktopfile df;
    int opt;
    const char *optstring = "d:nie:";
    while ((opt = getopt(argc, argv, optstring)) != -1)
    {
        switch (opt)
        {
        case 'd':
            df.set_desktopfile_path(string(optarg));
            break;
        case 'n':
            df.set_bNodeName(true);
            break;
        case 'i':
            df.set_bNodeicon(true);
            break;
        case 'e':
            df.set_desktop_exec_paramter(optarg);
            while (optind < argc)
            {
                df.set_desktop_exec_paramter(argv[optind++]);
            }
            break;
        default:
            cout << "Something wrong";
            break;
        }
    }
    return df.run_Paramter();
}
