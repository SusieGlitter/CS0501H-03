#include <iostream>
#include "shell.hpp"
void print(int argc,char** argv){
    for(int i=0;i<argc;++i)
        std::cout<<i<<": "<<argv[i]<<std::endl;
}
int main(){
    final::shell shell;
    shell.run(0,"echo 'Hello,world'",print);
    shell.subprocessExit(0,0);
    return 0;
}