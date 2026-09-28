add_library(areezecommon${QT_MAJOR_VERSION} OBJECT areezeboxshadowrenderer.cpp)

set_target_properties(areezecommon${QT_MAJOR_VERSION} PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

target_link_libraries(areezecommon${QT_MAJOR_VERSION}
    PUBLIC
        Qt${QT_MAJOR_VERSION}::Core
        Qt${QT_MAJOR_VERSION}::Gui)
