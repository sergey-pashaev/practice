struct Shape {};

// прямоугольник
struct Rectangle : Shape {};

// треугольник
struct Triangle : Shape {};

// функция для проверки пересечения двух прямоугольников
bool is_intersect_r_r(Shape*, Shape*) { return false; }

// функция для проверки пересечения прямоугольника и треугольника
bool is_intersect_r_t(Shape*, Shape*) { return false; }

#include <functional>
#include <map>
#include <typeindex>
#include <typeinfo>

template <class Base, class Result, bool Commutative>
struct Multimethod2 {
    using F = std::function<Result(Base*, Base*)>;
    using K = std::pair<std::type_index, std::type_index>;

    void addImpl(std::type_index t1, std::type_index t2, F f) {
        map_.insert({{t1, t2}, f});
    }

    bool hasImpl(Base* a, Base* b) const {
        return has_(a, b) || (Commutative && has_(b, a));
    }

    Result call(Base* a, Base* b) const {
        return has_(a, b) ? call_(a, b) : call_(b, a);
    }

   private:
    bool has_(Base* a, Base* b) const {
        return map_.count({typeid(*a), typeid(*b)});
    }

    Result call_(Base* a, Base* b) const {
        return map_[{typeid(*a), typeid(*b)}](a, b);
    }

    mutable std::map<K, F> map_;
};

int main() {
    // мультиметод для наследников Shape
    // возращающий bool и являющийся коммутативным
    Multimethod2<Shape, bool, true> is_intersect;

    // добавляем реализацию мультиметода для двух прямоугольников
    is_intersect.addImpl(typeid(Rectangle), typeid(Rectangle),
                         is_intersect_r_r);

    // добавляем реализацию мультиметода для прямоугольника и треугольника
    is_intersect.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);

    // создаём две фигуры
    Shape* s1 = new Triangle();
    Shape* s2 = new Rectangle();

    // проверяем, что реализация для s1 и s2 есть
    if (is_intersect.hasImpl(s1, s2)) {
        // вызывается функция is_intersect_r_t(s2, s1)
        is_intersect.call(s1, s2);

        // Замечание: is_intersect_r_t ожидает,
        // что первым аргументом будет прямоугольник
        // а вторым треугольник, а здесь аргументы
        // передаются в обратном порядке.
        // ваша реализация должна самостоятельно
        // об этом позаботиться
    }
}
