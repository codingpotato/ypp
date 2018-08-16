cc_test(
    name = "kernel",
    srcs = [
        "bit_priority_queue.cpp",
        "circ_queue.cpp",
        "task.cpp",
    ],
    copts = [
        "-Iexternal/gtest/include",
    ],
    deps = [
        "//kernel",
        "@gtest//:main",
    ],
)
