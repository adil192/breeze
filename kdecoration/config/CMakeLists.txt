set(areezedecoration_config_SRCS
    ../areezeexceptionlist.cpp
    areezeconfigwidget.cpp
    areezedetectwidget.cpp
    areezeexceptiondialog.cpp
    areezeexceptionlistwidget.cpp
    areezeexceptionmodel.cpp
    areezeitemmodel.cpp
)
ki18n_wrap_ui(areezedecoration_config_SRCS
   ui/areezeconfigurationui.ui
   ui/areezeexceptiondialog.ui
   ui/areezeexceptionlistwidget.ui
)

kcoreaddons_add_plugin(kcm_areezedecoration SOURCES kcm_areezedecoration.cpp ${areezedecoration_config_SRCS} INSTALL_NAMESPACE "${KDECORATION_KCM_PLUGIN_DIR}")
kconfig_add_kcfg_files(kcm_areezedecoration ../areezesettings.kcfgc)
target_include_directories(kcm_areezedecoration PRIVATE ${CMAKE_SOURCE_DIR}/kdecoration ${CMAKE_BINARY_DIR}/kdecoration/)
target_link_libraries(kcm_areezedecoration
    PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::DBus
    PRIVATE
        KF6::ConfigCore
        KF6::CoreAddons
        KF6::GuiAddons
        KF6::I18n
        KF6::IconThemes
        KF6::KCMUtils
)
kcmutils_generate_desktop_file(kcm_areezedecoration)

# kcmshell6 < 6.27.0 doesn't know the --smoke-test param, so skip this test for
# now.
# TODO: Drop this when KF6_MIN_VERSION >= 6.27.0
if(KF6KCMUtils_VERSION VERSION_GREATER_EQUAL "6.27.0")
    add_test(NAME kcm_areezedecoration_smoketest COMMAND kcmshell6 -style Areeze --smoke-test ${KDECORATION_KCM_PLUGIN_DIR}/kcm_areezedecoration)
    set_tests_properties(kcm_areezedecoration_smoketest PROPERTIES
        ENVIRONMENT_MODIFICATION QT_PLUGIN_PATH=path_list_prepend:${CMAKE_BINARY_DIR}/bin
    )
endif()
