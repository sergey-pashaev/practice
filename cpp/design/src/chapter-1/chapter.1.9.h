#ifndef DESIGN_CHAPTER_1_9_H
#define DESIGN_CHAPTER_1_9_H

#include <exception>
#include <mutex>

// Chapter 1.9
// Multiple strategies example.
namespace c_1_9 {

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
// ThreadingModel::Lock(T&);
template <class T>
struct MultiThreadSafe {
    // TODO: better use std::lock_guard or similar
    class Lock {
       public:
        explicit Lock(T&) { mutex_.lock(); };
        ~Lock() { mutex_.unlock(); }

       private:
        std::mutex mutex_;
    };
};

template <class T>
struct NoSynchronization {
    class Lock {
       public:
        explicit Lock(T&){};
    };
};

// SmartPtr
template <class T, template <class> class CheckingPolicy,
          template <class> class ThreadingModel>
class SmartPtr : public CheckingPolicy<T>, ThreadingModel<T> {
   public:
    explicit SmartPtr(T* ptr) : pointee_{ptr} {}

    T* operator->() {
        typename ThreadingModel<SmartPtr>::Lock guard(*this);
        CheckingPolicy<T>::Check(pointee_);
        return pointee_;
    }

    ~SmartPtr() {
        if (pointee_) delete pointee_;
    }

   private:
    T* pointee_;
};

}  // namespace c_1_9

#endif /* DESIGN_CHAPTER_1_9_H */
