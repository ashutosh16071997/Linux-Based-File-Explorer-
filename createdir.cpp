#include "config.h"
#define R S_IRUSR
#define W S_IWUSR
#define X S_IXUSR
#define RG S_IRGRP
#define RW S_IXGRP
#define RX S_IXOTH

int createdir(vector<string> &input)
{
    
    int i = 1;
    int n = input.size();
    string newarg = input[n-1];
    char *create;
    while(i<n-1)
    {
       
        string pq = newarg + "/" + input[i];
         create = new char[pq.length()+1];
         strcpy(create,pq.c_str());
         int val = mkdir(create,R|W|X|RG|RW|RX);
         if(val != 0)
         {
             cout<<endl<<"Invalid Path"<<endl;
         }
         i++;
 
    }
    return 0;
}
