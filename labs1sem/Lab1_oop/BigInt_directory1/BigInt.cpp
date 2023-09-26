#include <iostream>
#include "BigInt.h"
#include <string>
#include <cstring>

using namespace std;

void BigInt::set_sign(char c) {
    this->znak = c;
}

size_t get_length(int n) {
    size_t k = 0;

    if (n == 0) {
        return 1;
    }

    while (n) {
        n = n / 10;
        k++;
    }

    return k;
}

char digit_to_symbol(int n) {
    return n + '0';
}

int symbol_to_digit(char n) {
    return n - '0';
}

BigInt::BigInt() {
    digit = string(1, '0');
    size = 1;
    znak = '+';
}


BigInt::BigInt(int n) {
    size_t k = get_length(n);
    size = k;
    long long temp = n;
    if (temp < 0) {
        znak = '-';
    } else {
        znak = '+';
    }
    long long int r = 0;
    digit = string(k, '0');
    if (temp < 0) {
        r = temp * (-1);
    } else {
        r = temp;
    }

    for (size_t i = 0; i < k; i++) {
        char v = digit_to_symbol(r % 10);
        digit[i] = v;
        r = r / 10;
    }
}

BigInt::BigInt(string example) {

    int k = 0;
    size_t zeroes = 0;
    while (example[k] == '0') {
        zeroes++;
        k++;
    }
    if (zeroes == example.length()) {
        digit = string(1, '0');
        znak = '+';
        size = 1;
        return;
    }
    if ((example.length() == 2) && (example[0] == '-') && (example[1] == '0')) {
        digit = string(1, '0');
        znak = '+';
        size = 1;
        return;
    }
    string value;
    value = string(example.length() - zeroes, '0');
    value = example.substr(zeroes, example.length());
    if (value[0] == '-') {
        znak = '-';
        size = value.length() - 1;
        digit = string(size, '0');
        for (size_t i = 1; i < value.length(); i++) {
            if (value[i] < '0' || value[i] > '9') {
                throw invalid_argument("invalid number");
            }
            digit[size - i] = value[i];
        }
    } else {
        znak = '+';
        size = value.length();
        digit = string(size, '0');
        for (size_t i = 0; i < size; i++) {
            if (value[size - i - 1] < '0' || value[size - i - 1] > '9') {
                throw invalid_argument("invalid number");
            }
            digit[i] = value[size - i - 1];
        }
    }
}

BigInt::BigInt(const BigInt &other) {
    this->size = other.size;
    this->znak = other.znak;
    digit = string(size, '0');
    for (size_t i = 0; i < size; i++) {
        digit[i] = other.digit[i];
    }
}

string BigInt::get_digit() const {
    return this->digit;
}

size_t BigInt::get_size() const {
    return this->size;
}

char BigInt::get_znak() const {
    return this->znak;
}

BigInt &BigInt::operator=(const BigInt &other) {
    if ((*this) == other) {
        return *this;
    }
    this->digit.clear();
    this->size = other.size;
    this->znak = other.znak;
    this->digit = string(this->size, '0');
    for (size_t i = 0; i < this->size; i++) {
        this->digit[i] = other.digit[i];
    }
    return *this;
}


bool BigInt::operator==(const BigInt &other) const {
    bool first = true;
    for (size_t i = 0; i < this->size; i++) {
        if (this->digit[i] != other.digit[i]) {
            first = false;
            break;
        }
    }
    return (this->size == other.size) && (this->znak == other.znak) && first;
};

bool BigInt::operator!=(const BigInt &other) const {
    BigInt a;
    BigInt b;
    a = *this;
    b = other;
    a = delete_zeroes(a);
    b = delete_zeroes(b);
    bool first = true;
    for (size_t i = 0; i < this->size; i++) {
        if (a.get_digit()[i] != b.get_digit()[i]) {
            first = false;
            break;
        }
    }
    return !((a.size == b.size) && (a.znak == b.znak) && first);
};

