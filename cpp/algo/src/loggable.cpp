
#include <functional>
#include <iostream>
#include <string>

template <typename T>
class Loggable {
   public:
    typedef std::function<void(const std::string&)> Callback;

    static void Register(const Callback& cb) { cb_ = cb; }

    static void LogMessage(const std::string& msg) { cb_(msg); }

   private:
    static void Default(const std::string& msg) {
        std::cout << "default: " << msg << '\n';
    }

    static Callback cb_;
};

template <typename T>
typename Loggable<T>::Callback Loggable<T>::cb_ = Loggable<T>::Default;

struct Bar : public Loggable<Bar> {
    Bar() { LogMessage("bar"); }

    static void LogCallback(const std::string& msg) {
        std::cout << "bar custom: " << msg << '\n';
    }
};

struct Foo : public Loggable<Foo> {
    Foo() { LogMessage("foo"); }

    static void LogCallback(const std::string& msg) {
        std::cout << "foo custom: " << msg << '\n';
    }
};

struct Baz : public Loggable<Baz> {
    Baz() { LogMessage("baz"); }
};

int main() {
    Loggable<Foo>::Register(Foo::LogCallback);
    Loggable<Bar>::Register(Bar::LogCallback);
    Foo f;
    Bar b;
    {
        Foo f;
        Bar b;
        Baz z;
    }
    return 0;
}
