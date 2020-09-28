#ifndef DESIGN_CHAPTER_1_7_H
#define DESIGN_CHAPTER_1_7_H

// Chapter 1.7
// You should protect your policy destructor.
namespace c_1_7 {

template <class T>
struct OpNewCreator {
    static T* Create() { return new T; }

   protected:
    // Allow destructor for derived classes only.
    ~OpNewCreator() = default;
};

}  // namespace c_1_7

#endif /* DESIGN_CHAPTER_1_7_H */
