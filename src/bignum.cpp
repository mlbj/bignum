#include "bignum.h"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <algorithm>

// constructors
BigInt::BigInt() : digits(1, 0), isNegative(false){}

BigInt::BigInt(const std::string &number){
    int i = 0;
    if (number[0] == '-'){
        isNegative = true;
        i++;
    }else if (number[0] == '+'){
        isNegative = false;
        i++;
    }else{
        isNegative = false;
    }
    while (i < number.size() && number[i] == '0'){
        i++;
    }
    for (; i < number.size(); i++){
        if (number[i] < '0' || number[i] > '9'){
            throw std::invalid_argument("Invalid number");
        }else{
            digits.push_back(number[i] - '0');
        }
    }
    if (digits.empty()){
        digits.push_back(0);
        isNegative = false;
    }
}

// copy constructor 
BigInt::BigInt(const BigInt &other) : digits(other.digits), isNegative(other.isNegative) {}

// assignment operator
BigInt& BigInt::operator=(const BigInt &other){
    if (this != &other) {
        digits = other.digits;
        isNegative = other.isNegative;
    }
    return *this;
}

// subtraction operator- overloaded
BigInt BigInt::operator-(const BigInt& other) const{
    BigInt result;

    // unpack and handle signs 
    if (this->isNegative == other.isNegative){ // both are negative or positive 
        if (this->isNegative){ // both are negative 
            if (*this < other){ // -3 - (-2) = -3 + 2 
                result = this->subtract(other);
                result.isNegative = true;
            }else{  // -2 - (-3) = -2 + 3 = 3 - 2 
                result = other.subtract(*this);
                result.isNegative = false;
            }
        }else{ // both are positive 
            if (*this < other){ 
                result = other.subtract(*this);
                result.isNegative = true;
            }else{
                result = this->subtract(other);
                result.isNegative = false;
            }
        }
    }else{
        BigInt absOther = other;
        absOther.isNegative = !other.isNegative;
        result = this->add(absOther);
        result.isNegative = this->isNegative;
    }
    return result;
}

BigInt BigInt::subtract(const BigInt &other) const{
    BigInt result;
    result.digits.clear();
    int carry = 0;
    int maxLength = std::max(digits.size(), other.digits.size());

    // fill with leading zeros so that both numbers have the same length
    std::vector<int> a_digits = digits;
    std::vector<int> b_digits = other.digits;
    a_digits.insert(a_digits.begin(), maxLength - a_digits.size(), 0);
    b_digits.insert(b_digits.begin(), maxLength - b_digits.size(), 0);

    for (int i=0; i<maxLength; i++){
        int digit1 = a_digits[maxLength - 1 - i];
        int digit2 = b_digits[maxLength - 1 - i];
        int diff = digit1 - digit2 - carry;
        if (diff < 0){
            diff += 10;
            carry = 1;
        }else{
            carry = 0;
        }
        result.digits.push_back(diff);
    }

    std::reverse(result.digits.begin(), result.digits.end());
    result.removeLeadingZeros();
    return result;
}




// sum operator+ overloaded
BigInt BigInt::operator+(const BigInt& other) const{
    BigInt result;

    // handle signs
    if (this->isNegative == other.isNegative){
        result = add(other);
        result.isNegative = this->isNegative;
    } else {
        if (this->isNegative) {
            BigInt absThis = *this;
            absThis.isNegative = false;
            if (absThis > other) {
                result = absThis.subtract(other);
                result.isNegative = true;
            } else {
                result = other.subtract(absThis);
                result.isNegative = false;
            }
        } else {
            BigInt absOther = other;
            absOther.isNegative = false;
            if (*this > absOther) {
                result = this->subtract(absOther);
                result.isNegative = false;
            } else {
                result = absOther.subtract(*this);
                result.isNegative = true;
            }
        }
    }

    return result;
}

BigInt BigInt::add(const BigInt& other) const{
    BigInt result;
    result.digits.clear();
    int carry = 0;
    int maxLength = std::max(digits.size(), other.digits.size());

    for (int i = 0; i < maxLength; ++i){
        int digit1 = i < digits.size() ? digits[digits.size() - 1 - i] : 0;
        int digit2 = i < other.digits.size() ? other.digits[other.digits.size() - 1 - i] : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result.digits.push_back(sum % 10);
    }

    if (carry){
        result.digits.push_back(carry);
    }

    std::reverse(result.digits.begin(), result.digits.end());
    result.removeLeadingZeros();
    return result;
}

