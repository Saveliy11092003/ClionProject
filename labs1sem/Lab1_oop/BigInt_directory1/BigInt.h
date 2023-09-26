//
// Created by user on 30.09.22.
//

#ifndef LAB1_OOP_BIGINT_H
#define LAB1_OOP_BIGINT_H
#include <string>
using namespace std;

class BigInt {
private:
    size_t size;
    string digit;
    char znak;
public:
    explicit BigInt();
    explicit BigInt(int);
    explicit BigInt(std::string);
    BigInt(const BigInt&);
    ~BigInt();

    string get_digit() const;

    size_t get_size() const;

    char get_znak() const;
    void set_sign(char c);
    BigInt& operator=(const BigInt&);

    BigInt operator~();

    BigInt& operator++();
    const BigInt operator++(int) ;
    BigInt operator--();
    const BigInt operator--(int) ;

    BigInt& operator+=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator^=(const BigInt&);
    BigInt& operator%=(const BigInt&);
    BigInt& operator&=(const BigInt&);
    BigInt& operator|=(const BigInt&);

    BigInt operator+() const;  // unary +
    BigInt operator-();  // unary -

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    BigInt(BigInt &&vec) noexcept;
    BigInt& operator=(BigInt &&vec) noexcept;

    operator int() const;
    operator std::string() const;

};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);

BigInt delete_zeroes(BigInt b);

std::ostream& operator<<(std::ostream& o, const BigInt& i);

size_t get_length(int n);

char digit_to_symbol(int n);
int symbol_to_digit(char n);

string decimal_to_binary(const BigInt a);
BigInt binary_to_decimal(string a);
#endif //LAB1_OOP_BIGINT_H
