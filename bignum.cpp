#include <iostream>
#include <string>
using namespace std;

// bignum represents signed integers of arbitrary size  
// using a string of digits and an int to store its sign. 
class bignum{

public:
    string digits;
    int sign = 1;

    // main constructor
    bignum(string digits=""){
        int i = 0;
        if (digits[0]=='-'){
            this->sign = -1;
            i = i+1;
        }else if(digits[0]=='+'){
            this->sign = 1;
            i = i+1;
        }
        while (i<digits.size() && digits[i]=='0'){
            i = i+1;
        }
        digits.erase(0, i);
        this->digits = digits;
    }

     // greater than operator> overloaded
    bool operator>(const bignum& other) const{
        // mixed sign cases 
        if (this->sign>0 && other.sign<0){
            return true;
        }else if(this->sign<0 && other.sign>0){
            return false;
        }

        // equal sign cases
        string a_digits = this->digits;
        string b_digits = other.digits;
        int max_length = max(a_digits.length(),b_digits.length());

        a_digits.insert(0,max_length - a_digits.length(),'0');
        b_digits.insert(0,max_length - b_digits.length(),'0');

        // verify of one them has a larger number of digits
        int i = 0;
        while (i<max_length && a_digits[i] == b_digits[i] == '0'){
            i = i+1;
        }
        // both numbers are equal to zero 
        if (i==max_length){
           return false;
        }else{
            // this one has a larger number of digits 
            if (b_digits[i]==0){
                if (this->sign>0){
                    return true;
                }else{
                    return false;
                }
         
            // the other one has a larger number of digits 
            }else if (a_digits[i]==0){
                if (other.sign>0){
                    return false;
                }else{
                    return true;
                }
            
            // both have the same amount of digits
            }else{
                while (i<max_length && a_digits[i]==b_digits[i]){
                    i = i+1;
                }

                // both numbers are equal to zero 
                if (i==max_length){
                   return false;
                }

                // one of them is larger then the other one 
                if (a_digits[i]>b_digits[i]){
                    if (this->sign>0){
                        return true;
                    }else{
                        return false;
                    }
                }else{
                    if (this->sign>0){
                        return false;
                    }else{
                        return true;
                    }
                }
            }
        }
    }

    // subtraction operator- overloaded
    bignum operator-(const bignum& other) const{
        // output bignum 
        bignum result;

        // unpack and handle signs 
        if (this->sign>0 && other.sign>0){
            if (other>*this){
                result = other-*this;
                result.sign = -1;
                return result;
            }
            result.sign = 1;
        }else if(this->sign<0 && other.sign<0){      
            bignum abs_other;
            abs_other.digits = other.digits;
            abs_other.sign = 1;
            return *this + abs_other;
        }else if(this->sign>0 && other.sign<0){
            bignum abs_other;
            abs_other.digits = other.digits;
            abs_other.sign = 1;
            return *this + abs_other;
        }else if(this->sign<0 && other.sign>0){
            bignum neg_other;
            neg_other.digits = this->digits;
            neg_other.sign = 1;
            return *this-neg_other;
        }

        // fill with leading zeros so that both numbers 
        // have the same length 
        string a_digits = this->digits;
        string b_digits = other.digits;
        int max_length = max(a_digits.length(),b_digits.length());
        a_digits.insert(0,max_length - a_digits.length(),'0');
        b_digits.insert(0,max_length - b_digits.length(),'0');

        // create output digits whose size should be at most max_length+1 
        string result_digits(max_length+1,'0'); 
        
        // main summation loop with carry
        int carry = 0;
        for (int i=0; i<max_length; i++){
            int a_digit = (int) (a_digits[max_length-1-i] - '0');
            int b_digit = (int) (b_digits[max_length-1-i] - '0');
            int tmp = a_digit-b_digit-carry;
            result_digits[max_length-i] = (char)((tmp+10)%10 + '0');

            carry = (int)(tmp<0);
        }
        result.digits = result_digits;
        
        // remove leading zeros
        int i = 0;
        while (i<max_length && result_digits[i]=='0'){
            i = i+1;
        }
        result_digits.erase(0, i);

        // return 
        result.digits = result_digits;
        return result;
    }
    
