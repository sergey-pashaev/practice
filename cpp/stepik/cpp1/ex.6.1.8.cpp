
struct ICloneable {
    virtual ICloneable* clone() const = 0;
    virtual ~ICloneable() {}
};

template <typename T>
struct ValueHolder : public ICloneable  // дальше самостоятельно
{
    explicit ValueHolder(const T& data) : data_(data) {}

    ICloneable* clone() const { return new ValueHolder(data_); }

    T data_;
};

int main() {}
