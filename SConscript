Import("env")

board = env.SConscript(dirs="board")
kernel = env.SConscript(dirs="kernel")

ypp = env.Library("ypp", kernel + board)
Return("ypp")
