#include "config.h"
string root;
int main(int argc,char **argv) //start point
{
    printf("\033[H\033[J");  //for clear screen
    struct dirent **ns;  //for storing list of directories and files
    struct termios initial,newsetting; //for terminal setting
    struct winsize wind; //for terminal properties
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&wind); 
    int n;
    char* path1;
    tcgetattr(fileno(stdin),&initial);
    newsetting = initial;
    newsetting.c_lflag &= ~ICANON; //to revert back the setting
    newsetting.c_lflag &= ~ECHO;  //turn of displaying effect
    if(argc<1)
    {
        exit(EXIT_FAILURE);
    }
    else if(argc == 1)
    {
        n = scandir(".",&ns,NULL,alphasort); //store files and directories from specific path
    }
    else
    {
    
        n = scandir(argv[1],&ns,NULL,alphasort);
    }
    if(n<0)
    {
        perror("scandir");
        exit(EXIT_FAILURE);
    }
    else
    {
        string s;
        if(argc == 1)
        {
            s=".";
            path1  = new char[s.length()+1];
            strcpy(path1,s.c_str()); 
        }
        else
        {
            s = argv[1];
            path1 = new char[s.length()+1];
            strcpy(path1,s.c_str());
        }
        root = s;
        int i = 0;
        while(i<n-1)
        {
            if(string(ns[i]->d_name)=="..")
            {
                int val = i;
                for(;val<n-1;val++)
                {
                    ns[val] = ns[val+1];
                }
                break;
            }
            i++;
        }
        n--;
        int n1;
        if(n<=wind.ws_row-2)
        {
             n1 = n-1;
        }
         else if(n>wind.ws_row-2)
         {
         n1 = wind.ws_row-2;
         }
         int k = 0;
        while(k<=n1)
        {
            fileinfo(path1,ns[i]->d_name,0);
            k++;
        }
        n--;
    }
    if(tcsetattr(fileno(stdin),TCSAFLUSH,&newsetting)!=0)
    {
        fprintf(stderr,"Fail to achieve desired attribute");

    }
    else
    {
        navigate(n,ns,newsetting,initial,root);
    }
    printf("\033[H\033[J");
    cout<<"The End"<<endl;
    tcsetattr(fileno(stdin),TCSANOW,&initial);
    return 0;
    
    
}
