# # * Headers file(GLOB_RECURSE interfaces "include/*.hpp")
# add_library(fhmdot_headers INTERFACE ${interfaces}) install(TARGETS
# fhmdot_headers DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

# * Objects

# * Libraries
set(libraries apply_gate minimize_energy sweep)
foreach(library ${libraries})
  if(${PROJECT_STATIC})
    add_library(${library} STATIC core/${library}.cpp)
  else()
    add_library(${library} SHARED core/${library}.cpp)
  endif()
  target_link_libraries(${library} ${TBB_TBB_LIBRARY_RELEASE} Boost::system
                        Boost::filesystem)
endforeach()

# * Executable
set(clicommands fhmdot_exe)
foreach(clicommand ${clicommands})
  add_executable(cli_${clicommand} cli/${clicommand}.cpp)
  # target_link_libraries(cli_${clicommand} ${BOOST_LIBRARIES})
  install(
    TARGETS cli_${clicommand}
    CONFIGURATIONS Release
    DESTINATION bin)
endforeach()