BigInt BigInt::operator*(const BigInt& other) const{
    return multiply(other);
}

BigInt BigInt::multiply(const BigInt& other) const{
    BigInt result;

    // sign is easy to handle in this case
    result.isNegative = (this->isNegative != other.isNegative);

    // append leading zeros so that both inputs have the same size 
    std::vector<int> a_digits = this->digits;
    std::vector<int> b_digits = other.digits;
    int max_length = std::max(a_digits.size(), b_digits.size());
    a_digits.insert(a_digits.begin(), max_length - a_digits.size(), 0);
    b_digits.insert(b_digits.begin(), max_length - b_digits.size(), 0);

    // null base case
    if (max_length == 0){
        result.digits = {0};
        return result;
    }
    
    // base case
    if (max_length <= 2){
        int a = 0, b = 0;
        for (int digit : a_digits) a = a * 10 + digit;
        for (int digit : b_digits) b = b * 10 + digit;
        int product = a * b;
        result.digits.clear();
        while (product > 0) {
            result.digits.insert(result.digits.begin(), product % 10);
            product /= 10;
        }
        if (result.digits.empty()) result.digits.push_back(0);
        return result;
    }

    // if not a power of two, add leading zeros until it is 
    int check_power = max_length & (max_length - 1);
    while (check_power != 0) {
        max_length++;
        check_power = max_length & (max_length - 1);
        a_digits.insert(a_digits.begin(), 0);
        b_digits.insert(b_digits.begin(), 0);
    }

    // divide number in half 
    int len1 = max_length / 2;
    int len0 = max_length - len1;

    // store the divided numbers in these variables
    BigInt a1, a0, b1, b0;
    a1.digits.assign(a_digits.begin(), a_digits.begin() + len1);
    a0.digits.assign(a_digits.begin() + len1, a_digits.end());
    b1.digits.assign(b_digits.begin(), b_digits.begin() + len1);
    b0.digits.assign(b_digits.begin() + len1, b_digits.end());

    // operate using recursion 
    BigInt z2 = a1.multiply(b1);
    BigInt z1 = (a1 + a0).multiply(b1 + b0);
    BigInt z0 = a0.multiply(b0);

    // merge results in the proper way
    z1 = z1 - z2 - z0;
    z2.digits.insert(z2.digits.end(), 2 * len0, 0);
    z1.digits.insert(z1.digits.end(), len0, 0);
    result = z2 + z1 + z0;

    // remove leading zeros
    result.removeLeadingZeros();

    // return 
    return result;
}

// greater than operator> overloaded
bool BigInt::operator>(const BigInt& other) const{
    // mixed sign cases 
    if (this->isNegative && !other.isNegative){
        return false;
    } else if (!this->isNegative && other.isNegative){
        return true;
    }

    // equal sign cases
    if (digits.size() != other.digits.size()){
        return this->isNegative ? digits.size() < other.digits.size() : digits.size() > other.digits.size();
    }

    for (size_t i = 0; i < digits.size(); ++i){
        if (digits[i] != other.digits[i]) {
            return this->isNegative ? digits[i] < other.digits[i] : digits[i] > other.digits[i];
        }
    }

    return false;
}

// equality operator== overloaded
bool BigInt::operator==(const BigInt& other) const{
    return (this->isNegative == other.isNegative) && (this->digits == other.digits);
}

// greater than or equal to operator>= overloaded
bool BigInt::operator>=(const BigInt& other) const{
    return (*this > other) || (*this == other);
}


// less than operator< overloaded
bool BigInt::operator<(const BigInt& other) const{
    return !(*this >= other);
}

// inequality operator!= overloaded
bool BigInt::operator!=(const BigInt& other) const{
    return !(*this == other);
}

// less than or equal to operator<= overloaded
bool BigInt::operator<=(const BigInt& other) const{
    return !(*this > other);
}


// redirect operator<< overloaded to handle BigInt properly
std::ostream& operator<<(std::ostream &s, const BigInt &num){
    if (num.isNegative) {
        s << '-';
    }
    for (int digit : num.digits) {
        s << digit;
    }
    return s;
}

void BigInt::removeLeadingZeros(){
    while (digits.size() > 1 && digits[0] == 0){
        digits.erase(digits.begin());
    }
}

void BigInt::addLeadingZeros(int n){
    digits.insert(digits.begin(), n, 0);
}