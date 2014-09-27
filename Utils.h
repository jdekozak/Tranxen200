#ifndef __UTILS_H__
#define __UTILS_H__

namespace THCRecords
{
namespace Utils
{

struct Nil
{
  typedef Nil head;
  typedef Nil tail;
};

template<typename Head, typename Tail=Nil>
struct Cons
{
  typedef Head head;
  typedef Tail tail;
};

template<typename List>
struct length
{
  static const int size = 1 + length<typename List::tail>::size;
};
template<>
struct length<Nil>
{
  static const int size = 0;
};

}
}

#endif
