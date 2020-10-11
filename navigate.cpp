#include "config.h"
#define mc printf("%c[2K",27)
 int r1 = 1;
int  column = 0;
 int cursor = 1;
 int n;
struct dirent **ns;
//Normal Mode navigation utility
int navigate( int n1,struct dirent **ns1,struct termios newsetting, struct termios initial,string root)
{
    char *p;
    char character;
    n = n1;
    stack<string> previousstack;
    stack<string> forwardstack;
    ns = ns1;
    struct winsize wind;
    ioctl(STDOUT_FILENO, TIOCGWINSZ,&wind);
    string present = root;
    string display = "NORMAL MODE";
    previousstack.push(root);
   do
    {
         int last = wind.ws_row;
        printf("%c[%d;%dH",27,last,column);
        cout<<display;
        printf("%c[%d;%dH",27,r1,column);
        character = cin.get(); //when someone presses key left/right/up/down/
        if(character==27)
        {
            character = cin.get();
            character = cin.get();
            if(character == 'A' || character == 'k')
            {
                 --r1;
                 if(r1>=1)
                 {
                     printf("%c[%d;%dH",27,r1,column);
                 }
                 else if(cursor>1 && r1<1)
                 {
                     printf("\033[H\033[J"); //clear screen
                     cursor = cursor-1;
                     if(present == root)
                     {
                         p = new char[root.length()+1];
                         strcpy(p,root.c_str());
                         int n1;
                         if(wind.ws_row-2 >= n+1)
                           n1 = n;
                         else 
                           n1 = wind.ws_row -2; 
                           
                            int i = cursor-1;
                           while(i<=cursor+n1-1)
                           {
                               fileinfo(p,ns[i]->d_name,0);
                               i++;
                           } 
                     }
                     else
                     {
                         string s = present;
                         p = new char[s.length()+1];
                         strcpy(p,s.c_str());
                         int n1;
                         if(n<=wind.ws_row-2)
                           n1 = n;
                         else 
                         n1 = wind.ws_row-2;
                          int i = cursor-1;;
                         while(i<=cursor+n1-1 && i<n)
                         {
                             fileinfo(p,ns[i]->d_name,0);
                             i++;
                         }
                           
                     }
                     r1 = 1;
                     printf("%c[%d;%dH",27,r1,column); // we set cursor position
                 }
                 else
                 {
                     r1 = 1; //if cursor is at 1st position only
                 }
            }
                 
                 else if(character == 'B' || character == 'l')
                   {r1 = r1+1;
                   if(cursor+r1<=n+2 && r1 <= wind.ws_row -1) // if cursor is not at last position
                   {
                       printf("%c[%d;%dH",27,r1,column);

                   }
                   else if(r1>wind.ws_row-1 && cursor+r1<=n+2) // if cursor at last position but not at last window
                   {
                       printf("\033[H\033[J"); //clear screen
                       if(root == present)
                       {
                           p = new char[root.length()+1];
                           strcpy(p,root.c_str());
                           int n1;
                           if(n+1<=wind.ws_row-2)
                           {n1 = n;
                           }
                           else if(n+1>wind.ws_row-2)
                           {n1 = wind.ws_row-2;}
                           int i = cursor;
                           while(i<=cursor+n1)
                           {
                               fileinfo(p,ns[i]->d_name,0);
                               i++;
                           }
                       }
                       else
                       {
                           string pt = present;
                           p = new char[pt.length()+1];
                           strcpy(p,pt.c_str());
                           int n1;
                           if(n+1<=wind.ws_row-2)
                           {
                               n1 = n;
                           }
                           else 
                           {
                                n1 = wind.ws_row-2;

                            }  
                             int i = cursor;
                               while(i<=cursor+n1)
                               {
                                   fileinfo(p,ns[i]->d_name,0);
                                   i++;
                               }
                           }
                           cursor++;
                           r1--;
                           printf("%c[%d;%dH",27,r1,column);
                       }
                       else 
                       {
                           r1 = r1-1;
                       }
                       

                   }
                       
                       else if(character == 'C') //if right arrow key
                       {
                         if(forwardstack.size()>=1)
                         {
                             string pt = forwardstack.top();
                             previousstack.push(pt);
                             printf("\033[H\033[J"); //clear screen
                             forwardstack.pop();
                             
                             char *arr = new char[pt.length()+1];
                             strcpy(arr,pt.c_str());
                             DIR *d = opendir(arr);
                             if(!d)
                             {
                                // nothing happens
                             }
                             else
                             {
                                 present = pt;
                             }
                             printdirectorylist(present,root); // print directory and files
                             cursor = 1;
                             r1 = 1;
                             printf("%c[%d;%dH",27,r1,column);
                           
                         }
                       }
                         
                       else if(character == 'D') //if left arrow key
                       {
                       if(previousstack.size()>=2)
                       {
                            string pt = previousstack.top();
                             forwardstack.push(pt);
                             printf("\033[H\033[J");
                            previousstack.pop();
                            
                            string tq = previousstack.top();
                            char *arr = new char[tq.length()+1];
                            strcpy(arr,tq.c_str());
                            DIR *d = opendir(arr);
                            if(!d)
                            {
                               //Nothing should happen
                            }
                            else
                            {
                                present = tq;
                            }
                            printdirectorylist(present,root);
                            cursor = 1;
                            r1 = 1;
                            printf("%c[%d;%dH",27,r1,column);
                            
                       }
                       }
                   }

            if(character==104 || character==72)
            {
                if(present == root)
                {
                    //nothing happens
                }
                else if(present != root)
                {
                    printf("\033[H\033[J");
                    cursor = 1;
                    previousstack.push(root);
                    for(;forwardstack.empty()==false;)
                    {
                        forwardstack.pop();
                    }
                    
                    present = root;
                    searchresult.clear();
                    printdirectorylist(present,root);
                    r1 = 1;
                    printf("%c[%d;%dH",27,r1,column);
                    cursor = 1;
                }
            }
            else if(character==127)  // If BackSpace key then 
	    {
	    	if(present!=root && searchresult.size()==0)
	    	{
	    		while(!forwardstack.empty())
	    			forwardstack.pop();
	    		cursor=1;
	    		int f=present.find_last_of("/\\");
	    		present=present.substr(0,f);
		    	printf("\033[H\033[J");
		        previousstack.push(present);
	            printdirectorylist(present,root);	// Print directory and files
	            r1=1;
	            printf("%c[%d;%dH",27,r1,column);
	            cursor=1;
	    	}
        }	
          else if(character==58)
          {
              r1 = wind.ws_row;
              printf("%c[%d;%dH",27,r1,column);
              mc;
              cout<<":";
              newsetting = initial;
              newsetting.c_lflag &= ~ICANON;
              tcgetattr(fileno(stdin),&newsetting);
              string getcommand1 = commandMode(wind.ws_row,present,root);
              mc;
              printf("%c[%d;%dH",27,r1,column);
              newsetting = initial;
              newsetting.c_lflag &= ~ICANON;
              newsetting.c_lflag &= ~ECHO;
              tcgetattr(fileno(stdin),&newsetting);
              if(getcommand1 == "")
              {
                  printdirectorylist(present,root);
              }
              else if(getcommand1 != "")
              {
                  if(getcommand1 != "$$")
                  {
                      present = getcommand1;
                      printdirectorylist(present,root);
                  }
                  else if(getcommand1 == "$$")
                   {
                       previousstack.push(present);
                       printsearch();
                   }
              }
          }
            
            else if(character==10)
            {
                if(searchresult.size()>0)
                {
                    string ptq = present;
                     previousstack.push(ptq);
                    present = searchresult[cursor+r1-2];
                   
                    char *temp2 = new char[present.length()+1];
                    strcpy(temp2,present.c_str());
                    struct stat obj;
                    if(stat(temp2,&obj)<0)
                    {
                        cout<<"Error";
                    }
        
                     if(!S_ISDIR(obj.st_mode))
                    {
                        char* arr ;
                        string stq = present;
                        arr = new char[stq.length()+1];
                        strcpy(arr,stq.c_str());
                        int st = open("/dev/null",O_WRONLY);
                        dup2(st,2);
                        close(st);
                        pid_t pid = fork();
                        if(pid == 0)
                        {
                            fflush(stdin);
                            char execname[] = "vi";
                            char *exec_arg[] = {execname, arr,NULL};
                            execv("/usr/bin/vi",exec_arg);
                            
                        }
                        wait(NULL);
                    }
                    else
                    {
                        searchresult.clear();
                        printdirectorylist(present,root);
                    }
                    
                }
                else 
                {
                    struct stat obj;
                    string temp3,temp4;
                    char *temp5;
                    if( string(ns[cursor+r1-2]->d_name) != ".")
                    {
                        temp3 = "/";
                        temp4 = ns[cursor+r1-2]->d_name;
                        temp4 = temp3+temp4;
                        temp3 = present+temp4;
                        present = temp3;
                        for(;forwardstack.empty()==false;)
                        {
                            forwardstack.pop();
                        }
                        temp5 = new char[present.length()+1];
                        previousstack.push(present);
                    }
                    else if(string(ns[cursor+r1-2]->d_name) == "..")
                    {
                        for(;forwardstack.empty()==false;)
                        {
                            forwardstack.pop();
                        }
                        int fc = present.find_last_of("/\\");
                        present = present.substr(0,fc);
                        temp3 = present;
                        temp4 = new char[temp3.length()+1];
                        previousstack.push(temp3);
                    }
                    else
                    {
                        continue;
                    }
                    strcpy(temp5,present.c_str());
                    if(stat(temp5,&obj)<0)
                      {  cout<<"Error"<<endl; //return -1
                    }
                     if( !S_ISDIR(obj.st_mode))
                    {
                        char *brr;
                        string rtp = temp3;
                        brr = new char[rtp.length()+1];
                        strcpy(brr,rtp.c_str());
                        int f = present.find_last_of("/\\");
                        present = present.substr(0,f);
                        previousstack.pop();
                        int stqp = open("/dev/null",O_WRONLY);
                        dup2(stqp,2);
                        close(stqp);
                        pid_t pid = fork();
                        if(pid == 0)
                        {
                            fflush(stdin);
                            char execname[] = "vi";
                            char *exec_arg[] = {execname,brr,NULL};
                            execv("/usr/bin/vi",exec_arg);
                    
                        }
                        wait(NULL);
                    }
                    else if(string(ns[cursor+r1-2]->d_name)!=".")
                    {
                        printf("\033[H\033[J");
                        cursor = 1;
                        printdirectorylist(present,root);
                        r1 = 1;
                        printf("%c[%d;%dH",27,r1,column);
                    }
                    
                    
                }
                
            }
    } while(character!=81 && character!=113);
          return 0;
        }
        
    
    void printsearch()
    {
        n = searchresult.size();
        int n1;
        n1 = n-1;
        printf("\033[H\033[J");
        cursor = 1;
        r1 = 1;
        printf("%c[%d;%dH",27,r1,column);
         int d = 0;
        while(d<=n1)
        {
            int z = searchresult[d].find_last_of("/\\");
            string path2 = searchresult[d].substr(0,z);
            char *fpath3 = new char[path2.length()+1];
            strcpy(fpath3,path2.c_str());
            char *fname2 = new char[searchresult[d].length()+1];
            strcpy(fname2,searchresult[d].c_str());
            fileinfo(fpath3,fname2,1);
            d++;
        }
        n = n-1;

    }