bool BigInt::operator<(const BigInt &other) const {
    if (this->znak == '-' && other.znak == '+') {
        return true;
    }
    if (this->znak == '+' && other.znak == '-') {
        return false;
    }
    if (this->znak == '+' && other.znak == '+') {
        if (this->size < other.size) {
            return true;
        } else if (this->size > other.size) {
            return false;
        } else {
            for (size_t i = 0; i < this->size; i++) {
                if (this->digit[size - i - 1] < other.digit[size - i - 1]) {
                    return true;
                }
            }
            return false;
        }
    }

    if (this->znak == '-' && other.znak == '-') {
        if (this->size > other.size) {
            return true;
        } else if (this->size < other.size) {
            return false;
        } else {
            for (size_t i = 0; i < this->size; i++) {
                if (this->digit[size - i - 1] < other.digit[size - i - 1]) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
};

bool BigInt::operator>(const BigInt &other) const {
    if (this->znak == '-' && other.znak == '+') {
        return false;
    }
    if (this->znak == '+' && other.znak == '-') {
        return true;
    }
    if (this->znak == '+' && other.znak == '+') {

        if (this->size > other.size) {
            return true;
        } else if (this->size < other.size) {
            return false;
        } else {
            for (size_t i = 0; i < this->size; i++) {
                if (this->digit[size - i - 1] > other.digit[size - i - 1]) {
                    return true;
                }
            }
            return false;
        }
    }

    if (this->znak == '-' && other.znak == '-') {

        if (this->size < other.size) {
            return true;
        } else if (this->size > other.size) {
            return false;
        } else {
            for (size_t i = 0; i < this->size; i++) {
                if (this->digit[size - i - 1] > other.digit[size - i - 1]) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

bool BigInt::operator<=(const BigInt &other) const {
    return ((*this) < other) || ((*this) == other);
};

bool BigInt::operator>=(const BigInt &other) const {
    return ((*this) > other) || ((*this) == other);
};

BigInt &BigInt::operator++() {
    BigInt a(1);
    *this = *this + a;
    return *this;
};

BigInt BigInt::operator--() {
    BigInt a(1);
    *this = *this - a;
    return *this;
};

const BigInt BigInt::operator++(int) {
    BigInt res = *this;
    BigInt a(1);
    *this = *this + a;
    return res;
};

const BigInt BigInt::operator--(int) {
    BigInt res = *this;
    BigInt a(1);
    BigInt b;
    b = *this;
    *this = b - a;
    return res;
};

BigInt BigInt::operator+() const {
    return *this;
};

BigInt::operator int() const {
    int result = 0;
    int tmp = 1;
    for (size_t i = 0; i < this->size; i++) {
        result += tmp * symbol_to_digit(this->digit[i]);
        tmp *= 10;
    }
    return result;
};

BigInt::operator std::string() const {
    string result;
    if (znak == '-') {
        result = string(this->get_size() + 1, '0');
        result[0] = '-';
        for (size_t i = 0; i < this->size; i++) {
            result[i + 1] = this->digit[(this->size) - 1 - i];
        }
    } else {
        result = string(this->get_size(), '0');
        for (size_t i = 0; i < this->size; i++) {
            result[i] = this->digit[(this->size) - i - 1];
        }
    }

    return result;
};


BigInt::~BigInt() {
    digit.clear();
};


string decimal_to_binary(const BigInt a) {
    string result = string(a.get_size() * 5, '&');
    BigInt tmp;
    BigInt divider_2(2);
    BigInt digit_0(0);
    BigInt digit_1(1);
    BigInt digit_1_(-1);

    int i = 0;
    tmp = a;
    do {
        result[i] = digit_to_symbol(symbol_to_digit(tmp.get_digit()[0]) % 2);
        i++;
        tmp = tmp / divider_2;

    } while (tmp != digit_0 && tmp != digit_1);
    result[i] = tmp.get_digit()[0];

    int amp = 0;
    size_t k = result.length() - 1;
    while (result[k] == '&') {
        amp++;
        k -= 1;
    }
    string value;
    value = string(result.length() - amp, '0');
    value = result.substr(0, result.length() - amp);
    result.clear();
    result = string(value.length(), '0');

    for (size_t g = 0; g < value.length(); g++) {
        result[g] = value[g];
    }
    value.clear();
    return result;
}

bool operator>(string first, string second) {
    if (first[0] == '-' && second[0] != '-') {
        return false;
    }
    if (first[0] != '-' && second[0] == '-') {
        return true;
    }
    if (first[0] != '-' && second[0] != '-') {

        if (first.length() > second.length()) {
            return true;
        } else if (first.length() < second.length()) {
            return false;
        } else {
            for (size_t i = 0; i < first.length(); i++) {
                if (first[first.length() - i - 1] > second[first.length() - i - 1]) {
                    return true;
                }
                if (first[first.length() - i - 1] < second[first.length() - i - 1]) {
                    return false;
                }
            }
        }
    }
}

BigInt operator-(const BigInt &first, const BigInt &second) {
    string temp1, temp2;
    temp1 = string(first.get_size(), '0');
    if (first.get_znak() == '-') {
        temp1 = string(first.get_size() + 1, '0');
        temp1[0] = '-';
        for (size_t i = 0; i < first.get_size(); i++) {
            temp1[i + 1] = first.get_digit()[first.get_size() - 1 - i];
        }
    } else {
        temp1 = string(first.get_size(), '0');
        for (size_t i = 0; i < first.get_size(); i++) {
            temp1[i] = first.get_digit()[first.get_size() - 1 - i];
        }
    }
    if (second.get_znak() == '-') {
        temp2 = string(second.get_size(), '0');
        for (size_t i = 0; i < second.get_size(); i++) {
            temp2[i] = second.get_digit()[second.get_size() - 1 - i];
        }
    } else {
        temp2 = string(second.get_size() + 1, '0');
        temp2[0] = '-';
        for (size_t i = 0; i < second.get_size(); i++) {
            temp2[i + 1] = second.get_digit()[second.get_size() - 1 - i];
        }
    }
    BigInt tmp1(temp1);
    BigInt tmp2(temp2);
    BigInt temp;
    temp = tmp1 + tmp2;
    return temp;
}

BigInt operator+(const BigInt &first, const BigInt &second) {
    char flag = '+';
    if (first.get_znak() == '+' && second.get_znak() == '+') {
        flag = '1';
    }

    if (first.get_znak() == '-' && second.get_znak() == '-') {
        flag = '2';
    }

    if ((first.get_znak() == '+' && second.get_znak() == '-') ||
        (first.get_znak() == '-' && second.get_znak() == '+')) {
        flag = '3';
    }

    if (flag != '3') {
        size_t max_size = max(first.get_size(), second.get_size());
        size_t min_size = min(first.get_size(), second.get_size());
        string temp2;
        string temp3;
        temp2 = string(max_size, '0');
        if (first.get_size() > second.get_size()) {
            temp3 = string(first.get_size(), '0');
            for (size_t i = 0; i < first.get_size(); i++) {
                temp3[i] = first.get_digit()[i];
            }
            for (int v = 0; v < min_size; v++) {
                temp2[v] = second.get_digit()[v];
            }
        } else if (first.get_size() < second.get_size()) {
            temp3 = string(second.get_size(), '0');
            for (size_t i = 0; i < second.get_size(); i++) {
                temp3[i] = second.get_digit()[i];
            }
            for (size_t v = 0; v < min_size; v++) {
                temp2[v] = first.get_digit()[v];
            }
        } else {
            temp3 = string(second.get_size(), '0');
            temp2 = string(first.get_size(), '0');
            for (size_t i = 0; i < second.get_size(); i++) {
                temp3[i] = second.get_digit()[i];
            }
            for (size_t v = 0; v < min_size; v++) {
                temp2[v] = first.get_digit()[v];
            }
        }
        int k = 0;
        string temp1;
        temp1 = string(max_size, '0');
        int d1, d2;
        for (size_t i = 0; i < max_size; i++) {
            d1 = symbol_to_digit(temp2[i]);
            d2 = symbol_to_digit(temp3[i]);
            temp1[max_size - 1 - i] = digit_to_symbol((d1 + d2 + k) % 10);
            k = (d1 + d2 + k) / 10;
        }
        temp2.clear();
        temp3.clear();
        if (k != 0) {
            string temp;
            if (flag == '2') {
                temp = string(max_size + 2, '0');
                temp[0] = '-';
                temp[1] = digit_to_symbol(k);
                for (size_t j = 0; j < max_size; j++) {
                    temp[j + 2] = temp1[j];
                }
                temp1.clear();
                BigInt result(temp);
                result = delete_zeroes(result);
                return result;
            } else {
                temp = string(max_size + 1, '0');
                for (size_t j = 0; j < max_size; j++) {
                    temp[j + 1] = temp1[j];
                }
                temp[0] = digit_to_symbol(k);
                temp1.clear();
                BigInt result(temp);
                return result;
            }
        }
        if (flag == '1') {
            BigInt result(temp1);
            return result;
        } else {
            string result_str = string(temp1.length() + 1, '0');
            result_str[0] = '-';
            for (size_t i = 0; i < temp1.length(); i++) {
                result_str[i + 1] = temp1[i];
            }
            temp1.clear();
            BigInt result(result_str);
            result = delete_zeroes(result);
            return result;
        }
    } else {
        string temp5;
        string temp6;
        if (first.get_znak() == '-') {
            temp5 = string(first.get_size(), '0');
            for (size_t i = 0; i < first.get_size(); i++) {
                temp5[i] = first.get_digit()[i];
            }
            temp6 = string(second.get_size(), '0');
            for (size_t i = 0; i < second.get_size(); i++) {
                temp6[i] = second.get_digit()[i];
            }
        } else {
            temp5 = string(second.get_size(), '0');
            for (size_t i = 0; i < second.get_size(); i++) {
                temp5[i] = second.get_digit()[i];
            }
            temp6 = string(first.get_size(), '0');
            for (size_t i = 0; i < first.get_size(); i++) {
                temp6[i] = first.get_digit()[i];
            }
        }
        string temp7;
        string temp8;
        string temp9;
        char flag2;
        if (temp5 > temp6) {
            temp7 = string(temp5.length(), '0');
            for (size_t i = 0; i < temp5.length(); i++) {
                temp7[i] = temp5[i];
            }
            flag2 = '-';
            temp8 = string(temp5.length(), '0');
            for (size_t e = 0; e < temp6.length(); e++) {
                temp8[e] = temp6[e];
            }

        } else {
            temp7 = string(temp6.length(), '0');
            for (size_t i = 0; i < temp6.length(); i++) {
                temp7[i] = temp6[i];
            }
            flag2 = '+';
            temp8 = string(temp6.length(), '0');
            for (size_t e = 0; e < temp5.length(); e++) {
                temp8[e] = temp5[e];
            }
        }
        temp5.clear();
        temp6.clear();
        int z = 0;
        int d3, d4;
        int count = 0;
        if (flag2 == '-') {
            temp9 = string(temp7.length(), '0');
            for (size_t a = 0; a < temp7.length(); a++) {
                d3 = symbol_to_digit(temp7[a]);
                d4 = symbol_to_digit(temp8[a]);
                if (d3 - d4 - count < 0) {
                    z = 10 - count;
                    temp9[a] = digit_to_symbol(d3 - d4 + z);
                    count = 1;
                } else if (d3 - d4 - count == 0) {
                    temp9[a] = '0';
                    count = 0;
                } else {
                    if (count == 1) {
                        temp9[a] = digit_to_symbol(d3 - d4 - 1);
                    } else {
                        temp9[a] = digit_to_symbol(d3 - d4);
                    }
                    count = 0;
                }
            }

            string temp11 = string(temp9.length(), '0');
            for (size_t i = 0; i < temp9.length(); i++) {
                temp11[i] = temp9[temp9.length() - 1 - i];
            }
            string temp10 = string(temp7.length() + 1, '0');
            temp10[0] = '-';
            for (size_t i = 0; i < temp11.length(); i++) {
                temp10[i + 1] = temp11[i];
            }
            temp7.clear();
            temp8.clear();
            temp9.clear();
            BigInt result(temp10);
            result = delete_zeroes(result);
            return result;
        } else {
            temp9 = string(temp7.length(), '0');
            for (size_t a = 0; a < temp7.length(); a++) {
                d3 = symbol_to_digit(temp7[a]);
                d4 = symbol_to_digit(temp8[a]);
                if (d3 - d4 - count < 0) {
                    z = 10 - count;
                    temp9[a] = digit_to_symbol(d3 - d4 + z);
                    count = 1;
                } else if (d3 - d4 - count == 0) {
                    temp9[a] = '0';
                    count = 0;
                } else {
                    if (count == 1) {
                        temp9[a] = digit_to_symbol(d3 - d4 - 1);
                    } else {
                        temp9[a] = digit_to_symbol(d3 - d4);
                    }
                    count = 0;
                }
            }
            string temp11 = string(temp8.length(), '0');
            for (size_t i = 0; i < temp9.length(); i++) {
                temp11[i] = temp9[temp9.length() - 1 - i];
            }
            temp9.clear();
            temp7.clear();
            temp8.clear();
            BigInt result(temp11);
            result = delete_zeroes(result);
            return result;
        }
    }
};


BigInt operator*(const BigInt &first, const BigInt &second) {

    if ((first.get_size() == 1 && first.get_digit()[0] == '0') ||
        (second.get_size() == 1 && second.get_digit()[0] == '0')) {
        BigInt result;
        return result;
    }

    string value2 = string(second.get_size(), '0');
    for (int i = 0; i < second.get_size(); i++) {
        value2[i] = second.get_digit()[second.get_size() - i - 1];
    }

    string value1 = string(first.get_size(), '0');
    for (size_t i = 0; i < first.get_size(); i++) {
        value1[i] = first.get_digit()[first.get_size() - i - 1];
    }

    size_t len1 = first.get_size();
    size_t len2 = second.get_size();

    size_t length = len1 + len2 + 1;

    bool znak_res = true;
    if (second.get_znak() != first.get_znak()) {
        znak_res = false;
    }
    string a;
    string b;
    a = string(len1, '0');
    b = string(len1, '0');
    int *res = new int[length];


    for (size_t i = 0; i < len1; i++) {
        a[i] = value1[len1 - 1 - i];
    }

    for (size_t i = 0; i < len2; i++) {
        b[i] = value2[len2 - 1 - i];
    }

    for (size_t i = 0; i < length; i++) {
        res[i] = 0;
    }

    for (size_t i = 0; i < len1; i++) {
        for (size_t j = 0; j < len2; j++) {
            res[length - 1 - (i + j)] += symbol_to_digit(a[i]) * symbol_to_digit(b[j]);
            int v = symbol_to_digit(a[i]) * symbol_to_digit(b[j]);
            res[length - 1 - (i + j + 1)] += res[length - 1 - (i + j)] / 10;
            int r = res[length - 1 - (i + j)] / 10;
            res[length - 1 - (i + j)] %= 10;
            int g = res[length - 1 - (i + j)] % 10;
            int x = 1;
        }
    }
    value1.clear();
    value2.clear();

    size_t k = length;
    string result_str1 = string(length, '0');
    string result_str2 = string(length, '0');

    for (size_t i = 0; i < length; i++) {
        result_str1[i] = digit_to_symbol(res[i]);
    }

    char m = '-';
    if (result_str1[0] == '0') {
        m = '0';
    }
    int z = 0;
    for (size_t i = 0; i < length; i++) {

        if ((result_str1[i] == '0') && (m == '0')) {
            k--;
            continue;
        } else {
            m = '+';
            result_str2[z] = result_str1[i];
            z++;
        }
    }

    string result_str;

    if (znak_res == false) {
        result_str = string(k + 1, '0');
        result_str[0] = '-';
        for (size_t i = 0; i < k; i++) {
            result_str[i + 1] = result_str2[i];
        }
    } else {
        result_str = string(k, '0');
        for (size_t i = 0; i < k; i++) {
            result_str[i] = result_str2[i];
        }
    }

    result_str1.clear();
    result_str2.clear();

    a.clear();
    b.clear();
    delete[] res;
    BigInt result(result_str);
    result = delete_zeroes(result);
    return result;
}

BigInt binary_to_decimal(string a) {
    BigInt sum(0);
    BigInt tmp(1);
    BigInt mult_2(2);

    for (size_t i = 0; i < a.length(); i++) {
        if (a[i] == '1') {
            sum = sum + tmp;
        }
        tmp = tmp * mult_2;
    }

    return sum;
}

BigInt BigInt::operator~() {
    BigInt result;
    BigInt a(-1);
    result = ((*this) * a) + a;
    return result;
}

BigInt operator/(const BigInt &first, const BigInt &second) {

    string value1 = string(first.get_size(), '0');
    for (size_t i = 0; i < first.get_size(); i++) {
        value1[i] = first.get_digit()[first.get_size() - i - 1];
    }

    string value2 = string(second.get_size(), '0');
    for (size_t i = 0; i < second.get_size(); i++) {
        value2[i] = second.get_digit()[second.get_size() - i - 1];
    }
    if (value2 > value1) {
        BigInt result;
        return result;
    }
    if ((second.get_size() == 1 && second.get_digit()[0] == '0')) {
        cout << "Division by zero" << endl;
        BigInt result;
        return result;
    }

    if ((first.get_size() == 1 && first.get_digit()[0] == '0')) {
        BigInt result;
        return result;
    }

    bool znak_res = true;
    if (second.get_znak() != first.get_znak()) {
        znak_res = false;
    }

    if ((second.get_size() == 1 && second.get_digit()[0] == '1')) {
        string result_str;
        if (znak_res == false) {
            result_str = string(first.get_size() + 1, '0');
            result_str[0] = '-';
            for (size_t i = 0; i < first.get_size(); i++) {
                result_str[i + 1] = first.get_digit()[first.get_size() - 1 - i];
            }
        } else {
            result_str = string(first.get_size(), '0');
            for (size_t i = 0; i < first.get_size(); i++) {
                result_str[i] = first.get_digit()[first.get_size() - 1 - i];
            }
        }
        BigInt result(result_str);
        result = delete_zeroes(result);
        return result;
    }

    int zeroes = 0;
    while (value2[value2.length() - 1 - zeroes] == '0') {
        zeroes++;
    }

    if (zeroes) {
        value1 = value1.substr(0, value1.length() - zeroes);
        value2 = value2.substr(0, value2.length() - zeroes);
    }

    BigInt tmp(value2);

    size_t divider_length = value2.length();
    long divider_v = divider_length > 8 ? 0 : stol(value2);

    size_t length = value1.length();
    size_t index = 0;

    string div;
    string v;


    while (BigInt(v) < tmp && index < divider_length) {
        v += value1[index++];
    }

    do {
        int count = 0;
        if (BigInt(v) >= tmp) {
            if (divider_length > 8) {
                BigInt mod(v);

                while (mod >= tmp) {
                    mod -= tmp;
                    count++;
                }

                for (size_t i = 0; i < mod.get_size(); i++) {
                    v[i] = mod.get_digit()[i];
                }
            } else {
                long mod = stol(v);
                count = mod / divider_v;
                v = to_string(mod % divider_v);
            }
        }
        div += digit_to_symbol(count);

        if (index <= length) {
            v += value1[index++];
        }
    } while (index <= length);

    string result_str;
    if (znak_res == false) {
        result_str = string(div.length() + 1, '0');
        result_str[0] = '-';
        for (size_t i = 0; i < div.length(); i++) {
            result_str[i + 1] = div[i];
        }
    } else {
        result_str = string(div.length(), '0');
        for (size_t i = 0; i < div.length(); i++) {
            result_str[i] = div[i];
        }
    }
    value1.clear();
    value2.clear();
    div.clear();
    v.clear();

    BigInt result(result_str);
    result = delete_zeroes(result);
    return result;
}

BigInt operator%(const BigInt &first, const BigInt &second) {
    BigInt f = first / second;
    BigInt v = f * second;
    BigInt g = first - v;
    return g;
}


BigInt delete_zeroes(BigInt b) {
    int zeroes = 0;

    size_t i = 0;
    while (b.get_digit()[b.get_size() - i - 1] == '0') {
        zeroes++;
        i++;
    }

    if (zeroes == b.get_size()) {
        BigInt value;
        return value;
    }
    string value;
    value = string(b.get_size() - zeroes, '0');
    value = b.get_digit().substr(0, b.get_size() - zeroes);

    string value2;
    if (b.get_znak() == '-') {
        value2 = string(b.get_size() - zeroes + 1, '0');
        value2[0] = '-';
        for (size_t i = 0; i < b.get_size() - zeroes; i++) {
            value2[i + 1] = value[b.get_size() - zeroes - 1 - i];
        }
    } else {
        value2 = string(b.get_size() - zeroes, '0');
        for (size_t i = 0; i < b.get_size() - zeroes; i++) {
            value2[i] = value[b.get_size() - 1 - i];
        }
    }
    value.clear();
    BigInt result(value2);
    return result;
}

ostream &operator<<(ostream &out, const BigInt &value) {
    if (value.get_znak() == '-') {
        out << '-';
    }
    for (size_t i = 0; i < value.get_size(); i++) {
        out << value.get_digit()[value.get_size() - i - 1];
    }
    return out;
};


BigInt operator&(const BigInt &first, const BigInt &second) {
    string value1 = decimal_to_binary(first);
    string value2 = decimal_to_binary(second);
    size_t min_len = min(value1.length(), value2.length());
    string result_str;

    result_str = string(min_len, '0');
    for (size_t i = 0; i < min_len; i++) {
        result_str[i] = digit_to_symbol(symbol_to_digit(value1[i]) * symbol_to_digit(value2[i]));
    }

    value1.clear();
    value2.clear();

    if (first.get_znak() == '-' && second.get_znak() == '-') {
        BigInt temp;
        BigInt one(-1);
        temp = binary_to_decimal(result_str);
        BigInt result = temp * one;
        return result;
    } else {
        return binary_to_decimal(result_str);
    }
}


BigInt operator|(const BigInt &first, const BigInt &second) {
    string value1 = decimal_to_binary(first);
    string value2 = decimal_to_binary(second);
    size_t max_len = max(value1.length(), value2.length());
    string result_str;


    string value3 = string(max_len, '0');
    string value4 = string(max_len, '0');


    for (size_t j = 0; j < value1.length(); j++) {
        value3[j] = value1[j];
    }
    for (size_t j = 0; j < value2.length(); j++) {
        value4[j] = value2[j];
    }

    value1.clear();
    value2.clear();

    if (first.get_znak() == '-' || second.get_znak() == '-') {
        result_str = string(max_len, '0');
        for (size_t i = 0; i < max_len; i++) {
            if (value3[i] == '1' || value4[i] == '1') {
                result_str[i] = '1';
            } else {
                result_str[i] = '0';
            }
        }
        BigInt temp;
        BigInt one(-1);
        temp = binary_to_decimal(result_str);
        BigInt result = temp * one;
        value3.clear();
        value4.clear();
        return result;
    } else {
        result_str = string(max_len, '0');
        for (size_t i = 0; i < max_len; i++) {
            if (value3[i] == '1' || value4[i] == '1') {
                result_str[i] = '1';
            } else {
                result_str[i] = '0';
            }
        }
        value3.clear();
        value4.clear();
        return binary_to_decimal(result_str);
    }
}


BigInt operator^(const BigInt &first, const BigInt &second) {
    char flag = '+';
    if (first.get_znak() != second.get_znak()) {
        flag = '-';
    }
    string value1 = decimal_to_binary(first);
    string value2 = decimal_to_binary(second);
    size_t max_len = max(value1.length(), value2.length());
    string result_str;

    string value3 = string(max_len, '0');
    string value4 = string(max_len, '0');

    for (size_t j = 0; j < value1.length(); j++) {
        value3[j] = value1[j];
    }

    for (size_t j = 0; j < value2.length(); j++) {
        value4[j] = value2[j];
    }

    value1.clear();
    value2.clear();

    if (first.get_znak() != second.get_znak()) {
        result_str = string(max_len, '0');
        for (size_t i = 0; i < max_len; i++) {
            if (value3[i] != value4[i]) {
                result_str[i] = '1';
            } else {
                result_str[i] = '0';
            }
        }
        value3.clear();
        value4.clear();
        BigInt result = binary_to_decimal(result_str);
        BigInt a(0);
        if (result == a) {
            return a;
        }
        result.set_sign(flag);
        return result;
    } else {
        result_str = string(max_len, '0');
        for (size_t i = 0; i < max_len; i++) {
            if (value3[i] != value4[i]) {
                result_str[i] = '1';
            } else {
                result_str[i] = '0';
            }
        }
        BigInt result;
        result = binary_to_decimal(result_str);

        value3.clear();
        value4.clear();
        BigInt a(0);
        if (result == a) {
            return a;
        }
        result.set_sign(flag);
        return result;
    }
}

BigInt &BigInt::operator-=(const BigInt &other) {
    *(this) = *(this) - other;
    return *this;
};

BigInt &BigInt::operator+=(const BigInt &other) {
    *(this) = *(this) + other;
    return *this;
};

BigInt &BigInt::operator/=(const BigInt &other) {
    *(this) = *(this) / other;
    return *this;
};

BigInt &BigInt::operator*=(const BigInt &other) {
    *(this) = *(this) * other;
    return *this;
};

BigInt &BigInt::operator^=(const BigInt &other) {
    *(this) = *(this) ^ other;
    return *this;
};

BigInt &BigInt::operator&=(const BigInt &other) {
    *(this) = *(this) & other;
    return *this;
};

BigInt &BigInt::operator|=(const BigInt &other) {
    *(this) = *(this) | other;
    return *this;
};

BigInt &BigInt::operator%=(const BigInt &other) {
    *(this) = *(this) % other;
    return *this;
};

BigInt BigInt::operator-() {
    return (*this) * BigInt(-1);
};


BigInt::BigInt(BigInt &&other) noexcept {
    this->digit = std::move(other.digit);
    this->size = other.size;
    this->znak = other.znak;
    other.size = 0;
}

BigInt &BigInt::operator=(BigInt &&other) noexcept {
    this->digit.clear();
    this->digit = other.digit;
    this->size = other.size;
    this->znak = other.znak;
    other.size = 0;

    return *this;
}