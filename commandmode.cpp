#include "config.h"
string home,present;
vector<string> searchresult;
void MoveCursor(int row, int column) // For moving cursor to specified position
{
    printf("%c[2K",27);
    printf("%c[%d;%dH",27,row,column);
    cout<<":";
}
string stringprocess(string filename) //To process for relative/absolute path
{
    if(filename[0] == '/')
    {
        if(filename != "/")
         {
             filename = home + filename;
         }
         else
         {
             filename = filename.substr(1,filename.length());
             filename = home + filename;
         }
         
    }
    else if(filename[0] == '.')
    {
        filename = filename.substr(1,filename.length());
        filename = present + filename;
    }
    else if(filename[0] == '~')
    {
        filename = filename.substr(1,filename.length());
        filename = home + filename;
 
    }
    else
    {
        filename = present + "/" + filename;
    }
     return filename;   
}
string commandMode(int row,string presentpath,string root)
{
    string command = "";
    home = root;
    present = presentpath;
    int column = 0;
    char ch;
    vector<string>newfile;
    string s = "";
    do
    {
        command = "";
        while((ch=cin.get())!=27 && (ch!= 10))
        {
            cout<<ch;
            if(ch == 127)
            {
                if(command.length()<=1)
                {
                    command = "";
                    MoveCursor(row,column);
                    cout<<command;
                        
                }
                else
                {
                    command = command.substr(0,command.length()-1);
                    MoveCursor(row,column);
                    cout<<command;
                }
                
            }
            else
            command+=ch;
        }
        if(ch == 27)
        {
            return "";
        }
        else
        {
            unsigned int i = 0;
             int flag = 0;
            for(;i<command.length();i++)
            {
                flag = 0;
                if(command[i] == 32 && newfile.size()==0)
                {
                    newfile.push_back(s);
                    s = "";
                }
                else if(command[i]=='\\')
                {
                    s = s+ command[i+1];
                    i++;
                }
                else if(command[i]==32 && newfile.size()>=1)
                {
                    if(s!="" && s!=" " &&(newfile[0] == "search" || newfile[0] == "create_file" || newfile[0] == "create_dir"))
                    {
                        newfile.push_back(s);
                    }
                    else if(s!="" && s!=" ")
                    {
                        s = stringprocess(s);
                        newfile.push_back(s);
                    }
                    s = "";
                }
                else
                {
                    s = s+command[i];
                    flag = 1;
                }
                
            }
            if(newfile.size()==0)
            {
                cout<<endl<<"Invalid"<<endl;
                cout<<":";
                newfile.clear();
                s ="";
                continue;
            }
            else if(flag == 1 && newfile[0]!="search" && newfile[0]!= "create_dir" && newfile[0]!="create_file" )
            {
                s = stringprocess(s);
                newfile.push_back(s);
            }
            else if(flag == 1)
            {
                newfile.push_back(s);
            }
            if(newfile[0] == "copy") // if command is to copy file
            {
                if(newfile.size()<3)
                {
                    cout<<endl<<"Missing"<<endl<<":";
                }
                else
                {
                    copyfile(newfile);
                    MoveCursor(row,column);
                }
                
            }
            else if(newfile[0] == "move") // if move command is used
            {
                if(newfile.size()<3)
                {
                    cout<<endl<<"Missing"<<endl<<":";
                }
                else
                {
                    move(newfile);
                    MoveCursor(row,column);
                }
                
            }
            else if(newfile[0] == "rename") // if rename command is used
            {
                if(newfile.size()!=3)
                {
                    cout<<endl<<"Missing"<<endl;
                }
                else
                {
                    rename(newfile);
                    MoveCursor(row,column);
                }
                
            }
            else if(newfile[0] == "create_file") // if a new file is to be created
            {
                if(newfile.size()<3)
                {
                    cout<<endl<<"Missing"<<endl<<":";
                }
                else if(newfile.size()>=3)
                {
                    s = stringprocess(newfile[newfile.size()-1]);
                    newfile.pop_back();
                    newfile.push_back(s);
                    createfile(newfile);
                    MoveCursor(row,column);
                }
            }
            else if(newfile[0]=="create_dir") // if a new directory is need to be created
            {
                if(newfile.size()>=3)
                {
                    s = stringprocess(newfile[newfile.size()-1]);
                    newfile.pop_back();
                    newfile.push_back(s);
                    createdir(newfile);
                    MoveCursor(row,column);
                }
                else
                {
                    cout<<endl<<"Missing"<<endl<<":";
                }
                
            }
            else if(newfile[0] == "delete_file") // if a file need to be deleted
            {
                if(newfile.size()<2)
                {
                    cout<<endl<<"Missing"<<endl<<":";
                }
                else if(newfile.size()>=2)
                {
                    deletefile(newfile);
                    MoveCursor(row,column);
                }
            }
            else if(newfile[0] == "delete_dir")  // if a directory need to be deleted
            {
                if(newfile.size()<2)
                {
                    cout<<endl<<"Missing"<<endl<<":";
                }
                else
                {
                    vector<string> pq = deletedir(newfile);
                    if(pq.size()>0)
                    {    int i = pq.size()-1;
                        while(i>=0)
                        {
                            char* p = new char[pq[i].length()+1];
                            strcpy(p,pq[i].c_str());
                            struct stat obj;
                            stat(p,&obj);
                            if(S_ISDIR(obj.st_mode))
                            {
                                vector<string>tq;
                                tq.clear();
                                tq.push_back("abc");
                                tq.push_back(pq[i]);
                                deletedir(tq);
                            }
                            else
                            {
                                vector<string>tq;
                                tq.clear();
                                tq.push_back("abc");
                                tq.push_back(pq[i]);
                                deletefile(tq);
                            }
                            i--;
                        }
                    }
                    MoveCursor(row,column);
                }
                
            }
            else if(newfile[0] == "search") // if a file need to  be searched
            {
                if(newfile.size()!=2)
                {
                    cout<<endl<<"Missing"<<endl<<":";
                }
                else if(newfile.size() == 2)
                {
                    newfile.push_back(present);
                    vector<string>ans = searchfile(newfile);
                    if(ans.size()<=0)
                    {
                        cout<<endl<<"False"<<":";
                    }
                    else
                    {
                        searchresult=ans;
                        string s = "True";
                        return s;
                    }
                    
                }
                
            }
            else if(newfile[0] == "goto")  // if we want to go to a specific directory or file
            {
                if(newfile.size() != 2)
                {
                    cout<<endl<<"Error"<<endl<<":";
                }
                else
                {
                    string path1 = newfile[1];
                    DIR *d;
                    char* temp3  = new char[path1.length()+1];
                    strcpy(temp3,path1.c_str());
                    d = opendir(temp3);
                    if(d)
                    {
                        return path1;
                    }
                    else
                    {
                        cout<<endl<<"Invalid"<<endl<<":";
                    }
                    
                }
                
            }


        }
        newfile.clear();
        s = "";
        
    }while(true);
}
