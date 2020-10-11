#include "config.h"
#define O O_WRONLY
#define OC O_CREAT
#define R S_IRUSR
#define W S_IWUSR
#define X S_IXUSR
#define RG S_IRGRP
#define WG S_IXGRP
#define XG S_IXOTH
int createfile(vector<string> &newfile)
{
     int n = newfile.size();
    string result = newfile[n-1];
    char *create;
     int i = 1;
    while(i<n-1)
    {
        string s = result + "/" + newfile[i];
        create = new char[s.length()+1];
        strcpy(create,s.c_str());
        int tot = open(create,O|OC,R|W|X|RG|WG|XG);
        if(tot<0)
        {
            cout<<endl<<"WRONG"<<endl;
        }
        i++;
 
    }
    return 0;
}
