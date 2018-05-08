add_library(mongoose
  mongoose.c
)
add_library(cesanta::mongoose ALIAS mongoose)

target_include_directories(mongoose
  PUBLIC include
  PRIVATE include/mongoose
)

