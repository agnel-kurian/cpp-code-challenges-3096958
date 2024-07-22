// C++ Code Challenges, LinkedIn Learning

// Challenge #4: Checking for Bitonic Sequences
// Write a function to check if a vector of integers is bitonic or not.
// Bitonic sequences have an ascending segment followed by a descending segment (sort of).
// Circular shifts of these sequences are also bitonic.

// Formally, a bitonic sequence is a sequence with x[0] <= ... <= x[k] >= ... >= x[n-1]
//           for some k between 0 and n-1, or a circular shift of such a sequence.

// Special bitonic cases: Monotonic sequences and sequences where all elements have the same value.

#include <iostream>
#include <vector>

// is_bitonic()
// Summary: This function receives an STL vector of integers and returns true if it contains a bitonic sequence, false otherwise.
// Arguments:
//           v: A reference to the vector to analyze.
// Returns: A boolean value: True for bitonic sequences, false otherwise.
bool is_bitonic(const std::vector<int> &v){
    
    size_t vlen = v.size();
    if(vlen <= 3) return true;
    int imin = 0;
    for(size_t i = 1; i < vlen; ++i) {
        if(v[i] < v[imin]) imin = i;
    }


    bool rising = true;
    int j = (imin == vlen - 1) ? 0 : imin + 1;
    while(j != imin) {
        int j1 = (j == vlen - 1) ? 0 : j + 1;
        if(rising && v[j1] < v[j]) rising = false;
        else if(!rising && v[j1] > v[j]) return false;

        if(j == vlen - 1) j = 0; else j++;
    }

    return true;
}

void test1(const std::vector<int>& v, bool expected) {
    if(is_bitonic(v) != expected)
        std::cout << "FAILED" << std::endl;
    else
        std::cout << "PASSED" << std::endl;
}

// Main function
int main(){
    // Uncomment one of these lines and make sure you get the result at the right. 
    
    // std::vector<int> myvec = {1, 2, 5, 4, 3};  // Yes
    // std::vector<int> myvec = {1, 1, 1, 1, 1};  // Yes
    // std::vector<int> myvec = {3, 4, 5, 2, 2};  // Yes
    // std::vector<int> myvec = {3, 4, 5, 2, 4};  // No
    // std::vector<int> myvec = {1, 2, 3, 4, 5};  // Yes
    // std::vector<int> myvec = {1, 2, 3, 1, 2};  // No
    // std::vector<int> myvec = {5, 4, 6, 2, 6};  // No
    // std::vector<int> myvec = {5, 4, 3, 2, 1};  // Yes
    // std::vector<int> myvec = {5, 4, 3, 2, 6};  // Yes
    // std::vector<int> myvec = {5, 4, 6, 5, 4};  // No
    // std::vector<int> myvec = {5, 4, 6, 5, 5};  // Yes
    test1({1, 2, 5, 4, 3}, true);
    test1({1, 1, 1, 1, 1}, true);
    test1({3, 4, 5, 2, 2}, true);
    test1({3, 4, 5, 2, 4}, false);
    test1({1, 2, 3, 4, 5}, true);
    test1({1, 2, 3, 1, 2}, false);
    test1({5, 4, 6, 2, 6}, false);
    test1({5, 4, 3, 2, 1}, true);
    test1({5, 4, 3, 2, 6}, true);
    test1({5, 4, 6, 5, 4}, false);

    test1({5, 4, 6, 5, 5}, true);
    std::cout << std::endl << std::endl << std::flush;
    return 0;
}
