//
// Created by user on 28.12.22.
//

#ifndef LAB4_CSVPARSER_H
#define LAB4_CSVPARSER_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <climits>
using namespace std;

template <typename T>
T format(string element);

template <>
string format(string element);

template <typename T, T... S, typename F>
constexpr void for_sequence(std::integer_sequence<T, S...> V, F&& f);

template<typename... Args>
ostream& operator<<(ostream& os, tuple<Args...> const& t);


template <typename... Ts>
class CSVParser{
public:
    CSVParser(ifstream& file, int skip_lines);

    class ReadLineIterator {
    public:
        tuple<Ts...> tuple_result;
        ifstream* ifs{};
        string line;
        int cur_line{};

        ReadLineIterator() = default;
        explicit ReadLineIterator(ifstream* ifs);

        bool operator!=(ReadLineIterator& other);
        ReadLineIterator& operator++(){ return *this; };

        tuple<Ts...> operator*();
    };

    ReadLineIterator begin(){ return ReadLineIterator(file); };
    ReadLineIterator end(){ return ReadLineIterator(); };

private:
    static ifstream* file;
    int skip_lines;

    bool is_empty(ifstream& file);
    void check_file(ifstream& file);
};


#endif //LAB4_CSVPARSER_H
