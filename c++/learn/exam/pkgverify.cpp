#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
using namespace std;

void print_result(FILE *fp)
{
    char buf[1024];
    if(!fp)
    {
        cout<<"open file pipe failed"<<endl;
        return;
    }
    while(fgets(buf,1024,fp)!=nullptr)
    {
        string line(buf);
        if(line.back()=='\n')
            line.pop_back();
        if(line=="/.")
            continue;
        struct stat sa;
        if(lstat(line.c_str(),&sa)==0)
        {
            if((sa.st_mode & S_IFMT) == S_IFLNK)
            {
                if(access(line.c_str(),F_OK)==-1)
                    cout<<"link of file do not exist: "<<line<<endl;
            }
            if(line.find("/usr/")==0)
            {
                if(sa.st_uid!=0)
                    cout<<"master of file is not root: "<<line<<endl;
            }
        }
        else
        {
            cout<<"file or dir do not exits: " <<line <<endl;
        }
    }
}
int main(int argc, char *argv[])
{
    if(argc==2)
    {
        FILE *fp;
        string cmd="dpkg -L "+ string(argv[1]);
        fp=popen(cmd.c_str(),"r");
        print_result(fp);
        pclose(fp);
    }
    else
    {
        cout<<"arg wrong"<<endl;
    }
    return 0;
}
