from os import walk, path, environ
from dataclasses import dataclass

Import("env")

allow_template_creation = True

@dataclass
class EnvironmentVariable:
     name: str
     value: str
     typename: str
     description: str

def get_str_value_info(value: str) -> tuple[str, str]:
     if value.startswith("-") and value[1:].isnumeric():
          return int(value), "int" 
     elif value.isnumeric():
          return int(value), "int" 
     
     try:
          return float(value), "float"
     except:
          return value, "string"
     
def parse_environment_variables(path) -> list[EnvironmentVariable]:
     vairables = list()
     with open(path, "r") as file:
          description = ""
          for line in file.readlines():
               if line.startswith('#'):
                    description += line
               else: 
                    name, value = line.split("=")
                    if value.endswith("\n"):
                         value = value[:-1]
                    typename = "string"
                    if not value.startswith('"'): #if value is not a quoted string
                         value, typename = get_str_value_info(value)  
                         if typename == "string":
                              value = env.StringifyMacro(value)   
                    vairables.append(EnvironmentVariable(name=name, value=value, typename=typename, description=description))
                    description = ""
     return vairables

def create_template_file(template_path: str, variables: list[EnvironmentVariable]):
     with open(template_path, "w") as file:
          for variable in variables:
               file.write(f"{variable.description}")
               file.write(f"{variable.name}=#{variable.typename}\n")


env_path = path.join(env["PROJECT_DIR"], "config", "env")
template_env_path = path.join(env["PROJECT_DIR"], "config", "env_template")

allowed_extensions = [
    ".env",
    ".conf",
    ".config"
]

custom_env = list()

for root, dirs, files in walk(env_path):
    for file in files:
        name, extension = path.splitext(file)
        if extension in allowed_extensions:
          absolute_path = path.join(root, file)
          variables = parse_environment_variables(absolute_path)
          if allow_template_creation:
               template_path = path.join(template_env_path, file)     
               create_template_file(template_path, variables)
          for variable in variables:
               custom_env.append((variable.name, variable.value))

env.Append(
    CPPDEFINES=custom_env
)