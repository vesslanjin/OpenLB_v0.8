




















 




 





















 




 






















 






 


















































 



 




















































 




 






























 












































































 
namespace std
{
  typedef unsigned long 	size_t;
  typedef long	ptrdiff_t;

}



























































































 























 







































































 


 


 

 







 


 

 


 




 

 


 


















 
















 



 


 






 


 


 

 

















 


 



 

 






 



 


 


 


 






 


 


 


 


 
 










 







 



 



 



 



 

 






 




 


 


 

 


 


 




 

 



 

 





 


 


 





 

 

 





 


































 
























 
 

 

 

 

 

 

 

 

 

 

 
 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 
 

 
 

 

 

 


 

 

 

 

 

 
 

 

 

 
 

 

 

 

 

 

 

 

 

 

 

 

 
 

 
 

 
 

 
 

 
 

 
 

 

 

 

 

 

 

 
 

 
 

 

 

 

 

 

 
 

 

 

 

 
 

 
 

 

 

 

 

 

 

 

 

 

 

 

 

 
 

 

 

 

 

 

 
 


 

 
 

 

 

 
 

 
 

 

 

 

 

 

 

 

 
 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 
 

 


 

 
 

 

 

 

 

 

 

 
 

 
 

 
 

 
 

 
 

 

 
 

 


 

 


 

 
 

 
 

 

 

 

 
 

 
 

 
 

 
 

 

 

 

 

 
 

 

 
 

 
 


 



 



 


 


 


 


 


 


 


 

 
 

 
 


 

 

 

 

 
 

 
 


 

 
 

 































































































 



































 





namespace std __attribute__ ((__visibility__ ("default")))
{


  
  void
  __throw_bad_exception(void) __attribute__((__noreturn__));

  
  void
  __throw_bad_alloc(void) __attribute__((__noreturn__));

  
  void
  __throw_bad_cast(void) __attribute__((__noreturn__));

  void
  __throw_bad_typeid(void) __attribute__((__noreturn__));

  
  void
  __throw_logic_error(const char*) __attribute__((__noreturn__));

  void
  __throw_domain_error(const char*) __attribute__((__noreturn__));

  void
  __throw_invalid_argument(const char*) __attribute__((__noreturn__));

  void
  __throw_length_error(const char*) __attribute__((__noreturn__));

  void
  __throw_out_of_range(const char*) __attribute__((__noreturn__));

  void
  __throw_runtime_error(const char*) __attribute__((__noreturn__));

  void
  __throw_range_error(const char*) __attribute__((__noreturn__));

  void
  __throw_overflow_error(const char*) __attribute__((__noreturn__));

  void
  __throw_underflow_error(const char*) __attribute__((__noreturn__));

  
  void
  __throw_ios_failure(const char*) __attribute__((__noreturn__));

  void
  __throw_system_error(int) __attribute__((__noreturn__));

  void
  __throw_future_error(int) __attribute__((__noreturn__));

  
  void
  __throw_bad_function_call() __attribute__((__noreturn__));


} 





























 



































namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{


  template<typename _Iterator, typename _Container>
    class __normal_iterator;


} 

namespace std __attribute__ ((__visibility__ ("default")))
{


  struct __true_type { };
  struct __false_type { };

  template<bool>
    struct __truth_type
    { typedef __false_type __type; };

  template<>
    struct __truth_type<true>
    { typedef __true_type __type; };

  
  
  template<class _Sp, class _Tp>
    struct __traitor
    {
      enum { __value = bool(_Sp::__value) || bool(_Tp::__value) };
      typedef typename __truth_type<__value>::__type __type;
    };

  
  template<typename, typename>
    struct __are_same
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  template<typename _Tp>
    struct __are_same<_Tp, _Tp>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  
  template<typename _Tp>
    struct __is_void
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  template<>
    struct __is_void<void>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  
  
  
  template<typename _Tp>
    struct __is_integer
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  
  
  
  template<>
    struct __is_integer<bool>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<signed char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<unsigned char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<wchar_t>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };


  template<>
    struct __is_integer<short>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<unsigned short>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<int>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<unsigned int>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<unsigned long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<long long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<unsigned long long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  
  
  
  template<typename _Tp>
    struct __is_floating
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  
  template<>
    struct __is_floating<float>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_floating<double>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_floating<long double>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  
  
  
  template<typename _Tp>
    struct __is_pointer
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  template<typename _Tp>
    struct __is_pointer<_Tp*>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  
  
  
  template<typename _Tp>
    struct __is_normal_iterator
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  template<typename _Iterator, typename _Container>
    struct __is_normal_iterator< __gnu_cxx::__normal_iterator<_Iterator,
							      _Container> >
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  
  
  
  template<typename _Tp>
    struct __is_arithmetic
    : public __traitor<__is_integer<_Tp>, __is_floating<_Tp> >
    { };

  
  
  
  template<typename _Tp>
    struct __is_fundamental
    : public __traitor<__is_void<_Tp>, __is_arithmetic<_Tp> >
    { };

  
  
  
  template<typename _Tp>
    struct __is_scalar
    : public __traitor<__is_arithmetic<_Tp>, __is_pointer<_Tp> >
    { };

  
  
  
  template<typename _Tp>
    struct __is_char
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  template<>
    struct __is_char<char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_char<wchar_t>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<typename _Tp>
    struct __is_byte
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  template<>
    struct __is_byte<char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_byte<signed char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_byte<unsigned char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  
  
  
  template<typename _Tp>
    struct __is_move_iterator
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };



} 



























 




namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{


  
  template<bool, typename>
    struct __enable_if 
    { };

  template<typename _Tp>
    struct __enable_if<true, _Tp>
    { typedef _Tp __type; };


  
  template<bool _Cond, typename _Iftrue, typename _Iffalse>
    struct __conditional_type
    { typedef _Iftrue __type; };

  template<typename _Iftrue, typename _Iffalse>
    struct __conditional_type<false, _Iftrue, _Iffalse>
    { typedef _Iffalse __type; };


  
  template<typename _Tp>
    struct __add_unsigned
    { 
    private:
      typedef __enable_if<std::__is_integer<_Tp>::__value, _Tp> __if_type;
      
    public:
      typedef typename __if_type::__type __type; 
    };

  template<>
    struct __add_unsigned<char>
    { typedef unsigned char __type; };

  template<>
    struct __add_unsigned<signed char>
    { typedef unsigned char __type; };

  template<>
    struct __add_unsigned<short>
    { typedef unsigned short __type; };

  template<>
    struct __add_unsigned<int>
    { typedef unsigned int __type; };

  template<>
    struct __add_unsigned<long>
    { typedef unsigned long __type; };

  template<>
    struct __add_unsigned<long long>
    { typedef unsigned long long __type; };

  
  template<>
    struct __add_unsigned<bool>;

  template<>
    struct __add_unsigned<wchar_t>;


  
  template<typename _Tp>
    struct __remove_unsigned
    { 
    private:
      typedef __enable_if<std::__is_integer<_Tp>::__value, _Tp> __if_type;
      
    public:
      typedef typename __if_type::__type __type; 
    };

  template<>
    struct __remove_unsigned<char>
    { typedef signed char __type; };

  template<>
    struct __remove_unsigned<unsigned char>
    { typedef signed char __type; };

  template<>
    struct __remove_unsigned<unsigned short>
    { typedef short __type; };

  template<>
    struct __remove_unsigned<unsigned int>
    { typedef int __type; };

  template<>
    struct __remove_unsigned<unsigned long>
    { typedef long __type; };

  template<>
    struct __remove_unsigned<unsigned long long>
    { typedef long long __type; };

  
  template<>
    struct __remove_unsigned<bool>;

  template<>
    struct __remove_unsigned<wchar_t>;


  
  template<typename _Type>
    inline bool
    __is_null_pointer(_Type* __ptr)
    { return __ptr == 0; }

  template<typename _Type>
    inline bool
    __is_null_pointer(_Type)
    { return false; }


  
  template<typename _Tp, bool = std::__is_integer<_Tp>::__value>
    struct __promote
    { typedef double __type; };

  template<typename _Tp>
    struct __promote<_Tp, false>
    { typedef _Tp __type; };

  template<typename _Tp, typename _Up>
    struct __promote_2
    {
    private:
      typedef typename __promote<_Tp>::__type __type1;
      typedef typename __promote<_Up>::__type __type2;

    public:
      typedef __typeof__(__type1() + __type2()) __type;
    };

  template<typename _Tp, typename _Up, typename _Vp>
    struct __promote_3
    {
    private:
      typedef typename __promote<_Tp>::__type __type1;
      typedef typename __promote<_Up>::__type __type2;
      typedef typename __promote<_Vp>::__type __type3;

    public:
      typedef __typeof__(__type1() + __type2() + __type3()) __type;
    };

  template<typename _Tp, typename _Up, typename _Vp, typename _Wp>
    struct __promote_4
    {
    private:
      typedef typename __promote<_Tp>::__type __type1;
      typedef typename __promote<_Up>::__type __type2;
      typedef typename __promote<_Vp>::__type __type3;
      typedef typename __promote<_Wp>::__type __type4;

    public:
      typedef __typeof__(__type1() + __type2() + __type3() + __type4()) __type;
    };


} 



























 




namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{


  
  



  template<typename _Value>
    struct __numeric_traits_integer
    {
      
      static const _Value __min = (((_Value)(-1) < 0) ? (_Value)1 << (sizeof(_Value) * 8 - ((_Value)(-1) < 0)) : (_Value)0);
      static const _Value __max = (((_Value)(-1) < 0) ? (((((_Value)1 << ((sizeof(_Value) * 8 - ((_Value)(-1) < 0)) - 1)) - 1) << 1) + 1) : ~(_Value)0);

      
      
      static const bool __is_signed = ((_Value)(-1) < 0);
      static const int __digits = (sizeof(_Value) * 8 - ((_Value)(-1) < 0));      
    };

  template<typename _Value>
    const _Value __numeric_traits_integer<_Value>::__min;

  template<typename _Value>
    const _Value __numeric_traits_integer<_Value>::__max;

  template<typename _Value>
    const bool __numeric_traits_integer<_Value>::__is_signed;

  template<typename _Value>
    const int __numeric_traits_integer<_Value>::__digits;






  template<typename _Value>
    struct __numeric_traits_floating
    {
      
      static const int __max_digits10 = (2 + (std::__are_same<_Value, float> ::__value ? 24 : std::__are_same<_Value, double> ::__value ? 53 : 64) * 643L / 2136);

      
      static const bool __is_signed = true;
      static const int __digits10 = (std::__are_same<_Value, float> ::__value ? 6 : std::__are_same<_Value, double> ::__value ? 15 : 18);
      static const int __max_exponent10 = (std::__are_same<_Value, float> ::__value ? 38 : std::__are_same<_Value, double> ::__value ? 308 : 4932);
    };

  template<typename _Value>
    const int __numeric_traits_floating<_Value>::__max_digits10;

  template<typename _Value>
    const bool __numeric_traits_floating<_Value>::__is_signed;

  template<typename _Value>
    const int __numeric_traits_floating<_Value>::__digits10;

  template<typename _Value>
    const int __numeric_traits_floating<_Value>::__max_exponent10;

  template<typename _Value>
    struct __numeric_traits
    : public __conditional_type<std::__is_integer<_Value>::__value,
				__numeric_traits_integer<_Value>,
				__numeric_traits_floating<_Value> >::__type
    { };


} 



















































 




 





























 





























 
















namespace std __attribute__ ((__visibility__ ("default")))
{


  
  template<typename _Tp>
    inline _Tp*
    __addressof(_Tp& __r)
    {
      return reinterpret_cast<_Tp*>
	(&const_cast<char&>(reinterpret_cast<const volatile char&>(__r)));
    }


} 


namespace std __attribute__ ((__visibility__ ("default")))
{


  





 
  template<typename _Tp>
    inline void
    swap(_Tp& __a, _Tp& __b)
    {
      
      

      _Tp __tmp = (__a);
      __a = (__b);
      __b = (__tmp);
    }

  
  
  template<typename _Tp, size_t _Nm>
    inline void
    swap(_Tp (&__a)[_Nm], _Tp (&__b)[_Nm])
    {
      for (size_t __n = 0; __n < _Nm; ++__n)
	swap(__a[__n], __b[__n]);
    }


} 



namespace std __attribute__ ((__visibility__ ("default")))
{



  
  template<class _T1, class _T2>
    struct pair
    {
      typedef _T1 first_type;    
      typedef _T2 second_type;   

      _T1 first;                 
      _T2 second;                

      
      
      
 
       pair()
      : first(), second() { }

       
       pair(const _T1& __a, const _T2& __b)
      : first(__a), second(__b) { }

       
      template<class _U1, class _U2>
	 pair(const pair<_U1, _U2>& __p)
	: first(__p.first), second(__p.second) { }

    };

  
  template<class _T1, class _T2>
    inline  bool
    operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return __x.first == __y.first && __x.second == __y.second; }

  
  template<class _T1, class _T2>
    inline  bool
    operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return __x.first < __y.first
	     || (!(__y.first < __x.first) && __x.second < __y.second); }

  
  template<class _T1, class _T2>
    inline  bool
    operator!=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return !(__x == __y); }

  
  template<class _T1, class _T2>
    inline  bool
    operator>(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return __y < __x; }

  
  template<class _T1, class _T2>
    inline  bool
    operator<=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return !(__y < __x); }

  
  template<class _T1, class _T2>
    inline  bool
    operator>=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return !(__x < __y); }


  








 
  
  
  template<class _T1, class _T2>
    inline pair<_T1, _T2>
    make_pair(_T1 __x, _T2 __y)
    { return pair<_T1, _T2>(__x, __y); }


} 


















































 







 





namespace std __attribute__ ((__visibility__ ("default")))
{


  


 
  

  





 
  
  
  struct input_iterator_tag { };

  
  struct output_iterator_tag { };

  
  struct forward_iterator_tag : public input_iterator_tag { };

  
  
  struct bidirectional_iterator_tag : public forward_iterator_tag { };

  
  
  struct random_access_iterator_tag : public bidirectional_iterator_tag { };
  

  








 
  template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
           typename _Pointer = _Tp*, typename _Reference = _Tp&>
    struct iterator
    {
      
      typedef _Category  iterator_category;
      
      typedef _Tp        value_type;
      
      typedef _Distance  difference_type;
      
      typedef _Pointer   pointer;
      
      typedef _Reference reference;
    };

  






 
  template<typename _Iterator>
    struct iterator_traits
    {
      typedef typename _Iterator::iterator_category iterator_category;
      typedef typename _Iterator::value_type        value_type;
      typedef typename _Iterator::difference_type   difference_type;
      typedef typename _Iterator::pointer           pointer;
      typedef typename _Iterator::reference         reference;
    };

  
  template<typename _Tp>
    struct iterator_traits<_Tp*>
    {
      typedef random_access_iterator_tag iterator_category;
      typedef _Tp                         value_type;
      typedef ptrdiff_t                   difference_type;
      typedef _Tp*                        pointer;
      typedef _Tp&                        reference;
    };

  
  template<typename _Tp>
    struct iterator_traits<const _Tp*>
    {
      typedef random_access_iterator_tag iterator_category;
      typedef _Tp                         value_type;
      typedef ptrdiff_t                   difference_type;
      typedef const _Tp*                  pointer;
      typedef const _Tp&                  reference;
    };

  


 
  template<typename _Iter>
    inline typename iterator_traits<_Iter>::iterator_category
    __iterator_category(const _Iter&)
    { return typename iterator_traits<_Iter>::iterator_category(); }

  

  
  
  template<typename _Iterator, bool _HasBase>
    struct _Iter_base
    {
      typedef _Iterator iterator_type;
      static iterator_type _S_base(_Iterator __it)
      { return __it; }
    };

  template<typename _Iterator>
    struct _Iter_base<_Iterator, true>
    {
      typedef typename _Iterator::iterator_type iterator_type;
      static iterator_type _S_base(_Iterator __it)
      { return __it.base(); }
    };


} 



















































 







 




namespace std __attribute__ ((__visibility__ ("default")))
{


  template<typename _InputIterator>
    inline typename iterator_traits<_InputIterator>::difference_type
    __distance(_InputIterator __first, _InputIterator __last,
               input_iterator_tag)
    {
      
      

      typename iterator_traits<_InputIterator>::difference_type __n = 0;
      while (__first != __last)
	{
	  ++__first;
	  ++__n;
	}
      return __n;
    }

  template<typename _RandomAccessIterator>
    inline typename iterator_traits<_RandomAccessIterator>::difference_type
    __distance(_RandomAccessIterator __first, _RandomAccessIterator __last,
               random_access_iterator_tag)
    {
      
      
      return __last - __first;
    }

  










 
  template<typename _InputIterator>
    inline typename iterator_traits<_InputIterator>::difference_type
    distance(_InputIterator __first, _InputIterator __last)
    {
      
      return std::__distance(__first, __last,
			     std::__iterator_category(__first));
    }

  template<typename _InputIterator, typename _Distance>
    inline void
    __advance(_InputIterator& __i, _Distance __n, input_iterator_tag)
    {
      
      
      while (__n--)
	++__i;
    }

  template<typename _BidirectionalIterator, typename _Distance>
    inline void
    __advance(_BidirectionalIterator& __i, _Distance __n,
	      bidirectional_iterator_tag)
    {
      
      
      if (__n > 0)
        while (__n--)
	  ++__i;
      else
        while (__n++)
	  --__i;
    }

  template<typename _RandomAccessIterator, typename _Distance>
    inline void
    __advance(_RandomAccessIterator& __i, _Distance __n,
              random_access_iterator_tag)
    {
      
      
      __i += __n;
    }

  










 
  template<typename _InputIterator, typename _Distance>
    inline void
    advance(_InputIterator& __i, _Distance __n)
    {
      
      typename iterator_traits<_InputIterator>::difference_type __d = __n;
      std::__advance(__i, __d, std::__iterator_category(__i));
    }



} 


















































 








 



namespace std __attribute__ ((__visibility__ ("default")))
{


  


 

  
  
















 
  template<typename _Iterator>
    class reverse_iterator
    : public iterator<typename iterator_traits<_Iterator>::iterator_category,
		      typename iterator_traits<_Iterator>::value_type,
		      typename iterator_traits<_Iterator>::difference_type,
		      typename iterator_traits<_Iterator>::pointer,
                      typename iterator_traits<_Iterator>::reference>
    {
    protected:
      _Iterator current;

      typedef iterator_traits<_Iterator>		__traits_type;

    public:
      typedef _Iterator					iterator_type;
      typedef typename __traits_type::difference_type	difference_type;
      typedef typename __traits_type::pointer		pointer;
      typedef typename __traits_type::reference		reference;

      


 
      
      
      reverse_iterator() : current() { }

      

 
      explicit
      reverse_iterator(iterator_type __x) : current(__x) { }

      

 
      reverse_iterator(const reverse_iterator& __x)
      : current(__x.current) { }

      


 
      template<typename _Iter>
        reverse_iterator(const reverse_iterator<_Iter>& __x)
	: current(__x.base()) { }

      

 
      iterator_type
      base() const
      { return current; }

      



 
      reference
      operator*() const
      {
	_Iterator __tmp = current;
	return *--__tmp;
      }

      



 
      pointer
      operator->() const
      { return &(operator*()); }

      



 
      reverse_iterator&
      operator++()
      {
	--current;
	return *this;
      }

      



 
      reverse_iterator
      operator++(int)
      {
	reverse_iterator __tmp = *this;
	--current;
	return __tmp;
      }

      



 
      reverse_iterator&
      operator--()
      {
	++current;
	return *this;
      }

      



 
      reverse_iterator
      operator--(int)
      {
	reverse_iterator __tmp = *this;
	++current;
	return __tmp;
      }

      



 
      reverse_iterator
      operator+(difference_type __n) const
      { return reverse_iterator(current - __n); }

      



 
      reverse_iterator&
      operator+=(difference_type __n)
      {
	current -= __n;
	return *this;
      }

      



 
      reverse_iterator
      operator-(difference_type __n) const
      { return reverse_iterator(current + __n); }

      



 
      reverse_iterator&
      operator-=(difference_type __n)
      {
	current += __n;
	return *this;
      }

      



 
      reference
      operator[](difference_type __n) const
      { return *(*this + __n); }
    };

  
  







 
  template<typename _Iterator>
    inline bool
    operator==(const reverse_iterator<_Iterator>& __x,
	       const reverse_iterator<_Iterator>& __y)
    { return __x.base() == __y.base(); }

  template<typename _Iterator>
    inline bool
    operator<(const reverse_iterator<_Iterator>& __x,
	      const reverse_iterator<_Iterator>& __y)
    { return __y.base() < __x.base(); }

  template<typename _Iterator>
    inline bool
    operator!=(const reverse_iterator<_Iterator>& __x,
	       const reverse_iterator<_Iterator>& __y)
    { return !(__x == __y); }

  template<typename _Iterator>
    inline bool
    operator>(const reverse_iterator<_Iterator>& __x,
	      const reverse_iterator<_Iterator>& __y)
    { return __y < __x; }

  template<typename _Iterator>
    inline bool
    operator<=(const reverse_iterator<_Iterator>& __x,
	       const reverse_iterator<_Iterator>& __y)
    { return !(__y < __x); }

  template<typename _Iterator>
    inline bool
    operator>=(const reverse_iterator<_Iterator>& __x,
	       const reverse_iterator<_Iterator>& __y)
    { return !(__x < __y); }

  template<typename _Iterator>
    inline typename reverse_iterator<_Iterator>::difference_type
    operator-(const reverse_iterator<_Iterator>& __x,
	      const reverse_iterator<_Iterator>& __y)
    { return __y.base() - __x.base(); }

  template<typename _Iterator>
    inline reverse_iterator<_Iterator>
    operator+(typename reverse_iterator<_Iterator>::difference_type __n,
	      const reverse_iterator<_Iterator>& __x)
    { return reverse_iterator<_Iterator>(__x.base() - __n); }

  
  
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator==(const reverse_iterator<_IteratorL>& __x,
	       const reverse_iterator<_IteratorR>& __y)
    { return __x.base() == __y.base(); }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator<(const reverse_iterator<_IteratorL>& __x,
	      const reverse_iterator<_IteratorR>& __y)
    { return __y.base() < __x.base(); }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator!=(const reverse_iterator<_IteratorL>& __x,
	       const reverse_iterator<_IteratorR>& __y)
    { return !(__x == __y); }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator>(const reverse_iterator<_IteratorL>& __x,
	      const reverse_iterator<_IteratorR>& __y)
    { return __y < __x; }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator<=(const reverse_iterator<_IteratorL>& __x,
	       const reverse_iterator<_IteratorR>& __y)
    { return !(__y < __x); }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator>=(const reverse_iterator<_IteratorL>& __x,
	       const reverse_iterator<_IteratorR>& __y)
    { return !(__x < __y); }

  template<typename _IteratorL, typename _IteratorR>
    inline typename reverse_iterator<_IteratorL>::difference_type
    operator-(const reverse_iterator<_IteratorL>& __x,
	      const reverse_iterator<_IteratorR>& __y)
    { return __y.base() - __x.base(); }
  

  
  








 
  template<typename _Container>
    class back_insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;

    public:
      
      typedef _Container          container_type;

      
      explicit
      back_insert_iterator(_Container& __x) : container(&__x) { }

      









 
      back_insert_iterator&
      operator=(typename _Container::const_reference __value)
      {
	container->push_back(__value);
	return *this;
      }

      
      back_insert_iterator&
      operator*()
      { return *this; }

      
      back_insert_iterator&
      operator++()
      { return *this; }

      
      back_insert_iterator
      operator++(int)
      { return *this; }
    };

  









 
  template<typename _Container>
    inline back_insert_iterator<_Container>
    back_inserter(_Container& __x)
    { return back_insert_iterator<_Container>(__x); }

  








 
  template<typename _Container>
    class front_insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;

    public:
      
      typedef _Container          container_type;

      
      explicit front_insert_iterator(_Container& __x) : container(&__x) { }

      









 
      front_insert_iterator&
      operator=(typename _Container::const_reference __value)
      {
	container->push_front(__value);
	return *this;
      }

      
      front_insert_iterator&
      operator*()
      { return *this; }

      
      front_insert_iterator&
      operator++()
      { return *this; }

      
      front_insert_iterator
      operator++(int)
      { return *this; }
    };

  









 
  template<typename _Container>
    inline front_insert_iterator<_Container>
    front_inserter(_Container& __x)
    { return front_insert_iterator<_Container>(__x); }

  












 
  template<typename _Container>
    class insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;
      typename _Container::iterator iter;

    public:
      
      typedef _Container          container_type;

      


 
      insert_iterator(_Container& __x, typename _Container::iterator __i)
      : container(&__x), iter(__i) {}

      





















 
      insert_iterator&
      operator=(typename _Container::const_reference __value)
      {
	iter = container->insert(iter, __value);
	++iter;
	return *this;
      }

      
      insert_iterator&
      operator*()
      { return *this; }

      
      insert_iterator&
      operator++()
      { return *this; }

      
      insert_iterator&
      operator++(int)
      { return *this; }
    };

  









 
  template<typename _Container, typename _Iterator>
    inline insert_iterator<_Container>
    inserter(_Container& __x, _Iterator __i)
    {
      return insert_iterator<_Container>(__x,
					 typename _Container::iterator(__i));
    }

  


} 

namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{


  
  
  
  
  
  
  
  using std::iterator_traits;
  using std::iterator;
  template<typename _Iterator, typename _Container>
    class __normal_iterator
    {
    protected:
      _Iterator _M_current;

      typedef iterator_traits<_Iterator>		__traits_type;

    public:
      typedef _Iterator					iterator_type;
      typedef typename __traits_type::iterator_category iterator_category;
      typedef typename __traits_type::value_type  	value_type;
      typedef typename __traits_type::difference_type 	difference_type;
      typedef typename __traits_type::reference 	reference;
      typedef typename __traits_type::pointer   	pointer;

       __normal_iterator() : _M_current(_Iterator()) { }

      explicit
      __normal_iterator(const _Iterator& __i) : _M_current(__i) { }

      
      template<typename _Iter>
        __normal_iterator(const __normal_iterator<_Iter,
			  typename __enable_if<
      	       (std::__are_same<_Iter, typename _Container::pointer>::__value),
		      _Container>::__type>& __i)
        : _M_current(__i.base()) { }

      
      reference
      operator*() const
      { return *_M_current; }

      pointer
      operator->() const
      { return _M_current; }

      __normal_iterator&
      operator++()
      {
	++_M_current;
	return *this;
      }

      __normal_iterator
      operator++(int)
      { return __normal_iterator(_M_current++); }

      
      __normal_iterator&
      operator--()
      {
	--_M_current;
	return *this;
      }

      __normal_iterator
      operator--(int)
      { return __normal_iterator(_M_current--); }

      
      reference
      operator[](const difference_type& __n) const
      { return _M_current[__n]; }

      __normal_iterator&
      operator+=(const difference_type& __n)
      { _M_current += __n; return *this; }

      __normal_iterator
      operator+(const difference_type& __n) const
      { return __normal_iterator(_M_current + __n); }

      __normal_iterator&
      operator-=(const difference_type& __n)
      { _M_current -= __n; return *this; }

      __normal_iterator
      operator-(const difference_type& __n) const
      { return __normal_iterator(_M_current - __n); }

      const _Iterator&
      base() const
      { return _M_current; }
    };

  
  
  
  
  
  
  

  
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator==(const __normal_iterator<_IteratorL, _Container>& __lhs,
	       const __normal_iterator<_IteratorR, _Container>& __rhs)
    { return __lhs.base() == __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline bool
    operator==(const __normal_iterator<_Iterator, _Container>& __lhs,
	       const __normal_iterator<_Iterator, _Container>& __rhs)
    { return __lhs.base() == __rhs.base(); }

  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator!=(const __normal_iterator<_IteratorL, _Container>& __lhs,
	       const __normal_iterator<_IteratorR, _Container>& __rhs)
    { return __lhs.base() != __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline bool
    operator!=(const __normal_iterator<_Iterator, _Container>& __lhs,
	       const __normal_iterator<_Iterator, _Container>& __rhs)
    { return __lhs.base() != __rhs.base(); }

  
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator<(const __normal_iterator<_IteratorL, _Container>& __lhs,
	      const __normal_iterator<_IteratorR, _Container>& __rhs)
    { return __lhs.base() < __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline bool
    operator<(const __normal_iterator<_Iterator, _Container>& __lhs,
	      const __normal_iterator<_Iterator, _Container>& __rhs)
    { return __lhs.base() < __rhs.base(); }

  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator>(const __normal_iterator<_IteratorL, _Container>& __lhs,
	      const __normal_iterator<_IteratorR, _Container>& __rhs)
    { return __lhs.base() > __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline bool
    operator>(const __normal_iterator<_Iterator, _Container>& __lhs,
	      const __normal_iterator<_Iterator, _Container>& __rhs)
    { return __lhs.base() > __rhs.base(); }

  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator<=(const __normal_iterator<_IteratorL, _Container>& __lhs,
	       const __normal_iterator<_IteratorR, _Container>& __rhs)
    { return __lhs.base() <= __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline bool
    operator<=(const __normal_iterator<_Iterator, _Container>& __lhs,
	       const __normal_iterator<_Iterator, _Container>& __rhs)
    { return __lhs.base() <= __rhs.base(); }

  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator>=(const __normal_iterator<_IteratorL, _Container>& __lhs,
	       const __normal_iterator<_IteratorR, _Container>& __rhs)
    { return __lhs.base() >= __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline bool
    operator>=(const __normal_iterator<_Iterator, _Container>& __lhs,
	       const __normal_iterator<_Iterator, _Container>& __rhs)
    { return __lhs.base() >= __rhs.base(); }

  
  
  
  
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline typename __normal_iterator<_IteratorL, _Container>::difference_type
    operator-(const __normal_iterator<_IteratorL, _Container>& __lhs,
	      const __normal_iterator<_IteratorR, _Container>& __rhs)
    { return __lhs.base() - __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline typename __normal_iterator<_Iterator, _Container>::difference_type
    operator-(const __normal_iterator<_Iterator, _Container>& __lhs,
	      const __normal_iterator<_Iterator, _Container>& __rhs)
    { return __lhs.base() - __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline __normal_iterator<_Iterator, _Container>
    operator+(typename __normal_iterator<_Iterator, _Container>::difference_type
	      __n, const __normal_iterator<_Iterator, _Container>& __i)
    { return __normal_iterator<_Iterator, _Container>(__i.base() + __n); }


} 





























 








 






 
namespace std
{ 
  namespace __debug { } 
}



 
namespace __gnu_debug
{
  using namespace std::__debug;
}





namespace std __attribute__ ((__visibility__ ("default")))
{


  
  
  
  template<bool _BoolType>
    struct __iter_swap
    {
      template<typename _ForwardIterator1, typename _ForwardIterator2>
        static void
        iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
        {
          typedef typename iterator_traits<_ForwardIterator1>::value_type
            _ValueType1;
          _ValueType1 __tmp = (*__a);
          *__a = (*__b);
          *__b = (__tmp);
	}
    };

  template<>
    struct __iter_swap<true>
    {
      template<typename _ForwardIterator1, typename _ForwardIterator2>
        static void 
        iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
        {
          swap(*__a, *__b);
        }
    };

  








 
  template<typename _ForwardIterator1, typename _ForwardIterator2>
    inline void
    iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
    {
      typedef typename iterator_traits<_ForwardIterator1>::value_type
	_ValueType1;
      typedef typename iterator_traits<_ForwardIterator2>::value_type
	_ValueType2;

      
      
      
      
      

      typedef typename iterator_traits<_ForwardIterator1>::reference
	_ReferenceType1;
      typedef typename iterator_traits<_ForwardIterator2>::reference
	_ReferenceType2;
      std::__iter_swap<__are_same<_ValueType1, _ValueType2>::__value
	&& __are_same<_ValueType1&, _ReferenceType1>::__value
	&& __are_same<_ValueType2&, _ReferenceType2>::__value>::
	iter_swap(__a, __b);
    }

  










 
  template<typename _ForwardIterator1, typename _ForwardIterator2>
    _ForwardIterator2
    swap_ranges(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
		_ForwardIterator2 __first2)
    {
      
      
      
      ;

      for (; __first1 != __last1; ++__first1, ++__first2)
	std::iter_swap(__first1, __first2);
      return __first2;
    }

  









 
  template<typename _Tp>
    inline const _Tp&
    min(const _Tp& __a, const _Tp& __b)
    {
      
      
      
      if (__b < __a)
	return __b;
      return __a;
    }

  









 
  template<typename _Tp>
    inline const _Tp&
    max(const _Tp& __a, const _Tp& __b)
    {
      
      
      
      if (__a < __b)
	return __b;
      return __a;
    }

  









 
  template<typename _Tp, typename _Compare>
    inline const _Tp&
    min(const _Tp& __a, const _Tp& __b, _Compare __comp)
    {
      
      if (__comp(__b, __a))
	return __b;
      return __a;
    }

  









 
  template<typename _Tp, typename _Compare>
    inline const _Tp&
    max(const _Tp& __a, const _Tp& __b, _Compare __comp)
    {
      
      if (__comp(__a, __b))
	return __b;
      return __a;
    }

  
  
  template<typename _Iterator>
    struct _Niter_base
    : _Iter_base<_Iterator, __is_normal_iterator<_Iterator>::__value>
    { };

  template<typename _Iterator>
    inline typename _Niter_base<_Iterator>::iterator_type
    __niter_base(_Iterator __it)
    { return std::_Niter_base<_Iterator>::_S_base(__it); }

  
  template<typename _Iterator>
    struct _Miter_base
    : _Iter_base<_Iterator, __is_move_iterator<_Iterator>::__value>
    { };

  template<typename _Iterator>
    inline typename _Miter_base<_Iterator>::iterator_type
    __miter_base(_Iterator __it)
    { return std::_Miter_base<_Iterator>::_S_base(__it); }

  
  
  
  
  

  template<bool, bool, typename>
    struct __copy_move
    {
      template<typename _II, typename _OI>
        static _OI
        __copy_m(_II __first, _II __last, _OI __result)
        {
	  for (; __first != __last; ++__result, ++__first)
	    *__result = *__first;
	  return __result;
	}
    };


  template<>
    struct __copy_move<false, false, random_access_iterator_tag>
    {
      template<typename _II, typename _OI>
        static _OI
        __copy_m(_II __first, _II __last, _OI __result)
        { 
	  typedef typename iterator_traits<_II>::difference_type _Distance;
	  for(_Distance __n = __last - __first; __n > 0; --__n)
	    {
	      *__result = *__first;
	      ++__first;
	      ++__result;
	    }
	  return __result;
	}
    };


  template<bool _IsMove>
    struct __copy_move<_IsMove, true, random_access_iterator_tag>
    {
      template<typename _Tp>
        static _Tp*
        __copy_m(const _Tp* __first, const _Tp* __last, _Tp* __result)
        {
	  const ptrdiff_t _Num = __last - __first;
	  if (_Num)
	    __builtin_memmove(__result, __first, sizeof(_Tp) * _Num);
	  return __result + _Num;
	}
    };

  template<bool _IsMove, typename _II, typename _OI>
    inline _OI
    __copy_move_a(_II __first, _II __last, _OI __result)
    {
      typedef typename iterator_traits<_II>::value_type _ValueTypeI;
      typedef typename iterator_traits<_OI>::value_type _ValueTypeO;
      typedef typename iterator_traits<_II>::iterator_category _Category;
      const bool __simple = (__is_trivial(_ValueTypeI)
	                     && __is_pointer<_II>::__value
	                     && __is_pointer<_OI>::__value
			     && __are_same<_ValueTypeI, _ValueTypeO>::__value);

      return std::__copy_move<_IsMove, __simple,
	                      _Category>::__copy_m(__first, __last, __result);
    }

  
  
  template<typename _CharT>
    struct char_traits;

  template<typename _CharT, typename _Traits>
    class istreambuf_iterator;

  template<typename _CharT, typename _Traits>
    class ostreambuf_iterator;

  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value, 
	     ostreambuf_iterator<_CharT, char_traits<_CharT> > >::__type
    __copy_move_a2(_CharT*, _CharT*,
		   ostreambuf_iterator<_CharT, char_traits<_CharT> >);

  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value, 
	     ostreambuf_iterator<_CharT, char_traits<_CharT> > >::__type
    __copy_move_a2(const _CharT*, const _CharT*,
		   ostreambuf_iterator<_CharT, char_traits<_CharT> >);

  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
				    _CharT*>::__type
    __copy_move_a2(istreambuf_iterator<_CharT, char_traits<_CharT> >,
		   istreambuf_iterator<_CharT, char_traits<_CharT> >, _CharT*);

  template<bool _IsMove, typename _II, typename _OI>
    inline _OI
    __copy_move_a2(_II __first, _II __last, _OI __result)
    {
      return _OI(std::__copy_move_a<_IsMove>(std::__niter_base(__first),
					     std::__niter_base(__last),
					     std::__niter_base(__result)));
    }

  















 
  template<typename _II, typename _OI>
    inline _OI
    copy(_II __first, _II __last, _OI __result)
    {
      
      
      
      ;

      return (std::__copy_move_a2<__is_move_iterator<_II>::__value>
	      (std::__miter_base(__first), std::__miter_base(__last),
	       __result));
    }


  template<bool, bool, typename>
    struct __copy_move_backward
    {
      template<typename _BI1, typename _BI2>
        static _BI2
        __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
        {
	  while (__first != __last)
	    *--__result = *--__last;
	  return __result;
	}
    };


  template<>
    struct __copy_move_backward<false, false, random_access_iterator_tag>
    {
      template<typename _BI1, typename _BI2>
        static _BI2
        __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
        {
	  typename iterator_traits<_BI1>::difference_type __n;
	  for (__n = __last - __first; __n > 0; --__n)
	    *--__result = *--__last;
	  return __result;
	}
    };


  template<bool _IsMove>
    struct __copy_move_backward<_IsMove, true, random_access_iterator_tag>
    {
      template<typename _Tp>
        static _Tp*
        __copy_move_b(const _Tp* __first, const _Tp* __last, _Tp* __result)
        {
	  const ptrdiff_t _Num = __last - __first;
	  if (_Num)
	    __builtin_memmove(__result - _Num, __first, sizeof(_Tp) * _Num);
	  return __result - _Num;
	}
    };

  template<bool _IsMove, typename _BI1, typename _BI2>
    inline _BI2
    __copy_move_backward_a(_BI1 __first, _BI1 __last, _BI2 __result)
    {
      typedef typename iterator_traits<_BI1>::value_type _ValueType1;
      typedef typename iterator_traits<_BI2>::value_type _ValueType2;
      typedef typename iterator_traits<_BI1>::iterator_category _Category;
      const bool __simple = (__is_trivial(_ValueType1)
	                     && __is_pointer<_BI1>::__value
	                     && __is_pointer<_BI2>::__value
			     && __are_same<_ValueType1, _ValueType2>::__value);

      return std::__copy_move_backward<_IsMove, __simple,
	                               _Category>::__copy_move_b(__first,
								 __last,
								 __result);
    }

  template<bool _IsMove, typename _BI1, typename _BI2>
    inline _BI2
    __copy_move_backward_a2(_BI1 __first, _BI1 __last, _BI2 __result)
    {
      return _BI2(std::__copy_move_backward_a<_IsMove>
		  (std::__niter_base(__first), std::__niter_base(__last),
		   std::__niter_base(__result)));
    }

  
















 
  template<typename _BI1, typename _BI2>
    inline _BI2
    copy_backward(_BI1 __first, _BI1 __last, _BI2 __result)
    {
      
      
      
      
      ;

      return (std::__copy_move_backward_a2<__is_move_iterator<_BI1>::__value>
	      (std::__miter_base(__first), std::__miter_base(__last),
	       __result));
    }


  template<typename _ForwardIterator, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<!__is_scalar<_Tp>::__value, void>::__type
    __fill_a(_ForwardIterator __first, _ForwardIterator __last,
 	     const _Tp& __value)
    {
      for (; __first != __last; ++__first)
	*__first = __value;
    }
    
  template<typename _ForwardIterator, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_scalar<_Tp>::__value, void>::__type
    __fill_a(_ForwardIterator __first, _ForwardIterator __last,
	     const _Tp& __value)
    {
      const _Tp __tmp = __value;
      for (; __first != __last; ++__first)
	*__first = __tmp;
    }

  
  template<typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_byte<_Tp>::__value, void>::__type
    __fill_a(_Tp* __first, _Tp* __last, const _Tp& __c)
    {
      const _Tp __tmp = __c;
      __builtin_memset(__first, static_cast<unsigned char>(__tmp),
		       __last - __first);
    }

  










 
  template<typename _ForwardIterator, typename _Tp>
    inline void
    fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __value)
    {
      
      
      ;

      std::__fill_a(std::__niter_base(__first), std::__niter_base(__last),
		    __value);
    }

  template<typename _OutputIterator, typename _Size, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<!__is_scalar<_Tp>::__value, _OutputIterator>::__type
    __fill_n_a(_OutputIterator __first, _Size __n, const _Tp& __value)
    {
      for (__decltype(__n + 0) __niter = __n;
	   __niter > 0; --__niter, ++__first)
	*__first = __value;
      return __first;
    }

  template<typename _OutputIterator, typename _Size, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_scalar<_Tp>::__value, _OutputIterator>::__type
    __fill_n_a(_OutputIterator __first, _Size __n, const _Tp& __value)
    {
      const _Tp __tmp = __value;
      for (__decltype(__n + 0) __niter = __n;
	   __niter > 0; --__niter, ++__first)
	*__first = __tmp;
      return __first;
    }

  template<typename _Size, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_byte<_Tp>::__value, _Tp*>::__type
    __fill_n_a(_Tp* __first, _Size __n, const _Tp& __c)
    {
      std::__fill_a(__first, __first + __n, __c);
      return __first + __n;
    }

  













 
  template<typename _OI, typename _Size, typename _Tp>
    inline _OI
    fill_n(_OI __first, _Size __n, const _Tp& __value)
    {
      
      

      return _OI(std::__fill_n_a(std::__niter_base(__first), __n, __value));
    }

  template<bool _BoolType>
    struct __equal
    {
      template<typename _II1, typename _II2>
        static bool
        equal(_II1 __first1, _II1 __last1, _II2 __first2)
        {
	  for (; __first1 != __last1; ++__first1, ++__first2)
	    if (!(*__first1 == *__first2))
	      return false;
	  return true;
	}
    };

  template<>
    struct __equal<true>
    {
      template<typename _Tp>
        static bool
        equal(const _Tp* __first1, const _Tp* __last1, const _Tp* __first2)
        {
	  return !__builtin_memcmp(__first1, __first2, sizeof(_Tp)
				   * (__last1 - __first1));
	}
    };

  template<typename _II1, typename _II2>
    inline bool
    __equal_aux(_II1 __first1, _II1 __last1, _II2 __first2)
    {
      typedef typename iterator_traits<_II1>::value_type _ValueType1;
      typedef typename iterator_traits<_II2>::value_type _ValueType2;
      const bool __simple = (__is_integer<_ValueType1>::__value
	                     && __is_pointer<_II1>::__value
	                     && __is_pointer<_II2>::__value
			     && __are_same<_ValueType1, _ValueType2>::__value);

      return std::__equal<__simple>::equal(__first1, __last1, __first2);
    }


  template<typename, typename>
    struct __lc_rai
    {
      template<typename _II1, typename _II2>
        static _II1
        __newlast1(_II1, _II1 __last1, _II2, _II2)
        { return __last1; }

      template<typename _II>
        static bool
        __cnd2(_II __first, _II __last)
        { return __first != __last; }
    };

  template<>
    struct __lc_rai<random_access_iterator_tag, random_access_iterator_tag>
    {
      template<typename _RAI1, typename _RAI2>
        static _RAI1
        __newlast1(_RAI1 __first1, _RAI1 __last1,
		   _RAI2 __first2, _RAI2 __last2)
        {
	  const typename iterator_traits<_RAI1>::difference_type
	    __diff1 = __last1 - __first1;
	  const typename iterator_traits<_RAI2>::difference_type
	    __diff2 = __last2 - __first2;
	  return __diff2 < __diff1 ? __first1 + __diff2 : __last1;
	}

      template<typename _RAI>
        static bool
        __cnd2(_RAI, _RAI)
        { return true; }
    };

  template<bool _BoolType>
    struct __lexicographical_compare
    {
      template<typename _II1, typename _II2>
        static bool __lc(_II1, _II1, _II2, _II2);
    };

  template<bool _BoolType>
    template<typename _II1, typename _II2>
      bool
      __lexicographical_compare<_BoolType>::
      __lc(_II1 __first1, _II1 __last1, _II2 __first2, _II2 __last2)
      {
	typedef typename iterator_traits<_II1>::iterator_category _Category1;
	typedef typename iterator_traits<_II2>::iterator_category _Category2;
	typedef std::__lc_rai<_Category1, _Category2> 	__rai_type;
	
	__last1 = __rai_type::__newlast1(__first1, __last1,
					 __first2, __last2);
	for (; __first1 != __last1 && __rai_type::__cnd2(__first2, __last2);
	     ++__first1, ++__first2)
	  {
	    if (*__first1 < *__first2)
	      return true;
	    if (*__first2 < *__first1)
	      return false;
	  }
	return __first1 == __last1 && __first2 != __last2;
      }

  template<>
    struct __lexicographical_compare<true>
    {
      template<typename _Tp, typename _Up>
        static bool
        __lc(const _Tp* __first1, const _Tp* __last1,
	     const _Up* __first2, const _Up* __last2)
	{
	  const size_t __len1 = __last1 - __first1;
	  const size_t __len2 = __last2 - __first2;
	  const int __result = __builtin_memcmp(__first1, __first2,
						std::min(__len1, __len2));
	  return __result != 0 ? __result < 0 : __len1 < __len2;
	}
    };

  template<typename _II1, typename _II2>
    inline bool
    __lexicographical_compare_aux(_II1 __first1, _II1 __last1,
				  _II2 __first2, _II2 __last2)
    {
      typedef typename iterator_traits<_II1>::value_type _ValueType1;
      typedef typename iterator_traits<_II2>::value_type _ValueType2;
      const bool __simple =
	(__is_byte<_ValueType1>::__value && __is_byte<_ValueType2>::__value
	 && !__gnu_cxx::__numeric_traits<_ValueType1>::__is_signed
	 && !__gnu_cxx::__numeric_traits<_ValueType2>::__is_signed
	 && __is_pointer<_II1>::__value
	 && __is_pointer<_II2>::__value);

      return std::__lexicographical_compare<__simple>::__lc(__first1, __last1,
							    __first2, __last2);
    }

  









 
  template<typename _ForwardIterator, typename _Tp>
    _ForwardIterator
    lower_bound(_ForwardIterator __first, _ForwardIterator __last,
		const _Tp& __val)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
	_ValueType;
      typedef typename iterator_traits<_ForwardIterator>::difference_type
	_DistanceType;

      
      
      
      ;

      _DistanceType __len = std::distance(__first, __last);

      while (__len > 0)
	{
	  _DistanceType __half = __len >> 1;
	  _ForwardIterator __middle = __first;
	  std::advance(__middle, __half);
	  if (*__middle < __val)
	    {
	      __first = __middle;
	      ++__first;
	      __len = __len - __half - 1;
	    }
	  else
	    __len = __half;
	}
      return __first;
    }

  
  
  template<typename _Size>
    inline _Size
    __lg(_Size __n)
    {
      _Size __k;
      for (__k = 0; __n != 0; __n >>= 1)
	++__k;
      return __k - 1;
    }

  inline int
  __lg(int __n)
  { return sizeof(int) * 8  - 1 - __builtin_clz(__n); }

  inline long
  __lg(long __n)
  { return sizeof(long) * 8 - 1 - __builtin_clzl(__n); }

  inline long long
  __lg(long long __n)
  { return sizeof(long long) * 8 - 1 - __builtin_clzll(__n); }





  










 
  template<typename _II1, typename _II2>
    inline bool
    equal(_II1 __first1, _II1 __last1, _II2 __first2)
    {
      
      
      
      
      ;

      return std::__equal_aux(std::__niter_base(__first1),
			      std::__niter_base(__last1),
			      std::__niter_base(__first2));
    }

  













 
  template<typename _IIter1, typename _IIter2, typename _BinaryPredicate>
    inline bool
    equal(_IIter1 __first1, _IIter1 __last1,
	  _IIter2 __first2, _BinaryPredicate __binary_pred)
    {
      
      
      
      ;

      for (; __first1 != __last1; ++__first1, ++__first2)
	if (!bool(__binary_pred(*__first1, *__first2)))
	  return false;
      return true;
    }

  













 
  template<typename _II1, typename _II2>
    inline bool
    lexicographical_compare(_II1 __first1, _II1 __last1,
			    _II2 __first2, _II2 __last2)
    {
      
      typedef typename iterator_traits<_II1>::value_type _ValueType1;
      typedef typename iterator_traits<_II2>::value_type _ValueType2;
      
      
      
      
      ;
      ;

      return std::__lexicographical_compare_aux(std::__niter_base(__first1),
						std::__niter_base(__last1),
						std::__niter_base(__first2),
						std::__niter_base(__last2));
    }

  











 
  template<typename _II1, typename _II2, typename _Compare>
    bool
    lexicographical_compare(_II1 __first1, _II1 __last1,
			    _II2 __first2, _II2 __last2, _Compare __comp)
    {
      typedef typename iterator_traits<_II1>::iterator_category _Category1;
      typedef typename iterator_traits<_II2>::iterator_category _Category2;
      typedef std::__lc_rai<_Category1, _Category2> 	__rai_type;

      
      
      
      ;
      ;

      __last1 = __rai_type::__newlast1(__first1, __last1, __first2, __last2);
      for (; __first1 != __last1 && __rai_type::__cnd2(__first2, __last2);
	   ++__first1, ++__first2)
	{
	  if (__comp(*__first1, *__first2))
	    return true;
	  if (__comp(*__first2, *__first1))
	    return false;
	}
      return __first1 == __last1 && __first2 != __last2;
    }

  











 
  template<typename _InputIterator1, typename _InputIterator2>
    pair<_InputIterator1, _InputIterator2>
    mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
	     _InputIterator2 __first2)
    {
      
      
      
      
      ;

      while (__first1 != __last1 && *__first1 == *__first2)
        {
	  ++__first1;
	  ++__first2;
        }
      return pair<_InputIterator1, _InputIterator2>(__first1, __first2);
    }

  














 
  template<typename _InputIterator1, typename _InputIterator2,
	   typename _BinaryPredicate>
    pair<_InputIterator1, _InputIterator2>
    mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
	     _InputIterator2 __first2, _BinaryPredicate __binary_pred)
    {
      
      
      
      ;

      while (__first1 != __last1 && bool(__binary_pred(*__first1, *__first2)))
        {
	  ++__first1;
	  ++__first2;
        }
      return pair<_InputIterator1, _InputIterator2>(__first1, __first2);
    }


} 









































 




 






























 






























 



































 
































 



#pragma GCC visibility push(default)


extern "C++" {

namespace std
{
  





 

  






 
  class exception
  {
  public:
    exception() throw() { }
    virtual ~exception() throw();

    
 
    virtual const char* what() const throw();
  };

  
 
  class bad_exception : public exception
  {
  public:
    bad_exception() throw() { }

    
    
    virtual ~bad_exception() throw();

    
    virtual const char* what() const throw();
  };

  
  typedef void (*terminate_handler) ();

  
  typedef void (*unexpected_handler) ();

  
  terminate_handler set_terminate(terminate_handler) throw();

  
 
  void terminate() throw() __attribute__ ((__noreturn__));

  
  unexpected_handler set_unexpected(unexpected_handler) throw();

  
 
  void unexpected() __attribute__ ((__noreturn__));

  









 
  bool uncaught_exception() throw() __attribute__ ((__pure__));

  
} 

namespace __gnu_cxx
{


  














 
  void __verbose_terminate_handler();


} 

} 

#pragma GCC visibility pop



#pragma GCC visibility push(default)

extern "C++" {

namespace std 
{
  




 
  class bad_alloc : public exception 
  {
  public:
    bad_alloc() throw() { }

    
    
    virtual ~bad_alloc() throw();

    
    virtual const char* what() const throw();
  };

  struct nothrow_t { };

  extern const nothrow_t nothrow;

  
 
  typedef void (*new_handler)();

  
  
  new_handler set_new_handler(new_handler) throw();
} 











 
void* operator new(std::size_t) throw (std::bad_alloc);
void* operator new[](std::size_t) throw (std::bad_alloc);
void operator delete(void*) throw();
void operator delete[](void*) throw();
void* operator new(std::size_t, const std::nothrow_t&) throw();
void* operator new[](std::size_t, const std::nothrow_t&) throw();
void operator delete(void*, const std::nothrow_t&) throw();
void operator delete[](void*, const std::nothrow_t&) throw();


inline void* operator new(std::size_t, void* __p) throw() { return __p; }
inline void* operator new[](std::size_t, void* __p) throw() { return __p; }


inline void  operator delete  (void*, void*) throw() { }
inline void  operator delete[](void*, void*) throw() { }

} 

#pragma GCC visibility pop


namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{


  using std::size_t;
  using std::ptrdiff_t;

  






 
  template<typename _Tp>
    class new_allocator
    {
    public:
      typedef size_t     size_type;
      typedef ptrdiff_t  difference_type;
      typedef _Tp*       pointer;
      typedef const _Tp* const_pointer;
      typedef _Tp&       reference;
      typedef const _Tp& const_reference;
      typedef _Tp        value_type;

      template<typename _Tp1>
        struct rebind
        { typedef new_allocator<_Tp1> other; };

      new_allocator() throw() { }

      new_allocator(const new_allocator&) throw() { }

      template<typename _Tp1>
        new_allocator(const new_allocator<_Tp1>&) throw() { }

      ~new_allocator() throw() { }

      pointer
      address(reference __x) const { return std::__addressof(__x); }

      const_pointer
      address(const_reference __x) const { return std::__addressof(__x); }

      
      
      pointer
      allocate(size_type __n, const void* = 0)
      { 
	if (__n > this->max_size())
	  std::__throw_bad_alloc();

	return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
      }

      
      void
      deallocate(pointer __p, size_type)
      { ::operator delete(__p); }

      size_type
      max_size() const throw() 
      { return size_t(-1) / sizeof(_Tp); }

      
      
      void 
      construct(pointer __p, const _Tp& __val) 
      { ::new((void *)__p) _Tp(__val); }


      void 
      destroy(pointer __p) { __p->~_Tp(); }
    };

  template<typename _Tp>
    inline bool
    operator==(const new_allocator<_Tp>&, const new_allocator<_Tp>&)
    { return true; }
  
  template<typename _Tp>
    inline bool
    operator!=(const new_allocator<_Tp>&, const new_allocator<_Tp>&)
    { return false; }


} 




namespace std __attribute__ ((__visibility__ ("default")))
{


  




 

  template<typename _Tp>
    class allocator;

  
  template<>
    class allocator<void>
    {
    public:
      typedef size_t      size_type;
      typedef ptrdiff_t   difference_type;
      typedef void*       pointer;
      typedef const void* const_pointer;
      typedef void        value_type;

      template<typename _Tp1>
        struct rebind
        { typedef allocator<_Tp1> other; };
    };

  





 
  template<typename _Tp>
    class allocator: public __gnu_cxx::new_allocator<_Tp>
    {
   public:
      typedef size_t     size_type;
      typedef ptrdiff_t  difference_type;
      typedef _Tp*       pointer;
      typedef const _Tp* const_pointer;
      typedef _Tp&       reference;
      typedef const _Tp& const_reference;
      typedef _Tp        value_type;

      template<typename _Tp1>
        struct rebind
        { typedef allocator<_Tp1> other; };

      allocator() throw() { }

      allocator(const allocator& __a) throw()
      : __gnu_cxx::new_allocator<_Tp>(__a) { }

      template<typename _Tp1>
        allocator(const allocator<_Tp1>&) throw() { }

      ~allocator() throw() { }

      
    };

  template<typename _T1, typename _T2>
    inline bool
    operator==(const allocator<_T1>&, const allocator<_T2>&)
    { return true; }

  template<typename _Tp>
    inline bool
    operator==(const allocator<_Tp>&, const allocator<_Tp>&)
    { return true; }

  template<typename _T1, typename _T2>
    inline bool
    operator!=(const allocator<_T1>&, const allocator<_T2>&)
    { return false; }

  template<typename _Tp>
    inline bool
    operator!=(const allocator<_Tp>&, const allocator<_Tp>&)
    { return false; }

  
  
  extern template class allocator<char>;
  extern template class allocator<wchar_t>;

  

  
  template<typename _Alloc, bool = __is_empty(_Alloc)>
    struct __alloc_swap
    { static void _S_do_it(_Alloc&, _Alloc&) { } };

  template<typename _Alloc>
    struct __alloc_swap<_Alloc, false>
    {
      static void
      _S_do_it(_Alloc& __one, _Alloc& __two)
      {
	
	if (__one != __two)
	  swap(__one, __two);
      }
    };

  
  template<typename _Alloc, bool = __is_empty(_Alloc)>
    struct __alloc_neq
    {
      static bool
      _S_do_it(const _Alloc&, const _Alloc&)
      { return false; }
    };

  template<typename _Alloc>
    struct __alloc_neq<_Alloc, false>
    {
      static bool
      _S_do_it(const _Alloc& __one, const _Alloc& __two)
      { return __one != __two; }
    };



} 



















































 




 



namespace std __attribute__ ((__visibility__ ("default")))
{


  


 
  template<typename _T1, typename _T2>
    inline void
    _Construct(_T1* __p, const _T2& __value)
    {
      
      
      ::new(static_cast<void*>(__p)) _T1(__value);
    }

  

 
  template<typename _Tp>
    inline void
    _Destroy(_Tp* __pointer)
    { __pointer->~_Tp(); }

  template<bool>
    struct _Destroy_aux
    {
      template<typename _ForwardIterator>
        static void
        __destroy(_ForwardIterator __first, _ForwardIterator __last)
	{
	  for (; __first != __last; ++__first)
	    std::_Destroy(std::__addressof(*__first));
	}
    };

  template<>
    struct _Destroy_aux<true>
    {
      template<typename _ForwardIterator>
        static void
        __destroy(_ForwardIterator, _ForwardIterator) { }
    };

  



 
  template<typename _ForwardIterator>
    inline void
    _Destroy(_ForwardIterator __first, _ForwardIterator __last)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
                       _Value_type;
      std::_Destroy_aux<__has_trivial_destructor(_Value_type)>::
	__destroy(__first, __last);
    }

  



 

  template <typename _Tp> class allocator;

  template<typename _ForwardIterator, typename _Allocator>
    void
    _Destroy(_ForwardIterator __first, _ForwardIterator __last,
	     _Allocator& __alloc)
    {
      for (; __first != __last; ++__first)
	__alloc.destroy(std::__addressof(*__first));
    }

  template<typename _ForwardIterator, typename _Tp>
    inline void
    _Destroy(_ForwardIterator __first, _ForwardIterator __last,
	     allocator<_Tp>&)
    {
      _Destroy(__first, __last);
    }


} 




















































 




 


namespace std __attribute__ ((__visibility__ ("default")))
{


  template<bool _TrivialValueTypes>
    struct __uninitialized_copy
    {
      template<typename _InputIterator, typename _ForwardIterator>
        static _ForwardIterator
        __uninit_copy(_InputIterator __first, _InputIterator __last,
		      _ForwardIterator __result)
        {
	  _ForwardIterator __cur = __result;
	  try
	    {
	      for (; __first != __last; ++__first, ++__cur)
		std::_Construct(std::__addressof(*__cur), *__first);
	      return __cur;
	    }
	  catch(...)
	    {
	      std::_Destroy(__result, __cur);
	      throw;
	    }
	}
    };

  template<>
    struct __uninitialized_copy<true>
    {
      template<typename _InputIterator, typename _ForwardIterator>
        static _ForwardIterator
        __uninit_copy(_InputIterator __first, _InputIterator __last,
		      _ForwardIterator __result)
        { return std::copy(__first, __last, __result); }
    };

  







 
  template<typename _InputIterator, typename _ForwardIterator>
    inline _ForwardIterator
    uninitialized_copy(_InputIterator __first, _InputIterator __last,
		       _ForwardIterator __result)
    {
      typedef typename iterator_traits<_InputIterator>::value_type
	_ValueType1;
      typedef typename iterator_traits<_ForwardIterator>::value_type
	_ValueType2;

      return std::__uninitialized_copy<(__is_trivial(_ValueType1)
					&& __is_trivial(_ValueType2))>::
	__uninit_copy(__first, __last, __result);
    }


  template<bool _TrivialValueType>
    struct __uninitialized_fill
    {
      template<typename _ForwardIterator, typename _Tp>
        static void
        __uninit_fill(_ForwardIterator __first, _ForwardIterator __last,
		      const _Tp& __x)
        {
	  _ForwardIterator __cur = __first;
	  try
	    {
	      for (; __cur != __last; ++__cur)
		std::_Construct(std::__addressof(*__cur), __x);
	    }
	  catch(...)
	    {
	      std::_Destroy(__first, __cur);
	      throw;
	    }
	}
    };

  template<>
    struct __uninitialized_fill<true>
    {
      template<typename _ForwardIterator, typename _Tp>
        static void
        __uninit_fill(_ForwardIterator __first, _ForwardIterator __last,
		      const _Tp& __x)
        { std::fill(__first, __last, __x); }
    };

  







 
  template<typename _ForwardIterator, typename _Tp>
    inline void
    uninitialized_fill(_ForwardIterator __first, _ForwardIterator __last,
		       const _Tp& __x)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
	_ValueType;

      std::__uninitialized_fill<__is_trivial(_ValueType)>::
	__uninit_fill(__first, __last, __x);
    }


  template<bool _TrivialValueType>
    struct __uninitialized_fill_n
    {
      template<typename _ForwardIterator, typename _Size, typename _Tp>
        static void
        __uninit_fill_n(_ForwardIterator __first, _Size __n,
			const _Tp& __x)
        {
	  _ForwardIterator __cur = __first;
	  try
	    {
	      for (; __n > 0; --__n, ++__cur)
		std::_Construct(std::__addressof(*__cur), __x);
	    }
	  catch(...)
	    {
	      std::_Destroy(__first, __cur);
	      throw;
	    }
	}
    };

  template<>
    struct __uninitialized_fill_n<true>
    {
      template<typename _ForwardIterator, typename _Size, typename _Tp>
        static void
        __uninit_fill_n(_ForwardIterator __first, _Size __n,
			const _Tp& __x)
        { std::fill_n(__first, __n, __x); }
    };

  







 
  template<typename _ForwardIterator, typename _Size, typename _Tp>
    inline void
    uninitialized_fill_n(_ForwardIterator __first, _Size __n, const _Tp& __x)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
	_ValueType;

      std::__uninitialized_fill_n<__is_trivial(_ValueType)>::
	__uninit_fill_n(__first, __n, __x);
    }

  
  
  
  
  

  template<typename _InputIterator, typename _ForwardIterator,
	   typename _Allocator>
    _ForwardIterator
    __uninitialized_copy_a(_InputIterator __first, _InputIterator __last,
			   _ForwardIterator __result, _Allocator& __alloc)
    {
      _ForwardIterator __cur = __result;
      try
	{
	  for (; __first != __last; ++__first, ++__cur)
	    __alloc.construct(std::__addressof(*__cur), *__first);
	  return __cur;
	}
      catch(...)
	{
	  std::_Destroy(__result, __cur, __alloc);
	  throw;
	}
    }

  template<typename _InputIterator, typename _ForwardIterator, typename _Tp>
    inline _ForwardIterator
    __uninitialized_copy_a(_InputIterator __first, _InputIterator __last,
			   _ForwardIterator __result, allocator<_Tp>&)
    { return std::uninitialized_copy(__first, __last, __result); }

  template<typename _InputIterator, typename _ForwardIterator,
	   typename _Allocator>
    inline _ForwardIterator
    __uninitialized_move_a(_InputIterator __first, _InputIterator __last,
			   _ForwardIterator __result, _Allocator& __alloc)
    {
      return std::__uninitialized_copy_a((__first),
					 (__last),
					 __result, __alloc);
    }

  template<typename _ForwardIterator, typename _Tp, typename _Allocator>
    void
    __uninitialized_fill_a(_ForwardIterator __first, _ForwardIterator __last,
			   const _Tp& __x, _Allocator& __alloc)
    {
      _ForwardIterator __cur = __first;
      try
	{
	  for (; __cur != __last; ++__cur)
	    __alloc.construct(std::__addressof(*__cur), __x);
	}
      catch(...)
	{
	  std::_Destroy(__first, __cur, __alloc);
	  throw;
	}
    }

  template<typename _ForwardIterator, typename _Tp, typename _Tp2>
    inline void
    __uninitialized_fill_a(_ForwardIterator __first, _ForwardIterator __last,
			   const _Tp& __x, allocator<_Tp2>&)
    { std::uninitialized_fill(__first, __last, __x); }

  template<typename _ForwardIterator, typename _Size, typename _Tp,
	   typename _Allocator>
    void
    __uninitialized_fill_n_a(_ForwardIterator __first, _Size __n, 
			     const _Tp& __x, _Allocator& __alloc)
    {
      _ForwardIterator __cur = __first;
      try
	{
	  for (; __n > 0; --__n, ++__cur)
	    __alloc.construct(std::__addressof(*__cur), __x);
	}
      catch(...)
	{
	  std::_Destroy(__first, __cur, __alloc);
	  throw;
	}
    }

  template<typename _ForwardIterator, typename _Size, typename _Tp,
	   typename _Tp2>
    inline void
    __uninitialized_fill_n_a(_ForwardIterator __first, _Size __n, 
			     const _Tp& __x, allocator<_Tp2>&)
    { std::uninitialized_fill_n(__first, __n, __x); }


  
  
  
  

  
  
  
  
  template<typename _InputIterator1, typename _InputIterator2,
	   typename _ForwardIterator, typename _Allocator>
    inline _ForwardIterator
    __uninitialized_copy_move(_InputIterator1 __first1,
			      _InputIterator1 __last1,
			      _InputIterator2 __first2,
			      _InputIterator2 __last2,
			      _ForwardIterator __result,
			      _Allocator& __alloc)
    {
      _ForwardIterator __mid = std::__uninitialized_copy_a(__first1, __last1,
							   __result,
							   __alloc);
      try
	{
	  return std::__uninitialized_move_a(__first2, __last2, __mid, __alloc);
	}
      catch(...)
	{
	  std::_Destroy(__result, __mid, __alloc);
	  throw;
	}
    }

  
  
  
  
  template<typename _InputIterator1, typename _InputIterator2,
	   typename _ForwardIterator, typename _Allocator>
    inline _ForwardIterator
    __uninitialized_move_copy(_InputIterator1 __first1,
			      _InputIterator1 __last1,
			      _InputIterator2 __first2,
			      _InputIterator2 __last2,
			      _ForwardIterator __result,
			      _Allocator& __alloc)
    {
      _ForwardIterator __mid = std::__uninitialized_move_a(__first1, __last1,
							   __result,
							   __alloc);
      try
	{
	  return std::__uninitialized_copy_a(__first2, __last2, __mid, __alloc);
	}
      catch(...)
	{
	  std::_Destroy(__result, __mid, __alloc);
	  throw;
	}
    }
  
  
  
  
  template<typename _ForwardIterator, typename _Tp, typename _InputIterator,
	   typename _Allocator>
    inline _ForwardIterator
    __uninitialized_fill_move(_ForwardIterator __result, _ForwardIterator __mid,
			      const _Tp& __x, _InputIterator __first,
			      _InputIterator __last, _Allocator& __alloc)
    {
      std::__uninitialized_fill_a(__result, __mid, __x, __alloc);
      try
	{
	  return std::__uninitialized_move_a(__first, __last, __mid, __alloc);
	}
      catch(...)
	{
	  std::_Destroy(__result, __mid, __alloc);
	  throw;
	}
    }

  
  
  
  template<typename _InputIterator, typename _ForwardIterator, typename _Tp,
	   typename _Allocator>
    inline void
    __uninitialized_move_fill(_InputIterator __first1, _InputIterator __last1,
			      _ForwardIterator __first2,
			      _ForwardIterator __last2, const _Tp& __x,
			      _Allocator& __alloc)
    {
      _ForwardIterator __mid2 = std::__uninitialized_move_a(__first1, __last1,
							    __first2,
							    __alloc);
      try
	{
	  std::__uninitialized_fill_a(__mid2, __last2, __x, __alloc);
	}
      catch(...)
	{
	  std::_Destroy(__first2, __mid2, __alloc);
	  throw;
	}
    }



} 


















































 




 





























 




namespace std __attribute__ ((__visibility__ ("default")))
{


  
  template<typename _Tp, typename _Alloc>
    struct _Vector_base
    {
      typedef typename _Alloc::template rebind<_Tp>::other _Tp_alloc_type;

      struct _Vector_impl 
      : public _Tp_alloc_type
      {
	typename _Tp_alloc_type::pointer _M_start;
	typename _Tp_alloc_type::pointer _M_finish;
	typename _Tp_alloc_type::pointer _M_end_of_storage;

	_Vector_impl()
	: _Tp_alloc_type(), _M_start(0), _M_finish(0), _M_end_of_storage(0)
	{ }

	_Vector_impl(_Tp_alloc_type const& __a)
	: _Tp_alloc_type(__a), _M_start(0), _M_finish(0), _M_end_of_storage(0)
	{ }
      };
      
    public:
      typedef _Alloc allocator_type;

      _Tp_alloc_type&
      _M_get_Tp_allocator()
      { return *static_cast<_Tp_alloc_type*>(&this->_M_impl); }

      const _Tp_alloc_type&
      _M_get_Tp_allocator() const
      { return *static_cast<const _Tp_alloc_type*>(&this->_M_impl); }

      allocator_type
      get_allocator() const
      { return allocator_type(_M_get_Tp_allocator()); }

      _Vector_base()
      : _M_impl() { }

      _Vector_base(const allocator_type& __a)
      : _M_impl(__a) { }

      _Vector_base(size_t __n)
      : _M_impl()
      {
	this->_M_impl._M_start = this->_M_allocate(__n);
	this->_M_impl._M_finish = this->_M_impl._M_start;
	this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
      }

      _Vector_base(size_t __n, const allocator_type& __a)
      : _M_impl(__a)
      {
	this->_M_impl._M_start = this->_M_allocate(__n);
	this->_M_impl._M_finish = this->_M_impl._M_start;
	this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
      }


      ~_Vector_base()
      { _M_deallocate(this->_M_impl._M_start, this->_M_impl._M_end_of_storage
		      - this->_M_impl._M_start); }

    public:
      _Vector_impl _M_impl;

      typename _Tp_alloc_type::pointer
      _M_allocate(size_t __n)
      { return __n != 0 ? _M_impl.allocate(__n) : 0; }

      void
      _M_deallocate(typename _Tp_alloc_type::pointer __p, size_t __n)
      {
	if (__p)
	  _M_impl.deallocate(__p, __n);
      }
    };


  
















 
  template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
    class vector : protected _Vector_base<_Tp, _Alloc>
    {
      
      typedef typename _Alloc::value_type                _Alloc_value_type;
      
      
      
      typedef _Vector_base<_Tp, _Alloc>			 _Base;
      typedef typename _Base::_Tp_alloc_type		 _Tp_alloc_type;

    public:
      typedef _Tp					 value_type;
      typedef typename _Tp_alloc_type::pointer           pointer;
      typedef typename _Tp_alloc_type::const_pointer     const_pointer;
      typedef typename _Tp_alloc_type::reference         reference;
      typedef typename _Tp_alloc_type::const_reference   const_reference;
      typedef __gnu_cxx::__normal_iterator<pointer, vector> iterator;
      typedef __gnu_cxx::__normal_iterator<const_pointer, vector>
      const_iterator;
      typedef std::reverse_iterator<const_iterator>  const_reverse_iterator;
      typedef std::reverse_iterator<iterator>		 reverse_iterator;
      typedef size_t					 size_type;
      typedef ptrdiff_t					 difference_type;
      typedef _Alloc                        		 allocator_type;

    protected:
      using _Base::_M_allocate;
      using _Base::_M_deallocate;
      using _Base::_M_impl;
      using _Base::_M_get_Tp_allocator;

    public:
      
      
      

 
      vector()
      : _Base() { }

      


 
      explicit
      vector(const allocator_type& __a)
      : _Base(__a) { }

      






 
      explicit
      vector(size_type __n, const value_type& __value = value_type(),
	     const allocator_type& __a = allocator_type())
      : _Base(__n, __a)
      { _M_fill_initialize(__n, __value); }

      







 
      vector(const vector& __x)
      : _Base(__x.size(), __x._M_get_Tp_allocator())
      { this->_M_impl._M_finish =
	  std::__uninitialized_copy_a(__x.begin(), __x.end(),
				      this->_M_impl._M_start,
				      _M_get_Tp_allocator());
      }


      














 
      template<typename _InputIterator>
        vector(_InputIterator __first, _InputIterator __last,
	       const allocator_type& __a = allocator_type())
	: _Base(__a)
        {
	  
	  typedef typename std::__is_integer<_InputIterator>::__type _Integral;
	  _M_initialize_dispatch(__first, __last, _Integral());
	}

      




 
      ~vector()
      { std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
		      _M_get_Tp_allocator()); }

      






 
      vector&
      operator=(const vector& __x);


      








 
      void
      assign(size_type __n, const value_type& __val)
      { _M_fill_assign(__n, __val); }

      










 
      template<typename _InputIterator>
        void
        assign(_InputIterator __first, _InputIterator __last)
        {
	  
	  typedef typename std::__is_integer<_InputIterator>::__type _Integral;
	  _M_assign_dispatch(__first, __last, _Integral());
	}


      
      using _Base::get_allocator;

      
      



 
      iterator
      begin()
      { return iterator(this->_M_impl._M_start); }

      



 
      const_iterator
      begin() const
      { return const_iterator(this->_M_impl._M_start); }

      



 
      iterator
      end()
      { return iterator(this->_M_impl._M_finish); }

      



 
      const_iterator
      end() const
      { return const_iterator(this->_M_impl._M_finish); }

      



 
      reverse_iterator
      rbegin()
      { return reverse_iterator(end()); }

      



 
      const_reverse_iterator
      rbegin() const
      { return const_reverse_iterator(end()); }

      



 
      reverse_iterator
      rend()
      { return reverse_iterator(begin()); }

      



 
      const_reverse_iterator
      rend() const
      { return const_reverse_iterator(begin()); }


      
       
      size_type
      size() const
      { return size_type(this->_M_impl._M_finish - this->_M_impl._M_start); }

       
      size_type
      max_size() const
      { return _M_get_Tp_allocator().max_size(); }

      









 
      void
      resize(size_type __new_size, value_type __x = value_type())
      {
	if (__new_size > size())
	  insert(end(), __new_size - size(), __x);
	else if (__new_size < size())
	  _M_erase_at_end(this->_M_impl._M_start + __new_size);
      }


      


 
      size_type
      capacity() const
      { return size_type(this->_M_impl._M_end_of_storage
			 - this->_M_impl._M_start); }

      


 
      bool
      empty() const
      { return begin() == end(); }

      















 
      void
      reserve(size_type __n);

      
      









 
      reference
      operator[](size_type __n)
      { return *(this->_M_impl._M_start + __n); }

      









 
      const_reference
      operator[](size_type __n) const
      { return *(this->_M_impl._M_start + __n); }

    protected:
      
      void
      _M_range_check(size_type __n) const
      {
	if (__n >= this->size())
	  __throw_out_of_range(("vector::_M_range_check"));
      }

    public:
      









 
      reference
      at(size_type __n)
      {
	_M_range_check(__n);
	return (*this)[__n]; 
      }

      









 
      const_reference
      at(size_type __n) const
      {
	_M_range_check(__n);
	return (*this)[__n];
      }

      


 
      reference
      front()
      { return *begin(); }

      


 
      const_reference
      front() const
      { return *begin(); }

      


 
      reference
      back()
      { return *(end() - 1); }
      
      


 
      const_reference
      back() const
      { return *(end() - 1); }

      
      
      
      


 
      pointer
      data()
      { return std::__addressof(front()); }

      const_pointer
      data() const
      { return std::__addressof(front()); }

      
      








 
      void
      push_back(const value_type& __x)
      {
	if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
	  {
	    this->_M_impl.construct(this->_M_impl._M_finish, __x);
	    ++this->_M_impl._M_finish;
	  }
	else
	  _M_insert_aux(end(), __x);
      }


      







 
      void
      pop_back()
      {
	--this->_M_impl._M_finish;
	this->_M_impl.destroy(this->_M_impl._M_finish);
      }


      









 
      iterator
      insert(iterator __position, const value_type& __x);


      











 
      void
      insert(iterator __position, size_type __n, const value_type& __x)
      { _M_fill_insert(__position, __n, __x); }

      












 
      template<typename _InputIterator>
        void
        insert(iterator __position, _InputIterator __first,
	       _InputIterator __last)
        {
	  
	  typedef typename std::__is_integer<_InputIterator>::__type _Integral;
	  _M_insert_dispatch(__position, __first, __last, _Integral());
	}

      













 
      iterator
      erase(iterator __position);

      
















 
      iterator
      erase(iterator __first, iterator __last);

      







 
      void
      swap(vector& __x)
      {
	std::swap(this->_M_impl._M_start, __x._M_impl._M_start);
	std::swap(this->_M_impl._M_finish, __x._M_impl._M_finish);
	std::swap(this->_M_impl._M_end_of_storage,
		  __x._M_impl._M_end_of_storage);

	
	
	std::__alloc_swap<_Tp_alloc_type>::_S_do_it(_M_get_Tp_allocator(),
						    __x._M_get_Tp_allocator());
      }

      




 
      void
      clear()
      { _M_erase_at_end(this->_M_impl._M_start); }

    protected:
      


 
      template<typename _ForwardIterator>
        pointer
        _M_allocate_and_copy(size_type __n,
			     _ForwardIterator __first, _ForwardIterator __last)
        {
	  pointer __result = this->_M_allocate(__n);
	  try
	    {
	      std::__uninitialized_copy_a(__first, __last, __result,
					  _M_get_Tp_allocator());
	      return __result;
	    }
	  catch(...)
	    {
	      _M_deallocate(__result, __n);
	      throw;
	    }
	}


      

      

      
      
      template<typename _Integer>
        void
        _M_initialize_dispatch(_Integer __n, _Integer __value, __true_type)
        {
	  this->_M_impl._M_start = _M_allocate(static_cast<size_type>(__n));
	  this->_M_impl._M_end_of_storage =
	    this->_M_impl._M_start + static_cast<size_type>(__n);
	  _M_fill_initialize(static_cast<size_type>(__n), __value);
	}

      
      template<typename _InputIterator>
        void
        _M_initialize_dispatch(_InputIterator __first, _InputIterator __last,
			       __false_type)
        {
	  typedef typename std::iterator_traits<_InputIterator>::
	    iterator_category _IterCategory;
	  _M_range_initialize(__first, __last, _IterCategory());
	}

      
      template<typename _InputIterator>
        void
        _M_range_initialize(_InputIterator __first,
			    _InputIterator __last, std::input_iterator_tag)
        {
	  for (; __first != __last; ++__first)
	    push_back(*__first);
	}

      
      template<typename _ForwardIterator>
        void
        _M_range_initialize(_ForwardIterator __first,
			    _ForwardIterator __last, std::forward_iterator_tag)
        {
	  const size_type __n = std::distance(__first, __last);
	  this->_M_impl._M_start = this->_M_allocate(__n);
	  this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
	  this->_M_impl._M_finish =
	    std::__uninitialized_copy_a(__first, __last,
					this->_M_impl._M_start,
					_M_get_Tp_allocator());
	}

      
      
      void
      _M_fill_initialize(size_type __n, const value_type& __value)
      {
	std::__uninitialized_fill_n_a(this->_M_impl._M_start, __n, __value, 
				      _M_get_Tp_allocator());
	this->_M_impl._M_finish = this->_M_impl._M_end_of_storage;
      }


      
      

      

      
      
      template<typename _Integer>
        void
        _M_assign_dispatch(_Integer __n, _Integer __val, __true_type)
        { _M_fill_assign(__n, __val); }

      
      template<typename _InputIterator>
        void
        _M_assign_dispatch(_InputIterator __first, _InputIterator __last,
			   __false_type)
        {
	  typedef typename std::iterator_traits<_InputIterator>::
	    iterator_category _IterCategory;
	  _M_assign_aux(__first, __last, _IterCategory());
	}

      
      template<typename _InputIterator>
        void
        _M_assign_aux(_InputIterator __first, _InputIterator __last,
		      std::input_iterator_tag);

      
      template<typename _ForwardIterator>
        void
        _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last,
		      std::forward_iterator_tag);

      
      
      void
      _M_fill_assign(size_type __n, const value_type& __val);


      

      

      
      
      template<typename _Integer>
        void
        _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __val,
			   __true_type)
        { _M_fill_insert(__pos, __n, __val); }

      
      template<typename _InputIterator>
        void
        _M_insert_dispatch(iterator __pos, _InputIterator __first,
			   _InputIterator __last, __false_type)
        {
	  typedef typename std::iterator_traits<_InputIterator>::
	    iterator_category _IterCategory;
	  _M_range_insert(__pos, __first, __last, _IterCategory());
	}

      
      template<typename _InputIterator>
        void
        _M_range_insert(iterator __pos, _InputIterator __first,
			_InputIterator __last, std::input_iterator_tag);

      
      template<typename _ForwardIterator>
        void
        _M_range_insert(iterator __pos, _ForwardIterator __first,
			_ForwardIterator __last, std::forward_iterator_tag);

      
      
      void
      _M_fill_insert(iterator __pos, size_type __n, const value_type& __x);


      
      void
      _M_insert_aux(iterator __position, const value_type& __x);

      
      size_type
      _M_check_len(size_type __n, const char* __s) const
      {
	if (max_size() - size() < __n)
	  __throw_length_error((__s));

	const size_type __len = size() + std::max(size(), __n);
	return (__len < size() || __len > max_size()) ? max_size() : __len;
      }

      

      
      
      void
      _M_erase_at_end(pointer __pos)
      {
	std::_Destroy(__pos, this->_M_impl._M_finish, _M_get_Tp_allocator());
	this->_M_impl._M_finish = __pos;
      }
    };


  








 
  template<typename _Tp, typename _Alloc>
    inline bool
    operator==(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
    { return (__x.size() == __y.size()
	      && std::equal(__x.begin(), __x.end(), __y.begin())); }

  









 
  template<typename _Tp, typename _Alloc>
    inline bool
    operator<(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
    { return std::lexicographical_compare(__x.begin(), __x.end(),
					  __y.begin(), __y.end()); }

  
  template<typename _Tp, typename _Alloc>
    inline bool
    operator!=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
    { return !(__x == __y); }

  
  template<typename _Tp, typename _Alloc>
    inline bool
    operator>(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
    { return __y < __x; }

  
  template<typename _Tp, typename _Alloc>
    inline bool
    operator<=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
    { return !(__y < __x); }

  
  template<typename _Tp, typename _Alloc>
    inline bool
    operator>=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
    { return !(__x < __y); }

  
  template<typename _Tp, typename _Alloc>
    inline void
    swap(vector<_Tp, _Alloc>& __x, vector<_Tp, _Alloc>& __y)
    { __x.swap(__y); }


} 


















































 




 



namespace std __attribute__ ((__visibility__ ("default")))
{


  typedef unsigned long _Bit_type;
  enum { _S_word_bit = int(8 * sizeof(_Bit_type)) };

  struct _Bit_reference
  {
    _Bit_type * _M_p;
    _Bit_type _M_mask;

    _Bit_reference(_Bit_type * __x, _Bit_type __y)
    : _M_p(__x), _M_mask(__y) { }

    _Bit_reference() : _M_p(0), _M_mask(0) { }

    operator bool() const
    { return !!(*_M_p & _M_mask); }

    _Bit_reference&
    operator=(bool __x)
    {
      if (__x)
	*_M_p |= _M_mask;
      else
	*_M_p &= ~_M_mask;
      return *this;
    }

    _Bit_reference&
    operator=(const _Bit_reference& __x)
    { return *this = bool(__x); }

    bool
    operator==(const _Bit_reference& __x) const
    { return bool(*this) == bool(__x); }

    bool
    operator<(const _Bit_reference& __x) const
    { return !bool(*this) && bool(__x); }

    void
    flip()
    { *_M_p ^= _M_mask; }
  };

  struct _Bit_iterator_base
  : public std::iterator<std::random_access_iterator_tag, bool>
  {
    _Bit_type * _M_p;
    unsigned int _M_offset;

    _Bit_iterator_base(_Bit_type * __x, unsigned int __y)
    : _M_p(__x), _M_offset(__y) { }

    void
    _M_bump_up()
    {
      if (_M_offset++ == int(_S_word_bit) - 1)
	{
	  _M_offset = 0;
	  ++_M_p;
	}
    }

    void
    _M_bump_down()
    {
      if (_M_offset-- == 0)
	{
	  _M_offset = int(_S_word_bit) - 1;
	  --_M_p;
	}
    }

    void
    _M_incr(ptrdiff_t __i)
    {
      difference_type __n = __i + _M_offset;
      _M_p += __n / int(_S_word_bit);
      __n = __n % int(_S_word_bit);
      if (__n < 0)
	{
	  __n += int(_S_word_bit);
	  --_M_p;
	}
      _M_offset = static_cast<unsigned int>(__n);
    }

    bool
    operator==(const _Bit_iterator_base& __i) const
    { return _M_p == __i._M_p && _M_offset == __i._M_offset; }

    bool
    operator<(const _Bit_iterator_base& __i) const
    {
      return _M_p < __i._M_p
	     || (_M_p == __i._M_p && _M_offset < __i._M_offset);
    }

    bool
    operator!=(const _Bit_iterator_base& __i) const
    { return !(*this == __i); }

    bool
    operator>(const _Bit_iterator_base& __i) const
    { return __i < *this; }

    bool
    operator<=(const _Bit_iterator_base& __i) const
    { return !(__i < *this); }

    bool
    operator>=(const _Bit_iterator_base& __i) const
    { return !(*this < __i); }
  };

  inline ptrdiff_t
  operator-(const _Bit_iterator_base& __x, const _Bit_iterator_base& __y)
  {
    return (int(_S_word_bit) * (__x._M_p - __y._M_p)
	    + __x._M_offset - __y._M_offset);
  }

  struct _Bit_iterator : public _Bit_iterator_base
  {
    typedef _Bit_reference  reference;
    typedef _Bit_reference* pointer;
    typedef _Bit_iterator   iterator;

    _Bit_iterator() : _Bit_iterator_base(0, 0) { }

    _Bit_iterator(_Bit_type * __x, unsigned int __y)
    : _Bit_iterator_base(__x, __y) { }

    reference
    operator*() const
    { return reference(_M_p, 1UL << _M_offset); }

    iterator&
    operator++()
    {
      _M_bump_up();
      return *this;
    }

    iterator
    operator++(int)
    {
      iterator __tmp = *this;
      _M_bump_up();
      return __tmp;
    }

    iterator&
    operator--()
    {
      _M_bump_down();
      return *this;
    }

    iterator
    operator--(int)
    {
      iterator __tmp = *this;
      _M_bump_down();
      return __tmp;
    }

    iterator&
    operator+=(difference_type __i)
    {
      _M_incr(__i);
      return *this;
    }

    iterator&
    operator-=(difference_type __i)
    {
      *this += -__i;
      return *this;
    }

    iterator
    operator+(difference_type __i) const
    {
      iterator __tmp = *this;
      return __tmp += __i;
    }

    iterator
    operator-(difference_type __i) const
    {
      iterator __tmp = *this;
      return __tmp -= __i;
    }

    reference
    operator[](difference_type __i) const
    { return *(*this + __i); }
  };

  inline _Bit_iterator
  operator+(ptrdiff_t __n, const _Bit_iterator& __x)
  { return __x + __n; }

  struct _Bit_const_iterator : public _Bit_iterator_base
  {
    typedef bool                 reference;
    typedef bool                 const_reference;
    typedef const bool*          pointer;
    typedef _Bit_const_iterator  const_iterator;

    _Bit_const_iterator() : _Bit_iterator_base(0, 0) { }

    _Bit_const_iterator(_Bit_type * __x, unsigned int __y)
    : _Bit_iterator_base(__x, __y) { }

    _Bit_const_iterator(const _Bit_iterator& __x)
    : _Bit_iterator_base(__x._M_p, __x._M_offset) { }

    const_reference
    operator*() const
    { return _Bit_reference(_M_p, 1UL << _M_offset); }

    const_iterator&
    operator++()
    {
      _M_bump_up();
      return *this;
    }

    const_iterator
    operator++(int)
    {
      const_iterator __tmp = *this;
      _M_bump_up();
      return __tmp;
    }

    const_iterator&
    operator--()
    {
      _M_bump_down();
      return *this;
    }

    const_iterator
    operator--(int)
    {
      const_iterator __tmp = *this;
      _M_bump_down();
      return __tmp;
    }

    const_iterator&
    operator+=(difference_type __i)
    {
      _M_incr(__i);
      return *this;
    }

    const_iterator&
    operator-=(difference_type __i)
    {
      *this += -__i;
      return *this;
    }

    const_iterator 
    operator+(difference_type __i) const
    {
      const_iterator __tmp = *this;
      return __tmp += __i;
    }

    const_iterator
    operator-(difference_type __i) const
    {
      const_iterator __tmp = *this;
      return __tmp -= __i;
    }

    const_reference
    operator[](difference_type __i) const
    { return *(*this + __i); }
  };

  inline _Bit_const_iterator
  operator+(ptrdiff_t __n, const _Bit_const_iterator& __x)
  { return __x + __n; }

  inline void
  __fill_bvector(_Bit_iterator __first, _Bit_iterator __last, bool __x)
  {
    for (; __first != __last; ++__first)
      *__first = __x;
  }

  inline void
  fill(_Bit_iterator __first, _Bit_iterator __last, const bool& __x)
  {
    if (__first._M_p != __last._M_p)
      {
	std::fill(__first._M_p + 1, __last._M_p, __x ? ~0 : 0);
	__fill_bvector(__first, _Bit_iterator(__first._M_p + 1, 0), __x);
	__fill_bvector(_Bit_iterator(__last._M_p, 0), __last, __x);
      }
    else
      __fill_bvector(__first, __last, __x);
  }

  template<typename _Alloc>
    struct _Bvector_base
    {
      typedef typename _Alloc::template rebind<_Bit_type>::other
        _Bit_alloc_type;
      
      struct _Bvector_impl
      : public _Bit_alloc_type
      {
	_Bit_iterator 	_M_start;
	_Bit_iterator 	_M_finish;
	_Bit_type* 	_M_end_of_storage;

	_Bvector_impl()
	: _Bit_alloc_type(), _M_start(), _M_finish(), _M_end_of_storage(0)
	{ }
 
	_Bvector_impl(const _Bit_alloc_type& __a)
	: _Bit_alloc_type(__a), _M_start(), _M_finish(), _M_end_of_storage(0)
	{ }
      };

    public:
      typedef _Alloc allocator_type;

      _Bit_alloc_type&
      _M_get_Bit_allocator()
      { return *static_cast<_Bit_alloc_type*>(&this->_M_impl); }

      const _Bit_alloc_type&
      _M_get_Bit_allocator() const
      { return *static_cast<const _Bit_alloc_type*>(&this->_M_impl); }

      allocator_type
      get_allocator() const
      { return allocator_type(_M_get_Bit_allocator()); }

      _Bvector_base()
      : _M_impl() { }
      
      _Bvector_base(const allocator_type& __a)
      : _M_impl(__a) { }


      ~_Bvector_base()
      { this->_M_deallocate(); }

    protected:
      _Bvector_impl _M_impl;

      _Bit_type*
      _M_allocate(size_t __n)
      { return _M_impl.allocate((__n + int(_S_word_bit) - 1)
				/ int(_S_word_bit)); }

      void
      _M_deallocate()
      {
	if (_M_impl._M_start._M_p)
	  _M_impl.deallocate(_M_impl._M_start._M_p,
			     _M_impl._M_end_of_storage - _M_impl._M_start._M_p);
      }
    };


} 



namespace std __attribute__ ((__visibility__ ("default")))
{


  















 
template<typename _Alloc>
  class vector<bool, _Alloc> : protected _Bvector_base<_Alloc>
  {
    typedef _Bvector_base<_Alloc>			 _Base;


  public:
    typedef bool                                         value_type;
    typedef size_t                                       size_type;
    typedef ptrdiff_t                                    difference_type;
    typedef _Bit_reference                               reference;
    typedef bool                                         const_reference;
    typedef _Bit_reference*                              pointer;
    typedef const bool*                                  const_pointer;
    typedef _Bit_iterator                                iterator;
    typedef _Bit_const_iterator                          const_iterator;
    typedef std::reverse_iterator<const_iterator>        const_reverse_iterator;
    typedef std::reverse_iterator<iterator>              reverse_iterator;
    typedef _Alloc                        		 allocator_type;

    allocator_type get_allocator() const
    { return _Base::get_allocator(); }

  protected:
    using _Base::_M_allocate;
    using _Base::_M_deallocate;
    using _Base::_M_get_Bit_allocator;

  public:
    vector()
    : _Base() { }

    explicit
    vector(const allocator_type& __a)
    : _Base(__a) { }

    explicit
    vector(size_type __n, const bool& __value = bool(), 
	   const allocator_type& __a = allocator_type())
    : _Base(__a)
    {
      _M_initialize(__n);
      std::fill(this->_M_impl._M_start._M_p, this->_M_impl._M_end_of_storage, 
		__value ? ~0 : 0);
    }

    vector(const vector& __x)
    : _Base(__x._M_get_Bit_allocator())
    {
      _M_initialize(__x.size());
      _M_copy_aligned(__x.begin(), __x.end(), this->_M_impl._M_start);
    }


    template<typename _InputIterator>
      vector(_InputIterator __first, _InputIterator __last,
	     const allocator_type& __a = allocator_type())
      : _Base(__a)
      {
	typedef typename std::__is_integer<_InputIterator>::__type _Integral;
	_M_initialize_dispatch(__first, __last, _Integral());
      }

    ~vector() { }

    vector&
    operator=(const vector& __x)
    {
      if (&__x == this)
	return *this;
      if (__x.size() > capacity())
	{
	  this->_M_deallocate();
	  _M_initialize(__x.size());
	}
      this->_M_impl._M_finish = _M_copy_aligned(__x.begin(), __x.end(),
						begin());
      return *this;
    }


    
    
    
    
    void
    assign(size_type __n, const bool& __x)
    { _M_fill_assign(__n, __x); }

    template<typename _InputIterator>
      void
      assign(_InputIterator __first, _InputIterator __last)
      {
	typedef typename std::__is_integer<_InputIterator>::__type _Integral;
	_M_assign_dispatch(__first, __last, _Integral());
      }


    iterator
    begin()
    { return this->_M_impl._M_start; }

    const_iterator
    begin() const
    { return this->_M_impl._M_start; }

    iterator
    end()
    { return this->_M_impl._M_finish; }

    const_iterator
    end() const
    { return this->_M_impl._M_finish; }

    reverse_iterator
    rbegin()
    { return reverse_iterator(end()); }

    const_reverse_iterator
    rbegin() const
    { return const_reverse_iterator(end()); }

    reverse_iterator
    rend()
    { return reverse_iterator(begin()); }

    const_reverse_iterator
    rend() const
    { return const_reverse_iterator(begin()); }


    size_type
    size() const
    { return size_type(end() - begin()); }

    size_type
    max_size() const
    {
      const size_type __isize =
	__gnu_cxx::__numeric_traits<difference_type>::__max
	- int(_S_word_bit) + 1;
      const size_type __asize = _M_get_Bit_allocator().max_size();
      return (__asize <= __isize / int(_S_word_bit)
	      ? __asize * int(_S_word_bit) : __isize);
    }

    size_type
    capacity() const
    { return size_type(const_iterator(this->_M_impl._M_end_of_storage, 0)
		       - begin()); }

    bool
    empty() const
    { return begin() == end(); }

    reference
    operator[](size_type __n)
    {
      return *iterator(this->_M_impl._M_start._M_p
		       + __n / int(_S_word_bit), __n % int(_S_word_bit));
    }

    const_reference
    operator[](size_type __n) const
    {
      return *const_iterator(this->_M_impl._M_start._M_p
			     + __n / int(_S_word_bit), __n % int(_S_word_bit));
    }

  protected:
    void
    _M_range_check(size_type __n) const
    {
      if (__n >= this->size())
        __throw_out_of_range(("vector<bool>::_M_range_check"));
    }

  public:
    reference
    at(size_type __n)
    { _M_range_check(__n); return (*this)[__n]; }

    const_reference
    at(size_type __n) const
    { _M_range_check(__n); return (*this)[__n]; }

    void
    reserve(size_type __n);

    reference
    front()
    { return *begin(); }

    const_reference
    front() const
    { return *begin(); }

    reference
    back()
    { return *(end() - 1); }

    const_reference
    back() const
    { return *(end() - 1); }

    
    
    
    
    
    void
    data() { }

    void
    push_back(bool __x)
    {
      if (this->_M_impl._M_finish._M_p != this->_M_impl._M_end_of_storage)
        *this->_M_impl._M_finish++ = __x;
      else
        _M_insert_aux(end(), __x);
    }

    void
    swap(vector& __x)
    {
      std::swap(this->_M_impl._M_start, __x._M_impl._M_start);
      std::swap(this->_M_impl._M_finish, __x._M_impl._M_finish);
      std::swap(this->_M_impl._M_end_of_storage, 
		__x._M_impl._M_end_of_storage);

      
      
      std::__alloc_swap<typename _Base::_Bit_alloc_type>::
	_S_do_it(_M_get_Bit_allocator(), __x._M_get_Bit_allocator());
    }

    
    static void
    swap(reference __x, reference __y)
    {
      bool __tmp = __x;
      __x = __y;
      __y = __tmp;
    }

    iterator
    insert(iterator __position, const bool& __x = bool())
    {
      const difference_type __n = __position - begin();
      if (this->_M_impl._M_finish._M_p != this->_M_impl._M_end_of_storage
	  && __position == end())
        *this->_M_impl._M_finish++ = __x;
      else
        _M_insert_aux(__position, __x);
      return begin() + __n;
    }

    template<typename _InputIterator>
      void
      insert(iterator __position,
	     _InputIterator __first, _InputIterator __last)
      {
	typedef typename std::__is_integer<_InputIterator>::__type _Integral;
	_M_insert_dispatch(__position, __first, __last, _Integral());
      }

    void
    insert(iterator __position, size_type __n, const bool& __x)
    { _M_fill_insert(__position, __n, __x); }


    void
    pop_back()
    { --this->_M_impl._M_finish; }

    iterator
    erase(iterator __position)
    {
      if (__position + 1 != end())
        std::copy(__position + 1, end(), __position);
      --this->_M_impl._M_finish;
      return __position;
    }

    iterator
    erase(iterator __first, iterator __last)
    {
      _M_erase_at_end(std::copy(__last, end(), __first));
      return __first;
    }

    void
    resize(size_type __new_size, bool __x = bool())
    {
      if (__new_size < size())
        _M_erase_at_end(begin() + difference_type(__new_size));
      else
        insert(end(), __new_size - size(), __x);
    }


    void
    flip()
    {
      for (_Bit_type * __p = this->_M_impl._M_start._M_p;
	   __p != this->_M_impl._M_end_of_storage; ++__p)
        *__p = ~*__p;
    }

    void
    clear()
    { _M_erase_at_end(begin()); }

   
  protected:
    
    iterator
    _M_copy_aligned(const_iterator __first, const_iterator __last,
		    iterator __result)
    {
      _Bit_type* __q = std::copy(__first._M_p, __last._M_p, __result._M_p);
      return std::copy(const_iterator(__last._M_p, 0), __last,
		       iterator(__q, 0));
    }

    void
    _M_initialize(size_type __n)
    {
      _Bit_type* __q = this->_M_allocate(__n);
      this->_M_impl._M_end_of_storage = (__q
					 + ((__n + int(_S_word_bit) - 1)
					    / int(_S_word_bit)));
      this->_M_impl._M_start = iterator(__q, 0);
      this->_M_impl._M_finish = this->_M_impl._M_start + difference_type(__n);
    }

    

    
    
    template<typename _Integer>
      void
      _M_initialize_dispatch(_Integer __n, _Integer __x, __true_type)
      {
	_M_initialize(static_cast<size_type>(__n));
	std::fill(this->_M_impl._M_start._M_p, 
		  this->_M_impl._M_end_of_storage, __x ? ~0 : 0);
      }

    template<typename _InputIterator>
      void 
      _M_initialize_dispatch(_InputIterator __first, _InputIterator __last,
			     __false_type)
      { _M_initialize_range(__first, __last, 
			    std::__iterator_category(__first)); }

    template<typename _InputIterator>
      void
      _M_initialize_range(_InputIterator __first, _InputIterator __last,
			  std::input_iterator_tag)
      {
	for (; __first != __last; ++__first)
	  push_back(*__first);
      }

    template<typename _ForwardIterator>
      void
      _M_initialize_range(_ForwardIterator __first, _ForwardIterator __last,
			  std::forward_iterator_tag)
      {
	const size_type __n = std::distance(__first, __last);
	_M_initialize(__n);
	std::copy(__first, __last, this->_M_impl._M_start);
      }

    
    
    template<typename _Integer>
      void
      _M_assign_dispatch(_Integer __n, _Integer __val, __true_type)
      { _M_fill_assign(__n, __val); }

    template<class _InputIterator>
      void
      _M_assign_dispatch(_InputIterator __first, _InputIterator __last,
			 __false_type)
      { _M_assign_aux(__first, __last, std::__iterator_category(__first)); }

    void
    _M_fill_assign(size_t __n, bool __x)
    {
      if (__n > size())
	{
	  std::fill(this->_M_impl._M_start._M_p, 
		    this->_M_impl._M_end_of_storage, __x ? ~0 : 0);
	  insert(end(), __n - size(), __x);
	}
      else
	{
	  _M_erase_at_end(begin() + __n);
	  std::fill(this->_M_impl._M_start._M_p, 
		    this->_M_impl._M_end_of_storage, __x ? ~0 : 0);
	}
    }

    template<typename _InputIterator>
      void
      _M_assign_aux(_InputIterator __first, _InputIterator __last,
		    std::input_iterator_tag)
      {
	iterator __cur = begin();
	for (; __first != __last && __cur != end(); ++__cur, ++__first)
	  *__cur = *__first;
	if (__first == __last)
	  _M_erase_at_end(__cur);
	else
	  insert(end(), __first, __last);
      }
    
    template<typename _ForwardIterator>
      void
      _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last,
		    std::forward_iterator_tag)
      {
	const size_type __len = std::distance(__first, __last);
	if (__len < size())
	  _M_erase_at_end(std::copy(__first, __last, begin()));
	else
	  {
	    _ForwardIterator __mid = __first;
	    std::advance(__mid, size());
	    std::copy(__first, __mid, begin());
	    insert(end(), __mid, __last);
	  }
      }

    

    
    
    template<typename _Integer>
      void
      _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __x,
			 __true_type)
      { _M_fill_insert(__pos, __n, __x); }

    template<typename _InputIterator>
      void
      _M_insert_dispatch(iterator __pos,
			 _InputIterator __first, _InputIterator __last,
			 __false_type)
      { _M_insert_range(__pos, __first, __last,
			std::__iterator_category(__first)); }

    void
    _M_fill_insert(iterator __position, size_type __n, bool __x);

    template<typename _InputIterator>
      void
      _M_insert_range(iterator __pos, _InputIterator __first, 
		      _InputIterator __last, std::input_iterator_tag)
      {
	for (; __first != __last; ++__first)
	  {
	    __pos = insert(__pos, *__first);
	    ++__pos;
	  }
      }

    template<typename _ForwardIterator>
      void
      _M_insert_range(iterator __position, _ForwardIterator __first, 
		      _ForwardIterator __last, std::forward_iterator_tag);

    void
    _M_insert_aux(iterator __position, bool __x);

    size_type
    _M_check_len(size_type __n, const char* __s) const
    {
      if (max_size() - size() < __n)
	__throw_length_error((__s));

      const size_type __len = size() + std::max(size(), __n);
      return (__len < size() || __len > max_size()) ? max_size() : __len;
    }

    void
    _M_erase_at_end(iterator __pos)
    { this->_M_impl._M_finish = __pos; }
  };


} 





























 






















































 




 


namespace std __attribute__ ((__visibility__ ("default")))
{


  template<typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
    reserve(size_type __n)
    {
      if (__n > this->max_size())
	__throw_length_error(("vector::reserve"));
      if (this->capacity() < __n)
	{
	  const size_type __old_size = size();
	  pointer __tmp = _M_allocate_and_copy(__n,
		 (this->_M_impl . _M_start),
		 (this->_M_impl . _M_finish));
	  std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
			_M_get_Tp_allocator());
	  _M_deallocate(this->_M_impl._M_start,
			this->_M_impl._M_end_of_storage
			- this->_M_impl._M_start);
	  this->_M_impl._M_start = __tmp;
	  this->_M_impl._M_finish = __tmp + __old_size;
	  this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
	}
    }


  template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::
    insert(iterator __position, const value_type& __x)
    {
      const size_type __n = __position - begin();
      if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage
	  && __position == end())
	{
	  this->_M_impl.construct(this->_M_impl._M_finish, __x);
	  ++this->_M_impl._M_finish;
	}
      else
	{
	    _M_insert_aux(__position, __x);
	}
      return iterator(this->_M_impl._M_start + __n);
    }

  template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::
    erase(iterator __position)
    {
      if (__position + 1 != end())
	std::copy(__position + 1, end(), __position);
      --this->_M_impl._M_finish;
      this->_M_impl.destroy(this->_M_impl._M_finish);
      return __position;
    }

  template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::
    erase(iterator __first, iterator __last)
    {
      if (__last != end())
	std::copy(__last, end(), __first);
      _M_erase_at_end(__first.base() + (end() - __last));
      return __first;
    }

  template<typename _Tp, typename _Alloc>
    vector<_Tp, _Alloc>&
    vector<_Tp, _Alloc>::
    operator=(const vector<_Tp, _Alloc>& __x)
    {
      if (&__x != this)
	{
	  const size_type __xlen = __x.size();
	  if (__xlen > capacity())
	    {
	      pointer __tmp = _M_allocate_and_copy(__xlen, __x.begin(),
						   __x.end());
	      std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
			    _M_get_Tp_allocator());
	      _M_deallocate(this->_M_impl._M_start,
			    this->_M_impl._M_end_of_storage
			    - this->_M_impl._M_start);
	      this->_M_impl._M_start = __tmp;
	      this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __xlen;
	    }
	  else if (size() >= __xlen)
	    {
	      std::_Destroy(std::copy(__x.begin(), __x.end(), begin()),
			    end(), _M_get_Tp_allocator());
	    }
	  else
	    {
	      std::copy(__x._M_impl._M_start, __x._M_impl._M_start + size(),
			this->_M_impl._M_start);
	      std::__uninitialized_copy_a(__x._M_impl._M_start + size(),
					  __x._M_impl._M_finish,
					  this->_M_impl._M_finish,
					  _M_get_Tp_allocator());
	    }
	  this->_M_impl._M_finish = this->_M_impl._M_start + __xlen;
	}
      return *this;
    }

  template<typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
    _M_fill_assign(size_t __n, const value_type& __val)
    {
      if (__n > capacity())
	{
	  vector __tmp(__n, __val, _M_get_Tp_allocator());
	  __tmp.swap(*this);
	}
      else if (__n > size())
	{
	  std::fill(begin(), end(), __val);
	  std::__uninitialized_fill_n_a(this->_M_impl._M_finish,
					__n - size(), __val,
					_M_get_Tp_allocator());
	  this->_M_impl._M_finish += __n - size();
	}
      else
        _M_erase_at_end(std::fill_n(this->_M_impl._M_start, __n, __val));
    }

  template<typename _Tp, typename _Alloc>
    template<typename _InputIterator>
      void
      vector<_Tp, _Alloc>::
      _M_assign_aux(_InputIterator __first, _InputIterator __last,
		    std::input_iterator_tag)
      {
	pointer __cur(this->_M_impl._M_start);
	for (; __first != __last && __cur != this->_M_impl._M_finish;
	     ++__cur, ++__first)
	  *__cur = *__first;
	if (__first == __last)
	  _M_erase_at_end(__cur);
	else
	  insert(end(), __first, __last);
      }

  template<typename _Tp, typename _Alloc>
    template<typename _ForwardIterator>
      void
      vector<_Tp, _Alloc>::
      _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last,
		    std::forward_iterator_tag)
      {
	const size_type __len = std::distance(__first, __last);

	if (__len > capacity())
	  {
	    pointer __tmp(_M_allocate_and_copy(__len, __first, __last));
	    std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
			  _M_get_Tp_allocator());
	    _M_deallocate(this->_M_impl._M_start,
			  this->_M_impl._M_end_of_storage
			  - this->_M_impl._M_start);
	    this->_M_impl._M_start = __tmp;
	    this->_M_impl._M_finish = this->_M_impl._M_start + __len;
	    this->_M_impl._M_end_of_storage = this->_M_impl._M_finish;
	  }
	else if (size() >= __len)
	  _M_erase_at_end(std::copy(__first, __last, this->_M_impl._M_start));
	else
	  {
	    _ForwardIterator __mid = __first;
	    std::advance(__mid, size());
	    std::copy(__first, __mid, this->_M_impl._M_start);
	    this->_M_impl._M_finish =
	      std::__uninitialized_copy_a(__mid, __last,
					  this->_M_impl._M_finish,
					  _M_get_Tp_allocator());
	  }
      }

  template<typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
    _M_insert_aux(iterator __position, const _Tp& __x)
    {
      if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
	{
	  this->_M_impl.construct(this->_M_impl._M_finish,
				  (*(this->_M_impl . _M_finish - 1)));
	  ++this->_M_impl._M_finish;
	  _Tp __x_copy = __x;
	  std::copy_backward(__position . base(), this->_M_impl . _M_finish - 2, this->_M_impl . _M_finish - 1);
	  *__position = __x_copy;
	}
      else
	{
	  const size_type __len =
	    _M_check_len(size_type(1), "vector::_M_insert_aux");
	  const size_type __elems_before = __position - begin();
	  pointer __new_start(this->_M_allocate(__len));
	  pointer __new_finish(__new_start);
	  try
	    {
	      
	      
	      
	      
	      this->_M_impl.construct(__new_start + __elems_before,
	                              __x);
	      __new_finish = 0;

	      __new_finish =
		std::__uninitialized_move_a(this->_M_impl._M_start,
					    __position.base(), __new_start,
					    _M_get_Tp_allocator());
	      ++__new_finish;

	      __new_finish =
		std::__uninitialized_move_a(__position.base(),
					    this->_M_impl._M_finish,
					    __new_finish,
					    _M_get_Tp_allocator());
	    }
          catch(...)
	    {
	      if (!__new_finish)
		this->_M_impl.destroy(__new_start + __elems_before);
	      else
		std::_Destroy(__new_start, __new_finish, _M_get_Tp_allocator());
	      _M_deallocate(__new_start, __len);
	      throw;
	    }
	  std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
			_M_get_Tp_allocator());
	  _M_deallocate(this->_M_impl._M_start,
			this->_M_impl._M_end_of_storage
			- this->_M_impl._M_start);
	  this->_M_impl._M_start = __new_start;
	  this->_M_impl._M_finish = __new_finish;
	  this->_M_impl._M_end_of_storage = __new_start + __len;
	}
    }

  template<typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
    _M_fill_insert(iterator __position, size_type __n, const value_type& __x)
    {
      if (__n != 0)
	{
	  if (size_type(this->_M_impl._M_end_of_storage
			- this->_M_impl._M_finish) >= __n)
	    {
	      value_type __x_copy = __x;
	      const size_type __elems_after = end() - __position;
	      pointer __old_finish(this->_M_impl._M_finish);
	      if (__elems_after > __n)
		{
		  std::__uninitialized_move_a(this->_M_impl._M_finish - __n,
					      this->_M_impl._M_finish,
					      this->_M_impl._M_finish,
					      _M_get_Tp_allocator());
		  this->_M_impl._M_finish += __n;
		  std::copy_backward(__position . base(), __old_finish - __n, __old_finish);
		  std::fill(__position.base(), __position.base() + __n,
			    __x_copy);
		}
	      else
		{
		  std::__uninitialized_fill_n_a(this->_M_impl._M_finish,
						__n - __elems_after,
						__x_copy,
						_M_get_Tp_allocator());
		  this->_M_impl._M_finish += __n - __elems_after;
		  std::__uninitialized_move_a(__position.base(), __old_finish,
					      this->_M_impl._M_finish,
					      _M_get_Tp_allocator());
		  this->_M_impl._M_finish += __elems_after;
		  std::fill(__position.base(), __old_finish, __x_copy);
		}
	    }
	  else
	    {
	      const size_type __len =
		_M_check_len(__n, "vector::_M_fill_insert");
	      const size_type __elems_before = __position - begin();
	      pointer __new_start(this->_M_allocate(__len));
	      pointer __new_finish(__new_start);
	      try
		{
		  
		  std::__uninitialized_fill_n_a(__new_start + __elems_before,
						__n, __x,
						_M_get_Tp_allocator());
		  __new_finish = 0;

		  __new_finish =
		    std::__uninitialized_move_a(this->_M_impl._M_start,
						__position.base(),
						__new_start,
						_M_get_Tp_allocator());
		  __new_finish += __n;

		  __new_finish =
		    std::__uninitialized_move_a(__position.base(),
						this->_M_impl._M_finish,
						__new_finish,
						_M_get_Tp_allocator());
		}
	      catch(...)
		{
		  if (!__new_finish)
		    std::_Destroy(__new_start + __elems_before,
				  __new_start + __elems_before + __n,
				  _M_get_Tp_allocator());
		  else
		    std::_Destroy(__new_start, __new_finish,
				  _M_get_Tp_allocator());
		  _M_deallocate(__new_start, __len);
		  throw;
		}
	      std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
			    _M_get_Tp_allocator());
	      _M_deallocate(this->_M_impl._M_start,
			    this->_M_impl._M_end_of_storage
			    - this->_M_impl._M_start);
	      this->_M_impl._M_start = __new_start;
	      this->_M_impl._M_finish = __new_finish;
	      this->_M_impl._M_end_of_storage = __new_start + __len;
	    }
	}
    }


  template<typename _Tp, typename _Alloc>
    template<typename _InputIterator>
      void
      vector<_Tp, _Alloc>::
      _M_range_insert(iterator __pos, _InputIterator __first,
		      _InputIterator __last, std::input_iterator_tag)
      {
	for (; __first != __last; ++__first)
	  {
	    __pos = insert(__pos, *__first);
	    ++__pos;
	  }
      }

  template<typename _Tp, typename _Alloc>
    template<typename _ForwardIterator>
      void
      vector<_Tp, _Alloc>::
      _M_range_insert(iterator __position, _ForwardIterator __first,
		      _ForwardIterator __last, std::forward_iterator_tag)
      {
	if (__first != __last)
	  {
	    const size_type __n = std::distance(__first, __last);
	    if (size_type(this->_M_impl._M_end_of_storage
			  - this->_M_impl._M_finish) >= __n)
	      {
		const size_type __elems_after = end() - __position;
		pointer __old_finish(this->_M_impl._M_finish);
		if (__elems_after > __n)
		  {
		    std::__uninitialized_move_a(this->_M_impl._M_finish - __n,
						this->_M_impl._M_finish,
						this->_M_impl._M_finish,
						_M_get_Tp_allocator());
		    this->_M_impl._M_finish += __n;
		    std::copy_backward(__position . base(), __old_finish - __n, __old_finish);
		    std::copy(__first, __last, __position);
		  }
		else
		  {
		    _ForwardIterator __mid = __first;
		    std::advance(__mid, __elems_after);
		    std::__uninitialized_copy_a(__mid, __last,
						this->_M_impl._M_finish,
						_M_get_Tp_allocator());
		    this->_M_impl._M_finish += __n - __elems_after;
		    std::__uninitialized_move_a(__position.base(),
						__old_finish,
						this->_M_impl._M_finish,
						_M_get_Tp_allocator());
		    this->_M_impl._M_finish += __elems_after;
		    std::copy(__first, __mid, __position);
		  }
	      }
	    else
	      {
		const size_type __len =
		  _M_check_len(__n, "vector::_M_range_insert");
		pointer __new_start(this->_M_allocate(__len));
		pointer __new_finish(__new_start);
		try
		  {
		    __new_finish =
		      std::__uninitialized_move_a(this->_M_impl._M_start,
						  __position.base(),
						  __new_start,
						  _M_get_Tp_allocator());
		    __new_finish =
		      std::__uninitialized_copy_a(__first, __last,
						  __new_finish,
						  _M_get_Tp_allocator());
		    __new_finish =
		      std::__uninitialized_move_a(__position.base(),
						  this->_M_impl._M_finish,
						  __new_finish,
						  _M_get_Tp_allocator());
		  }
		catch(...)
		  {
		    std::_Destroy(__new_start, __new_finish,
				  _M_get_Tp_allocator());
		    _M_deallocate(__new_start, __len);
		    throw;
		  }
		std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
			      _M_get_Tp_allocator());
		_M_deallocate(this->_M_impl._M_start,
			      this->_M_impl._M_end_of_storage
			      - this->_M_impl._M_start);
		this->_M_impl._M_start = __new_start;
		this->_M_impl._M_finish = __new_finish;
		this->_M_impl._M_end_of_storage = __new_start + __len;
	      }
	  }
      }


  

  template<typename _Alloc>
    void
    vector<bool, _Alloc>::
    reserve(size_type __n)
    {
      if (__n > this->max_size())
	__throw_length_error(("vector::reserve"));
      if (this->capacity() < __n)
	{
	  _Bit_type* __q = this->_M_allocate(__n);
	  this->_M_impl._M_finish = _M_copy_aligned(begin(), end(),
						    iterator(__q, 0));
	  this->_M_deallocate();
	  this->_M_impl._M_start = iterator(__q, 0);
	  this->_M_impl._M_end_of_storage = (__q + (__n + int(_S_word_bit) - 1)
					     / int(_S_word_bit));
	}
    }

  template<typename _Alloc>
    void
    vector<bool, _Alloc>::
    _M_fill_insert(iterator __position, size_type __n, bool __x)
    {
      if (__n == 0)
	return;
      if (capacity() - size() >= __n)
	{
	  std::copy_backward(__position, end(),
			     this->_M_impl._M_finish + difference_type(__n));
	  std::fill(__position, __position + difference_type(__n), __x);
	  this->_M_impl._M_finish += difference_type(__n);
	}
      else
	{
	  const size_type __len = 
	    _M_check_len(__n, "vector<bool>::_M_fill_insert");
	  _Bit_type * __q = this->_M_allocate(__len);
	  iterator __i = _M_copy_aligned(begin(), __position,
					 iterator(__q, 0));
	  std::fill(__i, __i + difference_type(__n), __x);
	  this->_M_impl._M_finish = std::copy(__position, end(),
					      __i + difference_type(__n));
	  this->_M_deallocate();
	  this->_M_impl._M_end_of_storage = (__q + ((__len
						     + int(_S_word_bit) - 1)
						    / int(_S_word_bit)));
	  this->_M_impl._M_start = iterator(__q, 0);
	}
    }

  template<typename _Alloc>
    template<typename _ForwardIterator>
      void
      vector<bool, _Alloc>::
      _M_insert_range(iterator __position, _ForwardIterator __first, 
		      _ForwardIterator __last, std::forward_iterator_tag)
      {
	if (__first != __last)
	  {
	    size_type __n = std::distance(__first, __last);
	    if (capacity() - size() >= __n)
	      {
		std::copy_backward(__position, end(),
				   this->_M_impl._M_finish
				   + difference_type(__n));
		std::copy(__first, __last, __position);
		this->_M_impl._M_finish += difference_type(__n);
	      }
	    else
	      {
		const size_type __len =
		  _M_check_len(__n, "vector<bool>::_M_insert_range");
		_Bit_type * __q = this->_M_allocate(__len);
		iterator __i = _M_copy_aligned(begin(), __position,
					       iterator(__q, 0));
		__i = std::copy(__first, __last, __i);
		this->_M_impl._M_finish = std::copy(__position, end(), __i);
		this->_M_deallocate();
		this->_M_impl._M_end_of_storage = (__q
						   + ((__len
						       + int(_S_word_bit) - 1)
						      / int(_S_word_bit)));
		this->_M_impl._M_start = iterator(__q, 0);
	      }
	  }
      }

  template<typename _Alloc>
    void
    vector<bool, _Alloc>::
    _M_insert_aux(iterator __position, bool __x)
    {
      if (this->_M_impl._M_finish._M_p != this->_M_impl._M_end_of_storage)
	{
	  std::copy_backward(__position, this->_M_impl._M_finish, 
			     this->_M_impl._M_finish + 1);
	  *__position = __x;
	  ++this->_M_impl._M_finish;
	}
      else
	{
	  const size_type __len =
	    _M_check_len(size_type(1), "vector<bool>::_M_insert_aux");
	  _Bit_type * __q = this->_M_allocate(__len);
	  iterator __i = _M_copy_aligned(begin(), __position,
					 iterator(__q, 0));
	  *__i++ = __x;
	  this->_M_impl._M_finish = std::copy(__position, end(), __i);
	  this->_M_deallocate();
	  this->_M_impl._M_end_of_storage = (__q + ((__len
						     + int(_S_word_bit) - 1)
						    / int(_S_word_bit)));
	  this->_M_impl._M_start = iterator(__q, 0);
	}
    }


} 



























 




































 

























 



 







 


extern "C" {

 
extern void __assert_fail (__const char *__assertion, __const char *__file,
			   unsigned int __line, __const char *__function)
     throw () __attribute__ ((__noreturn__));

 
extern void __assert_perror_fail (int __errnum, __const char *__file,
				  unsigned int __line,
				  __const char *__function)
     throw () __attribute__ ((__noreturn__));



 
extern void __assert (const char *__assertion, const char *__file, int __line)
     throw () __attribute__ ((__noreturn__));


}







 




























 



































 


































 



































 




































 








namespace std __attribute__ ((__visibility__ ("default")))
{


  template<typename _Alloc>
    class allocator;

  



 

  template<class _CharT>
    struct char_traits;

  template<typename _CharT, typename _Traits = char_traits<_CharT>,
           typename _Alloc = allocator<_CharT> >
    class basic_string;

  template<> struct char_traits<char>;

  typedef basic_string<char>    string;   

  template<> struct char_traits<wchar_t>;

  typedef basic_string<wchar_t> wstring;   

   


} 






























 










































 























 




 



 

















 



 





 
struct _IO_FILE;


 
typedef struct _IO_FILE FILE;






 
typedef struct _IO_FILE __FILE;




 








 























 


typedef __builtin_va_list va_list;



 


 
typedef __builtin_va_list __gnuc_va_list;



















 


 


 


 































 
typedef long ptrdiff_t;

typedef unsigned long size_t;


 







 
 
typedef unsigned int wint_t;

 


 

 

 
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;		 
} __mbstate_t;



 


 
typedef __mbstate_t mbstate_t;



 



 


extern "C" {



 
struct tm;



 




 
extern wchar_t *wcscpy (wchar_t *__restrict __dest,
			__const wchar_t *__restrict __src) throw ();
 
extern wchar_t *wcsncpy (wchar_t *__restrict __dest,
			 __const wchar_t *__restrict __src, size_t __n)
     throw ();

 
extern wchar_t *wcscat (wchar_t *__restrict __dest,
			__const wchar_t *__restrict __src) throw ();
 
extern wchar_t *wcsncat (wchar_t *__restrict __dest,
			 __const wchar_t *__restrict __src, size_t __n)
     throw ();

 
extern int wcscmp (__const wchar_t *__s1, __const wchar_t *__s2)
     throw () __attribute__ ((__pure__));
 
extern int wcsncmp (__const wchar_t *__s1, __const wchar_t *__s2, size_t __n)
     throw () __attribute__ ((__pure__));


 
extern int wcscasecmp (__const wchar_t *__s1, __const wchar_t *__s2) throw ();

 
extern int wcsncasecmp (__const wchar_t *__s1, __const wchar_t *__s2,
			size_t __n) throw ();


 


















 





 
typedef struct __locale_struct
{
   
  struct locale_data *__locales[13];  

   
  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;

   
  const char *__names[13];
} *__locale_t;

 
typedef __locale_t locale_t;


extern int wcscasecmp_l (__const wchar_t *__s1, __const wchar_t *__s2,
			 __locale_t __loc) throw ();

extern int wcsncasecmp_l (__const wchar_t *__s1, __const wchar_t *__s2,
			  size_t __n, __locale_t __loc) throw ();



 
extern int wcscoll (__const wchar_t *__s1, __const wchar_t *__s2) throw ();


 
extern size_t wcsxfrm (wchar_t *__restrict __s1,
		       __const wchar_t *__restrict __s2, size_t __n) throw ();



 


 
extern int wcscoll_l (__const wchar_t *__s1, __const wchar_t *__s2,
		      __locale_t __loc) throw ();



 
extern size_t wcsxfrm_l (wchar_t *__s1, __const wchar_t *__s2,
			 size_t __n, __locale_t __loc) throw ();

 
extern wchar_t *wcsdup (__const wchar_t *__s) throw () __attribute__ ((__malloc__));


 
extern "C++" wchar_t *wcschr (wchar_t *__wcs, wchar_t __wc)
     throw () __asm ("wcschr") __attribute__ ((__pure__));
extern "C++" __const wchar_t *wcschr (__const wchar_t *__wcs, wchar_t __wc)
     throw () __asm ("wcschr")  __attribute__ ((__pure__));
 
extern "C++" wchar_t *wcsrchr (wchar_t *__wcs, wchar_t __wc)
     throw () __asm ("wcsrchr") __attribute__ ((__pure__));
extern "C++" __const wchar_t *wcsrchr (__const wchar_t *__wcs, wchar_t __wc)
     throw () __asm ("wcsrchr") __attribute__ ((__pure__));



 
extern wchar_t *wcschrnul (__const wchar_t *__s, wchar_t __wc)
     throw () __attribute__ ((__pure__));



 
extern size_t wcscspn (__const wchar_t *__wcs, __const wchar_t *__reject)
     throw () __attribute__ ((__pure__));

 
extern size_t wcsspn (__const wchar_t *__wcs, __const wchar_t *__accept)
     throw () __attribute__ ((__pure__));
 
extern "C++" wchar_t *wcspbrk (wchar_t *__wcs, __const wchar_t *__accept)
     throw () __asm ("wcspbrk") __attribute__ ((__pure__));
extern "C++" __const wchar_t *wcspbrk (__const wchar_t *__wcs,
				       __const wchar_t *__accept)
     throw () __asm ("wcspbrk") __attribute__ ((__pure__));
 
extern "C++" wchar_t *wcsstr (wchar_t *__haystack, __const wchar_t *__needle)
     throw () __asm ("wcsstr") __attribute__ ((__pure__));
extern "C++" __const wchar_t *wcsstr (__const wchar_t *__haystack,
				      __const wchar_t *__needle)
     throw () __asm ("wcsstr") __attribute__ ((__pure__));

 
extern wchar_t *wcstok (wchar_t *__restrict __s,
			__const wchar_t *__restrict __delim,
			wchar_t **__restrict __ptr) throw ();

 
extern size_t wcslen (__const wchar_t *__s) throw () __attribute__ ((__pure__));


 
extern "C++" wchar_t *wcswcs (wchar_t *__haystack, __const wchar_t *__needle)
     throw () __asm ("wcswcs") __attribute__ ((__pure__));
extern "C++" __const wchar_t *wcswcs (__const wchar_t *__haystack,
				      __const wchar_t *__needle)
     throw () __asm ("wcswcs") __attribute__ ((__pure__));

 
extern size_t wcsnlen (__const wchar_t *__s, size_t __maxlen)
     throw () __attribute__ ((__pure__));



 
extern "C++" wchar_t *wmemchr (wchar_t *__s, wchar_t __c, size_t __n)
     throw () __asm ("wmemchr") __attribute__ ((__pure__));
extern "C++" __const wchar_t *wmemchr (__const wchar_t *__s, wchar_t __c,
				       size_t __n)
     throw () __asm ("wmemchr") __attribute__ ((__pure__));

 
extern int wmemcmp (__const wchar_t *__restrict __s1,
		    __const wchar_t *__restrict __s2, size_t __n)
     throw () __attribute__ ((__pure__));

 
extern wchar_t *wmemcpy (wchar_t *__restrict __s1,
			 __const wchar_t *__restrict __s2, size_t __n) throw ();


 
extern wchar_t *wmemmove (wchar_t *__s1, __const wchar_t *__s2, size_t __n)
     throw ();

 
extern wchar_t *wmemset (wchar_t *__s, wchar_t __c, size_t __n) throw ();



 
extern wchar_t *wmempcpy (wchar_t *__restrict __s1,
			  __const wchar_t *__restrict __s2, size_t __n)
     throw ();




 
extern wint_t btowc (int __c) throw ();


 
extern int wctob (wint_t __c) throw ();


 
extern int mbsinit (__const mbstate_t *__ps) throw () __attribute__ ((__pure__));


 
extern size_t mbrtowc (wchar_t *__restrict __pwc,
		       __const char *__restrict __s, size_t __n,
		       mbstate_t *__p) throw ();

 
extern size_t wcrtomb (char *__restrict __s, wchar_t __wc,
		       mbstate_t *__restrict __ps) throw ();

 
extern size_t __mbrlen (__const char *__restrict __s, size_t __n,
			mbstate_t *__restrict __ps) throw ();
extern size_t mbrlen (__const char *__restrict __s, size_t __n,
		      mbstate_t *__restrict __ps) throw ();


 



 
extern wint_t __btowc_alias (int __c) __asm ("btowc");
extern __inline __attribute__ ((__gnu_inline__)) wint_t
btowc (int __c) throw ()
{ return (__builtin_constant_p (__c) && __c >= '\0' && __c <= '\x7f'
	  ? (wint_t) __c : __btowc_alias (__c)); }

extern int __wctob_alias (wint_t __c) __asm ("wctob");
extern __inline __attribute__ ((__gnu_inline__)) int
wctob (wint_t __wc) throw ()
{ return (__builtin_constant_p (__wc) && __wc >= L'\0' && __wc <= L'\x7f'
	  ? (int) __wc : __wctob_alias (__wc)); }

extern __inline __attribute__ ((__gnu_inline__)) size_t
mbrlen (__const char *__restrict __s, size_t __n, mbstate_t *__restrict __ps) throw ()
{ return (__ps != __null
	  ? mbrtowc (__null, __s, __n, __ps) : __mbrlen (__s, __n, __null)); }



 
extern size_t mbsrtowcs (wchar_t *__restrict __dst,
			 __const char **__restrict __src, size_t __len,
			 mbstate_t *__restrict __ps) throw ();


 
extern size_t wcsrtombs (char *__restrict __dst,
			 __const wchar_t **__restrict __src, size_t __len,
			 mbstate_t *__restrict __ps) throw ();




 
extern size_t mbsnrtowcs (wchar_t *__restrict __dst,
			  __const char **__restrict __src, size_t __nmc,
			  size_t __len, mbstate_t *__restrict __ps) throw ();


 
extern size_t wcsnrtombs (char *__restrict __dst,
			  __const wchar_t **__restrict __src,
			  size_t __nwc, size_t __len,
			  mbstate_t *__restrict __ps) throw ();


 
 
extern int wcwidth (wchar_t __c) throw ();


 
extern int wcswidth (__const wchar_t *__s, size_t __n) throw ();




 
extern double wcstod (__const wchar_t *__restrict __nptr,
		      wchar_t **__restrict __endptr) throw ();



 
extern float wcstof (__const wchar_t *__restrict __nptr,
		     wchar_t **__restrict __endptr) throw ();
extern long double wcstold (__const wchar_t *__restrict __nptr,
			    wchar_t **__restrict __endptr) throw ();





 
extern long int wcstol (__const wchar_t *__restrict __nptr,
			wchar_t **__restrict __endptr, int __base) throw ();


 
extern unsigned long int wcstoul (__const wchar_t *__restrict __nptr,
				  wchar_t **__restrict __endptr, int __base)
     throw ();




 
__extension__
extern long long int wcstoll (__const wchar_t *__restrict __nptr,
			      wchar_t **__restrict __endptr, int __base)
     throw ();


 
__extension__
extern unsigned long long int wcstoull (__const wchar_t *__restrict __nptr,
					wchar_t **__restrict __endptr,
					int __base) throw ();



 
__extension__
extern long long int wcstoq (__const wchar_t *__restrict __nptr,
			     wchar_t **__restrict __endptr, int __base)
     throw ();


 
__extension__
extern unsigned long long int wcstouq (__const wchar_t *__restrict __nptr,
				       wchar_t **__restrict __endptr,
				       int __base) throw ();










 


 


 
extern long int wcstol_l (__const wchar_t *__restrict __nptr,
			  wchar_t **__restrict __endptr, int __base,
			  __locale_t __loc) throw ();

extern unsigned long int wcstoul_l (__const wchar_t *__restrict __nptr,
				    wchar_t **__restrict __endptr,
				    int __base, __locale_t __loc) throw ();

__extension__
extern long long int wcstoll_l (__const wchar_t *__restrict __nptr,
				wchar_t **__restrict __endptr,
				int __base, __locale_t __loc) throw ();

__extension__
extern unsigned long long int wcstoull_l (__const wchar_t *__restrict __nptr,
					  wchar_t **__restrict __endptr,
					  int __base, __locale_t __loc)
     throw ();

extern double wcstod_l (__const wchar_t *__restrict __nptr,
			wchar_t **__restrict __endptr, __locale_t __loc)
     throw ();

extern float wcstof_l (__const wchar_t *__restrict __nptr,
		       wchar_t **__restrict __endptr, __locale_t __loc)
     throw ();

extern long double wcstold_l (__const wchar_t *__restrict __nptr,
			      wchar_t **__restrict __endptr,
			      __locale_t __loc) throw ();



 
extern wchar_t *wcpcpy (wchar_t *__dest, __const wchar_t *__src) throw ();


 
extern wchar_t *wcpncpy (wchar_t *__dest, __const wchar_t *__src, size_t __n)
     throw ();


 


 
extern __FILE *open_wmemstream (wchar_t **__bufloc, size_t *__sizeloc) throw ();



 
extern int fwide (__FILE *__fp, int __mode) throw ();





 
extern int fwprintf (__FILE *__restrict __stream,
		     __const wchar_t *__restrict __format, ...)
      ;



 
extern int wprintf (__const wchar_t *__restrict __format, ...)
      ;
 
extern int swprintf (wchar_t *__restrict __s, size_t __n,
		     __const wchar_t *__restrict __format, ...)
     throw ()  ;




 
extern int vfwprintf (__FILE *__restrict __s,
		      __const wchar_t *__restrict __format,
		      __gnuc_va_list __arg)
      ;



 
extern int vwprintf (__const wchar_t *__restrict __format,
		     __gnuc_va_list __arg)
      ;

 
extern int vswprintf (wchar_t *__restrict __s, size_t __n,
		      __const wchar_t *__restrict __format,
		      __gnuc_va_list __arg)
     throw ()  ;





 
extern int fwscanf (__FILE *__restrict __stream,
		    __const wchar_t *__restrict __format, ...)
      ;



 
extern int wscanf (__const wchar_t *__restrict __format, ...)
      ;
 
extern int swscanf (__const wchar_t *__restrict __s,
		    __const wchar_t *__restrict __format, ...)
     throw ()  ;








 
extern int vfwscanf (__FILE *__restrict __s,
		     __const wchar_t *__restrict __format,
		     __gnuc_va_list __arg)
      ;



 
extern int vwscanf (__const wchar_t *__restrict __format,
		    __gnuc_va_list __arg)
      ;
 
extern int vswscanf (__const wchar_t *__restrict __s,
		     __const wchar_t *__restrict __format,
		     __gnuc_va_list __arg)
     throw ()  ;









 
extern wint_t fgetwc (__FILE *__stream);
extern wint_t getwc (__FILE *__stream);




 
extern wint_t getwchar (void);





 
extern wint_t fputwc (wchar_t __wc, __FILE *__stream);
extern wint_t putwc (wchar_t __wc, __FILE *__stream);




 
extern wint_t putwchar (wchar_t __wc);






 
extern wchar_t *fgetws (wchar_t *__restrict __ws, int __n,
			__FILE *__restrict __stream);




 
extern int fputws (__const wchar_t *__restrict __ws,
		   __FILE *__restrict __stream);





 
extern wint_t ungetwc (wint_t __wc, __FILE *__stream);









 
extern wint_t getwc_unlocked (__FILE *__stream);
extern wint_t getwchar_unlocked (void);






 
extern wint_t fgetwc_unlocked (__FILE *__stream);






 
extern wint_t fputwc_unlocked (wchar_t __wc, __FILE *__stream);







 
extern wint_t putwc_unlocked (wchar_t __wc, __FILE *__stream);
extern wint_t putwchar_unlocked (wchar_t __wc);







 
extern wchar_t *fgetws_unlocked (wchar_t *__restrict __ws, int __n,
				 __FILE *__restrict __stream);






 
extern int fputws_unlocked (__const wchar_t *__restrict __ws,
			    __FILE *__restrict __stream);





 
extern size_t wcsftime (wchar_t *__restrict __s, size_t __maxsize,
			__const wchar_t *__restrict __format,
			__const struct tm *__restrict __tp) throw ();




 
extern size_t wcsftime_l (wchar_t *__restrict __s, size_t __maxsize,
			  __const wchar_t *__restrict __format,
			  __const struct tm *__restrict __tp,
			  __locale_t __loc) throw ();






 

 


}




 





namespace std
{
  using ::mbstate_t;
} 




namespace std __attribute__ ((__visibility__ ("default")))
{
  using ::wint_t;

  using ::btowc;
  using ::fgetwc;
  using ::fgetws;
  using ::fputwc;
  using ::fputws;
  using ::fwide;
  using ::fwprintf;
  using ::fwscanf;
  using ::getwc;
  using ::getwchar;
  using ::mbrlen;
  using ::mbrtowc;
  using ::mbsinit;
  using ::mbsrtowcs;
  using ::putwc;
  using ::putwchar;
  using ::swprintf;
  using ::swscanf;
  using ::ungetwc;
  using ::vfwprintf;
  using ::vfwscanf;
  using ::vswprintf;
  using ::vswscanf;
  using ::vwprintf;
  using ::vwscanf;
  using ::wcrtomb;
  using ::wcscat;
  using ::wcscmp;
  using ::wcscoll;
  using ::wcscpy;
  using ::wcscspn;
  using ::wcsftime;
  using ::wcslen;
  using ::wcsncat;
  using ::wcsncmp;
  using ::wcsncpy;
  using ::wcsrtombs;
  using ::wcsspn;
  using ::wcstod;
  using ::wcstof;
  using ::wcstok;
  using ::wcstol;
  using ::wcstoul;
  using ::wcsxfrm;
  using ::wctob;
  using ::wmemcmp;
  using ::wmemcpy;
  using ::wmemmove;
  using ::wmemset;
  using ::wprintf;
  using ::wscanf;
  using ::wcschr;
  using ::wcspbrk;
  using ::wcsrchr;
  using ::wcsstr;
  using ::wmemchr;





} 



namespace __gnu_cxx
{
  using ::wcstold;
  using ::wcstoll;
  using ::wcstoull;
} 

namespace std
{
  using ::__gnu_cxx::wcstold;
  using ::__gnu_cxx::wcstoll;
  using ::__gnu_cxx::wcstoull;
} 









namespace std __attribute__ ((__visibility__ ("default")))
{


  
  
  
  
  
  

  






   
  typedef long          streamoff;

  
  typedef ptrdiff_t	streamsize; 

  









 
  template<typename _StateT>
    class fpos
    {
    private:
      streamoff	                _M_off;
      _StateT			_M_state;

    public:
      
      
      
      
      fpos()
      : _M_off(0), _M_state() { }

      
      
      
      
      
      
      
      fpos(streamoff __off)
      : _M_off(__off), _M_state() { }

      
      operator streamoff() const { return _M_off; }

      
      void
      state(_StateT __st)
      { _M_state = __st; }

      
      _StateT
      state() const
      { return _M_state; }

      
      
      
      
      fpos&
      operator+=(streamoff __off)
      {
	_M_off += __off;
	return *this;
      }

      
      
      
      
      fpos&
      operator-=(streamoff __off)
      {
	_M_off -= __off;
	return *this;
      }

      
      
      
      
      
      
      fpos
      operator+(streamoff __off) const
      {
	fpos __pos(*this);
	__pos += __off;
	return __pos;
      }

      
      
      
      
      
      
      fpos
      operator-(streamoff __off) const
      {
	fpos __pos(*this);
	__pos -= __off;
	return __pos;
      }

      
      
      
      
      
      streamoff
      operator-(const fpos& __other) const
      { return _M_off - __other._M_off; }
    };

  
  
  
  
  
  template<typename _StateT>
    inline bool
    operator==(const fpos<_StateT>& __lhs, const fpos<_StateT>& __rhs)
    { return streamoff(__lhs) == streamoff(__rhs); }

  template<typename _StateT>
    inline bool
    operator!=(const fpos<_StateT>& __lhs, const fpos<_StateT>& __rhs)
    { return streamoff(__lhs) != streamoff(__rhs); }

  
  
  
  
  typedef fpos<mbstate_t> streampos;
  
  typedef fpos<mbstate_t> wstreampos;



} 


namespace std __attribute__ ((__visibility__ ("default")))
{


  


























 
  class ios_base;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ios;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_streambuf;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_istream;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ostream;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_iostream;

  template<typename _CharT, typename _Traits = char_traits<_CharT>,
	    typename _Alloc = allocator<_CharT> >
    class basic_stringbuf;

  template<typename _CharT, typename _Traits = char_traits<_CharT>,
	   typename _Alloc = allocator<_CharT> >
    class basic_istringstream;

  template<typename _CharT, typename _Traits = char_traits<_CharT>,
	   typename _Alloc = allocator<_CharT> >
    class basic_ostringstream;

  template<typename _CharT, typename _Traits = char_traits<_CharT>,
	   typename _Alloc = allocator<_CharT> >
    class basic_stringstream;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_filebuf;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ifstream;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ofstream;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_fstream;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class istreambuf_iterator;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class ostreambuf_iterator;


  
  typedef basic_ios<char> 		ios; 

  
  typedef basic_streambuf<char> 	streambuf;

  
  typedef basic_istream<char> 		istream;

  
  typedef basic_ostream<char> 		ostream;

  
  typedef basic_iostream<char> 		iostream;

  
  typedef basic_stringbuf<char> 	stringbuf;

  
  typedef basic_istringstream<char> 	istringstream;

  
  typedef basic_ostringstream<char> 	ostringstream;

  
  typedef basic_stringstream<char> 	stringstream;

  
  typedef basic_filebuf<char> 		filebuf;

  
  typedef basic_ifstream<char> 		ifstream;

  
  typedef basic_ofstream<char> 		ofstream;

  
  typedef basic_fstream<char> 		fstream;

  
  typedef basic_ios<wchar_t> 		wios;

  
  typedef basic_streambuf<wchar_t> 	wstreambuf;

  
  typedef basic_istream<wchar_t> 	wistream;

  
  typedef basic_ostream<wchar_t> 	wostream;

  
  typedef basic_iostream<wchar_t> 	wiostream;

  
  typedef basic_stringbuf<wchar_t> 	wstringbuf;

  
  typedef basic_istringstream<wchar_t> 	wistringstream;

  
  typedef basic_ostringstream<wchar_t> 	wostringstream;

  
  typedef basic_stringstream<wchar_t> 	wstringstream;

  
  typedef basic_filebuf<wchar_t> 	wfilebuf;

  
  typedef basic_ifstream<wchar_t> 	wifstream;

  
  typedef basic_ofstream<wchar_t> 	wofstream;

  
  typedef basic_fstream<wchar_t> 	wfstream;
   


} 






























 









































 























 




 



 


namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{


  








 
  template<typename _CharT>
    struct _Char_types
    {
      typedef unsigned long   int_type;
      typedef std::streampos  pos_type;
      typedef std::streamoff  off_type;
      typedef std::mbstate_t  state_type;
    };


  













 
  template<typename _CharT>
    struct char_traits
    {
      typedef _CharT                                    char_type;
      typedef typename _Char_types<_CharT>::int_type    int_type;
      typedef typename _Char_types<_CharT>::pos_type    pos_type;
      typedef typename _Char_types<_CharT>::off_type    off_type;
      typedef typename _Char_types<_CharT>::state_type  state_type;

      static void
      assign(char_type& __c1, const char_type& __c2)
      { __c1 = __c2; }

      static  bool
      eq(const char_type& __c1, const char_type& __c2)
      { return __c1 == __c2; }

      static  bool
      lt(const char_type& __c1, const char_type& __c2)
      { return __c1 < __c2; }

      static int
      compare(const char_type* __s1, const char_type* __s2, std::size_t __n);

      static std::size_t
      length(const char_type* __s);

      static const char_type*
      find(const char_type* __s, std::size_t __n, const char_type& __a);

      static char_type*
      move(char_type* __s1, const char_type* __s2, std::size_t __n);

      static char_type*
      copy(char_type* __s1, const char_type* __s2, std::size_t __n);

      static char_type*
      assign(char_type* __s, std::size_t __n, char_type __a);

      static  char_type
      to_char_type(const int_type& __c)
      { return static_cast<char_type>(__c); }

      static  int_type
      to_int_type(const char_type& __c)
      { return static_cast<int_type>(__c); }

      static  bool
      eq_int_type(const int_type& __c1, const int_type& __c2)
      { return __c1 == __c2; }

      static  int_type
      eof()
      { return static_cast<int_type>(-1); }

      static  int_type
      not_eof(const int_type& __c)
      { return !eq_int_type(__c, eof()) ? __c : to_int_type(char_type()); }
    };

  template<typename _CharT>
    int
    char_traits<_CharT>::
    compare(const char_type* __s1, const char_type* __s2, std::size_t __n)
    {
      for (std::size_t __i = 0; __i < __n; ++__i)
	if (lt(__s1[__i], __s2[__i]))
	  return -1;
	else if (lt(__s2[__i], __s1[__i]))
	  return 1;
      return 0;
    }

  template<typename _CharT>
    std::size_t
    char_traits<_CharT>::
    length(const char_type* __p)
    {
      std::size_t __i = 0;
      while (!eq(__p[__i], char_type()))
        ++__i;
      return __i;
    }

  template<typename _CharT>
    const typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    find(const char_type* __s, std::size_t __n, const char_type& __a)
    {
      for (std::size_t __i = 0; __i < __n; ++__i)
        if (eq(__s[__i], __a))
          return __s + __i;
      return 0;
    }

  template<typename _CharT>
    typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    move(char_type* __s1, const char_type* __s2, std::size_t __n)
    {
      return static_cast<_CharT*>(__builtin_memmove(__s1, __s2,
						    __n * sizeof(char_type)));
    }

  template<typename _CharT>
    typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    copy(char_type* __s1, const char_type* __s2, std::size_t __n)
    {
      
      std::copy(__s2, __s2 + __n, __s1);
      return __s1;
    }

  template<typename _CharT>
    typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    assign(char_type* __s, std::size_t __n, char_type __a)
    {
      
      std::fill_n(__s, __n, __a);
      return __s;
    }


} 

namespace std __attribute__ ((__visibility__ ("default")))
{


  
  










 
  template<class _CharT>
    struct char_traits : public __gnu_cxx::char_traits<_CharT>
    { };


  
  template<>
    struct char_traits<char>
    {
      typedef char              char_type;
      typedef int               int_type;
      typedef streampos         pos_type;
      typedef streamoff         off_type;
      typedef mbstate_t         state_type;

      static void
      assign(char_type& __c1, const char_type& __c2)
      { __c1 = __c2; }

      static  bool
      eq(const char_type& __c1, const char_type& __c2)
      { return __c1 == __c2; }

      static  bool
      lt(const char_type& __c1, const char_type& __c2)
      { return __c1 < __c2; }

      static int
      compare(const char_type* __s1, const char_type* __s2, size_t __n)
      { return __builtin_memcmp(__s1, __s2, __n); }

      static size_t
      length(const char_type* __s)
      { return __builtin_strlen(__s); }

      static const char_type*
      find(const char_type* __s, size_t __n, const char_type& __a)
      { return static_cast<const char_type*>(__builtin_memchr(__s, __a, __n)); }

      static char_type*
      move(char_type* __s1, const char_type* __s2, size_t __n)
      { return static_cast<char_type*>(__builtin_memmove(__s1, __s2, __n)); }

      static char_type*
      copy(char_type* __s1, const char_type* __s2, size_t __n)
      { return static_cast<char_type*>(__builtin_memcpy(__s1, __s2, __n)); }

      static char_type*
      assign(char_type* __s, size_t __n, char_type __a)
      { return static_cast<char_type*>(__builtin_memset(__s, __a, __n)); }

      static  char_type
      to_char_type(const int_type& __c)
      { return static_cast<char_type>(__c); }

      
      
      static  int_type
      to_int_type(const char_type& __c)
      { return static_cast<int_type>(static_cast<unsigned char>(__c)); }

      static  bool
      eq_int_type(const int_type& __c1, const int_type& __c2)
      { return __c1 == __c2; }

      static  int_type
      eof()
      { return static_cast<int_type>(-1); }

      static  int_type
      not_eof(const int_type& __c)
      { return (__c == eof()) ? 0 : __c; }
  };


  
  template<>
    struct char_traits<wchar_t>
    {
      typedef wchar_t           char_type;
      typedef wint_t            int_type;
      typedef streamoff         off_type;
      typedef wstreampos        pos_type;
      typedef mbstate_t         state_type;

      static void
      assign(char_type& __c1, const char_type& __c2)
      { __c1 = __c2; }

      static  bool
      eq(const char_type& __c1, const char_type& __c2)
      { return __c1 == __c2; }

      static  bool
      lt(const char_type& __c1, const char_type& __c2)
      { return __c1 < __c2; }

      static int
      compare(const char_type* __s1, const char_type* __s2, size_t __n)
      { return wmemcmp(__s1, __s2, __n); }

      static size_t
      length(const char_type* __s)
      { return wcslen(__s); }

      static const char_type*
      find(const char_type* __s, size_t __n, const char_type& __a)
      { return wmemchr(__s, __a, __n); }

      static char_type*
      move(char_type* __s1, const char_type* __s2, size_t __n)
      { return wmemmove(__s1, __s2, __n); }

      static char_type*
      copy(char_type* __s1, const char_type* __s2, size_t __n)
      { return wmemcpy(__s1, __s2, __n); }

      static char_type*
      assign(char_type* __s, size_t __n, char_type __a)
      { return wmemset(__s, __a, __n); }

      static  char_type
      to_char_type(const int_type& __c)
      { return char_type(__c); }

      static  int_type
      to_int_type(const char_type& __c)
      { return int_type(__c); }

      static  bool
      eq_int_type(const int_type& __c1, const int_type& __c2)
      { return __c1 == __c2; }

      static  int_type
      eof()
      { return static_cast<int_type>((0xffffffffu)); }

      static  int_type
      not_eof(const int_type& __c)
      { return eq_int_type(__c, eof()) ? 0 : __c; }
  };


} 































 



































 











































 






















 



 


































 



 







 

















 



enum
{
  __LC_CTYPE = 0,
  __LC_NUMERIC = 1,
  __LC_TIME = 2,
  __LC_COLLATE = 3,
  __LC_MONETARY = 4,
  __LC_MESSAGES = 5,
  __LC_ALL = 6,
  __LC_PAPER = 7,
  __LC_NAME = 8,
  __LC_ADDRESS = 9,
  __LC_TELEPHONE = 10,
  __LC_MEASUREMENT = 11,
  __LC_IDENTIFICATION = 12
};


extern "C" {


 




 
struct lconv
{
   

  char *decimal_point;		 
  char *thousands_sep;		 
  



 
  char *grouping;

   

  
 
  char *int_curr_symbol;
  char *currency_symbol;	 
  char *mon_decimal_point;	 
  char *mon_thousands_sep;	 
  char *mon_grouping;		 
  char *positive_sign;		 
  char *negative_sign;		 
  char int_frac_digits;		 
  char frac_digits;		 
   
  char p_cs_precedes;
   
  char p_sep_by_space;
   
  char n_cs_precedes;
   
  char n_sep_by_space;
  




 
  char p_sign_posn;
  char n_sign_posn;
   
  char int_p_cs_precedes;
   
  char int_p_sep_by_space;
   
  char int_n_cs_precedes;
   
  char int_n_sep_by_space;
  




 
  char int_p_sign_posn;
  char int_n_sign_posn;
};


 
extern char *setlocale (int __category, __const char *__locale) throw ();

 
extern struct lconv *localeconv (void) throw ();













 

 




 
extern __locale_t newlocale (int __category_mask, __const char *__locale,
			     __locale_t __base) throw ();




 


 
extern __locale_t duplocale (__locale_t __dataset) throw ();


 
extern void freelocale (__locale_t __dataset) throw ();





 
extern __locale_t uselocale (__locale_t __dataset) throw ();


 


}





namespace std
{
  using ::lconv;
  using ::setlocale;
  using ::localeconv;
} 




namespace std __attribute__ ((__visibility__ ("default")))
{


  typedef int*			__c_locale;

  
  
  
  
  inline int
  __convert_from_v(const __c_locale&, char* __out, 
		   const int __size __attribute__((__unused__)),
		   const char* __fmt, ...)
  {
    char* __old = std::setlocale(__LC_NUMERIC, 0);
    char* __sav = 0;
    if (__builtin_strcmp(__old, "C"))
      {
	const size_t __len = __builtin_strlen(__old) + 1;
	__sav = new char[__len];
	__builtin_memcpy(__sav, __old, __len);
	std::setlocale(__LC_NUMERIC, "C");
      }

    __builtin_va_list __args;
    __builtin_va_start(__args, __fmt);

    const int __ret = __builtin_vsnprintf(__out, __size, __fmt, __args);

    __builtin_va_end(__args);

    if (__sav)
      {
	std::setlocale(__LC_NUMERIC, __sav);
	delete [] __sav;
      }
    return __ret;
  }


} 



































 























 



 



















 



 


 


 
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;

 
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;

 
typedef long int __quad_t;
typedef unsigned long int __u_quad_t;





























 

 

















 




 


 




typedef unsigned long int __dev_t;	 
typedef unsigned int __uid_t;	 
typedef unsigned int __gid_t;	 
typedef unsigned long int __ino_t;	 
typedef unsigned long int __ino64_t;	 
typedef unsigned int __mode_t;	 
typedef unsigned long int __nlink_t;	 
typedef long int __off_t;	 
typedef long int __off64_t;	 
typedef int __pid_t;	 
typedef struct { int __val[2]; } __fsid_t;	 
typedef long int __clock_t;	 
typedef unsigned long int __rlim_t;	 
typedef unsigned long int __rlim64_t;	 
typedef unsigned int __id_t;		 
typedef long int __time_t;	 
typedef unsigned int __useconds_t;  
typedef long int __suseconds_t;  

typedef int __daddr_t;	 
typedef long int __swblk_t;	 
typedef int __key_t;	 

 
typedef int __clockid_t;

 
typedef void * __timer_t;

 
typedef long int __blksize_t;

 

 
typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;

 
typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;

 
typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;

typedef long int __ssize_t;  


 
typedef __off64_t __loff_t;	 
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;

 
typedef long int __intptr_t;

 
typedef unsigned int __socklen_t;




extern "C" {







 

















 









 


 
 




 




 


















 



 


 



 


 


 







enum
{
  _ISupper = ((0) < 8 ? ((1 << (0)) << 8) : ((1 << (0)) >> 8)),	 
  _ISlower = ((1) < 8 ? ((1 << (1)) << 8) : ((1 << (1)) >> 8)),	 
  _ISalpha = ((2) < 8 ? ((1 << (2)) << 8) : ((1 << (2)) >> 8)),	 
  _ISdigit = ((3) < 8 ? ((1 << (3)) << 8) : ((1 << (3)) >> 8)),	 
  _ISxdigit = ((4) < 8 ? ((1 << (4)) << 8) : ((1 << (4)) >> 8)),	 
  _ISspace = ((5) < 8 ? ((1 << (5)) << 8) : ((1 << (5)) >> 8)),	 
  _ISprint = ((6) < 8 ? ((1 << (6)) << 8) : ((1 << (6)) >> 8)),	 
  _ISgraph = ((7) < 8 ? ((1 << (7)) << 8) : ((1 << (7)) >> 8)),	 
  _ISblank = ((8) < 8 ? ((1 << (8)) << 8) : ((1 << (8)) >> 8)),	 
  _IScntrl = ((9) < 8 ? ((1 << (9)) << 8) : ((1 << (9)) >> 8)),	 
  _ISpunct = ((10) < 8 ? ((1 << (10)) << 8) : ((1 << (10)) >> 8)),	 
  _ISalnum = ((11) < 8 ? ((1 << (11)) << 8) : ((1 << (11)) >> 8))	 
};
















 
extern __const unsigned short int **__ctype_b_loc (void)
     throw () __attribute__ ((__const));
extern __const __int32_t **__ctype_tolower_loc (void)
     throw () __attribute__ ((__const));
extern __const __int32_t **__ctype_toupper_loc (void)
     throw () __attribute__ ((__const));









 
extern int isalnum (int) throw ();
extern int isalpha (int) throw ();
extern int iscntrl (int) throw ();
extern int isdigit (int) throw ();
extern int islower (int) throw ();
extern int isgraph (int) throw ();
extern int isprint (int) throw ();
extern int ispunct (int) throw ();
extern int isspace (int) throw ();
extern int isupper (int) throw ();
extern int isxdigit (int) throw ();


 
extern int tolower (int __c) throw ();

 
extern int toupper (int __c) throw ();




 


extern int isblank (int) throw ();



 
extern int isctype (int __c, int __mask) throw ();



 
extern int isascii (int __c) throw ();


 
extern int toascii (int __c) throw ();


 
extern int _toupper (int) throw ();
extern int _tolower (int) throw ();

 












 


 


 





 
extern int isalnum_l (int, __locale_t) throw ();
extern int isalpha_l (int, __locale_t) throw ();
extern int iscntrl_l (int, __locale_t) throw ();
extern int isdigit_l (int, __locale_t) throw ();
extern int islower_l (int, __locale_t) throw ();
extern int isgraph_l (int, __locale_t) throw ();
extern int isprint_l (int, __locale_t) throw ();
extern int ispunct_l (int, __locale_t) throw ();
extern int isspace_l (int, __locale_t) throw ();
extern int isupper_l (int, __locale_t) throw ();
extern int isxdigit_l (int, __locale_t) throw ();

extern int isblank_l (int, __locale_t) throw ();


 
extern int __tolower_l (int __c, __locale_t __l) throw ();
extern int tolower_l (int __c, __locale_t __l) throw ();

 
extern int __toupper_l (int __c, __locale_t __l) throw ();
extern int toupper_l (int __c, __locale_t __l) throw ();





}





namespace std
{
  using ::isalnum;
  using ::isalpha;
  using ::iscntrl;
  using ::isdigit;
  using ::isgraph;
  using ::islower;
  using ::isprint;
  using ::ispunct;
  using ::isspace;
  using ::isupper;
  using ::isxdigit;
  using ::tolower;
  using ::toupper;
} 



namespace std __attribute__ ((__visibility__ ("default")))
{


  



 

  
  class locale;

  template<typename _Facet>
    bool
    has_facet(const locale&) throw();

  template<typename _Facet>
    const _Facet&
    use_facet(const locale&);

  
  template<typename _CharT>
    bool
    isspace(_CharT, const locale&);

  template<typename _CharT>
    bool
    isprint(_CharT, const locale&);

  template<typename _CharT>
    bool
    iscntrl(_CharT, const locale&);

  template<typename _CharT>
    bool
    isupper(_CharT, const locale&);

  template<typename _CharT>
    bool
    islower(_CharT, const locale&);

  template<typename _CharT>
    bool
    isalpha(_CharT, const locale&);

  template<typename _CharT>
    bool
    isdigit(_CharT, const locale&);

  template<typename _CharT>
    bool
    ispunct(_CharT, const locale&);

  template<typename _CharT>
    bool
    isxdigit(_CharT, const locale&);

  template<typename _CharT>
    bool
    isalnum(_CharT, const locale&);

  template<typename _CharT>
    bool
    isgraph(_CharT, const locale&);

  template<typename _CharT>
    _CharT
    toupper(_CharT, const locale&);

  template<typename _CharT>
    _CharT
    tolower(_CharT, const locale&);

  
  class ctype_base;
  template<typename _CharT>
    class ctype;
  template<> class ctype<char>;
  template<> class ctype<wchar_t>;
  template<typename _CharT>
    class ctype_byname;
  

  class codecvt_base;
  template<typename _InternT, typename _ExternT, typename _StateT>
    class codecvt;
  template<> class codecvt<char, char, mbstate_t>;
  template<> class codecvt<wchar_t, char, mbstate_t>;
  template<typename _InternT, typename _ExternT, typename _StateT>
    class codecvt_byname;

  

  template<typename _CharT, typename _InIter = istreambuf_iterator<_CharT> >
    class num_get;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class num_put;

  template<typename _CharT> class numpunct;
  template<typename _CharT> class numpunct_byname;

  
  template<typename _CharT>
    class collate;
  template<typename _CharT> class
    collate_byname;

  
  class time_base;
  template<typename _CharT, typename _InIter =  istreambuf_iterator<_CharT> >
    class time_get;
  template<typename _CharT, typename _InIter =  istreambuf_iterator<_CharT> >
    class time_get_byname;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class time_put;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class time_put_byname;

  
  class money_base;

  template<typename _CharT, typename _InIter =  istreambuf_iterator<_CharT> >
    class money_get;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class money_put;

  template<typename _CharT, bool _Intl = false>
    class moneypunct;
  template<typename _CharT, bool _Intl = false>
    class moneypunct_byname;

  
  class messages_base;
  template<typename _CharT>
    class messages;
  template<typename _CharT>
    class messages_byname;


} 






























 


































 


 
 






















 


#pragma GCC visibility push(default)












































































































 

 
 
 






















 



 


 


















 



















 



 
































 



 







 

















 



 












 
struct timespec
  {
    __time_t tv_sec;		 
    long int tv_nsec;		 
  };





 



















 




 

 

 
struct sched_param
  {
    int __sched_priority;
  };

extern "C" {

 
extern int clone (int (*__fn) (void *__arg), void *__child_stack,
		  int __flags, void *__arg, ...) throw ();

 
extern int unshare (int __flags) throw ();

 
extern int sched_getcpu (void) throw ();

}


 
struct __sched_param
  {
    int __sched_priority;
  };


 

 
typedef unsigned long int __cpu_mask;

 

 
typedef struct
{
  __cpu_mask __bits[1024 / (8 * sizeof (__cpu_mask))];
} cpu_set_t;

 





extern "C" {

extern int __sched_cpucount (size_t __setsize, const cpu_set_t *__setp)
  throw ();
extern cpu_set_t *__sched_cpualloc (size_t __count) throw () ;
extern void __sched_cpufree (cpu_set_t *__set) throw ();

}

 


extern "C" {

 
extern int sched_setparam (__pid_t __pid, __const struct sched_param *__param)
     throw ();

 
extern int sched_getparam (__pid_t __pid, struct sched_param *__param) throw ();

 
extern int sched_setscheduler (__pid_t __pid, int __policy,
			       __const struct sched_param *__param) throw ();

 
extern int sched_getscheduler (__pid_t __pid) throw ();

 
extern int sched_yield (void) throw ();

 
extern int sched_get_priority_max (int __algorithm) throw ();

 
extern int sched_get_priority_min (int __algorithm) throw ();

 
extern int sched_rr_get_interval (__pid_t __pid, struct timespec *__t) throw ();


 






 
extern int sched_setaffinity (__pid_t __pid, size_t __cpusetsize,
			      __const cpu_set_t *__cpuset) throw ();

 
extern int sched_getaffinity (__pid_t __pid, size_t __cpusetsize,
			      cpu_set_t *__cpuset) throw ();

}

















 



 



extern "C" {


 































 



 







 


 

















 



 




 


 


 
 
 
 

 



 





 
typedef __clock_t clock_t;







 
typedef __time_t time_t;






 
typedef __clockid_t clockid_t;




 
typedef __timer_t timer_t;






 
struct tm
{
  int tm_sec;			 
  int tm_min;			 
  int tm_hour;			 
  int tm_mday;			 
  int tm_mon;			 
  int tm_year;			 
  int tm_wday;			 
  int tm_yday;			 
  int tm_isdst;			 

  long int tm_gmtoff;		 
  __const char *tm_zone;	 
};




 
struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  };

 
struct sigevent;


typedef __pid_t pid_t;




 
extern clock_t clock (void) throw ();

 
extern time_t time (time_t *__timer) throw ();

 
extern double difftime (time_t __time1, time_t __time0)
     throw () __attribute__ ((__const__));

 
extern time_t mktime (struct tm *__tp) throw ();




 
extern size_t strftime (char *__restrict __s, size_t __maxsize,
			__const char *__restrict __format,
			__const struct tm *__restrict __tp) throw ();



 
extern char *strptime (__const char *__restrict __s,
		       __const char *__restrict __fmt, struct tm *__tp)
     throw ();


 

extern size_t strftime_l (char *__restrict __s, size_t __maxsize,
			  __const char *__restrict __format,
			  __const struct tm *__restrict __tp,
			  __locale_t __loc) throw ();

extern char *strptime_l (__const char *__restrict __s,
			 __const char *__restrict __fmt, struct tm *__tp,
			 __locale_t __loc) throw ();




 
extern struct tm *gmtime (__const time_t *__timer) throw ();


 
extern struct tm *localtime (__const time_t *__timer) throw ();



 
extern struct tm *gmtime_r (__const time_t *__restrict __timer,
			    struct tm *__restrict __tp) throw ();


 
extern struct tm *localtime_r (__const time_t *__restrict __timer,
			       struct tm *__restrict __tp) throw ();



 
extern char *asctime (__const struct tm *__tp) throw ();

 
extern char *ctime (__const time_t *__timer) throw ();


 


 
extern char *asctime_r (__const struct tm *__restrict __tp,
			char *__restrict __buf) throw ();

 
extern char *ctime_r (__const time_t *__restrict __timer,
		      char *__restrict __buf) throw ();


 
extern char *__tzname[2];	 
extern int __daylight;		 
extern long int __timezone;	 


 
extern char *tzname[2];


 
extern void tzset (void) throw ();

extern int daylight;
extern long int timezone;


 
extern int stime (__const time_t *__when) throw ();



 



 

 
extern time_t timegm (struct tm *__tp) throw ();

 
extern time_t timelocal (struct tm *__tp) throw ();

 
extern int dysize (int __year) throw ()  __attribute__ ((__const__));





 
extern int nanosleep (__const struct timespec *__requested_time,
		      struct timespec *__remaining);


 
extern int clock_getres (clockid_t __clock_id, struct timespec *__res) throw ();

 
extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) throw ();

 
extern int clock_settime (clockid_t __clock_id, __const struct timespec *__tp)
     throw ();




 
extern int clock_nanosleep (clockid_t __clock_id, int __flags,
			    __const struct timespec *__req,
			    struct timespec *__rem);

 
extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) throw ();


 
extern int timer_create (clockid_t __clock_id,
			 struct sigevent *__restrict __evp,
			 timer_t *__restrict __timerid) throw ();

 
extern int timer_delete (timer_t __timerid) throw ();

 
extern int timer_settime (timer_t __timerid, int __flags,
			  __const struct itimerspec *__restrict __value,
			  struct itimerspec *__restrict __ovalue) throw ();

 
extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     throw ();

 
extern int timer_getoverrun (timer_t __timerid) throw ();












 
extern int getdate_err;







 
extern struct tm *getdate (__const char *__string);










 
extern int getdate_r (__const char *__restrict __string,
		      struct tm *__restrict __resbufp);

}



















 



 




extern "C" {



















 


typedef int __sig_atomic_t;

 

typedef struct
  {
    unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
  } __sigset_t;







 



 

typedef __sigset_t sigset_t;


}


















 


 





 
typedef unsigned long int pthread_t;


typedef union
{
  char __size[56];
  long int __align;
} pthread_attr_t;


typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;



 
typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;
    unsigned int __nusers;
    
 
    int __kind;
    int __spins;
    __pthread_list_t __list;
  } __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;



 
typedef union
{
  struct
  {
    int __lock;
    unsigned int __futex;
    __extension__ unsigned long long int __total_seq;
    __extension__ unsigned long long int __wakeup_seq;
    __extension__ unsigned long long int __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;


 
typedef unsigned int pthread_key_t;


 
typedef int pthread_once_t;



 
typedef union
{
  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    int __writer;
    int __shared;
    unsigned long int __pad1;
    unsigned long int __pad2;
    
 
    unsigned int __flags;
  } __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;


 
typedef volatile int pthread_spinlock_t;



 
typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;



















 

 


 



typedef long int __jmp_buf[8];


 



 
enum
{
  PTHREAD_CREATE_JOINABLE,
  PTHREAD_CREATE_DETACHED
};


 
enum
{
  PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_ADAPTIVE_NP
  ,
  PTHREAD_MUTEX_NORMAL = PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE = PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL
   
  , PTHREAD_MUTEX_FAST_NP = PTHREAD_MUTEX_TIMED_NP
};


 
enum
{
  PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_STALLED_NP = PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_ROBUST,
  PTHREAD_MUTEX_ROBUST_NP = PTHREAD_MUTEX_ROBUST
};


 
enum
{
  PTHREAD_PRIO_NONE,
  PTHREAD_PRIO_INHERIT,
  PTHREAD_PRIO_PROTECT
};


 


 
enum
{
  PTHREAD_RWLOCK_PREFER_READER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP,
  PTHREAD_RWLOCK_DEFAULT_NP = PTHREAD_RWLOCK_PREFER_READER_NP
};

 


 
enum
{
  PTHREAD_INHERIT_SCHED,
  PTHREAD_EXPLICIT_SCHED
};


 
enum
{
  PTHREAD_SCOPE_SYSTEM,
  PTHREAD_SCOPE_PROCESS
};


 
enum
{
  PTHREAD_PROCESS_PRIVATE,
  PTHREAD_PROCESS_SHARED
};



 


 
struct _pthread_cleanup_buffer
{
  void (*__routine) (void *);              
  void *__arg;                             
  int __canceltype;                        
  struct _pthread_cleanup_buffer *__prev;  
};

 
enum
{
  PTHREAD_CANCEL_ENABLE,
  PTHREAD_CANCEL_DISABLE
};
enum
{
  PTHREAD_CANCEL_DEFERRED,
  PTHREAD_CANCEL_ASYNCHRONOUS
};


 




 


extern "C" {



 
extern int pthread_create (pthread_t *__restrict __newthread,
			   __const pthread_attr_t *__restrict __attr,
			   void *(*__start_routine) (void *),
			   void *__restrict __arg) throw () __attribute__ ((__nonnull__ (1, 3)));




 
extern void pthread_exit (void *__retval) __attribute__ ((__noreturn__));






 
extern int pthread_join (pthread_t __th, void **__thread_return);


 
extern int pthread_tryjoin_np (pthread_t __th, void **__thread_return) throw ();






 
extern int pthread_timedjoin_np (pthread_t __th, void **__thread_return,
				 __const struct timespec *__abstime);




 
extern int pthread_detach (pthread_t __th) throw ();


 
extern pthread_t pthread_self (void) throw () __attribute__ ((__const__));

 
extern int pthread_equal (pthread_t __thread1, pthread_t __thread2) throw ();


 



 
extern int pthread_attr_init (pthread_attr_t *__attr) throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_attr_destroy (pthread_attr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_attr_getdetachstate (__const pthread_attr_t *__attr,
					int *__detachstate)
     throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int pthread_attr_setdetachstate (pthread_attr_t *__attr,
					int __detachstate)
     throw () __attribute__ ((__nonnull__ (1)));


 
extern int pthread_attr_getguardsize (__const pthread_attr_t *__attr,
				      size_t *__guardsize)
     throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int pthread_attr_setguardsize (pthread_attr_t *__attr,
				      size_t __guardsize)
     throw () __attribute__ ((__nonnull__ (1)));


 
extern int pthread_attr_getschedparam (__const pthread_attr_t *__restrict
				       __attr,
				       struct sched_param *__restrict __param)
     throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int pthread_attr_setschedparam (pthread_attr_t *__restrict __attr,
				       __const struct sched_param *__restrict
				       __param) throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int pthread_attr_getschedpolicy (__const pthread_attr_t *__restrict
					__attr, int *__restrict __policy)
     throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int pthread_attr_setschedpolicy (pthread_attr_t *__attr, int __policy)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_attr_getinheritsched (__const pthread_attr_t *__restrict
					 __attr, int *__restrict __inherit)
     throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int pthread_attr_setinheritsched (pthread_attr_t *__attr,
					 int __inherit)
     throw () __attribute__ ((__nonnull__ (1)));


 
extern int pthread_attr_getscope (__const pthread_attr_t *__restrict __attr,
				  int *__restrict __scope)
     throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int pthread_attr_setscope (pthread_attr_t *__attr, int __scope)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_attr_getstackaddr (__const pthread_attr_t *__restrict
				      __attr, void **__restrict __stackaddr)
     throw () __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__deprecated__));




 
extern int pthread_attr_setstackaddr (pthread_attr_t *__attr,
				      void *__stackaddr)
     throw () __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__));

 
extern int pthread_attr_getstacksize (__const pthread_attr_t *__restrict
				      __attr, size_t *__restrict __stacksize)
     throw () __attribute__ ((__nonnull__ (1, 2)));



 
extern int pthread_attr_setstacksize (pthread_attr_t *__attr,
				      size_t __stacksize)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_attr_getstack (__const pthread_attr_t *__restrict __attr,
				  void **__restrict __stackaddr,
				  size_t *__restrict __stacksize)
     throw () __attribute__ ((__nonnull__ (1, 2, 3)));



 
extern int pthread_attr_setstack (pthread_attr_t *__attr, void *__stackaddr,
				  size_t __stacksize) throw () __attribute__ ((__nonnull__ (1)));


 
extern int pthread_attr_setaffinity_np (pthread_attr_t *__attr,
					size_t __cpusetsize,
					__const cpu_set_t *__cpuset)
     throw () __attribute__ ((__nonnull__ (1, 3)));


 
extern int pthread_attr_getaffinity_np (__const pthread_attr_t *__attr,
					size_t __cpusetsize,
					cpu_set_t *__cpuset)
     throw () __attribute__ ((__nonnull__ (1, 3)));




 
extern int pthread_getattr_np (pthread_t __th, pthread_attr_t *__attr)
     throw () __attribute__ ((__nonnull__ (2)));


 


 
extern int pthread_setschedparam (pthread_t __target_thread, int __policy,
				  __const struct sched_param *__param)
     throw () __attribute__ ((__nonnull__ (3)));

 
extern int pthread_getschedparam (pthread_t __target_thread,
				  int *__restrict __policy,
				  struct sched_param *__restrict __param)
     throw () __attribute__ ((__nonnull__ (2, 3)));

 
extern int pthread_setschedprio (pthread_t __target_thread, int __prio)
     throw ();


 
extern int pthread_getconcurrency (void) throw ();

 
extern int pthread_setconcurrency (int __level) throw ();




 
extern int pthread_yield (void) throw ();



 
extern int pthread_setaffinity_np (pthread_t __th, size_t __cpusetsize,
				   __const cpu_set_t *__cpuset)
     throw () __attribute__ ((__nonnull__ (3)));

 
extern int pthread_getaffinity_np (pthread_t __th, size_t __cpusetsize,
				   cpu_set_t *__cpuset)
     throw () __attribute__ ((__nonnull__ (3)));


 







 
extern int pthread_once (pthread_once_t *__once_control,
			 void (*__init_routine) (void)) __attribute__ ((__nonnull__ (1, 2)));






 


 
extern int pthread_setcancelstate (int __state, int *__oldstate);


 
extern int pthread_setcanceltype (int __type, int *__oldtype);

 
extern int pthread_cancel (pthread_t __th);



 
extern void pthread_testcancel (void);


 

typedef struct
{
  struct
  {
    __jmp_buf __cancel_jmp_buf;
    int __mask_was_saved;
  } __cancel_jmp_buf[1];
  void *__pad[4];
} __pthread_unwind_buf_t __attribute__ ((__aligned__));

 


 
struct __pthread_cleanup_frame
{
  void (*__cancel_routine) (void *);
  void *__cancel_arg;
  int __do_it;
  int __cancel_type;
};

 
class __pthread_cleanup_class
{
  void (*__cancel_routine) (void *);
  void *__cancel_arg;
  int __do_it;
  int __cancel_type;

 public:
  __pthread_cleanup_class (void (*__fct) (void *), void *__arg)
    : __cancel_routine (__fct), __cancel_arg (__arg), __do_it (1) { }
  ~__pthread_cleanup_class () { if (__do_it) __cancel_routine (__cancel_arg); }
  void __setdoit (int __newval) { __do_it = __newval; }
  void __defer () { pthread_setcanceltype (PTHREAD_CANCEL_DEFERRED,
					   &__cancel_type); }
  void __restore () const { pthread_setcanceltype (__cancel_type, 0); }
};







 


 



 



 

 
struct __jmp_buf_tag;
extern int __sigsetjmp (struct __jmp_buf_tag *__env, int __savemask) throw ();


 

 
extern int pthread_mutex_init (pthread_mutex_t *__mutex,
			       __const pthread_mutexattr_t *__mutexattr)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_mutex_destroy (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_mutex_trylock (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_mutex_lock (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_mutex_timedlock (pthread_mutex_t *__restrict __mutex,
                                    __const struct timespec *__restrict
                                    __abstime) throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int pthread_mutex_unlock (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));


 
extern int pthread_mutex_getprioceiling (__const pthread_mutex_t *
					 __restrict __mutex,
					 int *__restrict __prioceiling)
     throw () __attribute__ ((__nonnull__ (1, 2)));


 
extern int pthread_mutex_setprioceiling (pthread_mutex_t *__restrict __mutex,
					 int __prioceiling,
					 int *__restrict __old_ceiling)
     throw () __attribute__ ((__nonnull__ (1, 3)));


 
extern int pthread_mutex_consistent_np (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_mutex_consistent_np (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));


 


 
extern int pthread_mutexattr_init (pthread_mutexattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_mutexattr_destroy (pthread_mutexattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_mutexattr_getpshared (__const pthread_mutexattr_t *
					 __restrict __attr,
					 int *__restrict __pshared)
     throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int pthread_mutexattr_setpshared (pthread_mutexattr_t *__attr,
					 int __pshared)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_mutexattr_gettype (__const pthread_mutexattr_t *__restrict
				      __attr, int *__restrict __kind)
     throw () __attribute__ ((__nonnull__ (1, 2)));



 
extern int pthread_mutexattr_settype (pthread_mutexattr_t *__attr, int __kind)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_mutexattr_getprotocol (__const pthread_mutexattr_t *
					  __restrict __attr,
					  int *__restrict __protocol)
     throw () __attribute__ ((__nonnull__ (1, 2)));


 
extern int pthread_mutexattr_setprotocol (pthread_mutexattr_t *__attr,
					  int __protocol)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_mutexattr_getprioceiling (__const pthread_mutexattr_t *
					     __restrict __attr,
					     int *__restrict __prioceiling)
     throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int pthread_mutexattr_setprioceiling (pthread_mutexattr_t *__attr,
					     int __prioceiling)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_mutexattr_getrobust (__const pthread_mutexattr_t *__attr,
					int *__robustness)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_mutexattr_getrobust_np (__const pthread_mutexattr_t *__attr,
					   int *__robustness)
     throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int pthread_mutexattr_setrobust (pthread_mutexattr_t *__attr,
					int __robustness)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_mutexattr_setrobust_np (pthread_mutexattr_t *__attr,
					   int __robustness)
     throw () __attribute__ ((__nonnull__ (1)));


 


 
extern int pthread_rwlock_init (pthread_rwlock_t *__restrict __rwlock,
				__const pthread_rwlockattr_t *__restrict
				__attr) throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_rwlock_destroy (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_rwlock_rdlock (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_rwlock_tryrdlock (pthread_rwlock_t *__rwlock)
  throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_rwlock_timedrdlock (pthread_rwlock_t *__restrict __rwlock,
				       __const struct timespec *__restrict
				       __abstime) throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int pthread_rwlock_wrlock (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_rwlock_trywrlock (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_rwlock_timedwrlock (pthread_rwlock_t *__restrict __rwlock,
				       __const struct timespec *__restrict
				       __abstime) throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int pthread_rwlock_unlock (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));


 

 
extern int pthread_rwlockattr_init (pthread_rwlockattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_rwlockattr_destroy (pthread_rwlockattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_rwlockattr_getpshared (__const pthread_rwlockattr_t *
					  __restrict __attr,
					  int *__restrict __pshared)
     throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int pthread_rwlockattr_setpshared (pthread_rwlockattr_t *__attr,
					  int __pshared)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_rwlockattr_getkind_np (__const pthread_rwlockattr_t *
					  __restrict __attr,
					  int *__restrict __pref)
     throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int pthread_rwlockattr_setkind_np (pthread_rwlockattr_t *__attr,
					  int __pref) throw () __attribute__ ((__nonnull__ (1)));


 


 
extern int pthread_cond_init (pthread_cond_t *__restrict __cond,
			      __const pthread_condattr_t *__restrict
			      __cond_attr) throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_cond_destroy (pthread_cond_t *__cond)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_cond_signal (pthread_cond_t *__cond)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_cond_broadcast (pthread_cond_t *__cond)
     throw () __attribute__ ((__nonnull__ (1)));





 
extern int pthread_cond_wait (pthread_cond_t *__restrict __cond,
			      pthread_mutex_t *__restrict __mutex)
     __attribute__ ((__nonnull__ (1, 2)));







 
extern int pthread_cond_timedwait (pthread_cond_t *__restrict __cond,
				   pthread_mutex_t *__restrict __mutex,
				   __const struct timespec *__restrict
				   __abstime) __attribute__ ((__nonnull__ (1, 2, 3)));

 

 
extern int pthread_condattr_init (pthread_condattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_condattr_destroy (pthread_condattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_condattr_getpshared (__const pthread_condattr_t *
                                        __restrict __attr,
                                        int *__restrict __pshared)
     throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int pthread_condattr_setpshared (pthread_condattr_t *__attr,
                                        int __pshared) throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_condattr_getclock (__const pthread_condattr_t *
				      __restrict __attr,
				      __clockid_t *__restrict __clock_id)
     throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int pthread_condattr_setclock (pthread_condattr_t *__attr,
				      __clockid_t __clock_id)
     throw () __attribute__ ((__nonnull__ (1)));


 


 
extern int pthread_spin_init (pthread_spinlock_t *__lock, int __pshared)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_spin_destroy (pthread_spinlock_t *__lock)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_spin_lock (pthread_spinlock_t *__lock)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_spin_trylock (pthread_spinlock_t *__lock)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_spin_unlock (pthread_spinlock_t *__lock)
     throw () __attribute__ ((__nonnull__ (1)));


 


 
extern int pthread_barrier_init (pthread_barrier_t *__restrict __barrier,
				 __const pthread_barrierattr_t *__restrict
				 __attr, unsigned int __count)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_barrier_destroy (pthread_barrier_t *__barrier)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_barrier_wait (pthread_barrier_t *__barrier)
     throw () __attribute__ ((__nonnull__ (1)));


 
extern int pthread_barrierattr_init (pthread_barrierattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_barrierattr_destroy (pthread_barrierattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_barrierattr_getpshared (__const pthread_barrierattr_t *
					   __restrict __attr,
					   int *__restrict __pshared)
     throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int pthread_barrierattr_setpshared (pthread_barrierattr_t *__attr,
                                           int __pshared)
     throw () __attribute__ ((__nonnull__ (1)));


 






 
extern int pthread_key_create (pthread_key_t *__key,
			       void (*__destr_function) (void *))
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int pthread_key_delete (pthread_key_t __key) throw ();

 
extern void *pthread_getspecific (pthread_key_t __key) throw ();

 
extern int pthread_setspecific (pthread_key_t __key,
				__const void *__pointer) throw () ;


 
extern int pthread_getcpuclockid (pthread_t __thread_id,
				  __clockid_t *__clock_id)
     throw () __attribute__ ((__nonnull__ (2)));











 

extern int pthread_atfork (void (*__prepare) (void),
			   void (*__parent) (void),
			   void (*__child) (void)) throw ();


 
extern __inline __attribute__ ((__gnu_inline__)) int
pthread_equal (pthread_t __thread1, pthread_t __thread2) throw ()
{
  return __thread1 == __thread2;
}

}

















 



 



extern "C" {


 

 


 

 


 


 


 


 

 

 

 

 

 


 

 




















































































 


















 


 

 

 

 

 

 

 

 

 

 


 

 

 

 

 

 

 

 

 

 

 

 


 

 

 

 

 
 
 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 


 
















 


 


















 










 


 

 



 


 


typedef __ssize_t ssize_t;
































 



 







 


 
typedef __gid_t gid_t;

typedef __uid_t uid_t;

typedef __off_t off_t;
typedef __off64_t off64_t;

typedef __useconds_t useconds_t;


typedef __intptr_t intptr_t;

typedef __socklen_t socklen_t;


 

 
extern int access (__const char *__name, int __type) throw () __attribute__ ((__nonnull__ (1)));


 
extern int euidaccess (__const char *__name, int __type)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern int eaccess (__const char *__name, int __type)
     throw () __attribute__ ((__nonnull__ (1)));



 
extern int faccessat (int __fd, __const char *__file, int __type, int __flag)
     throw () __attribute__ ((__nonnull__ (2))) ;


 

 






 
extern __off_t lseek (int __fd, __off_t __offset, int __whence) throw ();
extern __off64_t lseek64 (int __fd, __off64_t __offset, int __whence)
     throw ();




 
extern int close (int __fd);





 
extern ssize_t read (int __fd, void *__buf, size_t __nbytes) ;




 
extern ssize_t write (int __fd, __const void *__buf, size_t __n) ;






 
extern ssize_t pread (int __fd, void *__buf, size_t __nbytes,
		      __off_t __offset) ;





 
extern ssize_t pwrite (int __fd, __const void *__buf, size_t __n,
		       __off_t __offset) ;



 
extern ssize_t pread64 (int __fd, void *__buf, size_t __nbytes,
			__off64_t __offset) ;

 
extern ssize_t pwrite64 (int __fd, __const void *__buf, size_t __n,
			 __off64_t __offset) ;




 
extern int pipe (int __pipedes[2]) throw () ;


 
extern int pipe2 (int __pipedes[2], int __flags) throw () ;







 
extern unsigned int alarm (unsigned int __seconds) throw ();










 
extern unsigned int sleep (unsigned int __seconds);




 
extern __useconds_t ualarm (__useconds_t __value, __useconds_t __interval)
     throw ();





 
extern int usleep (__useconds_t __useconds);






 
extern int pause (void);


 
extern int chown (__const char *__file, __uid_t __owner, __gid_t __group)
     throw () __attribute__ ((__nonnull__ (1))) ;

 
extern int fchown (int __fd, __uid_t __owner, __gid_t __group) throw () ;



 
extern int lchown (__const char *__file, __uid_t __owner, __gid_t __group)
     throw () __attribute__ ((__nonnull__ (1))) ;



 
extern int fchownat (int __fd, __const char *__file, __uid_t __owner,
		     __gid_t __group, int __flag)
     throw () __attribute__ ((__nonnull__ (2))) ;

 
extern int chdir (__const char *__path) throw () __attribute__ ((__nonnull__ (1))) ;

 
extern int fchdir (int __fd) throw () ;







 
extern char *getcwd (char *__buf, size_t __size) throw () ;



 
extern char *get_current_dir_name (void) throw ();



 
extern char *getwd (char *__buf)
     throw () __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__)) ;


 
extern int dup (int __fd) throw () ;

 
extern int dup2 (int __fd, int __fd2) throw ();


 
extern int dup3 (int __fd, int __fd2, int __flags) throw ();

 
extern char **__environ;
extern char **environ;



 
extern int execve (__const char *__path, char *__const __argv[],
		   char *__const __envp[]) throw () __attribute__ ((__nonnull__ (1)));


 
extern int fexecve (int __fd, char *__const __argv[], char *__const __envp[])
     throw ();


 
extern int execv (__const char *__path, char *__const __argv[])
     throw () __attribute__ ((__nonnull__ (1)));


 
extern int execle (__const char *__path, __const char *__arg, ...)
     throw () __attribute__ ((__nonnull__ (1)));


 
extern int execl (__const char *__path, __const char *__arg, ...)
     throw () __attribute__ ((__nonnull__ (1)));


 
extern int execvp (__const char *__file, char *__const __argv[])
     throw () __attribute__ ((__nonnull__ (1)));



 
extern int execlp (__const char *__file, __const char *__arg, ...)
     throw () __attribute__ ((__nonnull__ (1)));


 
extern int nice (int __inc) throw () ;


 
extern void _exit (int __status) __attribute__ ((__noreturn__));




 


















 


 
enum
  {
    _PC_LINK_MAX,
    _PC_MAX_CANON,
    _PC_MAX_INPUT,
    _PC_NAME_MAX,
    _PC_PATH_MAX,
    _PC_PIPE_BUF,
    _PC_CHOWN_RESTRICTED,
    _PC_NO_TRUNC,
    _PC_VDISABLE,
    _PC_SYNC_IO,
    _PC_ASYNC_IO,
    _PC_PRIO_IO,
    _PC_SOCK_MAXBUF,
    _PC_FILESIZEBITS,
    _PC_REC_INCR_XFER_SIZE,
    _PC_REC_MAX_XFER_SIZE,
    _PC_REC_MIN_XFER_SIZE,
    _PC_REC_XFER_ALIGN,
    _PC_ALLOC_SIZE_MIN,
    _PC_SYMLINK_MAX,
    _PC_2_SYMLINKS
  };

 
enum
  {
    _SC_ARG_MAX,
    _SC_CHILD_MAX,
    _SC_CLK_TCK,
    _SC_NGROUPS_MAX,
    _SC_OPEN_MAX,
    _SC_STREAM_MAX,
    _SC_TZNAME_MAX,
    _SC_JOB_CONTROL,
    _SC_SAVED_IDS,
    _SC_REALTIME_SIGNALS,
    _SC_PRIORITY_SCHEDULING,
    _SC_TIMERS,
    _SC_ASYNCHRONOUS_IO,
    _SC_PRIORITIZED_IO,
    _SC_SYNCHRONIZED_IO,
    _SC_FSYNC,
    _SC_MAPPED_FILES,
    _SC_MEMLOCK,
    _SC_MEMLOCK_RANGE,
    _SC_MEMORY_PROTECTION,
    _SC_MESSAGE_PASSING,
    _SC_SEMAPHORES,
    _SC_SHARED_MEMORY_OBJECTS,
    _SC_AIO_LISTIO_MAX,
    _SC_AIO_MAX,
    _SC_AIO_PRIO_DELTA_MAX,
    _SC_DELAYTIMER_MAX,
    _SC_MQ_OPEN_MAX,
    _SC_MQ_PRIO_MAX,
    _SC_VERSION,
    _SC_PAGESIZE,
    _SC_RTSIG_MAX,
    _SC_SEM_NSEMS_MAX,
    _SC_SEM_VALUE_MAX,
    _SC_SIGQUEUE_MAX,
    _SC_TIMER_MAX,

    
 
    _SC_BC_BASE_MAX,
    _SC_BC_DIM_MAX,
    _SC_BC_SCALE_MAX,
    _SC_BC_STRING_MAX,
    _SC_COLL_WEIGHTS_MAX,
    _SC_EQUIV_CLASS_MAX,
    _SC_EXPR_NEST_MAX,
    _SC_LINE_MAX,
    _SC_RE_DUP_MAX,
    _SC_CHARCLASS_NAME_MAX,

    _SC_2_VERSION,
    _SC_2_C_BIND,
    _SC_2_C_DEV,
    _SC_2_FORT_DEV,
    _SC_2_FORT_RUN,
    _SC_2_SW_DEV,
    _SC_2_LOCALEDEF,

    _SC_PII,
    _SC_PII_XTI,
    _SC_PII_SOCKET,
    _SC_PII_INTERNET,
    _SC_PII_OSI,
    _SC_POLL,
    _SC_SELECT,
    _SC_UIO_MAXIOV,
    _SC_IOV_MAX = _SC_UIO_MAXIOV,
    _SC_PII_INTERNET_STREAM,
    _SC_PII_INTERNET_DGRAM,
    _SC_PII_OSI_COTS,
    _SC_PII_OSI_CLTS,
    _SC_PII_OSI_M,
    _SC_T_IOV_MAX,

     
    _SC_THREADS,
    _SC_THREAD_SAFE_FUNCTIONS,
    _SC_GETGR_R_SIZE_MAX,
    _SC_GETPW_R_SIZE_MAX,
    _SC_LOGIN_NAME_MAX,
    _SC_TTY_NAME_MAX,
    _SC_THREAD_DESTRUCTOR_ITERATIONS,
    _SC_THREAD_KEYS_MAX,
    _SC_THREAD_STACK_MIN,
    _SC_THREAD_THREADS_MAX,
    _SC_THREAD_ATTR_STACKADDR,
    _SC_THREAD_ATTR_STACKSIZE,
    _SC_THREAD_PRIORITY_SCHEDULING,
    _SC_THREAD_PRIO_INHERIT,
    _SC_THREAD_PRIO_PROTECT,
    _SC_THREAD_PROCESS_SHARED,

    _SC_NPROCESSORS_CONF,
    _SC_NPROCESSORS_ONLN,
    _SC_PHYS_PAGES,
    _SC_AVPHYS_PAGES,
    _SC_ATEXIT_MAX,
    _SC_PASS_MAX,

    _SC_XOPEN_VERSION,
    _SC_XOPEN_XCU_VERSION,
    _SC_XOPEN_UNIX,
    _SC_XOPEN_CRYPT,
    _SC_XOPEN_ENH_I18N,
    _SC_XOPEN_SHM,

    _SC_2_CHAR_TERM,
    _SC_2_C_VERSION,
    _SC_2_UPE,

    _SC_XOPEN_XPG2,
    _SC_XOPEN_XPG3,
    _SC_XOPEN_XPG4,

    _SC_CHAR_BIT,
    _SC_CHAR_MAX,
    _SC_CHAR_MIN,
    _SC_INT_MAX,
    _SC_INT_MIN,
    _SC_LONG_BIT,
    _SC_WORD_BIT,
    _SC_MB_LEN_MAX,
    _SC_NZERO,
    _SC_SSIZE_MAX,
    _SC_SCHAR_MAX,
    _SC_SCHAR_MIN,
    _SC_SHRT_MAX,
    _SC_SHRT_MIN,
    _SC_UCHAR_MAX,
    _SC_UINT_MAX,
    _SC_ULONG_MAX,
    _SC_USHRT_MAX,

    _SC_NL_ARGMAX,
    _SC_NL_LANGMAX,
    _SC_NL_MSGMAX,
    _SC_NL_NMAX,
    _SC_NL_SETMAX,
    _SC_NL_TEXTMAX,

    _SC_XBS5_ILP32_OFF32,
    _SC_XBS5_ILP32_OFFBIG,
    _SC_XBS5_LP64_OFF64,
    _SC_XBS5_LPBIG_OFFBIG,

    _SC_XOPEN_LEGACY,
    _SC_XOPEN_REALTIME,
    _SC_XOPEN_REALTIME_THREADS,

    _SC_ADVISORY_INFO,
    _SC_BARRIERS,
    _SC_BASE,
    _SC_C_LANG_SUPPORT,
    _SC_C_LANG_SUPPORT_R,
    _SC_CLOCK_SELECTION,
    _SC_CPUTIME,
    _SC_THREAD_CPUTIME,
    _SC_DEVICE_IO,
    _SC_DEVICE_SPECIFIC,
    _SC_DEVICE_SPECIFIC_R,
    _SC_FD_MGMT,
    _SC_FIFO,
    _SC_PIPE,
    _SC_FILE_ATTRIBUTES,
    _SC_FILE_LOCKING,
    _SC_FILE_SYSTEM,
    _SC_MONOTONIC_CLOCK,
    _SC_MULTI_PROCESS,
    _SC_SINGLE_PROCESS,
    _SC_NETWORKING,
    _SC_READER_WRITER_LOCKS,
    _SC_SPIN_LOCKS,
    _SC_REGEXP,
    _SC_REGEX_VERSION,
    _SC_SHELL,
    _SC_SIGNALS,
    _SC_SPAWN,
    _SC_SPORADIC_SERVER,
    _SC_THREAD_SPORADIC_SERVER,
    _SC_SYSTEM_DATABASE,
    _SC_SYSTEM_DATABASE_R,
    _SC_TIMEOUTS,
    _SC_TYPED_MEMORY_OBJECTS,
    _SC_USER_GROUPS,
    _SC_USER_GROUPS_R,
    _SC_2_PBS,
    _SC_2_PBS_ACCOUNTING,
    _SC_2_PBS_LOCATE,
    _SC_2_PBS_MESSAGE,
    _SC_2_PBS_TRACK,
    _SC_SYMLOOP_MAX,
    _SC_STREAMS,
    _SC_2_PBS_CHECKPOINT,

    _SC_V6_ILP32_OFF32,
    _SC_V6_ILP32_OFFBIG,
    _SC_V6_LP64_OFF64,
    _SC_V6_LPBIG_OFFBIG,

    _SC_HOST_NAME_MAX,
    _SC_TRACE,
    _SC_TRACE_EVENT_FILTER,
    _SC_TRACE_INHERIT,
    _SC_TRACE_LOG,

    _SC_LEVEL1_ICACHE_SIZE,
    _SC_LEVEL1_ICACHE_ASSOC,
    _SC_LEVEL1_ICACHE_LINESIZE,
    _SC_LEVEL1_DCACHE_SIZE,
    _SC_LEVEL1_DCACHE_ASSOC,
    _SC_LEVEL1_DCACHE_LINESIZE,
    _SC_LEVEL2_CACHE_SIZE,
    _SC_LEVEL2_CACHE_ASSOC,
    _SC_LEVEL2_CACHE_LINESIZE,
    _SC_LEVEL3_CACHE_SIZE,
    _SC_LEVEL3_CACHE_ASSOC,
    _SC_LEVEL3_CACHE_LINESIZE,
    _SC_LEVEL4_CACHE_SIZE,
    _SC_LEVEL4_CACHE_ASSOC,
    _SC_LEVEL4_CACHE_LINESIZE,
     

    _SC_IPV6 = _SC_LEVEL1_ICACHE_SIZE + 50,
    _SC_RAW_SOCKETS,

    _SC_V7_ILP32_OFF32,
    _SC_V7_ILP32_OFFBIG,
    _SC_V7_LP64_OFF64,
    _SC_V7_LPBIG_OFFBIG,

    _SC_SS_REPL_MAX,

    _SC_TRACE_EVENT_NAME_MAX,
    _SC_TRACE_NAME_MAX,
    _SC_TRACE_SYS_MAX,
    _SC_TRACE_USER_EVENT_MAX,

    _SC_XOPEN_STREAMS,

    _SC_THREAD_ROBUST_PRIO_INHERIT,
    _SC_THREAD_ROBUST_PRIO_PROTECT,
  };

 
enum
  {
    _CS_PATH,			 

    _CS_V6_WIDTH_RESTRICTED_ENVS,

    _CS_GNU_LIBC_VERSION,
    _CS_GNU_LIBPTHREAD_VERSION,

    _CS_V5_WIDTH_RESTRICTED_ENVS,

    _CS_V7_WIDTH_RESTRICTED_ENVS,

    _CS_LFS_CFLAGS = 1000,
    _CS_LFS_LDFLAGS,
    _CS_LFS_LIBS,
    _CS_LFS_LINTFLAGS,
    _CS_LFS64_CFLAGS,
    _CS_LFS64_LDFLAGS,
    _CS_LFS64_LIBS,
    _CS_LFS64_LINTFLAGS,

    _CS_XBS5_ILP32_OFF32_CFLAGS = 1100,
    _CS_XBS5_ILP32_OFF32_LDFLAGS,
    _CS_XBS5_ILP32_OFF32_LIBS,
    _CS_XBS5_ILP32_OFF32_LINTFLAGS,
    _CS_XBS5_ILP32_OFFBIG_CFLAGS,
    _CS_XBS5_ILP32_OFFBIG_LDFLAGS,
    _CS_XBS5_ILP32_OFFBIG_LIBS,
    _CS_XBS5_ILP32_OFFBIG_LINTFLAGS,
    _CS_XBS5_LP64_OFF64_CFLAGS,
    _CS_XBS5_LP64_OFF64_LDFLAGS,
    _CS_XBS5_LP64_OFF64_LIBS,
    _CS_XBS5_LP64_OFF64_LINTFLAGS,
    _CS_XBS5_LPBIG_OFFBIG_CFLAGS,
    _CS_XBS5_LPBIG_OFFBIG_LDFLAGS,
    _CS_XBS5_LPBIG_OFFBIG_LIBS,
    _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,

    _CS_POSIX_V6_ILP32_OFF32_CFLAGS,
    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS,
    _CS_POSIX_V6_ILP32_OFF32_LIBS,
    _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_LIBS,
    _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS,
    _CS_POSIX_V6_LP64_OFF64_CFLAGS,
    _CS_POSIX_V6_LP64_OFF64_LDFLAGS,
    _CS_POSIX_V6_LP64_OFF64_LIBS,
    _CS_POSIX_V6_LP64_OFF64_LINTFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LIBS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS,

    _CS_POSIX_V7_ILP32_OFF32_CFLAGS,
    _CS_POSIX_V7_ILP32_OFF32_LDFLAGS,
    _CS_POSIX_V7_ILP32_OFF32_LIBS,
    _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS,
    _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS,
    _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS,
    _CS_POSIX_V7_ILP32_OFFBIG_LIBS,
    _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS,
    _CS_POSIX_V7_LP64_OFF64_CFLAGS,
    _CS_POSIX_V7_LP64_OFF64_LDFLAGS,
    _CS_POSIX_V7_LP64_OFF64_LIBS,
    _CS_POSIX_V7_LP64_OFF64_LINTFLAGS,
    _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS,
    _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS,
    _CS_POSIX_V7_LPBIG_OFFBIG_LIBS,
    _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS
  };

 
extern long int pathconf (__const char *__path, int __name)
     throw () __attribute__ ((__nonnull__ (1)));

 
extern long int fpathconf (int __fd, int __name) throw ();

 
extern long int sysconf (int __name) throw ();

 
extern size_t confstr (int __name, char *__buf, size_t __len) throw ();


 
extern __pid_t getpid (void) throw ();

 
extern __pid_t getppid (void) throw ();


 
extern __pid_t getpgrp (void) throw ();

 
extern __pid_t __getpgid (__pid_t __pid) throw ();
extern __pid_t getpgid (__pid_t __pid) throw ();




 
extern int setpgid (__pid_t __pid, __pid_t __pgid) throw ();









 



 
extern int setpgrp (void) throw ();




 
extern __pid_t setsid (void) throw ();

 
extern __pid_t getsid (__pid_t __pid) throw ();

 
extern __uid_t getuid (void) throw ();

 
extern __uid_t geteuid (void) throw ();

 
extern __gid_t getgid (void) throw ();

 
extern __gid_t getegid (void) throw ();



 
extern int getgroups (int __size, __gid_t __list[]) throw () ;

 
extern int group_member (__gid_t __gid) throw ();




 
extern int setuid (__uid_t __uid) throw ();


 
extern int setreuid (__uid_t __ruid, __uid_t __euid) throw ();

 
extern int seteuid (__uid_t __uid) throw ();




 
extern int setgid (__gid_t __gid) throw ();


 
extern int setregid (__gid_t __rgid, __gid_t __egid) throw ();

 
extern int setegid (__gid_t __gid) throw ();


 
extern int getresuid (__uid_t *__ruid, __uid_t *__euid, __uid_t *__suid)
     throw ();


 
extern int getresgid (__gid_t *__rgid, __gid_t *__egid, __gid_t *__sgid)
     throw ();


 
extern int setresuid (__uid_t __ruid, __uid_t __euid, __uid_t __suid)
     throw ();


 
extern int setresgid (__gid_t __rgid, __gid_t __egid, __gid_t __sgid)
     throw ();




 
extern __pid_t fork (void) throw ();




 
extern __pid_t vfork (void) throw ();



 
extern char *ttyname (int __fd) throw ();


 
extern int ttyname_r (int __fd, char *__buf, size_t __buflen)
     throw () __attribute__ ((__nonnull__ (2))) ;


 
extern int isatty (int __fd) throw ();


 
extern int ttyslot (void) throw ();


 
extern int link (__const char *__from, __const char *__to)
     throw () __attribute__ ((__nonnull__ (1, 2))) ;


 
extern int linkat (int __fromfd, __const char *__from, int __tofd,
		   __const char *__to, int __flags)
     throw () __attribute__ ((__nonnull__ (2, 4))) ;

 
extern int symlink (__const char *__from, __const char *__to)
     throw () __attribute__ ((__nonnull__ (1, 2))) ;



 
extern ssize_t readlink (__const char *__restrict __path,
			 char *__restrict __buf, size_t __len)
     throw () __attribute__ ((__nonnull__ (1, 2))) ;

 
extern int symlinkat (__const char *__from, int __tofd,
		      __const char *__to) throw () __attribute__ ((__nonnull__ (1, 3))) ;

 
extern ssize_t readlinkat (int __fd, __const char *__restrict __path,
			   char *__restrict __buf, size_t __len)
     throw () __attribute__ ((__nonnull__ (2, 3))) ;

 
extern int unlink (__const char *__name) throw () __attribute__ ((__nonnull__ (1)));

 
extern int unlinkat (int __fd, __const char *__name, int __flag)
     throw () __attribute__ ((__nonnull__ (2)));

 
extern int rmdir (__const char *__path) throw () __attribute__ ((__nonnull__ (1)));


 
extern __pid_t tcgetpgrp (int __fd) throw ();

 
extern int tcsetpgrp (int __fd, __pid_t __pgrp_id) throw ();





 
extern char *getlogin (void);





 
extern int getlogin_r (char *__name, size_t __name_len) __attribute__ ((__nonnull__ (1)));

 
extern int setlogin (__const char *__name) throw () __attribute__ ((__nonnull__ (1)));




 


















 









 


extern "C" {





 

extern char *optarg;











 

extern int optind;


 

extern int opterr;

 

extern int optopt;

























 



 
extern int getopt (int ___argc, char *const *___argv, const char *__shortopts)
       throw ();



}

 





 
extern int gethostname (char *__name, size_t __len) throw () __attribute__ ((__nonnull__ (1)));



 
extern int sethostname (__const char *__name, size_t __len)
     throw () __attribute__ ((__nonnull__ (1))) ;


 
extern int sethostid (long int __id) throw () ;




 
extern int getdomainname (char *__name, size_t __len)
     throw () __attribute__ ((__nonnull__ (1))) ;
extern int setdomainname (__const char *__name, size_t __len)
     throw () __attribute__ ((__nonnull__ (1))) ;




 
extern int vhangup (void) throw ();

 
extern int revoke (__const char *__file) throw () __attribute__ ((__nonnull__ (1))) ;






 
extern int profil (unsigned short int *__sample_buffer, size_t __size,
		   size_t __offset, unsigned int __scale)
     throw () __attribute__ ((__nonnull__ (1)));




 
extern int acct (__const char *__name) throw ();


 
extern char *getusershell (void) throw ();
extern void endusershell (void) throw ();  
extern void setusershell (void) throw ();  




 
extern int daemon (int __nochdir, int __noclose) throw () ;



 
extern int chroot (__const char *__path) throw () __attribute__ ((__nonnull__ (1))) ;


 
extern char *getpass (__const char *__prompt) __attribute__ ((__nonnull__ (1)));





 
extern int fsync (int __fd);



 
extern long int gethostid (void);

 
extern void sync (void) throw ();



 
extern int getpagesize (void)  throw () __attribute__ ((__const__));



 
extern int getdtablesize (void) throw ();


 
extern int truncate (__const char *__file, __off_t __length)
     throw () __attribute__ ((__nonnull__ (1))) ;
extern int truncate64 (__const char *__file, __off64_t __length)
     throw () __attribute__ ((__nonnull__ (1))) ;



 
extern int ftruncate (int __fd, __off_t __length) throw () ;
extern int ftruncate64 (int __fd, __off64_t __length) throw () ;





 
extern int brk (void *__addr) throw () ;




 
extern void *sbrk (intptr_t __delta) throw ();











 
extern long int syscall (long int __sysno, ...) throw ();





 






 


extern int lockf (int __fd, int __cmd, __off_t __len) ;
extern int lockf64 (int __fd, int __cmd, __off64_t __len) ;




 



 
extern int fdatasync (int __fildes);



 
 
extern char *crypt (__const char *__key, __const char *__salt)
     throw () __attribute__ ((__nonnull__ (1, 2)));


 
extern void encrypt (char *__block, int __edflag) throw () __attribute__ ((__nonnull__ (1)));





 
extern void swab (__const void *__restrict __from, void *__restrict __to,
		  ssize_t __n) throw () __attribute__ ((__nonnull__ (1, 2)));



 
 
extern char *ctermid (char *__s) throw ();


 

}


typedef pthread_t __gthread_t;
typedef pthread_key_t __gthread_key_t;
typedef pthread_once_t __gthread_once_t;
typedef pthread_mutex_t __gthread_mutex_t;
typedef pthread_mutex_t __gthread_recursive_mutex_t;
typedef pthread_cond_t __gthread_cond_t;
typedef struct timespec __gthread_time_t;


 



 



 
static __typeof(pthread_once) __gthrw_pthread_once __attribute__ ((__weakref__("pthread_once"))); 
static __typeof(pthread_getspecific) __gthrw_pthread_getspecific __attribute__ ((__weakref__("pthread_getspecific"))); 
static __typeof(pthread_setspecific) __gthrw_pthread_setspecific __attribute__ ((__weakref__("pthread_setspecific"))); 

static __typeof(pthread_create) __gthrw_pthread_create __attribute__ ((__weakref__("pthread_create"))); 
static __typeof(pthread_join) __gthrw_pthread_join __attribute__ ((__weakref__("pthread_join"))); 
static __typeof(pthread_equal) __gthrw_pthread_equal __attribute__ ((__weakref__("pthread_equal"))); 
static __typeof(pthread_self) __gthrw_pthread_self __attribute__ ((__weakref__("pthread_self"))); 
static __typeof(pthread_detach) __gthrw_pthread_detach __attribute__ ((__weakref__("pthread_detach"))); 
static __typeof(pthread_cancel) __gthrw_pthread_cancel __attribute__ ((__weakref__("pthread_cancel"))); 
static __typeof(sched_yield) __gthrw_sched_yield __attribute__ ((__weakref__("sched_yield"))); 

static __typeof(pthread_mutex_lock) __gthrw_pthread_mutex_lock __attribute__ ((__weakref__("pthread_mutex_lock"))); 
static __typeof(pthread_mutex_trylock) __gthrw_pthread_mutex_trylock __attribute__ ((__weakref__("pthread_mutex_trylock"))); 
static __typeof(pthread_mutex_timedlock) __gthrw_pthread_mutex_timedlock __attribute__ ((__weakref__("pthread_mutex_timedlock"))); 
static __typeof(pthread_mutex_unlock) __gthrw_pthread_mutex_unlock __attribute__ ((__weakref__("pthread_mutex_unlock"))); 
static __typeof(pthread_mutex_init) __gthrw_pthread_mutex_init __attribute__ ((__weakref__("pthread_mutex_init"))); 
static __typeof(pthread_mutex_destroy) __gthrw_pthread_mutex_destroy __attribute__ ((__weakref__("pthread_mutex_destroy"))); 

static __typeof(pthread_cond_broadcast) __gthrw_pthread_cond_broadcast __attribute__ ((__weakref__("pthread_cond_broadcast"))); 
static __typeof(pthread_cond_signal) __gthrw_pthread_cond_signal __attribute__ ((__weakref__("pthread_cond_signal"))); 
static __typeof(pthread_cond_wait) __gthrw_pthread_cond_wait __attribute__ ((__weakref__("pthread_cond_wait"))); 
static __typeof(pthread_cond_timedwait) __gthrw_pthread_cond_timedwait __attribute__ ((__weakref__("pthread_cond_timedwait"))); 
static __typeof(pthread_cond_destroy) __gthrw_pthread_cond_destroy __attribute__ ((__weakref__("pthread_cond_destroy"))); 

static __typeof(pthread_key_create) __gthrw_pthread_key_create __attribute__ ((__weakref__("pthread_key_create"))); 
static __typeof(pthread_key_delete) __gthrw_pthread_key_delete __attribute__ ((__weakref__("pthread_key_delete"))); 
static __typeof(pthread_mutexattr_init) __gthrw_pthread_mutexattr_init __attribute__ ((__weakref__("pthread_mutexattr_init"))); 
static __typeof(pthread_mutexattr_settype) __gthrw_pthread_mutexattr_settype __attribute__ ((__weakref__("pthread_mutexattr_settype"))); 
static __typeof(pthread_mutexattr_destroy) __gthrw_pthread_mutexattr_destroy __attribute__ ((__weakref__("pthread_mutexattr_destroy"))); 













 


static inline int
__gthread_active_p (void)
{
  static void *const __gthread_active_ptr
    = __extension__ (void *) &
__gthrw_pthread_cancel;
  return __gthread_active_ptr != 0;
}




static inline int
__gthread_create (__gthread_t *__threadid, void *(*__func) (void*),
		  void *__args)
{
  return __gthrw_pthread_create (__threadid, __null, __func, __args);
}

static inline int
__gthread_join (__gthread_t __threadid, void **__value_ptr)
{
  return __gthrw_pthread_join (__threadid, __value_ptr);
}

static inline int
__gthread_detach (__gthread_t __threadid)
{
  return __gthrw_pthread_detach (__threadid);
}

static inline int
__gthread_equal (__gthread_t __t1, __gthread_t __t2)
{
  return __gthrw_pthread_equal (__t1, __t2);
}

static inline __gthread_t
__gthread_self (void)
{
  return __gthrw_pthread_self ();
}

static inline int
__gthread_yield (void)
{
  return __gthrw_sched_yield ();
}

static inline int
__gthread_once (__gthread_once_t *__once, void (*__func) (void))
{
  if (__gthread_active_p ())
    return __gthrw_pthread_once (__once, __func);
  else
    return -1;
}

static inline int
__gthread_key_create (__gthread_key_t *__key, void (*__dtor) (void *))
{
  return __gthrw_pthread_key_create (__key, __dtor);
}

static inline int
__gthread_key_delete (__gthread_key_t __key)
{
  return __gthrw_pthread_key_delete (__key);
}

static inline void *
__gthread_getspecific (__gthread_key_t __key)
{
  return __gthrw_pthread_getspecific (__key);
}

static inline int
__gthread_setspecific (__gthread_key_t __key, const void *__ptr)
{
  return __gthrw_pthread_setspecific (__key, __ptr);
}

static inline int
__gthread_mutex_destroy (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return __gthrw_pthread_mutex_destroy (__mutex);
  else
    return 0;
}

static inline int
__gthread_mutex_lock (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return __gthrw_pthread_mutex_lock (__mutex);
  else
    return 0;
}

static inline int
__gthread_mutex_trylock (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return __gthrw_pthread_mutex_trylock (__mutex);
  else
    return 0;
}

static inline int
__gthread_mutex_timedlock (__gthread_mutex_t *__mutex,
			   const __gthread_time_t *__abs_timeout)
{
  if (__gthread_active_p ())
    return __gthrw_pthread_mutex_timedlock (__mutex, __abs_timeout);
  else
    return 0;
}

static inline int
__gthread_mutex_unlock (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return __gthrw_pthread_mutex_unlock (__mutex);
  else
    return 0;
}


static inline int
__gthread_recursive_mutex_lock (__gthread_recursive_mutex_t *__mutex)
{
  return __gthread_mutex_lock (__mutex);
}

static inline int
__gthread_recursive_mutex_trylock (__gthread_recursive_mutex_t *__mutex)
{
  return __gthread_mutex_trylock (__mutex);
}

static inline int
__gthread_recursive_mutex_timedlock (__gthread_recursive_mutex_t *__mutex,
				     const __gthread_time_t *__abs_timeout)
{
  return __gthread_mutex_timedlock (__mutex, __abs_timeout);
}

static inline int
__gthread_recursive_mutex_unlock (__gthread_recursive_mutex_t *__mutex)
{
  return __gthread_mutex_unlock (__mutex);
}

static inline int
__gthread_cond_broadcast (__gthread_cond_t *__cond)
{
  return __gthrw_pthread_cond_broadcast (__cond);
}

static inline int
__gthread_cond_signal (__gthread_cond_t *__cond)
{
  return __gthrw_pthread_cond_signal (__cond);
}

static inline int
__gthread_cond_wait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex)
{
  return __gthrw_pthread_cond_wait (__cond, __mutex);
}

static inline int
__gthread_cond_timedwait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex,
			  const __gthread_time_t *__abs_timeout)
{
  return __gthrw_pthread_cond_timedwait (__cond, __mutex, __abs_timeout);
}

static inline int
__gthread_cond_wait_recursive (__gthread_cond_t *__cond,
			       __gthread_recursive_mutex_t *__mutex)
{
  return __gthread_cond_wait (__cond, __mutex);
}

static inline int
__gthread_cond_timedwait_recursive (__gthread_cond_t *__cond,
				    __gthread_recursive_mutex_t *__mutex,
				    const __gthread_time_t *__abs_timeout)
{
  return __gthread_cond_timedwait (__cond, __mutex, __abs_timeout);
}

static inline int
__gthread_cond_destroy (__gthread_cond_t* __cond)
{
  return __gthrw_pthread_cond_destroy (__cond);
}



 

#pragma GCC visibility pop



























 


typedef int _Atomic_word;















namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{


  
  
  
  
  static inline _Atomic_word 
  __exchange_and_add(volatile _Atomic_word* __mem, int __val)
  { return __sync_fetch_and_add(__mem, __val); }

  static inline void
  __atomic_add(volatile _Atomic_word* __mem, int __val)
  { __sync_fetch_and_add(__mem, __val); }

  static inline _Atomic_word
  __exchange_and_add_single(_Atomic_word* __mem, int __val)
  {
    _Atomic_word __result = *__mem;
    *__mem += __val;
    return __result;
  }

  static inline void
  __atomic_add_single(_Atomic_word* __mem, int __val)
  { *__mem += __val; }

  static inline _Atomic_word
  __attribute__ ((__unused__))
  __exchange_and_add_dispatch(_Atomic_word* __mem, int __val)
  {
    if (__gthread_active_p())
      return __exchange_and_add(__mem, __val);
    else
      return __exchange_and_add_single(__mem, __val);
  }

  static inline void
  __attribute__ ((__unused__))
  __atomic_add_dispatch(_Atomic_word* __mem, int __val)
  {
    if (__gthread_active_p())
      __atomic_add(__mem, __val);
    else
      __atomic_add_single(__mem, __val);
  }


} 


































 



































 


































 




  


























 



#pragma GCC visibility push(default)

namespace __cxxabiv1
{  
  





 
  class __forced_unwind
  {
    virtual ~__forced_unwind() throw();

    
    virtual void __pure_dummy() = 0; 
  };
}

#pragma GCC visibility pop


namespace std __attribute__ ((__visibility__ ("default")))
{


  template<typename _CharT, typename _Traits>
    inline void
    __ostream_write(basic_ostream<_CharT, _Traits>& __out,
		    const _CharT* __s, streamsize __n)
    {
      typedef basic_ostream<_CharT, _Traits>       __ostream_type;      
      typedef typename __ostream_type::ios_base    __ios_base;

      const streamsize __put = __out.rdbuf()->sputn(__s, __n);
      if (__put != __n)
	__out.setstate(__ios_base::badbit);
    }

  template<typename _CharT, typename _Traits>
    inline void
    __ostream_fill(basic_ostream<_CharT, _Traits>& __out, streamsize __n)
    {
      typedef basic_ostream<_CharT, _Traits>       __ostream_type;      
      typedef typename __ostream_type::ios_base    __ios_base;

      const _CharT __c = __out.fill();
      for (; __n > 0; --__n)
	{
	  const typename _Traits::int_type __put = __out.rdbuf()->sputc(__c);
	  if (_Traits::eq_int_type(__put, _Traits::eof()))
	    {
	      __out.setstate(__ios_base::badbit);
	      break;
	    }
	}
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    __ostream_insert(basic_ostream<_CharT, _Traits>& __out,
		     const _CharT* __s, streamsize __n)
    {
      typedef basic_ostream<_CharT, _Traits>       __ostream_type;
      typedef typename __ostream_type::ios_base    __ios_base;

      typename __ostream_type::sentry __cerb(__out);
      if (__cerb)
	{
	  try
	    {
	      const streamsize __w = __out.width();
	      if (__w > __n)
		{
		  const bool __left = ((__out.flags()
					& __ios_base::adjustfield)
				       == __ios_base::left);
		  if (!__left)
		    __ostream_fill(__out, __w - __n);
		  if (__out.good())
		    __ostream_write(__out, __s, __n);
		  if (__left && __out.good())
		    __ostream_fill(__out, __w - __n);
		}
	      else
		__ostream_write(__out, __s, __n);
	      __out.width(0);
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      __out._M_setstate(__ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { __out._M_setstate(__ios_base::badbit); }
	}
      return __out;
    }

  
  
  extern template ostream& __ostream_insert(ostream&, const char*, streamsize);

  extern template wostream& __ostream_insert(wostream&, const wchar_t*,
					     streamsize);


} 


















































 




 


namespace std __attribute__ ((__visibility__ ("default")))
{


  
  































 
  

 
  template<typename _Arg, typename _Result>
    struct unary_function
    {
      
      typedef _Arg 	argument_type;   

      
      typedef _Result 	result_type;  
    };

  

 
  template<typename _Arg1, typename _Arg2, typename _Result>
    struct binary_function
    {
      
      typedef _Arg1 	first_argument_type; 

      
      typedef _Arg2 	second_argument_type;

      
      typedef _Result 	result_type;
    };
   

  
  








 
  
  template<typename _Tp>
    struct plus : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x + __y; }
    };

  
  template<typename _Tp>
    struct minus : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x - __y; }
    };

  
  template<typename _Tp>
    struct multiplies : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x * __y; }
    };

  
  template<typename _Tp>
    struct divides : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x / __y; }
    };

  
  template<typename _Tp>
    struct modulus : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x % __y; }
    };

  
  template<typename _Tp>
    struct negate : public unary_function<_Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x) const
      { return -__x; }
    };
   

  
  






 
  
  template<typename _Tp>
    struct equal_to : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x == __y; }
    };

  
  template<typename _Tp>
    struct not_equal_to : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x != __y; }
    };

  
  template<typename _Tp>
    struct greater : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x > __y; }
    };

  
  template<typename _Tp>
    struct less : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x < __y; }
    };

  
  template<typename _Tp>
    struct greater_equal : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x >= __y; }
    };

  
  template<typename _Tp>
    struct less_equal : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x <= __y; }
    };
   

  
  






 
  
  template<typename _Tp>
    struct logical_and : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x && __y; }
    };

  
  template<typename _Tp>
    struct logical_or : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x || __y; }
    };

  
  template<typename _Tp>
    struct logical_not : public unary_function<_Tp, bool>
    {
      bool
      operator()(const _Tp& __x) const
      { return !__x; }
    };
   

  
  
  template<typename _Tp>
    struct bit_and : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x & __y; }
    };

  template<typename _Tp>
    struct bit_or : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x | __y; }
    };

  template<typename _Tp>
    struct bit_xor : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x ^ __y; }
    };

  
  


























 
  
  template<typename _Predicate>
    class unary_negate
    : public unary_function<typename _Predicate::argument_type, bool>
    {
    protected:
      _Predicate _M_pred;

    public:
      explicit
      unary_negate(const _Predicate& __x) : _M_pred(__x) { }

      bool
      operator()(const typename _Predicate::argument_type& __x) const
      { return !_M_pred(__x); }
    };

  
  template<typename _Predicate>
    inline unary_negate<_Predicate>
    not1(const _Predicate& __pred)
    { return unary_negate<_Predicate>(__pred); }

  
  template<typename _Predicate>
    class binary_negate
    : public binary_function<typename _Predicate::first_argument_type,
			     typename _Predicate::second_argument_type, bool>
    {
    protected:
      _Predicate _M_pred;

    public:
      explicit
      binary_negate(const _Predicate& __x) : _M_pred(__x) { }

      bool
      operator()(const typename _Predicate::first_argument_type& __x,
		 const typename _Predicate::second_argument_type& __y) const
      { return !_M_pred(__x, __y); }
    };

  
  template<typename _Predicate>
    inline binary_negate<_Predicate>
    not2(const _Predicate& __pred)
    { return binary_negate<_Predicate>(__pred); }
   

  
  



















 
  
  template<typename _Arg, typename _Result>
    class pointer_to_unary_function : public unary_function<_Arg, _Result>
    {
    protected:
      _Result (*_M_ptr)(_Arg);

    public:
      pointer_to_unary_function() { }

      explicit
      pointer_to_unary_function(_Result (*__x)(_Arg))
      : _M_ptr(__x) { }

      _Result
      operator()(_Arg __x) const
      { return _M_ptr(__x); }
    };

  
  template<typename _Arg, typename _Result>
    inline pointer_to_unary_function<_Arg, _Result>
    ptr_fun(_Result (*__x)(_Arg))
    { return pointer_to_unary_function<_Arg, _Result>(__x); }

  
  template<typename _Arg1, typename _Arg2, typename _Result>
    class pointer_to_binary_function
    : public binary_function<_Arg1, _Arg2, _Result>
    {
    protected:
      _Result (*_M_ptr)(_Arg1, _Arg2);

    public:
      pointer_to_binary_function() { }

      explicit
      pointer_to_binary_function(_Result (*__x)(_Arg1, _Arg2))
      : _M_ptr(__x) { }

      _Result
      operator()(_Arg1 __x, _Arg2 __y) const
      { return _M_ptr(__x, __y); }
    };

  
  template<typename _Arg1, typename _Arg2, typename _Result>
    inline pointer_to_binary_function<_Arg1, _Arg2, _Result>
    ptr_fun(_Result (*__x)(_Arg1, _Arg2))
    { return pointer_to_binary_function<_Arg1, _Arg2, _Result>(__x); }
   

  template<typename _Tp>
    struct _Identity : public unary_function<_Tp,_Tp>
    {
      _Tp&
      operator()(_Tp& __x) const
      { return __x; }

      const _Tp&
      operator()(const _Tp& __x) const
      { return __x; }
    };

  template<typename _Pair>
    struct _Select1st : public unary_function<_Pair,
					      typename _Pair::first_type>
    {
      typename _Pair::first_type&
      operator()(_Pair& __x) const
      { return __x.first; }

      const typename _Pair::first_type&
      operator()(const _Pair& __x) const
      { return __x.first; }

    };

  template<typename _Pair>
    struct _Select2nd : public unary_function<_Pair,
					      typename _Pair::second_type>
    {
      typename _Pair::second_type&
      operator()(_Pair& __x) const
      { return __x.second; }

      const typename _Pair::second_type&
      operator()(const _Pair& __x) const
      { return __x.second; }
    };

  
  













 
  
  
  template<typename _Ret, typename _Tp>
    class mem_fun_t : public unary_function<_Tp*, _Ret>
    {
    public:
      explicit
      mem_fun_t(_Ret (_Tp::*__pf)())
      : _M_f(__pf) { }

      _Ret
      operator()(_Tp* __p) const
      { return (__p->*_M_f)(); }

    private:
      _Ret (_Tp::*_M_f)();
    };

  
  
  template<typename _Ret, typename _Tp>
    class const_mem_fun_t : public unary_function<const _Tp*, _Ret>
    {
    public:
      explicit
      const_mem_fun_t(_Ret (_Tp::*__pf)() const)
      : _M_f(__pf) { }

      _Ret
      operator()(const _Tp* __p) const
      { return (__p->*_M_f)(); }

    private:
      _Ret (_Tp::*_M_f)() const;
    };

  
  
  template<typename _Ret, typename _Tp>
    class mem_fun_ref_t : public unary_function<_Tp, _Ret>
    {
    public:
      explicit
      mem_fun_ref_t(_Ret (_Tp::*__pf)())
      : _M_f(__pf) { }

      _Ret
      operator()(_Tp& __r) const
      { return (__r.*_M_f)(); }

    private:
      _Ret (_Tp::*_M_f)();
  };

  
  
  template<typename _Ret, typename _Tp>
    class const_mem_fun_ref_t : public unary_function<_Tp, _Ret>
    {
    public:
      explicit
      const_mem_fun_ref_t(_Ret (_Tp::*__pf)() const)
      : _M_f(__pf) { }

      _Ret
      operator()(const _Tp& __r) const
      { return (__r.*_M_f)(); }

    private:
      _Ret (_Tp::*_M_f)() const;
    };

  
  
  template<typename _Ret, typename _Tp, typename _Arg>
    class mem_fun1_t : public binary_function<_Tp*, _Arg, _Ret>
    {
    public:
      explicit
      mem_fun1_t(_Ret (_Tp::*__pf)(_Arg))
      : _M_f(__pf) { }

      _Ret
      operator()(_Tp* __p, _Arg __x) const
      { return (__p->*_M_f)(__x); }

    private:
      _Ret (_Tp::*_M_f)(_Arg);
    };

  
  
  template<typename _Ret, typename _Tp, typename _Arg>
    class const_mem_fun1_t : public binary_function<const _Tp*, _Arg, _Ret>
    {
    public:
      explicit
      const_mem_fun1_t(_Ret (_Tp::*__pf)(_Arg) const)
      : _M_f(__pf) { }

      _Ret
      operator()(const _Tp* __p, _Arg __x) const
      { return (__p->*_M_f)(__x); }

    private:
      _Ret (_Tp::*_M_f)(_Arg) const;
    };

  
  
  template<typename _Ret, typename _Tp, typename _Arg>
    class mem_fun1_ref_t : public binary_function<_Tp, _Arg, _Ret>
    {
    public:
      explicit
      mem_fun1_ref_t(_Ret (_Tp::*__pf)(_Arg))
      : _M_f(__pf) { }

      _Ret
      operator()(_Tp& __r, _Arg __x) const
      { return (__r.*_M_f)(__x); }

    private:
      _Ret (_Tp::*_M_f)(_Arg);
    };

  
  
  template<typename _Ret, typename _Tp, typename _Arg>
    class const_mem_fun1_ref_t : public binary_function<_Tp, _Arg, _Ret>
    {
    public:
      explicit
      const_mem_fun1_ref_t(_Ret (_Tp::*__pf)(_Arg) const)
      : _M_f(__pf) { }

      _Ret
      operator()(const _Tp& __r, _Arg __x) const
      { return (__r.*_M_f)(__x); }

    private:
      _Ret (_Tp::*_M_f)(_Arg) const;
    };

  
  
  template<typename _Ret, typename _Tp>
    inline mem_fun_t<_Ret, _Tp>
    mem_fun(_Ret (_Tp::*__f)())
    { return mem_fun_t<_Ret, _Tp>(__f); }

  template<typename _Ret, typename _Tp>
    inline const_mem_fun_t<_Ret, _Tp>
    mem_fun(_Ret (_Tp::*__f)() const)
    { return const_mem_fun_t<_Ret, _Tp>(__f); }

  template<typename _Ret, typename _Tp>
    inline mem_fun_ref_t<_Ret, _Tp>
    mem_fun_ref(_Ret (_Tp::*__f)())
    { return mem_fun_ref_t<_Ret, _Tp>(__f); }

  template<typename _Ret, typename _Tp>
    inline const_mem_fun_ref_t<_Ret, _Tp>
    mem_fun_ref(_Ret (_Tp::*__f)() const)
    { return const_mem_fun_ref_t<_Ret, _Tp>(__f); }

  template<typename _Ret, typename _Tp, typename _Arg>
    inline mem_fun1_t<_Ret, _Tp, _Arg>
    mem_fun(_Ret (_Tp::*__f)(_Arg))
    { return mem_fun1_t<_Ret, _Tp, _Arg>(__f); }

  template<typename _Ret, typename _Tp, typename _Arg>
    inline const_mem_fun1_t<_Ret, _Tp, _Arg>
    mem_fun(_Ret (_Tp::*__f)(_Arg) const)
    { return const_mem_fun1_t<_Ret, _Tp, _Arg>(__f); }

  template<typename _Ret, typename _Tp, typename _Arg>
    inline mem_fun1_ref_t<_Ret, _Tp, _Arg>
    mem_fun_ref(_Ret (_Tp::*__f)(_Arg))
    { return mem_fun1_ref_t<_Ret, _Tp, _Arg>(__f); }

  template<typename _Ret, typename _Tp, typename _Arg>
    inline const_mem_fun1_ref_t<_Ret, _Tp, _Arg>
    mem_fun_ref(_Ret (_Tp::*__f)(_Arg) const)
    { return const_mem_fun1_ref_t<_Ret, _Tp, _Arg>(__f); }

   


} 


















































 




 


namespace std __attribute__ ((__visibility__ ("default")))
{


  
  































 
  
  template<typename _Operation>
    class binder1st
    : public unary_function<typename _Operation::second_argument_type,
			    typename _Operation::result_type>
    {
    protected:
      _Operation op;
      typename _Operation::first_argument_type value;

    public:
      binder1st(const _Operation& __x,
		const typename _Operation::first_argument_type& __y)
      : op(__x), value(__y) { }

      typename _Operation::result_type
      operator()(const typename _Operation::second_argument_type& __x) const
      { return op(value, __x); }

      
      
      typename _Operation::result_type
      operator()(typename _Operation::second_argument_type& __x) const
      { return op(value, __x); }
    } ;

  
  template<typename _Operation, typename _Tp>
    inline binder1st<_Operation>
    bind1st(const _Operation& __fn, const _Tp& __x)
    {
      typedef typename _Operation::first_argument_type _Arg1_type;
      return binder1st<_Operation>(__fn, _Arg1_type(__x));
    }

  
  template<typename _Operation>
    class binder2nd
    : public unary_function<typename _Operation::first_argument_type,
			    typename _Operation::result_type>
    {
    protected:
      _Operation op;
      typename _Operation::second_argument_type value;

    public:
      binder2nd(const _Operation& __x,
		const typename _Operation::second_argument_type& __y)
      : op(__x), value(__y) { }

      typename _Operation::result_type
      operator()(const typename _Operation::first_argument_type& __x) const
      { return op(__x, value); }

      
      
      typename _Operation::result_type
      operator()(typename _Operation::first_argument_type& __x) const
      { return op(__x, value); }
    } ;

  
  template<typename _Operation, typename _Tp>
    inline binder2nd<_Operation>
    bind2nd(const _Operation& __fn, const _Tp& __x)
    {
      typedef typename _Operation::second_argument_type _Arg2_type;
      return binder2nd<_Operation>(__fn, _Arg2_type(__x));
    } 
   


} 































 








namespace std __attribute__ ((__visibility__ ("default")))
{


  






















































 
  
  template<typename _CharT, typename _Traits, typename _Alloc>
    class basic_string
    {
      typedef typename _Alloc::template rebind<_CharT>::other _CharT_alloc_type;

      
    public:
      typedef _Traits					    traits_type;
      typedef typename _Traits::char_type		    value_type;
      typedef _Alloc					    allocator_type;
      typedef typename _CharT_alloc_type::size_type	    size_type;
      typedef typename _CharT_alloc_type::difference_type   difference_type;
      typedef typename _CharT_alloc_type::reference	    reference;
      typedef typename _CharT_alloc_type::const_reference   const_reference;
      typedef typename _CharT_alloc_type::pointer	    pointer;
      typedef typename _CharT_alloc_type::const_pointer	    const_pointer;
      typedef __gnu_cxx::__normal_iterator<pointer, basic_string>  iterator;
      typedef __gnu_cxx::__normal_iterator<const_pointer, basic_string>
                                                            const_iterator;
      typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
      typedef std::reverse_iterator<iterator>		    reverse_iterator;

    private:
      
      
      
      
      
      
      
      
      
      
      
      
      

      struct _Rep_base
      {
	size_type		_M_length;
	size_type		_M_capacity;
	_Atomic_word		_M_refcount;
      };

      struct _Rep : _Rep_base
      {
	
	typedef typename _Alloc::template rebind<char>::other _Raw_bytes_alloc;

	

	
	
	
	
	
	
	
	
	
	
	
	static const size_type	_S_max_size;
	static const _CharT	_S_terminal;

	
        
        static size_type _S_empty_rep_storage[];

        static _Rep&
        _S_empty_rep()
        { 
	  
	  
	  
	  void* __p = reinterpret_cast<void*>(&_S_empty_rep_storage);
	  return *reinterpret_cast<_Rep*>(__p);
	}

        bool
	_M_is_leaked() const
        { return this->_M_refcount < 0; }

        bool
	_M_is_shared() const
        { return this->_M_refcount > 0; }

        void
	_M_set_leaked()
        { this->_M_refcount = -1; }

        void
	_M_set_sharable()
        { this->_M_refcount = 0; }

	void
	_M_set_length_and_sharable(size_type __n)
	{
	  if (__builtin_expect(this != &_S_empty_rep(), false))
	    {
	      this->_M_set_sharable();  
	      this->_M_length = __n;
	      traits_type::assign(this->_M_refdata()[__n], _S_terminal);
	      
	      
	    }
	}

	_CharT*
	_M_refdata() throw()
	{ return reinterpret_cast<_CharT*>(this + 1); }

	_CharT*
	_M_grab(const _Alloc& __alloc1, const _Alloc& __alloc2)
	{
	  return (!_M_is_leaked() && __alloc1 == __alloc2)
	          ? _M_refcopy() : _M_clone(__alloc1);
	}

	
	static _Rep*
	_S_create(size_type, size_type, const _Alloc&);

	void
	_M_dispose(const _Alloc& __a)
	{
	  if (__builtin_expect(this != &_S_empty_rep(), false))
	    {
	      
	      ;
	      if (__gnu_cxx::__exchange_and_add_dispatch(&this->_M_refcount,
							 -1) <= 0)
		{
		  ;
		  _M_destroy(__a);
		}
	    }
	}  

	void
	_M_destroy(const _Alloc&) throw();

	_CharT*
	_M_refcopy() throw()
	{
	  if (__builtin_expect(this != &_S_empty_rep(), false))
            __gnu_cxx::__atomic_add_dispatch(&this->_M_refcount, 1);
	  return _M_refdata();
	}  

	_CharT*
	_M_clone(const _Alloc&, size_type __res = 0);
      };

      
      struct _Alloc_hider : _Alloc
      {
	_Alloc_hider(_CharT* __dat, const _Alloc& __a)
	: _Alloc(__a), _M_p(__dat) { }

	_CharT* _M_p; 
      };

    public:
      
      
      
      
      static const size_type	npos = static_cast<size_type>(-1);

    private:
      
      mutable _Alloc_hider	_M_dataplus;

      _CharT*
      _M_data() const
      { return  _M_dataplus._M_p; }

      _CharT*
      _M_data(_CharT* __p)
      { return (_M_dataplus._M_p = __p); }

      _Rep*
      _M_rep() const
      { return &((reinterpret_cast<_Rep*> (_M_data()))[-1]); }

      
      
      iterator
      _M_ibegin() const
      { return iterator(_M_data()); }

      iterator
      _M_iend() const
      { return iterator(_M_data() + this->size()); }

      void
      _M_leak()    
      {
	if (!_M_rep()->_M_is_leaked())
	  _M_leak_hard();
      }

      size_type
      _M_check(size_type __pos, const char* __s) const
      {
	if (__pos > this->size())
	  __throw_out_of_range((__s));
	return __pos;
      }

      void
      _M_check_length(size_type __n1, size_type __n2, const char* __s) const
      {
	if (this->max_size() - (this->size() - __n1) < __n2)
	  __throw_length_error((__s));
      }

      
      size_type
      _M_limit(size_type __pos, size_type __off) const
      {
	const bool __testoff =  __off < this->size() - __pos;
	return __testoff ? __off : this->size() - __pos;
      }

      
      bool
      _M_disjunct(const _CharT* __s) const
      {
	return (less<const _CharT*>()(__s, _M_data())
		|| less<const _CharT*>()(_M_data() + this->size(), __s));
      }

      
      
      static void
      _M_copy(_CharT* __d, const _CharT* __s, size_type __n)
      {
	if (__n == 1)
	  traits_type::assign(*__d, *__s);
	else
	  traits_type::copy(__d, __s, __n);
      }

      static void
      _M_move(_CharT* __d, const _CharT* __s, size_type __n)
      {
	if (__n == 1)
	  traits_type::assign(*__d, *__s);
	else
	  traits_type::move(__d, __s, __n);	  
      }

      static void
      _M_assign(_CharT* __d, size_type __n, _CharT __c)
      {
	if (__n == 1)
	  traits_type::assign(*__d, __c);
	else
	  traits_type::assign(__d, __n, __c);	  
      }

      
      
      template<class _Iterator>
        static void
        _S_copy_chars(_CharT* __p, _Iterator __k1, _Iterator __k2)
        {
	  for (; __k1 != __k2; ++__k1, ++__p)
	    traits_type::assign(*__p, *__k1); 
	}

      static void
      _S_copy_chars(_CharT* __p, iterator __k1, iterator __k2)
      { _S_copy_chars(__p, __k1.base(), __k2.base()); }

      static void
      _S_copy_chars(_CharT* __p, const_iterator __k1, const_iterator __k2)
      { _S_copy_chars(__p, __k1.base(), __k2.base()); }

      static void
      _S_copy_chars(_CharT* __p, _CharT* __k1, _CharT* __k2)
      { _M_copy(__p, __k1, __k2 - __k1); }

      static void
      _S_copy_chars(_CharT* __p, const _CharT* __k1, const _CharT* __k2)
      { _M_copy(__p, __k1, __k2 - __k1); }

      static int
      _S_compare(size_type __n1, size_type __n2)
      {
	const difference_type __d = difference_type(__n1 - __n2);

	if (__d > __gnu_cxx::__numeric_traits<int>::__max)
	  return __gnu_cxx::__numeric_traits<int>::__max;
	else if (__d < __gnu_cxx::__numeric_traits<int>::__min)
	  return __gnu_cxx::__numeric_traits<int>::__min;
	else
	  return int(__d);
      }

      void
      _M_mutate(size_type __pos, size_type __len1, size_type __len2);

      void
      _M_leak_hard();

      static _Rep&
      _S_empty_rep()
      { return _Rep::_S_empty_rep(); }

    public:
      
      
      

      

 
      basic_string()
      : _M_dataplus(_S_empty_rep()._M_refdata(), _Alloc()) { }

      

 
      explicit
      basic_string(const _Alloc& __a);

      
      


 
      basic_string(const basic_string& __str);
      




 
      basic_string(const basic_string& __str, size_type __pos,
		   size_type __n = npos);
      





 
      basic_string(const basic_string& __str, size_type __pos,
		   size_type __n, const _Alloc& __a);

      







 
      basic_string(const _CharT* __s, size_type __n,
		   const _Alloc& __a = _Alloc());
      



 
      basic_string(const _CharT* __s, const _Alloc& __a = _Alloc());
      




 
      basic_string(size_type __n, _CharT __c, const _Alloc& __a = _Alloc());


      




 
      template<class _InputIterator>
        basic_string(_InputIterator __beg, _InputIterator __end,
		     const _Alloc& __a = _Alloc());

      

 
      ~basic_string()
      { _M_rep()->_M_dispose(this->get_allocator()); }

      


 
      basic_string&
      operator=(const basic_string& __str) 
      { return this->assign(__str); }

      


 
      basic_string&
      operator=(const _CharT* __s) 
      { return this->assign(__s); }

      





 
      basic_string&
      operator=(_CharT __c) 
      { 
	this->assign(1, __c); 
	return *this;
      }


      
      


 
      iterator
      begin()
      {
	_M_leak();
	return iterator(_M_data());
      }

      


 
      const_iterator
      begin() const
      { return const_iterator(_M_data()); }

      


 
      iterator
      end()
      {
	_M_leak();
	return iterator(_M_data() + this->size());
      }

      


 
      const_iterator
      end() const
      { return const_iterator(_M_data() + this->size()); }

      



 
      reverse_iterator
      rbegin()
      { return reverse_iterator(this->end()); }

      



 
      const_reverse_iterator
      rbegin() const
      { return const_reverse_iterator(this->end()); }

      



 
      reverse_iterator
      rend()
      { return reverse_iterator(this->begin()); }

      



 
      const_reverse_iterator
      rend() const
      { return const_reverse_iterator(this->begin()); }


    public:
      
      
      
      size_type
      size() const
      { return _M_rep()->_M_length; }

      
      
      size_type
      length() const
      { return _M_rep()->_M_length; }

      
      size_type
      max_size() const
      { return _Rep::_S_max_size; }

      








 
      void
      resize(size_type __n, _CharT __c);

      








 
      void
      resize(size_type __n)
      { this->resize(__n, _CharT()); }


      


 
      size_type
      capacity() const
      { return _M_rep()->_M_capacity; }

      















 
      void
      reserve(size_type __res_arg = 0);

      

 
      void
      clear()
      { _M_mutate(0, this->size(), 0); }

      


 
      bool
      empty() const
      { return this->size() == 0; }

      
      








 
      const_reference
      operator[] (size_type __pos) const
      {
	;
	return _M_data()[__pos];
      }

      








 
      reference
      operator[](size_type __pos)
      {
        
	;
        
	;
	_M_leak();
	return _M_data()[__pos];
      }

      








 
      const_reference
      at(size_type __n) const
      {
	if (__n >= this->size())
	  __throw_out_of_range(("basic_string::at"));
	return _M_data()[__n];
      }


      









 
      reference
      at(size_type __n)
      {
	if (__n >= size())
	  __throw_out_of_range(("basic_string::at"));
	_M_leak();
	return _M_data()[__n];
      }

      
      



 
      basic_string&
      operator+=(const basic_string& __str)
      { return this->append(__str); }

      



 
      basic_string&
      operator+=(const _CharT* __s)
      { return this->append(__s); }

      



 
      basic_string&
      operator+=(_CharT __c)
      { 
	this->push_back(__c);
	return *this;
      }


      



 
      basic_string&
      append(const basic_string& __str);

      










 
      basic_string&
      append(const basic_string& __str, size_type __pos, size_type __n);

      




 
      basic_string&
      append(const _CharT* __s, size_type __n);

      



 
      basic_string&
      append(const _CharT* __s)
      {
	;
	return this->append(__s, traits_type::length(__s));
      }

      






 
      basic_string&
      append(size_type __n, _CharT __c);


      






 
      template<class _InputIterator>
        basic_string&
        append(_InputIterator __first, _InputIterator __last)
        { return this->replace(_M_iend(), _M_iend(), __first, __last); }

      


 
      void
      push_back(_CharT __c)
      { 
	const size_type __len = 1 + this->size();
	if (__len > this->capacity() || _M_rep()->_M_is_shared())
	  this->reserve(__len);
	traits_type::assign(_M_data()[this->size()], __c);
	_M_rep()->_M_set_length_and_sharable(__len);
      }

      



 
      basic_string&
      assign(const basic_string& __str);


      










 
      basic_string&
      assign(const basic_string& __str, size_type __pos, size_type __n)
      { return this->assign(__str._M_data()
			    + __str._M_check(__pos, "basic_string::assign"),
			    __str._M_limit(__pos, __n)); }

      








 
      basic_string&
      assign(const _CharT* __s, size_type __n);

      







 
      basic_string&
      assign(const _CharT* __s)
      {
	;
	return this->assign(__s, traits_type::length(__s));
      }

      







 
      basic_string&
      assign(size_type __n, _CharT __c)
      { return _M_replace_aux(size_type(0), this->size(), __n, __c); }

      






 
      template<class _InputIterator>
        basic_string&
        assign(_InputIterator __first, _InputIterator __last)
        { return this->replace(_M_ibegin(), _M_iend(), __first, __last); }


      










 
      void
      insert(iterator __p, size_type __n, _CharT __c)
      {	this->replace(__p, __p, __n, __c);  }

      









 
      template<class _InputIterator>
        void
        insert(iterator __p, _InputIterator __beg, _InputIterator __end)
        { this->replace(__p, __p, __beg, __end); }


      









 
      basic_string&
      insert(size_type __pos1, const basic_string& __str)
      { return this->insert(__pos1, __str, size_type(0), __str.size()); }

      
















 
      basic_string&
      insert(size_type __pos1, const basic_string& __str,
	     size_type __pos2, size_type __n)
      { return this->insert(__pos1, __str._M_data()
			    + __str._M_check(__pos2, "basic_string::insert"),
			    __str._M_limit(__pos2, __n)); }

      














 
      basic_string&
      insert(size_type __pos, const _CharT* __s, size_type __n);

      













 
      basic_string&
      insert(size_type __pos, const _CharT* __s)
      {
	;
	return this->insert(__pos, __s, traits_type::length(__s));
      }

      














 
      basic_string&
      insert(size_type __pos, size_type __n, _CharT __c)
      { return _M_replace_aux(_M_check(__pos, "basic_string::insert"),
			      size_type(0), __n, __c); }

      










 
      iterator
      insert(iterator __p, _CharT __c)
      {
	;
	const size_type __pos = __p - _M_ibegin();
	_M_replace_aux(__pos, size_type(0), size_type(1), __c);
	_M_rep()->_M_set_leaked();
	return iterator(_M_data() + __pos);
      }

      












 
      basic_string&
      erase(size_type __pos = 0, size_type __n = npos)
      { 
	_M_mutate(_M_check(__pos, "basic_string::erase"),
		  _M_limit(__pos, __n), size_type(0));
	return *this;
      }

      






 
      iterator
      erase(iterator __position)
      {
	;
	const size_type __pos = __position - _M_ibegin();
	_M_mutate(__pos, size_type(1), size_type(0));
	_M_rep()->_M_set_leaked();
	return iterator(_M_data() + __pos);
      }

      







 
      iterator
      erase(iterator __first, iterator __last);
 
      














 
      basic_string&
      replace(size_type __pos, size_type __n, const basic_string& __str)
      { return this->replace(__pos, __n, __str._M_data(), __str.size()); }

      
















 
      basic_string&
      replace(size_type __pos1, size_type __n1, const basic_string& __str,
	      size_type __pos2, size_type __n2)
      { return this->replace(__pos1, __n1, __str._M_data()
			     + __str._M_check(__pos2, "basic_string::replace"),
			     __str._M_limit(__pos2, __n2)); }

      















 
      basic_string&
      replace(size_type __pos, size_type __n1, const _CharT* __s,
	      size_type __n2);

      













 
      basic_string&
      replace(size_type __pos, size_type __n1, const _CharT* __s)
      {
	;
	return this->replace(__pos, __n1, __s, traits_type::length(__s));
      }

      














 
      basic_string&
      replace(size_type __pos, size_type __n1, size_type __n2, _CharT __c)
      { return _M_replace_aux(_M_check(__pos, "basic_string::replace"),
			      _M_limit(__pos, __n1), __n2, __c); }

      











 
      basic_string&
      replace(iterator __i1, iterator __i2, const basic_string& __str)
      { return this->replace(__i1, __i2, __str._M_data(), __str.size()); }

      












 
      basic_string&
      replace(iterator __i1, iterator __i2, const _CharT* __s, size_type __n)
      {
	;
	return this->replace(__i1 - _M_ibegin(), __i2 - __i1, __s, __n);
      }

      











 
      basic_string&
      replace(iterator __i1, iterator __i2, const _CharT* __s)
      {
	;
	return this->replace(__i1, __i2, __s, traits_type::length(__s));
      }

      












 
      basic_string&
      replace(iterator __i1, iterator __i2, size_type __n, _CharT __c)
      {
	;
	return _M_replace_aux(__i1 - _M_ibegin(), __i2 - __i1, __n, __c);
      }

      












 
      template<class _InputIterator>
        basic_string&
        replace(iterator __i1, iterator __i2,
		_InputIterator __k1, _InputIterator __k2)
        {
	  ;
	  ;
	  typedef typename std::__is_integer<_InputIterator>::__type _Integral;
	  return _M_replace_dispatch(__i1, __i2, __k1, __k2, _Integral());
	}

      
      
      basic_string&
      replace(iterator __i1, iterator __i2, _CharT* __k1, _CharT* __k2)
      {
	;
	;
	return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
			     __k1, __k2 - __k1);
      }

      basic_string&
      replace(iterator __i1, iterator __i2,
	      const _CharT* __k1, const _CharT* __k2)
      {
	;
	;
	return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
			     __k1, __k2 - __k1);
      }

      basic_string&
      replace(iterator __i1, iterator __i2, iterator __k1, iterator __k2)
      {
	;
	;
	return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
			     __k1.base(), __k2 - __k1);
      }

      basic_string&
      replace(iterator __i1, iterator __i2,
	      const_iterator __k1, const_iterator __k2)
      {
	;
	;
	return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
			     __k1.base(), __k2 - __k1);
      }
      

    private:
      template<class _Integer>
	basic_string&
	_M_replace_dispatch(iterator __i1, iterator __i2, _Integer __n,
			    _Integer __val, __true_type)
        { return _M_replace_aux(__i1 - _M_ibegin(), __i2 - __i1, __n, __val); }

      template<class _InputIterator>
	basic_string&
	_M_replace_dispatch(iterator __i1, iterator __i2, _InputIterator __k1,
			    _InputIterator __k2, __false_type);

      basic_string&
      _M_replace_aux(size_type __pos1, size_type __n1, size_type __n2,
		     _CharT __c);

      basic_string&
      _M_replace_safe(size_type __pos1, size_type __n1, const _CharT* __s,
		      size_type __n2);

      
      
      template<class _InIterator>
        static _CharT*
        _S_construct_aux(_InIterator __beg, _InIterator __end,
			 const _Alloc& __a, __false_type)
	{
          typedef typename iterator_traits<_InIterator>::iterator_category _Tag;
          return _S_construct(__beg, __end, __a, _Tag());
	}

      
      
      template<class _Integer>
        static _CharT*
        _S_construct_aux(_Integer __beg, _Integer __end,
			 const _Alloc& __a, __true_type)
        { return _S_construct_aux_2(static_cast<size_type>(__beg),
				    __end, __a); }

      static _CharT*
      _S_construct_aux_2(size_type __req, _CharT __c, const _Alloc& __a)
      { return _S_construct(__req, __c, __a); }

      template<class _InIterator>
        static _CharT*
        _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a)
	{
	  typedef typename std::__is_integer<_InIterator>::__type _Integral;
	  return _S_construct_aux(__beg, __end, __a, _Integral());
        }

      
      template<class _InIterator>
        static _CharT*
         _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a,
		      input_iterator_tag);

      
      
      template<class _FwdIterator>
        static _CharT*
        _S_construct(_FwdIterator __beg, _FwdIterator __end, const _Alloc& __a,
		     forward_iterator_tag);

      static _CharT*
      _S_construct(size_type __req, _CharT __c, const _Alloc& __a);

    public:

      









 
      size_type
      copy(_CharT* __s, size_type __n, size_type __pos = 0) const;

      





 
      void
      swap(basic_string& __s);

      
      




 
      const _CharT*
      c_str() const
      { return _M_data(); }

      




 
      const _CharT*
      data() const
      { return _M_data(); }

      

 
      allocator_type
      get_allocator() const
      { return _M_dataplus; }

      









 
      size_type
      find(const _CharT* __s, size_type __pos, size_type __n) const;

      








 
      size_type
      find(const basic_string& __str, size_type __pos = 0) const
      { return this->find(__str.data(), __pos, __str.size()); }

      








 
      size_type
      find(const _CharT* __s, size_type __pos = 0) const
      {
	;
	return this->find(__s, __pos, traits_type::length(__s));
      }

      








 
      size_type
      find(_CharT __c, size_type __pos = 0) const;

      








 
      size_type
      rfind(const basic_string& __str, size_type __pos = npos) const
      { return this->rfind(__str.data(), __pos, __str.size()); }

      









 
      size_type
      rfind(const _CharT* __s, size_type __pos, size_type __n) const;

      








 
      size_type
      rfind(const _CharT* __s, size_type __pos = npos) const
      {
	;
	return this->rfind(__s, __pos, traits_type::length(__s));
      }

      








 
      size_type
      rfind(_CharT __c, size_type __pos = npos) const;

      








 
      size_type
      find_first_of(const basic_string& __str, size_type __pos = 0) const
      { return this->find_first_of(__str.data(), __pos, __str.size()); }

      









 
      size_type
      find_first_of(const _CharT* __s, size_type __pos, size_type __n) const;

      








 
      size_type
      find_first_of(const _CharT* __s, size_type __pos = 0) const
      {
	;
	return this->find_first_of(__s, __pos, traits_type::length(__s));
      }

      










 
      size_type
      find_first_of(_CharT __c, size_type __pos = 0) const
      { return this->find(__c, __pos); }

      








 
      size_type
      find_last_of(const basic_string& __str, size_type __pos = npos) const
      { return this->find_last_of(__str.data(), __pos, __str.size()); }

      









 
      size_type
      find_last_of(const _CharT* __s, size_type __pos, size_type __n) const;

      








 
      size_type
      find_last_of(const _CharT* __s, size_type __pos = npos) const
      {
	;
	return this->find_last_of(__s, __pos, traits_type::length(__s));
      }

      










 
      size_type
      find_last_of(_CharT __c, size_type __pos = npos) const
      { return this->rfind(__c, __pos); }

      








 
      size_type
      find_first_not_of(const basic_string& __str, size_type __pos = 0) const
      { return this->find_first_not_of(__str.data(), __pos, __str.size()); }

      









 
      size_type
      find_first_not_of(const _CharT* __s, size_type __pos,
			size_type __n) const;

      








 
      size_type
      find_first_not_of(const _CharT* __s, size_type __pos = 0) const
      {
	;
	return this->find_first_not_of(__s, __pos, traits_type::length(__s));
      }

      








 
      size_type
      find_first_not_of(_CharT __c, size_type __pos = 0) const;

      








 
      size_type
      find_last_not_of(const basic_string& __str, size_type __pos = npos) const
      { return this->find_last_not_of(__str.data(), __pos, __str.size()); }

      










 
      size_type
      find_last_not_of(const _CharT* __s, size_type __pos,
		       size_type __n) const;
      








 
      size_type
      find_last_not_of(const _CharT* __s, size_type __pos = npos) const
      {
	;
	return this->find_last_not_of(__s, __pos, traits_type::length(__s));
      }

      








 
      size_type
      find_last_not_of(_CharT __c, size_type __pos = npos) const;

      










 
      basic_string
      substr(size_type __pos = 0, size_type __n = npos) const
      { return basic_string(*this,
			    _M_check(__pos, "basic_string::substr"), __n); }

      











 
      int
      compare(const basic_string& __str) const
      {
	const size_type __size = this->size();
	const size_type __osize = __str.size();
	const size_type __len = std::min(__size, __osize);

	int __r = traits_type::compare(_M_data(), __str.data(), __len);
	if (!__r)
	  __r = _S_compare(__size, __osize);
	return __r;
      }

      















 
      int
      compare(size_type __pos, size_type __n, const basic_string& __str) const;

      



















 
      int
      compare(size_type __pos1, size_type __n1, const basic_string& __str,
	      size_type __pos2, size_type __n2) const;

      












 
      int
      compare(const _CharT* __s) const;

      
      
      
















 
      int
      compare(size_type __pos, size_type __n1, const _CharT* __s) const;

      




















 
      int
      compare(size_type __pos, size_type __n1, const _CharT* __s,
	      size_type __n2) const;
  };

  
  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>
    operator+(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
	      const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    {
      basic_string<_CharT, _Traits, _Alloc> __str(__lhs);
      __str.append(__rhs);
      return __str;
    }

  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT,_Traits,_Alloc>
    operator+(const _CharT* __lhs,
	      const basic_string<_CharT,_Traits,_Alloc>& __rhs);

  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT,_Traits,_Alloc>
    operator+(_CharT __lhs, const basic_string<_CharT,_Traits,_Alloc>& __rhs);

  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_string<_CharT, _Traits, _Alloc>
    operator+(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
	     const _CharT* __rhs)
    {
      basic_string<_CharT, _Traits, _Alloc> __str(__lhs);
      __str.append(__rhs);
      return __str;
    }

  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_string<_CharT, _Traits, _Alloc>
    operator+(const basic_string<_CharT, _Traits, _Alloc>& __lhs, _CharT __rhs)
    {
      typedef basic_string<_CharT, _Traits, _Alloc>	__string_type;
      typedef typename __string_type::size_type		__size_type;
      __string_type __str(__lhs);
      __str.append(__size_type(1), __rhs);
      return __str;
    }


  
  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator==(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
	       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) == 0; }

  template<typename _CharT>
    inline
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value, bool>::__type
    operator==(const basic_string<_CharT>& __lhs,
	       const basic_string<_CharT>& __rhs)
    { return (__lhs.size() == __rhs.size()
	      && !std::char_traits<_CharT>::compare(__lhs.data(), __rhs.data(),
						    __lhs.size())); }

  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator==(const _CharT* __lhs,
	       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) == 0; }

  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator==(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
	       const _CharT* __rhs)
    { return __lhs.compare(__rhs) == 0; }

  
  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator!=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
	       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return !(__lhs == __rhs); }

  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator!=(const _CharT* __lhs,
	       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return !(__lhs == __rhs); }

  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator!=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
	       const _CharT* __rhs)
    { return !(__lhs == __rhs); }

  
  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
	      const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) < 0; }

  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
	      const _CharT* __rhs)
    { return __lhs.compare(__rhs) < 0; }

  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<(const _CharT* __lhs,
	      const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) > 0; }

  
  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
	      const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) > 0; }

  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
	      const _CharT* __rhs)
    { return __lhs.compare(__rhs) > 0; }

  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>(const _CharT* __lhs,
	      const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) < 0; }

  
  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
	       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) <= 0; }

  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
	       const _CharT* __rhs)
    { return __lhs.compare(__rhs) <= 0; }

  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<=(const _CharT* __lhs,
	       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) >= 0; }

  
  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
	       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) >= 0; }

  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
	       const _CharT* __rhs)
    { return __lhs.compare(__rhs) >= 0; }

  




 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>=(const _CharT* __lhs,
	     const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) <= 0; }

  





 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline void
    swap(basic_string<_CharT, _Traits, _Alloc>& __lhs,
	 basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { __lhs.swap(__rhs); }

  









 
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __is,
	       basic_string<_CharT, _Traits, _Alloc>& __str);

  template<>
    basic_istream<char>&
    operator>>(basic_istream<char>& __is, basic_string<char>& __str);

  







 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os,
	       const basic_string<_CharT, _Traits, _Alloc>& __str)
    {
      
      
      return __ostream_insert(__os, __str.data(), __str.size());
    }

  











 
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    getline(basic_istream<_CharT, _Traits>& __is,
	    basic_string<_CharT, _Traits, _Alloc>& __str, _CharT __delim);

  











 
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_istream<_CharT, _Traits>&
    getline(basic_istream<_CharT, _Traits>& __is,
	    basic_string<_CharT, _Traits, _Alloc>& __str)
    { return getline(__is, __str, __is.widen('\n')); }

  template<>
    basic_istream<char>&
    getline(basic_istream<char>& __in, basic_string<char>& __str,
	    char __delim);

  template<>
    basic_istream<wchar_t>&
    getline(basic_istream<wchar_t>& __in, basic_string<wchar_t>& __str,
	    wchar_t __delim);


} 
































 











namespace std __attribute__ ((__visibility__ ("default")))
{


  template<typename _CharT, typename _Traits, typename _Alloc>
    const typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    _Rep::_S_max_size = (((npos - sizeof(_Rep_base))/sizeof(_CharT)) - 1) / 4;

  template<typename _CharT, typename _Traits, typename _Alloc>
    const _CharT
    basic_string<_CharT, _Traits, _Alloc>::
    _Rep::_S_terminal = _CharT();

  template<typename _CharT, typename _Traits, typename _Alloc>
    const typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::npos;

  
  
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::_Rep::_S_empty_rep_storage[
    (sizeof(_Rep_base) + sizeof(_CharT) + sizeof(size_type) - 1) /
      sizeof(size_type)];

  
  
  
  
  template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename _InIterator>
      _CharT*
      basic_string<_CharT, _Traits, _Alloc>::
      _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a,
		   input_iterator_tag)
      {
	if (__beg == __end && __a == _Alloc())
	  return _S_empty_rep()._M_refdata();
	
	_CharT __buf[128];
	size_type __len = 0;
	while (__beg != __end && __len < sizeof(__buf) / sizeof(_CharT))
	  {
	    __buf[__len++] = *__beg;
	    ++__beg;
	  }
	_Rep* __r = _Rep::_S_create(__len, size_type(0), __a);
	_M_copy(__r->_M_refdata(), __buf, __len);
	try
	  {
	    while (__beg != __end)
	      {
		if (__len == __r->_M_capacity)
		  {
		    
		    _Rep* __another = _Rep::_S_create(__len + 1, __len, __a);
		    _M_copy(__another->_M_refdata(), __r->_M_refdata(), __len);
		    __r->_M_destroy(__a);
		    __r = __another;
		  }
		__r->_M_refdata()[__len++] = *__beg;
		++__beg;
	      }
	  }
	catch(...)
	  {
	    __r->_M_destroy(__a);
	    throw;
	  }
	__r->_M_set_length_and_sharable(__len);
	return __r->_M_refdata();
      }

  template<typename _CharT, typename _Traits, typename _Alloc>
    template <typename _InIterator>
      _CharT*
      basic_string<_CharT, _Traits, _Alloc>::
      _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a,
		   forward_iterator_tag)
      {
	if (__beg == __end && __a == _Alloc())
	  return _S_empty_rep()._M_refdata();
	
	if (__gnu_cxx::__is_null_pointer(__beg) && __beg != __end)
	  __throw_logic_error(("basic_string::_S_construct null not valid"));

	const size_type __dnew = static_cast<size_type>(std::distance(__beg,
								      __end));
	
	_Rep* __r = _Rep::_S_create(__dnew, size_type(0), __a);
	try
	  { _S_copy_chars(__r->_M_refdata(), __beg, __end); }
	catch(...)
	  {
	    __r->_M_destroy(__a);
	    throw;
	  }
	__r->_M_set_length_and_sharable(__dnew);
	return __r->_M_refdata();
      }

  template<typename _CharT, typename _Traits, typename _Alloc>
    _CharT*
    basic_string<_CharT, _Traits, _Alloc>::
    _S_construct(size_type __n, _CharT __c, const _Alloc& __a)
    {
      if (__n == 0 && __a == _Alloc())
	return _S_empty_rep()._M_refdata();
      
      _Rep* __r = _Rep::_S_create(__n, size_type(0), __a);
      if (__n)
	_M_assign(__r->_M_refdata(), __n, __c);

      __r->_M_set_length_and_sharable(__n);
      return __r->_M_refdata();
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const basic_string& __str)
    : _M_dataplus(__str._M_rep()->_M_grab(_Alloc(__str.get_allocator()),
					  __str.get_allocator()),
		  __str.get_allocator())
    { }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const _Alloc& __a)
    : _M_dataplus(_S_construct(size_type(), _CharT(), __a), __a)
    { }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const basic_string& __str, size_type __pos, size_type __n)
    : _M_dataplus(_S_construct(__str._M_data()
			       + __str._M_check(__pos,
						"basic_string::basic_string"),
			       __str._M_data() + __str._M_limit(__pos, __n)
			       + __pos, _Alloc()), _Alloc())
    { }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const basic_string& __str, size_type __pos,
		 size_type __n, const _Alloc& __a)
    : _M_dataplus(_S_construct(__str._M_data()
			       + __str._M_check(__pos,
						"basic_string::basic_string"),
			       __str._M_data() + __str._M_limit(__pos, __n)
			       + __pos, __a), __a)
    { }

  
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const _CharT* __s, size_type __n, const _Alloc& __a)
    : _M_dataplus(_S_construct(__s, __s + __n, __a), __a)
    { }

  
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const _CharT* __s, const _Alloc& __a)
    : _M_dataplus(_S_construct(__s, __s ? __s + traits_type::length(__s) :
			       __s + npos, __a), __a)
    { }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(size_type __n, _CharT __c, const _Alloc& __a)
    : _M_dataplus(_S_construct(__n, __c, __a), __a)
    { }

  
  template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename _InputIterator>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(_InputIterator __beg, _InputIterator __end, const _Alloc& __a)
    : _M_dataplus(_S_construct(__beg, __end, __a), __a)
    { }


  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    assign(const basic_string& __str)
    {
      if (_M_rep() != __str._M_rep())
	{
	  
	  const allocator_type __a = this->get_allocator();
	  _CharT* __tmp = __str._M_rep()->_M_grab(__a, __str.get_allocator());
	  _M_rep()->_M_dispose(__a);
	  _M_data(__tmp);
	}
      return *this;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    assign(const _CharT* __s, size_type __n)
    {
      ;
      _M_check_length(this->size(), __n, "basic_string::assign");
      if (_M_disjunct(__s) || _M_rep()->_M_is_shared())
	return _M_replace_safe(size_type(0), this->size(), __s, __n);
      else
	{
	  
	  const size_type __pos = __s - _M_data();
	  if (__pos >= __n)
	    _M_copy(_M_data(), __s, __n);
	  else if (__pos)
	    _M_move(_M_data(), __s, __n);
	  _M_rep()->_M_set_length_and_sharable(__n);
	  return *this;
	}
     }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(size_type __n, _CharT __c)
    {
      if (__n)
	{
	  _M_check_length(size_type(0), __n, "basic_string::append");	  
	  const size_type __len = __n + this->size();
	  if (__len > this->capacity() || _M_rep()->_M_is_shared())
	    this->reserve(__len);
	  _M_assign(_M_data() + this->size(), __n, __c);
	  _M_rep()->_M_set_length_and_sharable(__len);
	}
      return *this;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(const _CharT* __s, size_type __n)
    {
      ;
      if (__n)
	{
	  _M_check_length(size_type(0), __n, "basic_string::append");
	  const size_type __len = __n + this->size();
	  if (__len > this->capacity() || _M_rep()->_M_is_shared())
	    {
	      if (_M_disjunct(__s))
		this->reserve(__len);
	      else
		{
		  const size_type __off = __s - _M_data();
		  this->reserve(__len);
		  __s = _M_data() + __off;
		}
	    }
	  _M_copy(_M_data() + this->size(), __s, __n);
	  _M_rep()->_M_set_length_and_sharable(__len);
	}
      return *this;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(const basic_string& __str)
    {
      const size_type __size = __str.size();
      if (__size)
	{
	  const size_type __len = __size + this->size();
	  if (__len > this->capacity() || _M_rep()->_M_is_shared())
	    this->reserve(__len);
	  _M_copy(_M_data() + this->size(), __str._M_data(), __size);
	  _M_rep()->_M_set_length_and_sharable(__len);
	}
      return *this;
    }    

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(const basic_string& __str, size_type __pos, size_type __n)
    {
      __str._M_check(__pos, "basic_string::append");
      __n = __str._M_limit(__pos, __n);
      if (__n)
	{
	  const size_type __len = __n + this->size();
	  if (__len > this->capacity() || _M_rep()->_M_is_shared())
	    this->reserve(__len);
	  _M_copy(_M_data() + this->size(), __str._M_data() + __pos, __n);
	  _M_rep()->_M_set_length_and_sharable(__len);	  
	}
      return *this;
    }

   template<typename _CharT, typename _Traits, typename _Alloc>
     basic_string<_CharT, _Traits, _Alloc>&
     basic_string<_CharT, _Traits, _Alloc>::
     insert(size_type __pos, const _CharT* __s, size_type __n)
     {
       ;
       _M_check(__pos, "basic_string::insert");
       _M_check_length(size_type(0), __n, "basic_string::insert");
       if (_M_disjunct(__s) || _M_rep()->_M_is_shared())
         return _M_replace_safe(__pos, size_type(0), __s, __n);
       else
         {
           
           const size_type __off = __s - _M_data();
           _M_mutate(__pos, 0, __n);
           __s = _M_data() + __off;
           _CharT* __p = _M_data() + __pos;
           if (__s  + __n <= __p)
             _M_copy(__p, __s, __n);
           else if (__s >= __p)
             _M_copy(__p, __s + __n, __n);
           else
             {
	       const size_type __nleft = __p - __s;
               _M_copy(__p, __s, __nleft);
               _M_copy(__p + __nleft, __p + __n, __n - __nleft);
             }
           return *this;
         }
     }

   template<typename _CharT, typename _Traits, typename _Alloc>
     typename basic_string<_CharT, _Traits, _Alloc>::iterator
     basic_string<_CharT, _Traits, _Alloc>::
     erase(iterator __first, iterator __last)
     {
       ;

       
       
       
       const size_type __size = __last - __first;
       if (__size)
	 {
	   const size_type __pos = __first - _M_ibegin();
	   _M_mutate(__pos, __size, size_type(0));
	   _M_rep()->_M_set_leaked();
	   return iterator(_M_data() + __pos);
	 }
       else
	 return __first;
     }

   template<typename _CharT, typename _Traits, typename _Alloc>
     basic_string<_CharT, _Traits, _Alloc>&
     basic_string<_CharT, _Traits, _Alloc>::
     replace(size_type __pos, size_type __n1, const _CharT* __s,
	     size_type __n2)
     {
       ;
       _M_check(__pos, "basic_string::replace");
       __n1 = _M_limit(__pos, __n1);
       _M_check_length(__n1, __n2, "basic_string::replace");
       bool __left;
       if (_M_disjunct(__s) || _M_rep()->_M_is_shared())
         return _M_replace_safe(__pos, __n1, __s, __n2);
       else if ((__left = __s + __n2 <= _M_data() + __pos)
		|| _M_data() + __pos + __n1 <= __s)
	 {
	   
	   size_type __off = __s - _M_data();
	   __left ? __off : (__off += __n2 - __n1);
	   _M_mutate(__pos, __n1, __n2);
	   _M_copy(_M_data() + __pos, _M_data() + __off, __n2);
	   return *this;
	 }
       else
	 {
	   
	   const basic_string __tmp(__s, __n2);
	   return _M_replace_safe(__pos, __n1, __tmp._M_data(), __n2);
	 }
     }

  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::_Rep::
    _M_destroy(const _Alloc& __a) throw ()
    {
      const size_type __size = sizeof(_Rep_base) +
	                       (this->_M_capacity + 1) * sizeof(_CharT);
      _Raw_bytes_alloc(__a).deallocate(reinterpret_cast<char*>(this), __size);
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    _M_leak_hard()
    {
      if (_M_rep() == &_S_empty_rep())
	return;
      if (_M_rep()->_M_is_shared())
	_M_mutate(0, 0, 0);
      _M_rep()->_M_set_leaked();
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    _M_mutate(size_type __pos, size_type __len1, size_type __len2)
    {
      const size_type __old_size = this->size();
      const size_type __new_size = __old_size + __len2 - __len1;
      const size_type __how_much = __old_size - __pos - __len1;

      if (__new_size > this->capacity() || _M_rep()->_M_is_shared())
	{
	  
	  const allocator_type __a = get_allocator();
	  _Rep* __r = _Rep::_S_create(__new_size, this->capacity(), __a);

	  if (__pos)
	    _M_copy(__r->_M_refdata(), _M_data(), __pos);
	  if (__how_much)
	    _M_copy(__r->_M_refdata() + __pos + __len2,
		    _M_data() + __pos + __len1, __how_much);

	  _M_rep()->_M_dispose(__a);
	  _M_data(__r->_M_refdata());
	}
      else if (__how_much && __len1 != __len2)
	{
	  
	  _M_move(_M_data() + __pos + __len2,
		  _M_data() + __pos + __len1, __how_much);
	}
      _M_rep()->_M_set_length_and_sharable(__new_size);
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    reserve(size_type __res)
    {
      if (__res != this->capacity() || _M_rep()->_M_is_shared())
        {
	  
	  if (__res < this->size())
	    __res = this->size();
	  const allocator_type __a = get_allocator();
	  _CharT* __tmp = _M_rep()->_M_clone(__a, __res - this->size());
	  _M_rep()->_M_dispose(__a);
	  _M_data(__tmp);
        }
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    swap(basic_string& __s)
    {
      if (_M_rep()->_M_is_leaked())
	_M_rep()->_M_set_sharable();
      if (__s._M_rep()->_M_is_leaked())
	__s._M_rep()->_M_set_sharable();
      if (this->get_allocator() == __s.get_allocator())
	{
	  _CharT* __tmp = _M_data();
	  _M_data(__s._M_data());
	  __s._M_data(__tmp);
	}
      
      else
	{
	  const basic_string __tmp1(_M_ibegin(), _M_iend(),
				    __s.get_allocator());
	  const basic_string __tmp2(__s._M_ibegin(), __s._M_iend(),
				    this->get_allocator());
	  *this = __tmp2;
	  __s = __tmp1;
	}
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::_Rep*
    basic_string<_CharT, _Traits, _Alloc>::_Rep::
    _S_create(size_type __capacity, size_type __old_capacity,
	      const _Alloc& __alloc)
    {
      
      
      if (__capacity > _S_max_size)
	__throw_length_error(("basic_string::_S_create"));

      
      
      

      
      
      
      
      
      
      
      
      

      
      
      
      
      
      
      
      
      
      const size_type __pagesize = 4096;
      const size_type __malloc_header_size = 4 * sizeof(void*);

      
      
      
      
      
      
      if (__capacity > __old_capacity && __capacity < 2 * __old_capacity)
	__capacity = 2 * __old_capacity;

      
      
      
      size_type __size = (__capacity + 1) * sizeof(_CharT) + sizeof(_Rep);

      const size_type __adj_size = __size + __malloc_header_size;
      if (__adj_size > __pagesize && __capacity > __old_capacity)
	{
	  const size_type __extra = __pagesize - __adj_size % __pagesize;
	  __capacity += __extra / sizeof(_CharT);
	  
	  if (__capacity > _S_max_size)
	    __capacity = _S_max_size;
	  __size = (__capacity + 1) * sizeof(_CharT) + sizeof(_Rep);
	}

      
      
      void* __place = _Raw_bytes_alloc(__alloc).allocate(__size);
      _Rep *__p = new (__place) _Rep;
      __p->_M_capacity = __capacity;
      
      
      
      
      
      
      
      __p->_M_set_sharable();
      return __p;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    _CharT*
    basic_string<_CharT, _Traits, _Alloc>::_Rep::
    _M_clone(const _Alloc& __alloc, size_type __res)
    {
      
      const size_type __requested_cap = this->_M_length + __res;
      _Rep* __r = _Rep::_S_create(__requested_cap, this->_M_capacity,
				  __alloc);
      if (this->_M_length)
	_M_copy(__r->_M_refdata(), _M_refdata(), this->_M_length);

      __r->_M_set_length_and_sharable(this->_M_length);
      return __r->_M_refdata();
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    resize(size_type __n, _CharT __c)
    {
      const size_type __size = this->size();
      _M_check_length(__size, __n, "basic_string::resize");
      if (__size < __n)
	this->append(__n - __size, __c);
      else if (__n < __size)
	this->erase(__n);
      
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename _InputIterator>
      basic_string<_CharT, _Traits, _Alloc>&
      basic_string<_CharT, _Traits, _Alloc>::
      _M_replace_dispatch(iterator __i1, iterator __i2, _InputIterator __k1,
			  _InputIterator __k2, __false_type)
      {
	const basic_string __s(__k1, __k2);
	const size_type __n1 = __i2 - __i1;
	_M_check_length(__n1, __s.size(), "basic_string::_M_replace_dispatch");
	return _M_replace_safe(__i1 - _M_ibegin(), __n1, __s._M_data(),
			       __s.size());
      }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    _M_replace_aux(size_type __pos1, size_type __n1, size_type __n2,
		   _CharT __c)
    {
      _M_check_length(__n1, __n2, "basic_string::_M_replace_aux");
      _M_mutate(__pos1, __n1, __n2);
      if (__n2)
	_M_assign(_M_data() + __pos1, __n2, __c);
      return *this;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    _M_replace_safe(size_type __pos1, size_type __n1, const _CharT* __s,
		    size_type __n2)
    {
      _M_mutate(__pos1, __n1, __n2);
      if (__n2)
	_M_copy(_M_data() + __pos1, __s, __n2);
      return *this;
    }
   
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>
    operator+(const _CharT* __lhs,
	      const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    {
      ;
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __string_type::size_type	  __size_type;
      const __size_type __len = _Traits::length(__lhs);
      __string_type __str;
      __str.reserve(__len + __rhs.size());
      __str.append(__lhs, __len);
      __str.append(__rhs);
      return __str;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>
    operator+(_CharT __lhs, const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    {
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __string_type::size_type	  __size_type;
      __string_type __str;
      const __size_type __len = __rhs.size();
      __str.reserve(__len + 1);
      __str.append(__size_type(1), __lhs);
      __str.append(__rhs);
      return __str;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    copy(_CharT* __s, size_type __n, size_type __pos) const
    {
      _M_check(__pos, "basic_string::copy");
      __n = _M_limit(__pos, __n);
      ;
      if (__n)
	_M_copy(__s, _M_data() + __pos, __n);
      
      return __n;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      const size_type __size = this->size();
      const _CharT* __data = _M_data();

      if (__n == 0)
	return __pos <= __size ? __pos : npos;

      if (__n <= __size)
	{
	  for (; __pos <= __size - __n; ++__pos)
	    if (traits_type::eq(__data[__pos], __s[0])
		&& traits_type::compare(__data + __pos + 1,
					__s + 1, __n - 1) == 0)
	      return __pos;
	}
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find(_CharT __c, size_type __pos) const
    {
      size_type __ret = npos;
      const size_type __size = this->size();
      if (__pos < __size)
	{
	  const _CharT* __data = _M_data();
	  const size_type __n = __size - __pos;
	  const _CharT* __p = traits_type::find(__data + __pos, __n, __c);
	  if (__p)
	    __ret = __p - __data;
	}
      return __ret;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    rfind(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      const size_type __size = this->size();
      if (__n <= __size)
	{
	  __pos = std::min(size_type(__size - __n), __pos);
	  const _CharT* __data = _M_data();
	  do
	    {
	      if (traits_type::compare(__data + __pos, __s, __n) == 0)
		return __pos;
	    }
	  while (__pos-- > 0);
	}
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    rfind(_CharT __c, size_type __pos) const
    {
      size_type __size = this->size();
      if (__size)
	{
	  if (--__size > __pos)
	    __size = __pos;
	  for (++__size; __size-- > 0; )
	    if (traits_type::eq(_M_data()[__size], __c))
	      return __size;
	}
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_first_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      for (; __n && __pos < this->size(); ++__pos)
	{
	  const _CharT* __p = traits_type::find(__s, __n, _M_data()[__pos]);
	  if (__p)
	    return __pos;
	}
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_last_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      size_type __size = this->size();
      if (__size && __n)
	{
	  if (--__size > __pos)
	    __size = __pos;
	  do
	    {
	      if (traits_type::find(__s, __n, _M_data()[__size]))
		return __size;
	    }
	  while (__size-- != 0);
	}
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_first_not_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      for (; __pos < this->size(); ++__pos)
	if (!traits_type::find(__s, __n, _M_data()[__pos]))
	  return __pos;
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_first_not_of(_CharT __c, size_type __pos) const
    {
      for (; __pos < this->size(); ++__pos)
	if (!traits_type::eq(_M_data()[__pos], __c))
	  return __pos;
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_last_not_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      size_type __size = this->size();
      if (__size)
	{
	  if (--__size > __pos)
	    __size = __pos;
	  do
	    {
	      if (!traits_type::find(__s, __n, _M_data()[__size]))
		return __size;
	    }
	  while (__size--);
	}
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_last_not_of(_CharT __c, size_type __pos) const
    {
      size_type __size = this->size();
      if (__size)
	{
	  if (--__size > __pos)
	    __size = __pos;
	  do
	    {
	      if (!traits_type::eq(_M_data()[__size], __c))
		return __size;
	    }
	  while (__size--);
	}
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string<_CharT, _Traits, _Alloc>::
    compare(size_type __pos, size_type __n, const basic_string& __str) const
    {
      _M_check(__pos, "basic_string::compare");
      __n = _M_limit(__pos, __n);
      const size_type __osize = __str.size();
      const size_type __len = std::min(__n, __osize);
      int __r = traits_type::compare(_M_data() + __pos, __str.data(), __len);
      if (!__r)
	__r = _S_compare(__n, __osize);
      return __r;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string<_CharT, _Traits, _Alloc>::
    compare(size_type __pos1, size_type __n1, const basic_string& __str,
	    size_type __pos2, size_type __n2) const
    {
      _M_check(__pos1, "basic_string::compare");
      __str._M_check(__pos2, "basic_string::compare");
      __n1 = _M_limit(__pos1, __n1);
      __n2 = __str._M_limit(__pos2, __n2);
      const size_type __len = std::min(__n1, __n2);
      int __r = traits_type::compare(_M_data() + __pos1,
				     __str.data() + __pos2, __len);
      if (!__r)
	__r = _S_compare(__n1, __n2);
      return __r;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string<_CharT, _Traits, _Alloc>::
    compare(const _CharT* __s) const
    {
      ;
      const size_type __size = this->size();
      const size_type __osize = traits_type::length(__s);
      const size_type __len = std::min(__size, __osize);
      int __r = traits_type::compare(_M_data(), __s, __len);
      if (!__r)
	__r = _S_compare(__size, __osize);
      return __r;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string <_CharT, _Traits, _Alloc>::
    compare(size_type __pos, size_type __n1, const _CharT* __s) const
    {
      ;
      _M_check(__pos, "basic_string::compare");
      __n1 = _M_limit(__pos, __n1);
      const size_type __osize = traits_type::length(__s);
      const size_type __len = std::min(__n1, __osize);
      int __r = traits_type::compare(_M_data() + __pos, __s, __len);
      if (!__r)
	__r = _S_compare(__n1, __osize);
      return __r;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string <_CharT, _Traits, _Alloc>::
    compare(size_type __pos, size_type __n1, const _CharT* __s,
	    size_type __n2) const
    {
      ;
      _M_check(__pos, "basic_string::compare");
      __n1 = _M_limit(__pos, __n1);
      const size_type __len = std::min(__n1, __n2);
      int __r = traits_type::compare(_M_data() + __pos, __s, __len);
      if (!__r)
	__r = _S_compare(__n1, __n2);
      return __r;
    }

  
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in,
	       basic_string<_CharT, _Traits, _Alloc>& __str)
    {
      typedef basic_istream<_CharT, _Traits>		__istream_type;
      typedef basic_string<_CharT, _Traits, _Alloc>	__string_type;
      typedef typename __istream_type::ios_base         __ios_base;
      typedef typename __istream_type::int_type		__int_type;
      typedef typename __string_type::size_type		__size_type;
      typedef ctype<_CharT>				__ctype_type;
      typedef typename __ctype_type::ctype_base         __ctype_base;

      __size_type __extracted = 0;
      typename __ios_base::iostate __err = __ios_base::goodbit;
      typename __istream_type::sentry __cerb(__in, false);
      if (__cerb)
	{
	  try
	    {
	      
	      __str.erase();
	      _CharT __buf[128];
	      __size_type __len = 0;	      
	      const streamsize __w = __in.width();
	      const __size_type __n = __w > 0 ? static_cast<__size_type>(__w)
		                              : __str.max_size();
	      const __ctype_type& __ct = use_facet<__ctype_type>(__in.getloc());
	      const __int_type __eof = _Traits::eof();
	      __int_type __c = __in.rdbuf()->sgetc();

	      while (__extracted < __n
		     && !_Traits::eq_int_type(__c, __eof)
		     && !__ct.is(__ctype_base::space,
				 _Traits::to_char_type(__c)))
		{
		  if (__len == sizeof(__buf) / sizeof(_CharT))
		    {
		      __str.append(__buf, sizeof(__buf) / sizeof(_CharT));
		      __len = 0;
		    }
		  __buf[__len++] = _Traits::to_char_type(__c);
		  ++__extracted;
		  __c = __in.rdbuf()->snextc();
		}
	      __str.append(__buf, __len);

	      if (_Traits::eq_int_type(__c, __eof))
		__err |= __ios_base::eofbit;
	      __in.width(0);
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      __in._M_setstate(__ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    {
	      
	      
	      
	      __in._M_setstate(__ios_base::badbit);
	    }
	}
      
      if (!__extracted)
	__err |= __ios_base::failbit;
      if (__err)
	__in.setstate(__err);
      return __in;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    getline(basic_istream<_CharT, _Traits>& __in,
	    basic_string<_CharT, _Traits, _Alloc>& __str, _CharT __delim)
    {
      typedef basic_istream<_CharT, _Traits>		__istream_type;
      typedef basic_string<_CharT, _Traits, _Alloc>	__string_type;
      typedef typename __istream_type::ios_base         __ios_base;
      typedef typename __istream_type::int_type		__int_type;
      typedef typename __string_type::size_type		__size_type;

      __size_type __extracted = 0;
      const __size_type __n = __str.max_size();
      typename __ios_base::iostate __err = __ios_base::goodbit;
      typename __istream_type::sentry __cerb(__in, true);
      if (__cerb)
	{
	  try
	    {
	      __str.erase();
	      const __int_type __idelim = _Traits::to_int_type(__delim);
	      const __int_type __eof = _Traits::eof();
	      __int_type __c = __in.rdbuf()->sgetc();

	      while (__extracted < __n
		     && !_Traits::eq_int_type(__c, __eof)
		     && !_Traits::eq_int_type(__c, __idelim))
		{
		  __str += _Traits::to_char_type(__c);
		  ++__extracted;
		  __c = __in.rdbuf()->snextc();
		}

	      if (_Traits::eq_int_type(__c, __eof))
		__err |= __ios_base::eofbit;
	      else if (_Traits::eq_int_type(__c, __idelim))
		{
		  ++__extracted;		  
		  __in.rdbuf()->sbumpc();
		}
	      else
		__err |= __ios_base::failbit;
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      __in._M_setstate(__ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    {
	      
	      
	      
	      __in._M_setstate(__ios_base::badbit);
	    }
	}
      if (!__extracted)
	__err |= __ios_base::failbit;
      if (__err)
	__in.setstate(__err);
      return __in;
    }

  
  
  extern template class basic_string<char>;
  extern template
    basic_istream<char>&
    operator>>(basic_istream<char>&, string&);
  extern template
    basic_ostream<char>&
    operator<<(basic_ostream<char>&, const string&);
  extern template
    basic_istream<char>&
    getline(basic_istream<char>&, string&, char);
  extern template
    basic_istream<char>&
    getline(basic_istream<char>&, string&);

  extern template class basic_string<wchar_t>;
  extern template
    basic_istream<wchar_t>&
    operator>>(basic_istream<wchar_t>&, wstring&);
  extern template
    basic_ostream<wchar_t>&
    operator<<(basic_ostream<wchar_t>&, const wstring&);
  extern template
    basic_istream<wchar_t>&
    getline(basic_istream<wchar_t>&, wstring&, wchar_t);
  extern template
    basic_istream<wchar_t>&
    getline(basic_istream<wchar_t>&, wstring&);


} 



namespace std __attribute__ ((__visibility__ ("default")))
{


  
  












 
  class locale
  {
  public:
    
    
    typedef int	category;

    
    class facet;
    class id;
    class _Impl;

    friend class facet;
    friend class _Impl;

    template<typename _Facet>
      friend bool
      has_facet(const locale&) throw();

    template<typename _Facet>
      friend const _Facet&
      use_facet(const locale&);

    template<typename _Cache>
      friend struct __use_cache;

    
    







 
    static const category none		= 0;
    static const category ctype		= 1L << 0;
    static const category numeric	= 1L << 1;
    static const category collate	= 1L << 2;
    static const category time		= 1L << 3;
    static const category monetary	= 1L << 4;
    static const category messages	= 1L << 5;
    static const category all		= (ctype | numeric | collate |
					   time  | monetary | messages);
    

    

    




 
    locale() throw();

    





 
    locale(const locale& __other) throw();

    






 
    explicit
    locale(const char* __s);

    










 
    locale(const locale& __base, const char* __s, category __cat);

    









 
    locale(const locale& __base, const locale& __add, category __cat);

    








 
    template<typename _Facet>
      locale(const locale& __other, _Facet* __f);

    
    ~locale() throw();

    






 
    const locale&
    operator=(const locale& __other) throw();

    










 
    template<typename _Facet>
      locale
      combine(const locale& __other) const;

    
    


 
    string
    name() const;

    





 
    bool
    operator==(const locale& __other) const throw();

    




 
    bool
    operator!=(const locale& __other) const throw()
    { return !(this->operator==(__other)); }

    













 
    template<typename _Char, typename _Traits, typename _Alloc>
      bool
      operator()(const basic_string<_Char, _Traits, _Alloc>& __s1,
		 const basic_string<_Char, _Traits, _Alloc>& __s2) const;

    
    








 
    static locale
    global(const locale&);

    

 
    static const locale&
    classic();

  private:
    
    _Impl*		_M_impl;

    
    static _Impl*       _S_classic;

    
    static _Impl*	_S_global;

    
    
    
    
    static const char* const* const _S_categories;

    
    
    
    
    
    
    
    
    
    
    enum { _S_categories_size = 6 + 0 };

    static __gthread_once_t _S_once;

    explicit
    locale(_Impl*) throw();

    static void
    _S_initialize();

    static void
    _S_initialize_once() throw();

    static category
    _S_normalize_category(category);

    void
    _M_coalesce(const locale& __base, const locale& __add, category __cat);
  };


  
  








 
  class locale::facet
  {
  private:
    friend class locale;
    friend class locale::_Impl;

    mutable _Atomic_word		_M_refcount;

    
    static __c_locale                   _S_c_locale;

    
    static const char			_S_c_name[2];

    static __gthread_once_t		_S_once;

    static void
    _S_initialize_once();

  protected:
    







 
    explicit
    facet(size_t __refs = 0) throw() : _M_refcount(__refs ? 1 : 0)
    { }

    
    virtual
    ~facet();

    static void
    _S_create_c_locale(__c_locale& __cloc, const char* __s,
		       __c_locale __old = 0);

    static __c_locale
    _S_clone_c_locale(__c_locale& __cloc) throw();

    static void
    _S_destroy_c_locale(__c_locale& __cloc);

    static __c_locale
    _S_lc_ctype_c_locale(__c_locale __cloc, const char* __s);

    
    
    static __c_locale
    _S_get_c_locale();

    __attribute__ ((__const__)) static const char*
    _S_get_c_name() throw();

  private:
    void
    _M_add_reference() const throw()
    { __gnu_cxx::__atomic_add_dispatch(&_M_refcount, 1); }

    void
    _M_remove_reference() const throw()
    {
      
      ;
      if (__gnu_cxx::__exchange_and_add_dispatch(&_M_refcount, -1) == 1)
	{
          ;
	  try
	    { delete this; }
	  catch(...)
	    { }
	}
    }

    facet(const facet&);  

    facet&
    operator=(const facet&);  
  };


  
  








 
  class locale::id
  {
  private:
    friend class locale;
    friend class locale::_Impl;

    template<typename _Facet>
      friend const _Facet&
      use_facet(const locale&);

    template<typename _Facet>
      friend bool
      has_facet(const locale&) throw();

    
    
    
    mutable size_t		_M_index;

    
    static _Atomic_word		_S_refcount;

    void
    operator=(const id&);  

    id(const id&);  

  public:
    
    
    
    id() { }

    size_t
    _M_id() const throw();
  };


  
  class locale::_Impl
  {
  public:
    
    friend class locale;
    friend class locale::facet;

    template<typename _Facet>
      friend bool
      has_facet(const locale&) throw();

    template<typename _Facet>
      friend const _Facet&
      use_facet(const locale&);

    template<typename _Cache>
      friend struct __use_cache;

  private:
    
    _Atomic_word			_M_refcount;
    const facet**			_M_facets;
    size_t				_M_facets_size;
    const facet**			_M_caches;
    char**				_M_names;
    static const locale::id* const	_S_id_ctype[];
    static const locale::id* const	_S_id_numeric[];
    static const locale::id* const	_S_id_collate[];
    static const locale::id* const	_S_id_time[];
    static const locale::id* const	_S_id_monetary[];
    static const locale::id* const	_S_id_messages[];
    static const locale::id* const* const _S_facet_categories[];

    void
    _M_add_reference() throw()
    { __gnu_cxx::__atomic_add_dispatch(&_M_refcount, 1); }

    void
    _M_remove_reference() throw()
    {
      
      ;
      if (__gnu_cxx::__exchange_and_add_dispatch(&_M_refcount, -1) == 1)
	{
          ;
	  try
	    { delete this; }
	  catch(...)
	    { }
	}
    }

    _Impl(const _Impl&, size_t);
    _Impl(const char*, size_t);
    _Impl(size_t) throw();

   ~_Impl() throw();

    _Impl(const _Impl&);  

    void
    operator=(const _Impl&);  

    bool
    _M_check_same_name()
    {
      bool __ret = true;
      if (_M_names[1])
	
	for (size_t __i = 0; __ret && __i < _S_categories_size - 1; ++__i)
	  __ret = __builtin_strcmp(_M_names[__i], _M_names[__i + 1]) == 0;
      return __ret;
    }

    void
    _M_replace_categories(const _Impl*, category);

    void
    _M_replace_category(const _Impl*, const locale::id* const*);

    void
    _M_replace_facet(const _Impl*, const locale::id*);

    void
    _M_install_facet(const locale::id*, const facet*);

    template<typename _Facet>
      void
      _M_init_facet(_Facet* __facet)
      { _M_install_facet(&_Facet::id, __facet); }

    void
    _M_install_cache(const facet*, size_t);
  };


  









 
  template<typename _Facet>
    bool
    has_facet(const locale& __loc) throw();

  











 
  template<typename _Facet>
    const _Facet&
    use_facet(const locale& __loc);


  










 
  template<typename _CharT>
    class collate : public locale::facet
    {
    public:
      
      
      
      typedef _CharT			char_type;
      typedef basic_string<_CharT>	string_type;
      

    protected:
      
      
      __c_locale			_M_c_locale_collate;

    public:
      
      static locale::id			id;

      





 
      explicit
      collate(size_t __refs = 0)
      : facet(__refs), _M_c_locale_collate(_S_get_c_locale())
      { }

      







 
      explicit
      collate(__c_locale __cloc, size_t __refs = 0)
      : facet(__refs), _M_c_locale_collate(_S_clone_c_locale(__cloc))
      { }

      










 
      int
      compare(const _CharT* __lo1, const _CharT* __hi1,
	      const _CharT* __lo2, const _CharT* __hi2) const
      { return this->do_compare(__lo1, __hi1, __lo2, __hi2); }

      












 
      string_type
      transform(const _CharT* __lo, const _CharT* __hi) const
      { return this->do_transform(__lo, __hi); }

      








 
      long
      hash(const _CharT* __lo, const _CharT* __hi) const
      { return this->do_hash(__lo, __hi); }

      
      int
      _M_compare(const _CharT*, const _CharT*) const throw();

      size_t
      _M_transform(_CharT*, const _CharT*, size_t) const throw();

  protected:
      
      virtual
      ~collate()
      { _S_destroy_c_locale(_M_c_locale_collate); }

      










 
      virtual int
      do_compare(const _CharT* __lo1, const _CharT* __hi1,
		 const _CharT* __lo2, const _CharT* __hi2) const;

      










 
      virtual string_type
      do_transform(const _CharT* __lo, const _CharT* __hi) const;

      








 
      virtual long
      do_hash(const _CharT* __lo, const _CharT* __hi) const;
    };

  template<typename _CharT>
    locale::id collate<_CharT>::id;

  
  template<>
    int
    collate<char>::_M_compare(const char*, const char*) const throw();

  template<>
    size_t
    collate<char>::_M_transform(char*, const char*, size_t) const throw();

  template<>
    int
    collate<wchar_t>::_M_compare(const wchar_t*, const wchar_t*) const throw();

  template<>
    size_t
    collate<wchar_t>::_M_transform(wchar_t*, const wchar_t*, size_t) const throw();

  
  template<typename _CharT>
    class collate_byname : public collate<_CharT>
    {
    public:
      
      
      typedef _CharT               char_type;
      typedef basic_string<_CharT> string_type;
      

      explicit
      collate_byname(const char* __s, size_t __refs = 0)
      : collate<_CharT>(__refs)
      {
	if (__builtin_strcmp(__s, "C") != 0
	    && __builtin_strcmp(__s, "POSIX") != 0)
	  {
	    this->_S_destroy_c_locale(this->_M_c_locale_collate);
	    this->_S_create_c_locale(this->_M_c_locale_collate, __s);
	  }
      }

    protected:
      virtual
      ~collate_byname() { }
    };


} 




























 







namespace std __attribute__ ((__visibility__ ("default")))
{


  template<typename _Facet>
    locale::
    locale(const locale& __other, _Facet* __f)
    {
      _M_impl = new _Impl(*__other._M_impl, 1);

      try
	{ _M_impl->_M_install_facet(&_Facet::id, __f); }
      catch(...)
	{
	  _M_impl->_M_remove_reference();
	  throw;
	}
      delete [] _M_impl->_M_names[0];
      _M_impl->_M_names[0] = 0;   
    }

  template<typename _Facet>
    locale
    locale::
    combine(const locale& __other) const
    {
      _Impl* __tmp = new _Impl(*_M_impl, 1);
      try
	{
	  __tmp->_M_replace_facet(__other._M_impl, &_Facet::id);
	}
      catch(...)
	{
	  __tmp->_M_remove_reference();
	  throw;
	}
      return locale(__tmp);
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    bool
    locale::
    operator()(const basic_string<_CharT, _Traits, _Alloc>& __s1,
	       const basic_string<_CharT, _Traits, _Alloc>& __s2) const
    {
      typedef std::collate<_CharT> __collate_type;
      const __collate_type& __collate = use_facet<__collate_type>(*this);
      return (__collate.compare(__s1.data(), __s1.data() + __s1.length(),
				__s2.data(), __s2.data() + __s2.length()) < 0);
    }


  template<typename _Facet>
    bool
    has_facet(const locale& __loc) throw()
    {
      const size_t __i = _Facet::id._M_id();
      const locale::facet** __facets = __loc._M_impl->_M_facets;
      return (__i < __loc._M_impl->_M_facets_size
	      && dynamic_cast<const _Facet*>(__facets[__i]));
    }

  template<typename _Facet>
    const _Facet&
    use_facet(const locale& __loc)
    {
      const size_t __i = _Facet::id._M_id();
      const locale::facet** __facets = __loc._M_impl->_M_facets;
      if (__i >= __loc._M_impl->_M_facets_size || !__facets[__i])
        __throw_bad_cast();
      return dynamic_cast<const _Facet&>(*__facets[__i]);
    }


  
  template<typename _CharT>
    int
    collate<_CharT>::_M_compare(const _CharT*, const _CharT*) const throw ()
    { return 0; }

  
  template<typename _CharT>
    size_t
    collate<_CharT>::_M_transform(_CharT*, const _CharT*, size_t) const throw ()
    { return 0; }

  template<typename _CharT>
    int
    collate<_CharT>::
    do_compare(const _CharT* __lo1, const _CharT* __hi1,
	       const _CharT* __lo2, const _CharT* __hi2) const
    {
      
      
      const string_type __one(__lo1, __hi1);
      const string_type __two(__lo2, __hi2);

      const _CharT* __p = __one.c_str();
      const _CharT* __pend = __one.data() + __one.length();
      const _CharT* __q = __two.c_str();
      const _CharT* __qend = __two.data() + __two.length();

      
      
      
      for (;;)
	{
	  const int __res = _M_compare(__p, __q);
	  if (__res)
	    return __res;

	  __p += char_traits<_CharT>::length(__p);
	  __q += char_traits<_CharT>::length(__q);
	  if (__p == __pend && __q == __qend)
	    return 0;
	  else if (__p == __pend)
	    return -1;
	  else if (__q == __qend)
	    return 1;

	  __p++;
	  __q++;
	}
    }

  template<typename _CharT>
    typename collate<_CharT>::string_type
    collate<_CharT>::
    do_transform(const _CharT* __lo, const _CharT* __hi) const
    {
      string_type __ret;

      
      const string_type __str(__lo, __hi);

      const _CharT* __p = __str.c_str();
      const _CharT* __pend = __str.data() + __str.length();

      size_t __len = (__hi - __lo) * 2;

      _CharT* __c = new _CharT[__len];

      try
	{
	  
	  
	  
	  for (;;)
	    {
	      
	      size_t __res = _M_transform(__c, __p, __len);
	      
	      
	      if (__res >= __len)
		{
		  __len = __res + 1;
		  delete [] __c, __c = 0;
		  __c = new _CharT[__len];
		  __res = _M_transform(__c, __p, __len);
		}

	      __ret.append(__c, __res);
	      __p += char_traits<_CharT>::length(__p);
	      if (__p == __pend)
		break;

	      __p++;
	      __ret.push_back(_CharT());
	    }
	}
      catch(...)
	{
	  delete [] __c;
	  throw;
	}

      delete [] __c;

      return __ret;
    }

  template<typename _CharT>
    long
    collate<_CharT>::
    do_hash(const _CharT* __lo, const _CharT* __hi) const
    {
      unsigned long __val = 0;
      for (; __lo < __hi; ++__lo)
	__val =
	  *__lo + ((__val << 7)
		   | (__val >> (__gnu_cxx::__numeric_traits<unsigned long>::
				__digits - 7)));
      return static_cast<long>(__val);
    }

  
  
  extern template class collate<char>;
  extern template class collate_byname<char>;

  extern template
    const collate<char>&
    use_facet<collate<char> >(const locale&);

  extern template
    bool
    has_facet<collate<char> >(const locale&);

  extern template class collate<wchar_t>;
  extern template class collate_byname<wchar_t>;

  extern template
    const collate<wchar_t>&
    use_facet<collate<wchar_t> >(const locale&);

  extern template
    bool
    has_facet<collate<wchar_t> >(const locale&);


} 



namespace std __attribute__ ((__visibility__ ("default")))
{


  
  
  
  
  enum _Ios_Fmtflags 
    { 
      _S_boolalpha 	= 1L << 0,
      _S_dec 		= 1L << 1,
      _S_fixed 		= 1L << 2,
      _S_hex 		= 1L << 3,
      _S_internal 	= 1L << 4,
      _S_left 		= 1L << 5,
      _S_oct 		= 1L << 6,
      _S_right 		= 1L << 7,
      _S_scientific 	= 1L << 8,
      _S_showbase 	= 1L << 9,
      _S_showpoint 	= 1L << 10,
      _S_showpos 	= 1L << 11,
      _S_skipws 	= 1L << 12,
      _S_unitbuf 	= 1L << 13,
      _S_uppercase 	= 1L << 14,
      _S_adjustfield 	= _S_left | _S_right | _S_internal,
      _S_basefield 	= _S_dec | _S_oct | _S_hex,
      _S_floatfield 	= _S_scientific | _S_fixed,
      _S_ios_fmtflags_end = 1L << 16 
    };

  inline  _Ios_Fmtflags
  operator&(_Ios_Fmtflags __a, _Ios_Fmtflags __b)
  { return _Ios_Fmtflags(static_cast<int>(__a) & static_cast<int>(__b)); }

  inline  _Ios_Fmtflags
  operator|(_Ios_Fmtflags __a, _Ios_Fmtflags __b)
  { return _Ios_Fmtflags(static_cast<int>(__a) | static_cast<int>(__b)); }

  inline  _Ios_Fmtflags
  operator^(_Ios_Fmtflags __a, _Ios_Fmtflags __b)
  { return _Ios_Fmtflags(static_cast<int>(__a) ^ static_cast<int>(__b)); }

  inline  _Ios_Fmtflags
  operator~(_Ios_Fmtflags __a)
  { return _Ios_Fmtflags(~static_cast<int>(__a)); }

  inline const _Ios_Fmtflags&
  operator|=(_Ios_Fmtflags& __a, _Ios_Fmtflags __b)
  { return __a = __a | __b; }

  inline const _Ios_Fmtflags&
  operator&=(_Ios_Fmtflags& __a, _Ios_Fmtflags __b)
  { return __a = __a & __b; }

  inline const _Ios_Fmtflags&
  operator^=(_Ios_Fmtflags& __a, _Ios_Fmtflags __b)
  { return __a = __a ^ __b; }


  enum _Ios_Openmode 
    { 
      _S_app 		= 1L << 0,
      _S_ate 		= 1L << 1,
      _S_bin 		= 1L << 2,
      _S_in 		= 1L << 3,
      _S_out 		= 1L << 4,
      _S_trunc 		= 1L << 5,
      _S_ios_openmode_end = 1L << 16 
    };

  inline  _Ios_Openmode
  operator&(_Ios_Openmode __a, _Ios_Openmode __b)
  { return _Ios_Openmode(static_cast<int>(__a) & static_cast<int>(__b)); }

  inline  _Ios_Openmode
  operator|(_Ios_Openmode __a, _Ios_Openmode __b)
  { return _Ios_Openmode(static_cast<int>(__a) | static_cast<int>(__b)); }

  inline  _Ios_Openmode
  operator^(_Ios_Openmode __a, _Ios_Openmode __b)
  { return _Ios_Openmode(static_cast<int>(__a) ^ static_cast<int>(__b)); }

  inline  _Ios_Openmode
  operator~(_Ios_Openmode __a)
  { return _Ios_Openmode(~static_cast<int>(__a)); }

  inline const _Ios_Openmode&
  operator|=(_Ios_Openmode& __a, _Ios_Openmode __b)
  { return __a = __a | __b; }

  inline const _Ios_Openmode&
  operator&=(_Ios_Openmode& __a, _Ios_Openmode __b)
  { return __a = __a & __b; }

  inline const _Ios_Openmode&
  operator^=(_Ios_Openmode& __a, _Ios_Openmode __b)
  { return __a = __a ^ __b; }


  enum _Ios_Iostate
    { 
      _S_goodbit 		= 0,
      _S_badbit 		= 1L << 0,
      _S_eofbit 		= 1L << 1,
      _S_failbit		= 1L << 2,
      _S_ios_iostate_end = 1L << 16 
    };

  inline  _Ios_Iostate
  operator&(_Ios_Iostate __a, _Ios_Iostate __b)
  { return _Ios_Iostate(static_cast<int>(__a) & static_cast<int>(__b)); }

  inline  _Ios_Iostate
  operator|(_Ios_Iostate __a, _Ios_Iostate __b)
  { return _Ios_Iostate(static_cast<int>(__a) | static_cast<int>(__b)); }

  inline  _Ios_Iostate
  operator^(_Ios_Iostate __a, _Ios_Iostate __b)
  { return _Ios_Iostate(static_cast<int>(__a) ^ static_cast<int>(__b)); }

  inline  _Ios_Iostate
  operator~(_Ios_Iostate __a)
  { return _Ios_Iostate(~static_cast<int>(__a)); }

  inline const _Ios_Iostate&
  operator|=(_Ios_Iostate& __a, _Ios_Iostate __b)
  { return __a = __a | __b; }

  inline const _Ios_Iostate&
  operator&=(_Ios_Iostate& __a, _Ios_Iostate __b)
  { return __a = __a & __b; }

  inline const  _Ios_Iostate&
  operator^=(_Ios_Iostate& __a, _Ios_Iostate __b)
  { return __a = __a ^ __b; }


  enum _Ios_Seekdir 
    { 
      _S_beg = 0,
      _S_cur = 1,
      _S_end = 2,
      _S_ios_seekdir_end = 1L << 16 
    };

  
  







 
  class ios_base
  {
  public:

    




 
    class failure : public exception
    {
    public:
      
      
      explicit
      failure(const string& __str) throw();

      
      
      virtual
      ~failure() throw();

      virtual const char*
      what() const throw();

    private:
      string _M_msg;
    };

    
    























 
    typedef _Ios_Fmtflags fmtflags;

    
    static const fmtflags boolalpha =   _S_boolalpha;

    
    static const fmtflags dec =         _S_dec;

    
    static const fmtflags fixed =       _S_fixed;

    
    static const fmtflags hex =         _S_hex;

    
    
    
    static const fmtflags internal =    _S_internal;

    
    
    static const fmtflags left =        _S_left;

    
    static const fmtflags oct =         _S_oct;

    
    
    static const fmtflags right =       _S_right;

    
    static const fmtflags scientific =  _S_scientific;

    
    
    static const fmtflags showbase =    _S_showbase;

    
    
    static const fmtflags showpoint =   _S_showpoint;

    
    static const fmtflags showpos =     _S_showpos;

    
    static const fmtflags skipws =      _S_skipws;

    
    static const fmtflags unitbuf =     _S_unitbuf;

    
    
    static const fmtflags uppercase =   _S_uppercase;

    
    static const fmtflags adjustfield = _S_adjustfield;

    
    static const fmtflags basefield =   _S_basefield;

    
    static const fmtflags floatfield =  _S_floatfield;

    
    









 
    typedef _Ios_Iostate iostate;

    
    
    static const iostate badbit =	_S_badbit;

    
    static const iostate eofbit =	_S_eofbit;

    
    
    
    static const iostate failbit =	_S_failbit;

    
    static const iostate goodbit =	_S_goodbit;

    
    











 
    typedef _Ios_Openmode openmode;

    
    static const openmode app =		_S_app;

    
    static const openmode ate =		_S_ate;

    
    
    
    static const openmode binary =	_S_bin;

    
    static const openmode in =		_S_in;

    
    static const openmode out =		_S_out;

    
    static const openmode trunc =	_S_trunc;

    
    







 
    typedef _Ios_Seekdir seekdir;

    
    static const seekdir beg =		_S_beg;

    
    static const seekdir cur =		_S_cur;

    
    static const seekdir end =		_S_end;

    
    typedef int io_state;
    typedef int open_mode;
    typedef int seek_dir;

    typedef std::streampos streampos;
    typedef std::streamoff streamoff;

    
    




 
    enum event
    {
      erase_event,
      imbue_event,
      copyfmt_event
    };

    








 
    typedef void (*event_callback) (event, ios_base&, int);

    








 
    void
    register_callback(event_callback __fn, int __index);

  protected:
    streamsize		_M_precision;
    streamsize		_M_width;
    fmtflags		_M_flags;
    iostate		_M_exception;
    iostate		_M_streambuf_state;

    
    
    struct _Callback_list
    {
      
      _Callback_list*		_M_next;
      ios_base::event_callback	_M_fn;
      int			_M_index;
      _Atomic_word		_M_refcount;  

      _Callback_list(ios_base::event_callback __fn, int __index,
		     _Callback_list* __cb)
      : _M_next(__cb), _M_fn(__fn), _M_index(__index), _M_refcount(0) { }

      void
      _M_add_reference() { __gnu_cxx::__atomic_add_dispatch(&_M_refcount, 1); }

      
      int
      _M_remove_reference() 
      {
        
        ;
        int __res = __gnu_cxx::__exchange_and_add_dispatch(&_M_refcount, -1);
        if (__res == 0)
          {
            ;
          }
        return __res;
      }
    };

     _Callback_list*	_M_callbacks;

    void
    _M_call_callbacks(event __ev) throw();

    void
    _M_dispose_callbacks(void) throw();

    
    struct _Words
    {
      void*	_M_pword;
      long	_M_iword;
      _Words() : _M_pword(0), _M_iword(0) { }
    };

    
    _Words		_M_word_zero;

    
    
    enum { _S_local_word_size = 8 };
    _Words		_M_local_word[_S_local_word_size];

    
    int			_M_word_size;
    _Words*		_M_word;

    _Words&
    _M_grow_words(int __index, bool __iword);

    
    locale		_M_ios_locale;

    void
    _M_init() throw();

  public:

    
    
    
    
    class Init
    {
      friend class ios_base;
    public:
      Init();
      ~Init();

    private:
      static _Atomic_word	_S_refcount;
      static bool		_S_synced_with_stdio;
    };

    
    


 
    fmtflags
    flags() const
    { return _M_flags; }

    





 
    fmtflags
    flags(fmtflags __fmtfl)
    {
      fmtflags __old = _M_flags;
      _M_flags = __fmtfl;
      return __old;
    }

    






 
    fmtflags
    setf(fmtflags __fmtfl)
    {
      fmtflags __old = _M_flags;
      _M_flags |= __fmtfl;
      return __old;
    }

    







 
    fmtflags
    setf(fmtflags __fmtfl, fmtflags __mask)
    {
      fmtflags __old = _M_flags;
      _M_flags &= ~__mask;
      _M_flags |= (__fmtfl & __mask);
      return __old;
    }

    




 
    void
    unsetf(fmtflags __mask)
    { _M_flags &= ~__mask; }

    





 
    streamsize
    precision() const
    { return _M_precision; }

    



 
    streamsize
    precision(streamsize __prec)
    {
      streamsize __old = _M_precision;
      _M_precision = __prec;
      return __old;
    }

    




 
    streamsize
    width() const
    { return _M_width; }

    



 
    streamsize
    width(streamsize __wide)
    {
      streamsize __old = _M_width;
      _M_width = __wide;
      return __old;
    }

    
    








 
    static bool
    sync_with_stdio(bool __sync = true);

    
    






 
    locale
    imbue(const locale& __loc) throw();

    






 
    locale
    getloc() const
    { return _M_ios_locale; }

    





 
    const locale&
    _M_getloc() const
    { return _M_ios_locale; }

    
    












 
    static int
    xalloc() throw();

    











 
    long&
    iword(int __ix)
    {
      _Words& __word = (__ix < _M_word_size)
			? _M_word[__ix] : _M_grow_words(__ix, true);
      return __word._M_iword;
    }

    











 
    void*&
    pword(int __ix)
    {
      _Words& __word = (__ix < _M_word_size)
			? _M_word[__ix] : _M_grow_words(__ix, false);
      return __word._M_pword;
    }

    
    






 
    virtual ~ios_base();

  protected:
    ios_base() throw ();

  
  
  private:
    ios_base(const ios_base&);

    ios_base&
    operator=(const ios_base&);
  };

  
  
  inline ios_base&
  boolalpha(ios_base& __base)
  {
    __base.setf(ios_base::boolalpha);
    return __base;
  }

  
  inline ios_base&
  noboolalpha(ios_base& __base)
  {
    __base.unsetf(ios_base::boolalpha);
    return __base;
  }

  
  inline ios_base&
  showbase(ios_base& __base)
  {
    __base.setf(ios_base::showbase);
    return __base;
  }

  
  inline ios_base&
  noshowbase(ios_base& __base)
  {
    __base.unsetf(ios_base::showbase);
    return __base;
  }

  
  inline ios_base&
  showpoint(ios_base& __base)
  {
    __base.setf(ios_base::showpoint);
    return __base;
  }

  
  inline ios_base&
  noshowpoint(ios_base& __base)
  {
    __base.unsetf(ios_base::showpoint);
    return __base;
  }

  
  inline ios_base&
  showpos(ios_base& __base)
  {
    __base.setf(ios_base::showpos);
    return __base;
  }

  
  inline ios_base&
  noshowpos(ios_base& __base)
  {
    __base.unsetf(ios_base::showpos);
    return __base;
  }

  
  inline ios_base&
  skipws(ios_base& __base)
  {
    __base.setf(ios_base::skipws);
    return __base;
  }

  
  inline ios_base&
  noskipws(ios_base& __base)
  {
    __base.unsetf(ios_base::skipws);
    return __base;
  }

  
  inline ios_base&
  uppercase(ios_base& __base)
  {
    __base.setf(ios_base::uppercase);
    return __base;
  }

  
  inline ios_base&
  nouppercase(ios_base& __base)
  {
    __base.unsetf(ios_base::uppercase);
    return __base;
  }

  
  inline ios_base&
  unitbuf(ios_base& __base)
  {
     __base.setf(ios_base::unitbuf);
     return __base;
  }

  
  inline ios_base&
  nounitbuf(ios_base& __base)
  {
     __base.unsetf(ios_base::unitbuf);
     return __base;
  }

  
  
  inline ios_base&
  internal(ios_base& __base)
  {
     __base.setf(ios_base::internal, ios_base::adjustfield);
     return __base;
  }

  
  inline ios_base&
  left(ios_base& __base)
  {
    __base.setf(ios_base::left, ios_base::adjustfield);
    return __base;
  }

  
  inline ios_base&
  right(ios_base& __base)
  {
    __base.setf(ios_base::right, ios_base::adjustfield);
    return __base;
  }

  
  
  inline ios_base&
  dec(ios_base& __base)
  {
    __base.setf(ios_base::dec, ios_base::basefield);
    return __base;
  }

  
  inline ios_base&
  hex(ios_base& __base)
  {
    __base.setf(ios_base::hex, ios_base::basefield);
    return __base;
  }

  
  inline ios_base&
  oct(ios_base& __base)
  {
    __base.setf(ios_base::oct, ios_base::basefield);
    return __base;
  }

  
  
  inline ios_base&
  fixed(ios_base& __base)
  {
    __base.setf(ios_base::fixed, ios_base::floatfield);
    return __base;
  }

  
  inline ios_base&
  scientific(ios_base& __base)
  {
    __base.setf(ios_base::scientific, ios_base::floatfield);
    return __base;
  }


} 




























 








namespace std __attribute__ ((__visibility__ ("default")))
{


  template<typename _CharT, typename _Traits>
    streamsize
    __copy_streambufs_eof(basic_streambuf<_CharT, _Traits>*,
			  basic_streambuf<_CharT, _Traits>*, bool&);

  



























































 
  template<typename _CharT, typename _Traits>
    class basic_streambuf 
    {
    public:
      
      



 
      typedef _CharT 					char_type;
      typedef _Traits 					traits_type;
      typedef typename traits_type::int_type 		int_type;
      typedef typename traits_type::pos_type 		pos_type;
      typedef typename traits_type::off_type 		off_type;
      

      
      
      typedef basic_streambuf<char_type, traits_type>  	__streambuf_type;
      
      
      friend class basic_ios<char_type, traits_type>;
      friend class basic_istream<char_type, traits_type>;
      friend class basic_ostream<char_type, traits_type>;
      friend class istreambuf_iterator<char_type, traits_type>;
      friend class ostreambuf_iterator<char_type, traits_type>;

      friend streamsize
      __copy_streambufs_eof<>(__streambuf_type*, __streambuf_type*, bool&);

      template<bool _IsMove, typename _CharT2>
        friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value, 
					       _CharT2*>::__type
        __copy_move_a2(istreambuf_iterator<_CharT2>,
		       istreambuf_iterator<_CharT2>, _CharT2*);

      template<typename _CharT2>
        friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
				  istreambuf_iterator<_CharT2> >::__type
        find(istreambuf_iterator<_CharT2>, istreambuf_iterator<_CharT2>,
	     const _CharT2&);

      template<typename _CharT2, typename _Traits2>
        friend basic_istream<_CharT2, _Traits2>&
        operator>>(basic_istream<_CharT2, _Traits2>&, _CharT2*);

      template<typename _CharT2, typename _Traits2, typename _Alloc>
        friend basic_istream<_CharT2, _Traits2>&
        operator>>(basic_istream<_CharT2, _Traits2>&,
		   basic_string<_CharT2, _Traits2, _Alloc>&);

      template<typename _CharT2, typename _Traits2, typename _Alloc>
        friend basic_istream<_CharT2, _Traits2>&
        getline(basic_istream<_CharT2, _Traits2>&,
		basic_string<_CharT2, _Traits2, _Alloc>&, _CharT2);

    protected:
      
      





 
      char_type* 		_M_in_beg;     
      char_type* 		_M_in_cur;     
      char_type* 		_M_in_end;     
      char_type* 		_M_out_beg;    
      char_type* 		_M_out_cur;    
      char_type* 		_M_out_end;    

      
      locale 			_M_buf_locale;	

  public:
      
      virtual 
      ~basic_streambuf() 
      { }

      
      





 
      locale 
      pubimbue(const locale &__loc)
      {
	locale __tmp(this->getloc());
	this->imbue(__loc);
	_M_buf_locale = __loc;
	return __tmp;
      }

      






 
      locale   
      getloc() const
      { return _M_buf_locale; } 

      
      
      





 
      __streambuf_type* 
      pubsetbuf(char_type* __s, streamsize __n) 
      { return this->setbuf(__s, __n); }

      pos_type 
      pubseekoff(off_type __off, ios_base::seekdir __way, 
		 ios_base::openmode __mode = ios_base::in | ios_base::out)
      { return this->seekoff(__off, __way, __mode); }

      pos_type 
      pubseekpos(pos_type __sp,
		 ios_base::openmode __mode = ios_base::in | ios_base::out)
      { return this->seekpos(__sp, __mode); }

      int 
      pubsync() { return this->sync(); }
      

      
      






 
      streamsize 
      in_avail() 
      { 
	const streamsize __ret = this->egptr() - this->gptr();
	return __ret ? __ret : this->showmanyc();
      }

      





 
      int_type 
      snextc()
      {
	int_type __ret = traits_type::eof();
	if (__builtin_expect(!traits_type::eq_int_type(this->sbumpc(), 
						       __ret), true))
	  __ret = this->sgetc();
	return __ret;
      }

      






 
      int_type 
      sbumpc()
      {
	int_type __ret;
	if (__builtin_expect(this->gptr() < this->egptr(), true))
	  {
	    __ret = traits_type::to_int_type(*this->gptr());
	    this->gbump(1);
	  }
	else 
	  __ret = this->uflow();
	return __ret;
      }

      






 
      int_type 
      sgetc()
      {
	int_type __ret;
	if (__builtin_expect(this->gptr() < this->egptr(), true))
	  __ret = traits_type::to_int_type(*this->gptr());
	else 
	  __ret = this->underflow();
	return __ret;
      }

      






 
      streamsize 
      sgetn(char_type* __s, streamsize __n)
      { return this->xsgetn(__s, __n); }

      
      








 
      int_type 
      sputbackc(char_type __c)
      {
	int_type __ret;
	const bool __testpos = this->eback() < this->gptr();
	if (__builtin_expect(!__testpos || 
			     !traits_type::eq(__c, this->gptr()[-1]), false))
	  __ret = this->pbackfail(traits_type::to_int_type(__c));
	else 
	  {
	    this->gbump(-1);
	    __ret = traits_type::to_int_type(*this->gptr());
	  }
	return __ret;
      }

      







 
      int_type 
      sungetc()
      {
	int_type __ret;
	if (__builtin_expect(this->eback() < this->gptr(), true))
	  {
	    this->gbump(-1);
	    __ret = traits_type::to_int_type(*this->gptr());
	  }
	else 
	  __ret = this->pbackfail();
	return __ret;
      }

      
      










 
      int_type 
      sputc(char_type __c)
      {
	int_type __ret;
	if (__builtin_expect(this->pptr() < this->epptr(), true))
	  {
	    *this->pptr() = __c;
	    this->pbump(1);
	    __ret = traits_type::to_int_type(__c);
	  }
	else
	  __ret = this->overflow(traits_type::to_int_type(__c));
	return __ret;
      }

      









 
      streamsize 
      sputn(const char_type* __s, streamsize __n)
      { return this->xsputn(__s, __n); }

    protected:
      







 
      basic_streambuf()
      : _M_in_beg(0), _M_in_cur(0), _M_in_end(0), 
      _M_out_beg(0), _M_out_cur(0), _M_out_end(0),
      _M_buf_locale(locale()) 
      { }

      
      
      








 
      char_type* 
      eback() const { return _M_in_beg; }

      char_type* 
      gptr()  const { return _M_in_cur;  }

      char_type* 
      egptr() const { return _M_in_end; }
      

      




 
      void 
      gbump(int __n) { _M_in_cur += __n; }

      






 
      void 
      setg(char_type* __gbeg, char_type* __gnext, char_type* __gend)
      {
	_M_in_beg = __gbeg;
	_M_in_cur = __gnext;
	_M_in_end = __gend;
      }

      
      
      








 
      char_type* 
      pbase() const { return _M_out_beg; }

      char_type* 
      pptr() const { return _M_out_cur; }

      char_type* 
      epptr() const { return _M_out_end; }
      

      




 
      void 
      pbump(int __n) { _M_out_cur += __n; }

      





 
      void 
      setp(char_type* __pbeg, char_type* __pend)
      { 
	_M_out_beg = _M_out_cur = __pbeg; 
	_M_out_end = __pend;
      }

      
      
      










 
      virtual void 
      imbue(const locale&) 
      { }

      
      








 
      virtual basic_streambuf<char_type,_Traits>* 
      setbuf(char_type*, streamsize)
      {	return this; }
      
      





 
      virtual pos_type 
      seekoff(off_type, ios_base::seekdir,
	      ios_base::openmode   = ios_base::in | ios_base::out)
      { return pos_type(off_type(-1)); } 

      





 
      virtual pos_type 
      seekpos(pos_type, 
	      ios_base::openmode   = ios_base::in | ios_base::out)
      { return pos_type(off_type(-1)); } 

      






 
      virtual int 
      sync() { return 0; }

      
      
















 
      virtual streamsize 
      showmanyc() { return 0; }

      











 
      virtual streamsize 
      xsgetn(char_type* __s, streamsize __n);

      

















 
      virtual int_type 
      underflow()
      { return traits_type::eof(); }

      







 
      virtual int_type 
      uflow() 
      {
	int_type __ret = traits_type::eof();
	const bool __testeof = traits_type::eq_int_type(this->underflow(), 
							__ret);
	if (!__testeof)
	  {
	    __ret = traits_type::to_int_type(*this->gptr());
	    this->gbump(1);
	  }
	return __ret;    
      }

      
      







 
      virtual int_type 
      pbackfail(int_type    = traits_type::eof())
      { return traits_type::eof(); }

      
      











 
      virtual streamsize 
      xsputn(const char_type* __s, streamsize __n);

      





















 
      virtual int_type 
      overflow(int_type   = traits_type::eof())
      { return traits_type::eof(); }

    
    public:
      






 
      void 
      stossc() 
      {
	if (this->gptr() < this->egptr()) 
	  this->gbump(1);
	else 
	  this->uflow();
      }

      
      void 
      __safe_gbump(streamsize __n) { _M_in_cur += __n; }

      void
      __safe_pbump(streamsize __n) { _M_out_cur += __n; }

    private:
      
      
      basic_streambuf(const __streambuf_type& __sb)
      : _M_in_beg(__sb._M_in_beg), _M_in_cur(__sb._M_in_cur), 
      _M_in_end(__sb._M_in_end), _M_out_beg(__sb._M_out_beg), 
      _M_out_cur(__sb._M_out_cur), _M_out_end(__sb._M_out_cur),
      _M_buf_locale(__sb._M_buf_locale) 
      { }

      __streambuf_type& 
      operator=(const __streambuf_type&) { return *this; };
    };

  
  template<>
    streamsize
    __copy_streambufs_eof(basic_streambuf<char>* __sbin,
			  basic_streambuf<char>* __sbout, bool& __ineof);
  template<>
    streamsize
    __copy_streambufs_eof(basic_streambuf<wchar_t>* __sbin,
			  basic_streambuf<wchar_t>* __sbout, bool& __ineof);


} 





























 







namespace std __attribute__ ((__visibility__ ("default")))
{


  template<typename _CharT, typename _Traits>
    streamsize
    basic_streambuf<_CharT, _Traits>::
    xsgetn(char_type* __s, streamsize __n)
    {
      streamsize __ret = 0;
      while (__ret < __n)
	{
	  const streamsize __buf_len = this->egptr() - this->gptr();
	  if (__buf_len)
	    {
	      const streamsize __remaining = __n - __ret;
	      const streamsize __len = std::min(__buf_len, __remaining);
	      traits_type::copy(__s, this->gptr(), __len);
	      __ret += __len;
	      __s += __len;
	      this->__safe_gbump(__len);
	    }

	  if (__ret < __n)
	    {
	      const int_type __c = this->uflow();
	      if (!traits_type::eq_int_type(__c, traits_type::eof()))
		{
		  traits_type::assign(*__s++, traits_type::to_char_type(__c));
		  ++__ret;
		}
	      else
		break;
	    }
	}
      return __ret;
    }

  template<typename _CharT, typename _Traits>
    streamsize
    basic_streambuf<_CharT, _Traits>::
    xsputn(const char_type* __s, streamsize __n)
    {
      streamsize __ret = 0;
      while (__ret < __n)
	{
	  const streamsize __buf_len = this->epptr() - this->pptr();
	  if (__buf_len)
	    {
	      const streamsize __remaining = __n - __ret;
	      const streamsize __len = std::min(__buf_len, __remaining);
	      traits_type::copy(this->pptr(), __s, __len);
	      __ret += __len;
	      __s += __len;
	      this->__safe_pbump(__len);
	    }

	  if (__ret < __n)
	    {
	      int_type __c = this->overflow(traits_type::to_int_type(*__s));
	      if (!traits_type::eq_int_type(__c, traits_type::eof()))
		{
		  ++__ret;
		  ++__s;
		}
	      else
		break;
	    }
	}
      return __ret;
    }

  
  
  
  template<typename _CharT, typename _Traits>
    streamsize
    __copy_streambufs_eof(basic_streambuf<_CharT, _Traits>* __sbin,
			  basic_streambuf<_CharT, _Traits>* __sbout,
			  bool& __ineof)
    {
      streamsize __ret = 0;
      __ineof = true;
      typename _Traits::int_type __c = __sbin->sgetc();
      while (!_Traits::eq_int_type(__c, _Traits::eof()))
	{
	  __c = __sbout->sputc(_Traits::to_char_type(__c));
	  if (_Traits::eq_int_type(__c, _Traits::eof()))
	    {
	      __ineof = false;
	      break;
	    }
	  ++__ret;
	  __c = __sbin->snextc();
	}
      return __ret;
    }

  template<typename _CharT, typename _Traits>
    inline streamsize
    __copy_streambufs(basic_streambuf<_CharT, _Traits>* __sbin,
		      basic_streambuf<_CharT, _Traits>* __sbout)
    {
      bool __ineof;
      return __copy_streambufs_eof(__sbin, __sbout, __ineof);
    }

  
  
  extern template class basic_streambuf<char>;
  extern template
    streamsize
    __copy_streambufs(basic_streambuf<char>*,
		      basic_streambuf<char>*);
  extern template
    streamsize
    __copy_streambufs_eof(basic_streambuf<char>*,
			  basic_streambuf<char>*, bool&);

  extern template class basic_streambuf<wchar_t>;
  extern template
    streamsize
    __copy_streambufs(basic_streambuf<wchar_t>*,
		      basic_streambuf<wchar_t>*);
  extern template
    streamsize
    __copy_streambufs_eof(basic_streambuf<wchar_t>*,
			  basic_streambuf<wchar_t>*, bool&);


} 































 
































 









































 

























 




 




 































 



 







 
 


 



 



 
typedef unsigned long int wctype_t;




 


enum
{
  __ISwupper = 0,			 
  __ISwlower = 1,			 
  __ISwalpha = 2,			 
  __ISwdigit = 3,			 
  __ISwxdigit = 4,			 
  __ISwspace = 5,			 
  __ISwprint = 6,			 
  __ISwgraph = 7,			 
  __ISwblank = 8,			 
  __ISwcntrl = 9,			 
  __ISwpunct = 10,			 
  __ISwalnum = 11,			 

  _ISwupper = ((__ISwupper) < 8 ? (int) ((1UL << (__ISwupper)) << 24) : ((__ISwupper) < 16 ? (int) ((1UL << (__ISwupper)) << 8) : ((__ISwupper) < 24 ? (int) ((1UL << (__ISwupper)) >> 8) : (int) ((1UL << (__ISwupper)) >> 24)))),	 
  _ISwlower = ((__ISwlower) < 8 ? (int) ((1UL << (__ISwlower)) << 24) : ((__ISwlower) < 16 ? (int) ((1UL << (__ISwlower)) << 8) : ((__ISwlower) < 24 ? (int) ((1UL << (__ISwlower)) >> 8) : (int) ((1UL << (__ISwlower)) >> 24)))),	 
  _ISwalpha = ((__ISwalpha) < 8 ? (int) ((1UL << (__ISwalpha)) << 24) : ((__ISwalpha) < 16 ? (int) ((1UL << (__ISwalpha)) << 8) : ((__ISwalpha) < 24 ? (int) ((1UL << (__ISwalpha)) >> 8) : (int) ((1UL << (__ISwalpha)) >> 24)))),	 
  _ISwdigit = ((__ISwdigit) < 8 ? (int) ((1UL << (__ISwdigit)) << 24) : ((__ISwdigit) < 16 ? (int) ((1UL << (__ISwdigit)) << 8) : ((__ISwdigit) < 24 ? (int) ((1UL << (__ISwdigit)) >> 8) : (int) ((1UL << (__ISwdigit)) >> 24)))),	 
  _ISwxdigit = ((__ISwxdigit) < 8 ? (int) ((1UL << (__ISwxdigit)) << 24) : ((__ISwxdigit) < 16 ? (int) ((1UL << (__ISwxdigit)) << 8) : ((__ISwxdigit) < 24 ? (int) ((1UL << (__ISwxdigit)) >> 8) : (int) ((1UL << (__ISwxdigit)) >> 24)))),	 
  _ISwspace = ((__ISwspace) < 8 ? (int) ((1UL << (__ISwspace)) << 24) : ((__ISwspace) < 16 ? (int) ((1UL << (__ISwspace)) << 8) : ((__ISwspace) < 24 ? (int) ((1UL << (__ISwspace)) >> 8) : (int) ((1UL << (__ISwspace)) >> 24)))),	 
  _ISwprint = ((__ISwprint) < 8 ? (int) ((1UL << (__ISwprint)) << 24) : ((__ISwprint) < 16 ? (int) ((1UL << (__ISwprint)) << 8) : ((__ISwprint) < 24 ? (int) ((1UL << (__ISwprint)) >> 8) : (int) ((1UL << (__ISwprint)) >> 24)))),	 
  _ISwgraph = ((__ISwgraph) < 8 ? (int) ((1UL << (__ISwgraph)) << 24) : ((__ISwgraph) < 16 ? (int) ((1UL << (__ISwgraph)) << 8) : ((__ISwgraph) < 24 ? (int) ((1UL << (__ISwgraph)) >> 8) : (int) ((1UL << (__ISwgraph)) >> 24)))),	 
  _ISwblank = ((__ISwblank) < 8 ? (int) ((1UL << (__ISwblank)) << 24) : ((__ISwblank) < 16 ? (int) ((1UL << (__ISwblank)) << 8) : ((__ISwblank) < 24 ? (int) ((1UL << (__ISwblank)) >> 8) : (int) ((1UL << (__ISwblank)) >> 24)))),	 
  _ISwcntrl = ((__ISwcntrl) < 8 ? (int) ((1UL << (__ISwcntrl)) << 24) : ((__ISwcntrl) < 16 ? (int) ((1UL << (__ISwcntrl)) << 8) : ((__ISwcntrl) < 24 ? (int) ((1UL << (__ISwcntrl)) >> 8) : (int) ((1UL << (__ISwcntrl)) >> 24)))),	 
  _ISwpunct = ((__ISwpunct) < 8 ? (int) ((1UL << (__ISwpunct)) << 24) : ((__ISwpunct) < 16 ? (int) ((1UL << (__ISwpunct)) << 8) : ((__ISwpunct) < 24 ? (int) ((1UL << (__ISwpunct)) >> 8) : (int) ((1UL << (__ISwpunct)) >> 24)))),	 
  _ISwalnum = ((__ISwalnum) < 8 ? (int) ((1UL << (__ISwalnum)) << 24) : ((__ISwalnum) < 16 ? (int) ((1UL << (__ISwalnum)) << 8) : ((__ISwalnum) < 24 ? (int) ((1UL << (__ISwalnum)) >> 8) : (int) ((1UL << (__ISwalnum)) >> 24))))	 
};


extern "C" {




 


 
extern int iswalnum (wint_t __wc) throw ();




 
extern int iswalpha (wint_t __wc) throw ();

 
extern int iswcntrl (wint_t __wc) throw ();


 
extern int iswdigit (wint_t __wc) throw ();


 
extern int iswgraph (wint_t __wc) throw ();



 
extern int iswlower (wint_t __wc) throw ();

 
extern int iswprint (wint_t __wc) throw ();



 
extern int iswpunct (wint_t __wc) throw ();



 
extern int iswspace (wint_t __wc) throw ();



 
extern int iswupper (wint_t __wc) throw ();



 
extern int iswxdigit (wint_t __wc) throw ();



 
extern int iswblank (wint_t __wc) throw ();



 


 
extern wctype_t wctype (__const char *__property) throw ();


 
extern int iswctype (wint_t __wc, wctype_t __desc) throw ();





 



 
typedef __const __int32_t *wctrans_t;




 
extern wint_t towlower (wint_t __wc) throw ();

 
extern wint_t towupper (wint_t __wc) throw ();


}




 



 

extern "C" {



 
extern wctrans_t wctrans (__const char *__property) throw ();

 
extern wint_t towctrans (wint_t __wc, wctrans_t __desc) throw ();


 


 
extern int iswalnum_l (wint_t __wc, __locale_t __locale) throw ();




 
extern int iswalpha_l (wint_t __wc, __locale_t __locale) throw ();

 
extern int iswcntrl_l (wint_t __wc, __locale_t __locale) throw ();


 
extern int iswdigit_l (wint_t __wc, __locale_t __locale) throw ();


 
extern int iswgraph_l (wint_t __wc, __locale_t __locale) throw ();



 
extern int iswlower_l (wint_t __wc, __locale_t __locale) throw ();

 
extern int iswprint_l (wint_t __wc, __locale_t __locale) throw ();



 
extern int iswpunct_l (wint_t __wc, __locale_t __locale) throw ();



 
extern int iswspace_l (wint_t __wc, __locale_t __locale) throw ();



 
extern int iswupper_l (wint_t __wc, __locale_t __locale) throw ();



 
extern int iswxdigit_l (wint_t __wc, __locale_t __locale) throw ();



 
extern int iswblank_l (wint_t __wc, __locale_t __locale) throw ();


 
extern wctype_t wctype_l (__const char *__property, __locale_t __locale)
     throw ();


 
extern int iswctype_l (wint_t __wc, wctype_t __desc, __locale_t __locale)
     throw ();




 

 
extern wint_t towlower_l (wint_t __wc, __locale_t __locale) throw ();

 
extern wint_t towupper_l (wint_t __wc, __locale_t __locale) throw ();


 
extern wctrans_t wctrans_l (__const char *__property, __locale_t __locale)
     throw ();

 
extern wint_t towctrans_l (wint_t __wc, wctrans_t __desc,
			   __locale_t __locale) throw ();


}







namespace std
{
  using ::wctrans_t;
  using ::wctype_t;
  using ::wint_t;

  using ::iswalnum;
  using ::iswalpha;
  using ::iswblank;
  using ::iswcntrl;
  using ::iswctype;
  using ::iswdigit;
  using ::iswgraph;
  using ::iswlower;
  using ::iswprint;
  using ::iswpunct;
  using ::iswspace;
  using ::iswupper;
  using ::iswxdigit;
  using ::towctrans;
  using ::towlower;
  using ::towupper;
  using ::wctrans;
  using ::wctype;
} 





































 



































 








namespace std __attribute__ ((__visibility__ ("default")))
{


  
  struct ctype_base
  {
    
    typedef const int* 		__to_type;

    
    
    typedef unsigned short 	mask;
    static const mask upper    	= _ISupper;
    static const mask lower 	= _ISlower;
    static const mask alpha 	= _ISalpha;
    static const mask digit 	= _ISdigit;
    static const mask xdigit 	= _ISxdigit;
    static const mask space 	= _ISspace;
    static const mask print 	= _ISprint;
    static const mask graph 	= _ISalpha | _ISdigit | _ISpunct;
    static const mask cntrl 	= _IScntrl;
    static const mask punct 	= _ISpunct;
    static const mask alnum 	= _ISalpha | _ISdigit;
  };


} 





























 




namespace std __attribute__ ((__visibility__ ("default")))
{

     
  


 

  
  
  template<typename _CharT, typename _Traits>
    class istreambuf_iterator
    : public iterator<input_iterator_tag, _CharT, typename _Traits::off_type,
		      _CharT*, _CharT&>
    {
    public:
      
      
      
      typedef _CharT					char_type;
      typedef _Traits					traits_type;
      typedef typename _Traits::int_type		int_type;
      typedef basic_streambuf<_CharT, _Traits>		streambuf_type;
      typedef basic_istream<_CharT, _Traits>		istream_type;
      

      template<typename _CharT2>
	friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
		                    ostreambuf_iterator<_CharT2> >::__type
	copy(istreambuf_iterator<_CharT2>, istreambuf_iterator<_CharT2>,
	     ostreambuf_iterator<_CharT2>);

      template<bool _IsMove, typename _CharT2>
	friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value, 
					       _CharT2*>::__type
	__copy_move_a2(istreambuf_iterator<_CharT2>,
		       istreambuf_iterator<_CharT2>, _CharT2*);

      template<typename _CharT2>
	friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
			            istreambuf_iterator<_CharT2> >::__type
	find(istreambuf_iterator<_CharT2>, istreambuf_iterator<_CharT2>,
	     const _CharT2&);

    private:
      
      
      
      
      
      
      
      mutable streambuf_type*	_M_sbuf;
      mutable int_type		_M_c;

    public:
      
       istreambuf_iterator() throw()
      : _M_sbuf(0), _M_c(traits_type::eof()) { }

      
      istreambuf_iterator(istream_type& __s) throw()
      : _M_sbuf(__s.rdbuf()), _M_c(traits_type::eof()) { }

      
      istreambuf_iterator(streambuf_type* __s) throw()
      : _M_sbuf(__s), _M_c(traits_type::eof()) { }

      
      
      
      char_type
      operator*() const
      {
	return traits_type::to_char_type(_M_get());
      }

      
      istreambuf_iterator&
      operator++()
      {
	;
	if (_M_sbuf)
	  {
	    _M_sbuf->sbumpc();
	    _M_c = traits_type::eof();
	  }
	return *this;
      }

      
      istreambuf_iterator
      operator++(int)
      {
	;

	istreambuf_iterator __old = *this;
	if (_M_sbuf)
	  {
	    __old._M_c = _M_sbuf->sbumpc();
	    _M_c = traits_type::eof();
	  }
	return __old;
      }

      
      
      
      
      bool
      equal(const istreambuf_iterator& __b) const
      { return _M_at_eof() == __b._M_at_eof(); }

    private:
      int_type
      _M_get() const
      {
	const int_type __eof = traits_type::eof();
	int_type __ret = __eof;
	if (_M_sbuf)
	  {
	    if (!traits_type::eq_int_type(_M_c, __eof))
	      __ret = _M_c;
	    else if (!traits_type::eq_int_type((__ret = _M_sbuf->sgetc()),
					       __eof))
	      _M_c = __ret;
	    else
	      _M_sbuf = 0;
	  }
	return __ret;
      }

      bool
      _M_at_eof() const
      {
	const int_type __eof = traits_type::eof();
	return traits_type::eq_int_type(_M_get(), __eof);
      }
    };

  template<typename _CharT, typename _Traits>
    inline bool
    operator==(const istreambuf_iterator<_CharT, _Traits>& __a,
	       const istreambuf_iterator<_CharT, _Traits>& __b)
    { return __a.equal(__b); }

  template<typename _CharT, typename _Traits>
    inline bool
    operator!=(const istreambuf_iterator<_CharT, _Traits>& __a,
	       const istreambuf_iterator<_CharT, _Traits>& __b)
    { return !__a.equal(__b); }

  
  template<typename _CharT, typename _Traits>
    class ostreambuf_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    public:
      
      
      
      typedef _CharT                           char_type;
      typedef _Traits                          traits_type;
      typedef basic_streambuf<_CharT, _Traits> streambuf_type;
      typedef basic_ostream<_CharT, _Traits>   ostream_type;
      

      template<typename _CharT2>
	friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
		                    ostreambuf_iterator<_CharT2> >::__type
	copy(istreambuf_iterator<_CharT2>, istreambuf_iterator<_CharT2>,
	     ostreambuf_iterator<_CharT2>);

    private:
      streambuf_type*	_M_sbuf;
      bool		_M_failed;

    public:
      
      ostreambuf_iterator(ostream_type& __s) throw ()
      : _M_sbuf(__s.rdbuf()), _M_failed(!_M_sbuf) { }

      
      ostreambuf_iterator(streambuf_type* __s) throw ()
      : _M_sbuf(__s), _M_failed(!_M_sbuf) { }

      
      ostreambuf_iterator&
      operator=(_CharT __c)
      {
	if (!_M_failed &&
	    _Traits::eq_int_type(_M_sbuf->sputc(__c), _Traits::eof()))
	  _M_failed = true;
	return *this;
      }

      
      ostreambuf_iterator&
      operator*()
      { return *this; }

      
      ostreambuf_iterator&
      operator++(int)
      { return *this; }

      
      ostreambuf_iterator&
      operator++()
      { return *this; }

      
      bool
      failed() const throw()
      { return _M_failed; }

      ostreambuf_iterator&
      _M_put(const _CharT* __ws, streamsize __len)
      {
	if (__builtin_expect(!_M_failed, true)
	    && __builtin_expect(this->_M_sbuf->sputn(__ws, __len) != __len,
				false))
	  _M_failed = true;
	return *this;
      }
    };

  
  template<typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
    	                 	    ostreambuf_iterator<_CharT> >::__type
    copy(istreambuf_iterator<_CharT> __first,
	 istreambuf_iterator<_CharT> __last,
	 ostreambuf_iterator<_CharT> __result)
    {
      if (__first._M_sbuf && !__last._M_sbuf && !__result._M_failed)
	{
	  bool __ineof;
	  __copy_streambufs_eof(__first._M_sbuf, __result._M_sbuf, __ineof);
	  if (!__ineof)
	    __result._M_failed = true;
	}
      return __result;
    }

  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value, 
    				    ostreambuf_iterator<_CharT> >::__type
    __copy_move_a2(_CharT* __first, _CharT* __last,
		   ostreambuf_iterator<_CharT> __result)
    {
      const streamsize __num = __last - __first;
      if (__num > 0)
	__result._M_put(__first, __num);
      return __result;
    }

  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
				    ostreambuf_iterator<_CharT> >::__type
    __copy_move_a2(const _CharT* __first, const _CharT* __last,
		   ostreambuf_iterator<_CharT> __result)
    {
      const streamsize __num = __last - __first;
      if (__num > 0)
	__result._M_put(__first, __num);
      return __result;
    }

  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value, 
    				    _CharT*>::__type
    __copy_move_a2(istreambuf_iterator<_CharT> __first,
		   istreambuf_iterator<_CharT> __last, _CharT* __result)
    {
      typedef istreambuf_iterator<_CharT>                  __is_iterator_type;
      typedef typename __is_iterator_type::traits_type     traits_type;
      typedef typename __is_iterator_type::streambuf_type  streambuf_type;
      typedef typename traits_type::int_type               int_type;

      if (__first._M_sbuf && !__last._M_sbuf)
	{
	  streambuf_type* __sb = __first._M_sbuf;
	  int_type __c = __sb->sgetc();
	  while (!traits_type::eq_int_type(__c, traits_type::eof()))
	    {
	      const streamsize __n = __sb->egptr() - __sb->gptr();
	      if (__n > 1)
		{
		  traits_type::copy(__result, __sb->gptr(), __n);
		  __sb->__safe_gbump(__n);
		  __result += __n;
		  __c = __sb->underflow();
		}
	      else
		{
		  *__result++ = traits_type::to_char_type(__c);
		  __c = __sb->snextc();
		}
	    }
	}
      return __result;
    }

  template<typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
		  		    istreambuf_iterator<_CharT> >::__type
    find(istreambuf_iterator<_CharT> __first,
	 istreambuf_iterator<_CharT> __last, const _CharT& __val)
    {
      typedef istreambuf_iterator<_CharT>                  __is_iterator_type;
      typedef typename __is_iterator_type::traits_type     traits_type;
      typedef typename __is_iterator_type::streambuf_type  streambuf_type;
      typedef typename traits_type::int_type               int_type;

      if (__first._M_sbuf && !__last._M_sbuf)
	{
	  const int_type __ival = traits_type::to_int_type(__val);
	  streambuf_type* __sb = __first._M_sbuf;
	  int_type __c = __sb->sgetc();
	  while (!traits_type::eq_int_type(__c, traits_type::eof())
		 && !traits_type::eq_int_type(__c, __ival))
	    {
	      streamsize __n = __sb->egptr() - __sb->gptr();
	      if (__n > 1)
		{
		  const _CharT* __p = traits_type::find(__sb->gptr(),
							__n, __val);
		  if (__p)
		    __n = __p - __sb->gptr();
		  __sb->__safe_gbump(__n);
		  __c = __sb->sgetc();
		}
	      else
		__c = __sb->snextc();
	    }

	  if (!traits_type::eq_int_type(__c, traits_type::eof()))
	    __first._M_c = __c;
	  else
	    __first._M_sbuf = 0;
	}
      return __first;
    }




} 


namespace std __attribute__ ((__visibility__ ("default")))
{


  

  
  
  
  template<typename _Tp>
    void
    __convert_to_v(const char*, _Tp&, ios_base::iostate&,
		   const __c_locale&) throw();

  
  template<>
    void
    __convert_to_v(const char*, float&, ios_base::iostate&,
		   const __c_locale&) throw();

  template<>
    void
    __convert_to_v(const char*, double&, ios_base::iostate&,
		   const __c_locale&) throw();

  template<>
    void
    __convert_to_v(const char*, long double&, ios_base::iostate&,
		   const __c_locale&) throw();

  
  
  template<typename _CharT, typename _Traits>
    struct __pad
    {
      static void
      _S_pad(ios_base& __io, _CharT __fill, _CharT* __news,
	     const _CharT* __olds, streamsize __newlen, streamsize __oldlen);
    };

  
  
  
  
  
  template<typename _CharT>
    _CharT*
    __add_grouping(_CharT* __s, _CharT __sep,
		   const char* __gbeg, size_t __gsize,
		   const _CharT* __first, const _CharT* __last);

  
  
  
  template<typename _CharT>
    inline
    ostreambuf_iterator<_CharT>
    __write(ostreambuf_iterator<_CharT> __s, const _CharT* __ws, int __len)
    {
      __s._M_put(__ws, __len);
      return __s;
    }

  
  template<typename _CharT, typename _OutIter>
    inline
    _OutIter
    __write(_OutIter __s, const _CharT* __ws, int __len)
    {
      for (int __j = 0; __j < __len; __j++, ++__s)
	*__s = __ws[__j];
      return __s;
    }


  
  

  







 
  template<typename _CharT>
    class __ctype_abstract_base : public locale::facet, public ctype_base
    {
    public:
      
      
      typedef _CharT char_type;

      








 
      bool
      is(mask __m, char_type __c) const
      { return this->do_is(__m, __c); }

      











 
      const char_type*
      is(const char_type *__lo, const char_type *__hi, mask *__vec) const
      { return this->do_is(__lo, __hi, __vec); }

      










 
      const char_type*
      scan_is(mask __m, const char_type* __lo, const char_type* __hi) const
      { return this->do_scan_is(__m, __lo, __hi); }

      










 
      const char_type*
      scan_not(mask __m, const char_type* __lo, const char_type* __hi) const
      { return this->do_scan_not(__m, __lo, __hi); }

      








 
      char_type
      toupper(char_type __c) const
      { return this->do_toupper(__c); }

      









 
      const char_type*
      toupper(char_type *__lo, const char_type* __hi) const
      { return this->do_toupper(__lo, __hi); }

      








 
      char_type
      tolower(char_type __c) const
      { return this->do_tolower(__c); }

      









 
      const char_type*
      tolower(char_type* __lo, const char_type* __hi) const
      { return this->do_tolower(__lo, __hi); }

      











 
      char_type
      widen(char __c) const
      { return this->do_widen(__c); }

      













 
      const char*
      widen(const char* __lo, const char* __hi, char_type* __to) const
      { return this->do_widen(__lo, __hi, __to); }

      













 
      char
      narrow(char_type __c, char __dfault) const
      { return this->do_narrow(__c, __dfault); }

      
















 
      const char_type*
      narrow(const char_type* __lo, const char_type* __hi,
	      char __dfault, char *__to) const
      { return this->do_narrow(__lo, __hi, __dfault, __to); }

    protected:
      explicit
      __ctype_abstract_base(size_t __refs = 0): facet(__refs) { }

      virtual
      ~__ctype_abstract_base() { }

      











 
      virtual bool
      do_is(mask __m, char_type __c) const = 0;

      














 
      virtual const char_type*
      do_is(const char_type* __lo, const char_type* __hi,
	    mask* __vec) const = 0;

      













 
      virtual const char_type*
      do_scan_is(mask __m, const char_type* __lo,
		 const char_type* __hi) const = 0;

      













 
      virtual const char_type*
      do_scan_not(mask __m, const char_type* __lo,
		  const char_type* __hi) const = 0;

      












 
      virtual char_type
      do_toupper(char_type) const = 0;

      












 
      virtual const char_type*
      do_toupper(char_type* __lo, const char_type* __hi) const = 0;

      











 
      virtual char_type
      do_tolower(char_type) const = 0;

      












 
      virtual const char_type*
      do_tolower(char_type* __lo, const char_type* __hi) const = 0;

      














 
      virtual char_type
      do_widen(char) const = 0;

      
















 
      virtual const char*
      do_widen(const char* __lo, const char* __hi,
	       char_type* __dest) const = 0;

      
















 
      virtual char
      do_narrow(char_type, char __dfault) const = 0;

      



















 
      virtual const char_type*
      do_narrow(const char_type* __lo, const char_type* __hi,
		char __dfault, char* __dest) const = 0;
    };

  
















 
  template<typename _CharT>
    class ctype : public __ctype_abstract_base<_CharT>
    {
    public:
      
      typedef _CharT			char_type;
      typedef typename __ctype_abstract_base<_CharT>::mask mask;

      
      static locale::id			id;

      explicit
      ctype(size_t __refs = 0) : __ctype_abstract_base<_CharT>(__refs) { }

   protected:
      virtual
      ~ctype();

      virtual bool
      do_is(mask __m, char_type __c) const;

      virtual const char_type*
      do_is(const char_type* __lo, const char_type* __hi, mask* __vec) const;

      virtual const char_type*
      do_scan_is(mask __m, const char_type* __lo, const char_type* __hi) const;

      virtual const char_type*
      do_scan_not(mask __m, const char_type* __lo,
		  const char_type* __hi) const;

      virtual char_type
      do_toupper(char_type __c) const;

      virtual const char_type*
      do_toupper(char_type* __lo, const char_type* __hi) const;

      virtual char_type
      do_tolower(char_type __c) const;

      virtual const char_type*
      do_tolower(char_type* __lo, const char_type* __hi) const;

      virtual char_type
      do_widen(char __c) const;

      virtual const char*
      do_widen(const char* __lo, const char* __hi, char_type* __dest) const;

      virtual char
      do_narrow(char_type, char __dfault) const;

      virtual const char_type*
      do_narrow(const char_type* __lo, const char_type* __hi,
		char __dfault, char* __dest) const;
    };

  template<typename _CharT>
    locale::id ctype<_CharT>::id;

  







 
  template<>
    class ctype<char> : public locale::facet, public ctype_base
    {
    public:
      
      
      typedef char		char_type;

    protected:
      
      __c_locale		_M_c_locale_ctype;
      bool			_M_del;
      __to_type			_M_toupper;
      __to_type			_M_tolower;
      const mask*		_M_table;
      mutable char		_M_widen_ok;
      mutable char		_M_widen[1 + static_cast<unsigned char>(-1)];
      mutable char		_M_narrow[1 + static_cast<unsigned char>(-1)];
      mutable char		_M_narrow_ok;	
						

    public:
      
      static locale::id        id;
      
      static const size_t      table_size = 1 + static_cast<unsigned char>(-1);

      








 
      explicit
      ctype(const mask* __table = 0, bool __del = false, size_t __refs = 0);

      








 
      explicit
      ctype(__c_locale __cloc, const mask* __table = 0, bool __del = false,
	    size_t __refs = 0);

      







 
      inline bool
      is(mask __m, char __c) const;

      










 
      inline const char*
      is(const char* __lo, const char* __hi, mask* __vec) const;

      









 
      inline const char*
      scan_is(mask __m, const char* __lo, const char* __hi) const;

      









 
      inline const char*
      scan_not(mask __m, const char* __lo, const char* __hi) const;

      










 
      char_type
      toupper(char_type __c) const
      { return this->do_toupper(__c); }

      











 
      const char_type*
      toupper(char_type *__lo, const char_type* __hi) const
      { return this->do_toupper(__lo, __hi); }

      










 
      char_type
      tolower(char_type __c) const
      { return this->do_tolower(__c); }

      











 
      const char_type*
      tolower(char_type* __lo, const char_type* __hi) const
      { return this->do_tolower(__lo, __hi); }

      














 
      char_type
      widen(char __c) const
      {
	if (_M_widen_ok)
	  return _M_widen[static_cast<unsigned char>(__c)];
	this->_M_widen_init();
	return this->do_widen(__c);
      }

      
















 
      const char*
      widen(const char* __lo, const char* __hi, char_type* __to) const
      {
	if (_M_widen_ok == 1)
	  {
	    __builtin_memcpy(__to, __lo, __hi - __lo);
	    return __hi;
	  }
	if (!_M_widen_ok)
	  _M_widen_init();
	return this->do_widen(__lo, __hi, __to);
      }

      
















 
      char
      narrow(char_type __c, char __dfault) const
      {
	if (_M_narrow[static_cast<unsigned char>(__c)])
	  return _M_narrow[static_cast<unsigned char>(__c)];
	const char __t = do_narrow(__c, __dfault);
	if (__t != __dfault)
	  _M_narrow[static_cast<unsigned char>(__c)] = __t;
	return __t;
      }

      




















 
      const char_type*
      narrow(const char_type* __lo, const char_type* __hi,
	     char __dfault, char *__to) const
      {
	if (__builtin_expect(_M_narrow_ok == 1, true))
	  {
	    __builtin_memcpy(__to, __lo, __hi - __lo);
	    return __hi;
	  }
	if (!_M_narrow_ok)
	  _M_narrow_init();
	return this->do_narrow(__lo, __hi, __dfault, __to);
      }

      
      
      
      
      const mask*
      table() const throw()
      { return _M_table; }

      
      static const mask*
      classic_table() throw();
    protected:

      




 
      virtual
      ~ctype();

      











 
      virtual char_type
      do_toupper(char_type) const;

      












 
      virtual const char_type*
      do_toupper(char_type* __lo, const char_type* __hi) const;

      











 
      virtual char_type
      do_tolower(char_type) const;

      












 
      virtual const char_type*
      do_tolower(char_type* __lo, const char_type* __hi) const;

      















 
      virtual char_type
      do_widen(char __c) const
      { return __c; }

      

















 
      virtual const char*
      do_widen(const char* __lo, const char* __hi, char_type* __dest) const
      {
	__builtin_memcpy(__dest, __lo, __hi - __lo);
	return __hi;
      }

      

















 
      virtual char
      do_narrow(char_type __c, char) const
      { return __c; }

      




















 
      virtual const char_type*
      do_narrow(const char_type* __lo, const char_type* __hi,
		char, char* __dest) const
      {
	__builtin_memcpy(__dest, __lo, __hi - __lo);
	return __hi;
      }

    private:
      void _M_narrow_init() const;
      void _M_widen_init() const;
    };

  









 
  template<>
    class ctype<wchar_t> : public __ctype_abstract_base<wchar_t>
    {
    public:
      
      
      typedef wchar_t		char_type;
      typedef wctype_t		__wmask_type;

    protected:
      __c_locale		_M_c_locale_ctype;

      
      bool                      _M_narrow_ok;
      char                      _M_narrow[128];
      wint_t                    _M_widen[1 + static_cast<unsigned char>(-1)];

      
      mask                      _M_bit[16];
      __wmask_type              _M_wmask[16];

    public:
      
      
      static locale::id		id;

      





 
      explicit
      ctype(size_t __refs = 0);

      






 
      explicit
      ctype(__c_locale __cloc, size_t __refs = 0);

    protected:
      __wmask_type
      _M_convert_to_wmask(const mask __m) const throw();

      
      virtual
      ~ctype();

      











 
      virtual bool
      do_is(mask __m, char_type __c) const;

      














 
      virtual const char_type*
      do_is(const char_type* __lo, const char_type* __hi, mask* __vec) const;

      













 
      virtual const char_type*
      do_scan_is(mask __m, const char_type* __lo, const char_type* __hi) const;

      













 
      virtual const char_type*
      do_scan_not(mask __m, const char_type* __lo,
		  const char_type* __hi) const;

      











 
      virtual char_type
      do_toupper(char_type) const;

      












 
      virtual const char_type*
      do_toupper(char_type* __lo, const char_type* __hi) const;

      











 
      virtual char_type
      do_tolower(char_type) const;

      












 
      virtual const char_type*
      do_tolower(char_type* __lo, const char_type* __hi) const;

      















 
      virtual char_type
      do_widen(char) const;

      

















 
      virtual const char*
      do_widen(const char* __lo, const char* __hi, char_type* __dest) const;

      


















 
      virtual char
      do_narrow(char_type, char __dfault) const;

      





















 
      virtual const char_type*
      do_narrow(const char_type* __lo, const char_type* __hi,
		char __dfault, char* __dest) const;

      
      void
      _M_initialize_ctype() throw();
    };

  
  template<typename _CharT>
    class ctype_byname : public ctype<_CharT>
    {
    public:
      typedef typename ctype<_CharT>::mask  mask;

      explicit
      ctype_byname(const char* __s, size_t __refs = 0);

    protected:
      virtual
      ~ctype_byname() { };
    };

  
  template<>
    class ctype_byname<char> : public ctype<char>
    {
    public:
      explicit
      ctype_byname(const char* __s, size_t __refs = 0);

    protected:
      virtual
      ~ctype_byname();
    };

  template<>
    class ctype_byname<wchar_t> : public ctype<wchar_t>
    {
    public:
      explicit
      ctype_byname(const char* __s, size_t __refs = 0);

    protected:
      virtual
      ~ctype_byname();
    };


} 





























 








namespace std __attribute__ ((__visibility__ ("default")))
{


  bool
  ctype<char>::
  is(mask __m, char __c) const
  { return _M_table[static_cast<unsigned char>(__c)] & __m; }

  const char*
  ctype<char>::
  is(const char* __low, const char* __high, mask* __vec) const
  {
    while (__low < __high)
      *__vec++ = _M_table[static_cast<unsigned char>(*__low++)];
    return __high;
  }

  const char*
  ctype<char>::
  scan_is(mask __m, const char* __low, const char* __high) const
  {
    while (__low < __high
	   && !(_M_table[static_cast<unsigned char>(*__low)] & __m))
      ++__low;
    return __low;
  }

  const char*
  ctype<char>::
  scan_not(mask __m, const char* __low, const char* __high) const
  {
    while (__low < __high
	   && (_M_table[static_cast<unsigned char>(*__low)] & __m) != 0)
      ++__low;
    return __low;
  }


} 

namespace std __attribute__ ((__visibility__ ("default")))
{


  
  class __num_base
  {
  public:
    
    
    enum
      {
        _S_ominus,
        _S_oplus,
        _S_ox,
        _S_oX,
        _S_odigits,
        _S_odigits_end = _S_odigits + 16,
        _S_oudigits = _S_odigits_end,
        _S_oudigits_end = _S_oudigits + 16,
        _S_oe = _S_odigits + 14,  
        _S_oE = _S_oudigits + 14, 
	_S_oend = _S_oudigits_end
      };

    
    
    
    
    
    static const char* _S_atoms_out;

    
    
    static const char* _S_atoms_in;

    enum
    {
      _S_iminus,
      _S_iplus,
      _S_ix,
      _S_iX,
      _S_izero,
      _S_ie = _S_izero + 14,
      _S_iE = _S_izero + 20,
      _S_iend = 26
    };

    
    
    static void
    _S_format_float(const ios_base& __io, char* __fptr, char __mod) throw();
  };

  template<typename _CharT>
    struct __numpunct_cache : public locale::facet
    {
      const char*			_M_grouping;
      size_t                            _M_grouping_size;
      bool				_M_use_grouping;
      const _CharT*			_M_truename;
      size_t                            _M_truename_size;
      const _CharT*			_M_falsename;
      size_t                            _M_falsename_size;
      _CharT				_M_decimal_point;
      _CharT				_M_thousands_sep;

      
      
      
      
      _CharT				_M_atoms_out[__num_base::_S_oend];

      
      
      
      
      _CharT				_M_atoms_in[__num_base::_S_iend];

      bool				_M_allocated;

      __numpunct_cache(size_t __refs = 0)
      : facet(__refs), _M_grouping(0), _M_grouping_size(0),
	_M_use_grouping(false),
	_M_truename(0), _M_truename_size(0), _M_falsename(0),
	_M_falsename_size(0), _M_decimal_point(_CharT()),
	_M_thousands_sep(_CharT()), _M_allocated(false)
        { }

      ~__numpunct_cache();

      void
      _M_cache(const locale& __loc);

    private:
      __numpunct_cache&
      operator=(const __numpunct_cache&);
      
      explicit
      __numpunct_cache(const __numpunct_cache&);
    };

  template<typename _CharT>
    __numpunct_cache<_CharT>::~__numpunct_cache()
    {
      if (_M_allocated)
	{
	  delete [] _M_grouping;
	  delete [] _M_truename;
	  delete [] _M_falsename;
	}
    }

  












 
  template<typename _CharT>
    class numpunct : public locale::facet
    {
    public:
      
      
      
      typedef _CharT			char_type;
      typedef basic_string<_CharT>	string_type;
      
      typedef __numpunct_cache<_CharT>  __cache_type;

    protected:
      __cache_type*			_M_data;

    public:
      
      static locale::id			id;

      



 
      explicit
      numpunct(size_t __refs = 0)
      : facet(__refs), _M_data(0)
      { _M_initialize_numpunct(); }

      







 
      explicit
      numpunct(__cache_type* __cache, size_t __refs = 0)
      : facet(__refs), _M_data(__cache)
      { _M_initialize_numpunct(); }

      







 
      explicit
      numpunct(__c_locale __cloc, size_t __refs = 0)
      : facet(__refs), _M_data(0)
      { _M_initialize_numpunct(__cloc); }

      







 
      char_type
      decimal_point() const
      { return this->do_decimal_point(); }

      







 
      char_type
      thousands_sep() const
      { return this->do_thousands_sep(); }

      

























 
      string
      grouping() const
      { return this->do_grouping(); }

      







 
      string_type
      truename() const
      { return this->do_truename(); }

      







 
      string_type
      falsename() const
      { return this->do_falsename(); }

    protected:
      
      virtual
      ~numpunct();

      






 
      virtual char_type
      do_decimal_point() const
      { return _M_data->_M_decimal_point; }

      






 
      virtual char_type
      do_thousands_sep() const
      { return _M_data->_M_thousands_sep; }

      







 
      virtual string
      do_grouping() const
      { return _M_data->_M_grouping; }

      







 
      virtual string_type
      do_truename() const
      { return _M_data->_M_truename; }

      







 
      virtual string_type
      do_falsename() const
      { return _M_data->_M_falsename; }

      
      void
      _M_initialize_numpunct(__c_locale __cloc = 0);
    };

  template<typename _CharT>
    locale::id numpunct<_CharT>::id;

  template<>
    numpunct<char>::~numpunct();

  template<>
    void
    numpunct<char>::_M_initialize_numpunct(__c_locale __cloc);

  template<>
    numpunct<wchar_t>::~numpunct();

  template<>
    void
    numpunct<wchar_t>::_M_initialize_numpunct(__c_locale __cloc);

  
  template<typename _CharT>
    class numpunct_byname : public numpunct<_CharT>
    {
    public:
      typedef _CharT			char_type;
      typedef basic_string<_CharT>	string_type;

      explicit
      numpunct_byname(const char* __s, size_t __refs = 0)
      : numpunct<_CharT>(__refs)
      {
	if (__builtin_strcmp(__s, "C") != 0
	    && __builtin_strcmp(__s, "POSIX") != 0)
	  {
	    __c_locale __tmp;
	    this->_S_create_c_locale(__tmp, __s);
	    this->_M_initialize_numpunct(__tmp);
	    this->_S_destroy_c_locale(__tmp);
	  }
      }

    protected:
      virtual
      ~numpunct_byname() { }
    };



  











 
  template<typename _CharT, typename _InIter>
    class num_get : public locale::facet
    {
    public:
      
      
      
      typedef _CharT			char_type;
      typedef _InIter			iter_type;
      

      
      static locale::id			id;

      





 
      explicit
      num_get(size_t __refs = 0) : facet(__refs) { }

      





















 
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
	  ios_base::iostate& __err, bool& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }

      
      




























 
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
	  ios_base::iostate& __err, long& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }

      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
	  ios_base::iostate& __err, unsigned short& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }

      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
	  ios_base::iostate& __err, unsigned int& __v)   const
      { return this->do_get(__in, __end, __io, __err, __v); }

      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
	  ios_base::iostate& __err, unsigned long& __v)  const
      { return this->do_get(__in, __end, __io, __err, __v); }

      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
	  ios_base::iostate& __err, long long& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }

      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
	  ios_base::iostate& __err, unsigned long long& __v)  const
      { return this->do_get(__in, __end, __io, __err, __v); }
      

      
      























 
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
	  ios_base::iostate& __err, float& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }

      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
	  ios_base::iostate& __err, double& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }

      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
	  ios_base::iostate& __err, long double& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      

      
























 
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
	  ios_base::iostate& __err, void*& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }

    protected:
      
      virtual ~num_get() { }

      iter_type
      _M_extract_float(iter_type, iter_type, ios_base&, ios_base::iostate&,
		       string&) const;

      template<typename _ValueT>
        iter_type
        _M_extract_int(iter_type, iter_type, ios_base&, ios_base::iostate&,
		       _ValueT&) const;

      template<typename _CharT2>
      typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value, int>::__type
        _M_find(const _CharT2*, size_t __len, _CharT2 __c) const
        {
	  int __ret = -1;
	  if (__len <= 10)
	    {
	      if (__c >= _CharT2('0') && __c < _CharT2(_CharT2('0') + __len))
		__ret = __c - _CharT2('0');
	    }
	  else
	    {
	      if (__c >= _CharT2('0') && __c <= _CharT2('9'))
		__ret = __c - _CharT2('0');
	      else if (__c >= _CharT2('a') && __c <= _CharT2('f'))
		__ret = 10 + (__c - _CharT2('a'));
	      else if (__c >= _CharT2('A') && __c <= _CharT2('F'))
		__ret = 10 + (__c - _CharT2('A'));
	    }
	  return __ret;
	}

      template<typename _CharT2>
      typename __gnu_cxx::__enable_if<!__is_char<_CharT2>::__value, 
				      int>::__type
        _M_find(const _CharT2* __zero, size_t __len, _CharT2 __c) const
        {
	  int __ret = -1;
	  const char_type* __q = char_traits<_CharT2>::find(__zero, __len, __c);
	  if (__q)
	    {
	      __ret = __q - __zero;
	      if (__ret > 15)
		__ret -= 6;
	    }
	  return __ret;
	}

      
      












 
      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate&, bool&) const;

      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
	     ios_base::iostate& __err, long& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }

      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
	     ios_base::iostate& __err, unsigned short& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }

      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
	     ios_base::iostate& __err, unsigned int& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }

      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
	     ios_base::iostate& __err, unsigned long& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }

      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
	     ios_base::iostate& __err, long long& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }	

      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
	     ios_base::iostate& __err, unsigned long long& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }

      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate& __err,
	     float&) const;

      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate& __err,
	     double&) const;

      
      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate& __err,
	     long double&) const;

      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate& __err,
	     void*&) const;

      
      
    };

  template<typename _CharT, typename _InIter>
    locale::id num_get<_CharT, _InIter>::id;


  










 
  template<typename _CharT, typename _OutIter>
    class num_put : public locale::facet
    {
    public:
      
      
      
      typedef _CharT		char_type;
      typedef _OutIter		iter_type;
      

      
      static locale::id		id;

      





 
      explicit
      num_put(size_t __refs = 0) : facet(__refs) { }

      













 
      iter_type
      put(iter_type __s, ios_base& __f, char_type __fill, bool __v) const
      { return this->do_put(__s, __f, __fill, __v); }

      
      



































 
      iter_type
      put(iter_type __s, ios_base& __f, char_type __fill, long __v) const
      { return this->do_put(__s, __f, __fill, __v); }

      iter_type
      put(iter_type __s, ios_base& __f, char_type __fill,
	  unsigned long __v) const
      { return this->do_put(__s, __f, __fill, __v); }

      iter_type
      put(iter_type __s, ios_base& __f, char_type __fill, long long __v) const
      { return this->do_put(__s, __f, __fill, __v); }

      iter_type
      put(iter_type __s, ios_base& __f, char_type __fill,
	  unsigned long long __v) const
      { return this->do_put(__s, __f, __fill, __v); }
      

      
      







































 
      iter_type
      put(iter_type __s, ios_base& __f, char_type __fill, double __v) const
      { return this->do_put(__s, __f, __fill, __v); }

      iter_type
      put(iter_type __s, ios_base& __f, char_type __fill,
	  long double __v) const
      { return this->do_put(__s, __f, __fill, __v); }
      

      













 
      iter_type
      put(iter_type __s, ios_base& __f, char_type __fill,
	  const void* __v) const
      { return this->do_put(__s, __f, __fill, __v); }

    protected:
      template<typename _ValueT>
        iter_type
        _M_insert_float(iter_type, ios_base& __io, char_type __fill,
			char __mod, _ValueT __v) const;

      void
      _M_group_float(const char* __grouping, size_t __grouping_size,
		     char_type __sep, const char_type* __p, char_type* __new,
		     char_type* __cs, int& __len) const;

      template<typename _ValueT>
        iter_type
        _M_insert_int(iter_type, ios_base& __io, char_type __fill,
		      _ValueT __v) const;

      void
      _M_group_int(const char* __grouping, size_t __grouping_size,
		   char_type __sep, ios_base& __io, char_type* __new,
		   char_type* __cs, int& __len) const;

      void
      _M_pad(char_type __fill, streamsize __w, ios_base& __io,
	     char_type* __new, const char_type* __cs, int& __len) const;

      
      virtual
      ~num_put() { };

      
      











 
      virtual iter_type
      do_put(iter_type, ios_base&, char_type __fill, bool __v) const;

      virtual iter_type
      do_put(iter_type __s, ios_base& __io, char_type __fill, long __v) const
      { return _M_insert_int(__s, __io, __fill, __v); }	

      virtual iter_type
      do_put(iter_type __s, ios_base& __io, char_type __fill,
	     unsigned long __v) const
      { return _M_insert_int(__s, __io, __fill, __v); }

      virtual iter_type
      do_put(iter_type __s, ios_base& __io, char_type __fill,
	     long long __v) const
      { return _M_insert_int(__s, __io, __fill, __v); }

      virtual iter_type
      do_put(iter_type __s, ios_base& __io, char_type __fill,
	     unsigned long long __v) const
      { return _M_insert_int(__s, __io, __fill, __v); }

      virtual iter_type
      do_put(iter_type, ios_base&, char_type __fill, double __v) const;

      
      virtual iter_type
      do_put(iter_type, ios_base&, char_type __fill, long double __v) const;

      virtual iter_type
      do_put(iter_type, ios_base&, char_type __fill, const void* __v) const;

      
      
    };

  template <typename _CharT, typename _OutIter>
    locale::id num_put<_CharT, _OutIter>::id;



  
  
  
  

  
  template<typename _CharT>
    inline bool
    isspace(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::space, __c); }

  
  template<typename _CharT>
    inline bool
    isprint(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::print, __c); }

  
  template<typename _CharT>
    inline bool
    iscntrl(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::cntrl, __c); }

  
  template<typename _CharT>
    inline bool
    isupper(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::upper, __c); }

  
  template<typename _CharT>
    inline bool 
    islower(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::lower, __c); }

  
  template<typename _CharT>
    inline bool
    isalpha(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::alpha, __c); }

  
  template<typename _CharT>
    inline bool
    isdigit(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::digit, __c); }

  
  template<typename _CharT>
    inline bool
    ispunct(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::punct, __c); }

  
  template<typename _CharT>
    inline bool
    isxdigit(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::xdigit, __c); }

  
  template<typename _CharT>
    inline bool
    isalnum(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::alnum, __c); }

  
  template<typename _CharT>
    inline bool
    isgraph(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::graph, __c); }

  
  template<typename _CharT>
    inline _CharT
    toupper(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).toupper(__c); }

  
  template<typename _CharT>
    inline _CharT
    tolower(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).tolower(__c); }


} 






























 



namespace std __attribute__ ((__visibility__ ("default")))
{


  
  
  template<typename _Facet>
    struct __use_cache
    {
      const _Facet*
      operator() (const locale& __loc) const;
    };

  
  template<typename _CharT>
    struct __use_cache<__numpunct_cache<_CharT> >
    {
      const __numpunct_cache<_CharT>*
      operator() (const locale& __loc) const
      {
	const size_t __i = numpunct<_CharT>::id._M_id();
	const locale::facet** __caches = __loc._M_impl->_M_caches;
	if (!__caches[__i])
	  {
	    __numpunct_cache<_CharT>* __tmp = 0;
	    try
	      {
		__tmp = new __numpunct_cache<_CharT>;
		__tmp->_M_cache(__loc);
	      }
	    catch(...)
	      {
		delete __tmp;
		throw;
	      }
	    __loc._M_impl->_M_install_cache(__tmp, __i);
	  }
	return static_cast<const __numpunct_cache<_CharT>*>(__caches[__i]);
      }
    };

  template<typename _CharT>
    void
    __numpunct_cache<_CharT>::_M_cache(const locale& __loc)
    {
      _M_allocated = true;

      const numpunct<_CharT>& __np = use_facet<numpunct<_CharT> >(__loc);

      char* __grouping = 0;
      _CharT* __truename = 0;
      _CharT* __falsename = 0;
      try
	{
	  _M_grouping_size = __np.grouping().size();
	  __grouping = new char[_M_grouping_size];
	  __np.grouping().copy(__grouping, _M_grouping_size);
	  _M_grouping = __grouping;
	  _M_use_grouping = (_M_grouping_size
			     && static_cast<signed char>(_M_grouping[0]) > 0
			     && (_M_grouping[0]
				 != __gnu_cxx::__numeric_traits<char>::__max));

	  _M_truename_size = __np.truename().size();
	  __truename = new _CharT[_M_truename_size];
	  __np.truename().copy(__truename, _M_truename_size);
	  _M_truename = __truename;

	  _M_falsename_size = __np.falsename().size();
	  __falsename = new _CharT[_M_falsename_size];
	  __np.falsename().copy(__falsename, _M_falsename_size);
	  _M_falsename = __falsename;

	  _M_decimal_point = __np.decimal_point();
	  _M_thousands_sep = __np.thousands_sep();

	  const ctype<_CharT>& __ct = use_facet<ctype<_CharT> >(__loc);
	  __ct.widen(__num_base::_S_atoms_out,
		     __num_base::_S_atoms_out
		     + __num_base::_S_oend, _M_atoms_out);
	  __ct.widen(__num_base::_S_atoms_in,
		     __num_base::_S_atoms_in
		     + __num_base::_S_iend, _M_atoms_in);
	}
      catch(...)
	{
	  delete [] __grouping;
	  delete [] __truename;
	  delete [] __falsename;
	  throw;
	}
    }

  
  
  
  
  
  
  
  
  __attribute__ ((__pure__)) bool
  __verify_grouping(const char* __grouping, size_t __grouping_size,
		    const string& __grouping_tmp) throw ();



  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    _M_extract_float(_InIter __beg, _InIter __end, ios_base& __io,
		     ios_base::iostate& __err, string& __xtrc) const
    {
      typedef char_traits<_CharT>			__traits_type;
      typedef __numpunct_cache<_CharT>                  __cache_type;
      __use_cache<__cache_type> __uc;
      const locale& __loc = __io._M_getloc();
      const __cache_type* __lc = __uc(__loc);
      const _CharT* __lit = __lc->_M_atoms_in;
      char_type __c = char_type();

      
      bool __testeof = __beg == __end;

      
      if (!__testeof)
	{
	  __c = *__beg;
	  const bool __plus = __c == __lit[__num_base::_S_iplus];
	  if ((__plus || __c == __lit[__num_base::_S_iminus])
	      && !(__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
	      && !(__c == __lc->_M_decimal_point))
	    {
	      __xtrc += __plus ? '+' : '-';
	      if (++__beg != __end)
		__c = *__beg;
	      else
		__testeof = true;
	    }
	}

      
      bool __found_mantissa = false;
      int __sep_pos = 0;
      while (!__testeof)
	{
	  if ((__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
	      || __c == __lc->_M_decimal_point)
	    break;
	  else if (__c == __lit[__num_base::_S_izero])
	    {
	      if (!__found_mantissa)
		{
		  __xtrc += '0';
		  __found_mantissa = true;
		}
	      ++__sep_pos;

	      if (++__beg != __end)
		__c = *__beg;
	      else
		__testeof = true;
	    }
	  else
	    break;
	}

      
      bool __found_dec = false;
      bool __found_sci = false;
      string __found_grouping;
      if (__lc->_M_use_grouping)
	__found_grouping.reserve(32);
      const char_type* __lit_zero = __lit + __num_base::_S_izero;

      if (!__lc->_M_allocated)
	
	while (!__testeof)
	  {
	    const int __digit = _M_find(__lit_zero, 10, __c);
	    if (__digit != -1)
	      {
		__xtrc += '0' + __digit;
		__found_mantissa = true;
	      }
	    else if (__c == __lc->_M_decimal_point
		     && !__found_dec && !__found_sci)
	      {
		__xtrc += '.';
		__found_dec = true;
	      }
	    else if ((__c == __lit[__num_base::_S_ie] 
		      || __c == __lit[__num_base::_S_iE])
		     && !__found_sci && __found_mantissa)
	      {
		
		__xtrc += 'e';
		__found_sci = true;
		
		
		if (++__beg != __end)
		  {
		    __c = *__beg;
		    const bool __plus = __c == __lit[__num_base::_S_iplus];
		    if (__plus || __c == __lit[__num_base::_S_iminus])
		      __xtrc += __plus ? '+' : '-';
		    else
		      continue;
		  }
		else
		  {
		    __testeof = true;
		    break;
		  }
	      }
	    else
	      break;

	    if (++__beg != __end)
	      __c = *__beg;
	    else
	      __testeof = true;
	  }
      else
	while (!__testeof)
	  {
	    
	    
	    if (__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
	      {
		if (!__found_dec && !__found_sci)
		  {
		    
		    
		    if (__sep_pos)
		      {
			__found_grouping += static_cast<char>(__sep_pos);
			__sep_pos = 0;
		      }
		    else
		      {
			
			
			__xtrc.clear();
			break;
		      }
		  }
		else
		  break;
	      }
	    else if (__c == __lc->_M_decimal_point)
	      {
		if (!__found_dec && !__found_sci)
		  {
		    
		    
		    
		    if (__found_grouping.size())
		      __found_grouping += static_cast<char>(__sep_pos);
		    __xtrc += '.';
		    __found_dec = true;
		  }
		else
		  break;
	      }
	    else
	      {
		const char_type* __q =
		  __traits_type::find(__lit_zero, 10, __c);
		if (__q)
		  {
		    __xtrc += '0' + (__q - __lit_zero);
		    __found_mantissa = true;
		    ++__sep_pos;
		  }
		else if ((__c == __lit[__num_base::_S_ie] 
			  || __c == __lit[__num_base::_S_iE])
			 && !__found_sci && __found_mantissa)
		  {
		    
		    if (__found_grouping.size() && !__found_dec)
		      __found_grouping += static_cast<char>(__sep_pos);
		    __xtrc += 'e';
		    __found_sci = true;
		    
		    
		    if (++__beg != __end)
		      {
			__c = *__beg;
			const bool __plus = __c == __lit[__num_base::_S_iplus];
			if ((__plus || __c == __lit[__num_base::_S_iminus])
			    && !(__lc->_M_use_grouping
				 && __c == __lc->_M_thousands_sep)
			    && !(__c == __lc->_M_decimal_point))
		      __xtrc += __plus ? '+' : '-';
			else
			  continue;
		      }
		    else
		      {
			__testeof = true;
			break;
		      }
		  }
		else
		  break;
	      }
	    
	    if (++__beg != __end)
	      __c = *__beg;
	    else
	      __testeof = true;
	  }

      
      
      if (__found_grouping.size())
        {
          
	  if (!__found_dec && !__found_sci)
	    __found_grouping += static_cast<char>(__sep_pos);

          if (!std::__verify_grouping(__lc->_M_grouping, 
				      __lc->_M_grouping_size,
				      __found_grouping))
	    __err = ios_base::failbit;
        }

      return __beg;
    }

  template<typename _CharT, typename _InIter>
    template<typename _ValueT>
      _InIter
      num_get<_CharT, _InIter>::
      _M_extract_int(_InIter __beg, _InIter __end, ios_base& __io,
		     ios_base::iostate& __err, _ValueT& __v) const
      {
        typedef char_traits<_CharT>			     __traits_type;
	using __gnu_cxx::__add_unsigned;
	typedef typename __add_unsigned<_ValueT>::__type __unsigned_type;
	typedef __numpunct_cache<_CharT>                     __cache_type;
	__use_cache<__cache_type> __uc;
	const locale& __loc = __io._M_getloc();
	const __cache_type* __lc = __uc(__loc);
	const _CharT* __lit = __lc->_M_atoms_in;
	char_type __c = char_type();

	
	const ios_base::fmtflags __basefield = __io.flags()
	                                       & ios_base::basefield;
	const bool __oct = __basefield == ios_base::oct;
	int __base = __oct ? 8 : (__basefield == ios_base::hex ? 16 : 10);

	
	bool __testeof = __beg == __end;

	
	bool __negative = false;
	if (!__testeof)
	  {
	    __c = *__beg;
	    __negative = __c == __lit[__num_base::_S_iminus];
	    if ((__negative || __c == __lit[__num_base::_S_iplus])
		&& !(__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
		&& !(__c == __lc->_M_decimal_point))
	      {
		if (++__beg != __end)
		  __c = *__beg;
		else
		  __testeof = true;
	      }
	  }

	
	
	bool __found_zero = false;
	int __sep_pos = 0;
	while (!__testeof)
	  {
	    if ((__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
		|| __c == __lc->_M_decimal_point)
	      break;
	    else if (__c == __lit[__num_base::_S_izero] 
		     && (!__found_zero || __base == 10))
	      {
		__found_zero = true;
		++__sep_pos;
		if (__basefield == 0)
		  __base = 8;
		if (__base == 8)
		  __sep_pos = 0;
	      }
	    else if (__found_zero
		     && (__c == __lit[__num_base::_S_ix]
			 || __c == __lit[__num_base::_S_iX]))
	      {
		if (__basefield == 0)
		  __base = 16;
		if (__base == 16)
		  {
		    __found_zero = false;
		    __sep_pos = 0;
		  }
		else
		  break;
	      }
	    else
	      break;

	    if (++__beg != __end)
	      {
		__c = *__beg;
		if (!__found_zero)
		  break;
	      }
	    else
	      __testeof = true;
	  }
	
	
	
	const size_t __len = (__base == 16 ? __num_base::_S_iend
			      - __num_base::_S_izero : __base);

	
	string __found_grouping;
	if (__lc->_M_use_grouping)
	  __found_grouping.reserve(32);
	bool __testfail = false;
	bool __testoverflow = false;
	const __unsigned_type __max =
	  (__negative && __gnu_cxx::__numeric_traits<_ValueT>::__is_signed)
	  ? -__gnu_cxx::__numeric_traits<_ValueT>::__min
	  : __gnu_cxx::__numeric_traits<_ValueT>::__max;
	const __unsigned_type __smax = __max / __base;
	__unsigned_type __result = 0;
	int __digit = 0;
	const char_type* __lit_zero = __lit + __num_base::_S_izero;

	if (!__lc->_M_allocated)
	  
	  while (!__testeof)
	    {
	      __digit = _M_find(__lit_zero, __len, __c);
	      if (__digit == -1)
		break;
	      
	      if (__result > __smax)
		__testoverflow = true;
	      else
		{
		  __result *= __base;
		  __testoverflow |= __result > __max - __digit;
		  __result += __digit;
		  ++__sep_pos;
		}
	      
	      if (++__beg != __end)
		__c = *__beg;
	      else
		__testeof = true;
	    }
	else
	  while (!__testeof)
	    {
	      
	      
	      if (__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
		{
		  
		  
		  if (__sep_pos)
		    {
		      __found_grouping += static_cast<char>(__sep_pos);
		      __sep_pos = 0;
		    }
		  else
		    {
		      __testfail = true;
		      break;
		    }
		}
	      else if (__c == __lc->_M_decimal_point)
		break;
	      else
		{
		  const char_type* __q =
		    __traits_type::find(__lit_zero, __len, __c);
		  if (!__q)
		    break;
		  
		  __digit = __q - __lit_zero;
		  if (__digit > 15)
		    __digit -= 6;
		  if (__result > __smax)
		    __testoverflow = true;
		  else
		    {
		      __result *= __base;
		      __testoverflow |= __result > __max - __digit;
		      __result += __digit;
		      ++__sep_pos;
		    }
		}
	      
	      if (++__beg != __end)
		__c = *__beg;
	      else
		__testeof = true;
	    }
	
	
	
	if (__found_grouping.size())
	  {
	    
	    __found_grouping += static_cast<char>(__sep_pos);

	    if (!std::__verify_grouping(__lc->_M_grouping,
					__lc->_M_grouping_size,
					__found_grouping))
	      __err = ios_base::failbit;
	  }

	
	
	if ((!__sep_pos && !__found_zero && !__found_grouping.size())
	    || __testfail)
	  {
	    __v = 0;
	    __err = ios_base::failbit;
	  }
	else if (__testoverflow)
	  {
	    if (__negative
		&& __gnu_cxx::__numeric_traits<_ValueT>::__is_signed)
	      __v = __gnu_cxx::__numeric_traits<_ValueT>::__min;
	    else
	      __v = __gnu_cxx::__numeric_traits<_ValueT>::__max;
	    __err = ios_base::failbit;
	  }
	else
	  __v = __negative ? -__result : __result;

	if (__testeof)
	  __err |= ios_base::eofbit;
	return __beg;
      }

  
  
  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
           ios_base::iostate& __err, bool& __v) const
    {
      if (!(__io.flags() & ios_base::boolalpha))
        {
	  
          
          
	  long __l = -1;
          __beg = _M_extract_int(__beg, __end, __io, __err, __l);
	  if (__l == 0 || __l == 1)
	    __v = bool(__l);
	  else
	    {
	      
	      
	      __v = true;
	      __err = ios_base::failbit;
	      if (__beg == __end)
		__err |= ios_base::eofbit;
	    }
        }
      else
        {
	  
	  typedef __numpunct_cache<_CharT>  __cache_type;
	  __use_cache<__cache_type> __uc;
	  const locale& __loc = __io._M_getloc();
	  const __cache_type* __lc = __uc(__loc);

	  bool __testf = true;
	  bool __testt = true;
	  bool __donef = __lc->_M_falsename_size == 0;
	  bool __donet = __lc->_M_truename_size == 0;
	  bool __testeof = false;
	  size_t __n = 0;
	  while (!__donef || !__donet)
	    {
	      if (__beg == __end)
		{
		  __testeof = true;
		  break;
		}

	      const char_type __c = *__beg;

	      if (!__donef)
		__testf = __c == __lc->_M_falsename[__n];

	      if (!__testf && __donet)
		break;

	      if (!__donet)
		__testt = __c == __lc->_M_truename[__n];

	      if (!__testt && __donef)
		break;

	      if (!__testt && !__testf)
		break;

	      ++__n;
	      ++__beg;

	      __donef = !__testf || __n >= __lc->_M_falsename_size;
	      __donet = !__testt || __n >= __lc->_M_truename_size;
	    }
	  if (__testf && __n == __lc->_M_falsename_size && __n)
	    {
	      __v = false;
	      if (__testt && __n == __lc->_M_truename_size)
		__err = ios_base::failbit;
	      else
		__err = __testeof ? ios_base::eofbit : ios_base::goodbit;
	    }
	  else if (__testt && __n == __lc->_M_truename_size && __n)
	    {
	      __v = true;
	      __err = __testeof ? ios_base::eofbit : ios_base::goodbit;
	    }
	  else
	    {
	      
	      
	      __v = false;
	      __err = ios_base::failbit;
	      if (__testeof)
		__err |= ios_base::eofbit;
	    }
	}
      return __beg;
    }

  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
	   ios_base::iostate& __err, float& __v) const
    {
      string __xtrc;
      __xtrc.reserve(32);
      __beg = _M_extract_float(__beg, __end, __io, __err, __xtrc);
      std::__convert_to_v(__xtrc.c_str(), __v, __err, _S_get_c_locale());
      if (__beg == __end)
	__err |= ios_base::eofbit;
      return __beg;
    }

  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
           ios_base::iostate& __err, double& __v) const
    {
      string __xtrc;
      __xtrc.reserve(32);
      __beg = _M_extract_float(__beg, __end, __io, __err, __xtrc);
      std::__convert_to_v(__xtrc.c_str(), __v, __err, _S_get_c_locale());
      if (__beg == __end)
	__err |= ios_base::eofbit;
      return __beg;
    }


  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
           ios_base::iostate& __err, long double& __v) const
    {
      string __xtrc;
      __xtrc.reserve(32);
      __beg = _M_extract_float(__beg, __end, __io, __err, __xtrc);
      std::__convert_to_v(__xtrc.c_str(), __v, __err, _S_get_c_locale());
      if (__beg == __end)
	__err |= ios_base::eofbit;
      return __beg;
    }

  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
           ios_base::iostate& __err, void*& __v) const
    {
      
      typedef ios_base::fmtflags        fmtflags;
      const fmtflags __fmt = __io.flags();
      __io.flags((__fmt & ~ios_base::basefield) | ios_base::hex);

      typedef __gnu_cxx::__conditional_type<(sizeof(void*)
					     <= sizeof(unsigned long)),
	unsigned long, unsigned long long>::__type _UIntPtrType;       

      _UIntPtrType __ul;
      __beg = _M_extract_int(__beg, __end, __io, __err, __ul);

      
      __io.flags(__fmt);

      __v = reinterpret_cast<void*>(__ul);
      return __beg;
    }

  
  
  template<typename _CharT, typename _OutIter>
    void
    num_put<_CharT, _OutIter>::
    _M_pad(_CharT __fill, streamsize __w, ios_base& __io,
	   _CharT* __new, const _CharT* __cs, int& __len) const
    {
      
      
      __pad<_CharT, char_traits<_CharT> >::_S_pad(__io, __fill, __new,
						  __cs, __w, __len);
      __len = static_cast<int>(__w);
    }



  template<typename _CharT, typename _ValueT>
    int
    __int_to_char(_CharT* __bufend, _ValueT __v, const _CharT* __lit,
		  ios_base::fmtflags __flags, bool __dec)
    {
      _CharT* __buf = __bufend;
      if (__builtin_expect(__dec, true))
	{
	  
	  do
	    {
	      *--__buf = __lit[(__v % 10) + __num_base::_S_odigits];
	      __v /= 10;
	    }
	  while (__v != 0);
	}
      else if ((__flags & ios_base::basefield) == ios_base::oct)
	{
	  
	  do
	    {
	      *--__buf = __lit[(__v & 0x7) + __num_base::_S_odigits];
	      __v >>= 3;
	    }
	  while (__v != 0);
	}
      else
	{
	  
	  const bool __uppercase = __flags & ios_base::uppercase;
	  const int __case_offset = __uppercase ? __num_base::_S_oudigits
	                                        : __num_base::_S_odigits;
	  do
	    {
	      *--__buf = __lit[(__v & 0xf) + __case_offset];
	      __v >>= 4;
	    }
	  while (__v != 0);
	}
      return __bufend - __buf;
    }



  template<typename _CharT, typename _OutIter>
    void
    num_put<_CharT, _OutIter>::
    _M_group_int(const char* __grouping, size_t __grouping_size, _CharT __sep,
		 ios_base&, _CharT* __new, _CharT* __cs, int& __len) const
    {
      _CharT* __p = std::__add_grouping(__new, __sep, __grouping,
					__grouping_size, __cs, __cs + __len);
      __len = __p - __new;
    }
  
  template<typename _CharT, typename _OutIter>
    template<typename _ValueT>
      _OutIter
      num_put<_CharT, _OutIter>::
      _M_insert_int(_OutIter __s, ios_base& __io, _CharT __fill,
		    _ValueT __v) const
      {
	using __gnu_cxx::__add_unsigned;
	typedef typename __add_unsigned<_ValueT>::__type __unsigned_type;
	typedef __numpunct_cache<_CharT>	             __cache_type;
	__use_cache<__cache_type> __uc;
	const locale& __loc = __io._M_getloc();
	const __cache_type* __lc = __uc(__loc);
	const _CharT* __lit = __lc->_M_atoms_out;
	const ios_base::fmtflags __flags = __io.flags();

	
	const int __ilen = 5 * sizeof(_ValueT);
	_CharT* __cs = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
							     * __ilen));

	
	
	const ios_base::fmtflags __basefield = __flags & ios_base::basefield;
	const bool __dec = (__basefield != ios_base::oct
			    && __basefield != ios_base::hex);
	const __unsigned_type __u = ((__v > 0 || !__dec)
				     ? __unsigned_type(__v)
				     : -__unsigned_type(__v));
 	int __len = __int_to_char(__cs + __ilen, __u, __lit, __flags, __dec);
	__cs += __ilen - __len;

	
	if (__lc->_M_use_grouping)
	  {
	    
	    
	    _CharT* __cs2 = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
								  * (__len + 1)
								  * 2));
	    _M_group_int(__lc->_M_grouping, __lc->_M_grouping_size,
			 __lc->_M_thousands_sep, __io, __cs2 + 2, __cs, __len);
	    __cs = __cs2 + 2;
	  }

	
	if (__builtin_expect(__dec, true))
	  {
	    
	    if (__v >= 0)
	      {
		if (bool(__flags & ios_base::showpos)
		    && __gnu_cxx::__numeric_traits<_ValueT>::__is_signed)
		  *--__cs = __lit[__num_base::_S_oplus], ++__len;
	      }
	    else
	      *--__cs = __lit[__num_base::_S_ominus], ++__len;
	  }
	else if (bool(__flags & ios_base::showbase) && __v)
	  {
	    if (__basefield == ios_base::oct)
	      *--__cs = __lit[__num_base::_S_odigits], ++__len;
	    else
	      {
		
		const bool __uppercase = __flags & ios_base::uppercase;
		*--__cs = __lit[__num_base::_S_ox + __uppercase];
		
		*--__cs = __lit[__num_base::_S_odigits];
		__len += 2;
	      }
	  }

	
	const streamsize __w = __io.width();
	if (__w > static_cast<streamsize>(__len))
	  {
	    _CharT* __cs3 = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
								  * __w));
	    _M_pad(__fill, __w, __io, __cs3, __cs, __len);
	    __cs = __cs3;
	  }
	__io.width(0);

	
	
	return std::__write(__s, __cs, __len);
      }

  template<typename _CharT, typename _OutIter>
    void
    num_put<_CharT, _OutIter>::
    _M_group_float(const char* __grouping, size_t __grouping_size,
		   _CharT __sep, const _CharT* __p, _CharT* __new,
		   _CharT* __cs, int& __len) const
    {
      
      
      
      const int __declen = __p ? __p - __cs : __len;
      _CharT* __p2 = std::__add_grouping(__new, __sep, __grouping,
					 __grouping_size,
					 __cs, __cs + __declen);

      
      int __newlen = __p2 - __new;
      if (__p)
	{
	  char_traits<_CharT>::copy(__p2, __p, __len - __declen);
	  __newlen += __len - __declen;
	}
      __len = __newlen;
    }

  
  
  
  
  
  
  
  
  
  
  template<typename _CharT, typename _OutIter>
    template<typename _ValueT>
      _OutIter
      num_put<_CharT, _OutIter>::
      _M_insert_float(_OutIter __s, ios_base& __io, _CharT __fill, char __mod,
		       _ValueT __v) const
      {
	typedef __numpunct_cache<_CharT>                __cache_type;
	__use_cache<__cache_type> __uc;
	const locale& __loc = __io._M_getloc();
	const __cache_type* __lc = __uc(__loc);

	
	const streamsize __prec = __io.precision() < 0 ? 6 : __io.precision();

	const int __max_digits =
	  __gnu_cxx::__numeric_traits<_ValueT>::__digits10;

	
	int __len;
	
	char __fbuf[16];
	__num_base::_S_format_float(__io, __fbuf, __mod);

	
	
	int __cs_size = __max_digits * 3;
	char* __cs = static_cast<char*>(__builtin_alloca(__cs_size));
	__len = std::__convert_from_v(_S_get_c_locale(), __cs, __cs_size,
				      __fbuf, __prec, __v);

	
	if (__len >= __cs_size)
	  {
	    __cs_size = __len + 1;
	    __cs = static_cast<char*>(__builtin_alloca(__cs_size));
	    __len = std::__convert_from_v(_S_get_c_locale(), __cs, __cs_size,
					  __fbuf, __prec, __v);
	  }

	
	
	const ctype<_CharT>& __ctype = use_facet<ctype<_CharT> >(__loc);
	
	_CharT* __ws = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
							     * __len));
	__ctype.widen(__cs, __cs + __len, __ws);
	
	
	_CharT* __wp = 0;
	const char* __p = char_traits<char>::find(__cs, __len, '.');
	if (__p)
	  {
	    __wp = __ws + (__p - __cs);
	    *__wp = __lc->_M_decimal_point;
	  }
	
	
	
	
	if (__lc->_M_use_grouping
	    && (__wp || __len < 3 || (__cs[1] <= '9' && __cs[2] <= '9'
				      && __cs[1] >= '0' && __cs[2] >= '0')))
	  {
	    
	    
	    _CharT* __ws2 = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
								  * __len * 2));
	    
	    streamsize __off = 0;
	    if (__cs[0] == '-' || __cs[0] == '+')
	      {
		__off = 1;
		__ws2[0] = __ws[0];
		__len -= 1;
	      }
	    
	    _M_group_float(__lc->_M_grouping, __lc->_M_grouping_size,
			   __lc->_M_thousands_sep, __wp, __ws2 + __off,
			   __ws + __off, __len);
	    __len += __off;
	    
	    __ws = __ws2;
	  }

	
	const streamsize __w = __io.width();
	if (__w > static_cast<streamsize>(__len))
	  {
	    _CharT* __ws3 = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
								  * __w));
	    _M_pad(__fill, __w, __io, __ws3, __ws, __len);
	    __ws = __ws3;
	  }
	__io.width(0);
	
	
	
	return std::__write(__s, __ws, __len);
      }
  
  template<typename _CharT, typename _OutIter>
    _OutIter
    num_put<_CharT, _OutIter>::
    do_put(iter_type __s, ios_base& __io, char_type __fill, bool __v) const
    {
      const ios_base::fmtflags __flags = __io.flags();
      if ((__flags & ios_base::boolalpha) == 0)
        {
          const long __l = __v;
          __s = _M_insert_int(__s, __io, __fill, __l);
        }
      else
        {
	  typedef __numpunct_cache<_CharT>              __cache_type;
	  __use_cache<__cache_type> __uc;
	  const locale& __loc = __io._M_getloc();
	  const __cache_type* __lc = __uc(__loc);

	  const _CharT* __name = __v ? __lc->_M_truename
	                             : __lc->_M_falsename;
	  int __len = __v ? __lc->_M_truename_size
	                  : __lc->_M_falsename_size;

	  const streamsize __w = __io.width();
	  if (__w > static_cast<streamsize>(__len))
	    {
	      const streamsize __plen = __w - __len;
	      _CharT* __ps
		= static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
							* __plen));

	      char_traits<_CharT>::assign(__ps, __plen, __fill);
	      __io.width(0);

	      if ((__flags & ios_base::adjustfield) == ios_base::left)
		{
		  __s = std::__write(__s, __name, __len);
		  __s = std::__write(__s, __ps, __plen);
		}
	      else
		{
		  __s = std::__write(__s, __ps, __plen);
		  __s = std::__write(__s, __name, __len);
		}
	      return __s;
	    }
	  __io.width(0);
	  __s = std::__write(__s, __name, __len);
	}
      return __s;
    }

  template<typename _CharT, typename _OutIter>
    _OutIter
    num_put<_CharT, _OutIter>::
    do_put(iter_type __s, ios_base& __io, char_type __fill, double __v) const
    { return _M_insert_float(__s, __io, __fill, char(), __v); }


  template<typename _CharT, typename _OutIter>
    _OutIter
    num_put<_CharT, _OutIter>::
    do_put(iter_type __s, ios_base& __io, char_type __fill,
	   long double __v) const
    { return _M_insert_float(__s, __io, __fill, 'L', __v); }

  template<typename _CharT, typename _OutIter>
    _OutIter
    num_put<_CharT, _OutIter>::
    do_put(iter_type __s, ios_base& __io, char_type __fill,
           const void* __v) const
    {
      const ios_base::fmtflags __flags = __io.flags();
      const ios_base::fmtflags __fmt = ~(ios_base::basefield
					 | ios_base::uppercase);
      __io.flags((__flags & __fmt) | (ios_base::hex | ios_base::showbase));

      typedef __gnu_cxx::__conditional_type<(sizeof(const void*)
					     <= sizeof(unsigned long)),
	unsigned long, unsigned long long>::__type _UIntPtrType;       

      __s = _M_insert_int(__s, __io, __fill,
			  reinterpret_cast<_UIntPtrType>(__v));
      __io.flags(__flags);
      return __s;
    }



  
  
  
  

  
  
  template<typename _CharT, typename _Traits>
    void
    __pad<_CharT, _Traits>::_S_pad(ios_base& __io, _CharT __fill,
				   _CharT* __news, const _CharT* __olds,
				   streamsize __newlen, streamsize __oldlen)
    {
      const size_t __plen = static_cast<size_t>(__newlen - __oldlen);
      const ios_base::fmtflags __adjust = __io.flags() & ios_base::adjustfield;

      
      if (__adjust == ios_base::left)
	{
	  _Traits::copy(__news, __olds, __oldlen);
	  _Traits::assign(__news + __oldlen, __plen, __fill);
	  return;
	}

      size_t __mod = 0;
      if (__adjust == ios_base::internal)
	{
	  
	  
	  
          const locale& __loc = __io._M_getloc();
	  const ctype<_CharT>& __ctype = use_facet<ctype<_CharT> >(__loc);

	  if (__ctype.widen('-') == __olds[0]
	      || __ctype.widen('+') == __olds[0])
	    {
	      __news[0] = __olds[0];
	      __mod = 1;
	      ++__news;
	    }
	  else if (__ctype.widen('0') == __olds[0]
		   && __oldlen > 1
		   && (__ctype.widen('x') == __olds[1]
		       || __ctype.widen('X') == __olds[1]))
	    {
	      __news[0] = __olds[0];
	      __news[1] = __olds[1];
	      __mod = 2;
	      __news += 2;
	    }
	  
	}
      _Traits::assign(__news, __plen, __fill);
      _Traits::copy(__news + __plen, __olds + __mod, __oldlen - __mod);
    }

  template<typename _CharT>
    _CharT*
    __add_grouping(_CharT* __s, _CharT __sep,
		   const char* __gbeg, size_t __gsize,
		   const _CharT* __first, const _CharT* __last)
    {
      size_t __idx = 0;
      size_t __ctr = 0;

      while (__last - __first > __gbeg[__idx]
	     && static_cast<signed char>(__gbeg[__idx]) > 0
	     && __gbeg[__idx] != __gnu_cxx::__numeric_traits<char>::__max)
	{
	  __last -= __gbeg[__idx];
	  __idx < __gsize - 1 ? ++__idx : ++__ctr;
	}

      while (__first != __last)
	*__s++ = *__first++;

      while (__ctr--)
	{
	  *__s++ = __sep;	  
	  for (char __i = __gbeg[__idx]; __i > 0; --__i)
	    *__s++ = *__first++;
	}

      while (__idx--)
	{
	  *__s++ = __sep;	  
	  for (char __i = __gbeg[__idx]; __i > 0; --__i)
	    *__s++ = *__first++;
	}

      return __s;
    }

  
  
  extern template class numpunct<char>;
  extern template class numpunct_byname<char>;
  extern template class  num_get<char>;
  extern template class  num_put<char>;
  extern template class ctype_byname<char>;

  extern template
    const ctype<char>&
    use_facet<ctype<char> >(const locale&);

  extern template
    const numpunct<char>&
    use_facet<numpunct<char> >(const locale&);

  extern template
    const num_put<char>&
    use_facet<num_put<char> >(const locale&);

  extern template
    const num_get<char>&
    use_facet<num_get<char> >(const locale&);

  extern template
    bool
    has_facet<ctype<char> >(const locale&);

  extern template
    bool
    has_facet<numpunct<char> >(const locale&);

  extern template
    bool
    has_facet<num_put<char> >(const locale&);

  extern template
    bool
    has_facet<num_get<char> >(const locale&);

  extern template class numpunct<wchar_t>;
  extern template class numpunct_byname<wchar_t>;
  extern template class  num_get<wchar_t>;
  extern template class  num_put<wchar_t>;
  extern template class ctype_byname<wchar_t>;

  extern template
    const ctype<wchar_t>&
    use_facet<ctype<wchar_t> >(const locale&);

  extern template
    const numpunct<wchar_t>&
    use_facet<numpunct<wchar_t> >(const locale&);

  extern template
    const num_put<wchar_t>&
    use_facet<num_put<wchar_t> >(const locale&);

  extern template
    const num_get<wchar_t>&
    use_facet<num_get<wchar_t> >(const locale&);

 extern template
    bool
    has_facet<ctype<wchar_t> >(const locale&);

  extern template
    bool
    has_facet<numpunct<wchar_t> >(const locale&);

  extern template
    bool
    has_facet<num_put<wchar_t> >(const locale&);

  extern template
    bool
    has_facet<num_get<wchar_t> >(const locale&);


} 



namespace std __attribute__ ((__visibility__ ("default")))
{


  template<typename _Facet>
    inline const _Facet&
    __check_facet(const _Facet* __f)
    {
      if (!__f)
	__throw_bad_cast();
      return *__f;
    }

  
  





 
  template<typename _CharT, typename _Traits>
    class basic_ios : public ios_base
    {
    public:
      
      



 
      typedef _CharT                                 char_type;
      typedef typename _Traits::int_type             int_type;
      typedef typename _Traits::pos_type             pos_type;
      typedef typename _Traits::off_type             off_type;
      typedef _Traits                                traits_type;
      

      
      

 
      typedef ctype<_CharT>                          __ctype_type;
      typedef num_put<_CharT, ostreambuf_iterator<_CharT, _Traits> >
						     __num_put_type;
      typedef num_get<_CharT, istreambuf_iterator<_CharT, _Traits> >
						     __num_get_type;
      

      
    protected:
      basic_ostream<_CharT, _Traits>*                _M_tie;
      mutable char_type                              _M_fill;
      mutable bool                                   _M_fill_init;
      basic_streambuf<_CharT, _Traits>*              _M_streambuf;

      
      const __ctype_type*                            _M_ctype;
      
      const __num_put_type*                          _M_num_put;
      
      const __num_get_type*                          _M_num_get;

    public:
      
      




 
      operator void*() const
      { return this->fail() ? 0 : const_cast<basic_ios*>(this); }

      bool
      operator!() const
      { return this->fail(); }
      

      





 
      iostate
      rdstate() const
      { return _M_streambuf_state; }

      





 
      void
      clear(iostate __state = goodbit);

      




 
      void
      setstate(iostate __state)
      { this->clear(this->rdstate() | __state); }

      
      
      
      void
      _M_setstate(iostate __state)
      {
	
	
	_M_streambuf_state |= __state;
	if (this->exceptions() & __state)
	  throw;
      }

      




 
      bool
      good() const
      { return this->rdstate() == 0; }

      




 
      bool
      eof() const
      { return (this->rdstate() & eofbit) != 0; }

      





 
      bool
      fail() const
      { return (this->rdstate() & (badbit | failbit)) != 0; }

      




 
      bool
      bad() const
      { return (this->rdstate() & badbit) != 0; }

      





 
      iostate
      exceptions() const
      { return _M_exception; }

      





























 
      void
      exceptions(iostate __except)
      {
        _M_exception = __except;
        this->clear(_M_streambuf_state);
      }

      
      



 
      explicit
      basic_ios(basic_streambuf<_CharT, _Traits>* __sb)
      : ios_base(), _M_tie(0), _M_fill(), _M_fill_init(false), _M_streambuf(0),
	_M_ctype(0), _M_num_put(0), _M_num_get(0)
      { this->init(__sb); }

      




 
      virtual
      ~basic_ios() { }

      
      







 
      basic_ostream<_CharT, _Traits>*
      tie() const
      { return _M_tie; }

      






 
      basic_ostream<_CharT, _Traits>*
      tie(basic_ostream<_CharT, _Traits>* __tiestr)
      {
        basic_ostream<_CharT, _Traits>* __old = _M_tie;
        _M_tie = __tiestr;
        return __old;
      }

      




 
      basic_streambuf<_CharT, _Traits>*
      rdbuf() const
      { return _M_streambuf; }

      




















 
      basic_streambuf<_CharT, _Traits>*
      rdbuf(basic_streambuf<_CharT, _Traits>* __sb);

      









 
      basic_ios&
      copyfmt(const basic_ios& __rhs);

      




 
      char_type
      fill() const
      {
	if (!_M_fill_init)
	  {
	    _M_fill = this->widen(' ');
	    _M_fill_init = true;
	  }
	return _M_fill;
      }

      







 
      char_type
      fill(char_type __ch)
      {
	char_type __old = this->fill();
	_M_fill = __ch;
	return __old;
      }

      
      









 
      locale
      imbue(const locale& __loc);

      















 
      char
      narrow(char_type __c, char __dfault) const
      { return __check_facet(_M_ctype).narrow(__c, __dfault); }

      













 
      char_type
      widen(char __c) const
      { return __check_facet(_M_ctype).widen(__c); }

    protected:
      
      




 
      basic_ios()
      : ios_base(), _M_tie(0), _M_fill(char_type()), _M_fill_init(false), 
	_M_streambuf(0), _M_ctype(0), _M_num_put(0), _M_num_get(0)
      { }

      




 
      void
      init(basic_streambuf<_CharT, _Traits>* __sb);

      void
      _M_cache_locale(const locale& __loc);
    };


} 





























 



namespace std __attribute__ ((__visibility__ ("default")))
{


  template<typename _CharT, typename _Traits>
    void
    basic_ios<_CharT, _Traits>::clear(iostate __state)
    {
      if (this->rdbuf())
	_M_streambuf_state = __state;
      else
	  _M_streambuf_state = __state | badbit;
      if (this->exceptions() & this->rdstate())
	__throw_ios_failure(("basic_ios::clear"));
    }

  template<typename _CharT, typename _Traits>
    basic_streambuf<_CharT, _Traits>*
    basic_ios<_CharT, _Traits>::rdbuf(basic_streambuf<_CharT, _Traits>* __sb)
    {
      basic_streambuf<_CharT, _Traits>* __old = _M_streambuf;
      _M_streambuf = __sb;
      this->clear();
      return __old;
    }

  template<typename _CharT, typename _Traits>
    basic_ios<_CharT, _Traits>&
    basic_ios<_CharT, _Traits>::copyfmt(const basic_ios& __rhs)
    {
      
      
      if (this != &__rhs)
	{
	  
	  

	  
	  _Words* __words = (__rhs._M_word_size <= _S_local_word_size) ?
	                     _M_local_word : new _Words[__rhs._M_word_size];

	  
	  _Callback_list* __cb = __rhs._M_callbacks;
	  if (__cb)
	    __cb->_M_add_reference();
	  _M_call_callbacks(erase_event);
	  if (_M_word != _M_local_word)
	    {
	      delete [] _M_word;
	      _M_word = 0;
	    }
	  _M_dispose_callbacks();

	  
	  _M_callbacks = __cb;
	  for (int __i = 0; __i < __rhs._M_word_size; ++__i)
	    __words[__i] = __rhs._M_word[__i];
	  _M_word = __words;
	  _M_word_size = __rhs._M_word_size;

	  this->flags(__rhs.flags());
	  this->width(__rhs.width());
	  this->precision(__rhs.precision());
	  this->tie(__rhs.tie());
	  this->fill(__rhs.fill());
	  _M_ios_locale = __rhs.getloc();
	  _M_cache_locale(_M_ios_locale);

	  _M_call_callbacks(copyfmt_event);

	  
	  this->exceptions(__rhs.exceptions());
	}
      return *this;
    }

  
  template<typename _CharT, typename _Traits>
    locale
    basic_ios<_CharT, _Traits>::imbue(const locale& __loc)
    {
      locale __old(this->getloc());
      ios_base::imbue(__loc);
      _M_cache_locale(__loc);
      if (this->rdbuf() != 0)
	this->rdbuf()->pubimbue(__loc);
      return __old;
    }

  template<typename _CharT, typename _Traits>
    void
    basic_ios<_CharT, _Traits>::init(basic_streambuf<_CharT, _Traits>* __sb)
    {
      
      ios_base::_M_init();

      
      _M_cache_locale(_M_ios_locale);

      
      
      
      
      
      
      
      
      
      
      
      
      _M_fill = _CharT();
      _M_fill_init = false;

      _M_tie = 0;
      _M_exception = goodbit;
      _M_streambuf = __sb;
      _M_streambuf_state = __sb ? goodbit : badbit;
    }

  template<typename _CharT, typename _Traits>
    void
    basic_ios<_CharT, _Traits>::_M_cache_locale(const locale& __loc)
    {
      if (__builtin_expect(has_facet<__ctype_type>(__loc), true))
	_M_ctype = &use_facet<__ctype_type>(__loc);
      else
	_M_ctype = 0;

      if (__builtin_expect(has_facet<__num_put_type>(__loc), true))
	_M_num_put = &use_facet<__num_put_type>(__loc);
      else
	_M_num_put = 0;

      if (__builtin_expect(has_facet<__num_get_type>(__loc), true))
	_M_num_get = &use_facet<__num_get_type>(__loc);
      else
	_M_num_get = 0;
    }

  
  
  extern template class basic_ios<char>;

  extern template class basic_ios<wchar_t>;


} 




namespace std __attribute__ ((__visibility__ ("default")))
{


  
  






 
  template<typename _CharT, typename _Traits>
    class basic_ostream : virtual public basic_ios<_CharT, _Traits>
    {
    public:
      
      typedef _CharT                     		char_type;
      typedef typename _Traits::int_type 		int_type;
      typedef typename _Traits::pos_type 		pos_type;
      typedef typename _Traits::off_type 		off_type;
      typedef _Traits                    		traits_type;
      
      
      typedef basic_streambuf<_CharT, _Traits> 		__streambuf_type;
      typedef basic_ios<_CharT, _Traits>		__ios_type;
      typedef basic_ostream<_CharT, _Traits>		__ostream_type;
      typedef num_put<_CharT, ostreambuf_iterator<_CharT, _Traits> >        
      							__num_put_type;
      typedef ctype<_CharT>           			__ctype_type;

      
      





 
      explicit 
      basic_ostream(__streambuf_type* __sb)
      { this->init(__sb); }

      



 
      virtual 
      ~basic_ostream() { }

      
      class sentry;
      friend class sentry;
      
      
      
      
      





 
      __ostream_type&
      operator<<(__ostream_type& (*__pf)(__ostream_type&))
      {
	
	
	
	return __pf(*this);
      }

      __ostream_type&
      operator<<(__ios_type& (*__pf)(__ios_type&))
      {
	
	
	
	__pf(*this);
	return *this;
      }

      __ostream_type&
      operator<<(ios_base& (*__pf) (ios_base&))
      {
	
	
	
	__pf(*this);
	return *this;
      }
      

      
      















 
      
      






 
      __ostream_type& 
      operator<<(long __n)
      { return _M_insert(__n); }
      
      __ostream_type& 
      operator<<(unsigned long __n)
      { return _M_insert(__n); }	

      __ostream_type& 
      operator<<(bool __n)
      { return _M_insert(__n); }

      __ostream_type& 
      operator<<(short __n);

      __ostream_type& 
      operator<<(unsigned short __n)
      {
	
	
	return _M_insert(static_cast<unsigned long>(__n));
      }

      __ostream_type& 
      operator<<(int __n);

      __ostream_type& 
      operator<<(unsigned int __n)
      {
	
	
	return _M_insert(static_cast<unsigned long>(__n));
      }

      __ostream_type& 
      operator<<(long long __n)
      { return _M_insert(__n); }

      __ostream_type& 
      operator<<(unsigned long long __n)
      { return _M_insert(__n); }	

      __ostream_type& 
      operator<<(double __f)
      { return _M_insert(__f); }

      __ostream_type& 
      operator<<(float __f)
      {
	
	
	return _M_insert(static_cast<double>(__f));
      }

      __ostream_type& 
      operator<<(long double __f)
      { return _M_insert(__f); }

      __ostream_type& 
      operator<<(const void* __p)
      { return _M_insert(__p); }

      



















 
      __ostream_type& 
      operator<<(__streambuf_type* __sb);
      

      
      















 
      
      








 
      __ostream_type& 
      put(char_type __c);

      
      void
      _M_write(const char_type* __s, streamsize __n)
      {
	const streamsize __put = this->rdbuf()->sputn(__s, __n);
	if (__put != __n)
	  this->setstate(ios_base::badbit);
      }

      














 
      __ostream_type& 
      write(const char_type* __s, streamsize __n);
      

      







 
      __ostream_type& 
      flush();

      
      





 
      pos_type 
      tellp();

      






 
      __ostream_type& 
      seekp(pos_type);

      







 
       __ostream_type& 
      seekp(off_type, ios_base::seekdir);
      
    protected:
      basic_ostream()
      { this->init(0); }

      template<typename _ValueT>
        __ostream_type&
        _M_insert(_ValueT __v);
    };

  





 
  template <typename _CharT, typename _Traits>
    class basic_ostream<_CharT, _Traits>::sentry
    {
      
      bool 				_M_ok;
      basic_ostream<_CharT, _Traits>& 	_M_os;
      
    public:
      









 
      explicit
      sentry(basic_ostream<_CharT, _Traits>& __os);

      





 
      ~sentry()
      {
	
	if (bool(_M_os.flags() & ios_base::unitbuf) && !uncaught_exception())
	  {
	    
	    if (_M_os.rdbuf() && _M_os.rdbuf()->pubsync() == -1)
	      _M_os.setstate(ios_base::badbit);
	  }
      }

      





 
      operator bool() const
      { return _M_ok; }
    };

  
  
  













 
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __out, _CharT __c)
    { return __ostream_insert(__out, &__c, 1); }

  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __out, char __c)
    { return (__out << __out.widen(__c)); }

  
  template <class _Traits> 
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, char __c)
    { return __ostream_insert(__out, &__c, 1); }

  
  template<class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, signed char __c)
    { return (__out << static_cast<char>(__c)); }
  
  template<class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, unsigned char __c)
    { return (__out << static_cast<char>(__c)); }
  
  
  
  











 
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __out, const _CharT* __s)
    {
      if (!__s)
	__out.setstate(ios_base::badbit);
      else
	__ostream_insert(__out, __s,
			 static_cast<streamsize>(_Traits::length(__s)));
      return __out;
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits> &
    operator<<(basic_ostream<_CharT, _Traits>& __out, const char* __s);

  
  template<class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, const char* __s)
    {
      if (!__s)
	__out.setstate(ios_base::badbit);
      else
	__ostream_insert(__out, __s,
			 static_cast<streamsize>(_Traits::length(__s)));
      return __out;
    }

  
  template<class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, const signed char* __s)
    { return (__out << reinterpret_cast<const char*>(__s)); }

  template<class _Traits>
    inline basic_ostream<char, _Traits> &
    operator<<(basic_ostream<char, _Traits>& __out, const unsigned char* __s)
    { return (__out << reinterpret_cast<const char*>(__s)); }
  

  
  






 
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>& 
    endl(basic_ostream<_CharT, _Traits>& __os)
    { return flush(__os.put(__os.widen('\n'))); }

  




 
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>& 
    ends(basic_ostream<_CharT, _Traits>& __os)
    { return __os.put(_CharT()); }
  
  



 
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>& 
    flush(basic_ostream<_CharT, _Traits>& __os)
    { return __os.flush(); }



} 






























 








namespace std __attribute__ ((__visibility__ ("default")))
{


  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>::sentry::
    sentry(basic_ostream<_CharT, _Traits>& __os)
    : _M_ok(false), _M_os(__os)
    {
      
      if (__os.tie() && __os.good())
	__os.tie()->flush();

      if (__os.good())
	_M_ok = true;
      else
	__os.setstate(ios_base::failbit);
    }

  template<typename _CharT, typename _Traits>
    template<typename _ValueT>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::
      _M_insert(_ValueT __v)
      {
	sentry __cerb(*this);
	if (__cerb)
	  {
	    ios_base::iostate __err = ios_base::goodbit;
	    try
	      {
		const __num_put_type& __np = __check_facet(this->_M_num_put);
		if (__np.put(*this, *this, this->fill(), __v).failed())
		  __err |= ios_base::badbit;
	      }
	    catch(__cxxabiv1::__forced_unwind&)
	      {
		this->_M_setstate(ios_base::badbit);		
		throw;
	      }
	    catch(...)
	      { this->_M_setstate(ios_base::badbit); }
	    if (__err)
	      this->setstate(__err);
	  }
	return *this;
      }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    operator<<(short __n)
    {
      
      
      const ios_base::fmtflags __fmt = this->flags() & ios_base::basefield;
      if (__fmt == ios_base::oct || __fmt == ios_base::hex)
	return _M_insert(static_cast<long>(static_cast<unsigned short>(__n)));
      else
	return _M_insert(static_cast<long>(__n));
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    operator<<(int __n)
    {
      
      
      const ios_base::fmtflags __fmt = this->flags() & ios_base::basefield;
      if (__fmt == ios_base::oct || __fmt == ios_base::hex)
	return _M_insert(static_cast<long>(static_cast<unsigned int>(__n)));
      else
	return _M_insert(static_cast<long>(__n));
    }
  
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    operator<<(__streambuf_type* __sbin)
    {
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this);
      if (__cerb && __sbin)
	{
	  try
	    {
	      if (!__copy_streambufs(__sbin, this->rdbuf()))
		__err |= ios_base::failbit;
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);		
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::failbit); }
	}
      else if (!__sbin)
	__err |= ios_base::badbit;
      if (__err)
	this->setstate(__err);
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    put(char_type __c)
    {
      
      
      
      
      
      
      sentry __cerb(*this);
      if (__cerb)
	{
	  ios_base::iostate __err = ios_base::goodbit;
	  try
	    {
	      const int_type __put = this->rdbuf()->sputc(__c);
	      if (traits_type::eq_int_type(__put, traits_type::eof()))
		__err |= ios_base::badbit;
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);		
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::badbit); }
	  if (__err)
	    this->setstate(__err);
	}
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    write(const _CharT* __s, streamsize __n)
    {
      
      
      
      
      
      
      
      sentry __cerb(*this);
      if (__cerb)
	{
	  try
	    { _M_write(__s, __n); }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);		
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::badbit); }
	}
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    flush()
    {
      
      
      
      ios_base::iostate __err = ios_base::goodbit;
      try
	{
	  if (this->rdbuf() && this->rdbuf()->pubsync() == -1)
	    __err |= ios_base::badbit;
	}
      catch(__cxxabiv1::__forced_unwind&)
	{
	  this->_M_setstate(ios_base::badbit);		
	  throw;
	}
      catch(...)
	{ this->_M_setstate(ios_base::badbit); }
      if (__err)
	this->setstate(__err);
      return *this;
    }

  template<typename _CharT, typename _Traits>
    typename basic_ostream<_CharT, _Traits>::pos_type
    basic_ostream<_CharT, _Traits>::
    tellp()
    {
      pos_type __ret = pos_type(-1);
      try
	{
	  if (!this->fail())
	    __ret = this->rdbuf()->pubseekoff(0, ios_base::cur, ios_base::out);
	}
      catch(__cxxabiv1::__forced_unwind&)
	{
	  this->_M_setstate(ios_base::badbit);		
	  throw;
	}
      catch(...)
	{ this->_M_setstate(ios_base::badbit); }
      return __ret;
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    seekp(pos_type __pos)
    {
      ios_base::iostate __err = ios_base::goodbit;
      try
	{
	  if (!this->fail())
	    {
	      
	      
	      const pos_type __p = this->rdbuf()->pubseekpos(__pos,
							     ios_base::out);

	      
	      if (__p == pos_type(off_type(-1)))
		__err |= ios_base::failbit;
	    }
	}
      catch(__cxxabiv1::__forced_unwind&)
	{
	  this->_M_setstate(ios_base::badbit);		
	  throw;
	}
      catch(...)
	{ this->_M_setstate(ios_base::badbit); }
      if (__err)
	this->setstate(__err);
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    seekp(off_type __off, ios_base::seekdir __dir)
    {
      ios_base::iostate __err = ios_base::goodbit;
      try
	{
	  if (!this->fail())
	    {
	      
	      
	      const pos_type __p = this->rdbuf()->pubseekoff(__off, __dir,
							     ios_base::out);

	      
	      if (__p == pos_type(off_type(-1)))
		__err |= ios_base::failbit;
	    }
	}
      catch(__cxxabiv1::__forced_unwind&)
	{
	  this->_M_setstate(ios_base::badbit);		
	  throw;
	}
      catch(...)
	{ this->_M_setstate(ios_base::badbit); }
      if (__err)
	this->setstate(__err);
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __out, const char* __s)
    {
      if (!__s)
	__out.setstate(ios_base::badbit);
      else
	{
	  
	  
	  const size_t __clen = char_traits<char>::length(__s);
	  try
	    {
	      struct __ptr_guard
	      {
		_CharT *__p;
		__ptr_guard (_CharT *__ip): __p(__ip) { }
		~__ptr_guard() { delete[] __p; }
		_CharT* __get() { return __p; }
	      } __pg (new _CharT[__clen]);

	      _CharT *__ws = __pg.__get();
	      for (size_t  __i = 0; __i < __clen; ++__i)
		__ws[__i] = __out.widen(__s[__i]);
	      __ostream_insert(__out, __ws, __clen);
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      __out._M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { __out._M_setstate(ios_base::badbit); }
	}
      return __out;
    }

  
  
  extern template class basic_ostream<char>;
  extern template ostream& endl(ostream&);
  extern template ostream& ends(ostream&);
  extern template ostream& flush(ostream&);
  extern template ostream& operator<<(ostream&, char);
  extern template ostream& operator<<(ostream&, unsigned char);
  extern template ostream& operator<<(ostream&, signed char);
  extern template ostream& operator<<(ostream&, const char*);
  extern template ostream& operator<<(ostream&, const unsigned char*);
  extern template ostream& operator<<(ostream&, const signed char*);

  extern template ostream& ostream::_M_insert(long);
  extern template ostream& ostream::_M_insert(unsigned long);
  extern template ostream& ostream::_M_insert(bool);
  extern template ostream& ostream::_M_insert(long long);
  extern template ostream& ostream::_M_insert(unsigned long long);
  extern template ostream& ostream::_M_insert(double);
  extern template ostream& ostream::_M_insert(long double);
  extern template ostream& ostream::_M_insert(const void*);

  extern template class basic_ostream<wchar_t>;
  extern template wostream& endl(wostream&);
  extern template wostream& ends(wostream&);
  extern template wostream& flush(wostream&);
  extern template wostream& operator<<(wostream&, wchar_t);
  extern template wostream& operator<<(wostream&, char);
  extern template wostream& operator<<(wostream&, const wchar_t*);
  extern template wostream& operator<<(wostream&, const char*);

  extern template wostream& wostream::_M_insert(long);
  extern template wostream& wostream::_M_insert(unsigned long);
  extern template wostream& wostream::_M_insert(bool);
  extern template wostream& wostream::_M_insert(long long);
  extern template wostream& wostream::_M_insert(unsigned long long);
  extern template wostream& wostream::_M_insert(double);
  extern template wostream& wostream::_M_insert(long double);
  extern template wostream& wostream::_M_insert(const void*);


} 


































 




namespace std __attribute__ ((__visibility__ ("default")))
{


  
  






 
  template<typename _CharT, typename _Traits>
    class basic_istream : virtual public basic_ios<_CharT, _Traits>
    {
    public:
      
      typedef _CharT                     		char_type;
      typedef typename _Traits::int_type 		int_type;
      typedef typename _Traits::pos_type 		pos_type;
      typedef typename _Traits::off_type 		off_type;
      typedef _Traits                    		traits_type;
      
      
      typedef basic_streambuf<_CharT, _Traits> 		__streambuf_type;
      typedef basic_ios<_CharT, _Traits>		__ios_type;
      typedef basic_istream<_CharT, _Traits>		__istream_type;
      typedef num_get<_CharT, istreambuf_iterator<_CharT, _Traits> >        
 							__num_get_type;
      typedef ctype<_CharT>           			__ctype_type;

    protected:
      
      


 
      streamsize 		_M_gcount;

    public:
      
      





 
      explicit
      basic_istream(__streambuf_type* __sb)
      : _M_gcount(streamsize(0))
      { this->init(__sb); }

      



 
      virtual 
      ~basic_istream() 
      { _M_gcount = streamsize(0); }

      
      class sentry;
      friend class sentry;

      
      
      
      






 
      __istream_type&
      operator>>(__istream_type& (*__pf)(__istream_type&))
      { return __pf(*this); }

      __istream_type&
      operator>>(__ios_type& (*__pf)(__ios_type&))
      { 
	__pf(*this);
	return *this;
      }

      __istream_type&
      operator>>(ios_base& (*__pf)(ios_base&))
      {
	__pf(*this);
	return *this;
      }
      
      
      
      
















 
      
      






 
      __istream_type& 
      operator>>(bool& __n)
      { return _M_extract(__n); }
      
      __istream_type& 
      operator>>(short& __n);
      
      __istream_type& 
      operator>>(unsigned short& __n)
      { return _M_extract(__n); }

      __istream_type& 
      operator>>(int& __n);
    
      __istream_type& 
      operator>>(unsigned int& __n)
      { return _M_extract(__n); }

      __istream_type& 
      operator>>(long& __n)
      { return _M_extract(__n); }
      
      __istream_type& 
      operator>>(unsigned long& __n)
      { return _M_extract(__n); }

      __istream_type& 
      operator>>(long long& __n)
      { return _M_extract(__n); }

      __istream_type& 
      operator>>(unsigned long long& __n)
      { return _M_extract(__n); }

      __istream_type& 
      operator>>(float& __f)
      { return _M_extract(__f); }

      __istream_type& 
      operator>>(double& __f)
      { return _M_extract(__f); }

      __istream_type& 
      operator>>(long double& __f)
      { return _M_extract(__f); }

      __istream_type& 
      operator>>(void*& __p)
      { return _M_extract(__p); }

      


















 
      __istream_type& 
      operator>>(__streambuf_type* __sb);
      
      
      
      



 
      streamsize 
      gcount() const 
      { return _M_gcount; }
      
      


















 
      
      





 
      int_type 
      get();

      









 
      __istream_type& 
      get(char_type& __c);

      






















 
      __istream_type& 
      get(char_type* __s, streamsize __n, char_type __delim);

      






 
      __istream_type& 
      get(char_type* __s, streamsize __n)
      { return this->get(__s, __n, this->widen('\n')); }

      

















 
      __istream_type&
      get(__streambuf_type& __sb, char_type __delim);

      





 
      __istream_type&
      get(__streambuf_type& __sb)
      { return this->get(__sb, this->widen('\n')); }

      























 
      __istream_type& 
      getline(char_type* __s, streamsize __n, char_type __delim);

      






 
      __istream_type& 
      getline(char_type* __s, streamsize __n)
      { return this->getline(__s, __n, this->widen('\n')); }

      


















 
      __istream_type& 
      ignore();

      __istream_type& 
      ignore(streamsize __n);

      __istream_type& 
      ignore(streamsize __n, int_type __delim);
      
      






 
      int_type 
      peek();
      
      













 
      __istream_type& 
      read(char_type* __s, streamsize __n);

      














 
      streamsize 
      readsome(char_type* __s, streamsize __n);
      
      












 
      __istream_type& 
      putback(char_type __c);

      











 
      __istream_type& 
      unget();

      













 
      int 
      sync();

      










 
      pos_type
      tellg();

      










 
      __istream_type&
      seekg(pos_type);

      











 
      __istream_type& 
      seekg(off_type, ios_base::seekdir);
      

    protected:
      basic_istream()
      : _M_gcount(streamsize(0))
      { this->init(0); }

      template<typename _ValueT>
        __istream_type&
        _M_extract(_ValueT& __v);
    };

  
  template<> 
    basic_istream<char>& 
    basic_istream<char>::
    getline(char_type* __s, streamsize __n, char_type __delim);
  
  template<>
    basic_istream<char>&
    basic_istream<char>::
    ignore(streamsize __n);
  
  template<>
    basic_istream<char>&
    basic_istream<char>::
    ignore(streamsize __n, int_type __delim);

  template<> 
    basic_istream<wchar_t>& 
    basic_istream<wchar_t>::
    getline(char_type* __s, streamsize __n, char_type __delim);

  template<>
    basic_istream<wchar_t>&
    basic_istream<wchar_t>::
    ignore(streamsize __n);
  
  template<>
    basic_istream<wchar_t>&
    basic_istream<wchar_t>::
    ignore(streamsize __n, int_type __delim);

  






 
  template<typename _CharT, typename _Traits>
    class basic_istream<_CharT, _Traits>::sentry
    {
      
      bool _M_ok;

    public:
      
      typedef _Traits 					traits_type;
      typedef basic_streambuf<_CharT, _Traits> 		__streambuf_type;
      typedef basic_istream<_CharT, _Traits> 		__istream_type;
      typedef typename __istream_type::__ctype_type 	__ctype_type;
      typedef typename _Traits::int_type		__int_type;

      




















 
      explicit
      sentry(basic_istream<_CharT, _Traits>& __is, bool __noskipws = false);

      





 
      operator bool() const
      { return _M_ok; }
    };

  
  
  









 
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in, _CharT& __c);

  template<class _Traits>
    inline basic_istream<char, _Traits>&
    operator>>(basic_istream<char, _Traits>& __in, unsigned char& __c)
    { return (__in >> reinterpret_cast<char&>(__c)); }

  template<class _Traits>
    inline basic_istream<char, _Traits>&
    operator>>(basic_istream<char, _Traits>& __in, signed char& __c)
    { return (__in >> reinterpret_cast<char&>(__c)); }
  

  
  
























 
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in, _CharT* __s);

  
  template<>
    basic_istream<char>&
    operator>>(basic_istream<char>& __in, char* __s);

  template<class _Traits>
    inline basic_istream<char, _Traits>&
    operator>>(basic_istream<char, _Traits>& __in, unsigned char* __s)
    { return (__in >> reinterpret_cast<char*>(__s)); }

  template<class _Traits>
    inline basic_istream<char, _Traits>&
    operator>>(basic_istream<char, _Traits>& __in, signed char* __s)
    { return (__in >> reinterpret_cast<char*>(__s)); }
  

  
  





 
  template<typename _CharT, typename _Traits>
    class basic_iostream
    : public basic_istream<_CharT, _Traits>, 
      public basic_ostream<_CharT, _Traits>
    {
    public:
      
      
      
      typedef _CharT                     		char_type;
      typedef typename _Traits::int_type 		int_type;
      typedef typename _Traits::pos_type 		pos_type;
      typedef typename _Traits::off_type 		off_type;
      typedef _Traits                    		traits_type;

      
      typedef basic_istream<_CharT, _Traits>		__istream_type;
      typedef basic_ostream<_CharT, _Traits>		__ostream_type;

      




 
      explicit
      basic_iostream(basic_streambuf<_CharT, _Traits>* __sb)
      : __istream_type(__sb), __ostream_type(__sb) { }

      

 
      virtual 
      ~basic_iostream() { }

    protected:
      basic_iostream()
      : __istream_type(), __ostream_type() { }
    };

  
  


















 
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>& 
    ws(basic_istream<_CharT, _Traits>& __is);



} 






























 








namespace std __attribute__ ((__visibility__ ("default")))
{


  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>::sentry::
    sentry(basic_istream<_CharT, _Traits>& __in, bool __noskip) : _M_ok(false)
    {
      ios_base::iostate __err = ios_base::goodbit;
      if (__in.good())
	{
	  if (__in.tie())
	    __in.tie()->flush();
	  if (!__noskip && bool(__in.flags() & ios_base::skipws))
	    {
	      const __int_type __eof = traits_type::eof();
	      __streambuf_type* __sb = __in.rdbuf();
	      __int_type __c = __sb->sgetc();

	      const __ctype_type& __ct = __check_facet(__in._M_ctype);
	      while (!traits_type::eq_int_type(__c, __eof)
		     && __ct.is(ctype_base::space, 
				traits_type::to_char_type(__c)))
		__c = __sb->snextc();

	      
	      
	      
	      if (traits_type::eq_int_type(__c, __eof))
		__err |= ios_base::eofbit;
	    }
	}

      if (__in.good() && __err == ios_base::goodbit)
	_M_ok = true;
      else
	{
	  __err |= ios_base::failbit;
	  __in.setstate(__err);
	}
    }

  template<typename _CharT, typename _Traits>
    template<typename _ValueT>
      basic_istream<_CharT, _Traits>&
      basic_istream<_CharT, _Traits>::
      _M_extract(_ValueT& __v)
      {
	sentry __cerb(*this, false);
	if (__cerb)
	  {
	    ios_base::iostate __err = ios_base::goodbit;
	    try
	      {
		const __num_get_type& __ng = __check_facet(this->_M_num_get);
		__ng.get(*this, 0, *this, __err, __v);
	      }
	    catch(__cxxabiv1::__forced_unwind&)
	      {
		this->_M_setstate(ios_base::badbit);
		throw;
	      }
	    catch(...)
	      { this->_M_setstate(ios_base::badbit); }
	    if (__err)
	      this->setstate(__err);
	  }
	return *this;
      }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    operator>>(short& __n)
    {
      
      
      sentry __cerb(*this, false);
      if (__cerb)
	{
	  ios_base::iostate __err = ios_base::goodbit;
	  try
	    {
	      long __l;
	      const __num_get_type& __ng = __check_facet(this->_M_num_get);
	      __ng.get(*this, 0, *this, __err, __l);

	      
	      
	      if (__l < __gnu_cxx::__numeric_traits<short>::__min)
		{
		  __err |= ios_base::failbit;
		  __n = __gnu_cxx::__numeric_traits<short>::__min;
		}
	      else if (__l > __gnu_cxx::__numeric_traits<short>::__max)
		{
		  __err |= ios_base::failbit;
		  __n = __gnu_cxx::__numeric_traits<short>::__max;
		}
	      else
		__n = short(__l);
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::badbit); }
	  if (__err)
	    this->setstate(__err);
	}
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    operator>>(int& __n)
    {
      
      
      sentry __cerb(*this, false);
      if (__cerb)
	{
	  ios_base::iostate __err = ios_base::goodbit;
	  try
	    {
	      long __l;
	      const __num_get_type& __ng = __check_facet(this->_M_num_get);
	      __ng.get(*this, 0, *this, __err, __l);

	      
	      
	      if (__l < __gnu_cxx::__numeric_traits<int>::__min)
		{
		  __err |= ios_base::failbit;
		  __n = __gnu_cxx::__numeric_traits<int>::__min;
		}
	      else if (__l > __gnu_cxx::__numeric_traits<int>::__max)
		{
		  __err |= ios_base::failbit;	      
		  __n = __gnu_cxx::__numeric_traits<int>::__max;
		}
	      else
		__n = int(__l);
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::badbit); }
	  if (__err)
	    this->setstate(__err);
	}
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    operator>>(__streambuf_type* __sbout)
    {
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, false);
      if (__cerb && __sbout)
	{
	  try
	    {
	      bool __ineof;
	      if (!__copy_streambufs_eof(this->rdbuf(), __sbout, __ineof))
		__err |= ios_base::failbit;
	      if (__ineof)
		__err |= ios_base::eofbit;
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::failbit);
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::failbit); }
	}
      else if (!__sbout)
	__err |= ios_base::failbit;
      if (__err)
	this->setstate(__err);
      return *this;
    }

  template<typename _CharT, typename _Traits>
    typename basic_istream<_CharT, _Traits>::int_type
    basic_istream<_CharT, _Traits>::
    get(void)
    {
      const int_type __eof = traits_type::eof();
      int_type __c = __eof;
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
	{
	  try
	    {
	      __c = this->rdbuf()->sbumpc();
	      
	      if (!traits_type::eq_int_type(__c, __eof))
		_M_gcount = 1;
	      else
		__err |= ios_base::eofbit;
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::badbit); }
	}
      if (!_M_gcount)
	__err |= ios_base::failbit;
      if (__err)
	this->setstate(__err);
      return __c;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    get(char_type& __c)
    {
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
	{
	  try
	    {
	      const int_type __cb = this->rdbuf()->sbumpc();
	      
	      if (!traits_type::eq_int_type(__cb, traits_type::eof()))
		{
		  _M_gcount = 1;
		  __c = traits_type::to_char_type(__cb);
		}
	      else
		__err |= ios_base::eofbit;
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::badbit); }
	}
      if (!_M_gcount)
	__err |= ios_base::failbit;
      if (__err)
	this->setstate(__err);
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    get(char_type* __s, streamsize __n, char_type __delim)
    {
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
	{
	  try
	    {
	      const int_type __idelim = traits_type::to_int_type(__delim);
	      const int_type __eof = traits_type::eof();
	      __streambuf_type* __sb = this->rdbuf();
	      int_type __c = __sb->sgetc();

	      while (_M_gcount + 1 < __n
		     && !traits_type::eq_int_type(__c, __eof)
		     && !traits_type::eq_int_type(__c, __idelim))
		{
		  *__s++ = traits_type::to_char_type(__c);
		  ++_M_gcount;
		  __c = __sb->snextc();
		}
	      if (traits_type::eq_int_type(__c, __eof))
		__err |= ios_base::eofbit;
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::badbit); }
	}
      
      
      if (__n > 0)
	*__s = char_type();
      if (!_M_gcount)
	__err |= ios_base::failbit;
      if (__err)
	this->setstate(__err);
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    get(__streambuf_type& __sb, char_type __delim)
    {
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
	{
	  try
	    {
	      const int_type __idelim = traits_type::to_int_type(__delim);
	      const int_type __eof = traits_type::eof();
	      __streambuf_type* __this_sb = this->rdbuf();
	      int_type __c = __this_sb->sgetc();
	      char_type __c2 = traits_type::to_char_type(__c);

	      while (!traits_type::eq_int_type(__c, __eof)
		     && !traits_type::eq_int_type(__c, __idelim)
		     && !traits_type::eq_int_type(__sb.sputc(__c2), __eof))
		{
		  ++_M_gcount;
		  __c = __this_sb->snextc();
		  __c2 = traits_type::to_char_type(__c);
		}
	      if (traits_type::eq_int_type(__c, __eof))
		__err |= ios_base::eofbit;
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::badbit); }
	}
      if (!_M_gcount)
	__err |= ios_base::failbit;
      if (__err)
	this->setstate(__err);
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    getline(char_type* __s, streamsize __n, char_type __delim)
    {
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
        {
          try
            {
              const int_type __idelim = traits_type::to_int_type(__delim);
              const int_type __eof = traits_type::eof();
              __streambuf_type* __sb = this->rdbuf();
              int_type __c = __sb->sgetc();

              while (_M_gcount + 1 < __n
                     && !traits_type::eq_int_type(__c, __eof)
                     && !traits_type::eq_int_type(__c, __idelim))
                {
                  *__s++ = traits_type::to_char_type(__c);
                  __c = __sb->snextc();
                  ++_M_gcount;
                }
              if (traits_type::eq_int_type(__c, __eof))
                __err |= ios_base::eofbit;
              else
                {
                  if (traits_type::eq_int_type(__c, __idelim))
                    {
                      __sb->sbumpc();
                      ++_M_gcount;
                    }
                  else
                    __err |= ios_base::failbit;
                }
            }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
          catch(...)
            { this->_M_setstate(ios_base::badbit); }
        }
      
      
      if (__n > 0)
	*__s = char_type();
      if (!_M_gcount)
        __err |= ios_base::failbit;
      if (__err)
        this->setstate(__err);
      return *this;
    }

  
  
  
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    ignore(void)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb)
	{
	  ios_base::iostate __err = ios_base::goodbit;
	  try
	    {
	      const int_type __eof = traits_type::eof();
	      __streambuf_type* __sb = this->rdbuf();

	      if (traits_type::eq_int_type(__sb->sbumpc(), __eof))
		__err |= ios_base::eofbit;
	      else
		_M_gcount = 1;
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::badbit); }
	  if (__err)
	    this->setstate(__err);
	}
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    ignore(streamsize __n)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb && __n > 0)
        {
          ios_base::iostate __err = ios_base::goodbit;
          try
            {
              const int_type __eof = traits_type::eof();
              __streambuf_type* __sb = this->rdbuf();
              int_type __c = __sb->sgetc();

	      
	      
	      
	      
	      
	      
	      
	      bool __large_ignore = false;
	      while (true)
		{
		  while (_M_gcount < __n
			 && !traits_type::eq_int_type(__c, __eof))
		    {
		      ++_M_gcount;
		      __c = __sb->snextc();
		    }
		  if (__n == __gnu_cxx::__numeric_traits<streamsize>::__max
		      && !traits_type::eq_int_type(__c, __eof))
		    {
		      _M_gcount =
			__gnu_cxx::__numeric_traits<streamsize>::__min;
		      __large_ignore = true;
		    }
		  else
		    break;
		}

	      if (__large_ignore)
		_M_gcount = __gnu_cxx::__numeric_traits<streamsize>::__max;

	      if (traits_type::eq_int_type(__c, __eof))
                __err |= ios_base::eofbit;
            }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
          catch(...)
            { this->_M_setstate(ios_base::badbit); }
          if (__err)
            this->setstate(__err);
        }
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    ignore(streamsize __n, int_type __delim)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb && __n > 0)
        {
          ios_base::iostate __err = ios_base::goodbit;
          try
            {
              const int_type __eof = traits_type::eof();
              __streambuf_type* __sb = this->rdbuf();
              int_type __c = __sb->sgetc();

	      
	      bool __large_ignore = false;
	      while (true)
		{
		  while (_M_gcount < __n
			 && !traits_type::eq_int_type(__c, __eof)
			 && !traits_type::eq_int_type(__c, __delim))
		    {
		      ++_M_gcount;
		      __c = __sb->snextc();
		    }
		  if (__n == __gnu_cxx::__numeric_traits<streamsize>::__max
		      && !traits_type::eq_int_type(__c, __eof)
		      && !traits_type::eq_int_type(__c, __delim))
		    {
		      _M_gcount =
			__gnu_cxx::__numeric_traits<streamsize>::__min;
		      __large_ignore = true;
		    }
		  else
		    break;
		}

	      if (__large_ignore)
		_M_gcount = __gnu_cxx::__numeric_traits<streamsize>::__max;

              if (traits_type::eq_int_type(__c, __eof))
                __err |= ios_base::eofbit;
	      else if (traits_type::eq_int_type(__c, __delim))
		{
		  if (_M_gcount
		      < __gnu_cxx::__numeric_traits<streamsize>::__max)
		    ++_M_gcount;
		  __sb->sbumpc();
		}
            }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
          catch(...)
            { this->_M_setstate(ios_base::badbit); }
          if (__err)
            this->setstate(__err);
        }
      return *this;
    }

  template<typename _CharT, typename _Traits>
    typename basic_istream<_CharT, _Traits>::int_type
    basic_istream<_CharT, _Traits>::
    peek(void)
    {
      int_type __c = traits_type::eof();
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb)
	{
	  ios_base::iostate __err = ios_base::goodbit;
	  try
	    {
	      __c = this->rdbuf()->sgetc();
	      if (traits_type::eq_int_type(__c, traits_type::eof()))
		__err |= ios_base::eofbit;
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::badbit); }
	  if (__err)
	    this->setstate(__err);
	}
      return __c;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    read(char_type* __s, streamsize __n)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb)
	{
	  ios_base::iostate __err = ios_base::goodbit;
	  try
	    {
	      _M_gcount = this->rdbuf()->sgetn(__s, __n);
	      if (_M_gcount != __n)
		__err |= (ios_base::eofbit | ios_base::failbit);
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::badbit); }
	  if (__err)
	    this->setstate(__err);
	}
      return *this;
    }

  template<typename _CharT, typename _Traits>
    streamsize
    basic_istream<_CharT, _Traits>::
    readsome(char_type* __s, streamsize __n)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb)
	{
	  ios_base::iostate __err = ios_base::goodbit;
	  try
	    {
	      
	      const streamsize __num = this->rdbuf()->in_avail();
	      if (__num > 0)
		_M_gcount = this->rdbuf()->sgetn(__s, std::min(__num, __n));
	      else if (__num == -1)
		__err |= ios_base::eofbit;
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::badbit); }
	  if (__err)
	    this->setstate(__err);
	}
      return _M_gcount;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    putback(char_type __c)
    {
      
      
      _M_gcount = 0;
      
      this->clear(this->rdstate() & ~ios_base::eofbit);
      sentry __cerb(*this, true);
      if (__cerb)
	{
	  ios_base::iostate __err = ios_base::goodbit;
	  try
	    {
	      const int_type __eof = traits_type::eof();
	      __streambuf_type* __sb = this->rdbuf();
	      if (!__sb
		  || traits_type::eq_int_type(__sb->sputbackc(__c), __eof))
		__err |= ios_base::badbit;
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::badbit); }
	  if (__err)
	    this->setstate(__err);
	}
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    unget(void)
    {
      
      
      _M_gcount = 0;
      
      this->clear(this->rdstate() & ~ios_base::eofbit);
      sentry __cerb(*this, true);
      if (__cerb)
	{
	  ios_base::iostate __err = ios_base::goodbit;
	  try
	    {
	      const int_type __eof = traits_type::eof();
	      __streambuf_type* __sb = this->rdbuf();
	      if (!__sb
		  || traits_type::eq_int_type(__sb->sungetc(), __eof))
		__err |= ios_base::badbit;
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::badbit); }
	  if (__err)
	    this->setstate(__err);
	}
      return *this;
    }

  template<typename _CharT, typename _Traits>
    int
    basic_istream<_CharT, _Traits>::
    sync(void)
    {
      
      
      int __ret = -1;
      sentry __cerb(*this, true);
      if (__cerb)
	{
	  ios_base::iostate __err = ios_base::goodbit;
	  try
	    {
	      __streambuf_type* __sb = this->rdbuf();
	      if (__sb)
		{
		  if (__sb->pubsync() == -1)
		    __err |= ios_base::badbit;
		  else
		    __ret = 0;
		}
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::badbit); }
	  if (__err)
	    this->setstate(__err);
	}
      return __ret;
    }

  template<typename _CharT, typename _Traits>
    typename basic_istream<_CharT, _Traits>::pos_type
    basic_istream<_CharT, _Traits>::
    tellg(void)
    {
      
      
      pos_type __ret = pos_type(-1);
      sentry __cerb(*this, true);
      if (__cerb)
	{
	  try
	    {
	      if (!this->fail())
		__ret = this->rdbuf()->pubseekoff(0, ios_base::cur,
						  ios_base::in);
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::badbit); }
	}
      return __ret;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    seekg(pos_type __pos)
    {
      
      
      
      this->clear(this->rdstate() & ~ios_base::eofbit);
      sentry __cerb(*this, true);
      if (__cerb)
	{
	  ios_base::iostate __err = ios_base::goodbit;
	  try
	    {
	      if (!this->fail())
		{
		  
		  const pos_type __p = this->rdbuf()->pubseekpos(__pos,
								 ios_base::in);
		  
		  
		  if (__p == pos_type(off_type(-1)))
		    __err |= ios_base::failbit;
		}
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::badbit); }
	  if (__err)
	    this->setstate(__err);
	}
      return *this;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    seekg(off_type __off, ios_base::seekdir __dir)
    {
      
      
      
      this->clear(this->rdstate() & ~ios_base::eofbit);
      sentry __cerb(*this, true);
      if (__cerb)
	{
	  ios_base::iostate __err = ios_base::goodbit;
	  try
	    {
	      if (!this->fail())
		{
		  
		  const pos_type __p = this->rdbuf()->pubseekoff(__off, __dir,
								 ios_base::in);
	      
		  
		  if (__p == pos_type(off_type(-1)))
		    __err |= ios_base::failbit;
		}
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      this->_M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { this->_M_setstate(ios_base::badbit); }
	  if (__err)
	    this->setstate(__err);
	}
      return *this;
    }

  
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in, _CharT& __c)
    {
      typedef basic_istream<_CharT, _Traits>		__istream_type;
      typedef typename __istream_type::int_type         __int_type;

      typename __istream_type::sentry __cerb(__in, false);
      if (__cerb)
	{
	  ios_base::iostate __err = ios_base::goodbit;
	  try
	    {
	      const __int_type __cb = __in.rdbuf()->sbumpc();
	      if (!_Traits::eq_int_type(__cb, _Traits::eof()))
		__c = _Traits::to_char_type(__cb);
	      else
		__err |= (ios_base::eofbit | ios_base::failbit);
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      __in._M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { __in._M_setstate(ios_base::badbit); }
	  if (__err)
	    __in.setstate(__err);
	}
      return __in;
    }

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in, _CharT* __s)
    {
      typedef basic_istream<_CharT, _Traits>		__istream_type;
      typedef basic_streambuf<_CharT, _Traits>          __streambuf_type;
      typedef typename _Traits::int_type		int_type;
      typedef _CharT					char_type;
      typedef ctype<_CharT>				__ctype_type;

      streamsize __extracted = 0;
      ios_base::iostate __err = ios_base::goodbit;
      typename __istream_type::sentry __cerb(__in, false);
      if (__cerb)
	{
	  try
	    {
	      
	      streamsize __num = __in.width();
	      if (__num <= 0)
		__num = __gnu_cxx::__numeric_traits<streamsize>::__max;

	      const __ctype_type& __ct = use_facet<__ctype_type>(__in.getloc());

	      const int_type __eof = _Traits::eof();
	      __streambuf_type* __sb = __in.rdbuf();
	      int_type __c = __sb->sgetc();

	      while (__extracted < __num - 1
		     && !_Traits::eq_int_type(__c, __eof)
		     && !__ct.is(ctype_base::space,
				 _Traits::to_char_type(__c)))
		{
		  *__s++ = _Traits::to_char_type(__c);
		  ++__extracted;
		  __c = __sb->snextc();
		}
	      if (_Traits::eq_int_type(__c, __eof))
		__err |= ios_base::eofbit;

	      
	      
	      *__s = char_type();
	      __in.width(0);
	    }
	  catch(__cxxabiv1::__forced_unwind&)
	    {
	      __in._M_setstate(ios_base::badbit);
	      throw;
	    }
	  catch(...)
	    { __in._M_setstate(ios_base::badbit); }
	}
      if (!__extracted)
	__err |= ios_base::failbit;
      if (__err)
	__in.setstate(__err);
      return __in;
    }

  
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    ws(basic_istream<_CharT, _Traits>& __in)
    {
      typedef basic_istream<_CharT, _Traits>		__istream_type;
      typedef basic_streambuf<_CharT, _Traits>          __streambuf_type;
      typedef typename __istream_type::int_type		__int_type;
      typedef ctype<_CharT>				__ctype_type;

      const __ctype_type& __ct = use_facet<__ctype_type>(__in.getloc());
      const __int_type __eof = _Traits::eof();
      __streambuf_type* __sb = __in.rdbuf();
      __int_type __c = __sb->sgetc();

      while (!_Traits::eq_int_type(__c, __eof)
	     && __ct.is(ctype_base::space, _Traits::to_char_type(__c)))
	__c = __sb->snextc();

       if (_Traits::eq_int_type(__c, __eof))
	 __in.setstate(ios_base::eofbit);
      return __in;
    }

  
  
  extern template class basic_istream<char>;
  extern template istream& ws(istream&);
  extern template istream& operator>>(istream&, char&);
  extern template istream& operator>>(istream&, char*);
  extern template istream& operator>>(istream&, unsigned char&);
  extern template istream& operator>>(istream&, signed char&);
  extern template istream& operator>>(istream&, unsigned char*);
  extern template istream& operator>>(istream&, signed char*);

  extern template istream& istream::_M_extract(unsigned short&);
  extern template istream& istream::_M_extract(unsigned int&);  
  extern template istream& istream::_M_extract(long&);
  extern template istream& istream::_M_extract(unsigned long&);
  extern template istream& istream::_M_extract(bool&);
  extern template istream& istream::_M_extract(long long&);
  extern template istream& istream::_M_extract(unsigned long long&);
  extern template istream& istream::_M_extract(float&);
  extern template istream& istream::_M_extract(double&);
  extern template istream& istream::_M_extract(long double&);
  extern template istream& istream::_M_extract(void*&);

  extern template class basic_iostream<char>;

  extern template class basic_istream<wchar_t>;
  extern template wistream& ws(wistream&);
  extern template wistream& operator>>(wistream&, wchar_t&);
  extern template wistream& operator>>(wistream&, wchar_t*);

  extern template wistream& wistream::_M_extract(unsigned short&);
  extern template wistream& wistream::_M_extract(unsigned int&);  
  extern template wistream& wistream::_M_extract(long&);
  extern template wistream& wistream::_M_extract(unsigned long&);
  extern template wistream& wistream::_M_extract(bool&);
  extern template wistream& wistream::_M_extract(long long&);
  extern template wistream& wistream::_M_extract(unsigned long long&);
  extern template wistream& wistream::_M_extract(float&);
  extern template wistream& wistream::_M_extract(double&);
  extern template wistream& wistream::_M_extract(long double&);
  extern template wistream& wistream::_M_extract(void*&);

  extern template class basic_iostream<wchar_t>;


} 



namespace std __attribute__ ((__visibility__ ("default")))
{


  











 
  
  extern istream cin;		
  extern ostream cout;		
  extern ostream cerr;		
  extern ostream clog;		

  extern wistream wcin;		
  extern wostream wcout;	
  extern wostream wcerr;	
  extern wostream wclog;	
  

  
  static ios_base::Init __ioinit;


} 






namespace olb {












 
namespace descriptors {

struct NoExternalField {
  static const int numScalars = 0;
  static const int numSpecies = 0;
  static const int forceBeginsAt = 0;
  static const int sizeOfForce   = 0;
};

struct NoExternalFieldBase {
  typedef NoExternalField ExternalField;
};

struct Force2dDescriptor {
  static const int numScalars = 2;
  static const int numSpecies = 1;
  static const int forceBeginsAt = 0;
  static const int sizeOfForce   = 2;
};

struct Force2dDescriptorBase {
  typedef Force2dDescriptor ExternalField;
};

struct Force3dDescriptor {
  static const int numScalars = 3;
  static const int numSpecies = 1;
  static const int forceBeginsAt = 0;
  static const int sizeOfForce   = 3;
};

struct Force3dDescriptorBase {
  typedef Force3dDescriptor ExternalField;
};

template<typename T, typename ExternalField>
class ExternalFieldArray {
public:
  T* get(int index) {
    ;
    return data+index;
  }
  T const* get(int index) const {
    ;
    return data+index;
  }
private:
  T data[ExternalField::numScalars];
};

template<typename T>
class ExternalFieldArray<T,descriptors::NoExternalField> {
public:
  T* get(unsigned index) {
    ;
    static T data = T();
    return &data;
  }
  T const* get(unsigned index) const {
    ;
    static T data = T();
    return &data;
  }
};



template <typename T> struct D2Q9DescriptorBase
{
  typedef D2Q9DescriptorBase<T> BaseDescriptor;
  enum { d = 2, q = 9 };      
  static const int vicinity;  
  static const int c[q][d];   
  static const T t[q];        
  static const T invCs2;      
};


template <typename T> struct D3Q13DescriptorBase
{
  typedef D3Q13DescriptorBase<T> BaseDescriptor;
  enum { d = 3, q = 13 };     
  static const int vicinity;  
  static const int c[q][d];   
  static const T t[q];        
  static const T invCs2;      
  static const T lambda_e;    
  static const T lambda_h;    
};


template <typename T> struct D3Q15DescriptorBase
{
  typedef D3Q15DescriptorBase<T> BaseDescriptor;
  enum { d = 3, q = 15 };     
  static const int vicinity;  
  static const int c[q][d];   
  static const T t[q];        
  static const T invCs2;      
};


template <typename T> struct D3Q19DescriptorBase
{
  typedef D3Q19DescriptorBase<T> BaseDescriptor;
  enum { d = 3, q = 19 };     
  static const int vicinity;  
  static const int c[q][d];   
  static const T t[q];        
  static const T invCs2;      
};


template <typename T> struct D3Q27DescriptorBase
{
  typedef D3Q27DescriptorBase<T> BaseDescriptor;
  enum { d = 3, q = 27 };     
  static const int vicinity;  
  static const int c[q][d];   
  static const T t[q];        
  static const T invCs2;      
};

template <typename T> struct D2Q9Descriptor
    : public D2Q9DescriptorBase<T>, public NoExternalFieldBase
  { };

template <typename T> struct ForcedD2Q9Descriptor
    : public D2Q9DescriptorBase<T>, public Force2dDescriptorBase
  { };

template <typename T> struct D3Q13Descriptor
    : public D3Q13DescriptorBase<T>, public NoExternalFieldBase
  { };

template <typename T> struct ForcedD3Q13Descriptor
    : public D3Q13DescriptorBase<T>, public Force3dDescriptorBase
  { };

template <typename T> struct D3Q15Descriptor
    : public D3Q15DescriptorBase<T>, public NoExternalFieldBase
  { };

template <typename T> struct ForcedD3Q15Descriptor
    : public D3Q15DescriptorBase<T>, public Force3dDescriptorBase
  { };

template <typename T> struct D3Q19Descriptor
    : public D3Q19DescriptorBase<T>, public NoExternalFieldBase
  { };

template <typename T> struct ForcedD3Q19Descriptor
    : public D3Q19DescriptorBase<T>, public Force3dDescriptorBase
  { };

template <typename T> struct D3Q27Descriptor
    : public D3Q27DescriptorBase<T>, public NoExternalFieldBase
  { };

template <typename T> struct ForcedD3Q27Descriptor
    : public D3Q27DescriptorBase<T>, public Force3dDescriptorBase
  { };

}  

}  






















 




 


















































 



 




















































 



 









 


















































 












 


namespace std __attribute__ ((__visibility__ ("default")))
{
  namespace rel_ops
  {
  

    

 

    






 
    template <class _Tp>
      inline bool
      operator!=(const _Tp& __x, const _Tp& __y)
      { return !(__x == __y); }

    






 
    template <class _Tp>
      inline bool
      operator>(const _Tp& __x, const _Tp& __y)
      { return __y < __x; }

    






 
    template <class _Tp>
      inline bool
      operator<=(const _Tp& __x, const _Tp& __y)
      { return !(__y < __x); }

    






 
    template <class _Tp>
      inline bool
      operator>=(const _Tp& __x, const _Tp& __y)
      { return !(__x < __y); }

  
  } 

} 





















































 




 




































 

























 



 



 































 



 







 

extern "C" {


 

















 



 

 


















 



 


 

 

 

 

 

 


 

 

 




union wait
  {
    int w_status;
    struct
      {
	unsigned int __w_termsig:7;  
	unsigned int __w_coredump:1;  
	unsigned int __w_retcode:8;  
	unsigned int:16;
      } __wait_terminated;
    struct
      {
	unsigned int __w_stopval:8;  
	unsigned int __w_stopsig:8;  
	unsigned int:16;
      } __wait_stopped;
  };





 





 



 


 
typedef struct
  {
    int quot;			 
    int rem;			 
  } div_t;

 
typedef struct
  {
    long int quot;		 
    long int rem;		 
  } ldiv_t;



 
__extension__ typedef struct
  {
    long long int quot;		 
    long long int rem;		 
  } lldiv_t;



 



 


 
extern size_t __ctype_get_mb_cur_max (void) throw () ;



 
extern double atof (__const char *__nptr)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
 
extern int atoi (__const char *__nptr)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
 
extern long int atol (__const char *__nptr)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;



 
__extension__ extern long long int atoll (__const char *__nptr)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;



 
extern double strtod (__const char *__restrict __nptr,
		      char **__restrict __endptr)
     throw () __attribute__ ((__nonnull__ (1))) ;



 
extern float strtof (__const char *__restrict __nptr,
		     char **__restrict __endptr) throw () __attribute__ ((__nonnull__ (1))) ;

extern long double strtold (__const char *__restrict __nptr,
			    char **__restrict __endptr)
     throw () __attribute__ ((__nonnull__ (1))) ;



 
extern long int strtol (__const char *__restrict __nptr,
			char **__restrict __endptr, int __base)
     throw () __attribute__ ((__nonnull__ (1))) ;
 
extern unsigned long int strtoul (__const char *__restrict __nptr,
				  char **__restrict __endptr, int __base)
     throw () __attribute__ ((__nonnull__ (1))) ;


 
__extension__
extern long long int strtoq (__const char *__restrict __nptr,
			     char **__restrict __endptr, int __base)
     throw () __attribute__ ((__nonnull__ (1))) ;
 
__extension__
extern unsigned long long int strtouq (__const char *__restrict __nptr,
				       char **__restrict __endptr, int __base)
     throw () __attribute__ ((__nonnull__ (1))) ;


 
__extension__
extern long long int strtoll (__const char *__restrict __nptr,
			      char **__restrict __endptr, int __base)
     throw () __attribute__ ((__nonnull__ (1))) ;
 
__extension__
extern unsigned long long int strtoull (__const char *__restrict __nptr,
					char **__restrict __endptr, int __base)
     throw () __attribute__ ((__nonnull__ (1))) ;












 


 


 
extern long int strtol_l (__const char *__restrict __nptr,
			  char **__restrict __endptr, int __base,
			  __locale_t __loc) throw () __attribute__ ((__nonnull__ (1, 4))) ;

extern unsigned long int strtoul_l (__const char *__restrict __nptr,
				    char **__restrict __endptr,
				    int __base, __locale_t __loc)
     throw () __attribute__ ((__nonnull__ (1, 4))) ;

__extension__
extern long long int strtoll_l (__const char *__restrict __nptr,
				char **__restrict __endptr, int __base,
				__locale_t __loc)
     throw () __attribute__ ((__nonnull__ (1, 4))) ;

__extension__
extern unsigned long long int strtoull_l (__const char *__restrict __nptr,
					  char **__restrict __endptr,
					  int __base, __locale_t __loc)
     throw () __attribute__ ((__nonnull__ (1, 4))) ;

extern double strtod_l (__const char *__restrict __nptr,
			char **__restrict __endptr, __locale_t __loc)
     throw () __attribute__ ((__nonnull__ (1, 3))) ;

extern float strtof_l (__const char *__restrict __nptr,
		       char **__restrict __endptr, __locale_t __loc)
     throw () __attribute__ ((__nonnull__ (1, 3))) ;

extern long double strtold_l (__const char *__restrict __nptr,
			      char **__restrict __endptr,
			      __locale_t __loc)
     throw () __attribute__ ((__nonnull__ (1, 3))) ;



extern __inline __attribute__ ((__gnu_inline__)) double
atof (__const char *__nptr) throw ()
{
  return strtod (__nptr, (char **) __null);
}
extern __inline __attribute__ ((__gnu_inline__)) int
atoi (__const char *__nptr) throw ()
{
  return (int) strtol (__nptr, (char **) __null, 10);
}
extern __inline __attribute__ ((__gnu_inline__)) long int
atol (__const char *__nptr) throw ()
{
  return strtol (__nptr, (char **) __null, 10);
}



__extension__ extern __inline __attribute__ ((__gnu_inline__)) long long int
atoll (__const char *__nptr) throw ()
{
  return strtoll (__nptr, (char **) __null, 10);
}





 
extern char *l64a (long int __n) throw () ;

 
extern long int a64l (__const char *__s)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;



















 



 



extern "C" {


typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;

typedef __loff_t loff_t;

typedef __ino_t ino_t;
typedef __ino64_t ino64_t;

typedef __dev_t dev_t;


typedef __mode_t mode_t;

typedef __nlink_t nlink_t;




typedef __id_t id_t;


typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;

typedef __key_t key_t;


typedef __suseconds_t suseconds_t;
































 



 







 

 
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;

 


 

typedef int int8_t __attribute__ ((__mode__ (__QI__)));
typedef int int16_t __attribute__ ((__mode__ (__HI__)));
typedef int int32_t __attribute__ ((__mode__ (__SI__)));
typedef int int64_t __attribute__ ((__mode__ (__DI__)));

typedef unsigned int u_int8_t __attribute__ ((__mode__ (__QI__)));
typedef unsigned int u_int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int u_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int u_int64_t __attribute__ ((__mode__ (__DI__)));

typedef int register_t __attribute__ ((__mode__ (__word__)));



 


 

 

















 

 



 

 
















 


 








 


















 







 



 

















 



 




 
struct timeval
  {
    __time_t tv_sec;		 
    __suseconds_t tv_usec;	 
  };



 
typedef long int __fd_mask;

 
 

 
typedef struct
  {
    
 
    __fd_mask fds_bits[1024 / (8 * sizeof (__fd_mask))];
  } fd_set;

 

 
typedef __fd_mask fd_mask;

 


 


extern "C" {








 
extern int select (int __nfds, fd_set *__restrict __readfds,
		   fd_set *__restrict __writefds,
		   fd_set *__restrict __exceptfds,
		   struct timeval *__restrict __timeout);






 
extern int pselect (int __nfds, fd_set *__restrict __readfds,
		    fd_set *__restrict __writefds,
		    fd_set *__restrict __exceptfds,
		    const struct timespec *__restrict __timeout,
		    const __sigset_t *__restrict __sigmask);

}


 


















 





 
__extension__
extern unsigned int gnu_dev_major (unsigned long long int __dev)
     throw ();
__extension__
extern unsigned int gnu_dev_minor (unsigned long long int __dev)
     throw ();
__extension__
extern unsigned long long int gnu_dev_makedev (unsigned int __major,
					       unsigned int __minor)
     throw ();

__extension__ extern __inline __attribute__ ((__gnu_inline__)) unsigned int
gnu_dev_major (unsigned long long int __dev) throw ()
{
  return ((__dev >> 8) & 0xfff) | ((unsigned int) (__dev >> 32) & ~0xfff);
}

__extension__ extern __inline __attribute__ ((__gnu_inline__)) unsigned int
gnu_dev_minor (unsigned long long int __dev) throw ()
{
  return (__dev & 0xff) | ((unsigned int) (__dev >> 12) & ~0xff);
}

__extension__ extern __inline __attribute__ ((__gnu_inline__)) unsigned long long int
gnu_dev_makedev (unsigned int __major, unsigned int __minor) throw ()
{
  return ((__minor & 0xff) | ((__major & 0xfff) << 8)
	  | (((unsigned long long int) (__minor & ~0xff)) << 12)
	  | (((unsigned long long int) (__major & ~0xfff)) << 32));
}


 



typedef __blksize_t blksize_t;

 
typedef __blkcnt_t blkcnt_t;	  
typedef __fsblkcnt_t fsblkcnt_t;  
typedef __fsfilcnt_t fsfilcnt_t;  

typedef __blkcnt64_t blkcnt64_t;      
typedef __fsblkcnt64_t fsblkcnt64_t;  
typedef __fsfilcnt64_t fsfilcnt64_t;  


 

}





 
 
extern long int random (void) throw ();

 
extern void srandom (unsigned int __seed) throw ();




 
extern char *initstate (unsigned int __seed, char *__statebuf,
			size_t __statelen) throw () __attribute__ ((__nonnull__ (2)));


 
extern char *setstate (char *__statebuf) throw () __attribute__ ((__nonnull__ (1)));




 

struct random_data
  {
    int32_t *fptr;		 
    int32_t *rptr;		 
    int32_t *state;		 
    int rand_type;		 
    int rand_deg;		 
    int rand_sep;		 
    int32_t *end_ptr;		 
  };

extern int random_r (struct random_data *__restrict __buf,
		     int32_t *__restrict __result) throw () __attribute__ ((__nonnull__ (1, 2)));

extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     throw () __attribute__ ((__nonnull__ (2)));

extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
			size_t __statelen,
			struct random_data *__restrict __buf)
     throw () __attribute__ ((__nonnull__ (2, 4)));

extern int setstate_r (char *__restrict __statebuf,
		       struct random_data *__restrict __buf)
     throw () __attribute__ ((__nonnull__ (1, 2)));



 
extern int rand (void) throw ();
 
extern void srand (unsigned int __seed) throw ();


 
extern int rand_r (unsigned int *__seed) throw ();


 

 
extern double drand48 (void) throw ();
extern double erand48 (unsigned short int __xsubi[3]) throw () __attribute__ ((__nonnull__ (1)));

 
extern long int lrand48 (void) throw ();
extern long int nrand48 (unsigned short int __xsubi[3])
     throw () __attribute__ ((__nonnull__ (1)));

 
extern long int mrand48 (void) throw ();
extern long int jrand48 (unsigned short int __xsubi[3])
     throw () __attribute__ ((__nonnull__ (1)));

 
extern void srand48 (long int __seedval) throw ();
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     throw () __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) throw () __attribute__ ((__nonnull__ (1)));



 
struct drand48_data
  {
    unsigned short int __x[3];	 
    unsigned short int __old_x[3];  
    unsigned short int __c;	 
    unsigned short int __init;	 
    unsigned long long int __a;	 
  };

 
extern int drand48_r (struct drand48_data *__restrict __buffer,
		      double *__restrict __result) throw () __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r (unsigned short int __xsubi[3],
		      struct drand48_data *__restrict __buffer,
		      double *__restrict __result) throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int lrand48_r (struct drand48_data *__restrict __buffer,
		      long int *__restrict __result)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r (unsigned short int __xsubi[3],
		      struct drand48_data *__restrict __buffer,
		      long int *__restrict __result)
     throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int mrand48_r (struct drand48_data *__restrict __buffer,
		      long int *__restrict __result)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r (unsigned short int __xsubi[3],
		      struct drand48_data *__restrict __buffer,
		      long int *__restrict __result)
     throw () __attribute__ ((__nonnull__ (1, 2)));

 
extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     throw () __attribute__ ((__nonnull__ (2)));

extern int seed48_r (unsigned short int __seed16v[3],
		     struct drand48_data *__buffer) throw () __attribute__ ((__nonnull__ (1, 2)));

extern int lcong48_r (unsigned short int __param[7],
		      struct drand48_data *__buffer)
     throw () __attribute__ ((__nonnull__ (1, 2)));



 
extern void *malloc (size_t __size) throw () __attribute__ ((__malloc__)) ;
 
extern void *calloc (size_t __nmemb, size_t __size)
     throw () __attribute__ ((__malloc__)) ;




 


 
extern void *realloc (void *__ptr, size_t __size)
     throw () __attribute__ ((__warn_unused_result__));
 
extern void free (void *__ptr) throw ();


 
extern void cfree (void *__ptr) throw ();

















 


































 



 







 

extern "C" {

 

 
extern void *alloca (size_t __size) throw ();


}


 
extern void *valloc (size_t __size) throw () __attribute__ ((__malloc__)) ;

 
extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     throw () __attribute__ ((__nonnull__ (1))) ;


 
extern void abort (void) throw () __attribute__ ((__noreturn__));


 
extern int atexit (void (*__func) (void)) throw () __attribute__ ((__nonnull__ (1)));



 
extern "C++" int at_quick_exit (void (*__func) (void))
     throw () __asm ("at_quick_exit") __attribute__ ((__nonnull__ (1)));



 
extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     throw () __attribute__ ((__nonnull__ (1)));




 
extern void exit (int __status) throw () __attribute__ ((__noreturn__));





 
extern void quick_exit (int __status) throw () __attribute__ ((__noreturn__));




 
extern void _Exit (int __status) throw () __attribute__ ((__noreturn__));




 
extern char *getenv (__const char *__name) throw () __attribute__ ((__nonnull__ (1))) ;



 
extern char *__secure_getenv (__const char *__name)
     throw () __attribute__ ((__nonnull__ (1))) ;

 

 
extern int putenv (char *__string) throw () __attribute__ ((__nonnull__ (1)));


 
extern int setenv (__const char *__name, __const char *__value, int __replace)
     throw () __attribute__ ((__nonnull__ (2)));

 
extern int unsetenv (__const char *__name) throw ();



 
extern int clearenv (void) throw ();





 
extern char *mktemp (char *__template) throw () __attribute__ ((__nonnull__ (1))) ;








 
extern int mkstemp (char *__template) __attribute__ ((__nonnull__ (1))) ;
extern int mkstemp64 (char *__template) __attribute__ ((__nonnull__ (1))) ;





 
extern char *mkdtemp (char *__template) throw () __attribute__ ((__nonnull__ (1))) ;






 
extern int mkostemp (char *__template, int __flags) __attribute__ ((__nonnull__ (1))) ;
extern int mkostemp64 (char *__template, int __flags) __attribute__ ((__nonnull__ (1))) ;






 
extern int system (__const char *__command) ;




 
extern char *canonicalize_file_name (__const char *__name)
     throw () __attribute__ ((__nonnull__ (1))) ;





 
extern char *realpath (__const char *__restrict __name,
		       char *__restrict __resolved) throw () ;


 
typedef int (*__compar_fn_t) (__const void *, __const void *);

typedef __compar_fn_t comparison_fn_t;
typedef int (*__compar_d_fn_t) (__const void *, __const void *, void *);



 
extern void *bsearch (__const void *__key, __const void *__base,
		      size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) ;


 
extern void qsort (void *__base, size_t __nmemb, size_t __size,
		   __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));
extern void qsort_r (void *__base, size_t __nmemb, size_t __size,
		     __compar_d_fn_t __compar, void *__arg)
  __attribute__ ((__nonnull__ (1, 4)));


 
extern int abs (int __x) throw () __attribute__ ((__const__)) ;
extern long int labs (long int __x) throw () __attribute__ ((__const__)) ;


__extension__ extern long long int llabs (long long int __x)
     throw () __attribute__ ((__const__)) ;




 
 
extern div_t div (int __numer, int __denom)
     throw () __attribute__ ((__const__)) ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     throw () __attribute__ ((__const__)) ;



__extension__ extern lldiv_t lldiv (long long int __numer,
				    long long int __denom)
     throw () __attribute__ ((__const__)) ;




 



 
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
		   int *__restrict __sign) throw () __attribute__ ((__nonnull__ (3, 4))) ;



 
extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
		   int *__restrict __sign) throw () __attribute__ ((__nonnull__ (3, 4))) ;



 
extern char *gcvt (double __value, int __ndigit, char *__buf)
     throw () __attribute__ ((__nonnull__ (3))) ;


 
extern char *qecvt (long double __value, int __ndigit,
		    int *__restrict __decpt, int *__restrict __sign)
     throw () __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qfcvt (long double __value, int __ndigit,
		    int *__restrict __decpt, int *__restrict __sign)
     throw () __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     throw () __attribute__ ((__nonnull__ (3))) ;



 
extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
		   int *__restrict __sign, char *__restrict __buf,
		   size_t __len) throw () __attribute__ ((__nonnull__ (3, 4, 5)));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
		   int *__restrict __sign, char *__restrict __buf,
		   size_t __len) throw () __attribute__ ((__nonnull__ (3, 4, 5)));

extern int qecvt_r (long double __value, int __ndigit,
		    int *__restrict __decpt, int *__restrict __sign,
		    char *__restrict __buf, size_t __len)
     throw () __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qfcvt_r (long double __value, int __ndigit,
		    int *__restrict __decpt, int *__restrict __sign,
		    char *__restrict __buf, size_t __len)
     throw () __attribute__ ((__nonnull__ (3, 4, 5)));




 
extern int mblen (__const char *__s, size_t __n) throw () ;

 
extern int mbtowc (wchar_t *__restrict __pwc,
		   __const char *__restrict __s, size_t __n) throw () ;

 
extern int wctomb (char *__s, wchar_t __wchar) throw () ;


 
extern size_t mbstowcs (wchar_t *__restrict  __pwcs,
			__const char *__restrict __s, size_t __n) throw ();
 
extern size_t wcstombs (char *__restrict __s,
			__const wchar_t *__restrict __pwcs, size_t __n)
     throw ();






 
extern int rpmatch (__const char *__response) throw () __attribute__ ((__nonnull__ (1))) ;







 
extern int getsubopt (char **__restrict __optionp,
		      char *__const *__restrict __tokens,
		      char **__restrict __valuep)
     throw () __attribute__ ((__nonnull__ (1, 2, 3))) ;


 
extern void setkey (__const char *__key) throw () __attribute__ ((__nonnull__ (1)));


 

 
extern int posix_openpt (int __oflag) ;


 

 
extern int grantpt (int __fd) throw ();


 
extern int unlockpt (int __fd) throw ();



 
extern char *ptsname (int __fd) throw () ;



 
extern int ptsname_r (int __fd, char *__buf, size_t __buflen)
     throw () __attribute__ ((__nonnull__ (2)));

 
extern int getpt (void);



 
extern int getloadavg (double __loadavg[], int __nelem)
     throw () __attribute__ ((__nonnull__ (1)));


 


}




namespace std __attribute__ ((__visibility__ ("default")))
{


  using ::div_t;
  using ::ldiv_t;

  using ::abort;
  using ::abs;
  using ::atexit;
  using ::atof;
  using ::atoi;
  using ::atol;
  using ::bsearch;
  using ::calloc;
  using ::div;
  using ::exit;
  using ::free;
  using ::getenv;
  using ::labs;
  using ::ldiv;
  using ::malloc;
  using ::mblen;
  using ::mbstowcs;
  using ::mbtowc;
  using ::qsort;
  using ::rand;
  using ::realloc;
  using ::srand;
  using ::strtod;
  using ::strtol;
  using ::strtoul;
  using ::system;
  using ::wcstombs;
  using ::wctomb;

  inline long
  abs(long __i) { return labs(__i); }

  inline ldiv_t
  div(long __i, long __j) { return ldiv(__i, __j); }


} 



namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{


  using ::lldiv_t;
  using ::_Exit;

  inline long long
  abs(long long __x) { return __x >= 0 ? __x : -__x; }

  using ::llabs;

  inline lldiv_t
  div(long long __n, long long __d)
  { lldiv_t __q; __q.quot = __n / __d; __q.rem = __n % __d; return __q; }

  using ::lldiv;

  using ::atoll;
  using ::strtoll;
  using ::strtoull;
  using ::strtof;
  using ::strtold;


} 

namespace std
{
  using ::__gnu_cxx::lldiv_t;
  using ::__gnu_cxx::_Exit;
  using ::__gnu_cxx::abs;
  using ::__gnu_cxx::llabs;
  using ::__gnu_cxx::div;
  using ::__gnu_cxx::lldiv;
  using ::__gnu_cxx::atoll;
  using ::__gnu_cxx::strtof;
  using ::__gnu_cxx::strtoll;
  using ::__gnu_cxx::strtoull;
  using ::__gnu_cxx::strtold;
} 































 




namespace std __attribute__ ((__visibility__ ("default")))
{


  


















































































 

  






 

  


 

  


 

  


 

  






 

  
























 

  


  template<typename _FIter, typename _Tp>
    bool 
    binary_search(_FIter, _FIter, const _Tp&);

  template<typename _FIter, typename _Tp, typename _Compare>
    bool 
    binary_search(_FIter, _FIter, const _Tp&, _Compare);

  template<typename _IIter, typename _OIter>
    _OIter 
    copy(_IIter, _IIter, _OIter);

  template<typename _BIter1, typename _BIter2>
    _BIter2
    copy_backward(_BIter1, _BIter1, _BIter2);


  
  

  template<typename _FIter, typename _Tp>
    pair<_FIter, _FIter>
    equal_range(_FIter, _FIter, const _Tp&);

  template<typename _FIter, typename _Tp, typename _Compare>
    pair<_FIter, _FIter>
    equal_range(_FIter, _FIter, const _Tp&, _Compare);

  template<typename _FIter, typename _Tp>
    void 
    fill(_FIter, _FIter, const _Tp&);

  template<typename _OIter, typename _Size, typename _Tp>
    _OIter
    fill_n(_OIter, _Size, const _Tp&);

  

  template<typename _FIter1, typename _FIter2>
    _FIter1
    find_end(_FIter1, _FIter1, _FIter2, _FIter2);

  template<typename _FIter1, typename _FIter2, typename _BinaryPredicate>
    _FIter1
    find_end(_FIter1, _FIter1, _FIter2, _FIter2, _BinaryPredicate);

  
  


  
  
  

  template<typename _IIter1, typename _IIter2>
    bool 
    includes(_IIter1, _IIter1, _IIter2, _IIter2);

  template<typename _IIter1, typename _IIter2, typename _Compare>
    bool 
    includes(_IIter1, _IIter1, _IIter2, _IIter2, _Compare);

  template<typename _BIter>
    void 
    inplace_merge(_BIter, _BIter, _BIter);

  template<typename _BIter, typename _Compare>
    void 
    inplace_merge(_BIter, _BIter, _BIter, _Compare);


  template<typename _FIter1, typename _FIter2>
    void 
    iter_swap(_FIter1, _FIter2);

  template<typename _FIter, typename _Tp>
    _FIter 
    lower_bound(_FIter, _FIter, const _Tp&);

  template<typename _FIter, typename _Tp, typename _Compare>
    _FIter 
    lower_bound(_FIter, _FIter, const _Tp&, _Compare);

  template<typename _RAIter>
    void 
    make_heap(_RAIter, _RAIter);

  template<typename _RAIter, typename _Compare>
    void 
    make_heap(_RAIter, _RAIter, _Compare);

  template<typename _Tp> 
    const _Tp& 
    max(const _Tp&, const _Tp&);

  template<typename _Tp, typename _Compare>
    const _Tp& 
    max(const _Tp&, const _Tp&, _Compare);

  
  

  template<typename _Tp> 
    const _Tp& 
    min(const _Tp&, const _Tp&);

  template<typename _Tp, typename _Compare>
    const _Tp& 
    min(const _Tp&, const _Tp&, _Compare);

  


  

  template<typename _BIter>
    bool 
    next_permutation(_BIter, _BIter);

  template<typename _BIter, typename _Compare>
    bool 
    next_permutation(_BIter, _BIter, _Compare);


  
  

  template<typename _IIter, typename _RAIter>
    _RAIter
    partial_sort_copy(_IIter, _IIter, _RAIter, _RAIter);

  template<typename _IIter, typename _RAIter, typename _Compare>
    _RAIter
    partial_sort_copy(_IIter, _IIter, _RAIter, _RAIter, _Compare);

  


  template<typename _RAIter>
    void 
    pop_heap(_RAIter, _RAIter);

  template<typename _RAIter, typename _Compare>
    void 
    pop_heap(_RAIter, _RAIter, _Compare);

  template<typename _BIter>
    bool 
    prev_permutation(_BIter, _BIter);

  template<typename _BIter, typename _Compare>
    bool 
    prev_permutation(_BIter, _BIter, _Compare);

  template<typename _RAIter>
    void 
    push_heap(_RAIter, _RAIter);

  template<typename _RAIter, typename _Compare>
    void 
    push_heap(_RAIter, _RAIter, _Compare);

  

  template<typename _FIter, typename _Tp>
    _FIter 
    remove(_FIter, _FIter, const _Tp&);

  template<typename _FIter, typename _Predicate>
    _FIter 
    remove_if(_FIter, _FIter, _Predicate);

  template<typename _IIter, typename _OIter, typename _Tp>
    _OIter 
    remove_copy(_IIter, _IIter, _OIter, const _Tp&);

  template<typename _IIter, typename _OIter, typename _Predicate>
    _OIter 
    remove_copy_if(_IIter, _IIter, _OIter, _Predicate);

  

  template<typename _IIter, typename _OIter, typename _Tp>
    _OIter 
    replace_copy(_IIter, _IIter, _OIter, const _Tp&, const _Tp&);

  template<typename _Iter, typename _OIter, typename _Predicate, typename _Tp>
    _OIter 
    replace_copy_if(_Iter, _Iter, _OIter, _Predicate, const _Tp&);

  

  template<typename _BIter>
    void 
    reverse(_BIter, _BIter);

  template<typename _BIter, typename _OIter>
    _OIter 
    reverse_copy(_BIter, _BIter, _OIter);

  template<typename _FIter>
    void 
    rotate(_FIter, _FIter, _FIter);

  template<typename _FIter, typename _OIter>
    _OIter 
    rotate_copy(_FIter, _FIter, _FIter, _OIter);

  
  
  
  
  
  


  template<typename _RAIter>
    void 
    sort_heap(_RAIter, _RAIter);

  template<typename _RAIter, typename _Compare>
    void 
    sort_heap(_RAIter, _RAIter, _Compare);

  template<typename _BIter, typename _Predicate>
    _BIter 
    stable_partition(_BIter, _BIter, _Predicate);

  template<typename _Tp> 
    void 
    swap(_Tp&, _Tp&);

  template<typename _Tp, size_t _Nm>
    void
    swap(_Tp (&)[_Nm], _Tp (&)[_Nm]);

  template<typename _FIter1, typename _FIter2>
    _FIter2 
    swap_ranges(_FIter1, _FIter1, _FIter2);

  

  template<typename _FIter>
    _FIter 
    unique(_FIter, _FIter);

  template<typename _FIter, typename _BinaryPredicate>
    _FIter 
    unique(_FIter, _FIter, _BinaryPredicate);

  

  template<typename _FIter, typename _Tp>
    _FIter 
    upper_bound(_FIter, _FIter, const _Tp&);

  template<typename _FIter, typename _Tp, typename _Compare>
    _FIter 
    upper_bound(_FIter, _FIter, const _Tp&, _Compare);





  template<typename _FIter>
    _FIter 
    adjacent_find(_FIter, _FIter);

  template<typename _FIter, typename _BinaryPredicate>
    _FIter 
    adjacent_find(_FIter, _FIter, _BinaryPredicate);

  template<typename _IIter, typename _Tp>
    typename iterator_traits<_IIter>::difference_type
    count(_IIter, _IIter, const _Tp&);

  template<typename _IIter, typename _Predicate>
    typename iterator_traits<_IIter>::difference_type
    count_if(_IIter, _IIter, _Predicate);

  template<typename _IIter1, typename _IIter2>
    bool 
    equal(_IIter1, _IIter1, _IIter2);

  template<typename _IIter1, typename _IIter2, typename _BinaryPredicate>
    bool 
    equal(_IIter1, _IIter1, _IIter2, _BinaryPredicate);

  template<typename _IIter, typename _Tp>
    _IIter 
    find(_IIter, _IIter, const _Tp&);

  template<typename _FIter1, typename _FIter2>
    _FIter1
    find_first_of(_FIter1, _FIter1, _FIter2, _FIter2);

  template<typename _FIter1, typename _FIter2, typename _BinaryPredicate>
    _FIter1
    find_first_of(_FIter1, _FIter1, _FIter2, _FIter2, _BinaryPredicate);

  template<typename _IIter, typename _Predicate>
    _IIter
    find_if(_IIter, _IIter, _Predicate);

  template<typename _IIter, typename _Funct>
    _Funct 
    for_each(_IIter, _IIter, _Funct);

  template<typename _FIter, typename _Generator>
    void 
    generate(_FIter, _FIter, _Generator);

  template<typename _OIter, typename _Size, typename _Generator>
    _OIter
    generate_n(_OIter, _Size, _Generator);

  template<typename _IIter1, typename _IIter2>
    bool 
    lexicographical_compare(_IIter1, _IIter1, _IIter2, _IIter2);

  template<typename _IIter1, typename _IIter2, typename _Compare>
    bool 
    lexicographical_compare(_IIter1, _IIter1, _IIter2, _IIter2, _Compare);

  template<typename _FIter>
    _FIter 
    max_element(_FIter, _FIter);

  template<typename _FIter, typename _Compare>
    _FIter 
    max_element(_FIter, _FIter, _Compare);

  template<typename _IIter1, typename _IIter2, typename _OIter>
    _OIter 
    merge(_IIter1, _IIter1, _IIter2, _IIter2, _OIter);

  template<typename _IIter1, typename _IIter2, typename _OIter, 
	   typename _Compare>
    _OIter 
    merge(_IIter1, _IIter1, _IIter2, _IIter2, _OIter, _Compare);

  template<typename _FIter>
    _FIter 
    min_element(_FIter, _FIter);

  template<typename _FIter, typename _Compare>
    _FIter 
    min_element(_FIter, _FIter, _Compare);

  template<typename _IIter1, typename _IIter2>
    pair<_IIter1, _IIter2>
    mismatch(_IIter1, _IIter1, _IIter2);

  template<typename _IIter1, typename _IIter2, typename _BinaryPredicate>
    pair<_IIter1, _IIter2>
    mismatch(_IIter1, _IIter1, _IIter2, _BinaryPredicate);

  template<typename _RAIter>
    void 
    nth_element(_RAIter, _RAIter, _RAIter);

  template<typename _RAIter, typename _Compare>
    void 
    nth_element(_RAIter, _RAIter, _RAIter, _Compare);

  template<typename _RAIter>
    void 
    partial_sort(_RAIter, _RAIter, _RAIter);

  template<typename _RAIter, typename _Compare>
    void 
    partial_sort(_RAIter, _RAIter, _RAIter, _Compare);

  template<typename _BIter, typename _Predicate>
    _BIter 
    partition(_BIter, _BIter, _Predicate);

  template<typename _RAIter>
    void 
    random_shuffle(_RAIter, _RAIter);

  template<typename _RAIter, typename _Generator>
    void 
    random_shuffle(_RAIter, _RAIter,
		   _Generator&);

  template<typename _FIter, typename _Tp>
    void 
    replace(_FIter, _FIter, const _Tp&, const _Tp&);

  template<typename _FIter, typename _Predicate, typename _Tp>
    void 
    replace_if(_FIter, _FIter, _Predicate, const _Tp&);

  template<typename _FIter1, typename _FIter2>
    _FIter1 
    search(_FIter1, _FIter1, _FIter2, _FIter2);

  template<typename _FIter1, typename _FIter2, typename _BinaryPredicate>
    _FIter1 
    search(_FIter1, _FIter1, _FIter2, _FIter2, _BinaryPredicate);

  template<typename _FIter, typename _Size, typename _Tp>
    _FIter 
    search_n(_FIter, _FIter, _Size, const _Tp&);

  template<typename _FIter, typename _Size, typename _Tp, 
	   typename _BinaryPredicate>
    _FIter 
    search_n(_FIter, _FIter, _Size, const _Tp&, _BinaryPredicate);

  template<typename _IIter1, typename _IIter2, typename _OIter>
    _OIter 
    set_difference(_IIter1, _IIter1, _IIter2, _IIter2, _OIter);

  template<typename _IIter1, typename _IIter2, typename _OIter, 
	   typename _Compare>
    _OIter 
    set_difference(_IIter1, _IIter1, _IIter2, _IIter2, _OIter, _Compare);

  template<typename _IIter1, typename _IIter2, typename _OIter>
    _OIter 
    set_intersection(_IIter1, _IIter1, _IIter2, _IIter2, _OIter);

  template<typename _IIter1, typename _IIter2, typename _OIter,
	   typename _Compare>
    _OIter 
    set_intersection(_IIter1, _IIter1, _IIter2, _IIter2, _OIter, _Compare);

  template<typename _IIter1, typename _IIter2, typename _OIter>
    _OIter
    set_symmetric_difference(_IIter1, _IIter1, _IIter2, _IIter2, _OIter);

  template<typename _IIter1, typename _IIter2, typename _OIter, 
	   typename _Compare>
    _OIter
    set_symmetric_difference(_IIter1, _IIter1, _IIter2, _IIter2, 
			     _OIter, _Compare);

  template<typename _IIter1, typename _IIter2, typename _OIter>
    _OIter 
    set_union(_IIter1, _IIter1, _IIter2, _IIter2, _OIter);

  template<typename _IIter1, typename _IIter2, typename _OIter,
	   typename _Compare>
    _OIter 
    set_union(_IIter1, _IIter1, _IIter2, _IIter2, _OIter, _Compare);

  template<typename _RAIter>
    void 
    sort(_RAIter, _RAIter);

  template<typename _RAIter, typename _Compare>
    void 
    sort(_RAIter, _RAIter, _Compare);

  template<typename _RAIter>
    void 
    stable_sort(_RAIter, _RAIter);

  template<typename _RAIter, typename _Compare>
    void 
    stable_sort(_RAIter, _RAIter, _Compare);

  template<typename _IIter, typename _OIter, typename _UnaryOperation>
    _OIter 
    transform(_IIter, _IIter, _OIter, _UnaryOperation);

  template<typename _IIter1, typename _IIter2, typename _OIter, 
	   typename _BinaryOperation>
    _OIter 
    transform(_IIter1, _IIter1, _IIter2, _OIter, _BinaryOperation);

  template<typename _IIter, typename _OIter>
    _OIter 
    unique_copy(_IIter, _IIter, _OIter);

  template<typename _IIter, typename _OIter, typename _BinaryPredicate>
    _OIter 
    unique_copy(_IIter, _IIter, _OIter, _BinaryPredicate);


} 



















































 




 



namespace std __attribute__ ((__visibility__ ("default")))
{


  


 

  template<typename _RandomAccessIterator, typename _Distance>
    _Distance
    __is_heap_until(_RandomAccessIterator __first, _Distance __n)
    {
      _Distance __parent = 0;
      for (_Distance __child = 1; __child < __n; ++__child)
	{
	  if (__first[__parent] < __first[__child])
	    return __child;
	  if ((__child & 1) == 0)
	    ++__parent;
	}
      return __n;
    }

  template<typename _RandomAccessIterator, typename _Distance,
	   typename _Compare>
    _Distance
    __is_heap_until(_RandomAccessIterator __first, _Distance __n,
		    _Compare __comp)
    {
      _Distance __parent = 0;
      for (_Distance __child = 1; __child < __n; ++__child)
	{
	  if (__comp(__first[__parent], __first[__child]))
	    return __child;
	  if ((__child & 1) == 0)
	    ++__parent;
	}
      return __n;
    }

  
  
  template<typename _RandomAccessIterator, typename _Distance>
    inline bool
    __is_heap(_RandomAccessIterator __first, _Distance __n)
    { return std::__is_heap_until(__first, __n) == __n; }

  template<typename _RandomAccessIterator, typename _Compare,
	   typename _Distance>
    inline bool
    __is_heap(_RandomAccessIterator __first, _Compare __comp, _Distance __n)
    { return std::__is_heap_until(__first, __n, __comp) == __n; }

  template<typename _RandomAccessIterator>
    inline bool
    __is_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    { return std::__is_heap(__first, std::distance(__first, __last)); }

  template<typename _RandomAccessIterator, typename _Compare>
    inline bool
    __is_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
	      _Compare __comp)
    { return std::__is_heap(__first, __comp, std::distance(__first, __last)); }

  
  

  template<typename _RandomAccessIterator, typename _Distance, typename _Tp>
    void
    __push_heap(_RandomAccessIterator __first,
		_Distance __holeIndex, _Distance __topIndex, _Tp __value)
    {
      _Distance __parent = (__holeIndex - 1) / 2;
      while (__holeIndex > __topIndex && *(__first + __parent) < __value)
	{
	  *(__first + __holeIndex) = (*(__first + __parent));
	  __holeIndex = __parent;
	  __parent = (__holeIndex - 1) / 2;
	}
      *(__first + __holeIndex) = (__value);
    }

  







 
  template<typename _RandomAccessIterator>
    inline void
    push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	  _ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
	  _DistanceType;

      
      
      
      ;
      ;

      _ValueType __value = (*(__last - 1));
      std::__push_heap(__first, _DistanceType((__last - __first) - 1),
		       _DistanceType(0), (__value));
    }

  template<typename _RandomAccessIterator, typename _Distance, typename _Tp,
	   typename _Compare>
    void
    __push_heap(_RandomAccessIterator __first, _Distance __holeIndex,
		_Distance __topIndex, _Tp __value, _Compare __comp)
    {
      _Distance __parent = (__holeIndex - 1) / 2;
      while (__holeIndex > __topIndex
	     && __comp(*(__first + __parent), __value))
	{
	  *(__first + __holeIndex) = (*(__first + __parent));
	  __holeIndex = __parent;
	  __parent = (__holeIndex - 1) / 2;
	}
      *(__first + __holeIndex) = (__value);
    }

  









 
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
	      _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	  _ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
	  _DistanceType;

      
      
      ;
      ;

      _ValueType __value = (*(__last - 1));
      std::__push_heap(__first, _DistanceType((__last - __first) - 1),
		       _DistanceType(0), (__value), __comp);
    }

  template<typename _RandomAccessIterator, typename _Distance, typename _Tp>
    void
    __adjust_heap(_RandomAccessIterator __first, _Distance __holeIndex,
		  _Distance __len, _Tp __value)
    {
      const _Distance __topIndex = __holeIndex;
      _Distance __secondChild = __holeIndex;
      while (__secondChild < (__len - 1) / 2)
	{
	  __secondChild = 2 * (__secondChild + 1);
	  if (*(__first + __secondChild) < *(__first + (__secondChild - 1)))
	    __secondChild--;
	  *(__first + __holeIndex) = (*(__first + __secondChild));
	  __holeIndex = __secondChild;
	}
      if ((__len & 1) == 0 && __secondChild == (__len - 2) / 2)
	{
	  __secondChild = 2 * (__secondChild + 1);
	  *(__first + __holeIndex) = (*(__first + (__secondChild - 1)));
	  __holeIndex = __secondChild - 1;
	}
      std::__push_heap(__first, __holeIndex, __topIndex,
		       (__value));
    }

  template<typename _RandomAccessIterator>
    inline void
    __pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
	       _RandomAccessIterator __result)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	_ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
	_DistanceType;

      _ValueType __value = (*__result);
      *__result = (*__first);
      std::__adjust_heap(__first, _DistanceType(0),
			 _DistanceType(__last - __first),
			 (__value));
    }

  







 
  template<typename _RandomAccessIterator>
    inline void
    pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	_ValueType;

      
      
      
      ;
      ;

      --__last;
      std::__pop_heap(__first, __last, __last);
    }

  template<typename _RandomAccessIterator, typename _Distance,
	   typename _Tp, typename _Compare>
    void
    __adjust_heap(_RandomAccessIterator __first, _Distance __holeIndex,
		  _Distance __len, _Tp __value, _Compare __comp)
    {
      const _Distance __topIndex = __holeIndex;
      _Distance __secondChild = __holeIndex;
      while (__secondChild < (__len - 1) / 2)
	{
	  __secondChild = 2 * (__secondChild + 1);
	  if (__comp(*(__first + __secondChild),
		     *(__first + (__secondChild - 1))))
	    __secondChild--;
	  *(__first + __holeIndex) = (*(__first + __secondChild));
	  __holeIndex = __secondChild;
	}
      if ((__len & 1) == 0 && __secondChild == (__len - 2) / 2)
	{
	  __secondChild = 2 * (__secondChild + 1);
	  *(__first + __holeIndex) = (*(__first + (__secondChild - 1)));
	  __holeIndex = __secondChild - 1;
	}
      std::__push_heap(__first, __holeIndex, __topIndex, 
		       (__value), __comp);      
    }

  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    __pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
	       _RandomAccessIterator __result, _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	_ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
	_DistanceType;

      _ValueType __value = (*__result);
      *__result = (*__first);
      std::__adjust_heap(__first, _DistanceType(0),
			 _DistanceType(__last - __first),
			 (__value), __comp);
    }

  









 
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    pop_heap(_RandomAccessIterator __first,
	     _RandomAccessIterator __last, _Compare __comp)
    {
      
      
      ;
      ;

      --__last;
      std::__pop_heap(__first, __last, __last, __comp);
    }

  






 
  template<typename _RandomAccessIterator>
    void
    make_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	  _ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
	  _DistanceType;

      
      
      
      ;

      if (__last - __first < 2)
	return;

      const _DistanceType __len = __last - __first;
      _DistanceType __parent = (__len - 2) / 2;
      while (true)
	{
	  _ValueType __value = (*(__first + __parent));
	  std::__adjust_heap(__first, __parent, __len, (__value));
	  if (__parent == 0)
	    return;
	  __parent--;
	}
    }

  








 
  template<typename _RandomAccessIterator, typename _Compare>
    void
    make_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
	      _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	  _ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
	  _DistanceType;

      
      
      ;

      if (__last - __first < 2)
	return;

      const _DistanceType __len = __last - __first;
      _DistanceType __parent = (__len - 2) / 2;
      while (true)
	{
	  _ValueType __value = (*(__first + __parent));
	  std::__adjust_heap(__first, __parent, __len, (__value),
			     __comp);
	  if (__parent == 0)
	    return;
	  __parent--;
	}
    }

  






 
  template<typename _RandomAccessIterator>
    void
    sort_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
      
      
      
      ;
      ;

      while (__last - __first > 1)
	{
	  --__last;
	  std::__pop_heap(__first, __last, __last);
	}
    }

  








 
  template<typename _RandomAccessIterator, typename _Compare>
    void
    sort_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
	      _Compare __comp)
    {
      
      
      ;
      ;

      while (__last - __first > 1)
	{
	  --__last;
	  std::__pop_heap(__first, __last, __last, __comp);
	}
    }



} 


















































 




 



namespace std __attribute__ ((__visibility__ ("default")))
{


  















 
  template<typename _Tp>
    pair<_Tp*, ptrdiff_t>
    get_temporary_buffer(ptrdiff_t __len)
    {
      const ptrdiff_t __max =
	__gnu_cxx::__numeric_traits<ptrdiff_t>::__max / sizeof(_Tp);
      if (__len > __max)
	__len = __max;
      
      while (__len > 0) 
	{
	  _Tp* __tmp = static_cast<_Tp*>(::operator new(__len * sizeof(_Tp), 
							std::nothrow));
	  if (__tmp != 0)
	    return std::pair<_Tp*, ptrdiff_t>(__tmp, __len);
	  __len /= 2;
	}
      return std::pair<_Tp*, ptrdiff_t>(static_cast<_Tp*>(0), 0);
    }

  





 
  template<typename _Tp>
    inline void
    return_temporary_buffer(_Tp* __p)
    { ::operator delete(__p, std::nothrow); }


  



 
  template<typename _ForwardIterator, typename _Tp>
    class _Temporary_buffer
    {
      
      

    public:
      typedef _Tp         value_type;
      typedef value_type* pointer;
      typedef pointer     iterator;
      typedef ptrdiff_t   size_type;

    protected:
      size_type  _M_original_len;
      size_type  _M_len;
      pointer    _M_buffer;

    public:
      
      size_type
      size() const
      { return _M_len; }

      
      size_type
      requested_size() const
      { return _M_original_len; }

      
      iterator
      begin()
      { return _M_buffer; }

      
      iterator
      end()
      { return _M_buffer + _M_len; }

      


 
      _Temporary_buffer(_ForwardIterator __first, _ForwardIterator __last);

      ~_Temporary_buffer()
      {
	std::_Destroy(_M_buffer, _M_buffer + _M_len);
	std::return_temporary_buffer(_M_buffer);
      }

    private:
      
      _Temporary_buffer(const _Temporary_buffer&);

      void
      operator=(const _Temporary_buffer&);
    };


  template<bool>
    struct __uninitialized_construct_buf_dispatch
    {
      template<typename _ForwardIterator, typename _Tp>
        static void
        __ucr(_ForwardIterator __first, _ForwardIterator __last,
	      _Tp& __value)
        {
	  if(__first == __last)
	    return;

	  _ForwardIterator __cur = __first;
	  try
	    {
	      std::_Construct(std::__addressof(*__first),
			      (__value));
	      _ForwardIterator __prev = __cur;
	      ++__cur;
	      for(; __cur != __last; ++__cur, ++__prev)
		std::_Construct(std::__addressof(*__cur),
				(*__prev));
	      __value = (*__prev);
	    }
	  catch(...)
	    {
	      std::_Destroy(__first, __cur);
	      throw;
	    }
	}
    };

  template<>
    struct __uninitialized_construct_buf_dispatch<true>
    {
      template<typename _ForwardIterator, typename _Tp>
        static void
        __ucr(_ForwardIterator, _ForwardIterator, _Tp&) { }
    };

  
  
  
  
  
  
  
  
  
  
  template<typename _ForwardIterator, typename _Tp>
    inline void
    __uninitialized_construct_buf(_ForwardIterator __first,
				  _ForwardIterator __last,
				  _Tp& __value)
    {
      typedef typename std::iterator_traits<_ForwardIterator>::value_type
	_ValueType;

      std::__uninitialized_construct_buf_dispatch<
        __has_trivial_constructor(_ValueType)>::
	  __ucr(__first, __last, __value);
    }

  template<typename _ForwardIterator, typename _Tp>
    _Temporary_buffer<_ForwardIterator, _Tp>::
    _Temporary_buffer(_ForwardIterator __first, _ForwardIterator __last)
    : _M_original_len(std::distance(__first, __last)),
      _M_len(0), _M_buffer(0)
    {
      try
	{
	  std::pair<pointer, size_type> __p(std::get_temporary_buffer<
					    value_type>(_M_original_len));
	  _M_buffer = __p.first;
	  _M_len = __p.second;
	  if(_M_buffer)
	    std::__uninitialized_construct_buf(_M_buffer, _M_buffer + _M_len,
					       *__first);
	}
      catch(...)
	{
	  std::return_temporary_buffer(_M_buffer);
	  _M_buffer = 0;
	  _M_len = 0;
	  throw;
	}
    }


} 






namespace std __attribute__ ((__visibility__ ("default")))
{


  
  template<typename _Iterator>
    void
    __move_median_first(_Iterator __a, _Iterator __b, _Iterator __c)
    {
      
      

      if (*__a < *__b)
	{
	  if (*__b < *__c)
	    std::iter_swap(__a, __b);
	  else if (*__a < *__c)
	    std::iter_swap(__a, __c);
	}
      else if (*__a < *__c)
	return;
      else if (*__b < *__c)
	std::iter_swap(__a, __c);
      else
	std::iter_swap(__a, __b);
    }

  
  template<typename _Iterator, typename _Compare>
    void
    __move_median_first(_Iterator __a, _Iterator __b, _Iterator __c,
			_Compare __comp)
    {
      
      

      if (__comp(*__a, *__b))
	{
	  if (__comp(*__b, *__c))
	    std::iter_swap(__a, __b);
	  else if (__comp(*__a, *__c))
	    std::iter_swap(__a, __c);
	}
      else if (__comp(*__a, *__c))
	return;
      else if (__comp(*__b, *__c))
	std::iter_swap(__a, __c);
      else
	std::iter_swap(__a, __b);
    }

  

  
  template<typename _InputIterator, typename _Tp>
    inline _InputIterator
    __find(_InputIterator __first, _InputIterator __last,
	   const _Tp& __val, input_iterator_tag)
    {
      while (__first != __last && !(*__first == __val))
	++__first;
      return __first;
    }

  
  template<typename _InputIterator, typename _Predicate>
    inline _InputIterator
    __find_if(_InputIterator __first, _InputIterator __last,
	      _Predicate __pred, input_iterator_tag)
    {
      while (__first != __last && !bool(__pred(*__first)))
	++__first;
      return __first;
    }

  
  template<typename _RandomAccessIterator, typename _Tp>
    _RandomAccessIterator
    __find(_RandomAccessIterator __first, _RandomAccessIterator __last,
	   const _Tp& __val, random_access_iterator_tag)
    {
      typename iterator_traits<_RandomAccessIterator>::difference_type
	__trip_count = (__last - __first) >> 2;

      for (; __trip_count > 0; --__trip_count)
	{
	  if (*__first == __val)
	    return __first;
	  ++__first;

	  if (*__first == __val)
	    return __first;
	  ++__first;

	  if (*__first == __val)
	    return __first;
	  ++__first;

	  if (*__first == __val)
	    return __first;
	  ++__first;
	}

      switch (__last - __first)
	{
	case 3:
	  if (*__first == __val)
	    return __first;
	  ++__first;
	case 2:
	  if (*__first == __val)
	    return __first;
	  ++__first;
	case 1:
	  if (*__first == __val)
	    return __first;
	  ++__first;
	case 0:
	default:
	  return __last;
	}
    }

  
  template<typename _RandomAccessIterator, typename _Predicate>
    _RandomAccessIterator
    __find_if(_RandomAccessIterator __first, _RandomAccessIterator __last,
	      _Predicate __pred, random_access_iterator_tag)
    {
      typename iterator_traits<_RandomAccessIterator>::difference_type
	__trip_count = (__last - __first) >> 2;

      for (; __trip_count > 0; --__trip_count)
	{
	  if (__pred(*__first))
	    return __first;
	  ++__first;

	  if (__pred(*__first))
	    return __first;
	  ++__first;

	  if (__pred(*__first))
	    return __first;
	  ++__first;

	  if (__pred(*__first))
	    return __first;
	  ++__first;
	}

      switch (__last - __first)
	{
	case 3:
	  if (__pred(*__first))
	    return __first;
	  ++__first;
	case 2:
	  if (__pred(*__first))
	    return __first;
	  ++__first;
	case 1:
	  if (__pred(*__first))
	    return __first;
	  ++__first;
	case 0:
	default:
	  return __last;
	}
    }


  
  
  
  
  
  
  
  
  
  
  
  

  



 
  template<typename _ForwardIterator, typename _Integer, typename _Tp>
    _ForwardIterator
    __search_n(_ForwardIterator __first, _ForwardIterator __last,
	       _Integer __count, const _Tp& __val,
	       std::forward_iterator_tag)
    {
      __first = std::find(__first, __last, __val);
      while (__first != __last)
	{
	  typename iterator_traits<_ForwardIterator>::difference_type
	    __n = __count;
	  _ForwardIterator __i = __first;
	  ++__i;
	  while (__i != __last && __n != 1 && *__i == __val)
	    {
	      ++__i;
	      --__n;
	    }
	  if (__n == 1)
	    return __first;
	  if (__i == __last)
	    return __last;
	  __first = std::find(++__i, __last, __val);
	}
      return __last;
    }

  



 
  template<typename _RandomAccessIter, typename _Integer, typename _Tp>
    _RandomAccessIter
    __search_n(_RandomAccessIter __first, _RandomAccessIter __last,
	       _Integer __count, const _Tp& __val, 
	       std::random_access_iterator_tag)
    {
      
      typedef typename std::iterator_traits<_RandomAccessIter>::difference_type
	_DistanceType;

      _DistanceType __tailSize = __last - __first;
      const _DistanceType __pattSize = __count;

      if (__tailSize < __pattSize)
        return __last;

      const _DistanceType __skipOffset = __pattSize - 1;
      _RandomAccessIter __lookAhead = __first + __skipOffset;
      __tailSize -= __pattSize;

      while (1) 
	{
	  
	  
	  while (!(*__lookAhead == __val)) 
	    {
	      if (__tailSize < __pattSize)
		return __last;  
	      __lookAhead += __pattSize;
	      __tailSize -= __pattSize;
	    }
	  _DistanceType __remainder = __skipOffset;
	  for (_RandomAccessIter __backTrack = __lookAhead - 1; 
	       *__backTrack == __val; --__backTrack)
	    {
	      if (--__remainder == 0)
		return (__lookAhead - __skipOffset); 
	    }
	  if (__remainder > __tailSize)
	    return __last; 
	  __lookAhead += __remainder;
	  __tailSize -= __remainder;
	}
    }

  

  




 
  template<typename _ForwardIterator, typename _Integer, typename _Tp,
           typename _BinaryPredicate>
    _ForwardIterator
    __search_n(_ForwardIterator __first, _ForwardIterator __last,
	       _Integer __count, const _Tp& __val,
	       _BinaryPredicate __binary_pred, std::forward_iterator_tag)
    {
      while (__first != __last && !bool(__binary_pred(*__first, __val)))
        ++__first;

      while (__first != __last)
	{
	  typename iterator_traits<_ForwardIterator>::difference_type
	    __n = __count;
	  _ForwardIterator __i = __first;
	  ++__i;
	  while (__i != __last && __n != 1 && bool(__binary_pred(*__i, __val)))
	    {
	      ++__i;
	      --__n;
	    }
	  if (__n == 1)
	    return __first;
	  if (__i == __last)
	    return __last;
	  __first = ++__i;
	  while (__first != __last
		 && !bool(__binary_pred(*__first, __val)))
	    ++__first;
	}
      return __last;
    }

  




 
  template<typename _RandomAccessIter, typename _Integer, typename _Tp,
	   typename _BinaryPredicate>
    _RandomAccessIter
    __search_n(_RandomAccessIter __first, _RandomAccessIter __last,
	       _Integer __count, const _Tp& __val,
	       _BinaryPredicate __binary_pred, std::random_access_iterator_tag)
    {
      
      typedef typename std::iterator_traits<_RandomAccessIter>::difference_type
	_DistanceType;

      _DistanceType __tailSize = __last - __first;
      const _DistanceType __pattSize = __count;

      if (__tailSize < __pattSize)
        return __last;

      const _DistanceType __skipOffset = __pattSize - 1;
      _RandomAccessIter __lookAhead = __first + __skipOffset;
      __tailSize -= __pattSize;

      while (1) 
	{
	  
	  
	  while (!bool(__binary_pred(*__lookAhead, __val))) 
	    {
	      if (__tailSize < __pattSize)
		return __last;  
	      __lookAhead += __pattSize;
	      __tailSize -= __pattSize;
	    }
	  _DistanceType __remainder = __skipOffset;
	  for (_RandomAccessIter __backTrack = __lookAhead - 1; 
	       __binary_pred(*__backTrack, __val); --__backTrack)
	    {
	      if (--__remainder == 0)
		return (__lookAhead - __skipOffset); 
	    }
	  if (__remainder > __tailSize)
	    return __last; 
	  __lookAhead += __remainder;
	  __tailSize -= __remainder;
	}
    }

  
  template<typename _ForwardIterator1, typename _ForwardIterator2>
    _ForwardIterator1
    __find_end(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
	       _ForwardIterator2 __first2, _ForwardIterator2 __last2,
	       forward_iterator_tag, forward_iterator_tag)
    {
      if (__first2 == __last2)
	return __last1;
      else
	{
	  _ForwardIterator1 __result = __last1;
	  while (1)
	    {
	      _ForwardIterator1 __new_result
		= std::search(__first1, __last1, __first2, __last2);
	      if (__new_result == __last1)
		return __result;
	      else
		{
		  __result = __new_result;
		  __first1 = __new_result;
		  ++__first1;
		}
	    }
	}
    }

  template<typename _ForwardIterator1, typename _ForwardIterator2,
	   typename _BinaryPredicate>
    _ForwardIterator1
    __find_end(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
	       _ForwardIterator2 __first2, _ForwardIterator2 __last2,
	       forward_iterator_tag, forward_iterator_tag,
	       _BinaryPredicate __comp)
    {
      if (__first2 == __last2)
	return __last1;
      else
	{
	  _ForwardIterator1 __result = __last1;
	  while (1)
	    {
	      _ForwardIterator1 __new_result
		= std::search(__first1, __last1, __first2,
					 __last2, __comp);
	      if (__new_result == __last1)
		return __result;
	      else
		{
		  __result = __new_result;
		  __first1 = __new_result;
		  ++__first1;
		}
	    }
	}
    }

  
  template<typename _BidirectionalIterator1, typename _BidirectionalIterator2>
    _BidirectionalIterator1
    __find_end(_BidirectionalIterator1 __first1,
	       _BidirectionalIterator1 __last1,
	       _BidirectionalIterator2 __first2,
	       _BidirectionalIterator2 __last2,
	       bidirectional_iterator_tag, bidirectional_iterator_tag)
    {
      
      
      

      typedef reverse_iterator<_BidirectionalIterator1> _RevIterator1;
      typedef reverse_iterator<_BidirectionalIterator2> _RevIterator2;

      _RevIterator1 __rlast1(__first1);
      _RevIterator2 __rlast2(__first2);
      _RevIterator1 __rresult = std::search(_RevIterator1(__last1),
						       __rlast1,
						       _RevIterator2(__last2),
						       __rlast2);

      if (__rresult == __rlast1)
	return __last1;
      else
	{
	  _BidirectionalIterator1 __result = __rresult.base();
	  std::advance(__result, -std::distance(__first2, __last2));
	  return __result;
	}
    }

  template<typename _BidirectionalIterator1, typename _BidirectionalIterator2,
	   typename _BinaryPredicate>
    _BidirectionalIterator1
    __find_end(_BidirectionalIterator1 __first1,
	       _BidirectionalIterator1 __last1,
	       _BidirectionalIterator2 __first2,
	       _BidirectionalIterator2 __last2,
	       bidirectional_iterator_tag, bidirectional_iterator_tag,
	       _BinaryPredicate __comp)
    {
      
      
      

      typedef reverse_iterator<_BidirectionalIterator1> _RevIterator1;
      typedef reverse_iterator<_BidirectionalIterator2> _RevIterator2;

      _RevIterator1 __rlast1(__first1);
      _RevIterator2 __rlast2(__first2);
      _RevIterator1 __rresult = std::search(_RevIterator1(__last1), __rlast1,
					    _RevIterator2(__last2), __rlast2,
					    __comp);

      if (__rresult == __rlast1)
	return __last1;
      else
	{
	  _BidirectionalIterator1 __result = __rresult.base();
	  std::advance(__result, -std::distance(__first2, __last2));
	  return __result;
	}
    }

  























 
  template<typename _ForwardIterator1, typename _ForwardIterator2>
    inline _ForwardIterator1
    find_end(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
	     _ForwardIterator2 __first2, _ForwardIterator2 __last2)
    {
      
      
      
      
      ;
      ;

      return std::__find_end(__first1, __last1, __first2, __last2,
			     std::__iterator_category(__first1),
			     std::__iterator_category(__first2));
    }

  

























 
  template<typename _ForwardIterator1, typename _ForwardIterator2,
	   typename _BinaryPredicate>
    inline _ForwardIterator1
    find_end(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
	     _ForwardIterator2 __first2, _ForwardIterator2 __last2,
	     _BinaryPredicate __comp)
    {
      
      
      
      
      ;
      ;

      return std::__find_end(__first1, __last1, __first2, __last2,
			     std::__iterator_category(__first1),
			     std::__iterator_category(__first2),
			     __comp);
    }



  












 
  template<typename _InputIterator, typename _OutputIterator, typename _Tp>
    _OutputIterator
    remove_copy(_InputIterator __first, _InputIterator __last,
		_OutputIterator __result, const _Tp& __value)
    {
      
      
      
      
      ;

      for (; __first != __last; ++__first)
	if (!(*__first == __value))
	  {
	    *__result = *__first;
	    ++__result;
	  }
      return __result;
    }

  













 
  template<typename _InputIterator, typename _OutputIterator,
	   typename _Predicate>
    _OutputIterator
    remove_copy_if(_InputIterator __first, _InputIterator __last,
		   _OutputIterator __result, _Predicate __pred)
    {
      
      
      
      
      ;

      for (; __first != __last; ++__first)
	if (!bool(__pred(*__first)))
	  {
	    *__result = *__first;
	    ++__result;
	  }
      return __result;
    }


  















 
  template<typename _ForwardIterator, typename _Tp>
    _ForwardIterator
    remove(_ForwardIterator __first, _ForwardIterator __last,
	   const _Tp& __value)
    {
      
      
      
      ;

      __first = std::find(__first, __last, __value);
      if(__first == __last)
        return __first;
      _ForwardIterator __result = __first;
      ++__first;
      for(; __first != __last; ++__first)
        if(!(*__first == __value))
          {
            *__result = (*__first);
            ++__result;
          }
      return __result;
    }

  















 
  template<typename _ForwardIterator, typename _Predicate>
    _ForwardIterator
    remove_if(_ForwardIterator __first, _ForwardIterator __last,
	      _Predicate __pred)
    {
      
      
      
      ;

      __first = std::find_if(__first, __last, __pred);
      if(__first == __last)
        return __first;
      _ForwardIterator __result = __first;
      ++__first;
      for(; __first != __last; ++__first)
        if(!bool(__pred(*__first)))
          {
            *__result = (*__first);
            ++__result;
          }
      return __result;
    }

  












 
  template<typename _ForwardIterator>
    _ForwardIterator
    unique(_ForwardIterator __first, _ForwardIterator __last)
    {
      
      
      
      ;

      
      __first = std::adjacent_find(__first, __last);
      if (__first == __last)
	return __last;

      
      _ForwardIterator __dest = __first;
      ++__first;
      while (++__first != __last)
	if (!(*__dest == *__first))
	  *++__dest = (*__first);
      return ++__dest;
    }

  













 
  template<typename _ForwardIterator, typename _BinaryPredicate>
    _ForwardIterator
    unique(_ForwardIterator __first, _ForwardIterator __last,
           _BinaryPredicate __binary_pred)
    {
      
      
      
      ;

      
      __first = std::adjacent_find(__first, __last, __binary_pred);
      if (__first == __last)
	return __last;

      
      _ForwardIterator __dest = __first;
      ++__first;
      while (++__first != __last)
	if (!bool(__binary_pred(*__dest, *__first)))
	  *++__dest = (*__first);
      return ++__dest;
    }

  



 
  template<typename _ForwardIterator, typename _OutputIterator>
    _OutputIterator
    __unique_copy(_ForwardIterator __first, _ForwardIterator __last,
		  _OutputIterator __result,
		  forward_iterator_tag, output_iterator_tag)
    {
      
      _ForwardIterator __next = __first;
      *__result = *__first;
      while (++__next != __last)
	if (!(*__first == *__next))
	  {
	    __first = __next;
	    *++__result = *__first;
	  }
      return ++__result;
    }

  



 
  template<typename _InputIterator, typename _OutputIterator>
    _OutputIterator
    __unique_copy(_InputIterator __first, _InputIterator __last,
		  _OutputIterator __result,
		  input_iterator_tag, output_iterator_tag)
    {
      
      typename iterator_traits<_InputIterator>::value_type __value = *__first;
      *__result = __value;
      while (++__first != __last)
	if (!(__value == *__first))
	  {
	    __value = *__first;
	    *++__result = __value;
	  }
      return ++__result;
    }

  



 
  template<typename _InputIterator, typename _ForwardIterator>
    _ForwardIterator
    __unique_copy(_InputIterator __first, _InputIterator __last,
		  _ForwardIterator __result,
		  input_iterator_tag, forward_iterator_tag)
    {
      
      *__result = *__first;
      while (++__first != __last)
	if (!(*__result == *__first))
	  *++__result = *__first;
      return ++__result;
    }

  




 
  template<typename _ForwardIterator, typename _OutputIterator,
	   typename _BinaryPredicate>
    _OutputIterator
    __unique_copy(_ForwardIterator __first, _ForwardIterator __last,
		  _OutputIterator __result, _BinaryPredicate __binary_pred,
		  forward_iterator_tag, output_iterator_tag)
    {
      
      

      _ForwardIterator __next = __first;
      *__result = *__first;
      while (++__next != __last)
	if (!bool(__binary_pred(*__first, *__next)))
	  {
	    __first = __next;
	    *++__result = *__first;
	  }
      return ++__result;
    }

  




 
  template<typename _InputIterator, typename _OutputIterator,
	   typename _BinaryPredicate>
    _OutputIterator
    __unique_copy(_InputIterator __first, _InputIterator __last,
		  _OutputIterator __result, _BinaryPredicate __binary_pred,
		  input_iterator_tag, output_iterator_tag)
    {
      
      

      typename iterator_traits<_InputIterator>::value_type __value = *__first;
      *__result = __value;
      while (++__first != __last)
	if (!bool(__binary_pred(__value, *__first)))
	  {
	    __value = *__first;
	    *++__result = __value;
	  }
      return ++__result;
    }

  




 
  template<typename _InputIterator, typename _ForwardIterator,
	   typename _BinaryPredicate>
    _ForwardIterator
    __unique_copy(_InputIterator __first, _InputIterator __last,
		  _ForwardIterator __result, _BinaryPredicate __binary_pred,
		  input_iterator_tag, forward_iterator_tag)
    {
      
      

      *__result = *__first;
      while (++__first != __last)
	if (!bool(__binary_pred(*__result, *__first)))
	  *++__result = *__first;
      return ++__result;
    }

  



 
  template<typename _BidirectionalIterator>
    void
    __reverse(_BidirectionalIterator __first, _BidirectionalIterator __last,
	      bidirectional_iterator_tag)
    {
      while (true)
	if (__first == __last || __first == --__last)
	  return;
	else
	  {
	    std::iter_swap(__first, __last);
	    ++__first;
	  }
    }

  



 
  template<typename _RandomAccessIterator>
    void
    __reverse(_RandomAccessIterator __first, _RandomAccessIterator __last,
	      random_access_iterator_tag)
    {
      if (__first == __last)
	return;
      --__last;
      while (__first < __last)
	{
	  std::iter_swap(__first, __last);
	  ++__first;
	  --__last;
	}
    }

  










 
  template<typename _BidirectionalIterator>
    inline void
    reverse(_BidirectionalIterator __first, _BidirectionalIterator __last)
    {
      
      
      ;
      std::__reverse(__first, __last, std::__iterator_category(__first));
    }

  














 
  template<typename _BidirectionalIterator, typename _OutputIterator>
    _OutputIterator
    reverse_copy(_BidirectionalIterator __first, _BidirectionalIterator __last,
		 _OutputIterator __result)
    {
      
      
      
      ;

      while (__first != __last)
	{
	  --__last;
	  *__result = *__last;
	  ++__result;
	}
      return __result;
    }

  


 
  template<typename _EuclideanRingElement>
    _EuclideanRingElement
    __gcd(_EuclideanRingElement __m, _EuclideanRingElement __n)
    {
      while (__n != 0)
	{
	  _EuclideanRingElement __t = __m % __n;
	  __m = __n;
	  __n = __t;
	}
      return __m;
    }

  
  template<typename _ForwardIterator>
    void
    __rotate(_ForwardIterator __first,
	     _ForwardIterator __middle,
	     _ForwardIterator __last,
	     forward_iterator_tag)
    {
      if (__first == __middle || __last  == __middle)
	return;

      _ForwardIterator __first2 = __middle;
      do
	{
	  std::iter_swap(__first, __first2);
	  ++__first;
	  ++__first2;
	  if (__first == __middle)
	    __middle = __first2;
	}
      while (__first2 != __last);

      __first2 = __middle;

      while (__first2 != __last)
	{
	  std::iter_swap(__first, __first2);
	  ++__first;
	  ++__first2;
	  if (__first == __middle)
	    __middle = __first2;
	  else if (__first2 == __last)
	    __first2 = __middle;
	}
    }

   
  template<typename _BidirectionalIterator>
    void
    __rotate(_BidirectionalIterator __first,
	     _BidirectionalIterator __middle,
	     _BidirectionalIterator __last,
	      bidirectional_iterator_tag)
    {
      
      

      if (__first == __middle || __last  == __middle)
	return;

      std::__reverse(__first,  __middle, bidirectional_iterator_tag());
      std::__reverse(__middle, __last,   bidirectional_iterator_tag());

      while (__first != __middle && __middle != __last)
	{
	  std::iter_swap(__first, --__last);
	  ++__first;
	}

      if (__first == __middle)
	std::__reverse(__middle, __last,   bidirectional_iterator_tag());
      else
	std::__reverse(__first,  __middle, bidirectional_iterator_tag());
    }

  
  template<typename _RandomAccessIterator>
    void
    __rotate(_RandomAccessIterator __first,
	     _RandomAccessIterator __middle,
	     _RandomAccessIterator __last,
	     random_access_iterator_tag)
    {
      
      

      if (__first == __middle || __last  == __middle)
	return;

      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
	_Distance;
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	_ValueType;

      _Distance __n = __last   - __first;
      _Distance __k = __middle - __first;

      if (__k == __n - __k)
	{
	  std::swap_ranges(__first, __middle, __middle);
	  return;
	}

      _RandomAccessIterator __p = __first;

      for (;;)
	{
	  if (__k < __n - __k)
	    {
	      if (__is_pod(_ValueType) && __k == 1)
		{
		  _ValueType __t = (*__p);
		  std::copy(__p + 1, __p + __n, __p);
		  *(__p + __n - 1) = (__t);
		  return;
		}
	      _RandomAccessIterator __q = __p + __k;
	      for (_Distance __i = 0; __i < __n - __k; ++ __i)
		{
		  std::iter_swap(__p, __q);
		  ++__p;
		  ++__q;
		}
	      __n %= __k;
	      if (__n == 0)
		return;
	      std::swap(__n, __k);
	      __k = __n - __k;
	    }
	  else
	    {
	      __k = __n - __k;
	      if (__is_pod(_ValueType) && __k == 1)
		{
		  _ValueType __t = (*(__p + __n - 1));
		  std::copy_backward(__p, __p + __n - 1, __p + __n);
		  *__p = (__t);
		  return;
		}
	      _RandomAccessIterator __q = __p + __n;
	      __p = __q - __k;
	      for (_Distance __i = 0; __i < __n - __k; ++ __i)
		{
		  --__p;
		  --__q;
		  std::iter_swap(__p, __q);
		}
	      __n %= __k;
	      if (__n == 0)
		return;
	      std::swap(__n, __k);
	    }
	}
    }

  

















 
  template<typename _ForwardIterator>
    inline void
    rotate(_ForwardIterator __first, _ForwardIterator __middle,
	   _ForwardIterator __last)
    {
      
      
      ;
      ;

      typedef typename iterator_traits<_ForwardIterator>::iterator_category
	_IterType;
      std::__rotate(__first, __middle, __last, _IterType());
    }

  
















 
  template<typename _ForwardIterator, typename _OutputIterator>
    _OutputIterator
    rotate_copy(_ForwardIterator __first, _ForwardIterator __middle,
                _ForwardIterator __last, _OutputIterator __result)
    {
      
      
      
      ;
      ;

      return std::copy(__first, __middle,
                       std::copy(__middle, __last, __result));
    }

  
  template<typename _ForwardIterator, typename _Predicate>
    _ForwardIterator
    __partition(_ForwardIterator __first, _ForwardIterator __last,
		_Predicate __pred, forward_iterator_tag)
    {
      if (__first == __last)
	return __first;

      while (__pred(*__first))
	if (++__first == __last)
	  return __first;

      _ForwardIterator __next = __first;

      while (++__next != __last)
	if (__pred(*__next))
	  {
	    std::iter_swap(__first, __next);
	    ++__first;
	  }

      return __first;
    }

  
  template<typename _BidirectionalIterator, typename _Predicate>
    _BidirectionalIterator
    __partition(_BidirectionalIterator __first, _BidirectionalIterator __last,
		_Predicate __pred, bidirectional_iterator_tag)
    {
      while (true)
	{
	  while (true)
	    if (__first == __last)
	      return __first;
	    else if (__pred(*__first))
	      ++__first;
	    else
	      break;
	  --__last;
	  while (true)
	    if (__first == __last)
	      return __first;
	    else if (!bool(__pred(*__last)))
	      --__last;
	    else
	      break;
	  std::iter_swap(__first, __last);
	  ++__first;
	}
    }

  

  
  template<typename _ForwardIterator, typename _Predicate, typename _Distance>
    _ForwardIterator
    __inplace_stable_partition(_ForwardIterator __first,
			       _ForwardIterator __last,
			       _Predicate __pred, _Distance __len)
    {
      if (__len == 1)
	return __pred(*__first) ? __last : __first;
      _ForwardIterator __middle = __first;
      std::advance(__middle, __len / 2);
      _ForwardIterator __begin = std::__inplace_stable_partition(__first,
								 __middle,
								 __pred,
								 __len / 2);
      _ForwardIterator __end = std::__inplace_stable_partition(__middle, __last,
							       __pred,
							       __len
							       - __len / 2);
      std::rotate(__begin, __middle, __end);
      std::advance(__begin, std::distance(__middle, __end));
      return __begin;
    }

  
  template<typename _ForwardIterator, typename _Pointer, typename _Predicate,
	   typename _Distance>
    _ForwardIterator
    __stable_partition_adaptive(_ForwardIterator __first,
				_ForwardIterator __last,
				_Predicate __pred, _Distance __len,
				_Pointer __buffer,
				_Distance __buffer_size)
    {
      if (__len <= __buffer_size)
	{
	  _ForwardIterator __result1 = __first;
	  _Pointer __result2 = __buffer;
	  for (; __first != __last; ++__first)
	    if (__pred(*__first))
	      {
		*__result1 = (*__first);
		++__result1;
	      }
	    else
	      {
		*__result2 = (*__first);
		++__result2;
	      }
	  std::copy(__buffer, __result2, __result1);
	  return __result1;
	}
      else
	{
	  _ForwardIterator __middle = __first;
	  std::advance(__middle, __len / 2);
	  _ForwardIterator __begin =
	    std::__stable_partition_adaptive(__first, __middle, __pred,
					     __len / 2, __buffer,
					     __buffer_size);
	  _ForwardIterator __end =
	    std::__stable_partition_adaptive(__middle, __last, __pred,
					     __len - __len / 2,
					     __buffer, __buffer_size);
	  std::rotate(__begin, __middle, __end);
	  std::advance(__begin, std::distance(__middle, __end));
	  return __begin;
	}
    }

  















 
  template<typename _ForwardIterator, typename _Predicate>
    _ForwardIterator
    stable_partition(_ForwardIterator __first, _ForwardIterator __last,
		     _Predicate __pred)
    {
      
      
      
      ;

      if (__first == __last)
	return __first;
      else
	{
	  typedef typename iterator_traits<_ForwardIterator>::value_type
	    _ValueType;
	  typedef typename iterator_traits<_ForwardIterator>::difference_type
	    _DistanceType;

	  _Temporary_buffer<_ForwardIterator, _ValueType> __buf(__first,
								__last);
	if (__buf.size() > 0)
	  return
	    std::__stable_partition_adaptive(__first, __last, __pred,
					  _DistanceType(__buf.requested_size()),
					  __buf.begin(),
					  _DistanceType(__buf.size()));
	else
	  return
	    std::__inplace_stable_partition(__first, __last, __pred,
					 _DistanceType(__buf.requested_size()));
	}
    }

  
  template<typename _RandomAccessIterator>
    void
    __heap_select(_RandomAccessIterator __first,
		  _RandomAccessIterator __middle,
		  _RandomAccessIterator __last)
    {
      std::make_heap(__first, __middle);
      for (_RandomAccessIterator __i = __middle; __i < __last; ++__i)
	if (*__i < *__first)
	  std::__pop_heap(__first, __middle, __i);
    }

  
  template<typename _RandomAccessIterator, typename _Compare>
    void
    __heap_select(_RandomAccessIterator __first,
		  _RandomAccessIterator __middle,
		  _RandomAccessIterator __last, _Compare __comp)
    {
      std::make_heap(__first, __middle, __comp);
      for (_RandomAccessIterator __i = __middle; __i < __last; ++__i)
	if (__comp(*__i, *__first))
	  std::__pop_heap(__first, __middle, __i, __comp);
    }

  

  
















 
  template<typename _InputIterator, typename _RandomAccessIterator>
    _RandomAccessIterator
    partial_sort_copy(_InputIterator __first, _InputIterator __last,
		      _RandomAccessIterator __result_first,
		      _RandomAccessIterator __result_last)
    {
      typedef typename iterator_traits<_InputIterator>::value_type
	_InputValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	_OutputValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
	_DistanceType;

      
      
      
      
      
      ;
      ;

      if (__result_first == __result_last)
	return __result_last;
      _RandomAccessIterator __result_real_last = __result_first;
      while(__first != __last && __result_real_last != __result_last)
	{
	  *__result_real_last = *__first;
	  ++__result_real_last;
	  ++__first;
	}
      std::make_heap(__result_first, __result_real_last);
      while (__first != __last)
	{
	  if (*__first < *__result_first)
	    std::__adjust_heap(__result_first, _DistanceType(0),
			       _DistanceType(__result_real_last
					     - __result_first),
			       _InputValueType(*__first));
	  ++__first;
	}
      std::sort_heap(__result_first, __result_real_last);
      return __result_real_last;
    }

  


















 
  template<typename _InputIterator, typename _RandomAccessIterator, typename _Compare>
    _RandomAccessIterator
    partial_sort_copy(_InputIterator __first, _InputIterator __last,
		      _RandomAccessIterator __result_first,
		      _RandomAccessIterator __result_last,
		      _Compare __comp)
    {
      typedef typename iterator_traits<_InputIterator>::value_type
	_InputValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	_OutputValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
	_DistanceType;

      
      
      
      
      
      
      ;
      ;

      if (__result_first == __result_last)
	return __result_last;
      _RandomAccessIterator __result_real_last = __result_first;
      while(__first != __last && __result_real_last != __result_last)
	{
	  *__result_real_last = *__first;
	  ++__result_real_last;
	  ++__first;
	}
      std::make_heap(__result_first, __result_real_last, __comp);
      while (__first != __last)
	{
	  if (__comp(*__first, *__result_first))
	    std::__adjust_heap(__result_first, _DistanceType(0),
			       _DistanceType(__result_real_last
					     - __result_first),
			       _InputValueType(*__first),
			       __comp);
	  ++__first;
	}
      std::sort_heap(__result_first, __result_real_last, __comp);
      return __result_real_last;
    }

  
  template<typename _RandomAccessIterator>
    void
    __unguarded_linear_insert(_RandomAccessIterator __last)
    {
      typename iterator_traits<_RandomAccessIterator>::value_type
	__val = (*__last);
      _RandomAccessIterator __next = __last;
      --__next;
      while (__val < *__next)
	{
	  *__last = (*__next);
	  __last = __next;
	  --__next;
	}
      *__last = (__val);
    }

  
  template<typename _RandomAccessIterator, typename _Compare>
    void
    __unguarded_linear_insert(_RandomAccessIterator __last,
			      _Compare __comp)
    {
      typename iterator_traits<_RandomAccessIterator>::value_type
	__val = (*__last);
      _RandomAccessIterator __next = __last;
      --__next;
      while (__comp(__val, *__next))
	{
	  *__last = (*__next);
	  __last = __next;
	  --__next;
	}
      *__last = (__val);
    }

  
  template<typename _RandomAccessIterator>
    void
    __insertion_sort(_RandomAccessIterator __first,
		     _RandomAccessIterator __last)
    {
      if (__first == __last)
	return;

      for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
	{
	  if (*__i < *__first)
	    {
	      typename iterator_traits<_RandomAccessIterator>::value_type
		__val = (*__i);
	      std::copy_backward(__first, __i, __i + 1);
	      *__first = (__val);
	    }
	  else
	    std::__unguarded_linear_insert(__i);
	}
    }

  
  template<typename _RandomAccessIterator, typename _Compare>
    void
    __insertion_sort(_RandomAccessIterator __first,
		     _RandomAccessIterator __last, _Compare __comp)
    {
      if (__first == __last) return;

      for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
	{
	  if (__comp(*__i, *__first))
	    {
	      typename iterator_traits<_RandomAccessIterator>::value_type
		__val = (*__i);
	      std::copy_backward(__first, __i, __i + 1);
	      *__first = (__val);
	    }
	  else
	    std::__unguarded_linear_insert(__i, __comp);
	}
    }

  
  template<typename _RandomAccessIterator>
    inline void
    __unguarded_insertion_sort(_RandomAccessIterator __first,
			       _RandomAccessIterator __last)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	_ValueType;

      for (_RandomAccessIterator __i = __first; __i != __last; ++__i)
	std::__unguarded_linear_insert(__i);
    }

  
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    __unguarded_insertion_sort(_RandomAccessIterator __first,
			       _RandomAccessIterator __last, _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	_ValueType;

      for (_RandomAccessIterator __i = __first; __i != __last; ++__i)
	std::__unguarded_linear_insert(__i, __comp);
    }

  


 
  enum { _S_threshold = 16 };

  
  template<typename _RandomAccessIterator>
    void
    __final_insertion_sort(_RandomAccessIterator __first,
			   _RandomAccessIterator __last)
    {
      if (__last - __first > int(_S_threshold))
	{
	  std::__insertion_sort(__first, __first + int(_S_threshold));
	  std::__unguarded_insertion_sort(__first + int(_S_threshold), __last);
	}
      else
	std::__insertion_sort(__first, __last);
    }

  
  template<typename _RandomAccessIterator, typename _Compare>
    void
    __final_insertion_sort(_RandomAccessIterator __first,
			   _RandomAccessIterator __last, _Compare __comp)
    {
      if (__last - __first > int(_S_threshold))
	{
	  std::__insertion_sort(__first, __first + int(_S_threshold), __comp);
	  std::__unguarded_insertion_sort(__first + int(_S_threshold), __last,
					  __comp);
	}
      else
	std::__insertion_sort(__first, __last, __comp);
    }

  
  template<typename _RandomAccessIterator, typename _Tp>
    _RandomAccessIterator
    __unguarded_partition(_RandomAccessIterator __first,
			  _RandomAccessIterator __last, const _Tp& __pivot)
    {
      while (true)
	{
	  while (*__first < __pivot)
	    ++__first;
	  --__last;
	  while (__pivot < *__last)
	    --__last;
	  if (!(__first < __last))
	    return __first;
	  std::iter_swap(__first, __last);
	  ++__first;
	}
    }

  
  template<typename _RandomAccessIterator, typename _Tp, typename _Compare>
    _RandomAccessIterator
    __unguarded_partition(_RandomAccessIterator __first,
			  _RandomAccessIterator __last,
			  const _Tp& __pivot, _Compare __comp)
    {
      while (true)
	{
	  while (__comp(*__first, __pivot))
	    ++__first;
	  --__last;
	  while (__comp(__pivot, *__last))
	    --__last;
	  if (!(__first < __last))
	    return __first;
	  std::iter_swap(__first, __last);
	  ++__first;
	}
    }

  
  template<typename _RandomAccessIterator>
    inline _RandomAccessIterator
    __unguarded_partition_pivot(_RandomAccessIterator __first,
				_RandomAccessIterator __last)
    {
      _RandomAccessIterator __mid = __first + (__last - __first) / 2;
      std::__move_median_first(__first, __mid, (__last - 1));
      return std::__unguarded_partition(__first + 1, __last, *__first);
    }


  
  template<typename _RandomAccessIterator, typename _Compare>
    inline _RandomAccessIterator
    __unguarded_partition_pivot(_RandomAccessIterator __first,
				_RandomAccessIterator __last, _Compare __comp)
    {
      _RandomAccessIterator __mid = __first + (__last - __first) / 2;
      std::__move_median_first(__first, __mid, (__last - 1), __comp);
      return std::__unguarded_partition(__first + 1, __last, *__first, __comp);
    }

  
  template<typename _RandomAccessIterator, typename _Size>
    void
    __introsort_loop(_RandomAccessIterator __first,
		     _RandomAccessIterator __last,
		     _Size __depth_limit)
    {
      while (__last - __first > int(_S_threshold))
	{
	  if (__depth_limit == 0)
	    {
	      std::partial_sort(__first, __last, __last);
	      return;
	    }
	  --__depth_limit;
	  _RandomAccessIterator __cut =
	    std::__unguarded_partition_pivot(__first, __last);
	  std::__introsort_loop(__cut, __last, __depth_limit);
	  __last = __cut;
	}
    }

  
  template<typename _RandomAccessIterator, typename _Size, typename _Compare>
    void
    __introsort_loop(_RandomAccessIterator __first,
		     _RandomAccessIterator __last,
		     _Size __depth_limit, _Compare __comp)
    {
      while (__last - __first > int(_S_threshold))
	{
	  if (__depth_limit == 0)
	    {
	      std::partial_sort(__first, __last, __last, __comp);
	      return;
	    }
	  --__depth_limit;
	  _RandomAccessIterator __cut =
	    std::__unguarded_partition_pivot(__first, __last, __comp);
	  std::__introsort_loop(__cut, __last, __depth_limit, __comp);
	  __last = __cut;
	}
    }

  

  template<typename _RandomAccessIterator, typename _Size>
    void
    __introselect(_RandomAccessIterator __first, _RandomAccessIterator __nth,
		  _RandomAccessIterator __last, _Size __depth_limit)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	_ValueType;

      while (__last - __first > 3)
	{
	  if (__depth_limit == 0)
	    {
	      std::__heap_select(__first, __nth + 1, __last);

	      
	      std::iter_swap(__first, __nth);
	      return;
	    }
	  --__depth_limit;
	  _RandomAccessIterator __cut =
	    std::__unguarded_partition_pivot(__first, __last);
	  if (__cut <= __nth)
	    __first = __cut;
	  else
	    __last = __cut;
	}
      std::__insertion_sort(__first, __last);
    }

  template<typename _RandomAccessIterator, typename _Size, typename _Compare>
    void
    __introselect(_RandomAccessIterator __first, _RandomAccessIterator __nth,
		  _RandomAccessIterator __last, _Size __depth_limit,
		  _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	_ValueType;

      while (__last - __first > 3)
	{
	  if (__depth_limit == 0)
	    {
	      std::__heap_select(__first, __nth + 1, __last, __comp);
	      
	      std::iter_swap(__first, __nth);
	      return;
	    }
	  --__depth_limit;
	  _RandomAccessIterator __cut =
	    std::__unguarded_partition_pivot(__first, __last, __comp);
	  if (__cut <= __nth)
	    __first = __cut;
	  else
	    __last = __cut;
	}
      std::__insertion_sort(__first, __last, __comp);
    }

  

  

  














 
  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    _ForwardIterator
    lower_bound(_ForwardIterator __first, _ForwardIterator __last,
		const _Tp& __val, _Compare __comp)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
	_ValueType;
      typedef typename iterator_traits<_ForwardIterator>::difference_type
	_DistanceType;

      
      
      
      ;

      _DistanceType __len = std::distance(__first, __last);

      while (__len > 0)
	{
	  _DistanceType __half = __len >> 1;
	  _ForwardIterator __middle = __first;
	  std::advance(__middle, __half);
	  if (__comp(*__middle, __val))
	    {
	      __first = __middle;
	      ++__first;
	      __len = __len - __half - 1;
	    }
	  else
	    __len = __half;
	}
      return __first;
    }

  









 
  template<typename _ForwardIterator, typename _Tp>
    _ForwardIterator
    upper_bound(_ForwardIterator __first, _ForwardIterator __last,
		const _Tp& __val)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
	_ValueType;
      typedef typename iterator_traits<_ForwardIterator>::difference_type
	_DistanceType;

      
      
      
      ;

      _DistanceType __len = std::distance(__first, __last);

      while (__len > 0)
	{
	  _DistanceType __half = __len >> 1;
	  _ForwardIterator __middle = __first;
	  std::advance(__middle, __half);
	  if (__val < *__middle)
	    __len = __half;
	  else
	    {
	      __first = __middle;
	      ++__first;
	      __len = __len - __half - 1;
	    }
	}
      return __first;
    }

  













 
  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    _ForwardIterator
    upper_bound(_ForwardIterator __first, _ForwardIterator __last,
		const _Tp& __val, _Compare __comp)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
	_ValueType;
      typedef typename iterator_traits<_ForwardIterator>::difference_type
	_DistanceType;

      
      
      
      ;

      _DistanceType __len = std::distance(__first, __last);

      while (__len > 0)
	{
	  _DistanceType __half = __len >> 1;
	  _ForwardIterator __middle = __first;
	  std::advance(__middle, __half);
	  if (__comp(__val, *__middle))
	    __len = __half;
	  else
	    {
	      __first = __middle;
	      ++__first;
	      __len = __len - __half - 1;
	    }
	}
      return __first;
    }

  















 
  template<typename _ForwardIterator, typename _Tp>
    pair<_ForwardIterator, _ForwardIterator>
    equal_range(_ForwardIterator __first, _ForwardIterator __last,
		const _Tp& __val)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
	_ValueType;
      typedef typename iterator_traits<_ForwardIterator>::difference_type
	_DistanceType;

      
      
      
      	
      ;
      ;      

      _DistanceType __len = std::distance(__first, __last);
 
      while (__len > 0)
	{
	  _DistanceType __half = __len >> 1;
	  _ForwardIterator __middle = __first;
	  std::advance(__middle, __half);
	  if (*__middle < __val)
	    {
	      __first = __middle;
	      ++__first;
	      __len = __len - __half - 1;
	    }
	  else if (__val < *__middle)
	    __len = __half;
	  else
	    {
	      _ForwardIterator __left = std::lower_bound(__first, __middle,
							 __val);
	      std::advance(__first, __len);
	      _ForwardIterator __right = std::upper_bound(++__middle, __first,
							  __val);
	      return pair<_ForwardIterator, _ForwardIterator>(__left, __right);
	    }
	}
      return pair<_ForwardIterator, _ForwardIterator>(__first, __first);
    }

  















 
  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    pair<_ForwardIterator, _ForwardIterator>
    equal_range(_ForwardIterator __first, _ForwardIterator __last,
		const _Tp& __val, _Compare __comp)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
	_ValueType;
      typedef typename iterator_traits<_ForwardIterator>::difference_type
	_DistanceType;

      
      
      
      
      ;
      ;

      _DistanceType __len = std::distance(__first, __last);

      while (__len > 0)
	{
	  _DistanceType __half = __len >> 1;
	  _ForwardIterator __middle = __first;
	  std::advance(__middle, __half);
	  if (__comp(*__middle, __val))
	    {
	      __first = __middle;
	      ++__first;
	      __len = __len - __half - 1;
	    }
	  else if (__comp(__val, *__middle))
	    __len = __half;
	  else
	    {
	      _ForwardIterator __left = std::lower_bound(__first, __middle,
							 __val, __comp);
	      std::advance(__first, __len);
	      _ForwardIterator __right = std::upper_bound(++__middle, __first,
							  __val, __comp);
	      return pair<_ForwardIterator, _ForwardIterator>(__left, __right);
	    }
	}
      return pair<_ForwardIterator, _ForwardIterator>(__first, __first);
    }

  









 
  template<typename _ForwardIterator, typename _Tp>
    bool
    binary_search(_ForwardIterator __first, _ForwardIterator __last,
                  const _Tp& __val)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
	_ValueType;

      
      
      
      ;
      ;

      _ForwardIterator __i = std::lower_bound(__first, __last, __val);
      return __i != __last && !(__val < *__i);
    }

  













 
  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    bool
    binary_search(_ForwardIterator __first, _ForwardIterator __last,
                  const _Tp& __val, _Compare __comp)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
	_ValueType;

      
      
      
      ;
      ;

      _ForwardIterator __i = std::lower_bound(__first, __last, __val, __comp);
      return __i != __last && !bool(__comp(__val, *__i));
    }

  

  
  template<typename _BidirectionalIterator1, typename _BidirectionalIterator2,
	   typename _BidirectionalIterator3>
    _BidirectionalIterator3
    __move_merge_backward(_BidirectionalIterator1 __first1,
			  _BidirectionalIterator1 __last1,
			  _BidirectionalIterator2 __first2,
			  _BidirectionalIterator2 __last2,
			  _BidirectionalIterator3 __result)
    {
      if (__first1 == __last1)
	return std::copy_backward(__first2, __last2, __result);
      if (__first2 == __last2)
	return std::copy_backward(__first1, __last1, __result);
      --__last1;
      --__last2;
      while (true)
	{
	  if (*__last2 < *__last1)
	    {
	      *--__result = (*__last1);
	      if (__first1 == __last1)
		return std::copy_backward(__first2, ++__last2, __result);
	      --__last1;
	    }
	  else
	    {
	      *--__result = (*__last2);
	      if (__first2 == __last2)
		return std::copy_backward(__first1, ++__last1, __result);
	      --__last2;
	    }
	}
    }

  
  template<typename _BidirectionalIterator1, typename _BidirectionalIterator2,
	   typename _BidirectionalIterator3, typename _Compare>
    _BidirectionalIterator3
    __move_merge_backward(_BidirectionalIterator1 __first1,
			  _BidirectionalIterator1 __last1,
			  _BidirectionalIterator2 __first2,
			  _BidirectionalIterator2 __last2,
			  _BidirectionalIterator3 __result,
			  _Compare __comp)
    {
      if (__first1 == __last1)
	return std::copy_backward(__first2, __last2, __result);
      if (__first2 == __last2)
	return std::copy_backward(__first1, __last1, __result);
      --__last1;
      --__last2;
      while (true)
	{
	  if (__comp(*__last2, *__last1))
	    {
	      *--__result = (*__last1);
	      if (__first1 == __last1)
		return std::copy_backward(__first2, ++__last2, __result);
	      --__last1;
	    }
	  else
	    {
	      *--__result = (*__last2);
	      if (__first2 == __last2)
		return std::copy_backward(__first1, ++__last1, __result);
	      --__last2;
	    }
	}
    }

  
  template<typename _InputIterator1, typename _InputIterator2,
	   typename _OutputIterator>
    _OutputIterator
    __move_merge(_InputIterator1 __first1, _InputIterator1 __last1,
		 _InputIterator2 __first2, _InputIterator2 __last2,
		 _OutputIterator __result)
    {
      while (__first1 != __last1 && __first2 != __last2)
	{
	  if (*__first2 < *__first1)
	    {
	      *__result = (*__first2);
	      ++__first2;
	    }
	  else
	    {
	      *__result = (*__first1);
	      ++__first1;
	    }
	  ++__result;
	}
      return std::copy(__first2, __last2, std::copy(__first1, __last1, __result));
    }

  
  template<typename _InputIterator1, typename _InputIterator2,
	   typename _OutputIterator, typename _Compare>
    _OutputIterator
    __move_merge(_InputIterator1 __first1, _InputIterator1 __last1,
		 _InputIterator2 __first2, _InputIterator2 __last2,
		 _OutputIterator __result, _Compare __comp)
    {
      while (__first1 != __last1 && __first2 != __last2)
	{
	  if (__comp(*__first2, *__first1))
	    {
	      *__result = (*__first2);
	      ++__first2;
	    }
	  else
	    {
	      *__result = (*__first1);
	      ++__first1;
	    }
	  ++__result;
	}
      return std::copy(__first2, __last2, std::copy(__first1, __last1, __result));
    }


  
  template<typename _BidirectionalIterator1, typename _BidirectionalIterator2,
	   typename _Distance>
    _BidirectionalIterator1
    __rotate_adaptive(_BidirectionalIterator1 __first,
		      _BidirectionalIterator1 __middle,
		      _BidirectionalIterator1 __last,
		      _Distance __len1, _Distance __len2,
		      _BidirectionalIterator2 __buffer,
		      _Distance __buffer_size)
    {
      _BidirectionalIterator2 __buffer_end;
      if (__len1 > __len2 && __len2 <= __buffer_size)
	{
	  __buffer_end = std::copy(__middle, __last, __buffer);
	  std::copy_backward(__first, __middle, __last);
	  return std::copy(__buffer, __buffer_end, __first);
	}
      else if (__len1 <= __buffer_size)
	{
	  __buffer_end = std::copy(__first, __middle, __buffer);
	  std::copy(__middle, __last, __first);
	  return std::copy_backward(__buffer, __buffer_end, __last);
	}
      else
	{
	  std::rotate(__first, __middle, __last);
	  std::advance(__first, std::distance(__middle, __last));
	  return __first;
	}
    }

  
  template<typename _BidirectionalIterator, typename _Distance,
	   typename _Pointer>
    void
    __merge_adaptive(_BidirectionalIterator __first,
                     _BidirectionalIterator __middle,
		     _BidirectionalIterator __last,
		     _Distance __len1, _Distance __len2,
		     _Pointer __buffer, _Distance __buffer_size)
    {
      if (__len1 <= __len2 && __len1 <= __buffer_size)
	{
	  _Pointer __buffer_end = std::copy(__first, __middle, __buffer);
	  std::__move_merge(__buffer, __buffer_end, __middle, __last, __first);
	}
      else if (__len2 <= __buffer_size)
	{
	  _Pointer __buffer_end = std::copy(__middle, __last, __buffer);
	  std::__move_merge_backward(__first, __middle, __buffer,
				    __buffer_end, __last);
	}
      else
	{
	  _BidirectionalIterator __first_cut = __first;
	  _BidirectionalIterator __second_cut = __middle;
	  _Distance __len11 = 0;
	  _Distance __len22 = 0;
	  if (__len1 > __len2)
	    {
	      __len11 = __len1 / 2;
	      std::advance(__first_cut, __len11);
	      __second_cut = std::lower_bound(__middle, __last,
					      *__first_cut);
	      __len22 = std::distance(__middle, __second_cut);
	    }
	  else
	    {
	      __len22 = __len2 / 2;
	      std::advance(__second_cut, __len22);
	      __first_cut = std::upper_bound(__first, __middle,
					     *__second_cut);
	      __len11 = std::distance(__first, __first_cut);
	    }
	  _BidirectionalIterator __new_middle =
	    std::__rotate_adaptive(__first_cut, __middle, __second_cut,
				   __len1 - __len11, __len22, __buffer,
				   __buffer_size);
	  std::__merge_adaptive(__first, __first_cut, __new_middle, __len11,
				__len22, __buffer, __buffer_size);
	  std::__merge_adaptive(__new_middle, __second_cut, __last,
				__len1 - __len11,
				__len2 - __len22, __buffer, __buffer_size);
	}
    }

  
  template<typename _BidirectionalIterator, typename _Distance, 
	   typename _Pointer, typename _Compare>
    void
    __merge_adaptive(_BidirectionalIterator __first,
                     _BidirectionalIterator __middle,
		     _BidirectionalIterator __last,
		     _Distance __len1, _Distance __len2,
		     _Pointer __buffer, _Distance __buffer_size,
		     _Compare __comp)
    {
      if (__len1 <= __len2 && __len1 <= __buffer_size)
	{
	  _Pointer __buffer_end = std::copy(__first, __middle, __buffer);
	  std::__move_merge(__buffer, __buffer_end, __middle, __last,
			    __first, __comp);
	}
      else if (__len2 <= __buffer_size)
	{
	  _Pointer __buffer_end = std::copy(__middle, __last, __buffer);
	  std::__move_merge_backward(__first, __middle, __buffer, __buffer_end,
				     __last, __comp);
	}
      else
	{
	  _BidirectionalIterator __first_cut = __first;
	  _BidirectionalIterator __second_cut = __middle;
	  _Distance __len11 = 0;
	  _Distance __len22 = 0;
	  if (__len1 > __len2)
	    {
	      __len11 = __len1 / 2;
	      std::advance(__first_cut, __len11);
	      __second_cut = std::lower_bound(__middle, __last, *__first_cut,
					      __comp);
	      __len22 = std::distance(__middle, __second_cut);
	    }
	  else
	    {
	      __len22 = __len2 / 2;
	      std::advance(__second_cut, __len22);
	      __first_cut = std::upper_bound(__first, __middle, *__second_cut,
					     __comp);
	      __len11 = std::distance(__first, __first_cut);
	    }
	  _BidirectionalIterator __new_middle =
	    std::__rotate_adaptive(__first_cut, __middle, __second_cut,
				   __len1 - __len11, __len22, __buffer,
				   __buffer_size);
	  std::__merge_adaptive(__first, __first_cut, __new_middle, __len11,
				__len22, __buffer, __buffer_size, __comp);
	  std::__merge_adaptive(__new_middle, __second_cut, __last,
				__len1 - __len11,
				__len2 - __len22, __buffer,
				__buffer_size, __comp);
	}
    }

  
  template<typename _BidirectionalIterator, typename _Distance>
    void
    __merge_without_buffer(_BidirectionalIterator __first,
			   _BidirectionalIterator __middle,
			   _BidirectionalIterator __last,
			   _Distance __len1, _Distance __len2)
    {
      if (__len1 == 0 || __len2 == 0)
	return;
      if (__len1 + __len2 == 2)
	{
	  if (*__middle < *__first)
	    std::iter_swap(__first, __middle);
	  return;
	}
      _BidirectionalIterator __first_cut = __first;
      _BidirectionalIterator __second_cut = __middle;
      _Distance __len11 = 0;
      _Distance __len22 = 0;
      if (__len1 > __len2)
	{
	  __len11 = __len1 / 2;
	  std::advance(__first_cut, __len11);
	  __second_cut = std::lower_bound(__middle, __last, *__first_cut);
	  __len22 = std::distance(__middle, __second_cut);
	}
      else
	{
	  __len22 = __len2 / 2;
	  std::advance(__second_cut, __len22);
	  __first_cut = std::upper_bound(__first, __middle, *__second_cut);
	  __len11 = std::distance(__first, __first_cut);
	}
      std::rotate(__first_cut, __middle, __second_cut);
      _BidirectionalIterator __new_middle = __first_cut;
      std::advance(__new_middle, std::distance(__middle, __second_cut));
      std::__merge_without_buffer(__first, __first_cut, __new_middle,
				  __len11, __len22);
      std::__merge_without_buffer(__new_middle, __second_cut, __last,
				  __len1 - __len11, __len2 - __len22);
    }

  
  template<typename _BidirectionalIterator, typename _Distance,
	   typename _Compare>
    void
    __merge_without_buffer(_BidirectionalIterator __first,
                           _BidirectionalIterator __middle,
			   _BidirectionalIterator __last,
			   _Distance __len1, _Distance __len2,
			   _Compare __comp)
    {
      if (__len1 == 0 || __len2 == 0)
	return;
      if (__len1 + __len2 == 2)
	{
	  if (__comp(*__middle, *__first))
	    std::iter_swap(__first, __middle);
	  return;
	}
      _BidirectionalIterator __first_cut = __first;
      _BidirectionalIterator __second_cut = __middle;
      _Distance __len11 = 0;
      _Distance __len22 = 0;
      if (__len1 > __len2)
	{
	  __len11 = __len1 / 2;
	  std::advance(__first_cut, __len11);
	  __second_cut = std::lower_bound(__middle, __last, *__first_cut,
					  __comp);
	  __len22 = std::distance(__middle, __second_cut);
	}
      else
	{
	  __len22 = __len2 / 2;
	  std::advance(__second_cut, __len22);
	  __first_cut = std::upper_bound(__first, __middle, *__second_cut,
					 __comp);
	  __len11 = std::distance(__first, __first_cut);
	}
      std::rotate(__first_cut, __middle, __second_cut);
      _BidirectionalIterator __new_middle = __first_cut;
      std::advance(__new_middle, std::distance(__middle, __second_cut));
      std::__merge_without_buffer(__first, __first_cut, __new_middle,
				  __len11, __len22, __comp);
      std::__merge_without_buffer(__new_middle, __second_cut, __last,
				  __len1 - __len11, __len2 - __len22, __comp);
    }

  
















 
  template<typename _BidirectionalIterator>
    void
    inplace_merge(_BidirectionalIterator __first,
		  _BidirectionalIterator __middle,
		  _BidirectionalIterator __last)
    {
      typedef typename iterator_traits<_BidirectionalIterator>::value_type
          _ValueType;
      typedef typename iterator_traits<_BidirectionalIterator>::difference_type
          _DistanceType;

      
      
      
      ;
      ;

      if (__first == __middle || __middle == __last)
	return;

      _DistanceType __len1 = std::distance(__first, __middle);
      _DistanceType __len2 = std::distance(__middle, __last);

      _Temporary_buffer<_BidirectionalIterator, _ValueType> __buf(__first,
								  __last);
      if (__buf.begin() == 0)
	std::__merge_without_buffer(__first, __middle, __last, __len1, __len2);
      else
	std::__merge_adaptive(__first, __middle, __last, __len1, __len2,
			      __buf.begin(), _DistanceType(__buf.size()));
    }

  




















 
  template<typename _BidirectionalIterator, typename _Compare>
    void
    inplace_merge(_BidirectionalIterator __first,
		  _BidirectionalIterator __middle,
		  _BidirectionalIterator __last,
		  _Compare __comp)
    {
      typedef typename iterator_traits<_BidirectionalIterator>::value_type
          _ValueType;
      typedef typename iterator_traits<_BidirectionalIterator>::difference_type
          _DistanceType;

      
      
      
      ;
      ;

      if (__first == __middle || __middle == __last)
	return;

      const _DistanceType __len1 = std::distance(__first, __middle);
      const _DistanceType __len2 = std::distance(__middle, __last);

      _Temporary_buffer<_BidirectionalIterator, _ValueType> __buf(__first,
								  __last);
      if (__buf.begin() == 0)
	std::__merge_without_buffer(__first, __middle, __last, __len1,
				    __len2, __comp);
      else
	std::__merge_adaptive(__first, __middle, __last, __len1, __len2,
			      __buf.begin(), _DistanceType(__buf.size()),
			      __comp);
    }

  template<typename _RandomAccessIterator1, typename _RandomAccessIterator2,
	   typename _Distance>
    void
    __merge_sort_loop(_RandomAccessIterator1 __first,
		      _RandomAccessIterator1 __last,
		      _RandomAccessIterator2 __result,
		      _Distance __step_size)
    {
      const _Distance __two_step = 2 * __step_size;

      while (__last - __first >= __two_step)
	{
	  __result = std::__move_merge(__first, __first + __step_size,
				       __first + __step_size,
				       __first + __two_step, __result);
	  __first += __two_step;
	}

      __step_size = std::min(_Distance(__last - __first), __step_size);
      std::__move_merge(__first, __first + __step_size,
			__first + __step_size, __last, __result);
    }

  template<typename _RandomAccessIterator1, typename _RandomAccessIterator2,
	   typename _Distance, typename _Compare>
    void
    __merge_sort_loop(_RandomAccessIterator1 __first,
		      _RandomAccessIterator1 __last,
		      _RandomAccessIterator2 __result, _Distance __step_size,
		      _Compare __comp)
    {
      const _Distance __two_step = 2 * __step_size;

      while (__last - __first >= __two_step)
	{
	  __result = std::__move_merge(__first, __first + __step_size,
				       __first + __step_size,
				       __first + __two_step,
				       __result, __comp);
	  __first += __two_step;
	}
      __step_size = std::min(_Distance(__last - __first), __step_size);

      std::__move_merge(__first,__first + __step_size,
			__first + __step_size, __last, __result, __comp);
    }

  template<typename _RandomAccessIterator, typename _Distance>
    void
    __chunk_insertion_sort(_RandomAccessIterator __first,
			   _RandomAccessIterator __last,
			   _Distance __chunk_size)
    {
      while (__last - __first >= __chunk_size)
	{
	  std::__insertion_sort(__first, __first + __chunk_size);
	  __first += __chunk_size;
	}
      std::__insertion_sort(__first, __last);
    }

  template<typename _RandomAccessIterator, typename _Distance,
	   typename _Compare>
    void
    __chunk_insertion_sort(_RandomAccessIterator __first,
			   _RandomAccessIterator __last,
			   _Distance __chunk_size, _Compare __comp)
    {
      while (__last - __first >= __chunk_size)
	{
	  std::__insertion_sort(__first, __first + __chunk_size, __comp);
	  __first += __chunk_size;
	}
      std::__insertion_sort(__first, __last, __comp);
    }

  enum { _S_chunk_size = 7 };

  template<typename _RandomAccessIterator, typename _Pointer>
    void
    __merge_sort_with_buffer(_RandomAccessIterator __first,
			     _RandomAccessIterator __last,
                             _Pointer __buffer)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
	_Distance;

      const _Distance __len = __last - __first;
      const _Pointer __buffer_last = __buffer + __len;

      _Distance __step_size = _S_chunk_size;
      std::__chunk_insertion_sort(__first, __last, __step_size);

      while (__step_size < __len)
	{
	  std::__merge_sort_loop(__first, __last, __buffer, __step_size);
	  __step_size *= 2;
	  std::__merge_sort_loop(__buffer, __buffer_last, __first, __step_size);
	  __step_size *= 2;
	}
    }

  template<typename _RandomAccessIterator, typename _Pointer, typename _Compare>
    void
    __merge_sort_with_buffer(_RandomAccessIterator __first,
			     _RandomAccessIterator __last,
                             _Pointer __buffer, _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
	_Distance;

      const _Distance __len = __last - __first;
      const _Pointer __buffer_last = __buffer + __len;

      _Distance __step_size = _S_chunk_size;
      std::__chunk_insertion_sort(__first, __last, __step_size, __comp);

      while (__step_size < __len)
	{
	  std::__merge_sort_loop(__first, __last, __buffer,
				 __step_size, __comp);
	  __step_size *= 2;
	  std::__merge_sort_loop(__buffer, __buffer_last, __first,
				 __step_size, __comp);
	  __step_size *= 2;
	}
    }

  template<typename _RandomAccessIterator, typename _Pointer,
	   typename _Distance>
    void
    __stable_sort_adaptive(_RandomAccessIterator __first,
			   _RandomAccessIterator __last,
                           _Pointer __buffer, _Distance __buffer_size)
    {
      const _Distance __len = (__last - __first + 1) / 2;
      const _RandomAccessIterator __middle = __first + __len;
      if (__len > __buffer_size)
	{
	  std::__stable_sort_adaptive(__first, __middle,
				      __buffer, __buffer_size);
	  std::__stable_sort_adaptive(__middle, __last,
				      __buffer, __buffer_size);
	}
      else
	{
	  std::__merge_sort_with_buffer(__first, __middle, __buffer);
	  std::__merge_sort_with_buffer(__middle, __last, __buffer);
	}
      std::__merge_adaptive(__first, __middle, __last,
			    _Distance(__middle - __first),
			    _Distance(__last - __middle),
			    __buffer, __buffer_size);
    }

  template<typename _RandomAccessIterator, typename _Pointer,
	   typename _Distance, typename _Compare>
    void
    __stable_sort_adaptive(_RandomAccessIterator __first,
			   _RandomAccessIterator __last,
                           _Pointer __buffer, _Distance __buffer_size,
                           _Compare __comp)
    {
      const _Distance __len = (__last - __first + 1) / 2;
      const _RandomAccessIterator __middle = __first + __len;
      if (__len > __buffer_size)
	{
	  std::__stable_sort_adaptive(__first, __middle, __buffer,
				      __buffer_size, __comp);
	  std::__stable_sort_adaptive(__middle, __last, __buffer,
				      __buffer_size, __comp);
	}
      else
	{
	  std::__merge_sort_with_buffer(__first, __middle, __buffer, __comp);
	  std::__merge_sort_with_buffer(__middle, __last, __buffer, __comp);
	}
      std::__merge_adaptive(__first, __middle, __last,
			    _Distance(__middle - __first),
			    _Distance(__last - __middle),
			    __buffer, __buffer_size,
			    __comp);
    }

  
  template<typename _RandomAccessIterator>
    void
    __inplace_stable_sort(_RandomAccessIterator __first,
			  _RandomAccessIterator __last)
    {
      if (__last - __first < 15)
	{
	  std::__insertion_sort(__first, __last);
	  return;
	}
      _RandomAccessIterator __middle = __first + (__last - __first) / 2;
      std::__inplace_stable_sort(__first, __middle);
      std::__inplace_stable_sort(__middle, __last);
      std::__merge_without_buffer(__first, __middle, __last,
				  __middle - __first,
				  __last - __middle);
    }

  
  template<typename _RandomAccessIterator, typename _Compare>
    void
    __inplace_stable_sort(_RandomAccessIterator __first,
			  _RandomAccessIterator __last, _Compare __comp)
    {
      if (__last - __first < 15)
	{
	  std::__insertion_sort(__first, __last, __comp);
	  return;
	}
      _RandomAccessIterator __middle = __first + (__last - __first) / 2;
      std::__inplace_stable_sort(__first, __middle, __comp);
      std::__inplace_stable_sort(__middle, __last, __comp);
      std::__merge_without_buffer(__first, __middle, __last,
				  __middle - __first,
				  __last - __middle,
				  __comp);
    }

  

  
  
  
  

  














 
  template<typename _InputIterator1, typename _InputIterator2>
    bool
    includes(_InputIterator1 __first1, _InputIterator1 __last1,
	     _InputIterator2 __first2, _InputIterator2 __last2)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
	_ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
	_ValueType2;

      
      
      
      
      
      ;
      ;

      while (__first1 != __last1 && __first2 != __last2)
	if (*__first2 < *__first1)
	  return false;
	else if(*__first1 < *__first2)
	  ++__first1;
	else
	  ++__first1, ++__first2;

      return __first2 == __last2;
    }

  


















 
  template<typename _InputIterator1, typename _InputIterator2,
	   typename _Compare>
    bool
    includes(_InputIterator1 __first1, _InputIterator1 __last1,
	     _InputIterator2 __first2, _InputIterator2 __last2,
	     _Compare __comp)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
	_ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
	_ValueType2;

      
      
      
      
      
      ;
      ;

      while (__first1 != __last1 && __first2 != __last2)
	if (__comp(*__first2, *__first1))
	  return false;
	else if(__comp(*__first1, *__first2))
	  ++__first1;
	else
	  ++__first1, ++__first2;

      return __first2 == __last2;
    }

  
  
  
  
  
  
  
  
  

  










 
  template<typename _BidirectionalIterator>
    bool
    next_permutation(_BidirectionalIterator __first,
		     _BidirectionalIterator __last)
    {
      
      
      
      ;

      if (__first == __last)
	return false;
      _BidirectionalIterator __i = __first;
      ++__i;
      if (__i == __last)
	return false;
      __i = __last;
      --__i;

      for(;;)
	{
	  _BidirectionalIterator __ii = __i;
	  --__i;
	  if (*__i < *__ii)
	    {
	      _BidirectionalIterator __j = __last;
	      while (!(*__i < *--__j))
		{}
	      std::iter_swap(__i, __j);
	      std::reverse(__ii, __last);
	      return true;
	    }
	  if (__i == __first)
	    {
	      std::reverse(__first, __last);
	      return false;
	    }
	}
    }

  













 
  template<typename _BidirectionalIterator, typename _Compare>
    bool
    next_permutation(_BidirectionalIterator __first,
		     _BidirectionalIterator __last, _Compare __comp)
    {
      
      
      
      ;

      if (__first == __last)
	return false;
      _BidirectionalIterator __i = __first;
      ++__i;
      if (__i == __last)
	return false;
      __i = __last;
      --__i;

      for(;;)
	{
	  _BidirectionalIterator __ii = __i;
	  --__i;
	  if (__comp(*__i, *__ii))
	    {
	      _BidirectionalIterator __j = __last;
	      while (!bool(__comp(*__i, *--__j)))
		{}
	      std::iter_swap(__i, __j);
	      std::reverse(__ii, __last);
	      return true;
	    }
	  if (__i == __first)
	    {
	      std::reverse(__first, __last);
	      return false;
	    }
	}
    }

  











 
  template<typename _BidirectionalIterator>
    bool
    prev_permutation(_BidirectionalIterator __first,
		     _BidirectionalIterator __last)
    {
      
      
      
      ;

      if (__first == __last)
	return false;
      _BidirectionalIterator __i = __first;
      ++__i;
      if (__i == __last)
	return false;
      __i = __last;
      --__i;

      for(;;)
	{
	  _BidirectionalIterator __ii = __i;
	  --__i;
	  if (*__ii < *__i)
	    {
	      _BidirectionalIterator __j = __last;
	      while (!(*--__j < *__i))
		{}
	      std::iter_swap(__i, __j);
	      std::reverse(__ii, __last);
	      return true;
	    }
	  if (__i == __first)
	    {
	      std::reverse(__first, __last);
	      return false;
	    }
	}
    }

  













 
  template<typename _BidirectionalIterator, typename _Compare>
    bool
    prev_permutation(_BidirectionalIterator __first,
		     _BidirectionalIterator __last, _Compare __comp)
    {
      
      
      
      ;

      if (__first == __last)
	return false;
      _BidirectionalIterator __i = __first;
      ++__i;
      if (__i == __last)
	return false;
      __i = __last;
      --__i;

      for(;;)
	{
	  _BidirectionalIterator __ii = __i;
	  --__i;
	  if (__comp(*__ii, *__i))
	    {
	      _BidirectionalIterator __j = __last;
	      while (!bool(__comp(*--__j, *__i)))
		{}
	      std::iter_swap(__i, __j);
	      std::reverse(__ii, __last);
	      return true;
	    }
	  if (__i == __first)
	    {
	      std::reverse(__first, __last);
	      return false;
	    }
	}
    }

  
  

  












 
  template<typename _InputIterator, typename _OutputIterator, typename _Tp>
    _OutputIterator
    replace_copy(_InputIterator __first, _InputIterator __last,
		 _OutputIterator __result,
		 const _Tp& __old_value, const _Tp& __new_value)
    {
      
      
      
      
      ;

      for (; __first != __last; ++__first, ++__result)
	if (*__first == __old_value)
	  *__result = __new_value;
	else
	  *__result = *__first;
      return __result;
    }

  













 
  template<typename _InputIterator, typename _OutputIterator,
	   typename _Predicate, typename _Tp>
    _OutputIterator
    replace_copy_if(_InputIterator __first, _InputIterator __last,
		    _OutputIterator __result,
		    _Predicate __pred, const _Tp& __new_value)
    {
      
      
      
      
      ;

      for (; __first != __last; ++__first, ++__result)
	if (__pred(*__first))
	  *__result = __new_value;
	else
	  *__result = *__first;
      return __result;
    }






  










 
  template<typename _InputIterator, typename _Function>
    _Function
    for_each(_InputIterator __first, _InputIterator __last, _Function __f)
    {
      
      
      ;
      for (; __first != __last; ++__first)
	__f(*__first);
      return (__f);
    }

  







 
  template<typename _InputIterator, typename _Tp>
    inline _InputIterator
    find(_InputIterator __first, _InputIterator __last,
	 const _Tp& __val)
    {
      
      
      
      ;
      return std::__find(__first, __last, __val,
		         std::__iterator_category(__first));
    }

  








 
  template<typename _InputIterator, typename _Predicate>
    inline _InputIterator
    find_if(_InputIterator __first, _InputIterator __last,
	    _Predicate __pred)
    {
      
      
      
      ;
      return std::__find_if(__first, __last, __pred,
			    std::__iterator_category(__first));
    }

  













 
  template<typename _InputIterator, typename _ForwardIterator>
    _InputIterator
    find_first_of(_InputIterator __first1, _InputIterator __last1,
		  _ForwardIterator __first2, _ForwardIterator __last2)
    {
      
      
      
      
      ;
      ;

      for (; __first1 != __last1; ++__first1)
	for (_ForwardIterator __iter = __first2; __iter != __last2; ++__iter)
	  if (*__first1 == *__iter)
	    return __first1;
      return __last1;
    }

  
















 
  template<typename _InputIterator, typename _ForwardIterator,
	   typename _BinaryPredicate>
    _InputIterator
    find_first_of(_InputIterator __first1, _InputIterator __last1,
		  _ForwardIterator __first2, _ForwardIterator __last2,
		  _BinaryPredicate __comp)
    {
      
      
      
      
      ;
      ;

      for (; __first1 != __last1; ++__first1)
	for (_ForwardIterator __iter = __first2; __iter != __last2; ++__iter)
	  if (__comp(*__first1, *__iter))
	    return __first1;
      return __last1;
    }

  







 
  template<typename _ForwardIterator>
    _ForwardIterator
    adjacent_find(_ForwardIterator __first, _ForwardIterator __last)
    {
      
      
      
      ;
      if (__first == __last)
	return __last;
      _ForwardIterator __next = __first;
      while(++__next != __last)
	{
	  if (*__first == *__next)
	    return __first;
	  __first = __next;
	}
      return __last;
    }

  









 
  template<typename _ForwardIterator, typename _BinaryPredicate>
    _ForwardIterator
    adjacent_find(_ForwardIterator __first, _ForwardIterator __last,
		  _BinaryPredicate __binary_pred)
    {
      
      
      
      ;
      if (__first == __last)
	return __last;
      _ForwardIterator __next = __first;
      while(++__next != __last)
	{
	  if (__binary_pred(*__first, *__next))
	    return __first;
	  __first = __next;
	}
      return __last;
    }

  







 
  template<typename _InputIterator, typename _Tp>
    typename iterator_traits<_InputIterator>::difference_type
    count(_InputIterator __first, _InputIterator __last, const _Tp& __value)
    {
      
      
      
      ;
      typename iterator_traits<_InputIterator>::difference_type __n = 0;
      for (; __first != __last; ++__first)
	if (*__first == __value)
	  ++__n;
      return __n;
    }

  







 
  template<typename _InputIterator, typename _Predicate>
    typename iterator_traits<_InputIterator>::difference_type
    count_if(_InputIterator __first, _InputIterator __last, _Predicate __pred)
    {
      
      
      
      ;
      typename iterator_traits<_InputIterator>::difference_type __n = 0;
      for (; __first != __last; ++__first)
	if (__pred(*__first))
	  ++__n;
      return __n;
    }

  






















 
  template<typename _ForwardIterator1, typename _ForwardIterator2>
    _ForwardIterator1
    search(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
	   _ForwardIterator2 __first2, _ForwardIterator2 __last2)
    {
      
      
      
      
      ;
      ;

      
      if (__first1 == __last1 || __first2 == __last2)
	return __first1;

      
      _ForwardIterator2 __p1(__first2);
      if (++__p1 == __last2)
	return std::find(__first1, __last1, *__first2);

      
      _ForwardIterator2 __p;
      _ForwardIterator1 __current = __first1;

      for (;;)
	{
	  __first1 = std::find(__first1, __last1, *__first2);
	  if (__first1 == __last1)
	    return __last1;

	  __p = __p1;
	  __current = __first1;
	  if (++__current == __last1)
	    return __last1;

	  while (*__current == *__p)
	    {
	      if (++__p == __last2)
		return __first1;
	      if (++__current == __last1)
		return __last1;
	    }
	  ++__first1;
	}
      return __first1;
    }

  



















 
  template<typename _ForwardIterator1, typename _ForwardIterator2,
	   typename _BinaryPredicate>
    _ForwardIterator1
    search(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
	   _ForwardIterator2 __first2, _ForwardIterator2 __last2,
	   _BinaryPredicate  __predicate)
    {
      
      
      
      
      ;
      ;

      
      if (__first1 == __last1 || __first2 == __last2)
	return __first1;

      
      _ForwardIterator2 __p1(__first2);
      if (++__p1 == __last2)
	{
	  while (__first1 != __last1
		 && !bool(__predicate(*__first1, *__first2)))
	    ++__first1;
	  return __first1;
	}

      
      _ForwardIterator2 __p;
      _ForwardIterator1 __current = __first1;

      for (;;)
	{
	  while (__first1 != __last1
		 && !bool(__predicate(*__first1, *__first2)))
	    ++__first1;
	  if (__first1 == __last1)
	    return __last1;

	  __p = __p1;
	  __current = __first1;
	  if (++__current == __last1)
	    return __last1;

	  while (__predicate(*__current, *__p))
	    {
	      if (++__p == __last2)
		return __first1;
	      if (++__current == __last1)
		return __last1;
	    }
	  ++__first1;
	}
      return __first1;
    }


  












 
  template<typename _ForwardIterator, typename _Integer, typename _Tp>
    _ForwardIterator
    search_n(_ForwardIterator __first, _ForwardIterator __last,
	     _Integer __count, const _Tp& __val)
    {
      
      
      
      ;

      if (__count <= 0)
	return __first;
      if (__count == 1)
	return std::find(__first, __last, __val);
      return std::__search_n(__first, __last, __count, __val,
			     std::__iterator_category(__first));
    }


  














 
  template<typename _ForwardIterator, typename _Integer, typename _Tp,
           typename _BinaryPredicate>
    _ForwardIterator
    search_n(_ForwardIterator __first, _ForwardIterator __last,
	     _Integer __count, const _Tp& __val,
	     _BinaryPredicate __binary_pred)
    {
      
      
      
      ;

      if (__count <= 0)
	return __first;
      if (__count == 1)
	{
	  while (__first != __last && !bool(__binary_pred(*__first, __val)))
	    ++__first;
	  return __first;
	}
      return std::__search_n(__first, __last, __count, __val, __binary_pred,
			     std::__iterator_category(__first));
    }


  














 
  template<typename _InputIterator, typename _OutputIterator,
	   typename _UnaryOperation>
    _OutputIterator
    transform(_InputIterator __first, _InputIterator __last,
	      _OutputIterator __result, _UnaryOperation __unary_op)
    {
      
      
      
      ;

      for (; __first != __last; ++__first, ++__result)
	*__result = __unary_op(*__first);
      return __result;
    }

  
















 
  template<typename _InputIterator1, typename _InputIterator2,
	   typename _OutputIterator, typename _BinaryOperation>
    _OutputIterator
    transform(_InputIterator1 __first1, _InputIterator1 __last1,
	      _InputIterator2 __first2, _OutputIterator __result,
	      _BinaryOperation __binary_op)
    {
      
      
      
      
      ;

      for (; __first1 != __last1; ++__first1, ++__first2, ++__result)
	*__result = __binary_op(*__first1, *__first2);
      return __result;
    }

  











 
  template<typename _ForwardIterator, typename _Tp>
    void
    replace(_ForwardIterator __first, _ForwardIterator __last,
	    const _Tp& __old_value, const _Tp& __new_value)
    {
      
      
      
      
      ;

      for (; __first != __last; ++__first)
	if (*__first == __old_value)
	  *__first = __new_value;
    }

  











 
  template<typename _ForwardIterator, typename _Predicate, typename _Tp>
    void
    replace_if(_ForwardIterator __first, _ForwardIterator __last,
	       _Predicate __pred, const _Tp& __new_value)
    {
      
      
      
      
      ;

      for (; __first != __last; ++__first)
	if (__pred(*__first))
	  *__first = __new_value;
    }

  











 
  template<typename _ForwardIterator, typename _Generator>
    void
    generate(_ForwardIterator __first, _ForwardIterator __last,
	     _Generator __gen)
    {
      
      
      
      ;

      for (; __first != __last; ++__first)
	*__first = __gen();
    }

  














 
  template<typename _OutputIterator, typename _Size, typename _Generator>
    _OutputIterator
    generate_n(_OutputIterator __first, _Size __n, _Generator __gen)
    {
      
      

      for (__decltype(__n + 0) __niter = __n;
	   __niter > 0; --__niter, ++__first)
	*__first = __gen();
      return __first;
    }


  



















 
  template<typename _InputIterator, typename _OutputIterator>
    inline _OutputIterator
    unique_copy(_InputIterator __first, _InputIterator __last,
		_OutputIterator __result)
    {
      
      
      
      
      ;

      if (__first == __last)
	return __result;
      return std::__unique_copy(__first, __last, __result,
				std::__iterator_category(__first),
				std::__iterator_category(__result));
    }

  

















 
  template<typename _InputIterator, typename _OutputIterator,
	   typename _BinaryPredicate>
    inline _OutputIterator
    unique_copy(_InputIterator __first, _InputIterator __last,
		_OutputIterator __result,
		_BinaryPredicate __binary_pred)
    {
      
      
      
      ;

      if (__first == __last)
	return __result;
      return std::__unique_copy(__first, __last, __result, __binary_pred,
				std::__iterator_category(__first),
				std::__iterator_category(__result));
    }


  









 
  template<typename _RandomAccessIterator>
    inline void
    random_shuffle(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
      
      
      ;

      if (__first != __last)
	for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
	  std::iter_swap(__i, __first + (std::rand() % ((__i - __first) + 1)));
    }

  












 
  template<typename _RandomAccessIterator, typename _RandomNumberGenerator>
    void
    random_shuffle(_RandomAccessIterator __first, _RandomAccessIterator __last,
		   _RandomNumberGenerator& __rand)
    {
      
      
      ;

      if (__first == __last)
	return;
      for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
	std::iter_swap(__i, __first + __rand((__i - __first) + 1));
    }


  













 
  template<typename _ForwardIterator, typename _Predicate>
    inline _ForwardIterator
    partition(_ForwardIterator __first, _ForwardIterator __last,
	      _Predicate   __pred)
    {
      
      
      
      ;

      return std::__partition(__first, __last, __pred,
			      std::__iterator_category(__first));
    }



  














 
  template<typename _RandomAccessIterator>
    inline void
    partial_sort(_RandomAccessIterator __first,
		 _RandomAccessIterator __middle,
		 _RandomAccessIterator __last)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	_ValueType;

      
      
      
      ;
      ;

      std::__heap_select(__first, __middle, __last);
      std::sort_heap(__first, __middle);
    }

  

















 
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    partial_sort(_RandomAccessIterator __first,
		 _RandomAccessIterator __middle,
		 _RandomAccessIterator __last,
		 _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	_ValueType;

      
      
      
      ;
      ;

      std::__heap_select(__first, __middle, __last, __comp);
      std::sort_heap(__first, __middle, __comp);
    }

  














 
  template<typename _RandomAccessIterator>
    inline void
    nth_element(_RandomAccessIterator __first, _RandomAccessIterator __nth,
		_RandomAccessIterator __last)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	_ValueType;

      
      
      
      ;
      ;

      if (__first == __last || __nth == __last)
	return;

      std::__introselect(__first, __nth, __last,
			 std::__lg(__last - __first) * 2);
    }

  















 
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    nth_element(_RandomAccessIterator __first, _RandomAccessIterator __nth,
		_RandomAccessIterator __last, _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	_ValueType;

      
      
      
      ;
      ;

      if (__first == __last || __nth == __last)
	return;

      std::__introselect(__first, __nth, __last,
			 std::__lg(__last - __first) * 2, __comp);
    }


  












 
  template<typename _RandomAccessIterator>
    inline void
    sort(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	_ValueType;

      
      
      
      ;

      if (__first != __last)
	{
	  std::__introsort_loop(__first, __last,
				std::__lg(__last - __first) * 2);
	  std::__final_insertion_sort(__first, __last);
	}
    }

  













 
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    sort(_RandomAccessIterator __first, _RandomAccessIterator __last,
	 _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	_ValueType;

      
      
      
      ;

      if (__first != __last)
	{
	  std::__introsort_loop(__first, __last,
				std::__lg(__last - __first) * 2, __comp);
	  std::__final_insertion_sort(__first, __last, __comp);
	}
    }

  
















 
  template<typename _InputIterator1, typename _InputIterator2,
	   typename _OutputIterator>
    _OutputIterator
    merge(_InputIterator1 __first1, _InputIterator1 __last1,
	  _InputIterator2 __first2, _InputIterator2 __last2,
	  _OutputIterator __result)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
	_ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
	_ValueType2;

      
      
      
      
      
      	
      ;
      ;

      while (__first1 != __last1 && __first2 != __last2)
	{
	  if (*__first2 < *__first1)
	    {
	      *__result = *__first2;
	      ++__first2;
	    }
	  else
	    {
	      *__result = *__first1;
	      ++__first1;
	    }
	  ++__result;
	}
      return std::copy(__first2, __last2, std::copy(__first1, __last1,
						    __result));
    }

  




















 
  template<typename _InputIterator1, typename _InputIterator2,
	   typename _OutputIterator, typename _Compare>
    _OutputIterator
    merge(_InputIterator1 __first1, _InputIterator1 __last1,
	  _InputIterator2 __first2, _InputIterator2 __last2,
	  _OutputIterator __result, _Compare __comp)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
	_ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
	_ValueType2;

      
      
      
      
      
      
      ;
      ;

      while (__first1 != __last1 && __first2 != __last2)
	{
	  if (__comp(*__first2, *__first1))
	    {
	      *__result = *__first2;
	      ++__first2;
	    }
	  else
	    {
	      *__result = *__first1;
	      ++__first1;
	    }
	  ++__result;
	}
      return std::copy(__first2, __last2, std::copy(__first1, __last1,
						    __result));
    }


  















 
  template<typename _RandomAccessIterator>
    inline void
    stable_sort(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	_ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
	_DistanceType;

      
      
      
      ;

      _Temporary_buffer<_RandomAccessIterator, _ValueType> __buf(__first,
								 __last);
      if (__buf.begin() == 0)
	std::__inplace_stable_sort(__first, __last);
      else
	std::__stable_sort_adaptive(__first, __last, __buf.begin(),
				    _DistanceType(__buf.size()));
    }

  
















 
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    stable_sort(_RandomAccessIterator __first, _RandomAccessIterator __last,
		_Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
	_ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
	_DistanceType;

      
      
      
      ;

      _Temporary_buffer<_RandomAccessIterator, _ValueType> __buf(__first,
								 __last);
      if (__buf.begin() == 0)
	std::__inplace_stable_sort(__first, __last, __comp);
      else
	std::__stable_sort_adaptive(__first, __last, __buf.begin(),
				    _DistanceType(__buf.size()), __comp);
    }


  
















 
  template<typename _InputIterator1, typename _InputIterator2,
	   typename _OutputIterator>
    _OutputIterator
    set_union(_InputIterator1 __first1, _InputIterator1 __last1,
	      _InputIterator2 __first2, _InputIterator2 __last2,
	      _OutputIterator __result)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
	_ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
	_ValueType2;

      
      
      
      
      
      
      
      ;
      ;

      while (__first1 != __last1 && __first2 != __last2)
	{
	  if (*__first1 < *__first2)
	    {
	      *__result = *__first1;
	      ++__first1;
	    }
	  else if (*__first2 < *__first1)
	    {
	      *__result = *__first2;
	      ++__first2;
	    }
	  else
	    {
	      *__result = *__first1;
	      ++__first1;
	      ++__first2;
	    }
	  ++__result;
	}
      return std::copy(__first2, __last2, std::copy(__first1, __last1,
						    __result));
    }

  

















 
  template<typename _InputIterator1, typename _InputIterator2,
	   typename _OutputIterator, typename _Compare>
    _OutputIterator
    set_union(_InputIterator1 __first1, _InputIterator1 __last1,
	      _InputIterator2 __first2, _InputIterator2 __last2,
	      _OutputIterator __result, _Compare __comp)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
	_ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
	_ValueType2;

      
      
      
      
      
      
      
      ;
      ;

      while (__first1 != __last1 && __first2 != __last2)
	{
	  if (__comp(*__first1, *__first2))
	    {
	      *__result = *__first1;
	      ++__first1;
	    }
	  else if (__comp(*__first2, *__first1))
	    {
	      *__result = *__first2;
	      ++__first2;
	    }
	  else
	    {
	      *__result = *__first1;
	      ++__first1;
	      ++__first2;
	    }
	  ++__result;
	}
      return std::copy(__first2, __last2, std::copy(__first1, __last1,
						    __result));
    }

  















 
  template<typename _InputIterator1, typename _InputIterator2,
	   typename _OutputIterator>
    _OutputIterator
    set_intersection(_InputIterator1 __first1, _InputIterator1 __last1,
		     _InputIterator2 __first2, _InputIterator2 __last2,
		     _OutputIterator __result)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
	_ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
	_ValueType2;

      
      
      
      
      
      
      ;
      ;

      while (__first1 != __last1 && __first2 != __last2)
	if (*__first1 < *__first2)
	  ++__first1;
	else if (*__first2 < *__first1)
	  ++__first2;
	else
	  {
	    *__result = *__first1;
	    ++__first1;
	    ++__first2;
	    ++__result;
	  }
      return __result;
    }

  


















 
  template<typename _InputIterator1, typename _InputIterator2,
	   typename _OutputIterator, typename _Compare>
    _OutputIterator
    set_intersection(_InputIterator1 __first1, _InputIterator1 __last1,
		     _InputIterator2 __first2, _InputIterator2 __last2,
		     _OutputIterator __result, _Compare __comp)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
	_ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
	_ValueType2;

      
      
      
      
      
      
      ;
      ;

      while (__first1 != __last1 && __first2 != __last2)
	if (__comp(*__first1, *__first2))
	  ++__first1;
	else if (__comp(*__first2, *__first1))
	  ++__first2;
	else
	  {
	    *__result = *__first1;
	    ++__first1;
	    ++__first2;
	    ++__result;
	  }
      return __result;
    }

  

















 
  template<typename _InputIterator1, typename _InputIterator2,
	   typename _OutputIterator>
    _OutputIterator
    set_difference(_InputIterator1 __first1, _InputIterator1 __last1,
		   _InputIterator2 __first2, _InputIterator2 __last2,
		   _OutputIterator __result)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
	_ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
	_ValueType2;

      
      
      
      
      
      	
      ;
      ;

      while (__first1 != __last1 && __first2 != __last2)
	if (*__first1 < *__first2)
	  {
	    *__result = *__first1;
	    ++__first1;
	    ++__result;
	  }
	else if (*__first2 < *__first1)
	  ++__first2;
	else
	  {
	    ++__first1;
	    ++__first2;
	  }
      return std::copy(__first1, __last1, __result);
    }

  




















 
  template<typename _InputIterator1, typename _InputIterator2,
	   typename _OutputIterator, typename _Compare>
    _OutputIterator
    set_difference(_InputIterator1 __first1, _InputIterator1 __last1,
		   _InputIterator2 __first2, _InputIterator2 __last2,
		   _OutputIterator __result, _Compare __comp)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
	_ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
	_ValueType2;

      
      
      
      
      
      
      ;
      ;

      while (__first1 != __last1 && __first2 != __last2)
	if (__comp(*__first1, *__first2))
	  {
	    *__result = *__first1;
	    ++__first1;
	    ++__result;
	  }
	else if (__comp(*__first2, *__first1))
	  ++__first2;
	else
	  {
	    ++__first1;
	    ++__first2;
	  }
      return std::copy(__first1, __last1, __result);
    }

  















 
  template<typename _InputIterator1, typename _InputIterator2,
	   typename _OutputIterator>
    _OutputIterator
    set_symmetric_difference(_InputIterator1 __first1, _InputIterator1 __last1,
			     _InputIterator2 __first2, _InputIterator2 __last2,
			     _OutputIterator __result)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
	_ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
	_ValueType2;

      
      
      
      
      
      
      	
      ;
      ;

      while (__first1 != __last1 && __first2 != __last2)
	if (*__first1 < *__first2)
	  {
	    *__result = *__first1;
	    ++__first1;
	    ++__result;
	  }
	else if (*__first2 < *__first1)
	  {
	    *__result = *__first2;
	    ++__first2;
	    ++__result;
	  }
	else
	  {
	    ++__first1;
	    ++__first2;
	  }
      return std::copy(__first2, __last2, std::copy(__first1,
						    __last1, __result));
    }

  


















 
  template<typename _InputIterator1, typename _InputIterator2,
	   typename _OutputIterator, typename _Compare>
    _OutputIterator
    set_symmetric_difference(_InputIterator1 __first1, _InputIterator1 __last1,
			     _InputIterator2 __first2, _InputIterator2 __last2,
			     _OutputIterator __result,
			     _Compare __comp)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
	_ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
	_ValueType2;

      
      
      
      
      
      
      
      ;
      ;

      while (__first1 != __last1 && __first2 != __last2)
	if (__comp(*__first1, *__first2))
	  {
	    *__result = *__first1;
	    ++__first1;
	    ++__result;
	  }
	else if (__comp(*__first2, *__first1))
	  {
	    *__result = *__first2;
	    ++__first2;
	    ++__result;
	  }
	else
	  {
	    ++__first1;
	    ++__first2;
	  }
      return std::copy(__first2, __last2, 
		       std::copy(__first1, __last1, __result));
    }


  





 
  template<typename _ForwardIterator>
    _ForwardIterator
    min_element(_ForwardIterator __first, _ForwardIterator __last)
    {
      
      
      
      ;

      if (__first == __last)
	return __first;
      _ForwardIterator __result = __first;
      while (++__first != __last)
	if (*__first < *__result)
	  __result = __first;
      return __result;
    }

  







 
  template<typename _ForwardIterator, typename _Compare>
    _ForwardIterator
    min_element(_ForwardIterator __first, _ForwardIterator __last,
		_Compare __comp)
    {
      
      
      
      ;

      if (__first == __last)
	return __first;
      _ForwardIterator __result = __first;
      while (++__first != __last)
	if (__comp(*__first, *__result))
	  __result = __first;
      return __result;
    }

  





 
  template<typename _ForwardIterator>
    _ForwardIterator
    max_element(_ForwardIterator __first, _ForwardIterator __last)
    {
      
      
      
      ;

      if (__first == __last)
	return __first;
      _ForwardIterator __result = __first;
      while (++__first != __last)
	if (*__result < *__first)
	  __result = __first;
      return __result;
    }

  







 
  template<typename _ForwardIterator, typename _Compare>
    _ForwardIterator
    max_element(_ForwardIterator __first, _ForwardIterator __last,
		_Compare __comp)
    {
      
      
      
      ;

      if (__first == __last) return __first;
      _ForwardIterator __result = __first;
      while (++__first != __last)
	if (__comp(*__result, *__first))
	  __result = __first;
      return __result;
    }


} 




namespace olb {

namespace util {

inline bool intersect (
  int x0, int x1, int y0, int y1,
  int x0_, int x1_, int y0_, int y1_,
  int& newX0, int& newX1, int& newY0, int& newY1 )
{
  newX0 = std::max(x0,x0_);
  newY0 = std::max(y0,y0_);

  newX1 = std::min(x1,x1_);
  newY1 = std::min(y1,y1_);

  return newX1>=newX0 && newY1>=newY0;
}

inline bool intersect (
  int x0, int x1, int y0, int y1, int z0, int z1,
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  int& newX0, int& newX1, int& newY0, int& newY1, int& newZ0, int& newZ1 )
{
  newX0 = std::max(x0,x0_);
  newY0 = std::max(y0,y0_);
  newZ0 = std::max(z0,z0_);

  newX1 = std::min(x1,x1_);
  newY1 = std::min(y1,y1_);
  newZ1 = std::min(z1,z1_);

  return newX1>=newX0 && newY1>=newY0 && newZ1>=newZ0;
}

inline bool contained(int x, int y,
                      int x0, int x1, int y0, int y1)
{
  return x>=x0 && x<=x1 &&
         y>=y0 && y<=y1;
}

inline bool contained(int x, int y, int z,
                      int x0, int x1, int y0, int y1, int z0, int z1)
{
  return x>=x0 && x<=x1 &&
         y>=y0 && y<=y1 &&
         z>=z0 && z<=z1;
}


template<typename T>
T sqr(T arg) {
  return arg*arg;
}


template<typename T, int d>
T normSqr(const T u[d]) {
  T uSqr = T();
  for (int iD=0; iD<d; ++iD) {
    uSqr += u[iD]*u[iD];
  }
  return uSqr;
}

template<typename T, int d>
T scalarProduct(const T u1[d], const T u2[d]) {
  T prod = T();
  for (int iD=0; iD<d; ++iD) {
    prod += u1[iD]*u2[iD];
  }
  return prod;
}


template <typename Descriptor> struct TensorVal {
  static const int n =
    (Descriptor::d*(Descriptor::d+1))/2; 
};


template <typename Descriptor> inline int opposite(int iPop) {
  if (iPop==0) return 0;
  if (iPop<=Descriptor::q/2) return iPop + Descriptor::q/2;
  return iPop - Descriptor::q/2;
}

template <typename Descriptor, int index, int value>
class SubIndex {
private:
  SubIndex() {
    for (int iVel=0; iVel<Descriptor::q; ++iVel) {
      if (Descriptor::c[iVel][index]==value) {
        indices.push_back(iVel);
      }
    }
  }

  std::vector<int> indices;

  template <typename Descriptor_, int index_, int value_>
  friend std::vector<int> const& subIndex();
};

template <typename Descriptor, int index, int value>
std::vector<int> const& subIndex() {
  static SubIndex<Descriptor, index, value> subIndexSingleton;
  return subIndexSingleton.indices;
}

template <typename Descriptor>
int findVelocity(const int v[Descriptor::d]) {
  for (int iPop=0; iPop<Descriptor::q; ++iPop) {
    bool fit = true;
    for (int iD=0; iD<Descriptor::d; ++iD) {
      if (Descriptor::c[iPop][iD] != v[iD]) {
        fit = false;
        break;
      }
    }
    if (fit) return iPop;
  }
  return Descriptor::q;
}





 
template <typename Descriptor, int direction, int orientation>
class SubIndexOutgoing {
private:
  SubIndexOutgoing() 
  {
    indices = util::subIndex<Descriptor,direction,orientation>();

    for (unsigned iPop = 0; iPop < indices.size(); ++iPop) {
      indices[iPop] = util::opposite<Descriptor>(indices[iPop]);
    }

  }

  std::vector<int> indices;

  template <typename Descriptor_, int direction_, int orientation_>
  friend std::vector<int> const& subIndexOutgoing();
};

template <typename Descriptor, int direction, int orientation>
std::vector<int> const& subIndexOutgoing() {
  static SubIndexOutgoing<Descriptor, direction, orientation> subIndexOutgoingSingleton;
  return subIndexOutgoingSingleton.indices;
}


template <typename Descriptor>
std::vector<int> remainingIndexes(const std::vector<int> &indices)
{
  std::vector<int> remaining;
  for (int iPop = 0; iPop < Descriptor::q; ++iPop)
  {
    bool found = false;
    for (unsigned jPop = 0; jPop < indices.size(); ++jPop)
    {
      if (indices[jPop] == iPop)
      {
        found = true;
      }
    }
    if (!found)
    {
      remaining.push_back(iPop);
    }
  }
  return remaining;
}


template <typename Descriptor, int xNormal, int yNormal>
class SubIndexOutgoingCorner2D {
private:
  SubIndexOutgoingCorner2D()
  {
    typedef Descriptor L;

    int vect[L::d] = {xNormal, yNormal};
    std::vector<int> knownIndexes;
    knownIndexes.push_back(util::findVelocity<L>(vect));
    vect[0] = xNormal;
    vect[1] = 0;
    knownIndexes.push_back(util::findVelocity<L>(vect));
    vect[0] = 0;
    vect[1] = yNormal;
    knownIndexes.push_back(util::findVelocity<L>(vect));
    vect[0] = 0;
    vect[1] = 0;
    knownIndexes.push_back(util::findVelocity<L>(vect));
    indices = util::remainingIndexes<L>(knownIndexes);
  }

  std::vector<int> indices;

  template <typename Descriptor_, int direction_, int orientation_>
  friend std::vector<int> const& subIndexOutgoingCorner2D();
};

template <typename Descriptor, int xNormal, int yNormal>
std::vector<int> const& subIndexOutgoingCorner2D() {
  static SubIndexOutgoingCorner2D<Descriptor, xNormal, yNormal> subIndexOutgoingCorner2DSingleton;
  return subIndexOutgoingCorner2DSingleton.indices;
}

namespace tensorIndices2D {
enum { xx=0, xy=1, yy=2 };
}

namespace tensorIndices3D {
enum { xx=0, xy=1, xz=2, yy=3, yz=4, zz=5 };
}

}  

}  






















 



 























 
























 



 



namespace olb {


struct BlockCoordinates2D {
  BlockCoordinates2D() : x0(), x1(), y0(), y1() { }
  BlockCoordinates2D(int x0_, int x1_, int y0_, int y1_)
    : x0(x0_), x1(x1_), y0(y0_), y1(y1_)
  { }
  BlockCoordinates2D shift(int deltaX, int deltaY) const {
    return BlockCoordinates2D(x0+deltaX, x1+deltaX, y0+deltaY, y1+deltaY);
  }
  int x0, x1, y0, y1;
};

namespace util {

inline bool intersect (
  BlockCoordinates2D const& block1,
  BlockCoordinates2D const& block2,
  BlockCoordinates2D& inters )
{
  return intersect(block1.x0, block1.x1, block1.y0, block1.y1,
                   block2.x0, block2.x1, block2.y0, block2.y1,
                   inters.x0, inters.x1, inters.y0, inters.y1);
}

inline bool contained(int iX, int iY, BlockCoordinates2D const& block) {
  return contained(iX,iY, block.x0, block.x1, block.y0, block.y1);
}

}

class BlockParameters2D {
public:
  BlockParameters2D(int x0_, int x1_, int y0_, int y1_, int envelopeWidth_, int procId_,
                    bool leftX, bool rightX, bool leftY, bool rightY);
  int getEnvelopeWidth()                             const { return envelopeWidth; }
  int getProcId()                                    const { return procId; }
  BlockCoordinates2D const& getBulk()                const { return bulk; }
  BlockCoordinates2D const& getEnvelope()            const { return envelope; }
  BlockCoordinates2D const& getNonPeriodicEnvelope() const { return nonPeriodicEnvelope; }
  int getBulkLx() const { return bulk.x1-bulk.x0+1; }
  int getBulkLy() const { return bulk.y1-bulk.y0+1; }
  int getEnvelopeLx() const { return envelope.x1-envelope.x0+1; }
  int getEnvelopeLy() const { return envelope.y1-envelope.y0+1; }
  int toLocalX(int iX) const { return iX-envelope.x0; }
  int toLocalY(int iY) const { return iY-envelope.y0; }
  BlockCoordinates2D toLocal(BlockCoordinates2D const& coord) const {
    return BlockCoordinates2D(coord.shift(-envelope.x0, -envelope.y0));
  }
private:
  int envelopeWidth, procId;
  BlockCoordinates2D bulk, envelope, nonPeriodicEnvelope;
};

class Overlap2D {
public:
  Overlap2D(int originalId_, int overlapId_, BlockCoordinates2D const& intersection_)
    : originalId(originalId_), overlapId(overlapId_),
      originalRegion(intersection_),
      overlapRegion(intersection_)
  { }
  Overlap2D(int originalId_, int overlapId_,
            BlockCoordinates2D const& originalRegion_,
            int shiftX, int shiftY)
    : originalId(originalId_), overlapId(overlapId_),
      originalRegion(originalRegion_),
      overlapRegion(originalRegion.shift(-shiftX, -shiftY))
  { }
  int getOriginalId() const { return originalId; }
  int getOverlapId()  const { return overlapId; }
  BlockCoordinates2D const& getOriginalCoordinates() const { return originalRegion; }
  BlockCoordinates2D const& getOverlapCoordinates() const  { return overlapRegion; }
  int getShiftX() const { return originalRegion.x0 - overlapRegion.x0; }
  int getShiftY() const { return originalRegion.y0 - overlapRegion.y0; }
private:
  int originalId, overlapId;
  BlockCoordinates2D originalRegion, overlapRegion;
};

class MultiDataDistribution2D {
public:
  MultiDataDistribution2D(int nx_, int ny_);
  MultiDataDistribution2D& operator=(MultiDataDistribution2D const& rhs);
  int getNx() const { return nx; }
  int getNy() const { return ny; }
  int getNumBlocks()           const { return blocks.size(); }
  int getNumNormalOverlaps()   const { return normalOverlaps.size(); }
  int getNumPeriodicOverlaps() const { return periodicOverlaps.size(); }
  void addBlock(int x0, int x1, int y0, int y1, int envelopeWidth, int procId=0);
  BlockParameters2D const& getBlockParameters(int whichBlock) const;
  Overlap2D   const& getNormalOverlap(int whichOverlap) const;
  Overlap2D const& getPeriodicOverlap(int whichOverlap) const;
  int locate(int iX, int iY, int guess=0) const;
  int locateInEnvelopes(int iX, int iY, std::vector<int>& foundId, int guess=0) const;
  size_t getNumAllocatedBulkCells() const;
  bool getNextChunkX(int iX, int iY, int& nextLattice, int& nextChunkSize) const;
  bool getNextChunkY(int iX, int iY, int& nextLattice, int& nextChunkSize) const;
private:
  void computeNormalOverlaps(BlockParameters2D const& newBlock);
  void computePeriodicOverlaps();
private:
  int nx, ny;
  std::vector<BlockParameters2D> blocks;
  std::vector<Overlap2D> normalOverlaps;
  std::vector<Overlap2D> periodicOverlaps;
  std::vector<std::vector<int> > neighbors;
};


class RelevantIndexes2D {
public:
  
  RelevantIndexes2D(int numBlocks, int numNormalOverlaps, int numPeriodicOverlaps, int nx, int ny);
  
  RelevantIndexes2D(MultiDataDistribution2D const& dataDistribution, int whichRank);
  
  std::vector<int> const& getBlocks()                const { return myBlocks; }
  
  std::vector<int> const& getNearbyBlocks()          const { return nearbyBlocks; }
  
  std::vector<int> const& getNormalOverlaps()        const { return normalOverlaps; }
  
  std::vector<int> const& getPeriodicOverlaps()      const { return periodicOverlaps; }
  
  std::vector<int> const& getPeriodicOverlapWithMe() const { return periodicOverlapWithMe; }
  
  BlockCoordinates2D const& getBoundingBox()         const { return boundingBox; }
private:
  void listAllIndexes(int numBlocks, int numNormalOverlaps, int numPeriodicOverlaps, int nx, int ny);
  void computeRelevantIndexesInParallel(MultiDataDistribution2D const& dataDistribution, int whichRank);
private:
  std::vector<int> myBlocks;
  std::vector<int> nearbyBlocks;
  std::vector<int> normalOverlaps;
  std::vector<int> periodicOverlaps;
  std::vector<int> periodicOverlapWithMe;
  BlockCoordinates2D boundingBox;
};

}  























 



namespace olb {

namespace multiPhysics {

typedef enum {
  UndefinedId           = 0,

  IntScalarFieldId      = 10000,
  FloatScalarFieldId    = 10001,
  DoubleScalarFieldId   = 10002,

  IntTensorField2Id     = 20020,
  FloatTensorField2Id   = 20021,
  DoubleTensorField2Id  = 20022,

  IntTensorField3Id     = 20030,
  FloatTensorField3Id   = 20031,
  DoubleTensorField3Id  = 20032,

  IntTensorField4Id     = 20040,
  FloatTensorField4Id   = 20041,
  DoubleTensorField4Id  = 20042,

  IntTensorField6Id     = 20060,
  FloatTensorField6Id   = 20061,
  DoubleTensorField6Id  = 20062,

  IntTensorField9Id     = 20090,
  FloatTensorField9Id   = 20091,
  DoubleTensorField9Id  = 20092,

  IntD2Q5BlockId        = 32040,
  FloatD2Q5BlockId      = 32041,
  DoubleD2Q5BlockId     = 32042,

  IntD2Q9BlockId        = 32090,
  FloatD2Q9BlockId      = 32091,
  DoubleD2Q9BlockId     = 32092,

  IntD3Q7BlockId        = 33070,
  FloatD3Q7BlockId      = 33071,
  DoubleD3Q7BlockId     = 33072,

  IntD3Q13BlockId       = 33130,
  FloatD3Q13BlockId     = 33131,
  DoubleD3Q13BlockId    = 33132,

  IntD3Q15BlockId       = 33150,
  FloatD3Q15BlockId     = 33151,
  DoubleD3Q15BlockId    = 33152,

  IntD3Q19BlockId       = 33190,
  FloatD3Q19BlockId     = 33191,
  DoubleD3Q19BlockId    = 33192,

  IntD3Q27BlockId       = 33270,
  FloatD3Q27BlockId     = 33271,
  DoubleD3Q27BlockId    = 33272,

  IntD2Q5WithForceBlockId    = 42040,
  FloatD2Q5WithForceBlockId  = 42041,
  DoubleD2Q5WithForceBlockId = 42042,

  IntD2Q9WithForceBlockId    = 42090,
  FloatD2Q9WithForceBlockId  = 42091,
  DoubleD2Q9WithForceBlockId = 42092,

  IntD3Q7WithForceBlockId    = 43070,
  FloatD3Q7WithForceBlockId  = 43071,
  DoubleD3Q7WithForceBlockId = 43072,

  IntD3Q13WithForceBlockId    = 43130,
  FloatD3Q13WithForceBlockId  = 43131,
  DoubleD3Q13WithForceBlockId = 43132,

  IntD3Q15WithForceBlockId    = 43150,
  FloatD3Q15WithForceBlockId  = 43151,
  DoubleD3Q15WithForceBlockId = 43152,

  IntD3Q19WithForceBlockId    = 43190,
  FloatD3Q19WithForceBlockId  = 43191,
  DoubleD3Q19WithForceBlockId = 43192,

  IntD3Q27WithForceBlockId    = 43270,
  FloatD3Q27WithForceBlockId  = 43271,
  DoubleD3Q27WithForceBlockId = 43272
}
MultiPhysicsId;

template<typename T>
MultiPhysicsId getMultiPhysicsScalarId() {
  return UndefinedId;
}

template<typename T, int n>
MultiPhysicsId getMultiPhysicsTensorId() {
  return UndefinedId;
}

template<typename T, template<typename U> class Lattice>
MultiPhysicsId getMultiPhysicsBlockId() {
  return UndefinedId;
}

} 

} 


namespace olb {

struct SpatiallyExtendedObject2D {
  virtual ~SpatiallyExtendedObject2D() { }
  virtual MultiDataDistribution2D getDataDistribution() const =0;
  virtual SpatiallyExtendedObject2D* getComponent(int iBlock) =0;
  virtual SpatiallyExtendedObject2D const* getComponent(int iBlock) const =0;
  virtual multiPhysics::MultiPhysicsId getMultiPhysicsId() const =0;
};

} 






















 
























 



 



namespace olb {


struct BlockCoordinates3D {
  BlockCoordinates3D() : x0(), x1(), y0(), y1(), z0(), z1() { }
  BlockCoordinates3D(int x0_, int x1_, int y0_, int y1_, int z0_, int z1_)
    : x0(x0_), x1(x1_), y0(y0_), y1(y1_), z0(z0_), z1(z1_)
  { }
  BlockCoordinates3D shift(int deltaX, int deltaY, int deltaZ) const {
    return BlockCoordinates3D(x0+deltaX, x1+deltaX, y0+deltaY, y1+deltaY, z0+deltaZ, z1+deltaZ);
  }
  int x0, x1, y0, y1, z0, z1;
};

namespace util {

inline bool intersect (
  BlockCoordinates3D const& block1,
  BlockCoordinates3D const& block2,
  BlockCoordinates3D& inters )
{
  return intersect(block1.x0, block1.x1, block1.y0, block1.y1, block1.z0, block1.z1,
                   block2.x0, block2.x1, block2.y0, block2.y1, block2.z0, block2.z1,
                   inters.x0, inters.x1, inters.y0, inters.y1, inters.z0, inters.z1);
}

inline bool contained(int iX, int iY, int iZ, BlockCoordinates3D const& block) {
  return contained(iX,iY,iZ, block.x0, block.x1, block.y0, block.y1, block.z0, block.z1);
}

}


class BlockParameters3D {
public:
  BlockParameters3D(int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
                    int envelopeWidth_, int procId_,
                    bool leftX, bool rightX, bool leftY, bool rightY, bool leftZ, bool rightZ);
  int getEnvelopeWidth()                             const { return envelopeWidth; }
  int getProcId()                                    const { return procId; }
  BlockCoordinates3D const& getBulk()                const { return bulk; }
  BlockCoordinates3D const& getEnvelope()            const { return envelope; }
  BlockCoordinates3D const& getNonPeriodicEnvelope() const { return nonPeriodicEnvelope; }
  int getBulkLx() const { return bulk.x1-bulk.x0+1; }
  int getBulkLy() const { return bulk.y1-bulk.y0+1; }
  int getBulkLz() const { return bulk.z1-bulk.z0+1; }
  int getEnvelopeLx() const { return envelope.x1-envelope.x0+1; }
  int getEnvelopeLy() const { return envelope.y1-envelope.y0+1; }
  int getEnvelopeLz() const { return envelope.z1-envelope.z0+1; }
  int toLocalX(int iX) const { return iX-envelope.x0; }
  int toLocalY(int iY) const { return iY-envelope.y0; }
  int toLocalZ(int iZ) const { return iZ-envelope.z0; }
  BlockCoordinates3D toLocal(BlockCoordinates3D const& coord) const {
    return BlockCoordinates3D(coord.shift(-envelope.x0, -envelope.y0, -envelope.z0));
  }
private:
  int envelopeWidth, procId;
  BlockCoordinates3D bulk, envelope, nonPeriodicEnvelope;
};

class Overlap3D {
public:
  Overlap3D(int originalId_, int overlapId_, BlockCoordinates3D const& intersection_)
    : originalId(originalId_), overlapId(overlapId_),
      originalRegion(intersection_),
      overlapRegion(intersection_)
  { }
  Overlap3D(int originalId_, int overlapId_,
            BlockCoordinates3D const& originalRegion_,
            int shiftX, int shiftY, int shiftZ)
    : originalId(originalId_), overlapId(overlapId_),
      originalRegion(originalRegion_),
      overlapRegion(originalRegion.shift(-shiftX, -shiftY, -shiftZ))
  { }
  int getOriginalId() const { return originalId; }
  int getOverlapId()  const { return overlapId; }
  BlockCoordinates3D const& getOriginalCoordinates() const { return originalRegion; }
  BlockCoordinates3D const& getOverlapCoordinates() const  { return overlapRegion; }
  int getShiftX() const { return originalRegion.x0 - overlapRegion.x0; }
  int getShiftY() const { return originalRegion.y0 - overlapRegion.y0; }
  int getShiftZ() const { return originalRegion.z0 - overlapRegion.z0; }
private:
  int originalId, overlapId;
  BlockCoordinates3D originalRegion, overlapRegion;
};

class MultiDataDistribution3D {
public:
  MultiDataDistribution3D(int nx_, int ny_, int nz_);
  MultiDataDistribution3D& operator=(MultiDataDistribution3D const& rhs);
  int getNx() const { return nx; }
  int getNy() const { return ny; }
  int getNz() const { return nz; }
  int getNumBlocks()           const { return blocks.size(); }
  int getNumNormalOverlaps()   const { return normalOverlaps.size(); }
  int getNumPeriodicOverlaps() const { return periodicOverlaps.size(); }
  void addBlock(int x0, int x1, int y0, int y1, int z0, int z1, int envelopeWidth, int procId=0);
  BlockParameters3D const& getBlockParameters(int whichBlock) const;
  Overlap3D   const& getNormalOverlap(int whichOverlap) const;
  Overlap3D const& getPeriodicOverlap(int whichOverlap) const;
  int locate(int iX, int iY, int iZ, int guess=0) const;
  int locateInEnvelopes(int iX, int iY, int iZ, std::vector<int>& foundId, int guess=0) const;
  size_t getNumAllocatedBulkCells() const;
  bool getNextChunkX(int iX, int iY, int iZ, int& nextLattice, int& nextChunkSize) const;
  bool getNextChunkY(int iX, int iY, int iZ, int& nextLattice, int& nextChunkSize) const;
  bool getNextChunkZ(int iX, int iY, int iZ, int& nextLattice, int& nextChunkSize) const;
private:
  void computeNormalOverlaps(BlockParameters3D const& newBlock);
  void computePeriodicOverlaps();
private:
  int nx, ny, nz;
  std::vector<BlockParameters3D> blocks;
  std::vector<Overlap3D> normalOverlaps;
  std::vector<Overlap3D> periodicOverlaps;
  std::vector<std::vector<int> > neighbors;
};


class RelevantIndexes3D {
public:
  
  RelevantIndexes3D(int numBlocks, int numNormalOverlaps, int numPeriodicOverlaps, int nx, int ny, int nz);
  
  RelevantIndexes3D(MultiDataDistribution3D const& dataDistribution, int whichRank);
  
  std::vector<int> const& getBlocks()                const { return myBlocks; }
  
  std::vector<int> const& getNearbyBlocks()          const { return nearbyBlocks; }
  
  std::vector<int> const& getNormalOverlaps()        const { return normalOverlaps; }
  
  std::vector<int> const& getPeriodicOverlaps()      const { return periodicOverlaps; }
  
  std::vector<int> const& getPeriodicOverlapWithMe() const { return periodicOverlapWithMe; }
  
  BlockCoordinates3D const& getBoundingBox()         const { return boundingBox; }
private:
  void listAllIndexes(int numBlocks, int numNormalOverlaps, int numPeriodicOverlaps, int nx, int ny, int nz);
  void computeRelevantIndexesInParallel(MultiDataDistribution3D const& dataDistribution, int whichRank);
private:
  std::vector<int> myBlocks;
  std::vector<int> nearbyBlocks;
  std::vector<int> normalOverlaps;
  std::vector<int> periodicOverlaps;
  std::vector<int> periodicOverlapWithMe;
  BlockCoordinates3D boundingBox;
};

}  


namespace olb {

struct SpatiallyExtendedObject3D {
  virtual ~SpatiallyExtendedObject3D() { }
  virtual MultiDataDistribution3D getDataDistribution() const =0;
  virtual SpatiallyExtendedObject3D* getComponent(int iBlock) =0;
  virtual const SpatiallyExtendedObject3D* getComponent(int iBlock) const =0;
  virtual multiPhysics::MultiPhysicsId getMultiPhysicsId() const =0;
};

} 






















 






























 








namespace std __attribute__ ((__visibility__ ("default")))
{


  
  










 
  template<typename _CharT, typename _Traits, typename _Alloc>
    class basic_stringbuf : public basic_streambuf<_CharT, _Traits>
    {
    public:
      
      typedef _CharT 					char_type;
      typedef _Traits 					traits_type;
      
      
      typedef _Alloc				       	allocator_type;
      typedef typename traits_type::int_type 		int_type;
      typedef typename traits_type::pos_type 		pos_type;
      typedef typename traits_type::off_type 		off_type;

      typedef basic_streambuf<char_type, traits_type>  	__streambuf_type;
      typedef basic_string<char_type, _Traits, _Alloc> 	__string_type;
      typedef typename __string_type::size_type		__size_type;

    protected:
      
      ios_base::openmode 	_M_mode;

      
      __string_type 		_M_string;

    public:
      
      





 
      explicit
      basic_stringbuf(ios_base::openmode __mode = ios_base::in | ios_base::out)
      : __streambuf_type(), _M_mode(__mode), _M_string()
      { }

      






 
      explicit
      basic_stringbuf(const __string_type& __str,
		      ios_base::openmode __mode = ios_base::in | ios_base::out)
      : __streambuf_type(), _M_mode(), _M_string(__str.data(), __str.size())
      { _M_stringbuf_init(__mode); }

      
      






 
      __string_type
      str() const
      {
	__string_type __ret;
	if (this->pptr())
	  {
	    
	    if (this->pptr() > this->egptr())
	      __ret = __string_type(this->pbase(), this->pptr());
	    else
 	      __ret = __string_type(this->pbase(), this->egptr());
	  }
	else
	  __ret = _M_string;
	return __ret;
      }

      





 
      void
      str(const __string_type& __s)
      {
	
	_M_string.assign(__s.data(), __s.size());
	_M_stringbuf_init(_M_mode);
      }

    protected:
      
      void
      _M_stringbuf_init(ios_base::openmode __mode)
      {
	_M_mode = __mode;
	__size_type __len = 0;
	if (_M_mode & (ios_base::ate | ios_base::app))
	  __len = _M_string.size();
	_M_sync(const_cast<char_type*>(_M_string.data()), 0, __len);
      }

      virtual streamsize
      showmanyc()
      { 
	streamsize __ret = -1;
	if (_M_mode & ios_base::in)
	  {
	    _M_update_egptr();
	    __ret = this->egptr() - this->gptr();
	  }
	return __ret;
      }

      virtual int_type
      underflow();

      virtual int_type
      pbackfail(int_type __c = traits_type::eof());

      virtual int_type
      overflow(int_type __c = traits_type::eof());

      









 
      virtual __streambuf_type*
      setbuf(char_type* __s, streamsize __n)
      {
	if (__s && __n >= 0)
	  {
	    
	    
	    
	    
	    
	    
	    _M_string.clear();
	    
	    
	    _M_sync(__s, __n, 0);
	  }
	return this;
      }

      virtual pos_type
      seekoff(off_type __off, ios_base::seekdir __way,
	      ios_base::openmode __mode = ios_base::in | ios_base::out);

      virtual pos_type
      seekpos(pos_type __sp,
	      ios_base::openmode __mode = ios_base::in | ios_base::out);

      
      
      
      void
      _M_sync(char_type* __base, __size_type __i, __size_type __o);

      
      
      void
      _M_update_egptr()
      {
	const bool __testin = _M_mode & ios_base::in;
	if (this->pptr() && this->pptr() > this->egptr())
	  {
	    if (__testin)
	      this->setg(this->eback(), this->gptr(), this->pptr());
	    else
	      this->setg(this->pptr(), this->pptr(), this->pptr());
	  }
      }

      
      
      void
      _M_pbump(char_type* __pbeg, char_type* __pend, off_type __off);
    };


  
  







 
  template<typename _CharT, typename _Traits, typename _Alloc>
    class basic_istringstream : public basic_istream<_CharT, _Traits>
    {
    public:
      
      typedef _CharT 					char_type;
      typedef _Traits 					traits_type;
      
      
      typedef _Alloc				       	allocator_type;
      typedef typename traits_type::int_type 		int_type;
      typedef typename traits_type::pos_type 		pos_type;
      typedef typename traits_type::off_type 		off_type;

      
      typedef basic_string<_CharT, _Traits, _Alloc> 	__string_type;
      typedef basic_stringbuf<_CharT, _Traits, _Alloc> 	__stringbuf_type;
      typedef basic_istream<char_type, traits_type>	__istream_type;

    private:
      __stringbuf_type	_M_stringbuf;

    public:
      
      










 
      explicit
      basic_istringstream(ios_base::openmode __mode = ios_base::in)
      : __istream_type(), _M_stringbuf(__mode | ios_base::in)
      { this->init(&_M_stringbuf); }

      











 
      explicit
      basic_istringstream(const __string_type& __str,
			  ios_base::openmode __mode = ios_base::in)
      : __istream_type(), _M_stringbuf(__str, __mode | ios_base::in)
      { this->init(&_M_stringbuf); }

      




 
      ~basic_istringstream()
      { }

      
      




 
      __stringbuf_type*
      rdbuf() const
      { return const_cast<__stringbuf_type*>(&_M_stringbuf); }

      


 
      __string_type
      str() const
      { return _M_stringbuf.str(); }

      




 
      void
      str(const __string_type& __s)
      { _M_stringbuf.str(__s); }
    };


  
  







 
  template <typename _CharT, typename _Traits, typename _Alloc>
    class basic_ostringstream : public basic_ostream<_CharT, _Traits>
    {
    public:
      
      typedef _CharT 					char_type;
      typedef _Traits 					traits_type;
      
      
      typedef _Alloc				       	allocator_type;
      typedef typename traits_type::int_type 		int_type;
      typedef typename traits_type::pos_type 		pos_type;
      typedef typename traits_type::off_type 		off_type;

      
      typedef basic_string<_CharT, _Traits, _Alloc> 	__string_type;
      typedef basic_stringbuf<_CharT, _Traits, _Alloc> 	__stringbuf_type;
      typedef basic_ostream<char_type, traits_type>	__ostream_type;

    private:
      __stringbuf_type	_M_stringbuf;

    public:
      
      










 
      explicit
      basic_ostringstream(ios_base::openmode __mode = ios_base::out)
      : __ostream_type(), _M_stringbuf(__mode | ios_base::out)
      { this->init(&_M_stringbuf); }

      











 
      explicit
      basic_ostringstream(const __string_type& __str,
			  ios_base::openmode __mode = ios_base::out)
      : __ostream_type(), _M_stringbuf(__str, __mode | ios_base::out)
      { this->init(&_M_stringbuf); }

      




 
      ~basic_ostringstream()
      { }

      
      




 
      __stringbuf_type*
      rdbuf() const
      { return const_cast<__stringbuf_type*>(&_M_stringbuf); }

      


 
      __string_type
      str() const
      { return _M_stringbuf.str(); }

      




 
      void
      str(const __string_type& __s)
      { _M_stringbuf.str(__s); }
    };


  
  







 
  template <typename _CharT, typename _Traits, typename _Alloc>
    class basic_stringstream : public basic_iostream<_CharT, _Traits>
    {
    public:
      
      typedef _CharT 					char_type;
      typedef _Traits 					traits_type;
      
      
      typedef _Alloc				       	allocator_type;
      typedef typename traits_type::int_type 		int_type;
      typedef typename traits_type::pos_type 		pos_type;
      typedef typename traits_type::off_type 		off_type;

      
      typedef basic_string<_CharT, _Traits, _Alloc> 	__string_type;
      typedef basic_stringbuf<_CharT, _Traits, _Alloc> 	__stringbuf_type;
      typedef basic_iostream<char_type, traits_type>	__iostream_type;

    private:
      __stringbuf_type	_M_stringbuf;

    public:
      
      








 
      explicit
      basic_stringstream(ios_base::openmode __m = ios_base::out | ios_base::in)
      : __iostream_type(), _M_stringbuf(__m)
      { this->init(&_M_stringbuf); }

      









 
      explicit
      basic_stringstream(const __string_type& __str,
			 ios_base::openmode __m = ios_base::out | ios_base::in)
      : __iostream_type(), _M_stringbuf(__str, __m)
      { this->init(&_M_stringbuf); }

      




 
      ~basic_stringstream()
      { }

      
      




 
      __stringbuf_type*
      rdbuf() const
      { return const_cast<__stringbuf_type*>(&_M_stringbuf); }

      


 
      __string_type
      str() const
      { return _M_stringbuf.str(); }

      




 
      void
      str(const __string_type& __s)
      { _M_stringbuf.str(__s); }
    };


} 






























 







namespace std __attribute__ ((__visibility__ ("default")))
{


  template <class _CharT, class _Traits, class _Alloc>
    typename basic_stringbuf<_CharT, _Traits, _Alloc>::int_type
    basic_stringbuf<_CharT, _Traits, _Alloc>::
    pbackfail(int_type __c)
    {
      int_type __ret = traits_type::eof();
      if (this->eback() < this->gptr())
	{
	  
	  
	  const bool __testeof = traits_type::eq_int_type(__c, __ret);
	  if (!__testeof)
	    {
	      const bool __testeq = traits_type::eq(traits_type::
						    to_char_type(__c),
						    this->gptr()[-1]);	  
	      const bool __testout = this->_M_mode & ios_base::out;
	      if (__testeq || __testout)
		{
		  this->gbump(-1);
		  if (!__testeq)
		    *this->gptr() = traits_type::to_char_type(__c);
		  __ret = __c;
		}
	    }
	  else
	    {
	      this->gbump(-1);
	      __ret = traits_type::not_eof(__c);
	    }
	}
      return __ret;
    }

  template <class _CharT, class _Traits, class _Alloc>
    typename basic_stringbuf<_CharT, _Traits, _Alloc>::int_type
    basic_stringbuf<_CharT, _Traits, _Alloc>::
    overflow(int_type __c)
    {
      const bool __testout = this->_M_mode & ios_base::out;
      if (__builtin_expect(!__testout, false))
	return traits_type::eof();

      const bool __testeof = traits_type::eq_int_type(__c, traits_type::eof());
      if (__builtin_expect(__testeof, false))
	return traits_type::not_eof(__c);

      const __size_type __capacity = _M_string.capacity();
      const __size_type __max_size = _M_string.max_size();
      const bool __testput = this->pptr() < this->epptr();
      if (__builtin_expect(!__testput && __capacity == __max_size, false))
	return traits_type::eof();

      
      
      const char_type __conv = traits_type::to_char_type(__c);
      if (!__testput)
	{
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  const __size_type __opt_len = std::max(__size_type(2 * __capacity),
						 __size_type(512));
	  const __size_type __len = std::min(__opt_len, __max_size);
	  __string_type __tmp;
	  __tmp.reserve(__len);
	  if (this->pbase())
	    __tmp.assign(this->pbase(), this->epptr() - this->pbase());
	  __tmp.push_back(__conv);
	  _M_string.swap(__tmp);
	  _M_sync(const_cast<char_type*>(_M_string.data()),
		  this->gptr() - this->eback(), this->pptr() - this->pbase());
	}
      else
	*this->pptr() = __conv;
      this->pbump(1);
      return __c;
    }

  template <class _CharT, class _Traits, class _Alloc>
    typename basic_stringbuf<_CharT, _Traits, _Alloc>::int_type
    basic_stringbuf<_CharT, _Traits, _Alloc>::
    underflow()
    {
      int_type __ret = traits_type::eof();
      const bool __testin = this->_M_mode & ios_base::in;
      if (__testin)
	{
	  
	  _M_update_egptr();

	  if (this->gptr() < this->egptr())
	    __ret = traits_type::to_int_type(*this->gptr());
	}
      return __ret;
    }

  template <class _CharT, class _Traits, class _Alloc>
    typename basic_stringbuf<_CharT, _Traits, _Alloc>::pos_type
    basic_stringbuf<_CharT, _Traits, _Alloc>::
    seekoff(off_type __off, ios_base::seekdir __way, ios_base::openmode __mode)
    {
      pos_type __ret =  pos_type(off_type(-1));
      bool __testin = (ios_base::in & this->_M_mode & __mode) != 0;
      bool __testout = (ios_base::out & this->_M_mode & __mode) != 0;
      const bool __testboth = __testin && __testout && __way != ios_base::cur;
      __testin &= !(__mode & ios_base::out);
      __testout &= !(__mode & ios_base::in);

      
      
      const char_type* __beg = __testin ? this->eback() : this->pbase();
      if ((__beg || !__off) && (__testin || __testout || __testboth))
	{
	  _M_update_egptr();

	  off_type __newoffi = __off;
	  off_type __newoffo = __newoffi;
	  if (__way == ios_base::cur)
	    {
	      __newoffi += this->gptr() - __beg;
	      __newoffo += this->pptr() - __beg;
	    }
	  else if (__way == ios_base::end)
	    __newoffo = __newoffi += this->egptr() - __beg;

	  if ((__testin || __testboth)
	      && __newoffi >= 0
	      && this->egptr() - __beg >= __newoffi)
	    {
	      this->setg(this->eback(), this->eback() + __newoffi,
			 this->egptr());
	      __ret = pos_type(__newoffi);
	    }
	  if ((__testout || __testboth)
	      && __newoffo >= 0
	      && this->egptr() - __beg >= __newoffo)
	    {
	      _M_pbump(this->pbase(), this->epptr(), __newoffo);
	      __ret = pos_type(__newoffo);
	    }
	}
      return __ret;
    }

  template <class _CharT, class _Traits, class _Alloc>
    typename basic_stringbuf<_CharT, _Traits, _Alloc>::pos_type
    basic_stringbuf<_CharT, _Traits, _Alloc>::
    seekpos(pos_type __sp, ios_base::openmode __mode)
    {
      pos_type __ret =  pos_type(off_type(-1));
      const bool __testin = (ios_base::in & this->_M_mode & __mode) != 0;
      const bool __testout = (ios_base::out & this->_M_mode & __mode) != 0;

      const char_type* __beg = __testin ? this->eback() : this->pbase();
      if ((__beg || !off_type(__sp)) && (__testin || __testout))
	{
	  _M_update_egptr();

	  const off_type __pos(__sp);
	  const bool __testpos = (0 <= __pos
				  && __pos <= this->egptr() - __beg);
	  if (__testpos)
	    {
	      if (__testin)
		this->setg(this->eback(), this->eback() + __pos,
			   this->egptr());
	      if (__testout)
		_M_pbump(this->pbase(), this->epptr(), __pos);
	      __ret = __sp;
	    }
	}
      return __ret;
    }

  template <class _CharT, class _Traits, class _Alloc>
    void
    basic_stringbuf<_CharT, _Traits, _Alloc>::
    _M_sync(char_type* __base, __size_type __i, __size_type __o)
    {
      const bool __testin = _M_mode & ios_base::in;
      const bool __testout = _M_mode & ios_base::out;
      char_type* __endg = __base + _M_string.size();
      char_type* __endp = __base + _M_string.capacity();

      if (__base != _M_string.data())
	{
	  
	  __endg += __i;
	  __i = 0;
	  __endp = __endg;
	}

      if (__testin)
	this->setg(__base, __base + __i, __endg);
      if (__testout)
	{
	  _M_pbump(__base, __endp, __o);
	  
	  
	  
	  if (!__testin)
	    this->setg(__endg, __endg, __endg);
	}
    }

  template <class _CharT, class _Traits, class _Alloc>
    void
    basic_stringbuf<_CharT, _Traits, _Alloc>::
    _M_pbump(char_type* __pbeg, char_type* __pend, off_type __off)
    {
      this->setp(__pbeg, __pend);
      while (__off > __gnu_cxx::__numeric_traits<int>::__max)
	{
	  this->pbump(__gnu_cxx::__numeric_traits<int>::__max);
	  __off -= __gnu_cxx::__numeric_traits<int>::__max;
	}
      this->pbump(__off);
    }

  
  
  extern template class basic_stringbuf<char>;
  extern template class basic_istringstream<char>;
  extern template class basic_ostringstream<char>;
  extern template class basic_stringstream<char>;

  extern template class basic_stringbuf<wchar_t>;
  extern template class basic_istringstream<wchar_t>;
  extern template class basic_ostringstream<wchar_t>;
  extern template class basic_stringstream<wchar_t>;


} 






























 









namespace std __attribute__ ((__visibility__ ("default")))
{


  
  

  struct _Resetiosflags { ios_base::fmtflags _M_mask; };

  





 
  inline _Resetiosflags 
  resetiosflags(ios_base::fmtflags __mask)
  { return { __mask }; }

  template<typename _CharT, typename _Traits>
    inline basic_istream<_CharT, _Traits>& 
    operator>>(basic_istream<_CharT, _Traits>& __is, _Resetiosflags __f)
    { 
      __is.setf(ios_base::fmtflags(0), __f._M_mask); 
      return __is; 
    }

  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>& 
    operator<<(basic_ostream<_CharT, _Traits>& __os, _Resetiosflags __f)
    { 
      __os.setf(ios_base::fmtflags(0), __f._M_mask); 
      return __os; 
    }


  struct _Setiosflags { ios_base::fmtflags _M_mask; };

  





 
  inline _Setiosflags 
  setiosflags(ios_base::fmtflags __mask)
  { return { __mask }; }

  template<typename _CharT, typename _Traits>
    inline basic_istream<_CharT, _Traits>& 
    operator>>(basic_istream<_CharT, _Traits>& __is, _Setiosflags __f)
    { 
      __is.setf(__f._M_mask); 
      return __is; 
    }

  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>& 
    operator<<(basic_ostream<_CharT, _Traits>& __os, _Setiosflags __f)
    { 
      __os.setf(__f._M_mask); 
      return __os; 
    }


  struct _Setbase { int _M_base; };

  






 
  inline _Setbase 
  setbase(int __base)
  { return { __base }; }

  template<typename _CharT, typename _Traits>
    inline basic_istream<_CharT, _Traits>& 
    operator>>(basic_istream<_CharT, _Traits>& __is, _Setbase __f)
    {
      __is.setf(__f._M_base ==  8 ? ios_base::oct : 
		__f._M_base == 10 ? ios_base::dec : 
		__f._M_base == 16 ? ios_base::hex : 
		ios_base::fmtflags(0), ios_base::basefield);
      return __is; 
    }
  
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>& 
    operator<<(basic_ostream<_CharT, _Traits>& __os, _Setbase __f)
    {
      __os.setf(__f._M_base ==  8 ? ios_base::oct : 
		__f._M_base == 10 ? ios_base::dec : 
		__f._M_base == 16 ? ios_base::hex : 
		ios_base::fmtflags(0), ios_base::basefield);
      return __os; 
    }
  

  template<typename _CharT>
    struct _Setfill { _CharT _M_c; };

  





 
  template<typename _CharT>
    inline _Setfill<_CharT>
    setfill(_CharT __c)
    { return { __c }; }

  template<typename _CharT, typename _Traits>
    inline basic_istream<_CharT, _Traits>& 
    operator>>(basic_istream<_CharT, _Traits>& __is, _Setfill<_CharT> __f)
    { 
      __is.fill(__f._M_c); 
      return __is; 
    }

  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>& 
    operator<<(basic_ostream<_CharT, _Traits>& __os, _Setfill<_CharT> __f)
    { 
      __os.fill(__f._M_c); 
      return __os; 
    }


  struct _Setprecision { int _M_n; };

  





 
  inline _Setprecision 
  setprecision(int __n)
  { return { __n }; }

  template<typename _CharT, typename _Traits>
    inline basic_istream<_CharT, _Traits>& 
    operator>>(basic_istream<_CharT, _Traits>& __is, _Setprecision __f)
    { 
      __is.precision(__f._M_n); 
      return __is; 
    }

  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>& 
    operator<<(basic_ostream<_CharT, _Traits>& __os, _Setprecision __f)
    { 
      __os.precision(__f._M_n); 
      return __os; 
    }


  struct _Setw { int _M_n; };

  





 
  inline _Setw 
  setw(int __n)
  { return { __n }; }

  template<typename _CharT, typename _Traits>
    inline basic_istream<_CharT, _Traits>& 
    operator>>(basic_istream<_CharT, _Traits>& __is, _Setw __f)
    {
      __is.width(__f._M_n);
      return __is; 
    }

  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>& 
    operator<<(basic_ostream<_CharT, _Traits>& __os, _Setw __f)
    {
      __os.width(__f._M_n);
      return __os; 
    }


  
  
  
  extern template ostream& operator<<(ostream&, _Setfill<char>);
  extern template ostream& operator<<(ostream&, _Setiosflags);
  extern template ostream& operator<<(ostream&, _Resetiosflags);
  extern template ostream& operator<<(ostream&, _Setbase);
  extern template ostream& operator<<(ostream&, _Setprecision);
  extern template ostream& operator<<(ostream&, _Setw);
  extern template istream& operator>>(istream&, _Setfill<char>);
  extern template istream& operator>>(istream&, _Setiosflags);
  extern template istream& operator>>(istream&, _Resetiosflags);
  extern template istream& operator>>(istream&, _Setbase);
  extern template istream& operator>>(istream&, _Setprecision);
  extern template istream& operator>>(istream&, _Setw);

  extern template wostream& operator<<(wostream&, _Setfill<wchar_t>);
  extern template wostream& operator<<(wostream&, _Setiosflags);
  extern template wostream& operator<<(wostream&, _Resetiosflags);
  extern template wostream& operator<<(wostream&, _Setbase);
  extern template wostream& operator<<(wostream&, _Setprecision);
  extern template wostream& operator<<(wostream&, _Setw);
  extern template wistream& operator>>(wistream&, _Setfill<wchar_t>);
  extern template wistream& operator>>(wistream&, _Setiosflags);
  extern template wistream& operator>>(wistream&, _Resetiosflags);
  extern template wistream& operator>>(wistream&, _Setbase);
  extern template wistream& operator>>(wistream&, _Setprecision);
  extern template wistream& operator>>(wistream&, _Setw);


} 


namespace olb {


 
class OMBuf : public std::stringbuf {
private:
  std::ostream* output;
  std::string text;
  static bool multiOutput;
public:
  OMBuf();
  ~OMBuf();
  OMBuf(const OMBuf& rhs);
  OMBuf& operator=(const OMBuf& rhs);
  void swap(OMBuf& rhs);
  OMBuf(std::ostream& str, std::string classname);
  void setMultiOutput(bool b);
  
  

 
  virtual int sync();
};

























 
class OstreamManager : public std::ostream
{
private:
  
  
  OMBuf buffer;

public:
  
  
  
  OstreamManager(std::string classname);
  
  OstreamManager(std::ostream& str, std::string classname);
  
  OstreamManager(const OstreamManager& rhs);
  
  OstreamManager& operator=(const OstreamManager& rhs);
  
  ~OstreamManager();
  
  void setMultiOutput(bool b);
};

} 


namespace olb {



template<typename T, template<typename U> class Lattice>
class BlockStructure2D;

template<typename T, template<typename U> class Lattice>
class BlockStructure3D;

template<typename T, template<typename U> class Lattice>
class BlockLattice2D;

template<typename T, template<typename U> class Lattice>
class BlockLattice3D;




template<typename T>
struct Reductor {
  virtual ~Reductor() { }
  virtual void subscribeSum(T& element) =0;
  virtual void subscribeAverage(size_t const& weight, T& element) =0;
  virtual void subscribeMin(T& element) =0;
  virtual void subscribeMax(T& element) =0;
};





template<typename T, template<typename U> class Lattice>
struct PostProcessor2D {
  virtual ~PostProcessor2D() { }
  
  virtual void process(BlockLattice2D<T,Lattice>& blockLattice) =0;
  
  virtual void processSubDomain(BlockLattice2D<T,Lattice>& blockLattice,
                                int x0_, int x1_, int y0_, int y1_) =0;
  
  virtual int extent() const =0;
  
  virtual int extent(int direction) const =0;
  virtual bool hasReductions() const =0;
  virtual void subscribeReductions(BlockLattice2D<T,Lattice>& blockLattice,
                                   Reductor<T>* reductor) =0;
};

template<typename T, template<typename U> class Lattice>
class PostProcessorGenerator2D {
public:
  PostProcessorGenerator2D(int x0_, int x1_, int y0_, int y1_);
  virtual ~PostProcessorGenerator2D() { }
  void shift(int deltaX, int deltaY);
  bool extract(int x0_, int x1_, int y0_, int y1_);
  virtual PostProcessor2D<T,Lattice>* generate() const =0;
  virtual PostProcessorGenerator2D<T,Lattice>* clone() const =0;
protected:
  int x0, x1, y0, y1;
};

template<typename T, template<typename U> class Lattice>
class LatticeCouplingGenerator2D {
public:
  LatticeCouplingGenerator2D(int x0_, int x1_, int y0_, int y1_);
  virtual ~LatticeCouplingGenerator2D() { }
  void shift(int deltaX, int deltaY);
  bool extract(int x0_, int x1_, int y0_, int y1_);
  virtual PostProcessor2D<T,Lattice>* generate(std::vector<SpatiallyExtendedObject2D*> partners) const =0;
  virtual LatticeCouplingGenerator2D<T,Lattice>* clone() const =0;
protected:
  int x0, x1, y0, y1;
};


template<typename T, template<typename U> class Lattice>
struct LocalPostProcessor2D : public PostProcessor2D<T,Lattice> {
  virtual bool hasReductions() const { return false; }
  virtual void subscribeReductions(BlockLattice2D<T,Lattice>& blockLattice,
                                   Reductor<T>* reductor)
  { }
};

template<typename T, template<typename U> class Lattice>
struct GlobalPostProcessor2D : public PostProcessor2D<T,Lattice> {
  virtual bool hasReductions() const { return true; }
  virtual void process(BlockLattice2D<T,Lattice>& blockLattice) =0;
  virtual void processSubDomain(BlockLattice2D<T,Lattice>& blockLattice,
                                int x0_, int x1_, int y0_, int y1_ )
  {
    this -> process(blockLattice);
  }
  virtual int extent() const {
    return 0;
  }
  virtual int extent(int direction) const {
    return 0;
  }
};




template<typename T, template<typename U> class Lattice>
struct PostProcessor3D {
  virtual ~PostProcessor3D() { }
  
  virtual void process(BlockLattice3D<T,Lattice>& blockLattice) =0;
  
  virtual void processSubDomain(BlockLattice3D<T,Lattice>& blockLattice,
                                int x0_, int x1_, int y0_, int y1_,
                                int z0_, int z1_ ) =0;
  
  virtual int extent() const =0;
  
  virtual int extent(int direction) const =0;
  virtual bool hasReductions() const =0;
  virtual void subscribeReductions(BlockLattice3D<T,Lattice>& blockLattice,
                                   Reductor<T>* reductor) =0;
};

template<typename T, template<typename U> class Lattice>
class PostProcessorGenerator3D {
public:
  PostProcessorGenerator3D( int x0_, int x1_, int y0_, int y1_,
                            int z0_, int z1_ );
  virtual ~PostProcessorGenerator3D() { }
  void shift(int deltaX, int deltaY, int deltaZ);
  bool extract(int x0_, int x1_, int y0_, int y1_, int z0_, int z1_);
  virtual PostProcessor3D<T,Lattice>* generate() const =0;
  virtual PostProcessorGenerator3D<T,Lattice>* clone() const =0;
protected:
  int x0, x1, y0, y1, z0, z1;
};


template<typename T, template<typename U> class Lattice>
class LatticeCouplingGenerator3D {
public:
  LatticeCouplingGenerator3D( int x0_, int x1_, int y0_, int y1_,
                              int z0_, int z1_ );
  virtual ~LatticeCouplingGenerator3D() { }
  void shift(int deltaX, int deltaY, int deltaZ);
  bool extract(int x0_, int x1_, int y0_, int y1_, int z0_, int z1_);
  virtual PostProcessor3D<T,Lattice>* generate(std::vector<SpatiallyExtendedObject3D*> partners) const =0;
  virtual LatticeCouplingGenerator3D<T,Lattice>* clone() const =0;
protected:
  int x0, x1, y0, y1, z0, z1;
};


template<typename T, template<typename U> class Lattice>
struct LocalPostProcessor3D : public PostProcessor3D<T,Lattice> {
  virtual bool hasReductions() const { return false; }
  virtual void subscribeReductions(BlockLattice3D<T,Lattice>& blockLattice,
                                   Reductor<T>* reductor)
  { }
};

template<typename T, template<typename U> class Lattice>
struct GlobalPostProcessor3D : public PostProcessor3D<T,Lattice> {
  virtual bool hasReductions() const { return true; }
  virtual void process(BlockLattice3D<T,Lattice>& blockLattice) =0;
  virtual void processSubDomain(BlockLattice3D<T,Lattice>& blockLattice,
                                int x0_, int x1_, int y0_, int y1_,
                                int z0_, int z1_ )
  {
    this -> process(blockLattice);
  }
  virtual int extent() const {
    return 0;
  }
  virtual int extent(int direction) const {
    return 0;
  }
};

template<typename T, template<typename U> class Lattice>
struct StatisticsPostProcessor2D : public GlobalPostProcessor2D<T,Lattice>
{
  StatisticsPostProcessor2D();
  virtual void process(BlockLattice2D<T,Lattice>& blockLattice);
  virtual void subscribeReductions(BlockLattice2D<T,Lattice>& blockLattice,
                                   Reductor<T>* reductor);
};

template<typename T, template<typename U> class Lattice>
class StatPPGenerator2D
  : public PostProcessorGenerator2D<T,Lattice>
{
public:
  StatPPGenerator2D();
  virtual PostProcessor2D<T,Lattice>* generate() const;
  virtual PostProcessorGenerator2D<T,Lattice>* clone() const;
};

template<typename T, template<typename U> class Lattice>
struct StatisticsPostProcessor3D : public GlobalPostProcessor3D<T,Lattice>
{
  StatisticsPostProcessor3D();
  virtual void process(BlockLattice3D<T,Lattice>& blockLattice);
  virtual void subscribeReductions(BlockLattice3D<T,Lattice>& blockLattice,
                                   Reductor<T>* reductor);
};

template<typename T, template<typename U> class Lattice>
class StatPPGenerator3D
  : public PostProcessorGenerator3D<T,Lattice>
{
public:
  StatPPGenerator3D();
  virtual PostProcessor3D<T,Lattice>* generate() const;
  virtual PostProcessorGenerator3D<T,Lattice>* clone() const;
};


}  






















 



 




namespace olb {



template<typename T>
class LatticeStatistics {
public:
  enum { avRho=0, avEnergy=1 } AverageT;
  enum { maxU=0 } MaxT;
public:
  LatticeStatistics();
  ~LatticeStatistics();
  void reset();
  void reset(T average_rho_, T average_energy_, T maxU_, size_t numCells_);

  int subscribeAverage();
  int subscribeSum();
  int subscribeMin();
  int subscribeMax();

  void incrementStats(T rho, T uSqr) {
    tmpAv[avRho]    += rho;
    tmpAv[avEnergy] += uSqr;
    if (uSqr > tmpMax[maxU]) {
      tmpMax[maxU] = uSqr;
    }
    ++tmpNumCells;
  }
  void gatherAverage(int whichAverage, T value);
  void gatherSum(int whichSum, T value);
  void gatherMin(int whichMin, T value);
  void gatherMax(int whichMax, T value);
  void incrementStats();
  T getAverageRho()        const { return averageVect[avRho]; }
  T getAverageEnergy()     const { return averageVect[avEnergy]; }
  T getMaxU()              const { return maxVect[maxU]; }
  size_t const& getNumCells() const { return numCells; }

  T getAverage(int whichAverage) const;
  T getSum(int whichSum) const;
  T getMin(int whichMin) const;
  T getMax(int whichMax) const;

  std::vector<T>& getAverageVect() { return averageVect; }
  std::vector<T>& getSumVect() { return sumVect; }
  std::vector<T>& getMinVect() { return minVect; }
  std::vector<T>& getMaxVect() { return maxVect; }

  void incrementTime() { ++latticeTime; };
  void resetTime(size_t value=0) { latticeTime=value; } ;
  size_t getTime() const { return latticeTime; };
  void print(int iterationStep, T physicalTime=-1) const;
  void initialize();
private:
  mutable OstreamManager clout;
  
  std::vector<T> tmpAv, tmpSum, tmpMin, tmpMax;
  size_t tmpNumCells;
  
  std::vector<T> averageVect, sumVect, minVect, maxVect;
  size_t numCells;
  size_t latticeTime;
  bool firstCall;
};

}  


namespace olb {

namespace dynamicParams {

const int omega_shear = 0;
const int omega_bulk  = 1;


const int sqrSpeedOfSound = 100; 
const int sqrInvSpeedOfSound = 101; 


}

template<typename T, template<typename U> class Lattice> class Cell;


template<typename T, template<typename U> class Lattice>
struct Dynamics {
  
  virtual ~Dynamics() { }
  
  virtual Dynamics<T,Lattice>* clone() const =0;
  
  virtual void collide(Cell<T,Lattice>& cell,
                       LatticeStatistics<T>& statistics_) =0;
  
  virtual void staticCollide(Cell<T,Lattice>& cell,
                             const T u[Lattice<T>::d],
                             LatticeStatistics<T>& statistics_) =0;
  
  virtual T computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const =0;
  
  virtual void iniEquilibrium(Cell<T,Lattice>& cell, T rho, const T u[Lattice<T>::d]);
  
  
 
  virtual T computeRho(Cell<T,Lattice> const& cell) const =0;
  
  
 
  virtual void computeU( Cell<T,Lattice> const& cell,
                         T u[Lattice<T>::d] ) const =0;
  
  
 
  virtual void computeJ( Cell<T,Lattice> const& cell,
                         T j[Lattice<T>::d] ) const =0;
  
   
  virtual void computeStress (
    Cell<T,Lattice> const& cell,
    T rho, const T u[Lattice<T>::d],
    T pi[util::TensorVal<Lattice<T> >::n] ) const =0;
  
  

 
  virtual void computeRhoU (
    Cell<T,Lattice> const& cell,
    T& rho, T u[Lattice<T>::d]) const =0;
  
  


 
  virtual void computeAllMomenta (
    Cell<T,Lattice> const& cell,
    T& rho, T u[Lattice<T>::d],
    T pi[util::TensorVal<Lattice<T> >::n] ) const =0;
  
  
 
  virtual void computePopulations(Cell<T,Lattice> const& cell, T* f) const;
  
  
 
  virtual void computeExternalField (
    Cell<T,Lattice> const& cell, int pos, int size, T* ext ) const;
  
  
 
  virtual void defineRho(Cell<T,Lattice>& cell, T rho) =0;
  
  
 
  virtual void defineU(Cell<T,Lattice>& cell,
                       const T u[Lattice<T>::d]) =0;
  
  virtual void setBoundaryIntersection(int iPop, T distance);
  virtual bool getBoundaryIntersection(int iPop, T point[Lattice<T>::d]);
  virtual void defineU(const T u[Lattice<T>::d]);
  virtual void defineU(int iPop, const T u[Lattice<T>::d]);
  virtual T    getVelocityCoefficient(int iPop);

  
  

 
  virtual void defineRhoU (
    Cell<T,Lattice>& cell,
    T rho, const T u[Lattice<T>::d]) =0;
  
  


 
  virtual void defineAllMomenta (
    Cell<T,Lattice>& cell,
    T rho, const T u[Lattice<T>::d],
    const T pi[util::TensorVal<Lattice<T> >::n] ) =0;
  
  
 
  virtual void definePopulations(Cell<T,Lattice>& cell, const T* f);
  
  
 
  virtual void defineExternalField (
    Cell<T,Lattice>& cell, int pos, int size, const T* ext);
  
  virtual T getOmega() const =0;
  
  virtual void setOmega(T omega_) =0;
  
  virtual T getParameter(int whichParameter) const;
  
  virtual void setParameter(int whichParameter, T value);
};





 
template<typename T, template<typename U> class Lattice>
struct Momenta {
  
  virtual ~Momenta() { }
  
  virtual T computeRho(Cell<T,Lattice> const& cell) const =0;
  
  virtual void computeU (
    Cell<T,Lattice> const& cell,
    T u[Lattice<T>::d] ) const =0;
  
  virtual void computeJ (
    Cell<T,Lattice> const& cell,
    T j[Lattice<T>::d] ) const =0;
  
  virtual void computeStress (
    Cell<T,Lattice> const& cell,
    T rho, const T u[Lattice<T>::d],
    T pi[util::TensorVal<Lattice<T> >::n] ) const =0;
  
  virtual void computeRhoU (
    Cell<T,Lattice> const& cell,
    T& rho, T u[Lattice<T>::d]) const;
  
  virtual void computeAllMomenta (
    Cell<T,Lattice> const& cell,
    T& rho, T u[Lattice<T>::d],
    T pi[util::TensorVal<Lattice<T> >::n] ) const;
  
  virtual void defineRho(Cell<T,Lattice>& cell, T rho) =0;
  
  virtual void defineU(Cell<T,Lattice>& cell,
                       const T u[Lattice<T>::d]) =0;
  
  virtual void defineRhoU (
    Cell<T,Lattice>& cell,
    T rho, const T u[Lattice<T>::d]);
  
  virtual void defineAllMomenta (
    Cell<T,Lattice>& cell,
    T rho, const T u[Lattice<T>::d],
    const T pi[util::TensorVal<Lattice<T> >::n] ) =0;
};




 
template<typename T, template<typename U> class Lattice>
class BasicDynamics : public Dynamics<T,Lattice> {
public:
  
  BasicDynamics(Momenta<T,Lattice>& momenta_);
  
  virtual T computeRho(Cell<T,Lattice> const& cell) const;
  
  virtual void computeU (
    Cell<T,Lattice> const& cell,
    T u[Lattice<T>::d] ) const;
  
  virtual void computeJ (
    Cell<T,Lattice> const& cell,
    T j[Lattice<T>::d] ) const;
  
  virtual void computeStress (
    Cell<T,Lattice> const& cell,
    T rho, const T u[Lattice<T>::d],
    T pi[util::TensorVal<Lattice<T> >::n] ) const;
  
  virtual void computeRhoU (
    Cell<T,Lattice> const& cell,
    T& rho, T u[Lattice<T>::d]) const;
  
  virtual void computeAllMomenta (
    Cell<T,Lattice> const& cell,
    T& rho, T u[Lattice<T>::d],
    T pi[util::TensorVal<Lattice<T> >::n] ) const;
  
  virtual void defineRho(Cell<T,Lattice>& cell, T rho);
  
  virtual void defineU(Cell<T,Lattice>& cell,
                       const T u[Lattice<T>::d]);
  
  virtual void defineRhoU (
    Cell<T,Lattice>& cell,
    T rho, const T u[Lattice<T>::d]);
  
  virtual void defineAllMomenta (
    Cell<T,Lattice>& cell,
    T rho, const T u[Lattice<T>::d],
    const T pi[util::TensorVal<Lattice<T> >::n] );
protected:
  Momenta<T,Lattice>& momenta;  
};


template<typename T, template<typename U> class Lattice>
class BGKdynamics : public BasicDynamics<T,Lattice> {
public:
  
  BGKdynamics(T omega_, Momenta<T,Lattice>& momenta_);
  
  virtual BGKdynamics<T,Lattice>* clone() const;
  
  virtual T computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const;
  
  virtual void collide(Cell<T,Lattice>& cell,
                       LatticeStatistics<T>& statistics_);
  
  virtual void staticCollide(Cell<T,Lattice>& cell,
                             const T u[Lattice<T>::d],
                             LatticeStatistics<T>& statistics_);
  
  virtual T getOmega() const;
  
  virtual void setOmega(T omega_);
private:
  T omega;  
};


template<typename T, template<typename U> class Lattice>
class ConstRhoBGKdynamics : public BasicDynamics<T,Lattice> {
public:
  
  ConstRhoBGKdynamics(T omega_, Momenta<T,Lattice>& momenta_);
  
  virtual ConstRhoBGKdynamics<T,Lattice>* clone() const;
  
  virtual T computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const;
  
  virtual void collide(Cell<T,Lattice>& cell,
                       LatticeStatistics<T>& statistics_);
  
  virtual void staticCollide(Cell<T,Lattice>& cell,
                             const T u[Lattice<T>::d],
                             LatticeStatistics<T>& statistics_);
  
  virtual T getOmega() const;
  
  virtual void setOmega(T omega_);
private:
  T omega;  
};


template<typename T, template<typename U> class Lattice>
class IncBGKdynamics : public BasicDynamics<T,Lattice> {
public:
  
  IncBGKdynamics(T omega_, Momenta<T,Lattice>& momenta_);
  
  virtual IncBGKdynamics<T,Lattice>* clone() const;
  
  virtual T computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const;
  
  virtual void collide(Cell<T,Lattice>& cell,
                       LatticeStatistics<T>& statistics_);
  
  virtual void staticCollide(Cell<T,Lattice>& cell,
                             const T u[Lattice<T>::d],
                             LatticeStatistics<T>& statistics_);
  
  virtual T getOmega() const;
  
  virtual void setOmega(T omega_);
private:
  T omega;  
};







 
template<typename T, template<typename U> class Lattice>
class RLBdynamics : public BasicDynamics<T,Lattice> {
public:
  
  RLBdynamics(T omega_, Momenta<T,Lattice>& momenta_);
  
  virtual RLBdynamics<T,Lattice>* clone() const;
  
  virtual T computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const;
  
  virtual void collide(Cell<T,Lattice>& cell,
                       LatticeStatistics<T>& statistics_);
  
  virtual void staticCollide(Cell<T,Lattice>& cell,
                             const T u[Lattice<T>::d],
                             LatticeStatistics<T>& statistics_);
  
  virtual T getOmega() const;
  
  virtual void setOmega(T omega_);
private:
  T omega;  
};


template<typename T, template<typename U> class Lattice, typename Dynamics>
class CombinedRLBdynamics : public BasicDynamics<T,Lattice>
{
public:
  
  CombinedRLBdynamics(T omega_, Momenta<T,Lattice>& momenta_);
  
  virtual CombinedRLBdynamics<T, Lattice, Dynamics>* clone() const;
  
  virtual T computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const;
  
  virtual void collide(Cell<T,Lattice>& cell,
                       LatticeStatistics<T>& statistics_);
  
  virtual void staticCollide(Cell<T,Lattice>& cell,
                             const T u[Lattice<T>::d],
                             LatticeStatistics<T>& statistics_);
  
  virtual T getOmega() const;
  
  virtual void setOmega(T omega_);
  
  virtual T getParameter(int whichParameter) const;
  
  virtual void setParameter(int whichParameter, T value);
private:
  Dynamics boundaryDynamics;
};


template<typename T, template<typename U> class Lattice>
class ForcedBGKdynamics : public BasicDynamics<T,Lattice> {
public:
  
  ForcedBGKdynamics(T omega_, Momenta<T,Lattice>& momenta_);
  
  virtual ForcedBGKdynamics<T,Lattice>* clone() const;
  
  virtual T computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const;
  
  virtual void collide(Cell<T,Lattice>& cell,
                       LatticeStatistics<T>& statistics_);
  
  virtual void staticCollide(Cell<T,Lattice>& cell,
                             const T u[Lattice<T>::d],
                             LatticeStatistics<T>& statistics_);
  
  virtual T getOmega() const;
  
  virtual void setOmega(T omega_);
protected:
  T omega;  
  static const int forceBeginsAt = Lattice<T>::ExternalField::forceBeginsAt;
  static const int sizeOfForce   = Lattice<T>::ExternalField::sizeOfForce;
};







 
template<typename T, template<typename U> class Lattice>
class D3Q13dynamics : public BasicDynamics<T,Lattice> {
public:
  
  D3Q13dynamics(T omega_, Momenta<T,Lattice>& momenta_);
  
  virtual D3Q13dynamics<T,Lattice>* clone() const;
  
  virtual T computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const;
  
  virtual void collide(Cell<T,Lattice>& cell,
                       LatticeStatistics<T>& statistics_);
  
  virtual void staticCollide(Cell<T,Lattice>& cell,
                             const T u[Lattice<T>::d],
                             LatticeStatistics<T>& statistics_);
  
  virtual T getOmega() const;
  
  virtual void setOmega(T omega_);
private:
  T lambda_nu;        
  T lambda_nu_prime;  
};


template<typename T, template<typename U> class Lattice>
struct BulkMomenta : public Momenta<T,Lattice> {
  
  virtual T computeRho(Cell<T,Lattice> const& cell) const;
  
  virtual void computeU (
    Cell<T,Lattice> const& cell,
    T u[Lattice<T>::d] ) const;
  
  virtual void computeJ (
    Cell<T,Lattice> const& cell,
    T j[Lattice<T>::d] ) const;
  
  virtual void computeStress (
    Cell<T,Lattice> const& cell,
    T rho, const T u[Lattice<T>::d],
    T pi[util::TensorVal<Lattice<T> >::n] ) const;
  
  virtual void computeRhoU (
    Cell<T,Lattice> const& cell,
    T& rho, T u[Lattice<T>::d]) const;
  
  virtual void computeAllMomenta (
    Cell<T,Lattice> const& cell,
    T& rho, T u[Lattice<T>::d],
    T pi[util::TensorVal<Lattice<T> >::n] ) const;
  
  virtual void defineRho(Cell<T,Lattice>& cell, T rho);
  
  virtual void defineU(Cell<T,Lattice>& cell,
                       const T u[Lattice<T>::d]);
  
  virtual void defineRhoU (
    Cell<T,Lattice>& cell,
    T rho, const T u[Lattice<T>::d]);
  
  virtual void defineAllMomenta (
    Cell<T,Lattice>& cell,
    T rho, const T u[Lattice<T>::d],
    const T pi[util::TensorVal<Lattice<T> >::n] );
};


template<typename T, template<typename U> class Lattice>
struct ExternalVelocityMomenta : public Momenta<T,Lattice> {
  
  virtual T computeRho(Cell<T,Lattice> const& cell) const;
  
  virtual void computeU (
    Cell<T,Lattice> const& cell,
    T u[Lattice<T>::d] ) const;
  
  virtual void computeJ (
    Cell<T,Lattice> const& cell,
    T j[Lattice<T>::d] ) const;
  
  virtual void computeStress (
    Cell<T,Lattice> const& cell,
    T rho, const T u[Lattice<T>::d],
    T pi[util::TensorVal<Lattice<T> >::n] ) const;
  
  virtual void computeRhoU (
    Cell<T,Lattice> const& cell,
    T& rho, T u[Lattice<T>::d]) const;
  
  virtual void computeAllMomenta (
    Cell<T,Lattice> const& cell,
    T& rho, T u[Lattice<T>::d],
    T pi[util::TensorVal<Lattice<T> >::n] ) const;
  
  virtual void defineRho(Cell<T,Lattice>& cell, T rho);
  
  virtual void defineU(Cell<T,Lattice>& cell,
                       const T u[Lattice<T>::d]);
  
  virtual void defineRhoU (
    Cell<T,Lattice>& cell,
    T rho, const T u[Lattice<T>::d]);
  
  virtual void defineAllMomenta (
    Cell<T,Lattice>& cell,
    T rho, const T u[Lattice<T>::d],
    const T pi[util::TensorVal<Lattice<T> >::n] );
};








 
template<typename T, template<typename U> class Lattice>
class BounceBack : public Dynamics<T,Lattice> {
public:
  
  BounceBack();
  
  BounceBack(T rho_);
  
  virtual BounceBack<T,Lattice>* clone() const;
  
  virtual T computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const;
  
  virtual void collide(Cell<T,Lattice>& cell,
                       LatticeStatistics<T>& statistics_);
  
  virtual void staticCollide(Cell<T,Lattice>& cell,
                             const T u[Lattice<T>::d],
                             LatticeStatistics<T>& statistics_);
  
  virtual T computeRho(Cell<T,Lattice> const& cell) const;
  
  virtual void computeU (
    Cell<T,Lattice> const& cell,
    T u[Lattice<T>::d] ) const;
  
  virtual void computeJ (
    Cell<T,Lattice> const& cell,
    T j[Lattice<T>::d] ) const;
  
  virtual void computeStress (
    Cell<T,Lattice> const& cell,
    T rho, const T u[Lattice<T>::d],
    T pi[util::TensorVal<Lattice<T> >::n] ) const;
  virtual void computeRhoU (
    Cell<T,Lattice> const& cell,
    T& rho, T u[Lattice<T>::d]) const;
  virtual void computeAllMomenta (
    Cell<T,Lattice> const& cell,
    T& rho, T u[Lattice<T>::d],
    T pi[util::TensorVal<Lattice<T> >::n] ) const;
  
  virtual void defineRho(Cell<T,Lattice>& cell, T rho);
  
  virtual void defineU(Cell<T,Lattice>& cell,
                       const T u[Lattice<T>::d]);
  
  virtual void defineRhoU (
    Cell<T,Lattice>& cell,
    T rho, const T u[Lattice<T>::d]);
  
  virtual void defineAllMomenta (
    Cell<T,Lattice>& cell,
    T rho, const T u[Lattice<T>::d],
    const T pi[util::TensorVal<Lattice<T> >::n] );
  
  virtual T getOmega() const;
  
  virtual void setOmega(T omega_);
private:
  T rho;
  bool rhoFixed;
};


template<typename T, template<typename U> class Lattice>
class NoDynamics : public Dynamics<T,Lattice> {
public:
  
  virtual NoDynamics<T,Lattice>* clone() const;
  
  virtual T computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const;
  
  virtual void collide(Cell<T,Lattice>& cell,
                       LatticeStatistics<T>& statistics_);
  
  virtual void staticCollide(Cell<T,Lattice>& cell,
                             const T u[Lattice<T>::d],
                             LatticeStatistics<T>& statistics_);
  
  virtual T computeRho(Cell<T,Lattice> const& cell) const;
  
  virtual void computeU (
    Cell<T,Lattice> const& cell,
    T u[Lattice<T>::d] ) const;
  
  virtual void computeJ (
    Cell<T,Lattice> const& cell,
    T j[Lattice<T>::d] ) const;
  
  virtual void computeStress (
    Cell<T,Lattice> const& cell,
    T rho, const T u[Lattice<T>::d],
    T pi[util::TensorVal<Lattice<T> >::n] ) const;
  virtual void computeRhoU (
    Cell<T,Lattice> const& cell,
    T& rho, T u[Lattice<T>::d]) const;
  virtual void computeAllMomenta (
    Cell<T,Lattice> const& cell,
    T& rho, T u[Lattice<T>::d],
    T pi[util::TensorVal<Lattice<T> >::n] ) const;
  
  virtual void defineRho(Cell<T,Lattice>& cell, T rho);
  
  virtual void defineU(Cell<T,Lattice>& cell,
                       const T u[Lattice<T>::d]);
  
  virtual void defineRhoU (
    Cell<T,Lattice>& cell,
    T rho, const T u[Lattice<T>::d]);
  
  virtual void defineAllMomenta (
    Cell<T,Lattice>& cell,
    T rho, const T u[Lattice<T>::d],
    const T pi[util::TensorVal<Lattice<T> >::n] );
  
  virtual T getOmega() const;
  
  virtual void setOmega(T omega_);
};




template<typename T, template<typename U> class Lattice>
class OffDynamics : public NoDynamics<T,Lattice> {
public:
  
  OffDynamics(const T _location[Lattice<T>::d]);
  
  OffDynamics(const T _location[Lattice<T>::d], T _distances[Lattice<T>::q]);
  
  virtual void setBoundaryIntersection(int iPop, T distance);
  
  virtual bool getBoundaryIntersection(int iPop, T intersection[Lattice<T>::d]);
  
  virtual void defineU(Cell<T,Lattice>& cell, const T u[Lattice<T>::d]);
  
  virtual void defineU(const T u[Lattice<T>::d]);
  
  virtual void defineU(int iPop, const T u[Lattice<T>::d]);
  
  virtual T    getVelocityCoefficient(int iPop);

private:
  T location[Lattice<T>::d];
  T distances[Lattice<T>::q];
  T boundaryIntersection[Lattice<T>::q][Lattice<T>::d];
  T velocityCoefficient[Lattice<T>::q];
};

namespace instances {

template<typename T, template<typename U> class Lattice>
BulkMomenta<T,Lattice>& getBulkMomenta();

template<typename T, template<typename U> class Lattice>
ExternalVelocityMomenta<T,Lattice>& getExternalVelocityMomenta();

template<typename T, template<typename U> class Lattice>
BounceBack<T,Lattice>& getBounceBack();

template<typename T, template<typename U> class Lattice>
NoDynamics<T,Lattice>& getNoDynamics();

}

}






















 




 




























 









































































namespace std __attribute__ ((__visibility__ ("default")))
{


  



 
  enum float_round_style
  {
    round_indeterminate       = -1,    
    round_toward_zero         = 0,     
    round_to_nearest          = 1,     
    round_toward_infinity     = 2,     
    round_toward_neg_infinity = 3      
  };

  




 
  enum float_denorm_style
  {
    
    denorm_indeterminate = -1,
    
    denorm_absent        = 0,
    
    denorm_present       = 1
  };

  








 
  struct __numeric_limits_base
  {
    
 
    static const bool is_specialized = false;

    

 
    static const int digits = 0;

     
    static const int digits10 = 0;


     
    static const bool is_signed = false;

    
 
    static const bool is_integer = false;

    


 
    static const bool is_exact = false;

    
 
    static const int radix = 0;

    
 
    static const int min_exponent = 0;

    
 
    static const int min_exponent10 = 0;

    

 
    static const int max_exponent = 0;

    
 
    static const int max_exponent10 = 0;

     
    static const bool has_infinity = false;

    
 
    static const bool has_quiet_NaN = false;

    
 
    static const bool has_signaling_NaN = false;

     
    static const float_denorm_style has_denorm = denorm_absent;

    
 
    static const bool has_denorm_loss = false;

    
 
    static const bool is_iec559 = false;

    

 
    static const bool is_bounded = false;

    


 
    static const bool is_modulo = false;

     
    static const bool traps = false;

     
    static const bool tinyness_before = false;

    

 
    static const float_round_style round_style = 
						    round_toward_zero;
  };

  









 
  template<typename _Tp>
    struct numeric_limits : public __numeric_limits_base
    {
      
 
      static  _Tp
      min() throw() { return static_cast<_Tp>(0); }

       
      static  _Tp
      max() throw() { return static_cast<_Tp>(0); }


      
 
      static  _Tp
      epsilon() throw() { return static_cast<_Tp>(0); }

       
      static  _Tp
      round_error() throw() { return static_cast<_Tp>(0); }

       
      static  _Tp
      infinity() throw()  { return static_cast<_Tp>(0); }

      
 
      static  _Tp
      quiet_NaN() throw() { return static_cast<_Tp>(0); }

      
 
      static  _Tp
      signaling_NaN() throw() { return static_cast<_Tp>(0); }

      

 
      static  _Tp
      denorm_min() throw() { return static_cast<_Tp>(0); }
    };


  
  

  
  template<>
    struct numeric_limits<bool>
    {
      static const bool is_specialized = true;

      static  bool 
      min() throw() { return false; }

      static  bool 
      max() throw()  { return true; }

      static const int digits = 1;
      static const int digits10 = 0;
      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static  bool 
      epsilon() throw() { return false; }

      static  bool 
      round_error() throw() { return false; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm 
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static  bool 
      infinity() throw() { return false; }

      static  bool 
      quiet_NaN() throw() { return false; }

      static  bool 
      signaling_NaN() throw() { return false; }

      static  bool 
      denorm_min() throw() { return false; }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      
      
      
      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style 
       = round_toward_zero;
    };

  
  template<>
    struct numeric_limits<char>
    {
      static const bool is_specialized = true;

      static  char 
      min() throw() { return (((char)(-1) < 0) ? (char)1 << (sizeof(char) * 8 - ((char)(-1) < 0)) : (char)0); }

      static  char 
      max() throw() { return (((char)(-1) < 0) ? (((((char)1 << ((sizeof(char) * 8 - ((char)(-1) < 0)) - 1)) - 1) << 1) + 1) : ~(char)0); }


      static const int digits = (sizeof(char) * 8 - ((char)(-1) < 0));
      static const int digits10 = ((sizeof(char) * 8 - ((char)(-1) < 0)) * 643L / 2136);
      static const bool is_signed = ((char)(-1) < 0);
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static  char 
      epsilon() throw() { return 0; }

      static  char 
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm 
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static  
      char infinity() throw()  { return char(); }

      static  char 
      quiet_NaN() throw() { return char(); }

      static  char 
      signaling_NaN() throw() { return char(); }

      static  char 
      denorm_min() throw() { return static_cast<char>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style 
       = round_toward_zero;
    };

  
  template<>
    struct numeric_limits<signed char>
    {
      static const bool is_specialized = true;

      static  signed char 
      min() throw() { return -127 - 1; }

      static  signed char 
      max() throw() { return 127; }


      static const int digits = (sizeof(signed char) * 8 - ((signed char)(-1) < 0));
      static const int digits10 
       = ((sizeof(signed char) * 8 - ((signed char)(-1) < 0)) * 643L / 2136);
      static const bool is_signed = true;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static  signed char 
      epsilon() throw() { return 0; }

      static  signed char 
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm 
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static  signed char 
      infinity() throw() { return static_cast<signed char>(0); }

      static  signed char 
      quiet_NaN() throw() { return static_cast<signed char>(0); }

      static  signed char 
      signaling_NaN() throw() { return static_cast<signed char>(0); }

      static  signed char 
      denorm_min() throw() { return static_cast<signed char>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style 
       = round_toward_zero;
    };

  
  template<>
    struct numeric_limits<unsigned char>
    {
      static const bool is_specialized = true;

      static  unsigned char 
      min() throw() { return 0; }

      static  unsigned char 
      max() throw() { return 127 * 2U + 1; }


      static const int digits 
       = (sizeof(unsigned char) * 8 - ((unsigned char)(-1) < 0));
      static const int digits10 
       = ((sizeof(unsigned char) * 8 - ((unsigned char)(-1) < 0)) * 643L / 2136);
      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static  unsigned char 
      epsilon() throw() { return 0; }

      static  unsigned char 
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm 
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static  unsigned char 
      infinity() throw() { return static_cast<unsigned char>(0); }

      static  unsigned char 
      quiet_NaN() throw() { return static_cast<unsigned char>(0); }

      static  unsigned char 
      signaling_NaN() throw() { return static_cast<unsigned char>(0); }

      static  unsigned char 
      denorm_min() throw() { return static_cast<unsigned char>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style 
       = round_toward_zero;
    };

  
  template<>
    struct numeric_limits<wchar_t>
    {
      static const bool is_specialized = true;

      static  wchar_t 
      min() throw() { return (((wchar_t)(-1) < 0) ? (wchar_t)1 << (sizeof(wchar_t) * 8 - ((wchar_t)(-1) < 0)) : (wchar_t)0); }

      static  wchar_t 
      max() throw()  { return (((wchar_t)(-1) < 0) ? (((((wchar_t)1 << ((sizeof(wchar_t) * 8 - ((wchar_t)(-1) < 0)) - 1)) - 1) << 1) + 1) : ~(wchar_t)0); }


      static const int digits = (sizeof(wchar_t) * 8 - ((wchar_t)(-1) < 0));
      static const int digits10 
       = ((sizeof(wchar_t) * 8 - ((wchar_t)(-1) < 0)) * 643L / 2136);
      static const bool is_signed = ((wchar_t)(-1) < 0);
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static  wchar_t 
      epsilon() throw() { return 0; }

      static  wchar_t 
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm 
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static  wchar_t 
      infinity() throw() { return wchar_t(); }

      static  wchar_t 
      quiet_NaN() throw() { return wchar_t(); }

      static  wchar_t 
      signaling_NaN() throw() { return wchar_t(); }

      static  wchar_t 
      denorm_min() throw() { return wchar_t(); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style 
       = round_toward_zero;
    };


  
  template<>
    struct numeric_limits<short>
    {
      static const bool is_specialized = true;

      static  short 
      min() throw() { return -32767 - 1; }

      static  short 
      max() throw() { return 32767; }


      static const int digits = (sizeof(short) * 8 - ((short)(-1) < 0));
      static const int digits10 = ((sizeof(short) * 8 - ((short)(-1) < 0)) * 643L / 2136);
      static const bool is_signed = true;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static  short 
      epsilon() throw() { return 0; }

      static  short 
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm 
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static  short 
      infinity() throw() { return short(); }

      static  short 
      quiet_NaN() throw() { return short(); }

      static  short 
      signaling_NaN() throw() { return short(); }

      static  short 
      denorm_min() throw() { return short(); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style 
       = round_toward_zero;
    };

  
  template<>
    struct numeric_limits<unsigned short>
    {
      static const bool is_specialized = true;

      static  unsigned short 
      min() throw() { return 0; }

      static  unsigned short 
      max() throw() { return 32767 * 2U + 1; }


      static const int digits 
       = (sizeof(unsigned short) * 8 - ((unsigned short)(-1) < 0));
      static const int digits10 
       = ((sizeof(unsigned short) * 8 - ((unsigned short)(-1) < 0)) * 643L / 2136);
      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static  unsigned short 
      epsilon() throw() { return 0; }

      static  unsigned short 
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm 
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static  unsigned short 
      infinity() throw() { return static_cast<unsigned short>(0); }

      static  unsigned short 
      quiet_NaN() throw() { return static_cast<unsigned short>(0); }

      static  unsigned short 
      signaling_NaN() throw() { return static_cast<unsigned short>(0); }

      static  unsigned short 
      denorm_min() throw() { return static_cast<unsigned short>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style 
       = round_toward_zero;
    };

  
  template<>
    struct numeric_limits<int>
    {
      static const bool is_specialized = true;

      static  int 
      min() throw() { return -2147483647 - 1; }

      static  int 
      max() throw() { return 2147483647; }


      static const int digits = (sizeof(int) * 8 - ((int)(-1) < 0));
      static const int digits10 = ((sizeof(int) * 8 - ((int)(-1) < 0)) * 643L / 2136);
      static const bool is_signed = true;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static  int 
      epsilon() throw() { return 0; }

      static  int 
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm 
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static  int 
      infinity() throw() { return static_cast<int>(0); }

      static  int 
      quiet_NaN() throw() { return static_cast<int>(0); }

      static  int 
      signaling_NaN() throw() { return static_cast<int>(0); }

      static  int 
      denorm_min() throw() { return static_cast<int>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style 
       = round_toward_zero;
    };

  
  template<>
    struct numeric_limits<unsigned int>
    {
      static const bool is_specialized = true;

      static  unsigned int 
      min() throw() { return 0; }

      static  unsigned int 
      max() throw() { return 2147483647 * 2U + 1; }


      static const int digits 
       = (sizeof(unsigned int) * 8 - ((unsigned int)(-1) < 0));
      static const int digits10 
       = ((sizeof(unsigned int) * 8 - ((unsigned int)(-1) < 0)) * 643L / 2136);
      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static  unsigned int 
      epsilon() throw() { return 0; }

      static  unsigned int 
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm 
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static  unsigned int 
      infinity() throw() { return static_cast<unsigned int>(0); }

      static  unsigned int 
      quiet_NaN() throw() { return static_cast<unsigned int>(0); }

      static  unsigned int 
      signaling_NaN() throw() { return static_cast<unsigned int>(0); }

      static  unsigned int 
      denorm_min() throw() { return static_cast<unsigned int>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style 
       = round_toward_zero;
    };

  
  template<>
    struct numeric_limits<long>
    {
      static const bool is_specialized = true;

      static  long
      min() throw() { return -9223372036854775807L - 1; }

      static  long 
      max() throw() { return 9223372036854775807L; }


      static const int digits = (sizeof(long) * 8 - ((long)(-1) < 0));
      static const int digits10 = ((sizeof(long) * 8 - ((long)(-1) < 0)) * 643L / 2136);
      static const bool is_signed = true;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static  long 
      epsilon() throw() { return 0; }

      static  long 
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm 
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static  long 
      infinity() throw() { return static_cast<long>(0); }

      static  long 
      quiet_NaN() throw() { return static_cast<long>(0); }

      static  long 
      signaling_NaN() throw() { return static_cast<long>(0); }

      static  long 
      denorm_min() throw() { return static_cast<long>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style 
       = round_toward_zero;
    };

  
  template<>
    struct numeric_limits<unsigned long>
    {
      static const bool is_specialized = true;

      static  unsigned long 
      min() throw() { return 0; }

      static  unsigned long 
      max() throw() { return 9223372036854775807L * 2UL + 1; }


      static const int digits 
       = (sizeof(unsigned long) * 8 - ((unsigned long)(-1) < 0));
      static const int digits10 
       = ((sizeof(unsigned long) * 8 - ((unsigned long)(-1) < 0)) * 643L / 2136);
      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static  unsigned long 
      epsilon() throw() { return 0; }

      static  unsigned long 
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm 
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static  unsigned long 
      infinity() throw() { return static_cast<unsigned long>(0); }

      static  unsigned long 
      quiet_NaN() throw() { return static_cast<unsigned long>(0); }

      static  unsigned long 
      signaling_NaN() throw() { return static_cast<unsigned long>(0); }

      static  unsigned long 
      denorm_min() throw() { return static_cast<unsigned long>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style 
       = round_toward_zero;
    };

  
  template<>
    struct numeric_limits<long long>
    {
      static const bool is_specialized = true;

      static  long long 
      min() throw() { return -0x7fffffffffffffff - 1; }

      static  long long 
      max() throw() { return 0x7fffffffffffffff; }


      static const int digits 
       = (sizeof(long long) * 8 - ((long long)(-1) < 0));
      static const int digits10 
       = ((sizeof(long long) * 8 - ((long long)(-1) < 0)) * 643L / 2136);
      static const bool is_signed = true;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static  long long 
      epsilon() throw() { return 0; }

      static  long long 
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm 
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static  long long 
      infinity() throw() { return static_cast<long long>(0); }

      static  long long 
      quiet_NaN() throw() { return static_cast<long long>(0); }

      static  long long 
      signaling_NaN() throw() { return static_cast<long long>(0); }

      static  long long 
      denorm_min() throw() { return static_cast<long long>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style 
       = round_toward_zero;
    };

  
  template<>
    struct numeric_limits<unsigned long long>
    {
      static const bool is_specialized = true;

      static  unsigned long long 
      min() throw() { return 0; }

      static  unsigned long long 
      max() throw() { return 0x7fffffffffffffff * 2ULL + 1; }


      static const int digits 
       = (sizeof(unsigned long long) * 8 - ((unsigned long long)(-1) < 0));
      static const int digits10 
       = ((sizeof(unsigned long long) * 8 - ((unsigned long long)(-1) < 0)) * 643L / 2136);
      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static  unsigned long long 
      epsilon() throw() { return 0; }

      static  unsigned long long 
      round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm 
       = denorm_absent;
      static const bool has_denorm_loss = false;

      static  unsigned long long 
      infinity() throw() { return static_cast<unsigned long long>(0); }

      static  unsigned long long 
      quiet_NaN() throw() { return static_cast<unsigned long long>(0); }

      static  unsigned long long 
      signaling_NaN() throw() { return static_cast<unsigned long long>(0); }

      static  unsigned long long 
      denorm_min() throw() { return static_cast<unsigned long long>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style 
       = round_toward_zero;
    };

  
  template<>
    struct numeric_limits<float>
    {
      static const bool is_specialized = true;

      static  float 
      min() throw() { return 1.17549435e-38F; }

      static  float 
      max() throw() { return 3.40282347e+38F; }


      static const int digits = 24;
      static const int digits10 = 6;
      static const bool is_signed = true;
      static const bool is_integer = false;
      static const bool is_exact = false;
      static const int radix = 2;

      static  float 
      epsilon() throw() { return 1.19209290e-7F; }

      static  float 
      round_error() throw() { return 0.5F; }

      static const int min_exponent = -125;
      static const int min_exponent10 = -37;
      static const int max_exponent = 128;
      static const int max_exponent10 = 38;

      static const bool has_infinity = 1;
      static const bool has_quiet_NaN = 1;
      static const bool has_signaling_NaN = has_quiet_NaN;
      static const float_denorm_style has_denorm
	= bool(1) ? denorm_present : denorm_absent;
      static const bool has_denorm_loss 
       = false;

      static  float 
      infinity() throw() { return __builtin_huge_valf (); }

      static  float 
      quiet_NaN() throw() { return __builtin_nanf (""); }

      static  float 
      signaling_NaN() throw() { return __builtin_nansf (""); }

      static  float 
      denorm_min() throw() { return 1.40129846e-45F; }

      static const bool is_iec559
	= has_infinity && has_quiet_NaN && has_denorm == denorm_present;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      static const bool traps = false;
      static const bool tinyness_before 
       = false;
      static const float_round_style round_style 
       = round_to_nearest;
    };


  
  template<>
    struct numeric_limits<double>
    {
      static const bool is_specialized = true;

      static  double 
      min() throw()  { return 2.2250738585072014e-308; }

      static  double 
      max() throw() { return 1.7976931348623157e+308; }


      static const int digits = 53;
      static const int digits10 = 15;
      static const bool is_signed = true;
      static const bool is_integer = false;
      static const bool is_exact = false;
      static const int radix = 2;

      static  double 
      epsilon() throw() { return 2.2204460492503131e-16; }

      static  double 
      round_error() throw() { return 0.5; }

      static const int min_exponent = -1021;
      static const int min_exponent10 = -307;
      static const int max_exponent = 1024;
      static const int max_exponent10 = 308;

      static const bool has_infinity = 1;
      static const bool has_quiet_NaN = 1;
      static const bool has_signaling_NaN = has_quiet_NaN;
      static const float_denorm_style has_denorm
	= bool(1) ? denorm_present : denorm_absent;
      static const bool has_denorm_loss 
        = false;

      static  double 
      infinity() throw() { return __builtin_huge_val(); }

      static  double 
      quiet_NaN() throw() { return __builtin_nan (""); }

      static  double 
      signaling_NaN() throw() { return __builtin_nans (""); }

      static  double 
      denorm_min() throw() { return 4.9406564584124654e-324; }

      static const bool is_iec559
	= has_infinity && has_quiet_NaN && has_denorm == denorm_present;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      static const bool traps = false;
      static const bool tinyness_before 
       = false;
      static const float_round_style round_style 
       = round_to_nearest;
    };


  
  template<>
    struct numeric_limits<long double>
    {
      static const bool is_specialized = true;

      static  long double 
      min() throw() { return 3.36210314311209350626e-4932L; }

      static  long double 
      max() throw() { return 1.18973149535723176502e+4932L; }


      static const int digits = 64;
      static const int digits10 = 18;
      static const bool is_signed = true;
      static const bool is_integer = false;
      static const bool is_exact = false;
      static const int radix = 2;

      static  long double 
      epsilon() throw() { return 1.08420217248550443401e-19L; }

      static  long double 
      round_error() throw() { return 0.5L; }

      static const int min_exponent = -16381;
      static const int min_exponent10 = -4931;
      static const int max_exponent = 16384;
      static const int max_exponent10 = 4932;

      static const bool has_infinity = 1;
      static const bool has_quiet_NaN = 1;
      static const bool has_signaling_NaN = has_quiet_NaN;
      static const float_denorm_style has_denorm
	= bool(1) ? denorm_present : denorm_absent;
      static const bool has_denorm_loss
	= false;

      static  long double 
      infinity() throw() { return __builtin_huge_vall (); }

      static  long double 
      quiet_NaN() throw() { return __builtin_nanl (""); }

      static  long double 
      signaling_NaN() throw() { return __builtin_nansl (""); }

      static  long double 
      denorm_min() throw() { return 3.64519953188247460253e-4951L; }

      static const bool is_iec559
	= has_infinity && has_quiet_NaN && has_denorm == denorm_present;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      static const bool traps = false;
      static const bool tinyness_before = 
					 false;
      static const float_round_style round_style = 
						      round_to_nearest;
    };



} 























 



 


namespace olb {













 
template<typename T, template<typename U> class Lattice>
class Cell {
public:
  
  typedef T fPop[Lattice<T>::q];
  
  typedef descriptors::ExternalFieldArray <
  T, typename Lattice<T>::ExternalField > External;
public:
  
  Cell();
  
  Cell(Dynamics<T,Lattice>* dynamics_);
public:
  
   
  T& operator[](int iPop) {
    ;
    return f[iPop];
  }
  
   
  T const& operator[](int iPop) const {
    ;
    return f[iPop];
  }
  
  
 
  Cell<T,Lattice>& attributeF(Cell<T,Lattice> const& rhs) {
    for (unsigned iPop=0; iPop < Lattice<T>::q; ++iPop) {
      f[iPop] = rhs.f[iPop];
    }
    return *this;
  };
  
  



 
  Cell<T,Lattice>& attributeValues(Cell<T,Lattice> const& rhs) {
    attributeF(rhs);
    for (int iExt=0; iExt < Lattice<T>::ExternalField::numScalars; ++iExt) {
      *external.get(iExt) = *rhs.external.get(iExt);
    }
    return *this;
  };
  
  T* getExternal(int offset) {
    ;
    return external.get(offset);
  }
  
  T const* getExternal(int offset) const {
    ;
    return external.get(offset);
  }
  
  

 
  void defineDynamics(Dynamics<T,Lattice>* dynamics_);
  
  Dynamics<T,Lattice> const* getDynamics() const;
  
  Dynamics<T,Lattice>* getDynamics();
  
  bool takesStatistics() const {
    return takesStat;
  }
  
  void specifyStatisticsStatus(bool status) {
    takesStat = status;
  }

  
  
public:
  
  void collide(LatticeStatistics<T>& statistics) {
    ;
    dynamics->collide(*this, statistics);
  }
  
  void staticCollide(const T u[Lattice<T>::d], LatticeStatistics<T>& statistics)
  {
    ;
    dynamics->staticCollide(*this, u, statistics);
  }

  
  T computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
  {
    ;
    return dynamics->computeEquilibrium(iPop, rho, u, uSqr);
  }

  
  
 
  T computeRho() const {
    ;
    return dynamics->computeRho(*this);
  }
  
  
 
  void computeU(T u[Lattice<T>::d]) const {
    ;
    dynamics->computeU(*this, u);
  }
  
   
  void computeStress (
    T pi[util::TensorVal<Lattice<T> >::n]) const
  {
    ;
    T rho, u[Lattice<T>::d];
    dynamics->computeRhoU(*this, rho, u);
    dynamics->computeStress(*this, rho, u, pi);
  }
  
  

 
  void computeRhoU(T& rho, T u[Lattice<T>::d]) const {
    ;
    dynamics->computeRhoU(*this, rho, u);
  }
  
  


 
  void computeAllMomenta (
    T& rho, T u[Lattice<T>::d],
    T pi[util::TensorVal<Lattice<T> >::n] ) const
  {
    ;
    dynamics->computeAllMomenta(*this, rho, u, pi);
  }
  
  



 
  void computePopulations(T* f) const {
    ;
    dynamics->computePopulations(*this, f);
  }
  
  



 
  void computeExternalField(int pos, int size, T* ext) const {
    ;
    dynamics->computeExternalField(*this, pos, size, ext);
  }
  
  
 
  void defineRho(T rho) {
    ;
    dynamics->defineRho(*this, rho);
  }
  
  
 
  void defineU(const T u[Lattice<T>::d]) {
    ;
    dynamics->defineU(*this, u);
  }
  
   
  void defineStress (
    const T pi[util::TensorVal<Lattice<T> >::n])
  {
    ;
    T rho, u[Lattice<T>::d];
    dynamics->computeRhoU(*this, rho, u);
    dynamics->defineAllMomenta(*this, rho, u, pi);
  }
  
  

 
  void defineRhoU(T rho, const T u[Lattice<T>::d]) {
    ;
    dynamics->defineRhoU(*this, rho, u);
  }
  
  


 
  void defineAllMomenta (
    T rho, const T u[Lattice<T>::d],
    const T pi[util::TensorVal<Lattice<T> >::n] )
  {
    ;
    dynamics->defineAllMomenta(*this, rho, u, pi);
  }
  
  



 
  void definePopulations(const T* f) {
    ;
    dynamics->definePopulations(*this, f);
  }
  
  



 
  void defineExternalField(int pos, int size, const T* ext) {
    ;
    dynamics->defineExternalField(*this, pos, size, ext);
  }
  
  void iniEquilibrium(T rho, const T u[Lattice<T>::d]) {
    ;
    dynamics->iniEquilibrium(*this, rho, u);
  }
  
  void revert();
  void serialize(T* data) const;
  void unSerialize(T const* data);
private:
  void iniPop();
  void iniExternal();
private:
  fPop                 f;         
  External             external;  
  bool                 takesStat; 
  Dynamics<T,Lattice>* dynamics;  
};

template<typename T, template<typename U> class Lattice>
struct WriteCellFunctional {
  virtual ~WriteCellFunctional() { };
  virtual void apply(Cell<T,Lattice>& cell) const =0;
};

}  






















 






 



namespace olb {



template<typename T, class Descriptor> struct lbDynamicsHelpers;
template<typename T, template<typename U> class Lattice> struct lbExternalHelpers;
template<typename T, template<typename U> class Lattice> struct lbLatticeHelpers;


template<typename T, template<typename U> class Lattice>
struct lbHelpers {

  static T equilibrium(int iPop, T rho, const T u[Lattice<T>::d], const T uSqr) {
    return lbDynamicsHelpers<T,typename Lattice<T>::BaseDescriptor>
           ::equilibrium(iPop, rho, u, uSqr);
  }

  static T incEquilibrium(int iPop, const T j[Lattice<T>::d], const T jSqr, const T pressure) {
    return lbDynamicsHelpers<T,typename Lattice<T>::BaseDescriptor>
           ::incEquilibrium(iPop, j, jSqr, pressure);
  }

  static void computeFneq ( Cell<T,Lattice> const& cell,
                            T fNeq[Lattice<T>::q], T rho, const T u[Lattice<T>::d] )
  {
    lbDynamicsHelpers<T,typename Lattice<T>::BaseDescriptor>
    ::computeFneq(&cell[0], fNeq, rho, u);
  }

  static T bgkCollision(Cell<T,Lattice>& cell, T rho, const T u[Lattice<T>::d], T omega)
  {
    return lbDynamicsHelpers<T,typename Lattice<T>::BaseDescriptor>
           ::bgkCollision(&cell[0], rho, u, omega);
  }

  static T incBgkCollision(Cell<T,Lattice>& cell, T pressure, const T j[Lattice<T>::d], T omega)
  {
    return lbDynamicsHelpers<T,typename Lattice<T>::BaseDescriptor>
           ::incBgkCollision(&cell[0], pressure, j, omega);
  }

  static T constRhoBgkCollision(Cell<T,Lattice>& cell,
                                T rho, const T u[Lattice<T>::d], T ratioRho, T omega)
  {
    return lbDynamicsHelpers<T,typename Lattice<T>::BaseDescriptor>
           ::constRhoBgkCollision(&cell[0], rho, u, ratioRho, omega);
  }

  static T computeRho(Cell<T,Lattice> const& cell) {
    return lbDynamicsHelpers<T,typename Lattice<T>::BaseDescriptor>
           ::computeRho(&cell[0]);
  }

  static void computeJ(Cell<T,Lattice> const& cell, T j[Lattice<T>::d] ) {
    lbDynamicsHelpers<T,typename Lattice<T>::BaseDescriptor>
    ::computeJ(&cell[0], j);
  }

  static void computeRhoU(Cell<T,Lattice> const& cell, T& rho, T u[Lattice<T>::d])
  {
    lbDynamicsHelpers<T,typename Lattice<T>::BaseDescriptor>
    ::computeRhoU(&cell[0], rho, u);
  }

  static void computeStress(Cell<T,Lattice> const& cell, T rho, const T u[Lattice<T>::d],
                            T pi[util::TensorVal<Lattice<T> >::n] )
  {
    lbDynamicsHelpers<T,typename Lattice<T>::BaseDescriptor>
    ::computeStress(&cell[0], rho, u, pi);
  }

  static void computeAllMomenta(Cell<T,Lattice> const& cell, T& rho, T u[Lattice<T>::d],
                                T pi[util::TensorVal<Lattice<T> >::n] )
  {
    lbDynamicsHelpers<T,typename Lattice<T>::BaseDescriptor>
    ::computeAllMomenta(&cell[0], rho, u, pi);
  }

  static void modifyVelocity(Cell<T,Lattice>& cell, const T newU[Lattice<T>::d]) {
    lbDynamicsHelpers<T,typename Lattice<T>::BaseDescriptor>
    ::modifyVelocity(&cell[0], newU);
  }

  static void addExternalForce(Cell<T,Lattice>& cell, const T u[Lattice<T>::d], T omega, T amplitude=(T)1)
  {
    lbExternalHelpers<T,Lattice>::addExternalForce(cell, u, omega, amplitude);
  }

  static void swapAndStream2D(Cell<T,Lattice> **grid, int iX, int iY)
  {
    lbLatticeHelpers<T,Lattice>::swapAndStream2D(grid, iX, iY);
  }

  static void swapAndStream3D(Cell<T,Lattice> ***grid, int iX, int iY, int iZ)
  {
    lbLatticeHelpers<T,Lattice>::swapAndStream3D(grid, iX, iY, iZ);
  }

};  



template<typename T, class Descriptor>
struct lbDynamicsHelpers {
  
  static T equilibrium(int iPop, T rho, const T u[Descriptor::d], const T uSqr) {
    T c_u = T();
    for (int iD=0; iD < Descriptor::d; ++iD) {
      c_u += Descriptor::c[iPop][iD]*u[iD];
    }
    return rho * Descriptor::t[iPop] * (
             (T)1 + Descriptor::invCs2 * c_u +
             Descriptor::invCs2 * Descriptor::invCs2/(T)2 * c_u*c_u -
             Descriptor::invCs2/(T)2 * uSqr
           ) - Descriptor::t[iPop];
  }

  static T incEquilibrium( int iPop, const T j[Descriptor::d],
                           const T jSqr, const T pressure )
  {
    T c_j = T();
    for (int iD=0; iD < Descriptor::d; ++iD) {
      c_j += Descriptor::c[iPop][iD]*j[iD];
    }
    T rho = (T)1 + pressure*Descriptor::invCs2;
    return Descriptor::t[iPop] * ( rho +
                                   Descriptor::invCs2 * c_j +
                                   Descriptor::invCs2 * Descriptor::invCs2/(T)2 * c_j*c_j -
                                   Descriptor::invCs2/(T)2 * jSqr
                                 ) - Descriptor::t[iPop];
  }

  static void computeFneq(T const* cell, T fNeq[Descriptor::q], T rho, const T u[Descriptor::d]) {
    const T uSqr = util::normSqr<T,Descriptor::d>(u);
    for (int iPop=0; iPop < Descriptor::q; ++iPop) {
      fNeq[iPop] = cell[iPop] - equilibrium(iPop, rho, u, uSqr);
    }
  }

  
  static T bgkCollision(T* cell, T rho, const T u[Descriptor::d], T omega) {
    const T uSqr = util::normSqr<T,Descriptor::d>(u);
    for (int iPop=0; iPop < Descriptor::q; ++iPop) {
      cell[iPop] *= (T)1-omega;
      cell[iPop] += omega * lbDynamicsHelpers<T,Descriptor>::equilibrium (
                      iPop, rho, u, uSqr );
    }
    return uSqr;
  }

  
  static T incBgkCollision(T* cell, T pressure, const T j[Descriptor::d], T omega) {
    const T jSqr = util::normSqr<T,Descriptor::d>(j);
    for (int iPop=0; iPop < Descriptor::q; ++iPop) {
      cell[iPop] *= (T)1-omega;
      cell[iPop] += omega * lbDynamicsHelpers<T,Descriptor>::incEquilibrium (
                      iPop, j, jSqr, pressure );
    }
    return jSqr;
  }

  
  static T constRhoBgkCollision(T* cell, T rho, const T u[Descriptor::d], T ratioRho, T omega) {
    const T uSqr = util::normSqr<T,Descriptor::d>(u);
    for (int iPop=0; iPop < Descriptor::q; ++iPop) {
      T feq = lbDynamicsHelpers<T,Descriptor>::equilibrium(iPop, rho, u, uSqr );
      cell[iPop] =
        ratioRho*(feq+Descriptor::t[iPop])-Descriptor::t[iPop] +
        ((T)1-omega)*(cell[iPop]-feq);
    }
    return uSqr;
  }

  
  static T computeRho(T const* cell) {
    T rho = T();
    for (int iPop=0; iPop < Descriptor::q; ++iPop) {
      rho += cell[iPop];
    }
    rho += (T)1;
    return rho;
  }

  
  static void computeJ(T const* cell, T j[Descriptor::d]) {
    for (int iD=0; iD < Descriptor::d; ++iD) {
      j[iD] = T();
    }
    for (int iPop=0; iPop < Descriptor::q; ++iPop) {
      for (int iD=0; iD < Descriptor::d; ++iD) {
        j[iD] += cell[iPop]*Descriptor::c[iPop][iD];
      }
    }
  }

  
  static void computeRhoU(T const* cell, T& rho, T u[Descriptor::d]) {
    rho = T();
    for (int iD=0; iD < Descriptor::d; ++iD) {
      u[iD] = T();
    }
    for (int iPop=0; iPop < Descriptor::q; ++iPop) {
      rho += cell[iPop];
      for (int iD=0; iD < Descriptor::d; ++iD) {
        u[iD] += cell[iPop]*Descriptor::c[iPop][iD];
      }
    }
    rho += (T)1;
    for (int iD=0; iD < Descriptor::d; ++iD) {
      u[iD] /= rho;
    }
  }

  
  static void computeStress(T const* cell, T rho, const T u[Descriptor::d],
                            T pi[util::TensorVal<Descriptor>::n] )
  {
    int iPi = 0;
    for (int iAlpha=0; iAlpha < Descriptor::d; ++iAlpha) {
      for (int iBeta=iAlpha; iBeta < Descriptor::d; ++iBeta) {
        pi[iPi] = T();
        for (int iPop=0; iPop < Descriptor::q; ++iPop) {
          pi[iPi] += Descriptor::c[iPop][iAlpha]*
                     Descriptor::c[iPop][iBeta] * cell[iPop];
        }
        
        pi[iPi] -= rho*u[iAlpha]*u[iBeta];
        if (iAlpha==iBeta) {
          pi[iPi] -= 1./Descriptor::invCs2*(rho-(T)1);
        }
        ++iPi;
      }
    }
  }

  
  static void computeAllMomenta(T const* cell, T& rho, T u[Descriptor::d],
                                T pi[util::TensorVal<Descriptor>::n] )
  {
    computeRhoU(cell, rho, u);
    computeStress(cell, rho, u, pi);
  }

  static void modifyVelocity(T* cell, const T newU[Descriptor::d]) {
    T rho, oldU[Descriptor::d];
    computeRhoU(cell, rho, oldU);
    const T oldUSqr = util::normSqr<T,Descriptor::d>(oldU);
    const T newUSqr = util::normSqr<T,Descriptor::d>(newU);
    for (int iPop=0; iPop<Descriptor::q; ++iPop) {
      cell[iPop] = cell[iPop]
                   - equilibrium(iPop, rho, oldU, oldUSqr)
                   + equilibrium(iPop, rho, newU, newUSqr);
    }
  }

};  


template<typename T, template<typename U> class Lattice>
struct lbExternalHelpers {
  
  static void addExternalForce(Cell<T,Lattice>& cell, const T u[Lattice<T>::d], T omega, T amplitude) {
    static const int forceBeginsAt = Lattice<T>::ExternalField::forceBeginsAt;
    T* force = cell.getExternal(forceBeginsAt);
    for (int iPop=0; iPop < Lattice<T>::q; ++iPop) {
      T c_u = T();
      for (int iD=0; iD < Lattice<T>::d; ++iD) {
        c_u += Lattice<T>::c[iPop][iD]*u[iD];
      }
      c_u *= Lattice<T>::invCs2 * Lattice<T>::invCs2;
      T forceTerm = T();
      for (int iD=0; iD < Lattice<T>::d; ++iD) {
        forceTerm +=
          (   (Lattice<T>::c[iPop][iD]-u[iD]) * Lattice<T>::invCs2
              + c_u * Lattice<T>::c[iPop][iD]
          )
          * force[iD];
      }
      forceTerm *= Lattice<T>::t[iPop];
      forceTerm *= 1-omega/(T)2;
      forceTerm *= amplitude;
      cell[iPop] += forceTerm;
    }
  }
};  


template<typename T, template<typename U> class Lattice>
struct lbLatticeHelpers {
  
  static void swapAndStream2D(Cell<T,Lattice> **grid, int iX, int iY)
  {
    const int half = Lattice<T>::q/2;
    for (int iPop=1; iPop<=half; ++iPop) {
      int nextX = iX + Lattice<T>::c[iPop][0];
      int nextY = iY + Lattice<T>::c[iPop][1];
      T fTmp                   = grid[iX][iY][iPop];
      grid[iX][iY][iPop]       = grid[iX][iY][iPop+half];
      grid[iX][iY][iPop+half]  = grid[nextX][nextY][iPop];
      grid[nextX][nextY][iPop] = fTmp;
    }
  }

  
  static void swapAndStream3D(Cell<T,Lattice> ***grid,
                              int iX, int iY, int iZ)
  {
    const int half = Lattice<T>::q/2;
    for (int iPop=1; iPop<=half; ++iPop) {
      int nextX = iX + Lattice<T>::c[iPop][0];
      int nextY = iY + Lattice<T>::c[iPop][1];
      int nextZ = iZ + Lattice<T>::c[iPop][2];
      T fTmp                          = grid[iX][iY][iZ][iPop];
      grid[iX][iY][iZ][iPop]          = grid[iX][iY][iZ][iPop+half];
      grid[iX][iY][iZ][iPop+half]     = grid[nextX][nextY][nextZ][iPop];
      grid[nextX][nextY][nextZ][iPop] = fTmp;
    }
  }
};


template<typename T, template<typename U> class Lattice, int direction, int orientation>
struct BoundaryHelpers {
  static void computeStress (
    Cell<T,Lattice> const& cell, T rho, const T u[Lattice<T>::d],
    T pi[util::TensorVal<Lattice<T> >::n] )
  {
    typedef Lattice<T> L;
    const T uSqr = util::normSqr<T,L::d>(u);

    std::vector<int> const& onWallIndices = util::subIndex<L, direction, 0>();
    std::vector<int> const& normalIndices = util::subIndex<L, direction, orientation>();

    T fNeq[Lattice<T>::q];
    for (unsigned fIndex=0; fIndex<onWallIndices.size(); ++fIndex) {
      int iPop = onWallIndices[fIndex];
      fNeq[iPop] =
        cell[iPop] -
        lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr);
    }
    for (unsigned fIndex=0; fIndex<normalIndices.size(); ++fIndex) {
      int iPop = normalIndices[fIndex];
      if (iPop == 0) {
        fNeq[iPop] = T();  
      }
      else {
        fNeq[iPop] =
          cell[iPop] -
          lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr);
      }
    }

    int iPi = 0;
    for (int iAlpha=0; iAlpha<L::d; ++iAlpha) {
      for (int iBeta=iAlpha; iBeta<L::d; ++iBeta) {
        pi[iPi] = T();
        for (unsigned fIndex=0; fIndex<onWallIndices.size(); ++fIndex)
        {
          const int iPop = onWallIndices[fIndex];
          pi[iPi] +=
            L::c[iPop][iAlpha]*L::c[iPop][iBeta]*fNeq[iPop];
        }
        for (unsigned fIndex=0; fIndex<normalIndices.size(); ++fIndex)
        {
          const int iPop = normalIndices[fIndex];
          pi[iPi] += (T)2 * L::c[iPop][iAlpha]*L::c[iPop][iBeta]*
                     fNeq[iPop];
        }
        ++iPi;
      }
    }
  }

};  

}  


























 




 


namespace olb {


template<typename T>
struct lbDynamicsHelpers<T, descriptors::D2Q9DescriptorBase<T> > {

  static T equilibrium( int iPop, T rho, const T u[2], T uSqr ) {
    typedef descriptors::D2Q9DescriptorBase<T> L;
    T c_u = L::c[iPop][0]*u[0] + L::c[iPop][1]*u[1];
    return rho * L::t[iPop] * (
             1. + 3.*c_u + 4.5*c_u*c_u - 1.5*uSqr )
           - L::t[iPop];
  }

  static T incEquilibrium( int iPop, const T j[2], const T jSqr, const T pressure ) {
    typedef descriptors::D2Q9DescriptorBase<T> L;
    T c_j = L::c[iPop][0]*j[0] + L::c[iPop][1]*j[1];
    return L::t[iPop] * (
             3.*pressure + 3.*c_j + 4.5*c_j*c_j - 1.5*jSqr )
           - L::t[iPop];
  }

  static void computeFneq ( T const* cell, T fNeq[9], T rho, const T u[2] ) {
    const T uSqr = u[0]*u[0] + u[1]*u[1];
    for (int iPop=0; iPop < 9; ++iPop) {
      fNeq[iPop] = cell[iPop] - equilibrium(iPop, rho, u, uSqr);
    }
  }

  static T bgkCollision ( T* cell, T rho, const T u[2], T omega) {
    T uxSqr = u[0]*u[0];
    T uySqr = u[1]*u[1];

    T ux_ = (T)3 * u[0];
    T uy_ = (T)3 * u[1];

    T uxSqr_ = (T)3 * uxSqr;
    T uySqr_ = (T)3 * uySqr;
    T uxSqr__ = (T)3/(T)2 * uxSqr;
    T uySqr__ = (T)3/(T)2 * uySqr;
    T uSqr_ = uxSqr__ + uySqr__;

    T uxPySqr_ = (T)9/(T)2 * (u[0]+u[1])*(u[0]+u[1]);
    T uxMySqr_ = (T)9/(T)2 * (u[0]-u[1])*(u[0]-u[1]);

    T rho_ = (T)4/(T)9 * rho;
    T cf_  = (T)4/(T)9 * (rho-(T)1);

    cell[0] *= (T)1-omega;
    cell[0] += omega*(cf_ + rho_*(- uxSqr__ - uySqr__));

    rho_ = (T)1/(T)9 * rho;
    cf_  = (T)1/(T)9 * (rho-(T)1);

    cell[6] *= (T)1-omega;
    cell[6] += omega*(cf_ + rho_*(ux_ + uxSqr_ - uySqr__));
    cell[8] *= (T)1-omega;
    cell[8] += omega*(cf_ + rho_*(uy_ + uySqr_ - uxSqr__));
    cell[2] *= (T)1-omega;
    cell[2] += omega*(cf_ + rho_*(-ux_ + uxSqr_ - uySqr__));
    cell[4] *= (T)1-omega;
    cell[4] += omega*(cf_ + rho_*(-uy_ + uySqr_ - uxSqr__));

    rho_ = (T)1/(T)36 * rho;
    cf_  = (T)1/(T)36 * (rho-(T)1);

    cell[7] *= (T)1-omega;
    cell[7] += omega*(cf_ + rho_*(ux_ + uy_ + uxPySqr_ - uSqr_));
    cell[1] *= (T)1-omega;
    cell[1] += omega*(cf_ + rho_*(-ux_ + uy_ + uxMySqr_ - uSqr_));
    cell[3] *= (T)1-omega;
    cell[3] += omega*(cf_ + rho_*(-ux_ - uy_ + uxPySqr_ - uSqr_));
    cell[5] *= (T)1-omega;
    cell[5] += omega*(cf_ + rho_*(ux_ - uy_ + uxMySqr_ - uSqr_));

    return uxSqr + uySqr;
  }

  static T incBgkCollision ( T* cell, T pressure, const T j[2], T omega) {
    const T jSqr = util::normSqr<T,descriptors::D2Q9DescriptorBase<T>::d>(j);
    for (int iPop=0; iPop < descriptors::D2Q9DescriptorBase<T>::q; ++iPop) {
      cell[iPop] *= (T)1-omega;
      cell[iPop] += omega * lbHelpers<T,descriptors::D2Q9DescriptorBase>::incEquilibrium (
                      iPop, j, jSqr, pressure );
    }
    return jSqr;
  }

  static T constRhoBgkCollision(T* cell, T rho, const T u[2], T ratioRho, T omega) {
    const T uSqr = util::normSqr<T,descriptors::D2Q9DescriptorBase<T>::d>(u);
    for (int iPop=0; iPop < descriptors::D2Q9DescriptorBase<T>::q; ++iPop) {
      T feq = lbHelpers<T,descriptors::D2Q9DescriptorBase>::equilibrium(iPop, rho, u, uSqr );
      cell[iPop] = ratioRho*(feq+descriptors::D2Q9DescriptorBase<T>::t[iPop])
                   -descriptors::D2Q9DescriptorBase<T>::t[iPop] +
                   ((T)1-omega)*(cell[iPop]-feq);
    }
    return uSqr;
  }


  static void partial_rho ( T const* cell,
                            T& lineX_P1, T& lineX_0, T& lineX_M1, T& lineY_P1, T& lineY_M1 )
  {
    lineX_P1  = cell[5] + cell[6] + cell[7];
    lineX_0   = cell[0] + cell[4] + cell[8];
    lineX_M1  = cell[1] + cell[2] + cell[3];

    lineY_P1  = cell[7] + cell[8] + cell[1];
    lineY_M1  = cell[3] + cell[4] + cell[5];
  }

  static T computeRho(T const* cell) {
    T rho = cell[0] + cell[1] + cell[2] + cell[3] + cell[4]
            + cell[5] + cell[6] + cell[7] + cell[8] + (T)1;
    return rho;
  }

  static void computeRhoU(T const* cell, T& rho, T u[2]) {
    T lineX_P1, lineX_0, lineX_M1, lineY_P1, lineY_M1;
    partial_rho(cell, lineX_P1, lineX_0, lineX_M1, lineY_P1, lineY_M1);

    rho = lineX_P1 + lineX_0 + lineX_M1 + (T)1;
    u[0]  = (lineX_P1 - lineX_M1)/rho;
    u[1]  = (lineY_P1 - lineY_M1)/rho;
  }

  static void computeJ(T const* cell, T j[2] ) {
    T lineX_P1, lineX_M1, lineY_P1, lineY_M1;

    lineX_P1  = cell[5] + cell[6] + cell[7];
    lineX_M1  = cell[1] + cell[2] + cell[3];
    lineY_P1  = cell[7] + cell[8] + cell[1];
    lineY_M1  = cell[3] + cell[4] + cell[5];

    j[0]  = (lineX_P1 - lineX_M1);
    j[1]  = (lineY_P1 - lineY_M1);
  }

  static void computeStress(T const* cell, T rho, const T u[2], T pi[3]) {
    typedef descriptors::D2Q9DescriptorBase<T> L;
    
    
    using util::tensorIndices2D::xx;
    using util::tensorIndices2D::yy;
    using util::tensorIndices2D::xy;

    T lineX_P1, lineX_0, lineX_M1, lineY_P1, lineY_M1;
    partial_rho(cell, lineX_P1, lineX_0, lineX_M1, lineY_P1, lineY_M1);

    pi[xx] = lineX_P1+lineX_M1 - 1./L::invCs2*(rho-(T)1) - rho*u[0]*u[0];
    pi[yy] = lineY_P1+lineY_M1 - 1./L::invCs2*(rho-(T)1) - rho*u[1]*u[1];
    pi[xy] = -cell[1] + cell[3] - cell[5] + cell[7]   - rho*u[0]*u[1];
  }

  static void computeAllMomenta(T const* cell, T& rho, T u[2], T pi[3] ) {
    typedef descriptors::D2Q9DescriptorBase<T> L;
    
    
    using util::tensorIndices2D::xx;
    using util::tensorIndices2D::yy;
    using util::tensorIndices2D::xy;

    T lineX_P1, lineX_0, lineX_M1, lineY_P1, lineY_M1;
    partial_rho(cell, lineX_P1, lineX_0, lineX_M1, lineY_P1, lineY_M1);

    rho = lineX_P1 + lineX_0 + lineX_M1 + (T)1;

    T rhoU0 = (lineX_P1 - lineX_M1);
    T rhoU1 = (lineY_P1 - lineY_M1);
    u[0]  = rhoU0/rho;
    u[1]  = rhoU1/rho;

    pi[xx] = lineX_P1 + lineX_M1 - 1./L::invCs2*(rho-(T)1) - rhoU0*u[0];
    pi[yy] = lineY_P1 + lineY_M1 - 1./L::invCs2*(rho-(T)1) - rhoU1*u[1];
    pi[xy] = -cell[1] + cell[3] - cell[5] + cell[7]        - rhoU0*u[1];
  }

  static void modifyVelocity(T* cell, const T newU[2]) {
    T rho, oldU[2];
    computeRhoU(cell, rho, oldU);
    const T oldUSqr = util::normSqr<T,2>(oldU);
    const T newUSqr = util::normSqr<T,2>(newU);
    for (int iPop=0; iPop<9; ++iPop) {
      cell[iPop] = cell[iPop]
                   - equilibrium(iPop, rho, oldU, oldUSqr)
                   + equilibrium(iPop, rho, newU, newUSqr);
    }
  }

};  


template<typename T>
struct lbExternalHelpers<T, descriptors::ForcedD2Q9Descriptor> {

  static void addExternalForce(
    Cell<T,descriptors::ForcedD2Q9Descriptor>& cell,
    const T u[descriptors::ForcedD2Q9Descriptor<T>::d], T omega, T amplitude)
  {
    static const int forceBeginsAt
    = descriptors::ForcedD2Q9Descriptor<T>::ExternalField::forceBeginsAt;
    T* force = cell.getExternal(forceBeginsAt);
    T mu = amplitude*((T)1-omega/(T)2);

    cell[0] += mu *(T)4/(T)3  *( force[0] * (-  u[0]             ) +
                                 force[1] * (        -   u[1]    )   );
    cell[1] += mu *(T)1/(T)12 *( force[0] * ( 2*u[0] - 3*u[1] - 1) +
                                 force[1] * (-3*u[0] + 2*u[1] + 1)   );
    cell[2] += mu *(T)1/(T)3  *( force[0] * ( 2*u[0]          - 1) +
                                 force[1] * (        -   u[1]    )   );
    cell[3] += mu *(T)1/(T)12 *( force[0] * ( 2*u[0] + 1*u[1] - 1) +
                                 force[1] * (   u[0] + 2*u[1] - 1)   );
    cell[4] += mu *(T)1/(T)3  *( force[0] * (-  u[0]             ) +
                                 force[1] * (        + 2*u[1] - 1)   );
    cell[5] += mu *(T)1/(T)12 *( force[0] * ( 2*u[0] -   u[1] + 1) +
                                 force[1] * (-1*u[0] + 2*u[1] - 1)   );
    cell[6] += mu *(T)1/(T)3  *( force[0] * ( 2*u[0]          + 1) +
                                 force[1] * (   u[0] -   u[1]    )   );
    cell[7] += mu *(T)1/(T)12 *( force[0] * ( 2*u[0] +   u[1] + 1) +
                                 force[1] * (   u[0] + 2*u[1] + 1)   );
    cell[8] += mu *(T)1/(T)3  *( force[0] * (-  u[0]             ) +
                                 force[1] * (        + 2*u[1] + 1)   );
  }
};




template<typename T>
struct lbLatticeHelpers<T, descriptors::D2Q9Descriptor> {

  static void swapAndStreamCell (
    Cell<T,descriptors::D2Q9Descriptor> **grid,
    int iX, int iY, int nX, int nY, int iPop, T& fTmp )
  {
    fTmp                 = grid[iX][iY][iPop];
    grid[iX][iY][iPop]   = grid[iX][iY][iPop+4];
    grid[iX][iY][iPop+4] = grid[nX][nY][iPop];
    grid[nX][nY][iPop]   = fTmp;
  }

  static void swapAndStream2D (
    Cell<T,descriptors::D2Q9Descriptor> **grid, int iX, int iY )
  {
    T fTmp;
    swapAndStreamCell(grid, iX, iY, iX-1, iY+1, 1, fTmp);
    swapAndStreamCell(grid, iX, iY, iX-1, iY,   2, fTmp);
    swapAndStreamCell(grid, iX, iY, iX-1, iY-1, 3, fTmp);
    swapAndStreamCell(grid, iX, iY, iX,   iY-1, 4, fTmp);
  }
};

template<typename T>
struct lbLatticeHelpers<T, descriptors::ForcedD2Q9Descriptor> {

  static void swapAndStreamCell (
    Cell<T,descriptors::ForcedD2Q9Descriptor> **grid,
    int iX, int iY, int nX, int nY, int iPop, T& fTmp )
  {
    fTmp                 = grid[iX][iY][iPop];
    grid[iX][iY][iPop]   = grid[iX][iY][iPop+4];
    grid[iX][iY][iPop+4] = grid[nX][nY][iPop];
    grid[nX][nY][iPop]   = fTmp;
  }

  static void swapAndStream2D (
    Cell<T,descriptors::ForcedD2Q9Descriptor> **grid, int iX, int iY )
  {
    T fTmp;
    swapAndStreamCell(grid, iX, iY, iX-1, iY+1, 1, fTmp);
    swapAndStreamCell(grid, iX, iY, iX-1, iY,   2, fTmp);
    swapAndStreamCell(grid, iX, iY, iX-1, iY-1, 3, fTmp);
    swapAndStreamCell(grid, iX, iY, iX,   iY-1, 4, fTmp);
  }

};

}  






















 




 


namespace olb {


template<typename T>
struct lbDynamicsHelpers<T, descriptors::D3Q19DescriptorBase<T> > {

  static T equilibrium( int iPop, T rho, const T u[3], const T uSqr ) {
    typedef descriptors::D3Q19DescriptorBase<T> L;
    T c_u = L::c[iPop][0]*u[0] + L::c[iPop][1]*u[1] + L::c[iPop][2]*u[2];
    return rho * L::t[iPop] * ( 1. + 3.*c_u + 4.5*c_u*c_u - 1.5*uSqr ) - L::t[iPop];
  }

  static T incEquilibrium(int iPop, const T j[3], const T jSqr, const T pressure)
  {
    typedef descriptors::D3Q19DescriptorBase<T> L;
    T c_j = L::c[iPop][0]*j[0] + L::c[iPop][1]*j[1] + L::c[iPop][2]*j[2];
    return L::t[iPop] * ( 3.*pressure + 3.*c_j + 4.5*c_j*c_j - 1.5*jSqr ) - L::t[iPop];
  }

  static void computeFneq (
    T const* cell, T fNeq[19], T rho, const T u[3] )
  {
    const T uSqr = u[0]*u[0] + u[1]*u[1] + u[2]*u[2];
    for (int iPop=0; iPop < 19; ++iPop) {
      fNeq[iPop] = cell[iPop] - equilibrium(iPop, rho, u, uSqr);
    }
  }

  static T bgkCollision(T* cell, T rho, const T u[3], T omega) {
    const T uSqr = u[0]*u[0] + u[1]*u[1] + u[2]*u[2];
    for (int iPop=0; iPop < 19; ++iPop) {
      cell[iPop] *= (T)1-omega;
      cell[iPop] += omega *
                    lbDynamicsHelpers<T,descriptors::D3Q19DescriptorBase<T> >::equilibrium(iPop, rho, u, uSqr);
    }
    return uSqr;
  }

  static T incBgkCollision(T* cell, T pressure, const T j[3], T omega) {
    const T jSqr = util::normSqr<T,descriptors::D3Q19DescriptorBase<T>::d>(j);
    for (int iPop=0; iPop < descriptors::D3Q19DescriptorBase<T>::q; ++iPop) {
      cell[iPop] *= (T)1-omega;
      cell[iPop] += omega * lbDynamicsHelpers<T,descriptors::D3Q19DescriptorBase<T> >
                    ::incEquilibrium(iPop, j, jSqr, pressure);
    }
    std::cout<<"incBgkCollision-lbHelper3D"<<std::endl;
    return jSqr;
  }

  static T constRhoBgkCollision(T* cell, T rho, const T u[3], T ratioRho, T omega) {
    const T uSqr = util::normSqr<T,descriptors::D3Q19DescriptorBase<T>::d>(u);
 for (int iPop=0; iPop < descriptors::D3Q19DescriptorBase<T>::q; ++iPop) {
      T feq = lbDynamicsHelpers<T,descriptors::D3Q19DescriptorBase<T> >::
              equilibrium(iPop, rho, u, uSqr );
      cell[iPop] =
        ratioRho*(feq+descriptors::D3Q19DescriptorBase<T>::t[iPop])
        -descriptors::D3Q19DescriptorBase<T>::t[iPop] +
        ((T)1-omega)*(cell[iPop]-feq);
    }
    
    return uSqr;
  }

  static void partial_rho ( T const* cell,
                            T& surfX_M1, T& surfX_0, T& surfX_P1,
                            T& surfY_M1, T& surfY_P1, T& surfZ_M1, T& surfZ_P1 )
  {
    surfX_M1 = cell[1] + cell[4] + cell[5] + cell[6] + cell[7];
    surfX_0  = cell[0] + cell[2] + cell[3] + cell[8] +
               cell[9] + cell[11] + cell[12] + cell[17] + cell[18];
    surfX_P1 = cell[10] + cell[13] + cell[14] + cell[15] + cell[16];

    surfY_M1 = cell[2] + cell[4] + cell[8] + cell[9] + cell[14];
    surfY_P1 = cell[5] + cell[11] + cell[13] + cell[17] + cell[18];

    surfZ_M1 = cell[3] + cell[6] + cell[8] + cell[16] + cell[18];
    surfZ_P1 = cell[7] + cell[9] + cell[12] + cell[15] + cell[17];

  }

  static void computeRhoU(T const* cell, T& rho, T u[3]) {
    T surfX_M1, surfX_0, surfX_P1,
      surfY_M1, surfY_P1, surfZ_M1, surfZ_P1;

    partial_rho(cell, surfX_M1, surfX_0, surfX_P1,
                surfY_M1, surfY_P1, surfZ_M1, surfZ_P1);

    rho = surfX_M1 + surfX_0 + surfX_P1 + (T)1;

    u[0]  = ( surfX_P1 - surfX_M1 ) / rho;
    u[1]  = ( surfY_P1 - surfY_M1 ) / rho;
    u[2]  = ( surfZ_P1 - surfZ_M1 ) / rho;
  }

  static void computeJ(T const* cell, T j[3]) {
    T surfX_M1, surfX_P1, surfY_M1, surfY_P1, surfZ_M1, surfZ_P1;

    surfX_M1 = cell[1] + cell[4] + cell[5] + cell[6] + cell[7];
    surfX_P1 = cell[10] + cell[13] + cell[14] + cell[15] + cell[16];

    surfY_M1 = cell[2] + cell[4] + cell[8] + cell[9] + cell[14];
    surfY_P1 = cell[5] + cell[11] + cell[13] + cell[17] + cell[18];

    surfZ_M1 = cell[3] + cell[6] + cell[8] + cell[16] + cell[18];
    surfZ_P1 = cell[7] + cell[9] + cell[12] + cell[15] + cell[17];

    j[0]  = ( surfX_P1 - surfX_M1 );
    j[1]  = ( surfY_P1 - surfY_M1 );
    j[2]  = ( surfZ_P1 - surfZ_M1 );
  }

  static void computeStress(T const* cell, T rho, const T u[3], T pi[6]) {
    typedef descriptors::D3Q19DescriptorBase<T> L;
    
    
    using util::tensorIndices3D::xx;
    using util::tensorIndices3D::yy;
    using util::tensorIndices3D::zz;
    using util::tensorIndices3D::xy;
    using util::tensorIndices3D::xz;
    using util::tensorIndices3D::yz;

    T surfX_M1, surfX_0, surfX_P1,
      surfY_M1, surfY_P1, surfZ_M1, surfZ_P1;

    partial_rho(cell, surfX_M1, surfX_0, surfX_P1,
                surfY_M1, surfY_P1, surfZ_M1, surfZ_P1);

    pi[xx] = surfX_P1+surfX_M1 - 1./L::invCs2*(rho-(T)1) - rho*u[0]*u[0];
    pi[yy] = surfY_P1+surfY_M1 - 1./L::invCs2*(rho-(T)1) - rho*u[1]*u[1];
    pi[zz] = surfZ_P1+surfZ_M1 - 1./L::invCs2*(rho-(T)1) - rho*u[2]*u[2];

    pi[xy] = cell[4] - cell[5] + cell[13] - cell[14] - rho*u[0]*u[1];
    pi[xz] = cell[6] - cell[7] + cell[15] - cell[16] - rho*u[0]*u[2];
    pi[yz] = cell[8] - cell[9] + cell[17] - cell[18] - rho*u[1]*u[2];
  }

  static void computeAllMomenta(T const* cell, T& rho, T u[3], T pi[6]) {
    typedef descriptors::D3Q19DescriptorBase<T> L;
    
    
    using util::tensorIndices3D::xx;
    using util::tensorIndices3D::yy;
    using util::tensorIndices3D::zz;
    using util::tensorIndices3D::xy;
    using util::tensorIndices3D::xz;
    using util::tensorIndices3D::yz;

    T surfX_M1, surfX_0, surfX_P1,
      surfY_M1, surfY_P1, surfZ_M1, surfZ_P1;

    partial_rho(cell, surfX_M1, surfX_0, surfX_P1,
                surfY_M1, surfY_P1, surfZ_M1, surfZ_P1);

    rho = surfX_M1 + surfX_0 + surfX_P1 + (T)1;

    T rhoU0  = ( surfX_P1 - surfX_M1 ) / rho;
    T rhoU1  = ( surfY_P1 - surfY_M1 ) / rho;
    T rhoU2  = ( surfZ_P1 - surfZ_M1 ) / rho;
    u[0] = rhoU0 / rho;
    u[1] = rhoU1 / rho;
    u[2] = rhoU2 / rho;

    pi[xx] = surfX_P1+surfX_M1 - 1./L::invCs2*(rho-(T)1) - rhoU0*u[0];
    pi[yy] = surfY_P1+surfY_M1 - 1./L::invCs2*(rho-(T)1) - rhoU1*u[1];
    pi[zz] = surfZ_P1+surfZ_M1 - 1./L::invCs2*(rho-(T)1) - rhoU2*u[2];

    pi[xy] = cell[4] - cell[5] + cell[13] - cell[14] - rhoU0*u[1];
    pi[xz] = cell[6] - cell[7] + cell[15] - cell[16] - rhoU0*u[2];
    pi[yz] = cell[8] - cell[9] + cell[17] - cell[18] - rhoU1*u[2];
  }

  static T computeRho(T const* cell) {
    T rho = cell[0] + cell[1] + cell[2] + cell[3] + cell[4]
            + cell[5] + cell[6] + cell[7] + cell[8]
            + cell[9] + cell[10] + cell[11] + cell[12]
            + cell[13] + cell[14] + cell[15] + cell[16]
            + cell[17] + cell[18] + (T)1;
    return rho;
  }

  static void modifyVelocity(T* cell, const T newU[3]) {
    T rho, oldU[3];
    computeRhoU(cell, rho, oldU);
    const T oldUSqr = util::normSqr<T,3>(oldU);
    const T newUSqr = util::normSqr<T,3>(newU);
    for (int iPop=0; iPop<19; ++iPop) {
      cell[iPop] = cell[iPop]
                   - equilibrium(iPop, rho, oldU, oldUSqr)
                   + equilibrium(iPop, rho, newU, newUSqr);
    }
  }

};  





template<typename T>
struct lbLatticeHelpers<T, descriptors::D3Q19Descriptor> {

  static void swapAndStreamCell (
    Cell<T,descriptors::D3Q19Descriptor> ***grid,
    int iX, int iY, int iZ, int nX, int nY, int nZ, int iPop, T& fTmp )
  {
    fTmp                     = grid[iX][iY][iZ][iPop];
    grid[iX][iY][iZ][iPop]   = grid[iX][iY][iZ][iPop+9];
    grid[iX][iY][iZ][iPop+9] = grid[nX][nY][nZ][iPop];
    grid[nX][nY][nZ][iPop]   = fTmp;
  }

  static void swapAndStream3D(Cell<T,descriptors::D3Q19Descriptor> ***grid,
                              int iX, int iY, int iZ)
  {
    T fTmp;
    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY,   iZ,   1, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX,   iY-1, iZ,   2, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX,   iY  , iZ-1, 3, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY-1, iZ,   4, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY+1, iZ,   5, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY  , iZ-1, 6, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY  , iZ+1, 7, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX  , iY-1, iZ-1, 8, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX  , iY-1, iZ+1, 9, fTmp);
  }

};

template<typename T>
struct lbLatticeHelpers<T, descriptors::ForcedD3Q19Descriptor> {

  static void swapAndStreamCell (
    Cell<T,descriptors::ForcedD3Q19Descriptor> ***grid,
    int iX, int iY, int iZ, int nX, int nY, int nZ, int iPop, T& fTmp )
  {
    fTmp                     = grid[iX][iY][iZ][iPop];
    grid[iX][iY][iZ][iPop]   = grid[iX][iY][iZ][iPop+9];
    grid[iX][iY][iZ][iPop+9] = grid[nX][nY][nZ][iPop];
    grid[nX][nY][nZ][iPop]   = fTmp;
  }

  static void swapAndStream3D(Cell<T,descriptors::ForcedD3Q19Descriptor> ***grid,
                              int iX, int iY, int iZ)
  {
    T fTmp;
    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY,   iZ,   1, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX,   iY-1, iZ,   2, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX,   iY  , iZ-1, 3, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY-1, iZ,   4, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY+1, iZ,   5, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY  , iZ-1, 6, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY  , iZ+1, 7, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX  , iY-1, iZ-1, 8, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX  , iY-1, iZ+1, 9, fTmp);
  }

};



template<typename T>
struct lbDynamicsHelpers<T, descriptors::D3Q15DescriptorBase<T> > {

  static T equilibrium( int iPop, T rho, const T u[3], const T uSqr ) {
    typedef descriptors::D3Q15DescriptorBase<T> L;
    T c_u = L::c[iPop][0]*u[0] + L::c[iPop][1]*u[1] + L::c[iPop][2]*u[2];
    return rho * L::t[iPop] * ( 1. + 3.*c_u + 4.5*c_u*c_u - 1.5*uSqr ) - L::t[iPop];
  }

  static T incEquilibrium(int iPop, const T j[3], const T jSqr, const T pressure) {
    typedef descriptors::D3Q15DescriptorBase<T> L;
    T c_j = L::c[iPop][0]*j[0] + L::c[iPop][1]*j[1] + L::c[iPop][2]*j[2];
    return L::t[iPop] * ( 3.*pressure + 3.*c_j + 4.5*c_j*c_j - 1.5*jSqr ) - L::t[iPop];
  }

  static void computeFneq(T const* cell, T fNeq[15], T rho, const T u[3] ) {
    const T uSqr = u[0]*u[0] + u[1]*u[1] + u[2]*u[2];
    for (int iPop=0; iPop < 15; ++iPop) {
      fNeq[iPop] = cell[iPop] - equilibrium(iPop, rho, u, uSqr);
    }
  }

  static T bgkCollision(T* cell, T rho, const T u[3], T omega) {
    const T uSqr = u[0]*u[0] + u[1]*u[1] + u[2]*u[2];
    for (int iPop=0; iPop < 15; ++iPop) {
      cell[iPop] *= (T)1-omega;
      cell[iPop] += omega *
                    lbDynamicsHelpers<T,descriptors::D3Q15DescriptorBase<T> >::equilibrium(iPop, rho, u, uSqr);
    }
    return uSqr;
  }

  static T incBgkCollision(T* cell, T pressure, const T j[3], T omega) {
    const T jSqr = util::normSqr<T,descriptors::D3Q15DescriptorBase<T>::d>(j);
    for (int iPop=0; iPop < descriptors::D3Q15DescriptorBase<T>::q; ++iPop) {
      cell[iPop] *= (T)1-omega;
      cell[iPop] += omega * lbDynamicsHelpers<T,descriptors::D3Q15DescriptorBase<T> >::incEquilibrium (
                      iPop, j, jSqr, pressure );
    }
    return jSqr;
  }

  static T constRhoBgkCollision(T* cell, T rho, const T u[3], T ratioRho, T omega) {
    const T uSqr = util::normSqr<T,descriptors::D3Q15DescriptorBase<T>::d>(u);
    for (int iPop=0; iPop < descriptors::D3Q15DescriptorBase<T>::q; ++iPop) {
      T feq = lbHelpers<T,descriptors::D3Q15DescriptorBase>::
              equilibrium(iPop, rho, u, uSqr );
      cell[iPop] =
        ratioRho*(feq+descriptors::D3Q15DescriptorBase<T>::t[iPop])
        -descriptors::D3Q15DescriptorBase<T>::t[iPop] +
        ((T)1-omega)*(cell[iPop]-feq);
    }
    return uSqr;
  }

  static void partial_rho(T const* cell,
                          T& surfX_M1, T& surfX_0, T& surfX_P1,
                          T& surfY_M1, T& surfY_P1, T& surfZ_M1, T& surfZ_P1 )
  {
    surfX_M1 = cell[1] + cell[4] + cell[5] + cell[6] + cell[7];
    surfX_0  = cell[0] + cell[2] + cell[3] + cell[9] + cell[10];
    surfX_P1 = cell[8] + cell[11] + cell[12] + cell[13] + cell[14];

    surfY_M1 = cell[2] + cell[4] + cell[5] + cell[13] + cell[14];
    surfY_P1 = cell[6] + cell[7] + cell[9] + cell[11] + cell[12];

    surfZ_M1 = cell[3] + cell[4] + cell[6] + cell[12] + cell[14];
    surfZ_P1 = cell[5] + cell[7] + cell[10] + cell[11] + cell[13];
  }

  static T computeRho(T const* cell) {
    T rho = cell[0] + cell[1] + cell[2] + cell[3] + cell[4]
            + cell[5] + cell[6] + cell[7] + cell[8]
            + cell[9] + cell[10] + cell[11] + cell[12]
            + cell[13] + cell[14] + (T)1;
    return rho;
  }

  static void computeRhoU(T const* cell, T& rho, T u[3]) {
    T surfX_M1, surfX_0, surfX_P1,
      surfY_M1, surfY_P1, surfZ_M1, surfZ_P1;

    partial_rho(cell, surfX_M1, surfX_0, surfX_P1,
                surfY_M1, surfY_P1, surfZ_M1, surfZ_P1);

    rho = surfX_M1 + surfX_0 + surfX_P1 + (T)1;

    
    
    
    T rho_ = (T)1/rho;
    u[0]  = ( surfX_P1 - surfX_M1 ) * rho_;
    u[1]  = ( surfY_P1 - surfY_M1 ) * rho_;
    u[2]  = ( surfZ_P1 - surfZ_M1 ) * rho_;
  }

  static void computeJ(T const* cell, T j[3]) {
    T surfX_M1, surfX_P1, surfY_M1, surfY_P1, surfZ_M1, surfZ_P1;

    surfX_M1 = cell[1] + cell[4] + cell[5] + cell[6] + cell[7];
    surfX_P1 = cell[8] + cell[11] + cell[12] + cell[13] + cell[14];

    surfY_M1 = cell[2] + cell[4] + cell[5] + cell[13] + cell[14];
    surfY_P1 = cell[6] + cell[7] + cell[9] + cell[11] + cell[12];

    surfZ_M1 = cell[3] + cell[4] + cell[6] + cell[12] + cell[14];
    surfZ_P1 = cell[5] + cell[7] + cell[10] + cell[11] + cell[13];

    j[0]  = ( surfX_P1 - surfX_M1 );
    j[1]  = ( surfY_P1 - surfY_M1 );
    j[2]  = ( surfZ_P1 - surfZ_M1 );
  }

  static void computeStress(T const* cell, T rho, const T u[3], T pi[6]) {
    typedef descriptors::D3Q15DescriptorBase<T> L;
    using namespace util::tensorIndices3D;

    T surfX_M1, surfX_0, surfX_P1,
      surfY_M1, surfY_P1, surfZ_M1, surfZ_P1;

    partial_rho(cell, surfX_M1, surfX_0, surfX_P1,
                surfY_M1, surfY_P1, surfZ_M1, surfZ_P1);

    pi[xx] = surfX_P1+surfX_M1 - 1./L::invCs2*(rho-(T)1) - rho*u[0]*u[0];
    pi[yy] = surfY_P1+surfY_M1 - 1./L::invCs2*(rho-(T)1) - rho*u[1]*u[1];
    pi[zz] = surfZ_P1+surfZ_M1 - 1./L::invCs2*(rho-(T)1) - rho*u[2]*u[2];

    pi[xy] =   cell[4] + cell[5] - cell[6]  - cell[7]
               + cell[11] + cell[12] - cell[13] - cell[14] - rho*u[0]*u[1];
    pi[xz] =   cell[4] - cell[5] + cell[6]  - cell[7]
               + cell[11] - cell[12] + cell[13] - cell[14] - rho*u[0]*u[2];
    pi[yz] =   cell[4] - cell[5] - cell[6]  + cell[7]
               + cell[11] - cell[12] - cell[13] + cell[14] - rho*u[1]*u[2];

  }

  static void computeAllMomenta(T const* cell, T& rho, T u[3], T pi[6]) {
    typedef descriptors::D3Q15DescriptorBase<T> L;
    using namespace util::tensorIndices3D;

    T surfX_M1, surfX_0, surfX_P1,
      surfY_M1, surfY_P1, surfZ_M1, surfZ_P1;

    partial_rho(cell, surfX_M1, surfX_0, surfX_P1,
                surfY_M1, surfY_P1, surfZ_M1, surfZ_P1);

    rho = surfX_M1 + surfX_0 + surfX_P1 + (T)1;

    T rhoU0  = ( surfX_P1 - surfX_M1 ) / rho;
    T rhoU1  = ( surfY_P1 - surfY_M1 ) / rho;
    T rhoU2  = ( surfZ_P1 - surfZ_M1 ) / rho;
    u[0] = rhoU0 / rho;
    u[1] = rhoU1 / rho;
    u[2] = rhoU2 / rho;

    pi[xx] = surfX_P1+surfX_M1 - 1./L::invCs2*(rho-(T)1) - rhoU0*u[0];
    pi[yy] = surfY_P1+surfY_M1 - 1./L::invCs2*(rho-(T)1) - rhoU1*u[1];
    pi[zz] = surfZ_P1+surfZ_M1 - 1./L::invCs2*(rho-(T)1) - rhoU2*u[2];

    pi[xy] =   cell[4] + cell[5] - cell[6]  - cell[7]
               + cell[11] + cell[12] - cell[13] - cell[14] - rhoU0*u[1];
    pi[xz] =   cell[4] - cell[5] + cell[6]  - cell[7]
               + cell[11] - cell[12] + cell[13] - cell[14] - rhoU0*u[2];
    pi[yz] =   cell[4] - cell[5] - cell[6]  + cell[7]
               + cell[11] - cell[12] - cell[13] + cell[14] - rhoU1*u[2];
  }

  static void modifyVelocity(T* cell, const T newU[3]) {
    T rho, oldU[3];
    computeRhoU(cell, rho, oldU);
    const T oldUSqr = util::normSqr<T,3>(oldU);
    const T newUSqr = util::normSqr<T,3>(newU);
    for (int iPop=0; iPop<15; ++iPop) {
      cell[iPop] = cell[iPop]
                   - equilibrium(iPop, rho, oldU, oldUSqr)
                   + equilibrium(iPop, rho, newU, newUSqr);
    }
  }

};  





template<typename T>
struct lbLatticeHelpers<T, descriptors::D3Q15Descriptor> {
  static void swapAndStreamCell (
    Cell<T,descriptors::D3Q15Descriptor> ***grid,
    int iX, int iY, int iZ, int nX, int nY, int nZ, int iPop, T& fTmp )
  {
    fTmp                     = grid[iX][iY][iZ][iPop];
    grid[iX][iY][iZ][iPop]   = grid[iX][iY][iZ][iPop+7];
    grid[iX][iY][iZ][iPop+7] = grid[nX][nY][nZ][iPop];
    grid[nX][nY][nZ][iPop]   = fTmp;
  }

  static void swapAndStream3D(Cell<T,descriptors::D3Q15Descriptor> ***grid,
                              int iX, int iY, int iZ)
  {
    T fTmp;
    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY,   iZ,   1, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX,   iY-1, iZ,   2, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX,   iY  , iZ-1, 3, fTmp);

    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY-1, iZ-1, 4, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY-1, iZ+1, 5, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY+1, iZ-1, 6, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY+1, iZ+1, 7, fTmp);
  }

};

template<typename T>
struct lbLatticeHelpers<T, descriptors::ForcedD3Q15Descriptor> {

  static void swapAndStreamCell (
    Cell<T,descriptors::D3Q15Descriptor> ***grid,
    int iX, int iY, int iZ, int nX, int nY, int nZ, int iPop, T& fTmp )
  {
    fTmp                     = grid[iX][iY][iZ][iPop];
    grid[iX][iY][iZ][iPop]   = grid[iX][iY][iZ][iPop+7];
    grid[iX][iY][iZ][iPop+7] = grid[nX][nY][nZ][iPop];
    grid[nX][nY][nZ][iPop]   = fTmp;
  }

  static void swapAndStream3D(Cell<T,descriptors::D3Q15Descriptor> ***grid,
                              int iX, int iY, int iZ)
  {
    T fTmp;
    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY,   iZ,   1, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX,   iY-1, iZ,   2, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX,   iY  , iZ-1, 3, fTmp);

    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY-1, iZ-1, 4, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY-1, iZ+1, 5, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY+1, iZ-1, 6, fTmp);
    swapAndStreamCell(grid, iX, iY, iZ, iX-1, iY+1, iZ+1, 7, fTmp);
  }

};


}  























 












 


namespace olb {


template<typename T, template<typename U> class Lattice>
struct firstOrderLbHelpers {

  
  





 
  static T fromPiToFneq (
    int iPop, const T pi[util::TensorVal<Lattice<T> >::n] )
  {
    typedef Lattice<T> L;
    T fNeq = T();
    int iPi = 0;
    
    
    for (int iAlpha=0; iAlpha<L::d; ++iAlpha) {
      for (int iBeta=iAlpha; iBeta<L::d; ++iBeta) {
        T toAdd = L::c[iPop][iAlpha]*L::c[iPop][iBeta];
        if (iAlpha==iBeta) {
          toAdd -= 1./L::invCs2;
        }
        else {
          toAdd *= (T)2; 
        }                  
        toAdd *= pi[iPi++];
        fNeq += toAdd;
      }
    }
    fNeq *= L::t[iPop] * L::invCs2 * L::invCs2 / (T)2;
    return fNeq;
  }

  
  





 
  static T fromStrainToFneq (
    int iPop, const T S[util::TensorVal<Lattice<T> >::n], T omega )
  {
    typedef Lattice<T> L;
    T fNeq = fromPiToFneq(iPop,S) * (-(T)2 / L::invCs2 / omega);
    return fNeq;
  }

};  


template<typename T, template<typename U> class Lattice>
struct rlbHelpers {
  
  static T rlbCollision (
    Cell<T,Lattice>& cell, T rho, const T u[Lattice<T>::d],
    const T pi[util::TensorVal<Lattice<T> >::n], T omega )
  {
    typedef Lattice<T> L;
    const T uSqr = util::normSqr<T,L::d>(u);
    cell[0] = lbHelpers<T,Lattice>::equilibrium(0, rho, u, uSqr)
              + ((T)1-omega) *
              firstOrderLbHelpers<T,Lattice>::fromPiToFneq(0, pi);
    for (int iPop=1; iPop<=L::q/2; ++iPop) {
      cell[iPop] =
        lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr);
      cell[iPop+L::q/2] =
        lbHelpers<T,Lattice>::equilibrium(iPop+L::q/2, rho, u, uSqr);

      T fNeq = ((T)1-omega) *
               firstOrderLbHelpers<T,Lattice>::fromPiToFneq(iPop, pi);
      cell[iPop] += fNeq;
      cell[iPop+L::q/2] += fNeq;
    }
    return uSqr;
  }

};  

}  


























 



 

namespace olb {


namespace neqPiD2Q9 {

using namespace olb::util::tensorIndices2D;

template<typename T>
T fromPiToFneq0(const T pi[3]) {
  return (T)2 * (-(T)1/(T)3*pi[xx] - (T)1/(T)3*pi[yy]);
}

template<typename T>
T fromPiToFneq1(const T pi[3]) {
  return (T)1/(T)4 * ((T)1/(T)3*pi[xx] + (T)1/(T)3*pi[yy] - pi[xy]);
}

template<typename T>
T fromPiToFneq2(const T pi[3]) {
  return (T)1/(T)2 * ((T)2/(T)3*pi[xx] - (T)1/(T)3*pi[yy]);
}

template<typename T>
T fromPiToFneq3(const T pi[3]) {
  return (T)1/(T)4 * ((T)1/(T)3*pi[xx] + (T)1/(T)3*pi[yy] + pi[xy]);
}

template<typename T>
T fromPiToFneq4(const T pi[3]) {
  return (T)1/(T)2 * (-(T)1/(T)3*pi[xx] + (T)2/(T)3*pi[yy]);
}

}  

template<typename T>
struct rlbHelpers<T, descriptors::D2Q9Descriptor> {

  static T rlbCollision (
    Cell<T,descriptors::D2Q9Descriptor>& cell,
    T rho, const T u[2], const T pi[3], T omega )
  {
    typedef lbHelpers<T, descriptors::D2Q9Descriptor> LH;
    const T uSqr = u[0]*u[0] + u[1]*u[1];

    cell[0]  = LH::equilibrium(0, rho, u, uSqr) +
               ((T)1-omega) * neqPiD2Q9::fromPiToFneq0(pi);
    cell[1]  = LH::equilibrium(1, rho, u, uSqr) +
               ((T)1-omega) * neqPiD2Q9::fromPiToFneq1(pi);
    cell[2]  = LH::equilibrium(2, rho, u, uSqr) +
               ((T)1-omega) * neqPiD2Q9::fromPiToFneq2(pi);
    cell[3]  = LH::equilibrium(3, rho, u, uSqr) +
               ((T)1-omega) * neqPiD2Q9::fromPiToFneq3(pi);
    cell[4]  = LH::equilibrium(4, rho, u, uSqr) +
               ((T)1-omega) * neqPiD2Q9::fromPiToFneq4(pi);
    cell[5]  = LH::equilibrium(5, rho, u, uSqr) +
               ((T)1-omega) * neqPiD2Q9::fromPiToFneq1(pi);
    cell[6]  = LH::equilibrium(6, rho, u, uSqr) +
               ((T)1-omega) * neqPiD2Q9::fromPiToFneq2(pi);
    cell[7]  = LH::equilibrium(7, rho, u, uSqr) +
               ((T)1-omega) * neqPiD2Q9::fromPiToFneq3(pi);
    cell[8]  = LH::equilibrium(8, rho, u, uSqr) +
               ((T)1-omega) * neqPiD2Q9::fromPiToFneq4(pi);
    return uSqr;
  }

};  

}  























 



 

namespace olb {

























































































































































































































































 

}  
























 






 



namespace olb {


template<typename T>
struct d3q13Helpers {
  typedef descriptors::D3Q13Descriptor<T> Lattice;

  
  static T collision( Cell<T,descriptors::D3Q13Descriptor>& cell,
                      T rho, const T u[Lattice::d],
                      T lambda_nu, T lambda_nu_prime)
  {
    const T lambda_e = descriptors::D3Q13Descriptor<T>::lambda_e;
    const T lambda_h = descriptors::D3Q13Descriptor<T>::lambda_h;

    T uxSqr = util::sqr(u[0]);
    T uySqr = util::sqr(u[1]);
    T uzSqr = util::sqr(u[2]);
    T uSqr = uxSqr + uySqr + uzSqr;

    T s1 = cell[7] + cell[8] + cell[9] + cell[10];
    T s2 = cell[11] + cell[12];
    T s3 = cell[1] + cell[2] + cell[3] + cell[4];
    T s4 = cell[5] + cell[6];
    T sTot = s1 + s2 + s3 + s4;
    T d1 = cell[7] + cell[8] - cell[9] - cell[10];
    T d2 = cell[1] + cell[2] - cell[3] - cell[4];

    T M[13]; 
    
    
    
    M[4] = -(T)12*cell[0] + sTot - (T)11/(T)2;
    
    
    M[5] = s1 - (T)2*s2 + s3 - (T)2*s4;
    M[6] = d1 + d2;
    M[7] = cell[7] - cell[8] + cell[1] - cell[2];
    M[8] = cell[11] - cell[12] + cell[5] - cell[6];
    M[9] = cell[9] - cell[10] + cell[3] - cell[4];
    M[10] = d1 - d2;
    M[11] = -cell[7] + cell[8] + s2 + cell[1] - cell[2] - s4;
    M[12] = cell[9] - cell[10] - cell[11] + cell[12]
            - cell[3] + cell[4] + cell[5] - cell[6];
    T Mneq[13]; 
    
    
    
    Mneq[4] = M[4] + (T)11/(T)2*rho - (T)13/(T)2*rho*uSqr;
    Mneq[5] = M[5] - rho*( (T)2*uxSqr-(uySqr+uzSqr) );
    Mneq[6] = M[6] - rho*( uySqr-uzSqr );
    Mneq[7] = M[7] - rho*( u[0]*u[1] );
    Mneq[8] = M[8] - rho*( u[1]*u[2] );
    Mneq[9] = M[9] - rho*( u[0]*u[2] );
    Mneq[10] = M[10];
    Mneq[11] = M[11];
    Mneq[12] = M[12];

    Mneq[4]  *= lambda_e  / (T)156;
    Mneq[5]  *= lambda_nu / (T)24;
    Mneq[6]  *= lambda_nu / (T)8;
    Mneq[7]  *= lambda_nu_prime / (T)4;
    Mneq[8]  *= lambda_nu_prime / (T)4;
    Mneq[9]  *= lambda_nu_prime / (T)4;
    Mneq[10] *= lambda_h / (T)8;
    Mneq[11] *= lambda_h / (T)8;
    Mneq[12] *= lambda_h / (T)8;

    T F1 = Mneq[4] + Mneq[5] + Mneq[6];
    T F2 = Mneq[4] + Mneq[5] - Mneq[6];
    T F3 = Mneq[4] - (T)2*Mneq[5];

    cell[0]  -= (T)-12*Mneq[4];
    cell[1]  -= F1 + Mneq[7]                -Mneq[10]+Mneq[11];
    cell[2]  -= F1 - Mneq[7]                -Mneq[10]-Mneq[11];
    cell[3]  -= F2                  +Mneq[9]+Mneq[10]         -Mneq[12];
    cell[4]  -= F2                  -Mneq[9]+Mneq[10]         +Mneq[12];
    cell[5]  -= F3          +Mneq[8]                 -Mneq[11]+Mneq[12];
    cell[6]  -= F3          -Mneq[8]                 -Mneq[11]-Mneq[12];
    cell[7]  -= F1 + Mneq[7]                +Mneq[10]-Mneq[11];
    cell[8]  -= F1 - Mneq[7]                +Mneq[10]+Mneq[11];
    cell[9]  -= F2                  +Mneq[9]-Mneq[10]         +Mneq[12];
    cell[10] -= F2                  -Mneq[9]-Mneq[10]         -Mneq[12];
    cell[11] -= F3          +Mneq[8]                 +Mneq[11]-Mneq[12];
    cell[12] -= F3          -Mneq[8]                 +Mneq[11]+Mneq[12];

    return uSqr;
  }

  
  static T constRhoCollision( Cell<T,descriptors::D3Q13Descriptor>& cell,
                              T rho, const T u[Lattice::d],
                              T ratioRho,
                              T lambda_nu, T lambda_nu_prime)
  {
    const T uSqr = util::normSqr<T,Lattice::d>(u);

    return uSqr;
  }
}; 

}  


namespace olb {



template<typename T, template<typename U> class Lattice>
void Dynamics<T,Lattice>::computePopulations(Cell<T,Lattice> const& cell, T* f) const {
  for (int iPop=0; iPop<Lattice<T>::q; ++iPop) {
    f[iPop] = cell[iPop];
  }
}

template<typename T, template<typename U> class Lattice>
void Dynamics<T,Lattice>::iniEquilibrium(Cell<T,Lattice>& cell, T rho, const T u[Lattice<T>::d]) {
  T uSqr = util::normSqr<T,Lattice<T>::d>(u);
  for (int iPop=0; iPop<Lattice<T>::q; ++iPop) {
    cell[iPop] = computeEquilibrium(iPop, rho, u, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void Dynamics<T,Lattice>::computeExternalField (
  Cell<T,Lattice> const& cell, int pos, int size, T* ext) const {
  ;
  T const* externalData = cell.getExternal(pos);
  for (int iExt=0; iExt<size; ++iExt) {
    ext[iExt] = externalData[iExt];
  }
}

template<typename T, template<typename U> class Lattice>
void Dynamics<T,Lattice>::definePopulations(Cell<T,Lattice>& cell, const T* f)
{
  for (int iPop=0; iPop<Lattice<T>::q; ++iPop) {
    cell[iPop] = f[iPop];
  }
}

template<typename T, template<typename U> class Lattice>
void Dynamics<T,Lattice>::defineExternalField (
  Cell<T,Lattice>& cell, int pos, int size, const T* ext)
{
  ;
  T* externalData = cell.getExternal(pos);
  for (int iExt=0; iExt<size; ++iExt) {
    externalData[iExt] = ext[iExt];
  }
}

template<typename T, template<typename U> class Lattice>
T Dynamics<T,Lattice>::getParameter(int whichParameter) const {
  if (whichParameter == dynamicParams::omega_shear) {
    return getOmega();
  }
  return 0.;
}

template<typename T, template<typename U> class Lattice>
void Dynamics<T,Lattice>::setParameter(int whichParameter, T value) {
  if (whichParameter == dynamicParams::omega_shear) {
    setOmega(value);
  }
}

template<typename T, template<typename U> class Lattice>
void Dynamics<T,Lattice>::setBoundaryIntersection(int iPop, T distance)
{ }

template<typename T, template<typename U> class Lattice>
bool Dynamics<T,Lattice>::getBoundaryIntersection(int iPop, T point[Lattice<T>::d])
{ return 0; }

template<typename T, template<typename U> class Lattice>
void Dynamics<T,Lattice>::defineU(const T u[Lattice<T>::d])
{ }

template<typename T, template<typename U> class Lattice>
void Dynamics<T,Lattice>::defineU(int iPop, const T u[Lattice<T>::d])
{ }

template<typename T, template<typename U> class Lattice>
T Dynamics<T,Lattice>::getVelocityCoefficient(int iPop)
{ return 0; }



template<typename T, template<typename U> class Lattice>
BasicDynamics<T,Lattice>::BasicDynamics(Momenta<T,Lattice>& momenta_)
  : momenta(momenta_)
{ }

template<typename T, template<typename U> class Lattice>
T BasicDynamics<T,Lattice>::computeRho(Cell<T,Lattice> const& cell) const
{
  return momenta.computeRho(cell);
}

template<typename T, template<typename U> class Lattice>
void BasicDynamics<T,Lattice>::computeU (
  Cell<T,Lattice> const& cell,
  T u[Lattice<T>::d]) const
{
  momenta.computeU(cell, u);
}

template<typename T, template<typename U> class Lattice>
void BasicDynamics<T,Lattice>::computeJ (
  Cell<T,Lattice> const& cell,
  T j[Lattice<T>::d]) const
{
  momenta.computeJ(cell, j);
}

template<typename T, template<typename U> class Lattice>
void BasicDynamics<T,Lattice>::computeStress (
  Cell<T,Lattice> const& cell,
  T rho, const T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  momenta.computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void BasicDynamics<T,Lattice>::computeRhoU (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d]) const
{
  momenta.computeRhoU(cell, rho, u);
}

template<typename T, template<typename U> class Lattice>
void BasicDynamics<T,Lattice>::computeAllMomenta (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  this->computeRhoU(cell, rho, u);
  this->computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void BasicDynamics<T,Lattice>::defineRho(Cell<T,Lattice>& cell, T rho) {
  momenta.defineRho(cell, rho);
}

template<typename T, template<typename U> class Lattice>
void BasicDynamics<T,Lattice>::defineU (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d])
{
  momenta.defineU(cell, u);
}

template<typename T, template<typename U> class Lattice>
void BasicDynamics<T,Lattice>::defineRhoU (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d])
{
  momenta.defineRhoU(cell, rho, u);
}

template<typename T, template<typename U> class Lattice>
void BasicDynamics<T,Lattice>::defineAllMomenta (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d],
  const T pi[util::TensorVal<Lattice<T> >::n] )
{
  momenta.defineAllMomenta(cell, rho, u, pi);
}






 
template<typename T, template<typename U> class Lattice>
BGKdynamics<T,Lattice>::BGKdynamics (
  T omega_, Momenta<T,Lattice>& momenta_ )
  : BasicDynamics<T,Lattice>(momenta_),
    omega(omega_)
{ }

template<typename T, template<typename U> class Lattice>
BGKdynamics<T,Lattice>* BGKdynamics<T,Lattice>::clone() const {
  return new BGKdynamics<T,Lattice>(*this);
}

template<typename T, template<typename U> class Lattice>
T BGKdynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  return lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr);
}

template<typename T, template<typename U> class Lattice>
void BGKdynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  T rho, u[Lattice<T>::d];
  this->momenta.computeRhoU(cell, rho, u);
  T uSqr = lbHelpers<T,Lattice>::bgkCollision(cell, rho, u, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void BGKdynamics<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{
  T rho;
  rho = this->momenta.computeRho(cell);
  T uSqr = lbHelpers<T,Lattice>::bgkCollision(cell, rho, u, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
T BGKdynamics<T,Lattice>::getOmega() const {
  return omega;
}

template<typename T, template<typename U> class Lattice>
void BGKdynamics<T,Lattice>::setOmega(T omega_) {
  omega = omega_;
}






 
template<typename T, template<typename U> class Lattice>
ConstRhoBGKdynamics<T,Lattice>::ConstRhoBGKdynamics (
  T omega_, Momenta<T,Lattice>& momenta_ )
  : BasicDynamics<T,Lattice>(momenta_),
    omega(omega_)
{ }

template<typename T, template<typename U> class Lattice>
ConstRhoBGKdynamics<T,Lattice>* ConstRhoBGKdynamics<T,Lattice>::clone()
const
{
  return new ConstRhoBGKdynamics<T,Lattice>(*this);
}

template<typename T, template<typename U> class Lattice>
T ConstRhoBGKdynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  return lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr);
}

template<typename T, template<typename U> class Lattice>
void ConstRhoBGKdynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  T rho, u[Lattice<T>::d];
  this->momenta.computeRhoU(cell, rho, u);

  T deltaRho = (T)1 - (statistics).getAverageRho();
  
  T rho_ = (T)1/rho;
  T ratioRho = deltaRho*rho_ + (T)1;

  T uSqr = lbHelpers<T,Lattice>::constRhoBgkCollision (
             cell, rho, u, ratioRho, omega );
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho+deltaRho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void ConstRhoBGKdynamics<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{
  T rho = this->momenta.computeRho(cell);
  T uSqr = lbHelpers<T,Lattice>::bgkCollision(cell, rho, u, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
T ConstRhoBGKdynamics<T,Lattice>::getOmega() const {
  return omega;
}

template<typename T, template<typename U> class Lattice>
void ConstRhoBGKdynamics<T,Lattice>::setOmega(T omega_) {
  omega = omega_;
}





 
template<typename T, template<typename U> class Lattice>
IncBGKdynamics<T,Lattice>::IncBGKdynamics (
  T omega_, Momenta<T,Lattice>& momenta_ )
  : BasicDynamics<T,Lattice>(momenta_),
    omega(omega_)
{ }

template<typename T, template<typename U> class Lattice>
IncBGKdynamics<T,Lattice>* IncBGKdynamics<T,Lattice>::clone() const {
  return new IncBGKdynamics<T,Lattice>(*this);
}

template<typename T, template<typename U> class Lattice>
T IncBGKdynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  return lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr);
}

template<typename T, template<typename U> class Lattice>
void IncBGKdynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  T rho = this->momenta.computeRho(cell);
  T p = rho / Lattice<T>::invCs2;
  T j[Lattice<T>::d];
  this->momenta.computeJ(cell, j);
  T uSqr = lbHelpers<T,Lattice>::incBgkCollision(cell, p, j, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void IncBGKdynamics<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell,
  const T j[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{
  T rho = this->momenta.computeRho(cell);
  T p = rho / Lattice<T>::invCs2;
  T uSqr = lbHelpers<T,Lattice>::incBgkCollision(cell, p, j, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
T IncBGKdynamics<T,Lattice>::getOmega() const {
  return omega;
}

template<typename T, template<typename U> class Lattice>
void IncBGKdynamics<T,Lattice>::setOmega(T omega_) {
  omega = omega_;
}







 
template<typename T, template<typename U> class Lattice>
RLBdynamics<T,Lattice>::RLBdynamics (
  T omega_, Momenta<T,Lattice>& momenta_ )
  : BasicDynamics<T,Lattice>(momenta_),
    omega(omega_)
{ }

template<typename T, template<typename U> class Lattice>
RLBdynamics<T,Lattice>* RLBdynamics<T,Lattice>::clone() const {
  return new RLBdynamics<T,Lattice>(*this);
}

template<typename T, template<typename U> class Lattice>
T RLBdynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  return lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr);
}

template<typename T, template<typename U> class Lattice>
void RLBdynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  T rho, u[Lattice<T>::d], pi[util::TensorVal<Lattice<T> >::n];
  this->momenta.computeAllMomenta(cell, rho, u, pi);
  T uSqr = rlbHelpers<T,Lattice>::rlbCollision(cell, rho, u, pi, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void RLBdynamics<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{
  T rho, uDummy[Lattice<T>::d], pi[util::TensorVal<Lattice<T> >::n];
  this->momenta.computeAllMomenta(cell, rho, uDummy, pi);
  T uSqr = rlbHelpers<T,Lattice>::rlbCollision(cell, rho, u, pi, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
T RLBdynamics<T,Lattice>::getOmega() const {
  return omega;
}

template<typename T, template<typename U> class Lattice>
void RLBdynamics<T,Lattice>::setOmega(T omega_) {
  omega = omega_;
}




template<typename T, template<typename U> class Lattice, typename Dynamics>
CombinedRLBdynamics<T,Lattice,Dynamics>::CombinedRLBdynamics (
  T omega_, Momenta<T,Lattice>& momenta_ )
  : BasicDynamics<T,Lattice>(momenta_),
    boundaryDynamics(omega_, momenta_)
{ }

template<typename T, template<typename U> class Lattice, typename Dynamics>
CombinedRLBdynamics<T,Lattice,Dynamics>*
CombinedRLBdynamics<T,Lattice, Dynamics>::clone() const
{
  return new CombinedRLBdynamics<T,Lattice,Dynamics>(*this);
}

template<typename T, template<typename U> class Lattice, typename Dynamics>
T CombinedRLBdynamics<T,Lattice,Dynamics>::
computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  return boundaryDynamics.computeEquilibrium(iPop, rho, u, uSqr);
}

template<typename T, template<typename U> class Lattice, typename Dynamics>
void CombinedRLBdynamics<T,Lattice,Dynamics>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  typedef Lattice<T> L;

  T rho, u[L::d], pi[util::TensorVal<Lattice<T> >::n];
  this->momenta.computeAllMomenta(cell,rho,u,pi);

  T uSqr = util::normSqr<T,L::d>(u);

  for (int iPop = 0; iPop < L::q; ++iPop)
  {
    cell[iPop] = computeEquilibrium(iPop,rho,u,uSqr) +
                 firstOrderLbHelpers<T,Lattice>::fromPiToFneq(iPop, pi);
  }

  boundaryDynamics.collide(cell, statistics);
}

template<typename T, template<typename U> class Lattice, typename Dynamics>
void CombinedRLBdynamics<T,Lattice,Dynamics>::staticCollide (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{
  typedef Lattice<T> L;

  T rho, falseU[L::d], pi[util::TensorVal<Lattice<T> >::n];
  this->momenta.computeAllMomenta(cell, rho, falseU, pi);

  T uSqr = util::normSqr<T,L::d>(u);

  for (int iPop = 0; iPop < L::q; ++iPop)
  {
    cell[iPop] = computeEquilibrium(iPop,rho,u,uSqr) +
                 firstOrderLbHelpers<T,Lattice>::fromPiToFneq(iPop, pi);
  }

  boundaryDynamics.staticCollide(cell, u, statistics);
}

template<typename T, template<typename U> class Lattice, typename Dynamics>
T CombinedRLBdynamics<T,Lattice,Dynamics>::getOmega() const
{
  return boundaryDynamics.getOmega();
}

template<typename T, template<typename U> class Lattice, typename Dynamics>
void CombinedRLBdynamics<T,Lattice,Dynamics>::setOmega(T omega_)
{
  boundaryDynamics.setOmega(omega_);
}

template<typename T, template<typename U> class Lattice, typename Dynamics>
T CombinedRLBdynamics<T,Lattice,Dynamics>::getParameter(int whichParameter) const {
  return boundaryDynamics.getParameter(whichParameter);
}

template<typename T, template<typename U> class Lattice, typename Dynamics>
void CombinedRLBdynamics<T,Lattice,Dynamics>::setParameter(int whichParameter, T value) {
  boundaryDynamics.setParameter(whichParameter, value);
}






 
template<typename T, template<typename U> class Lattice>
ForcedBGKdynamics<T,Lattice>::ForcedBGKdynamics (
  T omega_, Momenta<T,Lattice>& momenta_ )
  : BasicDynamics<T,Lattice>(momenta_),
    omega(omega_)
{
  
  
  ;
}

template<typename T, template<typename U> class Lattice>
ForcedBGKdynamics<T,Lattice>* ForcedBGKdynamics<T,Lattice>::clone() const {
  return new ForcedBGKdynamics<T,Lattice>(*this);
}

template<typename T, template<typename U> class Lattice>
T ForcedBGKdynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  return lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr);
}

template<typename T, template<typename U> class Lattice>
void ForcedBGKdynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  T rho, u[Lattice<T>::d];
  this->momenta.computeRhoU(cell, rho, u);
  T* force = cell.getExternal(forceBeginsAt);
  for (int iVel=0; iVel<Lattice<T>::d; ++iVel) {
    u[iVel] += force[iVel] / (T)2.;
  }
  T uSqr = lbHelpers<T,Lattice>::bgkCollision(cell, rho, u, omega);
  lbHelpers<T,Lattice>::addExternalForce(cell, u, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void ForcedBGKdynamics<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{
  T rho, uDummy[Lattice<T>::d];
  this->momenta.computeRhoU(cell, rho, uDummy);
  T uSqr = lbHelpers<T,Lattice>::bgkCollision(cell, rho, u, omega);
  lbHelpers<T,Lattice>::addExternalForce(cell, u, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
T ForcedBGKdynamics<T,Lattice>::getOmega() const {
  return omega;
}

template<typename T, template<typename U> class Lattice>
void ForcedBGKdynamics<T,Lattice>::setOmega(T omega_) {
  omega = omega_;
}







 
template<typename T, template<typename U> class Lattice>
D3Q13dynamics<T,Lattice>::D3Q13dynamics (
  T omega_, Momenta<T,Lattice>& momenta_ )
  : BasicDynamics<T,Lattice>(momenta_)
{
  setOmega(omega_);
}

template<typename T, template<typename U> class Lattice>
D3Q13dynamics<T,Lattice>* D3Q13dynamics<T,Lattice>::clone() const {
  return new D3Q13dynamics<T,Lattice>(*this);
}

template<typename T, template<typename U> class Lattice>
T D3Q13dynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  
  Cell<T,Lattice> tmp;
  for (int pop=0; pop<Lattice<T>::q; ++pop) {
    tmp[pop] = Lattice<T>::t[pop];
  }
  d3q13Helpers<T>::collision(tmp, rho, u, (T)1, (T)1);
  return tmp[iPop];
}


template<typename T, template<typename U> class Lattice>
void D3Q13dynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  T rho, u[Lattice<T>::d];
  this->momenta.computeRhoU(cell, rho, u);
  T uSqr = d3q13Helpers<T>::collision (
             cell, rho, u, lambda_nu, lambda_nu_prime );
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void D3Q13dynamics<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{
  T rho = this->momenta.computeRho(cell);
  T uSqr = d3q13Helpers<T>::collision (
             cell, rho, u, lambda_nu, lambda_nu_prime );
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
T D3Q13dynamics<T,Lattice>::getOmega() const {
  return (T)4 / ( (T)3/lambda_nu + (T)1/(T)2 );
}

template<typename T, template<typename U> class Lattice>
void D3Q13dynamics<T,Lattice>::setOmega(T omega_) {
  lambda_nu = (T)3 / ( (T)4/omega_ - (T)1/(T)2 );
  lambda_nu_prime = (T)3 / ( (T)2/omega_ + (T)1/(T)2 );
}



template<typename T, template<typename U> class Lattice>
void Momenta<T,Lattice>::computeRhoU (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d]) const
{
  rho = this->computeRho(cell);
  this->computeU(cell, u);

}

template<typename T, template<typename U> class Lattice>
void Momenta<T,Lattice>::computeAllMomenta (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  this->computeRhoU(cell, rho, u);
  this->computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void Momenta<T,Lattice>::defineRhoU (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d])
{
  this->defineRho(cell, rho);
  this->defineU(cell, u);

}



template<typename T, template<typename U> class Lattice>
T BulkMomenta<T,Lattice>::computeRho(Cell<T,Lattice> const& cell) const {
  return lbHelpers<T,Lattice>::computeRho(cell);
}

template<typename T, template<typename U> class Lattice>
void BulkMomenta<T,Lattice>::computeU(Cell<T,Lattice> const& cell, T u[Lattice<T>::d]) const
{
  T dummyRho;
  lbHelpers<T,Lattice>::computeRhoU(cell, dummyRho, u);
}

template<typename T, template<typename U> class Lattice>
void BulkMomenta<T,Lattice>::computeJ(Cell<T,Lattice> const& cell, T j[Lattice<T>::d]) const
{
  lbHelpers<T,Lattice>::computeJ(cell, j);
}

template<typename T, template<typename U> class Lattice>
void BulkMomenta<T,Lattice>::computeStress (
  Cell<T,Lattice> const& cell,
  T rho, const T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  lbHelpers<T,Lattice>::computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void BulkMomenta<T,Lattice>::computeRhoU (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d] ) const
{
  lbHelpers<T,Lattice>::computeRhoU(cell, rho,u);
}

template<typename T, template<typename U> class Lattice>
void BulkMomenta<T,Lattice>::computeAllMomenta (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  this->computeRhoU(cell, rho, u);
  this->computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void BulkMomenta<T,Lattice>::defineRho(Cell<T,Lattice>& cell, T rho) {
  T oldRho, u[Lattice<T>::d];
  computeRhoU(cell, oldRho, u);
  T uSqr = util::normSqr<T,Lattice<T>::d>(u);
  T fNeq[Lattice<T>::q];
  lbHelpers<T,Lattice>::computeFneq(cell, fNeq, oldRho, u);
  for (int iPop=0; iPop < Lattice<T>::q; ++iPop) {
    cell[iPop] = lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr) +
                 fNeq[iPop];
  }
}

template<typename T, template<typename U> class Lattice>
void BulkMomenta<T,Lattice>::defineU (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d])
{
  T rho, oldU[Lattice<T>::d];
  computeRhoU(cell, rho, oldU);
  T uSqr = util::normSqr<T,Lattice<T>::d>(u);
  T fNeq[Lattice<T>::q];
  lbHelpers<T,Lattice>::computeFneq(cell, fNeq, rho, oldU);
  for (int iPop=0; iPop < Lattice<T>::q; ++iPop) {
    cell[iPop] = lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr) +
                 fNeq[iPop];
  }

}

template<typename T, template<typename U> class Lattice>
void BulkMomenta<T,Lattice>::defineRhoU (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d])
{
  T oldRho, oldU[Lattice<T>::d];
  computeRhoU(cell, oldRho, oldU);
  T uSqr = util::normSqr<T,Lattice<T>::d>(u);
  T fNeq[Lattice<T>::q];
  lbHelpers<T,Lattice>::computeFneq(cell, fNeq, oldRho, oldU);
  for (int iPop=0; iPop < Lattice<T>::q; ++iPop) {
    cell[iPop] = lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr) +
                 fNeq[iPop];
  }
}

template<typename T, template<typename U> class Lattice>
void BulkMomenta<T,Lattice>::defineAllMomenta (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d],
  const T pi[util::TensorVal<Lattice<T> >::n] )
{
  T uSqr = util::normSqr<T,Lattice<T>::d>(u);
  for (int iPop=0; iPop < Lattice<T>::q; ++iPop) {
    cell[iPop] = lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr) +
                 firstOrderLbHelpers<T,Lattice>::fromPiToFneq(iPop, pi);
  }
}



template<typename T, template<typename U> class Lattice>
T ExternalVelocityMomenta<T,Lattice>::computeRho(Cell<T,Lattice> const& cell) const {
  return lbHelpers<T,Lattice>::computeRho(cell);
}

template<typename T, template<typename U> class Lattice>
void ExternalVelocityMomenta<T,Lattice>::computeU(Cell<T,Lattice> const& cell, T u[Lattice<T>::d]) const
{
  T const* uExt = cell.getExternal(Lattice<T>::ExternalField::velocityBeginsAt);
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    u[iD] = uExt[iD];
  }
}

template<typename T, template<typename U> class Lattice>
void ExternalVelocityMomenta<T,Lattice>::computeJ(Cell<T,Lattice> const& cell, T j[Lattice<T>::d]) const
{
  T rho = computeRho(cell);
  T const* uExt = cell.getExternal(Lattice<T>::ExternalField::velocityBeginsAt);
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    j[iD] = uExt[iD]*rho;
  }
}

template<typename T, template<typename U> class Lattice>
void ExternalVelocityMomenta<T,Lattice>::computeStress (
  Cell<T,Lattice> const& cell,
  T rho, const T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  lbHelpers<T,Lattice>::computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void ExternalVelocityMomenta<T,Lattice>::computeRhoU (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d] ) const
{
  rho = computeRho(cell);
  computeU(cell,u);
}

template<typename T, template<typename U> class Lattice>
void ExternalVelocityMomenta<T,Lattice>::computeAllMomenta (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  computeRhoU(cell, rho,u);
  computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void ExternalVelocityMomenta<T,Lattice>::defineRho(Cell<T,Lattice>& cell, T rho) {
  T oldRho, u[Lattice<T>::d];
  computeRhoU(cell, oldRho, u);
  T uSqr = util::normSqr<T,Lattice<T>::d>(u);
  T fNeq[Lattice<T>::q];
  lbHelpers<T,Lattice>::computeFneq(cell, fNeq, oldRho, u);
  for (int iPop=0; iPop < Lattice<T>::q; ++iPop) {
    cell[iPop] = lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr) +
                 fNeq[iPop];
  }
}

template<typename T, template<typename U> class Lattice>
void ExternalVelocityMomenta<T,Lattice>::defineU (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d])
{
  T* uExt = cell.getExternal(Lattice<T>::ExternalField::velocityBeginsAt);
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    uExt[iD] = u[iD];
  }
}

template<typename T, template<typename U> class Lattice>
void ExternalVelocityMomenta<T,Lattice>::defineRhoU (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d])
{
  defineRho(cell, rho);
  defineU(cell, u);
}

template<typename T, template<typename U> class Lattice>
void ExternalVelocityMomenta<T,Lattice>::defineAllMomenta (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d],
  const T pi[util::TensorVal<Lattice<T> >::n] )
{
  defineU(cell, u);
  T uSqr = util::normSqr<T,Lattice<T>::d>(u);
  for (int iPop=0; iPop < Lattice<T>::q; ++iPop) {
    cell[iPop] = lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr) +
                 firstOrderLbHelpers<T,Lattice>::fromPiToFneq(iPop, pi);
  }
}




template<typename T, template<typename U> class Lattice>
BounceBack<T,Lattice>::BounceBack()
{ 
  rhoFixed=false;
}

template<typename T, template<typename U> class Lattice>
BounceBack<T,Lattice>::BounceBack(T rho_)
  :rho(rho_)
{ 
  rhoFixed=true;
}

template<typename T, template<typename U> class Lattice>
BounceBack<T,Lattice>* BounceBack<T,Lattice>::clone() const {
  return new BounceBack<T,Lattice>();
}

template<typename T, template<typename U> class Lattice>
T BounceBack<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  return T();
}

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  for (int iPop=1; iPop <= Lattice<T>::q/2; ++iPop) {
    std::swap(cell[iPop], cell[iPop+Lattice<T>::q/2]);
  }
}

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{
  this->collide(cell, statistics);
}

template<typename T, template<typename U> class Lattice>
T BounceBack<T,Lattice>::computeRho(Cell<T,Lattice> const& cell) const {
 
  if (rhoFixed)
    return rho;
  return lbHelpers<T,Lattice>::computeRho(cell);
}

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::computeU (
  Cell<T,Lattice> const& cell,
  T u[Lattice<T>::d]) const
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    u[iD] = T();
  }
}

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::computeJ (
  Cell<T,Lattice> const& cell,
  T j[Lattice<T>::d]) const
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    j[iD] = T();
  }
}

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::computeStress (
  Cell<T,Lattice> const& cell,
  T rho, const T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  for (int iPi=0; iPi<util::TensorVal<Lattice<T> >::n; ++iPi) {
    pi[iPi] = T();
  }
}

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::computeRhoU (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d]) const
{
  rho = computeRho(cell);
  computeU(cell, u);
}

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::computeAllMomenta (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  computeRhoU(cell, rho, u);
  computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::defineRho(Cell<T,Lattice>& cell, T rho)
{ }

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::defineU (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d])
{ }

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::defineRhoU (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d])
{ }

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::defineAllMomenta (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d],
  const T pi[util::TensorVal<Lattice<T> >::n] )
{ }

template<typename T, template<typename U> class Lattice>
T BounceBack<T,Lattice>::getOmega() const {
  return T();
}

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::setOmega(T omega_)
{ }



template<typename T, template<typename U> class Lattice>
NoDynamics<T,Lattice>* NoDynamics<T,Lattice>::clone() const {
  return new NoDynamics<T,Lattice>();
}

template<typename T, template<typename U> class Lattice>
T NoDynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  return T();
}

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{ }

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{ }

template<typename T, template<typename U> class Lattice>
T NoDynamics<T,Lattice>::computeRho(Cell<T,Lattice> const& cell) const
{
  return (T)0;
}

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::computeU (
  Cell<T,Lattice> const& cell,
  T u[Lattice<T>::d]) const
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    u[iD] = T();
  }
}

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::computeJ (
  Cell<T,Lattice> const& cell,
  T j[Lattice<T>::d]) const
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    j[iD] = T();
  }
}

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::computeStress (
  Cell<T,Lattice> const& cell,
  T rho, const T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  for (int iPi=0; iPi<util::TensorVal<Lattice<T> >::n; ++iPi) {
    pi[iPi] = T();
  }
}

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::computeRhoU (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d]) const
{
  rho = computeRho(cell);
  computeU(cell, u);
}

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::computeAllMomenta (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  computeRhoU(cell, rho, u);
  computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::defineRho(Cell<T,Lattice>& cell, T rho)
{ }

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::defineU (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d])
{ }

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::defineRhoU (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d])
{ }

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::defineAllMomenta (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d],
  const T pi[util::TensorVal<Lattice<T> >::n] )
{ }

template<typename T, template<typename U> class Lattice>
T NoDynamics<T,Lattice>::getOmega() const {
  return T();
}

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::setOmega(T omega_)
{ }


template<typename T, template<typename U> class Lattice>
OffDynamics<T,Lattice>::OffDynamics(
  const T _location[Lattice<T>::d])
{
  typedef Lattice<T> L;
  for (int iD = 0; iD < L::d; iD++)
    location[iD] = _location[iD];
  for (int iPop = 0; iPop < L::q; iPop++){
    distances[iPop] = -1;
    velocityCoefficient[iPop] = 0;
    for (int iD = 0; iD < L::d; iD++)
      boundaryIntersection[iPop][iD] = _location[iD];
  }
}

template<typename T, template<typename U> class Lattice>
OffDynamics<T,Lattice>::OffDynamics(
  const T _location[Lattice<T>::d], T _distances[Lattice<T>::q])
{
  typedef Lattice<T> L;
  for (int iD = 0; iD < L::d; iD++)
    location[iD] = _location[iD];
  for (int iPop = 0; iPop < L::q; iPop++){
    distances[iPop] = _distances[iPop];
    velocityCoefficient[iPop] = 0;
    const int* c = L::c[iPop];
    for (int iD = 0; iD < L::d; iD++)
      boundaryIntersection[iPop][iD] = _location[iD] - _distances[iPop]*c[iD];
  }
}

template<typename T, template<typename U> class Lattice>
void OffDynamics<T,Lattice>::setBoundaryIntersection(int iPop, T distance)
{
  
  
  typedef Lattice<T> L;
  distances[iPop] = distance;
  const int* c = L::c[iPop];
  for (int iD = 0; iD < L::d; iD++)
    boundaryIntersection[iPop][iD] = location[iD] - distance*c[iD];
}

template<typename T, template<typename U> class Lattice>
bool OffDynamics<T,Lattice>::getBoundaryIntersection(int iPop, T intersection[Lattice<T>::d])
{
  typedef Lattice<T> L;
  if (distances[iPop] != -1){
    for (int iD = 0; iD < L::d; iD++){
      intersection[iD] = boundaryIntersection[iPop][iD];
    }
    return true;
  }
  return false;
}

template<typename T, template<typename U> class Lattice>
void OffDynamics<T,Lattice>::defineU (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d])
{
  defineU(u);
}

template<typename T, template<typename U> class Lattice>
void OffDynamics<T,Lattice>::defineU(const T u[Lattice<T>::d])
{
  typedef Lattice<T> L;
  for (int iPop = 0; iPop < L::q; iPop++){
    if (distances[iPop] != -1){
      defineU(iPop, u);
    }
  }
}




 

template<typename T, template<typename U> class Lattice>
void OffDynamics<T,Lattice>::defineU(
  int iPop, const T u[Lattice<T>::d])
{
  
  typedef Lattice<T> L;
  const int* c = L::c[iPop];
  velocityCoefficient[iPop] = 0;
  
  for (int sum = 0; sum < L::d; sum++)  
    velocityCoefficient[iPop] -= c[sum]*u[sum];
  
  velocityCoefficient[iPop] *= 2*L::invCs2 * L::t[iPop];

}

template<typename T, template<typename U> class Lattice>
T OffDynamics<T,Lattice>::getVelocityCoefficient(int iPop)
{
  return velocityCoefficient[iPop];
}



namespace instances {

template<typename T, template<typename U> class Lattice>
BulkMomenta<T,Lattice>& getBulkMomenta() {
  static BulkMomenta<T,Lattice> bulkMomentaSingleton;
  return bulkMomentaSingleton;
}

template<typename T, template<typename U> class Lattice>
ExternalVelocityMomenta<T,Lattice>& getExternalVelocityMomenta() {
  static ExternalVelocityMomenta<T,Lattice> externalVelocityMomentaSingleton;
  return externalVelocityMomentaSingleton;
}

template<typename T, template<typename U> class Lattice>
BounceBack<T,Lattice>& getBounceBack() {
  static BounceBack<T,Lattice> bounceBackSingleton;
  return bounceBackSingleton;
}

template<typename T, template<typename U> class Lattice>
NoDynamics<T,Lattice>& getNoDynamics() {
  static NoDynamics<T,Lattice> noDynamicsSingleton;
  return noDynamicsSingleton;
}

}

}






















 






 


namespace olb {

namespace descriptors {



template<typename T>
const int D2Q9DescriptorBase<T>::vicinity = 1;

template<typename T>
const int D2Q9DescriptorBase<T>::c
[D2Q9DescriptorBase<T>::q][D2Q9DescriptorBase<T>::d] =
{
  { 0, 0},
  {-1, 1}, {-1, 0}, {-1,-1}, { 0,-1},
  { 1,-1}, { 1, 0}, { 1, 1}, { 0, 1}
};

template<typename T>
const T D2Q9DescriptorBase<T>::t[D2Q9DescriptorBase<T>::q] =
{
  (T)4/(T)9, (T)1/(T)36, (T)1/(T)9, (T)1/(T)36, (T)1/(T)9,
  (T)1/(T)36, (T)1/(T)9, (T)1/(T)36, (T)1/(T)9
};

template<typename T>
const T D2Q9DescriptorBase<T>::invCs2 = (T)3;



template<typename T>
const int D3Q13DescriptorBase<T>::vicinity = 1;

template<typename T>
const int D3Q13DescriptorBase<T>::c
[D3Q13DescriptorBase<T>::q][D3Q13DescriptorBase<T>::d] =
{
  { 0, 0, 0},

  {-1,-1, 0}, {-1, 1, 0}, {-1, 0,-1},
  {-1, 0, 1}, { 0,-1,-1}, { 0,-1, 1},

  { 1, 1, 0}, { 1,-1, 0}, { 1, 0, 1},
  { 1, 0,-1}, { 0, 1, 1}, { 0, 1,-1}
};

template<typename T>
const T D3Q13DescriptorBase<T>::t[D3Q13DescriptorBase<T>::q] =
{
  (T)1/(T)2,

  (T)1/(T)24, (T)1/(T)24, (T)1/(T)24,
  (T)1/(T)24, (T)1/(T)24, (T)1/(T)24,

  (T)1/(T)24, (T)1/(T)24, (T)1/(T)24,
  (T)1/(T)24, (T)1/(T)24, (T)1/(T)24
};


 
template<typename T>
const T D3Q13DescriptorBase<T>::invCs2 = (T)3;

 
template<typename T>
const T D3Q13DescriptorBase<T>::lambda_e = (T)1.5;

 
template<typename T>
const T D3Q13DescriptorBase<T>::lambda_h = (T)1.8;




template<typename T>
const int D3Q15DescriptorBase<T>::vicinity = 1;

template<typename T>
const int D3Q15DescriptorBase<T>::c
[D3Q15DescriptorBase<T>::q][D3Q15DescriptorBase<T>::d] =
{
  { 0, 0, 0},

  {-1, 0, 0}, { 0,-1, 0}, { 0, 0,-1},
  {-1,-1,-1}, {-1,-1, 1}, {-1, 1,-1}, {-1, 1, 1},

  { 1, 0, 0}, { 0, 1, 0}, { 0, 0, 1},
  { 1, 1, 1}, { 1, 1,-1}, { 1,-1, 1}, { 1,-1,-1},

};

template<typename T>
const T D3Q15DescriptorBase<T>::t[D3Q15DescriptorBase<T>::q] =
{
  (T)2/(T)9,

  (T)1/(T)9, (T)1/(T)9, (T)1/(T)9,
  (T)1/(T)72, (T)1/(T)72, (T)1/(T)72, (T)1/(T)72,

  (T)1/(T)9, (T)1/(T)9, (T)1/(T)9,
  (T)1/(T)72, (T)1/(T)72, (T)1/(T)72, (T)1/(T)72
};

template<typename T>
const T D3Q15DescriptorBase<T>::invCs2 = (T)3;




template<typename T>
const int D3Q19DescriptorBase<T>::vicinity = 1;

template<typename T>
const int D3Q19DescriptorBase<T>::c
[D3Q19DescriptorBase<T>::q][D3Q19DescriptorBase<T>::d] =
{
  { 0, 0, 0},

  {-1, 0, 0}, { 0,-1, 0}, { 0, 0,-1},
  {-1,-1, 0}, {-1, 1, 0}, {-1, 0,-1},
  {-1, 0, 1}, { 0,-1,-1}, { 0,-1, 1},

  { 1, 0, 0}, { 0, 1, 0}, { 0, 0, 1},
  { 1, 1, 0}, { 1,-1, 0}, { 1, 0, 1},
  { 1, 0,-1}, { 0, 1, 1}, { 0, 1,-1}
};

template<typename T>
const T D3Q19DescriptorBase<T>::t[D3Q19DescriptorBase<T>::q] =
{
  (T)1/(T)3,

  (T)1/(T)18, (T)1/(T)18, (T)1/(T)18,
  (T)1/(T)36, (T)1/(T)36, (T)1/(T)36,
  (T)1/(T)36, (T)1/(T)36, (T)1/(T)36,

  (T)1/(T)18, (T)1/(T)18, (T)1/(T)18,
  (T)1/(T)36, (T)1/(T)36, (T)1/(T)36,
  (T)1/(T)36, (T)1/(T)36, (T)1/(T)36
};

template<typename T>
const T D3Q19DescriptorBase<T>::invCs2 = (T)3;




template<typename T>
const int D3Q27DescriptorBase<T>::vicinity = 1;

template<typename T>
const int D3Q27DescriptorBase<T>::c
[D3Q27DescriptorBase<T>::q][D3Q27DescriptorBase<T>::d] =
{
  { 0, 0, 0},

  {-1, 0, 0}, { 0,-1, 0}, { 0, 0,-1},
  {-1,-1, 0}, {-1, 1, 0}, {-1, 0,-1},
  {-1, 0, 1}, { 0,-1,-1}, { 0,-1, 1},
  {-1,-1,-1}, {-1,-1, 1}, {-1, 1,-1}, {-1, 1, 1},

  { 1, 0, 0}, { 0, 1, 0}, { 0, 0, 1},
  { 1, 1, 0}, { 1,-1, 0}, { 1, 0, 1},
  { 1, 0,-1}, { 0, 1, 1}, { 0, 1,-1},
  { 1, 1, 1}, { 1, 1,-1}, { 1,-1, 1}, { 1,-1,-1}
};

template<typename T>
const T D3Q27DescriptorBase<T>::t[D3Q27DescriptorBase<T>::q] =
{
  (T)8/(T)27,

  (T)2/(T)27, (T)2/(T)27, (T)2/(T)27,
  (T)1/(T)54, (T)1/(T)54, (T)1/(T)54,
  (T)1/(T)54, (T)1/(T)54, (T)1/(T)54,
  (T)1/(T)216, (T)1/(T)216, (T)1/(T)216, (T)1/(T)216,

  (T)2/(T)27, (T)2/(T)27, (T)2/(T)27,
  (T)1/(T)54, (T)1/(T)54, (T)1/(T)54,
  (T)1/(T)54, (T)1/(T)54, (T)1/(T)54,
  (T)1/(T)216, (T)1/(T)216, (T)1/(T)216, (T)1/(T)216
};

template<typename T>
const T D3Q27DescriptorBase<T>::invCs2 = (T)3;

}  

}  


namespace olb {

template class Dynamics<double, descriptors::D2Q9Descriptor>;
template class Momenta<double, descriptors::D2Q9Descriptor>;
template class BasicDynamics<double, descriptors::D2Q9Descriptor>;
template class BGKdynamics<double, descriptors::D2Q9Descriptor>;
template class ConstRhoBGKdynamics<double, descriptors::D2Q9Descriptor>;
template class IncBGKdynamics<double, descriptors::D2Q9Descriptor>;
template class RLBdynamics<double, descriptors::D2Q9Descriptor>;
template class CombinedRLBdynamics<double, descriptors::D2Q9Descriptor,
         RLBdynamics<double, descriptors::D2Q9Descriptor> >;
template class CombinedRLBdynamics<double, descriptors::D2Q9Descriptor,
         BGKdynamics<double, descriptors::D2Q9Descriptor> >;
template class BulkMomenta<double, descriptors::D2Q9Descriptor>;
template class BounceBack<double, descriptors::D2Q9Descriptor>;
template class NoDynamics<double, descriptors::D2Q9Descriptor>;
template class OffDynamics<double, descriptors::D2Q9Descriptor>;

template class Dynamics<double, descriptors::D3Q19Descriptor>;
template class Momenta<double, descriptors::D3Q19Descriptor>;
template class BasicDynamics<double, descriptors::D3Q19Descriptor>;
template class BGKdynamics<double, descriptors::D3Q19Descriptor>;
template class ConstRhoBGKdynamics<double, descriptors::D3Q19Descriptor>;
template class IncBGKdynamics<double, descriptors::D3Q19Descriptor>;
template class RLBdynamics<double, descriptors::D3Q19Descriptor>;
template class CombinedRLBdynamics<double, descriptors::D3Q19Descriptor,
         RLBdynamics<double, descriptors::D3Q19Descriptor> >;
template class CombinedRLBdynamics<double, descriptors::D3Q19Descriptor,
         BGKdynamics<double, descriptors::D3Q19Descriptor> >;
template class BulkMomenta<double, descriptors::D3Q19Descriptor>;
template class BounceBack<double, descriptors::D3Q19Descriptor>;
template class NoDynamics<double, descriptors::D3Q19Descriptor>;
template class OffDynamics<double, descriptors::D3Q19Descriptor>;

namespace instances {

template BulkMomenta<double, descriptors::D2Q9Descriptor>& getBulkMomenta();

template BounceBack<double, descriptors::D2Q9Descriptor>& getBounceBack();

template NoDynamics<double, descriptors::D2Q9Descriptor>& getNoDynamics();

template BulkMomenta<double, descriptors::D3Q19Descriptor>& getBulkMomenta();

template BounceBack<double, descriptors::D3Q19Descriptor>& getBounceBack();

template NoDynamics<double, descriptors::D3Q19Descriptor>& getNoDynamics();

}

}
