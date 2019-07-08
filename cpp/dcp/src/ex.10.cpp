// ex.10

// Implement a job scheduler which takes in a function f and an
// integer n, and calls f after n milliseconds.

#include <catch2/catch.hpp>

#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

class Scheduler {
   public:
    template <typename Func>
    void RunWithDelay(Func f, chrono::milliseconds ms) {
        // run lambda with delay in separate thread
        auto lambda = [f, ms]() {
            this_thread::sleep_for(ms);
            f();
        };

        tasks.emplace_back(lambda);
    }

    ~Scheduler() {
        // join all threads before exit
        for (auto& t : tasks) {
            t.join();
        }
    }

   private:
    vector<thread> tasks;
};

TEST_CASE("ex.10") {
    Scheduler s;

    auto start = chrono::system_clock::now();

    s.RunWithDelay([]() { cout << "after 1000\n"; }, 1000ms);
    s.RunWithDelay([]() { cout << "after 500\n"; }, 500ms);
    s.RunWithDelay([]() { cout << "after 1500\n"; }, 1500ms);

    // print time line
    for (int i = 0; i < 20; ++i) {
        this_thread::sleep_for(chrono::milliseconds(100));
        auto now = chrono::system_clock::now();
        auto dur = chrono::duration_cast<chrono::milliseconds>(now - start);
        cout << dur.count() << " ms\n";
    }
}
