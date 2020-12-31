ool Desktopfile::exec_desktop()
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