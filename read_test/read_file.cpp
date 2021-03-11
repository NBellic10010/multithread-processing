#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;
int main() {
    ifstream fd;
    fd.open("file.txt");
    string line;
    char buf[1024];
    int arrivaltime;
    char t[2];
    while(fd.good() && !fd.eof()) {
        fd >> t;
        cout << t << endl;
        memset(buf, 0, 1024);
        fd.getline(buf, 1024);
        cout << buf << endl;
    }
    return 0;
}