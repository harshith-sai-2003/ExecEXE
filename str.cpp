#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <istream>
#include <string>
#include <stdio.h>
using namespace std::literals;

int main(){
    char buffer[128];
    std::string out, prev, curr, query, resp;
    std::string executablePath = "main.exe";
    std::string outPath = "ye.txt";
    FILE* pipe = _popen(executablePath.c_str(), "r");
    std::fstream outputFile(outPath);

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        //RE::ConsoleLog::GetSingleton()->Print(buffer);
        //out += buffer;
        outputFile << buffer;
        std::cout << buffer << std::endl;
    }
    outputFile.close();
    std::fstream read;
    //read.open(outPath.c_str(),std::ios::in);
    if (read.is_open()) {
        while (getline(read, out)) {
            if (!curr.empty()) 
                prev = curr;
            curr = out;
            if (curr.substr(0, 3) == "Bot") {
                query = prev;
            }
            if (!query.empty()) 
                resp += curr;
        }
    }
    read.close();
    std::cout<<query+"\n"+resp<<std::endl;
    return 0;
}