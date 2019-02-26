

find_package(ROSE REQUIRED)

set(instro_compiler_I_items "${ROSE_INCLUDES}")
set(instro_compiler_L_items "${ROSE_EXPORTED_TARGETS}")

set(INSTRO_USE_ROSE True)