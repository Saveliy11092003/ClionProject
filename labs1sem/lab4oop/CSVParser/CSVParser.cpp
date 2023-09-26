//
// Created by user on 28.12.22.
//

#include "CSVParser.h"

using namespace std;

template <typename T>
T format(string element) { return (T) stod(element); }

template <>
string format(string element) { return element; }

template <typename T, T... S, typename F>
constexpr void for_sequence(std::integer_sequence<T, S...> V, F&& f) {
    (void(f(std::integral_constant<T, S>{})), ...);
}

template<typename... Args>
ostream& operator<<(ostream& os, tuple<Args...> const& t) {
    bool first = true;
    apply([&](auto&&... args){ ((os << (first ? "" : ", ") << args, first = false), ...); }, t);
    return os;
}

template<typename ... Ts>
    CSVParser<Ts...>::CSVParser(ifstream& file, int skip_lines){
        this->file = &file;
        this->skip_lines = skip_lines;
        check_file(*(this->file));
        for(int i = 0; i < skip_lines; i++) {
            (*(this->file)).ignore(LONG_MAX, '\n');
        }
    }

template<typename... Ts>
CSVParser<Ts...>::ReadLineIterator::ReadLineIterator(ifstream* ifs){ this->ifs = ifs; cur_line = 0; }

template<typename... Ts>
bool CSVParser<Ts...>::ReadLineIterator:: operator!=(ReadLineIterator& other) { return !(ifs->eof()); }

template<typename... Ts>
tuple<Ts...> CSVParser<Ts...>::ReadLineIterator:: operator*() {
    getline(*ifs, line);
    cur_line++;
    stringstream ss_line(line); string element; int cur_row = 0;
    for_sequence(std::make_index_sequence<sizeof... (Ts)>{}, [&](auto i) {
        if (getline(ss_line, element, ',')) {
            auto tuple_i = std::get<i>(tuple_result);
            using subtype = decltype(tuple_i);
            auto& tuple_i_ref = std::get<i>(tuple_result);
            cur_row++;
            try { tuple_i_ref = format<subtype>(element); }
            catch (const std::invalid_argument& e) { throw std::invalid_argument("Bad type at line: " + to_string(cur_line) + " and row: " + to_string(cur_row)); } //exception throws based on new line iteration (not including skipped lines)
        } });
    cur_row = 0;
    return tuple_result;
}

template<typename... Ts>
bool CSVParser<Ts...>:: is_empty(ifstream& file){ return file.peek() == ifstream::traits_type::eof(); }
template<typename... Ts>
void CSVParser<Ts...>::check_file(ifstream& file){ if(!file.is_open() || is_empty(file)) { cout << "File is empty of does not exist" << endl; exit(0); } }
