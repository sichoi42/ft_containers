#ifndef FT_STACK_HPP
#define FT_STACK_HPP

// FIXME: stack을 테스트하기 위해 선언한 것이므로, 나중에 삭제할 것
#include <vector>

namespace ft
{
  // FIXME: 추후 ft::vector로 수정 필요
  template <class T, class Container = std::vector<T> >
  class stack
  {
    public:
      typedef Container container_type;
      typedef typename container_type::value_type value_type;
      typedef typename container_type::reference reference;
      typedef typename container_type::const_reference const_reference;
      typedef typename container_type::size_type size_type;

    protected:
      container_type c;

    public:
      stack() : c() {}
      stack(const stack& st) : c(st.c) {}
      stack& operator=(const stack& st) { c = st.c; return *this; }
      ~stack() {}

      bool empty() const { return c.empty(); }
      size_type size() const { return c.size(); }
      reference top() { return c.back(); }
      const_reference top() const { return c.back(); }
      void push(const value_type& val) { c.push_back(val); }
      void pop() { c.pop_back(); }
  };

  template <class T, class Container>
  bool operator==(const stack<T, Container>& x, const stack<T, Container>& y)
  {
    return x.c == y.c;
  }

  template <class T, class Container>
  bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y)
  {
    return !(x.c == y.c);
  }

  template <class T, class Container>
  bool operator<(const stack<T, Container>& x, const stack<T, Container>& y)
  {
    return x.c < y.c;
  }

  template <class T, class Container>
  bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y)
  {
    return x.c <= y.c;
  }

  template <class T, class Container>
  bool operator>(const stack<T, Container>& x, const stack<T, Container>& y)
  {
    return x.c > y.c;
  }

  template <class T, class Container>
  bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y)
  {
    return x.c >= y.c;
  }
}

#endif
