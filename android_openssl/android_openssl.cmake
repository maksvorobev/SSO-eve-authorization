function(add_android_openssl_libraries)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set (ssl_root_path ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/no-asm)
    else()
        set (ssl_root_path ${CMAKE_CURRENT_FUNCTION_LIST_DIR})
    endif()

    if (Qt6_VERSION VERSION_GREATER_EQUAL 6.5.0)
        list(APPEND android_extra_libs
            ${ssl_root_path}/ssl_3/${CMAKE_ANDROID_ARCH_ABI}/libcrypto.a
            ${ssl_root_path}/ssl_3/${CMAKE_ANDROID_ARCH_ABI}/libssl.a)
    else()
        list(APPEND android_extra_libs
            ${ssl_root_path}/ssl_1.1/${CMAKE_ANDROID_ARCH_ABI}/libcrypto.a
            ${ssl_root_path}/ssl_1.1/${CMAKE_ANDROID_ARCH_ABI}/libssl.a)
    endif()

    set_target_properties(${ARGN} PROPERTIES
        QT_ANDROID_EXTRA_LIBS "${android_extra_libs}")
endfunction()
