# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("myapplication")













add_library(GetAway        "GetAway/GetAway/src/serverListener.cpp"
        "GetAway/GetAway/src/serverAuthManager.cpp" "GetAway/GetAway/src/serverLobbyManager.cpp"
        "GetAway/GetAway/src/serverGameManager.cpp" "GetAway/GetAway/src/messageTypeEnums.cpp"
        "GetAway/GetAway/src/ManagementFunctions.cpp" "GetAway/GetAway/src/satiAndroid.cpp"
        "GetAway/GetAway/src/replacementStreamBuff.cpp" "GetAway/GetAway/src/playerData.cpp"
        "GetAway/GetAway/src/constants.cpp" "GetAway/GetAway/src/deckSuit.cpp"
        "GetAway/GetAway/src/serverHome.cpp" "GetAway/GetAway/src/serverPF.cpp"
        "GetAway/GetAway/src/resourceStrings.cpp"
        "GetAway/GetAway/src/androidServerMain.cpp")

target_compile_definitions(GetAway PRIVATE SERVERMACRO=1)
target_include_directories(GetAway PRIVATE "GetAway/GetAway/header")



target_compile_options(GetAway PRIVATE -DANDROID -DASIO_STANDALONE )
find_package(Threads REQUIRED)
target_link_libraries(GetAway PRIVATE Threads::Threads)

target_include_directories(GetAway PRIVATE GetAway/asio/asio/include)













# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             native-lib.cpp )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib PRIVATE

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
target_link_libraries(native-lib PRIVATE GetAway)
target_include_directories(native-lib PRIVATE "GetAway/GetAway/header")
target_include_directories(native-lib PRIVATE "GetAway/asio/asio/include")