void printdirectorylist(string present,string root) // For printing list of files and directories
{
	char *path8=new char[present.length()+1];
    strcpy(path8,present.c_str());
    int n1;
    struct winsize wind;	//to get terminal property
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wind);    
	if(present==root)
    {
    	n = scandir(path8, &ns, NULL,alphasort);	//store all files and dirctories into namelist from specified path
    	
    	if(n>0)
    	{
    		if((wind.ws_row-n)==1)
    			n1=n-2;
	    	else if(n<=wind.ws_row-2)
	    		n1=n-2;
	    	else 
	    		n1=wind.ws_row-2;
	    	int i = 0;
            while(i<n-1)
	    	{
	    		if(string(ns[i]->d_name)=="..")
	    		{
	        		int x=i;
	    			for(;x<n-1;x++)
	    			{
	        			ns[x]=ns[x+1];
	        	
	    			}
	    			i--;
	    			break;
	        	}
                i++;
	    	}
	    	 int j = 0;
            while(j<=n1)
	    	{
	    		fileinfo(path8,ns[i]->d_name,0);
                j++;
	    	}
	    	n=n-2;
    	}
    }
    else 
    {
    	n = scandir(path8, &ns, NULL,alphasort);	//store all files and dirctories into namelist from specified path
    	if(n>0)
    	{
    		if(n<=wind.ws_row-2)
	    		n1=n-1;
	    	else 
	    		n1=wind.ws_row-2;
	    	int i = 0;
            while(i<=n1)
	    	{		
	    		fileinfo(path8,ns[i]->d_name,0);
                i++;
	    	}
	    	n--;
        }
    }
}
