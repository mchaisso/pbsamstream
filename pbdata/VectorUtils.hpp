#ifndef _BLASR_VECTOR_UTILS_HPP_
#define _BLASR_VECTOR_UTILS_HPP_

#include <vector>

// Clear all memory allocated by this vector
template <typename T>
void ClearMemory(std::vector<T>& vt)
{
    // Create an empty vector
    std::vector<T> emptyVector;
    // First clear the content
    vt.clear();
    // Then swap vt with the empty vector
    vt.swap(emptyVector);
}

#endif  // _BLASR_VECTOR_UTILS_HPP_
