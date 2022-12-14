add_subdirectory(icons)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (NOT DISABLE_KWATCHGNUPG)
    add_subdirectory(kwatchgnupg)
endif()
add_subdirectory(libkleopatraclient)
add_subdirectory(conf)
add_subdirectory(kconf_update)

if(WIN32)
  set(_kleopatra_extra_uiserver_SRCS uiserver/uiserver_win.cpp)
  set(_kleopatra_extra_SRCS
      utils/gnupg-registry.c
      selftest/registrycheck.cpp
      utils/windowsprocessdevice.cpp
      utils/userinfo_win.cpp
  )
else()
  set(_kleopatra_extra_uiserver_SRCS uiserver/uiserver_unix.cpp)
  set(_kleopatra_extra_SRCS)
endif()

set(_kleopatra_uiserver_SRCS
    uiserver/sessiondata.cpp
    uiserver/uiserver.cpp
    ${_kleopatra_extra_uiserver_SRCS}
    uiserver/assuanserverconnection.cpp
    uiserver/echocommand.cpp
    uiserver/decryptverifycommandemailbase.cpp
    uiserver/decryptverifycommandfilesbase.cpp
    uiserver/signcommand.cpp
    uiserver/signencryptfilescommand.cpp
    uiserver/prepencryptcommand.cpp
    uiserver/prepsigncommand.cpp
    uiserver/encryptcommand.cpp
    uiserver/selectcertificatecommand.cpp
    uiserver/importfilescommand.cpp
    uiserver/createchecksumscommand.cpp
    uiserver/verifychecksumscommand.cpp

    selftest/uiservercheck.cpp
  )

if(ASSUAN2_FOUND)
  include_directories(${ASSUAN2_INCLUDES})
  set(_kleopatra_uiserver_extra_libs ${ASSUAN2_LIBRARIES})
else()
  include_directories(${ASSUAN_INCLUDES})
  if(WIN32)
    set(_kleopatra_uiserver_extra_libs ${ASSUAN_VANILLA_LIBRARIES})
  else()
    set(_kleopatra_uiserver_extra_libs ${ASSUAN_PTHREAD_LIBRARIES})
  endif()
endif()

if(HAVE_GPG_ERR_SOURCE_KLEO)
  add_definitions(-DGPG_ERR_SOURCE_DEFAULT=GPG_ERR_SOURCE_KLEO)
  add_definitions(-DGPGMEPP_ERR_SOURCE_DEFAULT=GPG_ERR_SOURCE_KLEO)
else()
  add_definitions(-DGPG_ERR_SOURCE_DEFAULT=GPG_ERR_SOURCE_USER_1)
  add_definitions(-DGPGMEPP_ERR_SOURCE_DEFAULT=GPG_ERR_SOURCE_USER_1)
endif()

ki18n_wrap_ui(_kleopatra_uiserver_SRCS crypto/gui/signingcertificateselectionwidget.ui)

if("${Gpgmepp_VERSION}" VERSION_GREATER_EQUAL "1.14.1")
    set(_kleopatra_deviceinfowatcher_files
        smartcard/deviceinfowatcher.cpp
    )
else()
    set(_kleopatra_deviceinfowatcher_files)
endif()

