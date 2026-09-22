#include <cstddef>

namespace wstd::memory {

template <typename T> class unique_ptr {
public:
  unique_ptr() noexcept = default;

  unique_ptr(std::nullptr_t) noexcept {}

  explicit unique_ptr(T *ptr) noexcept : _ptr{ptr} {}

  ~unique_ptr() { delete _ptr; }

  unique_ptr(unique_ptr &&other) noexcept : _ptr{other._ptr} {
    other._ptr = nullptr;
  }

  unique_ptr &operator=(unique_ptr &&other) noexcept {
    if (this != &other) {
      delete _ptr;
      _ptr = other._ptr;
      other._ptr = nullptr;
    }

    return *this;
  }

  unique_ptr(const unique_ptr &other) = delete;

  unique_ptr &operator=(const unique_ptr &other) = delete;

  T *get() const noexcept { return _ptr; }

  T &operator*() const noexcept { return *_ptr; }

  T *operator->() const noexcept { return _ptr; }

  T *release() noexcept {
    T *p = _ptr;
    _ptr = nullptr;
    return p;
  }

  void reset(T *p = nullptr) noexcept {
    delete _ptr;
    _ptr = p;
  }

private:
  T *_ptr{nullptr};
};

} // namespace wstd::memory
