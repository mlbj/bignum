#include "bignum.h"
#include <iostream>

int main() {
    // tests + and - 
    BigInt a1("1"), b1("-11");
    std::cout << a1 - b1 << "\t expected = +12" << "\t" << std::endl;  
    BigInt a2("-1"), b2("-11");
    std::cout << a2 - b2 << "\t expected = +10" << "\t" << std::endl; 
    BigInt a3("10"), b3("-11");
    std::cout << a3 + b3 << "\t expected = -1" << "\t" << std::endl;  
    BigInt a4("-1"), b4("-11");
    std::cout << a4 + b4 << "\t expected = -12" << "\t" << std::endl;  
    BigInt a5("-1"), b5("11");
    std::cout << a5 + b5 << "\t expected = +10" << "\t" << std::endl;  
    BigInt a6("2"), b6("11");
    std::cout << a6 - b6 << "\t expected = -9" << "\t" << std::endl;  
    BigInt a7("11"), b7("2");
    std::cout << a7 - b7 << "\t expected = +9" << "\t" << std::endl; 
    BigInt a8("6532"), b8("000300");
    std::cout << a8 + b8 << "\t expected = +6832" << "\t" << std::endl;

    // tests * 
    BigInt c1("3212"), d1("2002");
    std::cout << c1 * d1 << "\t expected = +6430424" << "\t" << std::endl;  
    BigInt c2("11312"), d2("49329124323");
    std::cout << c2 * d2 << "\t expected = +558011054341776" << "\t" << std::endl;  
    BigInt c3("3141592653589793238462643383279502884197169399375105820974944592");
    BigInt d3("2718281828459045235360287471352662497757247093699959574966967627");
    std::cout << c3 * d3 << "\t expected = +8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184" << "\t" << std::endl;  

    return 0;
}

