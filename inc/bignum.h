#ifndef BIGNUM_H
#define BIGNUM_H

#include <iostream>
#include <vector>
#include <string>

class BigInt {
public:
    // constructors 
    BigInt();
    BigInt(const std::string& number);
    BigInt(const BigInt& other);

    // assignment operator
    BigInt& operator=(const BigInt& other);

    // arithmetic operators
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;

    // arithmetic helper functions
    BigInt add(const BigInt& other) const;
    BigInt subtract(const BigInt& other) const;
    BigInt multiply(const BigInt& other) const;

    // comparison operators 
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const; 
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;


    // friend input and output operators 
    friend std::ostream& operator<<(std::ostream& os, const BigInt& bignum);

private: 
    std::vector<int> digits;
    bool isNegative;

    // helper functions
    void removeLeadingZeros();
    void addLeadingZeros(int n);
};

#endif // BIGNUM_H