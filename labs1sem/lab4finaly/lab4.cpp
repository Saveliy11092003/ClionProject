//
// Created by user on 28.12.22.
//
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <climits>
#include "gtest/gtest.h"

using namespace std;

template<typename T>
T format(string element) { return (T) stod(element); }

template<>
string format(string element) { return element; }

template<typename T, T... S, typename F>
constexpr void for_sequence(std::integer_sequence<T, S...>, F &&f) {
    (void(f(std::integral_constant<T, S>{})), ...);
}

template<typename... Ts>
ostream &operator<<(ostream &os, tuple<Ts...> const &t) {
    for_sequence(std::make_index_sequence<sizeof... (Ts)>{}, [&](auto i) {
        auto element = std::get<i>(t); // using local variable `i` as constexpr
        os << element << ((i != sizeof... (Ts) - 1) ? "," : "");
    });
    return os;
}

template<typename... Ts>
class CSVParser {
public:
    CSVParser(ifstream &file, int skip_lines) {
        this->file = &file;
        this->skip_lines = skip_lines;
        check_file(*(this->file));
        for (int i = 0; i < skip_lines; i++)
            (*(this->file)).ignore(LONG_MAX, '\n');
    }

    ifstream *GetFile() {
        return file;
    }

    class ReadLineIterator {
    public:
        tuple<Ts...> tuple_result;
        ifstream *ifs;
        string line;
        int cur_line;

        ReadLineIterator() {}

        ReadLineIterator(ifstream *ifs) {
            this->ifs = ifs;
            cur_line = 0;
        }

        bool operator!=(ReadLineIterator &other) { return !(ifs->eof()); }

        ReadLineIterator &operator++() { return *this; }

        tuple<Ts...> operator*() {
            getline(*ifs, line);
            cur_line++;
            stringstream ss_line(line);
            string element;
            int cur_row = 0;
            for_sequence(std::make_index_sequence<sizeof... (Ts)>{}, [&](auto i) {
                if (getline(ss_line, element, ',')) {
                    auto tuple_i = std::get<i>(tuple_result);
                    using subtype = decltype(tuple_i);
                    auto &tuple_i_ref = std::get<i>(tuple_result);
                    cur_row++;
                    try { tuple_i_ref = format<subtype>(element); }
                    catch (const std::invalid_argument &e) {
                        throw std::invalid_argument(
                                "Bad type at line: " + to_string(cur_line) + " and row: " + to_string(cur_row));
                    } //exception throws based on new line iteration (not including skipped lines)
                }
            });
            cur_row = 0;
            return tuple_result;
        }

        ifstream *GetFileITer() {
            return ifs;
        }
    };

    ReadLineIterator begin() { return ReadLineIterator(file); }

    ReadLineIterator end() { return ReadLineIterator(); }

private:
    ifstream *file;
    int skip_lines;

    bool is_empty(ifstream &file) { return file.peek() == ifstream::traits_type::eof(); }

    void check_file(ifstream &file) {
        if (!file.is_open() || is_empty(file)) {
            cout << "File is empty of does not exist" << endl;
            exit(0);
        }
    }
};
/*
int main() {
    ifstream file("/home/user/CLionProjects/lab4finaly/file");
    CSVParser<long int, string> parser(file, 0 /*skip first lines count);
    for (tuple<long int, string> rs: parser) {
        cout << rs << endl;
    }
}*/

TEST(MyTests, check_format_str) {
    string element = "dlfjal";
    string a = format<string>(element);
    ASSERT_EQ(a, element);
}

TEST(MyTests, check_format) {

    string element1 = "5";
    string element2 = "5.5";

    int a = format<int>(element1);
    short int b = format<short int>(element1);
    long int c = format<long int>(element1);
    double d = format<double>(element2);
    float e = format<float>(element2);

    ASSERT_EQ(a, 5);
    ASSERT_EQ(b, 5);
    ASSERT_EQ(c, 5);
    ASSERT_EQ(d, 5.5);
    ASSERT_EQ(e, 5.5);
}

TEST(MyTests, check_constuctor_csv) {
    ifstream file("/home/user/CLionProjects/lab4finaly/file");
    CSVParser<long int, string> parser(file, 0 /*skip first lines count*/);
    string line1;
    string line2;
    getline(file, line1);
    getline(*parser.GetFile(), line2);
    ASSERT_EQ(line1, line2);
}

TEST(MyTests, check_constuctor_reader_line) {
    ifstream file("/home/user/CLionProjects/lab4finaly/file");
    CSVParser<long int, string>::ReadLineIterator iter(&file);
    string line1;
    string line2;
    getline(file, line1);
    getline(*iter.GetFileITer(), line2);
    ASSERT_EQ(line1, line2);
}

TEST(MyTests, check_constuctor_reader_line_not_equal) {
    ifstream file("/home/user/CLionProjects/lab4finaly/file845928345");
    CSVParser<long int, string>::ReadLineIterator iter(&file);
    CSVParser<long int, string>::ReadLineIterator iter1(&file);
    ASSERT_EQ(1, iter != iter1);
}

TEST(MyTests, check_iter_func) {
    ifstream file("/home/user/CLionProjects/lab4finaly/file");
    CSVParser<long int, string>::ReadLineIterator iter(&file);
    long int a = get<0>(iter.operator*());
    string b = get<1>(iter.operator*());
    ASSERT_EQ(2323, a);
    ASSERT_EQ("white", b);
}