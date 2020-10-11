#include "config.h"

int fileinfo(char *p , char *n , int c)  //Printing of all file info like permission/size etc
{
   
    register struct group *g;
    register struct passwd *pw;
    struct stat obj;
    char *fn;
    register uid_t id1;
    register gid_t id2;
    double tot;
   
   
    if(c == 0)
    {
        string pq = string(p) + "/" + string(n);
        fn = new char[pq.length()+1];
        strcpy(fn,pq.c_str());
    }
    else
     {
        string pq = string(n);
        fn = new char[pq.length()+1];
        strcpy(fn,pq.c_str());
    }
    if(stat(fn ,&obj) < 0)
    {
        cout<<"Error Criteria Approached"<<endl;
    }
    if(S_ISDIR(obj.st_mode) != 0) //if it is a directory
      {
          cout<<"d";
      }   
    else
      {
          cout<<"-";
      }
    if((obj.st_mode & S_IRUSR) != 0) // if the user has read permission
    {
        cout<<"r";
    }
    else
    {
        cout<<"-";
    }
    if((obj.st_mode & S_IWUSR) != 0) // if the user has write permission
     {
         cout<<"w";
     }
     else
     {
         cout<<"-";
     }
    if((obj.st_mode & S_IXUSR) != 0) // if the user has execute permission
    {
        cout<<"x";
    }
    else
    {
        cout<<"-";
    }
    if((obj.st_mode & S_IRGRP) != 0) // if the group has read permission
    {
        cout<<"r";
    }  
    else
    {
        cout<<"-";
    }
    if((obj.st_mode & S_IWGRP) != 0) // if the group has write permission
    {
        cout<<"w";
    }
    else
    {
        cout<<"-";
    }
    if((obj.st_mode & S_IXGRP) != 0) // if the group has execute permission
    {
        cout<<"x";
    }
    else
    {
        cout<<"-";
    }
    if((obj.st_mode & S_IROTH) != 0) // if others has read permission
    {
        cout<<"r";
    }
    else
    {
        cout<<"-";
    }
    if((obj.st_mode & S_IWOTH) != 0) // if the others has write permission
    {
        cout<<"w";
    }
    else
    {
        cout<<"-";
    }
    if((obj.st_mode & S_IXOTH) != 0) // if the others has execute permission
    {
        cout<<"x";
    }
    else
    {
        cout<<"-";
    }
    tot = (obj.st_size)/1024.0; // finding the size of file in KB
     printf("\t%10.4f KB",tot);
    id1 = geteuid();
    pw = getpwuid(id1);
    if(pw)
    {
        printf("\t%s",pw->pw_name);
    }
    id2 = obj.st_gid;
    g = getgrgid(id2);
    printf("\t%s",g->gr_name);
    string tq = ctime(&obj.st_mtime); // to find the time of file execution
    printf("\t");
    unsigned int i = 0;
    while(i<tq.length()-1)
    {
        printf("%c",tq[i]);
        i++;
    } 
    printf(" %s",n);
    printf("\n");
    return 0;


}
