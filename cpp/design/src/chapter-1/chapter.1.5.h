#ifndef DESIGN_CHAPTER_1_5_H
#define DESIGN_CHAPTER_1_5_H

#include <memory>

#include <chapter-1/creator.h>

// Chapter 1.5
// Usage of creator class as template argument
namespace c_1_5 {

struct Widget {
    explicit Widget(int v = 42) : value{v} {}
    Widget* Clone() const { return new Widget(value); }

    int value;
};

template <class CreationPolicy>
class WidgetManager : public CreationPolicy {
   public:
    WidgetManager() : widget_{this->Create()} {}
    const Widget& GetWidget() const { return *widget_; }

   private:
    std::unique_ptr<Widget> widget_;
};

}  // namespace c_1_5

// Chapter 1.5.1
// In 1.5 WidgetManager can use CreationPolicy only for type Widget. It would be
// great if we can create not only Widgets with this CreationPolicy.
namespace c_1_5_1 {

using Widget = c_1_5::Widget;
struct Gadget {};

template <template <class Created> class CreationPolicy>
class WidgetManager : public CreationPolicy<Widget> {
   public:
    WidgetManager() : widget_{this->Create()} {}
    const Widget& GetWidget() const { return *widget_; }

    void DoSomething() {
        // Now we can create gadgets also.
        std::unique_ptr<Gadget> g{CreationPolicy<Gadget>().Create()};
    }

   private:
    std::unique_ptr<Widget> widget_;
};

}  // namespace c_1_5_1

#endif /* DESIGN_CHAPTER_1_5_H */
