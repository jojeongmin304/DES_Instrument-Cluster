file(REMOVE_RECURSE
  "IC_Project/Main.qml"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/appIC_Project_tooling.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
