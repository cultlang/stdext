#pragma once
namespace stdext
{
	/******************************************************************************
	** stdext::pointer_view
	******************************************************************************/

	template<typename T>
	class pointer_view
	{
	private:
		T* _data;
		std::size_t _size;

	public:
		typedef T* iterator_type;
		typedef T const* const_iterator_type;

		pointer_view(T* data, std::size_t size)
			: _data(data)
			, _size(size)
		{ }

		const_iterator_type begin() const { return _data; }
		const_iterator_type end() const { return _data + _size; }

		iterator_type begin() { return _data; }
		iterator_type end() { return _data + _size; }
	};

	/******************************************************************************
	** stdext::breadth_first_iterator
	******************************************************************************/

	template<typename T> struct breadth_first_iterator;

	template<typename T> bool operator == (breadth_first_iterator<T> const& this_, breadth_first_iterator<T> const& that_);
	template<typename T> bool operator != (breadth_first_iterator<T> const& this_, breadth_first_iterator<T> const& that_);

	template<typename T>
	struct breadth_first_iterator
		: std::iterator<std::input_iterator_tag, T>
	{
		using real_type = typename std::remove_pointer<T>::type;
		using sub_iterator_type = typename real_type::iterator_type;

	private:
		std::queue<T> _queue;

		inline void _push_queue_front()
		{
			for (auto value : *_queue.front())
				_queue.push(value);
		}

		friend bool operator == <>(breadth_first_iterator<T> const&, breadth_first_iterator<T> const&);
		friend bool operator != <>(breadth_first_iterator<T> const&, breadth_first_iterator<T> const&);

	public:
		breadth_first_iterator(T const& root)
		{
			_queue.push(root);
			_push_queue_front();
		}

		breadth_first_iterator()
		{
		}

		breadth_first_iterator& operator++()
		{
			do { _queue.pop(); } while (!_queue.empty() && _queue.front() == nullptr);

			if (!_queue.empty())
				_push_queue_front();

			return *this;
		}

		T const& operator*() const
		{
			return _queue.front();
		}
	};

	template<typename T>
	bool operator == (breadth_first_iterator<T> const& this_, breadth_first_iterator<T> const& that_)
	{
		return this_._queue.size() == that_._queue.size() && this_._queue == that_._queue;
	}
	template<typename T>
	bool operator != (breadth_first_iterator<T> const& this_, breadth_first_iterator<T> const& that_)
	{
		return this_._queue.size() != that_._queue.size() && this_._queue != that_._queue;
	}

	/******************************************************************************
	** stdext::depth_first_iterator
	******************************************************************************/

	template<typename T> struct depth_first_iterator;

	template<typename T> bool operator == (depth_first_iterator<T> const& this_, depth_first_iterator<T> const& that_);
	template<typename T> bool operator != (depth_first_iterator<T> const& this_, depth_first_iterator<T> const& that_);

	template<typename T>
	struct depth_first_iterator
		: std::iterator<std::input_iterator_tag, T>
	{
		using real_type = typename std::remove_pointer<T>::type;
		using sub_iterator_type = typename real_type::iterator_type;

	private:
		std::stack<T> _stack;

		inline void _push_stack_top()
		{
			auto top = _stack.top(); _stack.pop();
			std::vector<T> temp; temp.reserve(8);
			for (auto value : *top)
				temp.push_back(value);
			for (auto it = temp.rbegin(); it != temp.rend(); ++it)
				_stack.push(*it);
			_stack.push(top);
		}

		friend bool operator == <>(depth_first_iterator<T> const&, depth_first_iterator<T> const&);
		friend bool operator != <>(depth_first_iterator<T> const&, depth_first_iterator<T> const&);

	public:
		depth_first_iterator(T const& root)
		{
			_stack.push(root);
			_push_stack_top();
		}

		depth_first_iterator()
		{
		}

		depth_first_iterator& operator++()
		{
			do { _stack.pop(); } while (!_stack.empty() && _stack.top() == nullptr);

			if (!_stack.empty())
				_push_stack_top();

			return *this;
		}

		T const& operator*() const
		{
			return _stack.top();
		}
	};

	template<typename T>
	bool operator == (depth_first_iterator<T> const& this_, depth_first_iterator<T> const& that_)
	{
		return this_._stack.size() == that_._stack.size() && this_._stack == that_._stack;
	}
	template<typename T>
	bool operator != (depth_first_iterator<T> const& this_, depth_first_iterator<T> const& that_)
	{
		return this_._stack.size() != that_._stack.size() && this_._stack != that_._stack;
	}

