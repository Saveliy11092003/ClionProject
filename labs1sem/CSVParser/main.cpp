//
// Created by user on 24.12.22.
//
#include"CsvParser_dir/Csv.h"

int main(){
   ifstream file("/home/user/CLionProjects/lab4oop/file");
    CSVParser<int, float, string> parser(file);
    for (tuple<int, float, string> rs : parser) {
        cout<<rs<<endl;
    }
}
