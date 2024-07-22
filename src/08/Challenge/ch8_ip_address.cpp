// C++ Code Challenges, LinkedIn Learning

// Challenge #8: IP Address Validation
// Write an application that reads a string from the terminal and responds with a message indicating whether the string is a valid IP address or not.
// Assume decimal IP addresses.
// 158.25.0.33
// All numbers between 0 and 255.

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// is_valid_ip()
// Summary: This function validates an IP address.
// Arguments:
//           ip: The string to analyze with a potential ip address.
// Returns: A boolean value. True for valid ip addresses, false otherwise.
bool is_valid_ip(std::string ip){
    std::stringstream ss[4];

    size_t slen = ip.length();
    int iss = 0;
    for(size_t i = 0; i < slen; ++i) {
        char c = ip[i];
        if(c == '.') {
            if(iss > 3) return false;
            iss++;
        }
        else if(c < '0' || c > '9')
            return false;
        else
            ss[iss] << c;
    }

    for(int i = 0; i < 4; ++i) {
        std::string s = ss[i].str();
        if(s.length() == 0) return false;
        int iaddr = std::atoi(s.c_str());
        if(iaddr < 0 || iaddr > 255) return false;
    }

    return true;
}

// Main function
int main(){
    std::string s;
    
    std::cout << std::endl << "Enter an IP address in decimal: " << std::flush;
    std::getline(std::cin,s);
    std::cout << " \n" << s << (is_valid_ip(s) ? " is" : " is not" ) << " a valid IP address.\n\n";
    return 0;
}
