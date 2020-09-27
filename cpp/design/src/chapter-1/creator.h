#ifndef DESIGN_CREATOR_H
#define DESIGN_CREATOR_H

#include <cstdlib>

template <class T>
struct OpNewCreator {
    static T* Create() { return new T; }
};

template <class T>
struct MallocCreator {
    static T* Create() {
        void* buf = std::malloc(sizeof(T));
        if (!buf) return nullptr;
        return new (buf) T;
    }
};

template <class T>
struct PrototypeCreator {
    PrototypeCreator(T* object = nullptr) : prototype_{object} {}
    T* Create() { return prototype_ ? prototype_->Clone() : nullptr; }
    T* GetPrototype() { return prototype_; }
    void SetPrototype(T* object) { prototype_ = object; }

   private:
    T* prototype_;
};

#endif /* DESIGN_CREATOR_H */
