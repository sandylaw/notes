#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
class DesktopFile
{
    public:
        DesktopFile(){}
        ~DesktopFile(){}
        int run();
        void set_file_path(string file_path)
        {
            desk_file=file_path;
            desk_flag=true;
        }
        void set_exec_para(string sub_para)
        {
            para.push_back(sub_para);
            exec_flag=true;
        }
        void set_name()
        {
            name_flag=true;
        }
        void set_icon()
        {
            icon_flag=true;
        }
    private:
        bool print_name();
        bool print_icon();
        bool check_deskfile();
        bool exec_desktop();
        vector<string> split(const string &str,const char delim)
        {
            vector<string> res;
            istringstream iss(str);
            string temp;
            while(getline(iss,temp,delim))
            {
                res.emplace_back(temp);
            }
            return res;
        }
        bool desk_flag=false;
        bool name_flag=false;
        bool icon_flag=false;
        bool exec_flag=false;
        string desk_file;
        string desk_icon;
        string desk_exec;
        vector<string> allname;
        vector<string> para;
};
int DesktopFile::run()
{
    if(desk_flag)
    {
        if(!check_deskfile())
            return 1;
    }
    else
    {
        cout<<"Please set desktop file"<<endl;
        return 1;
    }
    if(name_flag)
    {
        if(!print_name())
            return 1;
    }
    if(icon_flag)
    {
        if(!print_icon())
            return 1;
    }
    if(exec_flag)
    {
        if(!exec_desktop())
            return 1;
    }
    return 0;
}
bool DesktopFile::check_deskfile()
{
    string check_str=desk_file.substr(desk_file.find_last_of('.')+1);
    if(check_str!="desktop")
    {
        cout<<"it's not desktop file"<<endl;
        return false;
    }
    ifstream fin(desk_file);
    if(!fin)
    {
        cout<<"desktopfile do not exist"<<endl;
        return false;
    }
    string line;
    while(getline(fin,line))
    {
        if(line.find("Name")==0)
        {
            auto right_value=split(line,'=').back();
            allname.push_back(right_value);
        }
        if(line.find("Icon")==0)
        {
            desk_icon=split(line,'=').back();
        }
        if(line.find("Exec")==0)
        {
            desk_exec=split(line,'=').back();
            desk_exec=split(desk_exec,' ').back();
            para.emplace(para.begin(),desk_exec);
        }
    }
    desk_flag=true;
    return 0;
}
bool DesktopFile::print_name()
{

}
