#include <stack>
#include <iostream>
#include <vector>
#include "../containers/stack.hpp"

int main()
{
    std::stack<int> std_st;
    ft::stack<int> ft_st;

    std::cout << std_st.empty() << std::endl;
    std::cout << ft_st.empty() << std::endl;

    std::cout << std_st.size() << std::endl;
    std::cout << ft_st.size() << std::endl;

    std_st.push(1);
    ft_st.push(1);

    std::cout << std_st.top() << std::endl;
    std::cout << ft_st.top() << std::endl;

    std_st.pop();
    ft_st.pop();

    std::cout << std_st.empty() << std::endl;
    std::cout << ft_st.empty() << std::endl;

    return 0;
}
