#include "config.h"
int rename(vector<string> &newfile)  //accepts files from command and rename it
{   
    char *n2 = new char[newfile[2].length()+1];
    char* n1 = new char[newfile[1].length()+1];
    strcpy(n2,newfile[2].c_str());
    strcpy(n1,newfile[1].c_str());
    int tot = rename(n1,n2);
    if(tot != 0)
    {
        cout<<endl<<"No such file"<<endl;
    }
    return 0;
}
