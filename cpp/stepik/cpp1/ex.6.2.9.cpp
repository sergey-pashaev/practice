#include <iostream>

// Весь вывод должен осуществляться в поток out,
// переданный в качестве параметра.
//
// Можно заводить любые вспомогательные функции,
// структуры или даже изменять сигнатуру flatten,
// но при этом все примеры вызова из задания должны
// компилироваться и работать.

template <typename T>
class Array {
   public:
    explicit Array(size_t size = 0, const T& value = T());
    Array(const Array& other);
    ~Array();
    Array& operator=(Array other);
    void swap(Array& other);
    size_t size() const;
    T& operator[](size_t idx);
    const T& operator[](size_t idx) const;

   private:
    size_t size_;
    T* data_;
};

template <typename T>
void flatten(const T& val, std::ostream& out) {
    out << val << ' ';
}

template <typename T>
void flatten(const Array<T>& array, std::ostream& out) {
    const size_t size = array.size();
    for (size_t i = 0; i < size; ++i) {
        flatten(array[i], out);
    }
}

int main() {}
