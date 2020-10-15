#ifndef DESIGN_TYPELIST_H
#define DESIGN_TYPELIST_H

template <typename T, typename U>
struct TypeList {
    using Head = T;
    using Tail = U;
};

struct NullType {};

// TypeList length
template <class TList>
struct Length;

template <>
struct Length<NullType> {
    enum { value = 0 };
};

template <class T, class U>
struct Length<TypeList<T, U>> {
    enum { value = 1 + Length<U>::value };
};

// TypeAt
template <class TList, unsigned int index>
struct TypeAt;

template <class Head, class Tail>
struct TypeAt<TypeList<Head, Tail>, 0> {
    using Result = Head;
};

template <class Head, class Tail, unsigned int i>
struct TypeAt<TypeList<Head, Tail>, i> {
    using Result = typename TypeAt<Tail, i - 1>::Result;
};

// Indexof
template <class TList, typename T>
struct IndexOf;

template <typename T>
struct IndexOf<NullType, T> {
    enum { value = -1 };
};

template <class T, class Tail>
struct IndexOf<TypeList<T, Tail>, T> {
    enum { value = 0 };
};

template <class Head, class Tail, typename T>
struct IndexOf<TypeList<Head, Tail>, T> {
   private:
    enum { temp = IndexOf<Tail, T>::value };

   public:
    enum { value = temp == -1 ? -1 : 1 + temp };
};

// Append
template <class TList, typename T>
struct Append;

template <>
struct Append<NullType, NullType> {
    using Result = NullType;
};

template <typename T>
struct Append<NullType, T> {
    using Result = TypeList<T, NullType>;
};

template <class Head, class Tail>
struct Append<NullType, TypeList<Head, Tail>> {
    using Result = TypeList<Head, Tail>;
};

template <class Head, class Tail, typename T>
struct Append<TypeList<Head, Tail>, T> {
    using Result = TypeList<Head, typename Append<Tail, T>::Result>;
};

#define TYPELIST_1(T1) TypeList<T1, NullType>
#define TYPELIST_2(T1, T2) TypeList<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1, T2, T3) TypeList<T1, TYPELIST_2(T2, T3)>
#define TYPELIST_4(T1, T2, T3, T4) TypeList<T1, TYPELIST_3(T2, T3, T4)>
#define TYPELIST_5(T1, T2, T3, T4, T5) TypeList<T1, TYPELIST_4(T2, T3, T4, T5)>

#endif /* DESIGN_TYPELIST_H */
