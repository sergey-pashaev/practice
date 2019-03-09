#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

/// Loggable
template <typename T>
class Loggable {
   public:
    virtual ~Loggable() = default;

    typedef void (*Callback)(const std::string&);
    // #include <functional>
    // typedef std::function<void(const std::string&)> Callback;

    static void RegisterCallback(const Callback& cb) {
        if (cb) {
            callbacks_.push_back(cb);
        }
    }

    static void Remove(const Callback& cb) {
        callbacks_.erase(
            std::remove(std::begin(callbacks_), std::end(callbacks_), cb),
            std::end(callbacks_));

        if (callbacks_.empty()) {
            callbacks_.push_back(Default);
        }
    }

    static void LogMessage(const std::string& msg) {
        for (const auto& cb : callbacks_) {
            cb(msg);
        }
    }

   private:
    static void Default(const std::string& msg) {
        std::cout << "default: " << msg << '\n';
    }

    static std::vector<Callback> callbacks_;
};

template <typename T>
typename std::vector<typename Loggable<T>::Callback> Loggable<T>::callbacks_ = {
    Loggable<T>::Default};

/// Loggable users
struct Bar : public Loggable<Bar> {
    Bar() { LogMessage("bar mesasge"); }

    static void LogCallback(const std::string& msg) {
        std::cout << "bar: " << msg << '\n';
    }
};

struct Foo : public Loggable<Foo> {
    Foo() { LogMessage("foo message"); }

    static void LogCallback(const std::string& msg) {
        std::cout << "foo: " << msg << '\n';
    }
};

struct Baz : public Loggable<Baz> {
    Baz() { LogMessage("baz message"); }
};

/// main
int main() {
    Loggable<Foo>::RegisterCallback(Foo::LogCallback);
    Loggable<Foo>::RegisterCallback(nullptr);
    Loggable<Bar>::RegisterCallback(Bar::LogCallback);
    Foo f1;
    Bar b1;
    Baz z1;

    Loggable<Foo>::Remove(Foo::LogCallback);
    Foo f2;
    Bar b2;

    return 0;
}

// $ ./loggable
// default: foo
// foo custom: foo
// default: bar
// bar custom: bar
// default: foo
// default: bar
// bar custom: bar
// default: baz
