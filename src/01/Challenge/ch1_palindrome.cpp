// C++ Code Challenges, LinkedIn Learning

// Challenge #1: Checking for Palindromes
// Write a function to check if a string is a palindrome or not.
// Examples: civic, radar, level.

#include <iostream>
#include <algorithm>

std::string tolower(const std::string& s) {
    std::string s1 = s;
    auto x = 'a' - 'A';
    for(size_t i = 0, slen = s.size(); i < slen; ++i) {
        if(s1[i] >= 'A' && s1[i] <= 'Z')
            s1[i] += x;
    } 

    return s1;
}

// is_palindrome()
// Summary: This function receives a string and returns true if the string is a palindrome, false otherwise.
// Arguments:
//           str: The string to analyze.
// Returns: A boolean value. True for palindromes, false otherwise.
bool is_palindrome(std::string str){
    std::string str1 = tolower(str);
    size_t j = str1.length() - 1;
    size_t i = 0;
    while(i < j)
        if(str1[i++] != str1[j--]) return false;

    return true;
}

// Main function
int main(){
    std::string s;
    std::cout << "Enter a string: " << std::flush;
    std::getline(std::cin,s);
    std::cout << "\n\"" << s << (is_palindrome(s) ? "\" is" : "\" is not" ) << " a palindrome.\n\n";
    return 0;
}
