set(HEADERS
    Assert.h
    Box.h
    BoxInline.h
    BoxPack.h
    Color.h
    ColorInline.h
    Command.h
    Context.h
    ContextInline.h
    Error.h
    FileIO.h
    FileIOInline.h
    File.h
    FontSystem.h
    FontSystemInline.h
    Format.h
    FormatInline.h
    IRender.h
    ISystem.h
    ISystemInline.h
    ImageIO.h
    Image.h
    ImageInline.h
    Init.h
    LogSystem.h
    LRUCache.h
    LRUCacheInline.h
    Math.h
    MathInline.h
    Matrix.h
    MatrixInline.h
    Memory.h
    MemoryInline.h
    Mesh.h
    MeshInline.h
    Noise.h
    OS.h
    Observable.h
    ObservableList.h
    ObservableListInline.h
    ObservableMap.h
    ObservableMapInline.h
    ObservableValue.h
    ObservableValueInline.h
    PNG.h
    Random.h
    RandomInline.h
    Range.h
    RangeInline.h
    RenderOptions.h
    RenderOptionsInline.h
    RenderUtil.h
    Size.h
    SizeInline.h
    String.h
    Time.h
    Timer.h
    Util.h
    Vector.h
    VectorInline.h)
set(HEADERS_PRIVATE
    PNGPrivate.h)
set(SOURCE
    Assert.cpp
    BoxPack.cpp
    Command.cpp
    Context.cpp
    Error.cpp
    File.cpp
    FileIO.cpp
    FontSystem.cpp
    Format.cpp
    IRender.cpp
    ISystem.cpp
    ImageIO.cpp
    Image.cpp
    Init.cpp
    LogSystem.cpp
    Math.cpp
    Memory.cpp
    Mesh.cpp
    Noise.cpp
    PNG.cpp
    PNGRead.cpp
    PNGWrite.cpp
    OS.cpp
    Random.cpp
    RenderOptions.cpp
    RenderUtil.cpp
    String.cpp
    Time.cpp
    Timer.cpp)
if(WIN32)
    list(APPEND SOURCE
        ErrorWin32.cpp
        FileIOWin32.cpp
        FileWin32.cpp
        OSWin32.cpp
        TimeWin32.cpp)
else()
    list(APPEND SOURCE
        FileIOUnix.cpp
        FileUnix.cpp
        OSUnix.cpp
        TimeUnix.cpp)
endif()

add_library(dtkCore ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(dtkCore
    PUBLIC nlohmann_json::nlohmann_json
    PRIVATE Freetype::Freetype PNG::png ZLIB::ZLIB)
set_target_properties(dtkCore PROPERTIES FOLDER lib)
set_target_properties(dtkCore PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(
    TARGETS dtkCore
    EXPORT dtkCoreTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/dtk/dtkCore)
install(
    EXPORT dtkCoreTargets
    FILE dtkCoreTargets.cmake
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/dtk"
    NAMESPACE dtk::)
