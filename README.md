# bignum

A toy arbitrary precision integer arithmetic library written in C++. Currently, it features addition and subtraction implemented in linear time, as well as multiplication in subquadratic time using Karatsuba's algorithm. This is designed only for educational purposes.

Numbers are represented in base 10, stored using a `std::vector<int>` object for digits and a `bool` for sign.

## Build instructions

To build the project using CMake, follow these steps:

```bash
mkdir build
cd build
cmake ..
make
```

## Test 

Run `./test`. 
