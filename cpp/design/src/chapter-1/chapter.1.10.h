#ifndef DESIGN_CHAPTER_1_10_H
#define DESIGN_CHAPTER_1_10_H

// Chapter 1.10
// Pointer storage strategy.
namespace c_1_10 {

// CheckingPolicy<T>:
// void Check(T*)
template <class T>
struct NoChecking {
    static void Check(T*) {}
};

// ThreadingModel<T>:
// ThreadingModel::Lock(T*);
template <class T>
struct NoSynchronization {
    class Lock {
       public:
        explicit Lock(T*){};
    };
};

// Storage<T>:
// Storage<T>::PointerType
// Storage<T>::ReferenceType
template <class T>
class DefaultSmartPtrStorage {
   public:
    using PointerType = T*;
    using ReferenceType = T&;

   protected:
    PointerType GetPointer() { return ptr_; }
    void SetPointer(PointerType ptr) { ptr_ = ptr; }

   private:
    PointerType ptr_;
};

// SmartPtr
template <class T, template <class> class CheckingPolicy,
          template <class> class ThreadingModel,
          template <class> class Storage = DefaultSmartPtrStorage>
class SmartPtr : public CheckingPolicy<T>, ThreadingModel<T>, Storage<T> {
   public:
    explicit SmartPtr(typename Storage<T>::PointerType ptr) : pointee_{ptr} {}

    typename Storage<T>::PointerType operator->() {
        typename ThreadingModel<SmartPtr>::Lock guard(this);
        CheckingPolicy<T>::Check(pointee_);
        return pointee_;
    }

    void Reset(typename Storage<T>::PointerType ptr) {
        typename ThreadingModel<SmartPtr>::Lock guard(this);
        if (pointee_) delete pointee_;
        pointee_ = ptr;
    }

    ~SmartPtr() {
        if (pointee_) delete pointee_;
    }

   private:
    typename Storage<T>::PointerType pointee_;
};

}  // namespace c_1_10

#endif /* DESIGN_CHAPTER_1_10_H */
