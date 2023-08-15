cmake_minimum_required(VERSION 3.16)

project(speechwriter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_executable(appspeechwriter
    src/main.cpp
    src/application.cpp src/application.h
    src/controllers/document.cpp src/controllers/document.h
    src/data/sentence.cpp src/data/sentence.h
    src/models/sentencesmodel.cpp src/models/sentencesmodel.h
)

qt_add_qml_module(appspeechwriter
    URI speechwriter
    VERSION 1.0
    QML_FILES qml/main.qml
    qml/ui/DocumentForm.ui.qml qml/logic/Document.qml
    qml/ui/components/SimpleButtonForm.ui.qml qml/logic/components/SimpleButton.qml
    qml/ui/delegates/SentenceDelegateForm.ui.qml qml/logic/delegates/SentenceDelegate.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appspeechwriter PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appspeechwriter
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appspeechwriter
    PRIVATE Qt6::Quick)

include(GNUInstallDirs)
install(TARGETS appspeechwriter
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
