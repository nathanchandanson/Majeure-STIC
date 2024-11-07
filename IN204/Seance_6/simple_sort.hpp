#pragma once
#include<algorithm>

/************* Définition de simple_sort *************/
// Si pas d'accès par index (!std::random_access_iterator<iterator>)
template<typename  iterator>
void simple_sort(iterator start, iterator end) 
    requires(std::forward_iterator<iterator> && ! std::random_access_iterator<iterator> && std::input_or_output_iterator<iterator>)
{
    std::cout << "Insertion Sort\n";
    for(;start != end; start ++)
    {
        auto it = start; it++;
        for(;it != end; it ++)
        {
            // Compare si les deux elements sont dans le bon ordre.
            if (*start > *it)
                std::swap(*start, *it);
        }
    }
}

// Si accès par index
template<typename iterator>
void simple_sort(iterator start, iterator end) 
    requires(std::random_access_iterator<iterator> && std::input_or_output_iterator<iterator>)
{
    std::cout << "Quicksort\n";
    return std::sort(start, end);
}



/************* Définition des opérateurs << *************/
// Browsable concept
template<typename T>
concept browsable = requires(const T& a)
{
    { a.begin() } -> std::forward_iterator; // a.begin() existe et c'est un forward_iterator
    { a.end() } -> std::forward_iterator;   // a.end() existe et c'est un forward_iterator
};


template<typename containerT, typename charT, typename traits = std::char_traits<charT>>
requires browsable<containerT>
std::basic_ostream<charT, traits>& operator << (std::basic_ostream<charT, traits>& aStream, const containerT& aContainer)
{
    aStream << "{";
    auto end = aContainer.end();
    for(auto it = aContainer.begin(); it != end;)
    {
        aStream << *it ++;
        if(it != end)
            aStream << ", ";
    }
    aStream << "}";
    return aStream;
} 

template<typename T, typename charT, typename traits = std::char_traits<charT>>
std::basic_ostream<charT, traits>& operator << (std::basic_ostream<charT, traits>& aStream, const T& aContainer)
{
    std::cout << "NONE";
    return aStream;
}