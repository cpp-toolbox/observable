#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP

#include <functional>
#include <vector>

template <typename T> class Observable {
  public:
    using Callback = std::function<void(const T &new_value)>;

    Observable() = default;
    Observable(const T &value) : value(value) {}
    Observable(T &&value) : value(std::move(value)) {}

    Observable &operator=(const T &new_value) {
        value = new_value;
        notify();
        return *this;
    }

    Observable &operator=(T &&new_value) {
        value = std::move(new_value);
        notify();
        return *this;
    }

    void set(const T &new_value) { *this = new_value; }

    void set(T &&new_value) { *this = std::move(new_value); }

    const T &get() const { return value; }

    operator const T &() const { return value; }

    // Add a new observer callback
    void add_observer(Callback cb) { observers.push_back(std::move(cb)); }

  private:
    T value;
    std::vector<Callback> observers;

    void notify() {
        for (const auto &cb : observers) {
            cb(value);
        }
    }
};

#endif // OBSERVABLE_HPP
