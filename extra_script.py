# # ATmega64 芯片烧录文件.bin
# from ast import Import
# from os.path import join
# Import("env", "projenv")
# # Custom BIN from ELF 
# env.AddPostAction(
#     "$BUILD_DIR/${PROGNAME}.elf",
#     env.VerboseAction(" ".join([
#                 "$OBJCOPY",
#                 "-O",
#                 "binary",
#                 "$TARGET",
#                 "$BUILD_DIR/${PROGNAME}.bin"
#             ]), "Building $TARGET"))

# 改变烧录文件名称  
Import("env")

my_flags = env.ParseFlags(env['BUILD_FLAGS'])
defines = {k: v for (k, v) in my_flags.get("CPPDEFINES")}
# print(defines)

env.Replace(PROGNAME="serialservo_%s" % defines.get("VERSION"))
