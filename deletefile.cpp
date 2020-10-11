#include "config.h"

int deletefile(vector<string> &newfile) // it takes argument and delete file
{    unsigned i = 1;
    char *removefile;
     unsigned n = newfile.size();
    while(i<n)
    {
        removefile = new char[newfile[i].length()+1];
        strcpy(removefile,newfile[i].c_str());
        int tot = remove(removefile);
        if(tot != 0)  // checking if remove is working or not
        {
            cout<<endl<<"File deleted"<<endl;
        }
        i++;
    }
    return 0;
}
