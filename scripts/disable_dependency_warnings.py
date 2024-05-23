Import("env")

# Define build flags specific to your project files
project_build_flags = [
    "-Wall",           
    "-Wextra",         
    "-Wpedantic",      
    '-Wshadow',
    '-Wpointer-arith',
    '-Wcast-align',
    '-Wwrite-strings',
    '-Wredundant-decls',
    '-Wmissing-declarations',
    '-Wdouble-promotion',
    '-Wformat=2',
    '-Wconversion',
    '-Wlogical-op',
    '-Wnull-dereference',
    '-Wold-style-cast',
    '-Woverloaded-virtual',
    '-Wstrict-aliasing=2',
    '-Wno-unused-parameter'
]

# Append build flags to the environment
env.Append(
    BUILD_FLAGS=project_build_flags
)

# Exclude these flags from dependencies
env.Replace(
    BUILD_FLAGS=[
        flag for flag in env.get("BUILD_FLAGS", []) if flag not in project_build_flags
    ]
)

src_filter = "+<*> -<.pio>"