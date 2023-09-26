//
// Created by user on 24.12.22.
//

#ifndef LAB4_CSV_H
#define LAB4_CSV_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <list>
#include <map>
#include <unordered_map>
using namespace std;

template <typename T>                           // data formatting
T format(string element);

template <>
int format(string element);

template <>
float format(string element);

template <>
double format(string element);

template <>
bool format(string element);

template <>
string format(string element);

template <typename T, T... S, typename F>
constexpr void for_sequence(std::integer_sequence<T, S...>, F&& f) {
    (void(f(std::integral_constant<T, S>{})), ...);
}

template<typename... Args>                          // tuple output
ostream& operator<<(ostream& os, tuple<Args...> const& t) {
    bool first = true;
    apply([&](auto&&... args){ ((os << (first ? "" : ", ") << args, first = false), ...); }, t);
    return os;
}

template <typename... Ts>
class CSVParser{
public:

    CSVParser(ifstream& file){
        this->file = &file;
    }

    struct ReadLineIterator {
        tuple<Ts...> tuple_result;
        ifstream* ifs;
        string line;

        ReadLineIterator() { }
        ReadLineIterator(ifstream* ifs){ this->ifs = ifs; }
        bool operator!=(ReadLineIterator& other) { return !(ifs->eof()); }
        ReadLineIterator& operator++() { return *this; }

        tuple<Ts...> operator*() {
            getline(*ifs, line);

            stringstream ss_line(line); string element; int row;

            for_sequence(std::make_index_sequence<sizeof... (Ts)>{}, [&](auto i) {
                if (getline(ss_line, element, ',')) {
                    auto tuple_i = std::get<i>(tuple_result); // using local variable `i` as constexpr
                    row++;
                    decltype(tuple_i) x;
                    try { std::get<i>(tuple_result) = format<decltype(tuple_i)>(element); }
                    catch (const std::invalid_argument& e) { cout << "Exc bad type in row: " << row << " line:" << "TODO LINE NUM" << endl; }
                }

            });

            return tuple_result;
        }
    };

    ReadLineIterator begin(){ return ReadLineIterator(file); }

    ReadLineIterator end(){ return ReadLineIterator(); }

private:
    ifstream* file;
};

#endif //LAB4_CSV_H
