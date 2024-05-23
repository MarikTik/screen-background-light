Import("env")
from os import path
# Define build flags specific to your project files

warnings_file_path = path.join(env["PROJECT_DIR"], "config", "build", "warnings.txt")

with open(warnings_file_path, "r") as warnings_file:
    project_build_flags = warnings_file.readlines()

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

 