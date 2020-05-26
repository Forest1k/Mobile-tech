#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "mobile.cpp"
#include "net.cpp"
#include <unistd.h>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[]) {
    int rez = 0;
    string internetname;
    string mobilename;
    while ( (rez = getopt(argc, argv, "I:M:")) != -1){
        switch(rez){
            case 'I':
                internetname = optarg;
                break;
            case 'M':
                mobilename = optarg;
                break;
            case '?':
                printf("ERROR in arguments");
                return 1;
        }
    }
    net(internetname);
    mobile(mobilename);

    return 0;
}