set(_kleopatra_SRCS
  utils/gui-helper.cpp
  utils/filedialog.cpp
  utils/kdpipeiodevice.cpp
  utils/headerview.cpp
  utils/scrollarea.cpp
  utils/dragqueen.cpp
  utils/multivalidator.cpp
  utils/systemtrayicon.cpp

  utils/hex.cpp
  utils/path-helper.cpp
  utils/input.cpp
  utils/output.cpp
  utils/validation.cpp
  utils/wsastarter.cpp
  utils/iodevicelogger.cpp
  utils/log.cpp
  utils/action_data.cpp
  utils/types.cpp
  utils/archivedefinition.cpp
  utils/auditlog.cpp
  utils/clipboardmenu.cpp
  utils/kuniqueservice.cpp
  utils/tags.cpp
  utils/writecertassuantransaction.cpp
  utils/keyparameters.cpp
  utils/userinfo.cpp

  selftest/selftest.cpp
  selftest/enginecheck.cpp
  selftest/gpgconfcheck.cpp
  selftest/gpgagentcheck.cpp
  selftest/libkleopatrarccheck.cpp

  ${_kleopatra_extra_SRCS}

  view/keylistcontroller.cpp
  view/keytreeview.cpp
  view/searchbar.cpp
  view/smartcardwidget.cpp
  view/openpgpkeycardwidget.cpp
  view/padwidget.cpp
  view/pgpcardwidget.cpp
  view/pivcardwidget.cpp
  view/p15cardwidget.cpp
  view/netkeywidget.cpp
  view/nullpinwidget.cpp
  view/tabwidget.cpp
  view/keycacheoverlay.cpp
  view/waitwidget.cpp
  view/welcomewidget.cpp

  dialogs/certificateselectiondialog.cpp
  dialogs/certifywidget.cpp
  dialogs/expirydialog.cpp
  dialogs/lookupcertificatesdialog.cpp
  dialogs/ownertrustdialog.cpp
  dialogs/selftestdialog.cpp
  dialogs/certifycertificatedialog.cpp
  dialogs/revokecertificationwidget.cpp
  dialogs/revokecertificationdialog.cpp
  dialogs/adduseriddialog.cpp
  dialogs/addemaildialog.cpp
  dialogs/deletecertificatesdialog.cpp
  dialogs/setinitialpindialog.cpp
  dialogs/certificatedetailsdialog.cpp
  dialogs/certificatedetailswidget.cpp
  dialogs/trustchainwidget.cpp
  dialogs/weboftrustwidget.cpp
  dialogs/weboftrustdialog.cpp
  dialogs/exportdialog.cpp
  dialogs/subkeyswidget.cpp
  dialogs/gencardkeydialog.cpp
  dialogs/updatenotification.cpp
  dialogs/pivcardapplicationadministrationkeyinputdialog.cpp
  dialogs/certificatedetailsinputwidget.cpp
  dialogs/createcsrforcardkeydialog.cpp
  dialogs/groupdetailsdialog.cpp
  dialogs/editgroupdialog.cpp

  crypto/controller.cpp
  crypto/certificateresolver.cpp
  crypto/sender.cpp
  crypto/recipient.cpp
  crypto/task.cpp
  crypto/taskcollection.cpp
  crypto/decryptverifytask.cpp
  crypto/decryptverifyemailcontroller.cpp
  crypto/decryptverifyfilescontroller.cpp
  crypto/autodecryptverifyfilescontroller.cpp
  crypto/encryptemailtask.cpp
  crypto/encryptemailcontroller.cpp
  crypto/newsignencryptemailcontroller.cpp
  crypto/signencrypttask.cpp
  crypto/signencryptfilescontroller.cpp
  crypto/signemailtask.cpp
  crypto/signemailcontroller.cpp
  crypto/createchecksumscontroller.cpp
  crypto/verifychecksumscontroller.cpp

  crypto/gui/wizard.cpp
  crypto/gui/wizardpage.cpp

  crypto/gui/certificateselectionline.cpp
  crypto/gui/certificatelineedit.cpp
  crypto/gui/signingcertificateselectionwidget.cpp
  crypto/gui/signingcertificateselectiondialog.cpp

  crypto/gui/resultitemwidget.cpp
  crypto/gui/resultlistwidget.cpp
  crypto/gui/resultpage.cpp

  crypto/gui/newresultpage.cpp
  crypto/gui/signencryptfileswizard.cpp

  crypto/gui/signencryptemailconflictdialog.cpp

  crypto/gui/decryptverifyoperationwidget.cpp
  crypto/gui/decryptverifyfileswizard.cpp
  crypto/gui/decryptverifyfilesdialog.cpp

  crypto/gui/objectspage.cpp
  crypto/gui/resolverecipientspage.cpp
  crypto/gui/signerresolvepage.cpp
  crypto/gui/encryptemailwizard.cpp
  crypto/gui/signemailwizard.cpp
  crypto/gui/signencryptwidget.cpp
  crypto/gui/signencryptwizard.cpp
  crypto/gui/unknownrecipientwidget.cpp

  crypto/gui/verifychecksumsdialog.cpp

  commands/command.cpp
  commands/gnupgprocesscommand.cpp
  commands/detailscommand.cpp
  commands/exportcertificatecommand.cpp
  commands/importcertificatescommand.cpp
  commands/importcertificatefromfilecommand.cpp
  commands/importcertificatefromclipboardcommand.cpp
  commands/importcertificatefromdatacommand.cpp
  commands/lookupcertificatescommand.cpp
  commands/reloadkeyscommand.cpp
  commands/refreshx509certscommand.cpp
  commands/refreshopenpgpcertscommand.cpp
  commands/deletecertificatescommand.cpp
  commands/decryptverifyfilescommand.cpp
  commands/signencryptfilescommand.cpp
  commands/signencryptfoldercommand.cpp
  commands/encryptclipboardcommand.cpp
  commands/signclipboardcommand.cpp
  commands/decryptverifyclipboardcommand.cpp
  commands/clearcrlcachecommand.cpp
  commands/dumpcrlcachecommand.cpp
  commands/dumpcertificatecommand.cpp
  commands/importcrlcommand.cpp
  commands/changeexpirycommand.cpp
  commands/changeownertrustcommand.cpp
  commands/changeroottrustcommand.cpp
  commands/changepassphrasecommand.cpp
  commands/certifycertificatecommand.cpp
  commands/revokecertificationcommand.cpp
  commands/selftestcommand.cpp
  commands/exportsecretkeycommand.cpp
  commands/exportopenpgpcertstoservercommand.cpp
  commands/adduseridcommand.cpp
  commands/newcertificatecommand.cpp
  commands/setinitialpincommand.cpp
  commands/learncardkeyscommand.cpp
  commands/checksumcreatefilescommand.cpp
  commands/checksumverifyfilescommand.cpp
  commands/exportpaperkeycommand.cpp
  commands/importpaperkeycommand.cpp
  commands/genrevokecommand.cpp
  commands/keytocardcommand.cpp
  commands/cardcommand.cpp
  commands/pivgeneratecardkeycommand.cpp
  commands/changepincommand.cpp
  commands/authenticatepivcardapplicationcommand.cpp
  commands/setpivcardapplicationadministrationkeycommand.cpp
  commands/certificatetopivcardcommand.cpp
  commands/importcertificatefrompivcardcommand.cpp
  commands/createopenpgpkeyfromcardkeyscommand.cpp
  commands/createcsrforcardkeycommand.cpp

  ${_kleopatra_uiserver_files}

  conf/configuredialog.cpp
  conf/groupsconfigdialog.cpp
  conf/groupsconfigpage.cpp
  conf/groupsconfigwidget.cpp

  newcertificatewizard/listwidget.cpp
  newcertificatewizard/newcertificatewizard.cpp

  smartcard/readerstatus.cpp
  smartcard/card.cpp
  smartcard/openpgpcard.cpp
  smartcard/netkeycard.cpp
  smartcard/pivcard.cpp
  smartcard/p15card.cpp
  smartcard/keypairinfo.cpp
  smartcard/utils.cpp

  ${_kleopatra_deviceinfowatcher_files}

  aboutdata.cpp
  systrayicon.cpp
  kleopatraapplication.cpp
  mainwindow.cpp
  main.cpp
  kleopatra.qrc
)

