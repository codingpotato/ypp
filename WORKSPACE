load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

# bazel query fails for gtest without this dependency
git_repository(
    name = "com_google_absl",
    remote = "https://github.com/abseil/abseil-cpp.git",
    tag = "20180600",
)

# Google Test 1.9.0 is not yet out, while 1.8.0 did not have support for Bazel
# Will prefer to use stable build 1.9.0 when it's out
git_repository(
    name = "gtest",
    commit = "d1c1aac78160ae31353d9fe1bb1171353986a4f1",  # using nightly build on Aug 19, 2018
    remote = "https://github.com/google/googletest.git",
)
