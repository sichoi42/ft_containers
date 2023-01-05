#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP
# include <memory>
# include "../implements/reverse_iterator.hpp"
# include "../implements/random_access_iterator.hpp"

namespace ft {
	template <class T, class Allocator = std::allocator<T> >
	class vector {
		public:
			typedef T	value_type;
			typedef Allocator	allocator_type;
			typedef value_type*	pointer;
			typedef const value_type*	const_pointer;
			typedef value_type&	reference;
			typedef const value_type&	const_reference;
			typedef size_t	size_type;
			typedef ptrdiff_t	difference_type;
			typedef ft::random_access_iterator<pointer>	iterator;
			typedef ft::random_access_iterator<const_pointer>	const_iterator;
			typedef ft::reverse_iterator<iterator>	reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			_alloc;

		public:
			// Constrcutor
			vector();
			vector(const allocator_type& alloc = allocator_type());
			vector(size_type n, const value_type& val = value_type(), const Allocator& alloc = allocator_type());
			template <typename InputIterator>
			// TODO: enable_if 필요
			vector(InputIterator first, InputIterator last, const Allocator& alloc = allocator_type());

			// Copy constructor
			vector(const vector& vec);

			// Destructor
			~vector();

			// Copy assignment operator
			vector& operator=(const vector& vec);

			// Member function
			void	assign(size_type n, const value_type& val);

			template <typename InputIterator>
			// TODO: enable_if 필요
			void	assign(InputIterator first, InputIterator last);

			allocator_type	get_allocator() const;

			// Element access
			reference	at(size_type pos);
			const_reference	at(size_type pos) const;

			reference	operator[](size_type pos);
			const_reference	operator[](size_type pos) const;

			reference	front();
			const_reference	front() const;

			reference	back();
			const_reference	back() const;

			pointer	date();
			const_pointer	date() const;

			// Iterators
			iterator	begin();
			const_iterator	begin() const;

			iterator	end();
			const_iterator	end() const;

			reverse_iterator	rbegin();
			const_reverse_iterator	rbegin() const;

			reverse_iterator	rend();
			const_reverse_iterator	rend() const;

			// Capacity
			bool empty() const;

			size_type	size() const;

			size_type	max_size() const;

			void	reserve(size_type new_capacity);

			size_type	capacity() const;

			// Modifiers
			void	clear();

			iterator	insert(const_iterator pos, const value_type& val);
			iterator	insert(const_iterator pos, size_type n, const value_type& val);
			template <typename InputIterator>
			iterator	insert(const_iterator pos, InputIterator first, InputIterator last);

			iterator	erase(iterator pos);
			iterator	erase(iterator first, iterator last);

			void	push_back(const value_type& value);

			void	pop_back();

			void	resize(size_type n, value_type val = value_type());

			void	swap(vector& vec);
	};
	// Non-member function overloads
	template <typename T, typename Allocator>
	bool	operator==(const ft::vector<T, Allocator>& x, const ft::vector<T, Allocator>& y);

	template <typename T, typename Allocator>
	bool	operator!=(const ft::vector<T, Allocator>& x, const ft::vector<T, Allocator>& y);

	template <typename T, typename Allocator>
	bool	operator<(const ft::vector<T, Allocator>& x, const ft::vector<T, Allocator>& y);

	template <typename T, typename Allocator>
	bool	operator<=(const ft::vector<T, Allocator>& x, const ft::vector<T, Allocator>& y);

	template <typename T, typename Allocator>
	bool	operator>(const ft::vector<T, Allocator>& x, const ft::vector<T, Allocator>& y);

	template <typename T, typename Allocator>
	bool	operator>=(const ft::vector<T, Allocator>& x, const ft::vector<T, Allocator>& y);

	// Non-member function
	template<typename T, typename Allocator>
	void	swap(ft::vector<T, Allocator>& x, ft::vector<T, Allocator>& y);
}

#endif

/*
	STL Reference
	https://en.cppreference.com/w/cpp/container/stack

	STL Base Header
	https://en.cppreference.com/w/cpp/header/stack
*/
