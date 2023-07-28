cmake_minimum_required(VERSION 3.16)

SET(CMAKE_BUILD_TYPE Debug)
project(SSO-eve-authorization VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OPENSLL_FOR_ANDROID_PATH ${CMAKE_CURRENT_SOURCE_DIR}/android_openssl/ssl_1.1)
find_package(Qt6 6.2 REQUIRED COMPONENTS Quick Network NetworkAuth)

qt_add_executable(appSSO-eve-authorization
    main.cpp Authorization_engine.h Authorization_engine.cpp
    Tcp_server.h Tcp_server.cpp
    Validating_JWT.cpp Validating_JWT.h
)

qt_add_qml_module(appSSO-eve-authorization
    URI eve_authorization
    VERSION 1.0
    QML_FILES Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSSO-eve-authorization PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appuntitled
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSSO-eve-authorization
    PRIVATE Qt6::Quick Qt6::Network Qt6::NetworkAuth
)


if (ANDROID)
    if(CMAKE_ANDROID_ARCH_ABI STREQUAL "x86")
        target_link_libraries(appSSO-eve-authorization PRIVATE
            ${OPENSLL_FOR_ANDROID_PATH}/x86/libcrypto_1_1.so
            ${OPENSLL_FOR_ANDROID_PATH}/x86/libssl_1_1.so
        )
    elseif(CMAKE_ANDROID_ARCH_ABI STREQUAL "x86_64")
        target_link_libraries(appSSO-eve-authorization PRIVATE
            ${OPENSLL_FOR_ANDROID_PATH}/x86_64/libcrypto_1_1.so
            ${OPENSLL_FOR_ANDROID_PATH}/x86_64/libssl_1_1.so
        )
    elseif(CMAKE_ANDROID_ARCH_ABI STREQUAL "armeabi-v7a")
        target_link_libraries(appSSO-eve-authorization PRIVATE
        ${OPENSLL_FOR_ANDROID_PATH}/armeabi-v7a/libcrypto_1_1.so
        ${OPENSLL_FOR_ANDROID_PATH}/armeabi-v7a/libssl_1_1.so
    )
    elseif(CMAKE_ANDROID_ARCH_ABI STREQUAL "arm64-v8a")
        target_link_libraries(appSSO-eve-authorization PRIVATE
        ${OPENSLL_FOR_ANDROID_PATH}/arm64-v8a/libcrypto_1_1.so
        ${OPENSLL_FOR_ANDROID_PATH}/arm64-v8a/libssl_1_1.so
    )
    else()
        message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
    endif()
else()
    target_link_libraries(appSSO-eve-authorization PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party-lib/openssl/libssl.a
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party-lib/openssl/libcrypto.a

    )
endif()


target_include_directories(appSSO-eve-authorization
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/android_openssl/ssl_1.1/include
)


include(GNUInstallDirs)
install(TARGETS appSSO-eve-authorization
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