    // sum operator+ overloaded
    bignum operator+(const bignum& other) const{
        // output bignum 
        bignum result;
        
        // handle and handle signs
        if (this->sign>0 && other.sign>0){
            result.sign = 1;
        }else if(this->sign<0 && other.sign<0){  
            result.sign = -1;
        }else if(this->sign>0 && other.sign<0){
            // call subtraction of *this - |other|
            bignum abs_other;
            abs_other.digits = other.digits;
            abs_other.sign = 1;
            return *this - abs_other;
        }else if(this->sign<0 && other.sign>0){
            // call subtractions of other - |*this|
            bignum abs_this;
            abs_this.digits = this->digits;
            abs_this.sign = 1;
            return other - abs_this;
        }
        
        // add leading zeros so that both inputs have
        // the same length 
        string a_digits = this->digits;
        string b_digits = other.digits;
        int max_length = max(a_digits.length(),b_digits.length());
        a_digits.insert(0,max_length - a_digits.length(),'0');
        b_digits.insert(0,max_length - b_digits.length(),'0');

        // create output digits whose length should be at most
        // max_length+1 
        string result_digits(max_length+1,'0'); 

        // main subtraction loop with borrowing 
        int carry = 0;   
        for (int i=0; i<max_length; i++){
            int a_digit = (int) (a_digits[max_length-1-i] - '0');
            int b_digit = (int) (b_digits[max_length-1-i] - '0');
            int tmp = carry+a_digit+b_digit;
            result_digits[max_length-i] =  ((tmp%10) + '0');

            carry = (int)(tmp>9);
        }

        // fix last digit 
        result_digits[0] = carry + '0';

        // remove leading zeros
        int j = 0;
        while (j<max_length && result_digits[j]=='0'){
            j = j+1;
        }
        result_digits.erase(0, j);

        // return 
        result.digits = result_digits;
        return result;
    }
    
    // multiplication operator* overloaded using karatsuba's algorithm
    // https://en.wikipedia.org/wiki/Karatsuba_algorithm
    bignum operator*(const bignum& other) const{
        // output bignum variable 
        bignum result;

        // sign is easy to handle in this case
        result.sign = (this->sign)*(other.sign);

        // append leading zeros so that both inputs have the
        // same size 
        string a_digits = this->digits;
        string b_digits = other.digits;
        int max_length = max(a_digits.length(),b_digits.length());
        a_digits.insert(0,max_length - a_digits.length(),'0');
        b_digits.insert(0,max_length - b_digits.length(),'0');

        // null base case
        if (max_length==0){
            result.digits = "0";
            return result;
        }
        
        // base case
        if (max_length<=2){
            result.digits = to_string(int(stoi(a_digits)*stoi(b_digits)));
            return result;
        }

        // if not a power of two, add leading zeros until it is 
        int check_power = max_length & (max_length-1);
        while (check_power != 0){
            max_length = max_length+1;
            check_power = max_length & (max_length-1);
            a_digits.insert(0,1,'0');
            b_digits.insert(0,1,'0');
        }

        // divide number in half 
        int len1;
        int len0;
        if (max_length%2==0){
            len1 = (int) (max_length/2);
            len0 = (int) (max_length/2);
        }else{
            len1 = (int)((max_length+1)/2);
            len0 = (int)((max_length-1)/2);
        }

        // store the divided numbers in these variables
        bignum a1,a0,b1,b0;
        a1.sign = 1;
        a0.sign = 1;
        b1.sign = 1;
        b0.sign = 1;
        a1.digits = a_digits.substr(0,len1);
        a0.digits = a_digits.substr(len0,len1);
        b1.digits = b_digits.substr(0,len1);
        b0.digits = b_digits.substr(len0,len1);

        // operate using recursion 
        bignum z2,z1,z0;
        z2 = a1*b1;
        z1 = (a1*b0) + (a0*b1);
        z0 = a0*b0;

        // merge results in the proper way
        z2.digits.insert(z2.digits.length(),2*len0,'0');
        z1.digits.insert(z1.digits.length(),len0,'0');
        result.digits = (z2 + z1 + z0).digits;

        // return 
        return result;
    }
};

// redirect operator<< overloaded to handle bignums properly
std::ostream& operator<<(std::ostream &s, const bignum &num) {
    char sign_symbol = '+';
    if (num.sign<0){
        sign_symbol = '-';
    }
    return s << sign_symbol << num.digits;
}
 

int main(){
    // tests + and - 
    bignum a1("1"),b1("-11");
    cout << a1-b1 << "\t expected = +12" << "\t"<<   endl;  
    bignum a2("-1"),b2("-11");
    cout << a2-b2 << "\t expected = +10" << "\t"<<  endl; 
    bignum a3("10"),b3("-11");
    cout << a3+b3 << "\t expected = -1" << "\t"<<  endl;  
    bignum a4("-1"),b4("-11");
    cout << a4+b4  << "\t expected = -12" << "\t"<<  endl;  
    bignum a5("-1"),b5("11");
    cout << a5+b5 << "\t expected = +10" << "\t"<<  endl;  
    bignum a6("2"),b6("11");
    cout << a6-b6 << "\t expected = -9" << "\t"<< endl;  
    bignum a7("11"),b7("2");
    cout << a7-b7 << "\t expected = +9" << "\t"<<  endl; 
    bignum a8("6532"),b8("000300");
    cout << a8+b8 << "\t expected = +6832" << "\t" << endl;


    // tests * 
    bignum c1("3212"),d1("2002");
    cout << c1*d1 << "\t expected = +6430424" << "\t"<<  endl;  
    bignum c2("11312"),d2("49329124323");
    cout << c2*d2 << "\t expected = +558011054341776" << "\t"<<  endl;  
    bignum c3("3141592653589793238462643383279502884197169399375105820974944592");
    bignum d3("2718281828459045235360287471352662497757247093699959574966967627");
    cout << c3*d3 << "\t expected = +8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184" << "\t"<<  endl;  

  
    return 0;
}

