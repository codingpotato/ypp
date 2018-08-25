Import("env")

kernel = env.SConscript(dirs="kernel")

ypp = env.Library("ypp", kernel)
Return("ypp")
