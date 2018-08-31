Import("env")

cxxflags = env.get("CXXFLAGS", [])
if ("-std=c++17" not in cxxflags) and ("--std=c++17" not in cxxflags):
    env.Append(CXXFLAGS=["-std=c++17"])


def _ypp_main_program_impl(env, *args, **kwargs):
    return env.MainProgram(*args, **kwargs)


env.AddMethod(_ypp_main_program_impl, "YPPMainProgram")

board = env.SConscript(dirs="board")
kernel = env.SConscript(dirs="kernel")

ypp = env.Library("ypp", kernel + board)
Return("ypp")
