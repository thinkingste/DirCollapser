//
//  main.cpp
//  DirCollapser
//
//  Created by Stephanus Adi on 10/15/15.
//

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <vector>

using namespace std;
using namespace boost::filesystem;

int copyFileFromSourceToTarget(const char *source, const char *target){
    path sourceDir(source);
    path targetDir(target);
    path targetPath;
    if (!exists(sourceDir)) throw "Source directory not found";
    if (!is_directory(sourceDir)) throw string(source)+" is not a directory";
    
    recursive_directory_iterator recursive_itr(sourceDir);
    while (recursive_itr != recursive_directory_iterator())
    {
        if (is_regular_file(recursive_itr->path())){
            cout << recursive_itr->path().string() << endl;
            targetPath=targetDir/path(recursive_itr->path().filename());
            copy_file(recursive_itr->path(), targetPath, copy_option::overwrite_if_exists);
        }
        ++recursive_itr;
    }
    return 0;
}

void displayHelp(){
    cout << "Usage: DirCollapser [options] source_directory target_directory" << endl
    << "Options:" << endl
    << "-h or --help            Display this help messages" << endl
    << "--exclude [file_name]   Exclude the file from copied into target_directory" << endl;
}

int main(int argc, char *argv[])
{
    
    if (argc<2){
        cout << "ERROR: No argument found." << endl;
        displayHelp();
        return 0;
    }
    
    // Scan through arguments list.
    // If invalid arguments were found, display error and help message
    bool isDisplayHelp=false;
    //bool isReplaceAllFile=false;
    string sourceDir="";
    string targetDir="";
    
    for (int i=1; i<argc && !isDisplayHelp; i++){
        if (strcmp(argv[i],"-h")==0 ||strcmp(argv[i],"--help")==0){
            isDisplayHelp=true;
        }else{
              if (strncmp(argv[i],"-",1)==0){
                  cout << "ERROR: Invalid options argument found: " << argv[i] << endl;
                  isDisplayHelp=true;
              } else if (i==argc-2){
                  sourceDir=argv[i];
                  cout << "source directory:" << sourceDir << endl;
              } else if (i==argc-1){
                  targetDir=argv[i];
                  cout << "target directory:" << targetDir << endl;
              }
          }
    }
    
    if (isDisplayHelp){
        displayHelp();
        return 0;
    }
    
    if (sourceDir==""){
        cout << "ERROR: source_directory argument not found." << endl;
        return 0;
    }
    
    if (targetDir==""){
        cout << "ERROR: target_directory argument not found." << endl;
        return 0;
    }
    
    int fileCount=0;
    try{
        fileCount=copyFileFromSourceToTarget(sourceDir.c_str(), targetDir.c_str());
    }catch (const char *msg){
        cout << "ERROR: " << msg << endl;;
    }
    return 0;
}