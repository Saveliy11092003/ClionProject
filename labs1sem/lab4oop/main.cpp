#include "CSVParser.h"

int main(){
    ifstream file("/home/user/CLionProjects/lab4oop/file");
    CSVParser<long int, string, string> parser(file, 0 /*skip first lines count*/);
    for (tuple<long int, string, string> rs : parser) {
        cout<<rs<<endl;
    }
}
