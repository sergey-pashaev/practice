#ifndef CLONABLE_H
#define CLONABLE_H

#include <memory>

namespace psv {

class Clonable {
   public:
    virtual ~Clonable() = default;

    std::unique_ptr<Clonable> Clone() const {
        return std::unique_ptr<Clonable>(this->DoClone());
    }

   private:
    virtual Clonable* DoClone() const = 0;
};

template <class Derived, class Base>
class CloneInherit : public Base {
   public:
    std::unique_ptr<Derived> Clone() const {
        return std::unique_ptr<Derived>(static_cast<Derived*>(this->DoClone()));
    }

   private:
    virtual CloneInherit* DoClone() const override {
        return new Derived(static_cast<const Derived&>(*this));
    }
};

}  // namespace psv

#endif /* CLONABLE_H */
