#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<bits/stdc++.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<time.h>
#include<fcntl.h>
#include<termios.h>
#include<pwd.h>
#include<grp.h>
#include<fstream>
#include <sys/ioctl.h>
#include<sys/wait.h>
using namespace std;
extern vector<string> searchresult;	

int fileinfo(char*,char*,int);	
int navigate(int ,struct dirent** ,struct termios ,struct termios ,string ); 
string commandMode( int,string,string); 
int deletefile(vector<string> &);	
int createfile(vector<string> &);	
int createdir(vector<string> &);	
vector<string> deletedir(vector<string> &);	
int rename(vector<string> &);	
string stringprocess(string fname);	
void printdirectorylist(string ,string );	
void deletea(string);	
int copyfile(vector<string> &);	
int copyfile1(string,string);	
void copyall(string,string);	
int move(vector<string> &);		
void findall(string);
void findA(string ,string );	
vector<string> searchfile(vector<string> &);  
void MoveCursor( int,int);	
void printsearch();	
void window_resize(int);
