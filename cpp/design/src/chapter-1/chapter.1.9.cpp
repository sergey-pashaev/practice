#include <catch2/catch.hpp>

#include <thread>
#include <vector>

#include <utils/utils.h>

#include <chapter-1/chapter.1.5.h>
#include <chapter-1/chapter.1.9.h>

namespace c_1_9 {

class Widget {
   public:
    Widget() = default;
    explicit Widget(int v) : value_{v} {}
    void Increment() { ++value_; }
    int Value() const { return value_; }

   private:
    int value_ = 0;
};

TEST_CASE("NoChecking") {
    using MyPtr = SmartPtr<Widget, NoChecking, NoSynchronization>;

    SECTION("Valid pointer to object") {
        MyPtr ptr(new Widget(5));
        REQUIRE(ptr->Value() == 5);
    }

#ifdef NO_CHECKING_NULLPTR
    SECTION("Null pointer") {
        MyPtr ptr(nullptr);
        REQUIRE(ptr->Value() == 0);
    }
#endif
}

TEST_CASE("EnforceNotNull") {
    using MyPtr = SmartPtr<Widget, EnforceNotNull, NoSynchronization>;

    SECTION("Valid pointer to object") {
        MyPtr ptr(new Widget(5));
        REQUIRE(ptr->Value() == 5);
    }

    SECTION("Null pointer") {
        MyPtr ptr(nullptr);
        REQUIRE_THROWS_AS(ptr->Value(),
                          EnforceNotNull<Widget>::NullPointerException);
    }
}

TEST_CASE("EnsureNotNull") {
    using MyPtr = SmartPtr<Widget, EnsureNotNull, NoSynchronization>;

    SECTION("Valid pointer to object") {
        MyPtr ptr(new Widget(5));
        REQUIRE(ptr->Value() == 5);
    }

    SECTION("Null pointer") {
        MyPtr ptr(nullptr);
        REQUIRE(ptr->Value() == 0);
    }
}

template <class T>
void DoWorkInThreads(T& ptr, int threads, int increments) {
    auto work = [&ptr](int n) {
        for (int i = 0; i < n; ++i) {
            ptr.Reset(new Widget());
            ptr->Increment();
        }
    };

    std::vector<std::thread> workers;
    for (int i = 0; i < threads; ++i) {
        workers.push_back(std::thread(work, increments));
    }

    for (auto& worker : workers) {
        worker.join();
    }
}

#ifdef NO_SYNCHRONIZATION_SEGFAULT
TEST_CASE("NoSynchronization") {
    using MyPtr = SmartPtr<Widget, NoChecking, NoSynchronization>;
    MyPtr ptr(new Widget());

    int increments = 2000;
    int threads = 5;
    DoWorkInThreads(ptr, threads, increments);
}
#endif

TEST_CASE("MultiThreadSafe") {
    using MyPtr = SmartPtr<Widget, NoChecking, MultiThreadSafe>;
    MyPtr ptr(new Widget());

    int increments = 2000;
    int threads = 5;
    DoWorkInThreads(ptr, threads, increments);
}

}  // namespace c_1_9
