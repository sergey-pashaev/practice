#include <utility>

// Эти классы реализовывать заново не нужно
struct ICloneable {
    ICloneable* clone() const { return nullptr; }
};

// Поле data_ типа T в классе ValueHolder
// открыто, к нему можно обращаться
template <typename T>
struct ValueHolder {
    T data_;
};

class Any {
   public:
    Any() : value_(0) {}

    template <typename T>
    explicit Any(const T& value) : value_(new ValueHolder<T>(value)) {}

    ~Any() { delete value_; }

    Any(const Any& other) : value_(other.value_ ? other.value_->clone() : 0) {}

    friend void swap(Any& a, Any& b) { std::swap(a.value_, b.value_); }

    Any& operator=(Any other) {
        swap(*this, other);
        return *this;
    }

    template <typename T>
    Any& operator=(const T& value) {
        delete value_;
        value_ = new ValueHolder<T>(value);
        return *this;
    }

    template <typename T>
    T* cast() {
        if (value_) {
            ValueHolder<T>* casted = dynamic_cast<ValueHolder<T>*>(value_);
            return casted ? &(casted->data_) : 0;
        }

        return 0;
    }

   private:
    ICloneable* value_;
};

int main() {}
