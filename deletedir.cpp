#include "config.h"
vector<string> d;
vector<string> deletedir(vector<string> &newfile) // takes command from user and uses deleteall to recursively delete all files
{
    unsigned i = 1;
    char* remove;
    int tot;
    unsigned n = newfile.size();
    d.clear();
    while(i<n)
    {
        remove = new char[newfile[i].length()+1];
        strcpy(remove,newfile[i].c_str());
        DIR *f;
        f = opendir(remove);
        if(f)
        {
            tot = rmdir(remove);
            if(tot != 0)
            {
                d.push_back(newfile[i]);
                deletea(newfile[i]);
            }
        }
        else 
        {
            cout<<"Error"<<endl;
        }
        i++;
    } // closing of loop
    return d;
}
void deletea(string pq) // recursively goes in all depth to remove the directories
{
    struct dirent **e;
    struct stat val;
    string p;
    char *pq1 = new char[pq.length()+1];
    strcpy(pq1,pq.c_str());
    char * pq2;
    int tot = scandir(pq1,&e,NULL,alphasort);
     int i = 0;
    while(i<tot)
    {
        p = pq + "/" + e[i]->d_name;
        pq2 = new char[p.length()+1];
        strcpy(pq2,p.c_str());
        if(stat(pq2,&val) <0)
        {
            cout<<"No such Directory"<<endl;
        }
        if(S_ISDIR(val.st_mode) && string(e[i]->d_name) != ".." && string(e[i]->d_name)!=".")
        {
            d.push_back(p);
            deletea(p);
        }
        else 
        {
            if(string(e[i]->d_name)!=".." && string(e[i]->d_name)!=".")
             d.push_back(p);
        }
        i++;
    }// close of while loop
} // close of function