if(WIN32)
  configure_file (versioninfo.rc.in versioninfo.rc)
  set(_kleopatra_SRCS ${CMAKE_CURRENT_BINARY_DIR}/versioninfo.rc ${_kleopatra_SRCS})
endif()

set (_kleopatra_SRCS conf/kleopageconfigdialog.cpp ${_kleopatra_SRCS})

ecm_qt_declare_logging_category(_kleopatra_SRCS HEADER kleopatra_debug.h IDENTIFIER KLEOPATRA_LOG CATEGORY_NAME org.kde.pim.kleopatra
        DESCRIPTION "kleopatra (kleopatra)"
        OLD_CATEGORY_NAMES log_kleopatra
        EXPORT KLEOPATRA
    )


if(KLEO_MODEL_TEST)
  add_definitions(-DKLEO_MODEL_TEST)
  set(_kleopatra_SRCS ${_kleopatra_SRCS} models/modeltest.cpp)
endif()

ki18n_wrap_ui(_kleopatra_SRCS
  dialogs/lookupcertificatesdialog.ui
  dialogs/ownertrustdialog.ui
  dialogs/selectchecklevelwidget.ui
  dialogs/selftestdialog.ui
  dialogs/adduseriddialog.ui
  dialogs/setinitialpindialog.ui
  dialogs/trustchainwidget.ui
  dialogs/subkeyswidget.ui
  newcertificatewizard/listwidget.ui
  newcertificatewizard/chooseprotocolpage.ui
  newcertificatewizard/enterdetailspage.ui
  newcertificatewizard/keycreationpage.ui
  newcertificatewizard/resultpage.ui
  newcertificatewizard/advancedsettingsdialog.ui
)