	/******************************************************************************
	** stdext::breadth_first_view
	******************************************************************************/

	template<typename T>
	class breadth_first_view
	{
	private:
		T* _root;

	public:
		typedef breadth_first_iterator<T*> iterator_type;
		typedef breadth_first_iterator<T const*> const_iterator_type;

		breadth_first_view(T* const& root)
			: _root(root)
		{ }

		const_iterator_type begin() const { return const_iterator_type(_root); }
		const_iterator_type end() const { return const_iterator_type(); }

		iterator_type begin() { return iterator_type(_root); }
		iterator_type end() { return iterator_type(); }
	};

	template<typename T>
	inline breadth_first_view<T> do_breadth_first(T* const& root)
	{
		return breadth_first_view<T>(root);
	}

	/******************************************************************************
	** stdext::depth_first_view
	******************************************************************************/

	template<typename T>
	class depth_first_view
	{
	private:
		T* _root;

	public:
		typedef depth_first_iterator<T*> iterator_type;
		typedef depth_first_iterator<T const*> const_iterator_type;

		depth_first_view(T* const& root)
			: _root(root)
		{ }

		const_iterator_type begin() const { return const_iterator_type(_root); }
		const_iterator_type end() const { return const_iterator_type(); }

		iterator_type begin() { return iterator_type(_root); }
		iterator_type end() { return iterator_type(); }
	};

	template<typename T>
	inline depth_first_view<T> do_depth_first(T* const& root)
	{
		return depth_first_view<T>(root);
	}


	/******************************************************************************
	** stdext::element_iterator
	******************************************************************************/

	template <size_t N, typename TIterator>
	struct element_iterator : private TIterator
	{
	private:
		TIterator _internal;
		
	public:
		typedef typename std::tuple_element<N, typename std::iterator_traits<TIterator>::value_type>::type value_type;
		typedef value_type& reference;
		typedef value_type* pointer;
		typedef typename std::iterator_traits<TIterator>::difference_type difference_type;
		typedef typename std::iterator_traits<TIterator>::iterator_category iterator_category;

		typedef element_iterator iterator;

		inline element_iterator(TIterator const& it) : _internal(it) { }

		inline pointer operator->() const { return &(std::get<N>(*_internal.operator->())); }
		inline value_type operator*() const { return std::get<N>(_internal.operator*()); }
		
		inline element_iterator& operator++()
		{
			_internal.operator++();
			return *this;
		}
		inline element_iterator operator++(int _)
		{
			return element_iterator(_internal.operator++(_));
		}
		
		inline bool operator==(const element_iterator& other) const { return _internal == other._internal; }
		inline bool operator!=(const element_iterator& other) const { return !(*this == other); }
	};

	template <typename TIterator>
	element_iterator<0, TIterator> key_iterator(TIterator const& it)
	{
		return { it };
	}

	template <typename TIterator>
	element_iterator<1, TIterator> value_iterator(TIterator const& it)
	{
		return { it };
	}

	template <size_t N, typename TIterator>
	element_iterator<N, TIterator> tuple_iterator(TIterator const& it)
	{
		return { it };
	}

	template <size_t N, typename TContainer>
	struct element_container_adaptor : public TContainer
	{
		typedef element_iterator<N, typename TContainer::const_iterator> const_iterator;

		inline element_container_adaptor(TContainer const& cn) : TContainer(cn) { }

		inline const_iterator begin() const { return const_iterator(TContainer::begin()); }
		inline const_iterator end() const { return const_iterator(TContainer::end()); }
		inline const_iterator cbegin() const { return const_iterator(TContainer::cbegin()); }
		inline const_iterator cend() const { return const_iterator(TContainer::cend()); }
	};

	template <typename TContainer>
	element_container_adaptor<0, TContainer> key_adaptor(TContainer const& cn)
	{
		return { cn };
	}

	template <typename TContainer>
	element_container_adaptor<1, TContainer> value_adaptor(TContainer const& cn)
	{
		return { cn };
	}

	template <size_t N, typename TContainer>
	element_container_adaptor<N, TContainer> tuple_adaptor(TContainer const& cn)
	{
		return { cn };
	}

}
