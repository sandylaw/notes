#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
using namespace std;

void print_result(FILE *fp)
{
    char buf[1024];
    if (!fp)
    {
        cout << "Open pipe failed!" << endl;
        return;
    }
    while (fgets(buf, 1024, fp) != nullptr)
    {
        string line(buf);
        if (line.back() == '\n')
            line.pop_back();
        if (line == "/.")
            continue;
        struct stat sb;
        if (lstat(line.c_str(), &sb) == 0)
        {
            if ((sb.st_mode & S_IFMT) == S_IFLNK)
            {
                if (access(line.c_str(), F_OK) == -1)
                {
                    cout << "The file of link do not exist:" << line << endl;
                }
            }
            if (line.find("/usr/") != string::npos)
            {
                if (sb.st_uid != 0)
                    cout << "The master of file is not root" << line << endl;
            }
        }
        else
        {
            cout << "Do not exist :" << line << endl;
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *fp = nullptr;
    if (argc == 2)
    {
        string cmd = "dpkg -L " + string(argv[1]);
        fp = popen(cmd.c_str(), "r");
        print_result(fp);
        pclose(fp);
    }
    else
    {
        cout << "The argument is wrong!" << endl;
    }
    return 0;
}
