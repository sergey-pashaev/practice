#ifndef DESIGN_CHAPTER_1_8_H
#define DESIGN_CHAPTER_1_8_H

#include <memory>

#include <chapter-1/chapter.1.5.h>
#include <chapter-1/creator.h>

// Chapter 1.8
// Template class methods you don't use - don't compile.
namespace c_1_8 {

using Widget = c_1_5::Widget;

template <template <class> class CreationPolicy>
class WidgetManager : public CreationPolicy<Widget> {
   public:
    WidgetManager() : widget_{this->Create()} {}

    void SwitchPrototype(Widget* new_prototype) {
        CreationPolicy<Widget>& creator = *this;
        widget_.reset(new_prototype);
        creator.SetPrototype(widget_.get());
    }

    const Widget& GetWidget() const {
        return *widget_;
    }

   private:
    std::unique_ptr<Widget> widget_;
};

}  // namespace c_1_8

#endif /* DESIGN_CHAPTER_1_8_H */
