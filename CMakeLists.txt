file(
    GLOB_RECURSE SOURCE_FILES_BOOST_DI 
    LIST_DIRECTORIES false
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${BOOST_DI_INCLUDE}/*.c*"
    "${BOOST_DI_INCLUDE}/*.h*"
)

foreach(_source IN ITEMS ${SOURCE_FILES_BOOST_DI})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
    source_group("${_source_path_msvc}" FILES "${_source}")
endforeach()

file(
    GLOB_RECURSE SOURCE_FILES 
    LIST_DIRECTORIES false
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "Source/*.c*"
    "Source/*.h*"
)

foreach(_source IN ITEMS ${SOURCE_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
    source_group("${_source_path_msvc}" FILES "${_source}")
endforeach()

if (WIN32)
    add_definitions(-DATOMIC_WIN32_CONSOLE)
endif()

include_directories(
    Source
    Source/Implementation
    ${BOOST_DI_INCLUDE}
)
add_executable(AITactics_Game ${SOURCE_FILES} ${SOURCE_FILES_BOOST_DI})

target_link_libraries(AITactics_Game Atomic)
target_link_libraries(AITactics_Game AITactics)

# Copy to Artifacts
add_custom_command( TARGET AITactics_Game POST_BUILD
                    COMMAND "${CMAKE_COMMAND}"
                    ARGS -E make_directory \"${ATOMIC_SOURCE_DIR}/Artifacts/AITactics_Game\"
                    COMMAND "${CMAKE_COMMAND}"
                    ARGS -E copy_if_different \"$<TARGET_FILE:AITactics_Game>\" \"${ATOMIC_SOURCE_DIR}/Artifacts/AITactics_Game\"
                    COMMENT "Copying AITactics_Game to Build Artifacts" )

if (WIN32)

  # pre-Windows 8 can't count on D3DCompiler_47.dll being on system
  add_custom_command (TARGET AITactics_Game POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy_if_different \"${D3DCOMPILER_47_DLL}\" \"$<TARGET_FILE_DIR:AITactics_Game>/D3DCompiler_47.dll\"
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy_if_different \"${D3DCOMPILER_47_DLL}\" \"${ATOMIC_SOURCE_DIR}/Artifacts/AITactics/D3DCompiler_47.dll\" )

endif(WIN32)