### configuration plugin
add_definitions(-DTRANSLATION_DOMAIN=\"areeze_style_config\")
set(kstyle_areeze_config_PART_SRCS areezestyleconfig.cpp)

set(kstyle_areeze_config_PART_SRCS ${kstyle_areeze_config_PART_SRCS} areezestyleconfigmodule.cpp)

kconfig_add_kcfg_files(kstyle_areeze_config_PART_SRCS ../areezestyleconfigdata.kcfgc)
set(kstyle_areeze_config_PART_FORMS ui/areezestyleconfig.ui)
ki18n_wrap_ui(kstyle_areeze_config_PART_FORMS_HEADERS ${kstyle_areeze_config_PART_FORMS})

kcoreaddons_add_plugin(areezestyleconfig SOURCES
    ${kstyle_areeze_config_PART_SRCS}
    ${kstyle_areeze_config_PART_FORMS_HEADERS}
    INSTALL_NAMESPACE "kstyle_config"
)

target_link_libraries(areezestyleconfig
    PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

if(HAVE_QTDBUS)
    target_link_libraries(areezestyleconfig
        PUBLIC
            Qt6::DBus
    )
endif()

target_link_libraries(areezestyleconfig
    PUBLIC
        KF6::CoreAddons
        KF6::ConfigCore
        KF6::ConfigWidgets
        KF6::I18n
)
if(QT_MAJOR_VERSION STREQUAL "6")
    target_link_libraries(areezestyleconfig
        PUBLIC
    KF6::KCMUtils
)
endif()
kcmutils_generate_desktop_file(areezestyleconfig)

set(areeze_settings_SOURCES main.cpp)
add_executable(areeze-settings ${areeze_settings_SOURCES} )
target_link_libraries(areeze-settings Qt6::Core Qt6::Gui Qt6::Widgets )
target_link_libraries(areeze-settings KF6::I18n KF6::KCMUtils KF6::CoreAddons)

set_target_properties(areeze-settings PROPERTIES OUTPUT_NAME areeze-settings6)

install(TARGETS areeze-settings ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

# icon
ecm_install_icons(ICONS sc-apps-areeze-settings.svgz
    DESTINATION ${KDE_INSTALL_ICONDIR}
    THEME hicolor )

# kcmshell6 < 6.27.0 doesn't know the --smoke-test param, so skip this test for
# now.
# TODO: Drop this when KF6_MIN_VERSION >= 6.27.0
if(KF6KCMUtils_VERSION VERSION_GREATER_EQUAL "6.27.0")
    add_test(NAME areezestyleconfig_smoketest COMMAND kcmshell6 -style Areeze --smoke-test kstyle_config/areezestyleconfig)
    set_tests_properties(areezestyleconfig_smoketest PROPERTIES
        ENVIRONMENT_MODIFICATION QT_PLUGIN_PATH=path_list_prepend:${CMAKE_BINARY_DIR}/bin
    )
endif()