kconfig_add_kcfg_files(_kleopatra_SRCS
  kcfg/tooltippreferences.kcfgc
  kcfg/emailoperationspreferences.kcfgc
  kcfg/fileoperationspreferences.kcfgc
  kcfg/smimevalidationpreferences.kcfgc
  kcfg/tagspreferences.kcfgc
  kcfg/settings.kcfgc
)

file(GLOB ICONS_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/icons/*-apps-kleopatra.png")
ecm_add_app_icon(_kleopatra_SRCS ICONS ${ICONS_SRCS})

add_executable(kleopatra_bin ${_kleopatra_SRCS} ${_kleopatra_uiserver_SRCS})

# For the ConfigureDialog & KCMs
target_link_libraries(kleopatra_bin kcm_kleopatra_static)

#if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
#    set_target_properties(kleopatra_bin PROPERTIES UNITY_BUILD ON)
#endif()
set_target_properties(kleopatra_bin PROPERTIES OUTPUT_NAME kleopatra)

if (WIN32)
  set(_kleopatra_platform_libs "secur32")
endif ()

target_link_libraries(kleopatra_bin
  Gpgmepp
  QGpgme
  ${_kleopatra_extra_libs}
  KF5::Libkleo
  KF5::Mime
  KF5::I18n
  KF5::XmlGui
  KF5::IconThemes
  KF5::WindowSystem
  KF5::CoreAddons
  KF5::ItemModels
  KF5::Crash
  Qt::Network
  Qt::PrintSupport # Printing secret keys
  ${_kleopatra_uiserver_extra_libs}
  ${_kleopatra_dbusaddons_libs}
  kleopatraclientcore
  ${_kleopatra_platform_libs}
)

install(TARGETS kleopatra_bin ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(
  PROGRAMS data/org.kde.kleopatra.desktop data/kleopatra_import.desktop
  DESTINATION ${KDE_INSTALL_APPDIR}
)
install(FILES data/org.kde.kleopatra.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
install(
  FILES data/kleopatra_signencryptfiles.desktop
        data/kleopatra_signencryptfolders.desktop
        data/kleopatra_decryptverifyfiles.desktop
        data/kleopatra_decryptverifyfolders.desktop
  DESTINATION ${KDE_INSTALL_KSERVICES5DIR}/ServiceMenus
)
