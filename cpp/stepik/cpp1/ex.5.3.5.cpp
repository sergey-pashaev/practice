struct Expression {};
struct Number {};
struct BinaryOperation {};

struct SharedPtr {
    explicit SharedPtr(Expression *ptr = 0)
        : count(new int(ptr != 0)), ptr(ptr) {}
    ~SharedPtr() { dec(); }
    SharedPtr(const SharedPtr &other) : count(other.count), ptr(other.ptr) {
        inc();
    }
    SharedPtr &operator=(const SharedPtr &other) {
        if (this != &other) {
            dec();

            count = other.count;
            ptr = other.ptr;
            inc();
        }

        return *this;
    }
    Expression *get() const { return ptr; }
    void reset(Expression *ptr = 0) {
        dec();
        count = new int(ptr != 0);
        this->ptr = ptr;
    }
    Expression &operator*() const { return *ptr; }
    Expression *operator->() const { return ptr; }

   private:
    void dec() {
        if (ptr) (*count)--;
        if (*count <= 0) {
            delete ptr;
            delete count;
        }
    }

    void inc() {
        if (ptr) (*count)++;
    }

    int *count;
    Expression *ptr;
};

int main() {}
