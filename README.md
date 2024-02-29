# bignum

A toy arbitrary precision integer arithmetic library written in C++. Currently, it features addition and subtraction implemented in linear time, as well as multiplication in subcubic time using Karatsuba's algorithm. This library is designed only for educational purposes.

Numbers are represented in base 10 (which is far from optimal), stored using a `std::string` object for digits and an `int` variable for sign.

## Test Instructions

Compile with  

```bash
gcc -g bignum.cpp -o test -lstdc++
```

and run `test`. 