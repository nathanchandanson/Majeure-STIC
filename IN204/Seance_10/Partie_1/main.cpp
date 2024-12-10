#include <iostream>
#include <regex>
#include <fstream>
#include <map>

template<class T>
class temporary_buffer
{
public:
    using value_type = T;
    using pointer = value_type*;
    using iterator = value_type*;
    using size_type = size_t;
 
private:
    std::unique_ptr<value_type[]> m_memory;
    size_type m_size;
public:
    explicit temporary_buffer(
        size_type initial_size): 
        m_size(initial_size),
        m_memory(std::make_unique_for_overwrite<value_type[]>(initial_size))
    {}
 
    ~temporary_buffer() = default;
 
    constexpr iterator begin() { return m_memory.get(); }
    constexpr iterator end() { return m_memory.get() + m_size; }
 
    constexpr pointer data() { return m_memory.get(); }
 
    void increase_by(size_type number_of_elements)
    {
        size_type new_size = m_size + number_of_elements;
        auto new_memory = std::make_unique_for_overwrite<value_type[]>(new_size);
        std::copy_n(m_memory.get(), m_size, new_memory.get());
        m_size = new_size;
        std::swap(m_memory, new_memory);
    }
 
    constexpr size_type size() const noexcept { return m_size; }
};

std::regex match_variables(
    "^([A-Za-z_][A-Za-z_0-9]*)\\s*=\\s*(.*)$", 
    std::regex_constants::multiline);
 
std::map<std::string, std::string> find_all_variables(std::string filename)
{
    using buffer_type = temporary_buffer<char>;
    using iterator = typename buffer_type::iterator;
 
    const size_t buffer_size = 80;
    const size_t increment = 40;
 
    buffer_type buffer(buffer_size) ;
    std::map<std::string, std::string> variables;
    std::ifstream stream(filename);
 
    while(!stream.eof() && !stream.fail())
    {
        // Try to load the full line into the buffer.
        stream.getline(buffer.data(), buffer.size());
        size_t number_of_available_chars = (size_t)stream.gcount();
        while(stream.fail() && !stream.eof() 
            && number_of_available_chars == buffer.size() - 1)
        {
            // Increase the buffer as long as it is required.
            buffer.increase_by(increment);
            stream.clear();
            stream.getline(
                buffer.data() + number_of_available_chars, 
                buffer.size() - number_of_available_chars);
            number_of_available_chars += (size_t)stream.gcount();
        }
 
        // Test if the line matches the regular expressions and
        // retrieve the name of the variable and the associated value.
        std::match_results<iterator> match;
        if(std::regex_match(buffer.begin(), buffer.end(), 
            match, match_variables))
        {
            variables[match[1].str()] = match[2].str();
        }
    }
    return variables;
}

int main()
{
    return 0;
}