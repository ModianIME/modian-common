include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

if (MSVC)
    add_compile_options("/utf-8")
endif()

add_executable(scriptorium_felt_tests
    core/protocol/key_event_test.cpp
    infra/ipc/sync_named_pipe_client_test.cpp
    infra/utils/string_utils_test.cpp
    service/protocol/input_protocol_service_test.cpp
    service/protocol/ui_protocol_service_test.cpp
)

target_link_libraries(scriptorium_felt_tests PRIVATE
    scriptorium::felt::core::ipc
    scriptorium::felt::core::protocol
    scriptorium::felt::service::protocol
    scriptorium::felt::infra::utils
    scriptorium::felt::infra::ipc
    GTest::gtest_main
    GTest::gmock
)

include(GoogleTest)
gtest_discover_tests(scriptorium_felt_tests)
