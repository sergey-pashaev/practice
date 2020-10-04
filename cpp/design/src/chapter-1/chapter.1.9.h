#ifndef DESIGN_CHAPTER_1_9_H
#define DESIGN_CHAPTER_1_9_H

#include <cassert>
#include <exception>
#include <map>
#include <memory>
#include <mutex>

// Chapter 1.9
// Multiple strategies example.
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

// CheckingPolicy<T>:
// void Check(T*)
template <class T>
struct NoChecking {
    static void Check(T*) {}
};

template <class T>
struct EnforceNotNull {
    class NullPointerException : public std::exception {};
    static void Check(T* ptr) {
        if (!ptr) throw NullPointerException();
    }
};

template <class T>
struct EnsureNotNull {
    static void Check(T*& ptr) {
        if (!ptr) ptr = GetDefaultValue();
    }

    static T* GetDefaultValue() { return new T(); };
};

// ThreadingModel<T>:
// ThreadingModel::Lock(T*);
template <class T>
struct MultiThreadSafe {
    class Lock {
       public:
        explicit Lock(T* object) : object_{object} {
            const std::lock_guard<std::mutex> lock(map_mutex_);
            auto res = locks_.emplace(object, std::make_unique<std::mutex>());
            assert(res.second == true);
            res.first->second->lock();
        };
        ~Lock() {
            const std::lock_guard<std::mutex> lock(map_mutex_);
            auto it = locks_.find(object_);
            assert(it != locks_.end());
            auto mutex(std::move(it->second));
            locks_.erase(object_);
            mutex->unlock();
        }

       private:
        std::mutex& GetLock(T* object) {
            const std::lock_guard<std::mutex> lock(map_mutex_);
            auto it = locks_.find(object);
            if (it == locks_.end()) {
                locks_.emplace(object, std::make_unique<std::mutex>());
            }

            it = locks_.find(object);
            assert(it != locks_.end());
            return *it->second;
        }

       private:
        T* object_ = nullptr;
        static std::mutex map_mutex_;
        static std::map<T*, std::unique_ptr<std::mutex>> locks_;
    };
};

template <class T>
struct NoSynchronization {
    class Lock {
       public:
        explicit Lock(T*){};
    };
};

// SmartPtr
template <class T, template <class> class CheckingPolicy,
          template <class> class ThreadingModel>
class SmartPtr : public CheckingPolicy<T>, ThreadingModel<T> {
   public:
    explicit SmartPtr(T* ptr) : pointee_{ptr} {}

    T* operator->() {
        typename ThreadingModel<SmartPtr>::Lock guard(this);
        CheckingPolicy<T>::Check(pointee_);
        return pointee_;
    }

    void Reset(T* ptr) {
        typename ThreadingModel<SmartPtr>::Lock guard(this);
        if (pointee_) delete pointee_;
        pointee_ = ptr;
    }

    ~SmartPtr() {
        if (pointee_) delete pointee_;
    }

   private:
    T* pointee_;
};

}  // namespace c_1_9

#endif /* DESIGN_CHAPTER_1_9_H */
