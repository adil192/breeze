################# includes #################
include_directories(
  animations
  debug
)

include_directories(${CMAKE_SOURCE_DIR}/libareezecommon)
include_directories(${CMAKE_BINARY_DIR}/libareezecommon)

################# configuration #################
configure_file(config-areeze.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-areeze.h )

########### next target ###############
set(areeze_PART_SRCS
    animations/areezeanimation.cpp
    animations/areezeanimations.cpp
    animations/areezeanimationdata.cpp
    animations/areezebaseengine.cpp
    animations/areezebusyindicatordata.cpp
    animations/areezebusyindicatorengine.cpp
    animations/areezedialdata.cpp
    animations/areezedialengine.cpp
    animations/areezeenabledata.cpp
    animations/areezegenericdata.cpp
    animations/areezeheaderviewdata.cpp
    animations/areezeheaderviewengine.cpp
    animations/areezescrollbardata.cpp
    animations/areezescrollbarengine.cpp
    animations/areezespinboxengine.cpp
    animations/areezespinboxdata.cpp
    animations/areezestackedwidgetdata.cpp
    animations/areezestackedwidgetengine.cpp
    animations/areezetabbarengine.cpp
    animations/areezetabbardata.cpp
    animations/areezetoolboxengine.cpp
    animations/areezetransitiondata.cpp
    animations/areezetransitionwidget.cpp
    animations/areezewidgetstateengine.cpp
    animations/areezewidgetstatedata.cpp
    debug/areezewidgetexplorer.cpp
    areezeaddeventfilter.cpp
    areezeblurhelper.cpp
    areezeframeshadow.cpp
    areezehelper.cpp
    areezemdiwindowshadow.cpp
    areezemnemonics.cpp
    areezepropertynames.cpp
    areezeshadowhelper.cpp
    areezesplitterproxy.cpp
    areezestyle.cpp
    areezestyleplugin.cpp
    areezetileset.cpp
    areezewindowmanager.cpp
    areezetoolsareamanager.cpp
)

kconfig_add_kcfg_files(areeze_PART_SRCS ../kdecoration/areezesettings.kcfgc)
kconfig_add_kcfg_files(areeze_PART_SRCS areezestyleconfigdata.kcfgc)


add_library(areeze${QT_MAJOR_VERSION} MODULE ${areeze_PART_SRCS})

ecm_qt_declare_logging_category(areeze${QT_MAJOR_VERSION}
    HEADER
        areeze_logging.h
    IDENTIFIER
        AREEZE
    CATEGORY_NAME
        areeze${QT_MAJOR_VERSION}
    DEFAULT_SEVERITY
        Warning
)

target_link_libraries(areeze${QT_MAJOR_VERSION}
    Qt${QT_MAJOR_VERSION}::Core
    Qt${QT_MAJOR_VERSION}::Gui
    Qt${QT_MAJOR_VERSION}::Widgets
)

if(HAVE_QTDBUS)
    target_link_libraries(areeze${QT_MAJOR_VERSION}
        Qt${QT_MAJOR_VERSION}::DBus
    )
endif()

if( AREEZE_HAVE_QTQUICK )
    target_link_libraries(areeze${QT_MAJOR_VERSION} 
        Qt${QT_MAJOR_VERSION}::Quick
        KF${QT_MAJOR_VERSION}::CoreAddons
    )
endif()

target_link_libraries(areeze${QT_MAJOR_VERSION}
    KF${QT_MAJOR_VERSION}::CoreAddons
    KF${QT_MAJOR_VERSION}::ConfigCore
    KF${QT_MAJOR_VERSION}::ConfigGui
    KF${QT_MAJOR_VERSION}::GuiAddons
    KF${QT_MAJOR_VERSION}::IconThemes
    KF${QT_MAJOR_VERSION}::WindowSystem
)

if(QT_MAJOR_VERSION STREQUAL "5")
    target_link_libraries(areeze5 KF5::ConfigWidgets)
else()
    target_link_libraries(areeze6 KF6::ColorScheme)
endif()

target_link_libraries(areeze${QT_MAJOR_VERSION} areezecommon${QT_MAJOR_VERSION})

if(KF${QT_MAJOR_VERSION}FrameworkIntegration_FOUND)
    target_link_libraries(areeze${QT_MAJOR_VERSION}  KF${QT_MAJOR_VERSION}::Style)
endif()


if (WIN32)
    # As stated in https://docs.microsoft.com/en-us/cpp/c-runtime-library/math-constants M_PI only gets defined
    # when if _USE_MATH_DEFINES is defined
    target_compile_definitions(areeze${QT_MAJOR_VERSION}  PRIVATE _USE_MATH_DEFINES _BSD_SOURCE)
endif()


########### install files ###############
install(TARGETS areeze${QT_MAJOR_VERSION}  DESTINATION ${KDE_INSTALL_QTPLUGINDIR}/styles/)
install(FILES areeze.themerc  DESTINATION  ${KDE_INSTALL_DATADIR}/kstyle/themes)
install(FILES areeze.kcfg DESTINATION ${KDE_INSTALL_KCFGDIR})

########### subdirectories ###############

if (QT_MAJOR_VERSION EQUAL "6" AND TARGET "KF6::KCMUtils")
    add_subdirectory(config)
endif()
