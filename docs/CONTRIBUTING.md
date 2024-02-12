# Making contributions
Since this project is in it's early stages, feel free
to make contributions in areas you deem desirable. 

# Coding style
## Variables/Constants
- Trivial variables: i, n, c, etc... (only one letter. if one letter isn't clear, then make it a local variable)
- Local variables: camelcase
- Global variables: g_camelcase
- Const variables: ALL_CAPS
- Pointer variables: Add a p_ to the prefix. For global variables it would be gp_var, for local variables p_var, for const variables p_VAR. if far pointers are used then use an fp_ instead of p_.

## Structs
- Structs: ModulePascalCase (module = full module name, or a 2-3 letter abbreviation, but still in pascalcase.)
- Struct member variables: camelCase

## Enums
- Enums: ModulePascalCase
- Enum values: ALL_CAPS

## Macros
- Macros: PascalCase
