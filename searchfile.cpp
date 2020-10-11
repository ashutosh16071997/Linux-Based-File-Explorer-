#include "config.h"
vector<string> result;
vector<string> searchfile(vector<string> &newfile) //Accepts arguments from command mode to search file
{
    string a = newfile[1];
    string b = newfile[2];
    result.clear();
    findA(a,b);
    string ans;
    if(result.size()>0)
    {
        ans = "True";
        result.push_back(ans);

    }
    else
    {
        ans = "FALSE";
        result.push_back(ans);
 
    }
    return result;
}
void findA(string a,string b) // Recursively searches for each and every file
{
    char *path1 = new char[a.length()+1];
    strcpy(path1,a.c_str());
    struct dirent **ns;
    struct stat obj;
    int tot = scandir(path1,&ns,NULL,alphasort);
    int i = 0;
    while(i<tot)
    {
        string newarg = a + "/" + ns[i]->d_name;
        char *np = new char[newarg.length()+1];
        strcpy(np,newarg.c_str());
        if(stat(np,&obj)<0)
        {
            cout<<"NO SUCH DIRECTORY"<<endl;
        }
        if(S_ISDIR(obj.st_mode) && string(ns[i]->d_name)!= ".." && string(ns[i]->d_name)!=".")
        {
            if(string(ns[i]->d_name) == b)
            {
                result.push_back(newarg);
            }
            findA(newarg,b);
        }
        else
        {
            if(string(ns[i]->d_name)!="." && string(ns[i]->d_name)!="..")
            {
                if(string(ns[i]->d_name) == b)
                result.push_back(newarg);
            }
        }
        i++;
    }
}