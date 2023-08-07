if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set (SSL_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR}/no-asm)
else()
    set (SSL_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR})
endif()

if (Qt6_VERSION VERSION_GREATER_EQUAL 6.5.0)
    list(APPEND ANDROID_EXTRA_LIBS
        ${SSL_ROOT_PATH}/ssl_3/${CMAKE_ANDROID_ARCH_ABI}/libcrypto.a
        ${SSL_ROOT_PATH}/ssl_3/${CMAKE_ANDROID_ARCH_ABI}/libssl.a)
else()
    list(APPEND ANDROID_EXTRA_LIBS
        ${SSL_ROOT_PATH}/ssl_1.1/${CMAKE_ANDROID_ARCH_ABI}/libcrypto.a
        ${SSL_ROOT_PATH}/ssl_1.1/${CMAKE_ANDROID_ARCH_ABI}/libssl.a)
endif()

set_target_properties(appeve_authorization PROPERTIES
    QT_ANDROID_EXTRA_LIBS "${ANDROID_EXTRA_LIBS}")
