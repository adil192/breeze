add_definitions(-DTRANSLATION_DOMAIN="areeze_kwin_deco")

################# includes #################
include_directories(${CMAKE_SOURCE_DIR}/libareezecommon)
include_directories(${CMAKE_BINARY_DIR}/libareezecommon)

################# newt target #################
### plugin classes
set(areezedecoration_SRCS
    areezebutton.cpp
    areezedecoration.cpp
    areezesettingsprovider.cpp
    areezeexceptionlist.cpp
)

### build library
kconfig_add_kcfg_files(areezedecoration_SRCS areezesettings.kcfgc)
add_library(areezedecoration MODULE
    ${areezedecoration_SRCS}
    ${areezedecoration_config_PART_FORMS_HEADERS})

set_target_properties(areezedecoration PROPERTIES
    OUTPUT_NAME org.kde.areeze
)

target_link_libraries(areezedecoration
    PRIVATE
        areezecommon6
        Qt6::DBus
        KF6::CoreAddons
        KF6::ConfigGui
        KF6::GuiAddons
        KF6::I18n
        KF6::IconThemes
        KDecoration3::KDecoration
        KF6::ColorScheme
)

install(TARGETS areezedecoration DESTINATION ${KDE_INSTALL_PLUGINDIR}/${KDECORATION_PLUGIN_DIR})
install(FILES areezesettingsdata.kcfg DESTINATION ${KDE_INSTALL_KCFGDIR} RENAME areeze-decoration.kcfg)

add_subdirectory(config)

