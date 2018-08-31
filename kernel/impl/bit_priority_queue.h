#ifndef YPP_KERNEL_BIT_PRIORITY_QUEUE_H
#define YPP_KERNEL_BIT_PRIORITY_QUEUE_H

#include <cstdint>

namespace ypp::kernel_impl {

struct bit_priority_queue {
  inline bool empty() const {
    return !bits_;
  }

  inline bool test(int bit) const {
    return bits_ & (1 << static_cast<std::uint32_t>(bit));
  }

  inline void set(int bit) {
    bits_ |= 1 << static_cast<std::uint32_t>(bit);
  }

  inline void unset(int bit) {
    bits_ &= ~(1 << static_cast<std::uint32_t>(bit));
  }

  /* must not be empty */
  inline int first() const {
#ifdef __ARM_FEATURE_CLZ
    /* use glibc builtin */
    return __builtin_ffsl(bits_) - 1;
#else
    /* Source:
     * http://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightMultLookup
     */
    static const std::uint8_t MultiplyDeBruijnBitPosition[32] = {
        0,  1,  28, 2,  29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4,  8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6,  11, 5,  10, 9};
    return MultiplyDeBruijnBitPosition[((bits_ & -bits_) * 0x077CB531U) >> 27];
#endif
  }

private:
  std::uint32_t bits_ = 0;
};

} // namespace ypp::kernel_impl

#endif /* YPP_KERNEL_BIT_PRIORITY_QUEUE_H */
