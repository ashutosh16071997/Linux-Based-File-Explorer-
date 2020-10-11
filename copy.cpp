#include "config.h"
#define R S_IRUSR
#define W S_IWUSR
#define X S_IXUSR
#define RG S_IRGRP
#define XG S_IXGRP
#define XO S_IXOTH
#define O O_RDONLY
#define OW O_WRONLY
#define OC O_CREAT
int copyfile(vector<string> &newfile) //Receives command from command mode as what to copy
{
    int i = 0;
    struct stat obj;
    string d = newfile[newfile.size()-1];
    int n = newfile.size();
    while(i<n-1)
    {
         string s = newfile[i];
         char *pq = new char[newfile[i].length()+1];
         strcpy(pq,s.c_str());
         if(stat(pq,&obj)<0)
         {
             cout<<"Error"<<endl;

         }
         if(S_ISDIR(obj.st_mode)==0)
         {
             int f = newfile[i].find_last_of("/\\");
             newfile[i] = newfile[i].substr(f+1,newfile[i].length());
             string ds = d + "/" + newfile[i];
             copyfile1(s,ds);
         }
         else
         {
             int f = s.find_last_of("/\\");
             string s1 = s.substr(f+1,s.length());
             string s2 = d + "/" + s1;
             char *create = new char[s2.length()+1];
             strcpy(create,s2.c_str());
             mkdir(create,R|W|X|RG|XG|XO);
             string d1 = d + "/" + s1;
             copyall(s,d1);
         }
         i++;
    }
    return 0;
}
void copyall(string s,string d)
{
    char *sc = new char[s.length()+1];
    strcpy(sc,s.c_str());
    struct dirent **ns;
    int tot = scandir(sc,&ns,NULL,alphasort);
    struct stat obj;
    int i = 0;
    while(i<tot)
    {
        string st = s + "/" + ns[i]->d_name;
        char *st1 = new char[st.length()+1];
        strcpy(st1,st.c_str());
        if(stat(st1,&obj)<0)
        {
            cout<<endl<<"Error"<<endl;
        }
        if(S_ISDIR(obj.st_mode) && string(ns[i]->d_name)!=".." && string(ns[i]->d_name)!= ".")
        {
            string pq = d +"/" + ns[i]->d_name;
            char *create = new char[pq.length()+1];
            strcpy(create,pq.c_str());
            mkdir(create,R|W|X|RG|XG|XO);
            copyall(s + "/" + ns[i]->d_name,d + "/" + ns[i]->d_name);

         }
         else 
         { 
             if(string(ns[i]->d_name)!= ".." && string(ns[i]->d_name)!=".")
             copyfile1(s+"/"+ns[i]->d_name,d+"/"+ns[i]->d_name);
         }
         i++;
            
    }
}
int copyfile1(string s,string d) // it recursively goes in depth to copy file
{
    struct stat fstat,fstat1;
    int nr;
    char arr[1024];
    char *cp;
    int in,out;
    cp = new char[s.length()+1];
    strcpy(cp,s.c_str());
    in = open(cp,O);
    char *pt = new char[d.length()+1];
    strcpy(pt,d.c_str());
    out = open(pt,OW|OC,R|W);
    while((nr = read(in,arr,sizeof(arr)))>0)
    {
        write(out,arr,nr);
    }
     if(stat(cp,&fstat)<0)
    {
        cout<<"Error";
    }
    if(stat(pt,&fstat1)<0)
    {
        cout<<"Error";
    }
   
    int tot = chown(pt,fstat.st_uid,fstat.st_gid);
    if(tot!=0)
    {
        cout<<"Error"<<endl;
    }
    tot = chmod(pt,fstat.st_mode);
    if(tot!=0)
    {
        cout<<"Error";
    }
    return 0;
}
