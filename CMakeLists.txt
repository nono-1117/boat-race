cmake_minimum_required(VERSION 3.16)
project(MonProjet LANGUAGES CXX)

# Standard C++ (ajuste en 17 ou 20 si nécessaire)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Récupération automatique des fichiers sources dans src/
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Création de l'exécutable
add_executable(app ${SOURCES})

# Options de compilation (-Wall et mode Release équivalent à -O2 -DNDEBUG)
target_compile_options(app PRIVATE -Wall)

# Dossiers d'en-têtes (-I...)
target_include_directories(app PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/support/libphysics/include
        ${CMAKE_CURRENT_SOURCE_DIR}/support/SFML/SFML-2.6.1/include
)

# Dossiers des bibliothèques (-L...)
target_link_directories(app PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/support/SFML/install/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/support/libphysics/Release
)

# Édition des liens (-l...)
# Note : sous Linux/GCC, -llibphysics cherche "liblibphysics.so" ou ".a"
target_link_libraries(app PRIVATE
        sfml-system
        sfml-graphics
        sfml-window
        sfml-audio
        libphysics
)

# Gestion du rpath pour trouver libphysics et SFML à l'exécution sans erreur
set_target_properties(app PROPERTIES
        BUILD_RPATH "${CMAKE_CURRENT_SOURCE_DIR}/support/libphysics/Release;${CMAKE_CURRENT_SOURCE_DIR}/support/SFML/install/lib"
)