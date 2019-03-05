
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
class Loggable {
   public:
    virtual ~Loggable() = default;

    typedef void (*Callback)(const std::string&);
    // #include <functional>
    // typedef std::function<void(const std::string&)> Callback;

    static void Register(const Callback& cb) {
        if (cb) {
            cb_.push_back(cb);
        }
    }

    static void Remove(const Callback& cb) {
        cb_.erase(std::remove(std::begin(cb_), std::end(cb_), cb),
                  std::end(cb_));

        if (cb_.empty()) {
            cb_.push_back(Default);
        }
    }

    static void LogMessage(const std::string& msg) {
        for (const auto& f : cb_) {
            f(msg);
        }
    }

   private:
    static void Default(const std::string& msg) {
        std::cout << "default: " << msg << '\n';
    }

    static std::vector<Callback> cb_;
};

template <typename T>
typename std::vector<typename Loggable<T>::Callback> Loggable<T>::cb_ = {
    Loggable<T>::Default};

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
    Loggable<Foo>::Register(Foo::LogCallback);
    Loggable<Foo>::Register(nullptr);
    Loggable<Foo>::Remove(Foo::LogCallback);
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
