#include "config.h"
int move(vector<string> &newfile) //take argument from command and movies file/directories
{
    vector<string> pq;
    string final = newfile[newfile.size()-1];
      unsigned  i = 0;
    unsigned  n = newfile.size();
    while(i<n-1)
    {
        pq.clear();
        pq.push_back("copy");
        pq.push_back(newfile[i]);
        copyfile(pq);
        char *v = new char[newfile[i].length()+1];
        strcpy(v,newfile[i].c_str());
        struct stat obj;
        if(stat(v,&obj)<0)
        {
            cout<<"Error"<<endl;
        }
        
     if(S_ISDIR(obj.st_mode))
        {
            pq.clear();
            pq.push_back("delete");
            pq.push_back(newfile[i]);
            vector<string>t = deletedir(pq);
            if(t.size()>0)
            {
                 int j = t.size()-1;
                while(j>=0)
                {
                    char* z = new char[t[j].length()+1];
                    strcpy(z,t[j].c_str());
                    struct stat obj;
                    stat(z,&obj);
                    if(S_ISDIR(obj.st_mode))
                    {
                        vector<string> pq;
                        pq.clear();
                        pq.push_back("abc");
                        pq.push_back(t[j]);
                        deletedir(pq);
                    }
                    else 
                    {
                        vector<string>pq;
                        pq.clear();
                        pq.push_back("abc");
                        pq.push_back(t[j]);
                        deletefile(pq);
                    }
                    j--;
                }
            }
        }
        else 
        {
            pq.clear();
            pq.push_back("delete");
            pq.push_back(newfile[i]);
            deletefile(pq);
        }
        i++;
    }
    return 0;
}
