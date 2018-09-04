#ifndef YPP_BOARD_NATIVE_CONFIG_H
#define YPP_BOARD_NATIVE_CONFIG_H

#include <cstddef>

namespace ypp {

static constexpr std::size_t DEFAULT_STACK_SIZE = 32768;

static constexpr std::size_t EXEC_CONTEXT_SIZE = 72;

} // namespace ypp

#endif /* YPP_BOARD_NATIVE_CONFIG_H */