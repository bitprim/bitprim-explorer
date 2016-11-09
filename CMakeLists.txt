scmake_policy(VERSION 3.4)

# bitprim-explorer
#==============================================================================
project(bitprim-explorer
  VERSION 3.0.0
  LANGUAGES CXX C)
cmake_minimum_required(VERSION 3.4)

# Check for baseline language coverage in the compiler for the C++11 standard.
#------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Process options.
#==============================================================================
# Implement --with-tests and declare WITH_TESTS.
#------------------------------------------------------------------------------
option(WITH_TESTS "Compile with unit tests." ON)

# Implement --with-console and declare WITH_CONSOLE.
#------------------------------------------------------------------------------
option(WITH_CONSOLE "Compile console application." ON)

# Inherit --enable-shared and define BOOST_TEST_DYN_LINK.
#------------------------------------------------------------------------------
option(ENABLE_SHARED "" OFF)

# Check dependencies.
#==============================================================================
# Require Boost of at least version 1.56.0 and output ${boost_CPPFLAGS/LDFLAGS}.
#------------------------------------------------------------------------------
if (NOT ENABLE_SHARED)
  set(Boost_USE_STATIC_LIBS ON)
endif()
find_package(
  Boost 1.54.0 REQUIRED
  COMPONENTS unit_test_framework)

# Require bitprim-client of at least version 3.0.0 and output ${bitprim_client_CPPFLAGS/LIBS/PKG}.
#------------------------------------------------------------------------------
if (NOT TARGET bitprim-client)
  find_package(bitprim-client 3.0.0 REQUIRED)
endif()

# Require bitprim-network of at least version 3.0.0 and output ${bitprim_network_CPPFLAGS/LIBS/PKG}.
if (NOT TARGET bitprim-network)
  find_package(bitprim-network 3.0.0 REQUIRED)
endif()

# Set flags.
#==============================================================================
include(CheckCXXCompilerFlag)

function(_add_c_compile_flag _Flag _Var)
  check_cxx_compiler_flag(${_Flag} ${_Var})
  if (${_Var})
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${_Flag}" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${_Flag}" )
  endif()
endfunction()

function(_add_cxx_compile_flag _Flag _Var)
  check_cxx_compiler_flag(${_Flag} ${_Var})
  if (${_Var})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${_Flag}" )
  endif()
endfunction()

function(_add_link_flag _Flag _Var)
  check_cxx_compiler_flag(${_Flag} ${_Var})
  if (${_Var})
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${_Flag}" )
    set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} ${_Flag}" )
  endif()
endfunction()

# Warn on all stuff.
#------------------------------------------------------------------------------
if (NOT MSVC)
  _add_c_compile_flag(-Wall _has_all_warning_flag)
else()
  _add_c_compile_flag(-W4 _has_all_warning_flag)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif()

# Warn on extra stuff.
#------------------------------------------------------------------------------
if (NOT MSVC)
  _add_c_compile_flag(-Wextra _has_extra_warning_flag)
endif()

# Be really annoying.
#------------------------------------------------------------------------------
_add_c_compile_flag(-Wpedantic _has_pedantic_warning_flag)
if (_has_pedantic_warning_flag)
  _add_c_compile_flag(-pedantic _has_pedantic_flag)
endif()

# Conform to style.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-Wno-missing-braces _has_no_missing_braces_warning_flag)

# Conflict in stdlib under clang. Enabled in clang only.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-Wno-mismatched-tags _has_no_mismatched_tags_warning_flag)

# Clean up boost 1.55 headers. Enabled in gcc only.
#------------------------------------------------------------------------------
_add_c_compile_flag(-Wno-deprecated-declarations _has_no_deprecated_declarations_warning_flag)

# Protect stack.
#------------------------------------------------------------------------------
_add_link_flag(-fstack-protector _has_stack_protector_flag)

# Protect stack comprehensively.
#------------------------------------------------------------------------------
_add_link_flag(-fstack-protector-all _has_stack_protector_all_flag)

# Hide internal functions from external libs. Enabled in gcc only.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-fvisibility-hidden _has_visibility_hidden_flag)

# Hide inlines from external libs. Enabled in gcc only.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-fvisibility-inlines-hidden _has_visibility_inlines_hidden_flag)

# Build
#==============================================================================
# src/bitprim-explorer.la => ${libdir}
#------------------------------------------------------------------------------
set(MODE STATIC)
if (ENABLE_SHARED)
  set(MODE SHARED)
endif()

add_library(bitprim-explorer ${MODE}
  src/callback_state.cpp
  src/dispatch.cpp
  src/display.cpp
  src/generated.cpp
  src/parser.cpp
  src/prop_tree.cpp
  src/utility.cpp
  src/commands/address-decode.cpp
  src/commands/address-embed.cpp
  src/commands/address-encode.cpp
  src/commands/base16-decode.cpp
  src/commands/base16-encode.cpp
  src/commands/base58-decode.cpp
  src/commands/base58-encode.cpp
  src/commands/base58check-decode.cpp
  src/commands/base58check-encode.cpp
  src/commands/base64-decode.cpp
  src/commands/base64-encode.cpp
  src/commands/bitcoin160.cpp
  src/commands/bitcoin256.cpp
  src/commands/btc-to-satoshi.cpp
  src/commands/cert-new.cpp
  src/commands/cert-public.cpp
  src/commands/ec-add-secrets.cpp
  src/commands/ec-add.cpp
  src/commands/ec-multiply-secrets.cpp
  src/commands/ec-multiply.cpp
  src/commands/ec-new.cpp
  src/commands/ec-to-address.cpp
  src/commands/ec-to-ek.cpp
  src/commands/ec-to-public.cpp
  src/commands/ec-to-wif.cpp
  src/commands/ek-address.cpp
  src/commands/ek-new.cpp
  src/commands/ek-public-to-address.cpp
  src/commands/ek-public-to-ec.cpp
  src/commands/ek-public.cpp
  src/commands/ek-to-address.cpp
  src/commands/ek-to-ec.cpp
  src/commands/fetch-balance.cpp
  src/commands/fetch-header.cpp
  src/commands/fetch-height.cpp
  src/commands/fetch-history.cpp
  src/commands/fetch-public-key.cpp
  src/commands/fetch-stealth.cpp
  src/commands/fetch-tx-index.cpp
  src/commands/fetch-tx.cpp
  src/commands/fetch-utxo.cpp
  src/commands/hd-new.cpp
  src/commands/hd-private.cpp
  src/commands/hd-public.cpp
  src/commands/hd-to-address.cpp
  src/commands/hd-to-ec.cpp
  src/commands/hd-to-public.cpp
  src/commands/hd-to-wif.cpp
  src/commands/help.cpp
  src/commands/input-set.cpp
  src/commands/input-sign.cpp
  src/commands/input-validate.cpp
  src/commands/message-sign.cpp
  src/commands/message-validate.cpp
  src/commands/mnemonic-decode.cpp
  src/commands/mnemonic-encode.cpp
  src/commands/mnemonic-new.cpp
  src/commands/mnemonic-to-seed.cpp
  src/commands/qrcode.cpp
  src/commands/ripemd160.cpp
  src/commands/satoshi-to-btc.cpp
  src/commands/script-decode.cpp
  src/commands/script-encode.cpp
  src/commands/script-to-address.cpp
  src/commands/seed.cpp
  src/commands/send-tx-node.cpp
  src/commands/send-tx-p2p.cpp
  src/commands/send-tx.cpp
  src/commands/settings.cpp
  src/commands/sha160.cpp
  src/commands/sha256.cpp
  src/commands/sha512.cpp
  src/commands/stealth-decode.cpp
  src/commands/stealth-encode.cpp
  src/commands/stealth-public.cpp
  src/commands/stealth-secret.cpp
  src/commands/stealth-shared.cpp
  src/commands/token-new.cpp
  src/commands/tx-decode.cpp
  src/commands/tx-encode.cpp
  src/commands/tx-sign.cpp
  src/commands/uri-decode.cpp
  src/commands/uri-encode.cpp
  src/commands/validate-tx.cpp
  src/commands/watch-address.cpp
  src/commands/watch-tx.cpp
  src/commands/wif-to-ec.cpp
  src/commands/wif-to-public.cpp
  src/commands/wrap-decode.cpp
  src/commands/wrap-encode.cpp
  src/config/address.cpp
  src/config/algorithm.cpp
  src/config/btc.cpp
  src/config/byte.cpp
  src/config/cert_key.cpp
  src/config/ec_private.cpp
  src/config/encoding.cpp
  src/config/endorsement.cpp
  src/config/hashtype.cpp
  src/config/hd_key.cpp
  src/config/header.cpp
  src/config/input.cpp
  src/config/language.cpp
  src/config/output.cpp
  src/config/point.cpp
  src/config/raw.cpp
  src/config/script.cpp
  src/config/signature.cpp
  src/config/transaction.cpp
  src/config/wrapper.cpp)
target_include_directories(bitprim-explorer PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_compile_definitions(bitprim-explorer PUBLIC -DBCX_STATIC)
if (NOT MSVC)
  target_compile_definitions(bitprim-explorer PUBLIC -DSYSCONFDIR=\"${SYSCONFDIR}\")
endif()

target_link_libraries(bitprim-explorer bitprim-client bitprim-network)

# Group sources
file(GLOB_RECURSE headers
  RELATIVE ${CMAKE_CURRENT_LIST_DIR}
  include/*.h include/*.hpp)
target_sources(bitprim-explorer PRIVATE "${headers}")

get_target_property(sources bitprim-explorer SOURCES)
foreach (source ${sources})
  get_filename_component(group ${source} DIRECTORY)
  if (MSVC)
    string(REPLACE "/" "\\" group ${group})
  endif()
  source_group("${group}" FILES ${source})
endforeach()

# local: test/bitprim_explorer_test
#------------------------------------------------------------------------------
if (WITH_TESTS)
  add_executable(bitprim_explorer_test
    test/generated__broadcast.cpp
    test/generated__find.cpp
    test/generated__formerly.cpp
    test/generated__symbol.cpp
    test/main.cpp
    test/commands/address-decode.cpp
    test/commands/address-embed.cpp
    test/commands/address-encode.cpp
    test/commands/base16-decode.cpp
    test/commands/base16-encode.cpp
    test/commands/base58-decode.cpp
    test/commands/base58-encode.cpp
    test/commands/base58check-decode.cpp
    test/commands/base58check-encode.cpp
    test/commands/base64-decode.cpp
    test/commands/base64-encode.cpp
    test/commands/bitcoin160.cpp
    test/commands/bitcoin256.cpp
    test/commands/btc-to-satoshi.cpp
    test/commands/cert-new.cpp
    test/commands/cert-public.cpp
    test/commands/command.hpp
    test/commands/ec-add-secrets.cpp
    test/commands/ec-add.cpp
    test/commands/ec-multiply-secrets.cpp
    test/commands/ec-multiply.cpp
    test/commands/ec-new.cpp
    test/commands/ec-to-address.cpp
    test/commands/ec-to-ek.cpp
    test/commands/ec-to-public.cpp
    test/commands/ec-to-wif.cpp
    test/commands/ek-address.cpp
    test/commands/ek-new.cpp
    test/commands/ek-public-to-address.cpp
    test/commands/ek-public-to-ec.cpp
    test/commands/ek-public.cpp
    test/commands/ek-to-address.cpp
    test/commands/ek-to-ec.cpp
    test/commands/fetch-balance.cpp
    test/commands/fetch-header.cpp
    test/commands/fetch-height.cpp
    test/commands/fetch-history.cpp
    test/commands/fetch-public-key.cpp
    test/commands/fetch-stealth.cpp
    test/commands/fetch-tx-index.cpp
    test/commands/fetch-tx.cpp
    test/commands/fetch-utxo.cpp
    test/commands/hd-new.cpp
    test/commands/hd-private.cpp
    test/commands/hd-public.cpp
    test/commands/hd-to-address.cpp
    test/commands/hd-to-ec.cpp
    test/commands/hd-to-public.cpp
    test/commands/hd-to-wif.cpp
    test/commands/help.cpp
    test/commands/input-set.cpp
    test/commands/input-sign.cpp
    test/commands/input-validate.cpp
    test/commands/message-sign.cpp
    test/commands/message-validate.cpp
    test/commands/mnemonic-decode.cpp
    test/commands/mnemonic-encode.cpp
    test/commands/mnemonic-new.cpp
    test/commands/mnemonic-to-seed.cpp
    test/commands/qrcode.cpp
    test/commands/ripemd160.cpp
    test/commands/satoshi-to-btc.cpp
    test/commands/script-decode.cpp
    test/commands/script-encode.cpp
    test/commands/script-to-address.cpp
    test/commands/seed.cpp
    test/commands/send-tx-node.cpp
    test/commands/send-tx-p2p.cpp
    test/commands/send-tx.cpp
    test/commands/settings.cpp
    test/commands/sha160.cpp
    test/commands/sha256.cpp
    test/commands/sha512.cpp
    test/commands/stealth-decode.cpp
    test/commands/stealth-encode.cpp
    test/commands/stealth-public.cpp
    test/commands/stealth-secret.cpp
    test/commands/stealth-shared.cpp
    test/commands/token-new.cpp
    test/commands/tx-decode.cpp
    test/commands/tx-encode.cpp
    test/commands/tx-sign.cpp
    test/commands/uri-decode.cpp
    test/commands/uri-encode.cpp
    test/commands/validate-tx.cpp
    test/commands/watch-address.cpp
    test/commands/watch-tx.cpp
    test/commands/wif-to-ec.cpp
    test/commands/wif-to-public.cpp
    test/commands/wrap-decode.cpp
    test/commands/wrap-encode.cpp
    test/config/address.cpp)
  if (ENABLE_SHARED)
    target_compile_definitions(bitprim_explorer_test PRIVATE -DBOOST_TEST_DYN_LINK)
  endif()
  target_link_libraries(bitprim_explorer_test bitprim-explorer)

  target_include_directories(bitprim_explorer_test SYSTEM PUBLIC ${Boost_INCLUDE_DIR})
  target_link_libraries(bitprim_explorer_test
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

  enable_testing()
  set(_bitprim_tests generated obsolete offline config stub)
  foreach (_test_name ${_bitprim_tests})
    add_test(
      NAME test.${_test_name}
      COMMAND bitprim_explorer_test
        --run_test=${_test_name}
        --show_progress=no
        --detect_memory_leak=0
        --report_level=no
        --build_info=yes)
  endforeach()
endif()

# console/bx => ${bindir}
#------------------------------------------------------------------------------
if (WITH_CONSOLE)
  add_executable(console.bx
    console/main.cpp)
  target_link_libraries(console.bx bitprim-explorer)

  set_target_properties(
    console.bx PROPERTIES
    OUTPUT_NAME bx)
endif()

# Install
#==============================================================================
install(TARGETS bitprim-explorer
  EXPORT bitprim-explorer
  ARCHIVE DESTINATION lib)

if (WITH_CONSOLE)
  install(TARGETS console.bx
    RUNTIME DESTINATION bin)
endif()

set(_bitprim_headers
  # include_bitcoin_HEADERS =
  bitcoin/explorer.hpp
  # include_bitcoin_explorer_HEADERS =
  bitcoin/explorer/callback_state.hpp
  bitcoin/explorer/command.hpp
  bitcoin/explorer/define.hpp
  bitcoin/explorer/dispatch.hpp
  bitcoin/explorer/display.hpp
  bitcoin/explorer/generated.hpp
  bitcoin/explorer/parser.hpp
  bitcoin/explorer/prop_tree.hpp
  bitcoin/explorer/utility.hpp
  bitcoin/explorer/version.hpp
  # include_bitcoin_explorer_commands_HEADERS =
  bitcoin/explorer/commands/address-decode.hpp
  bitcoin/explorer/commands/address-embed.hpp
  bitcoin/explorer/commands/address-encode.hpp
  bitcoin/explorer/commands/base16-decode.hpp
  bitcoin/explorer/commands/base16-encode.hpp
  bitcoin/explorer/commands/base58-decode.hpp
  bitcoin/explorer/commands/base58-encode.hpp
  bitcoin/explorer/commands/base58check-decode.hpp
  bitcoin/explorer/commands/base58check-encode.hpp
  bitcoin/explorer/commands/base64-decode.hpp
  bitcoin/explorer/commands/base64-encode.hpp
  bitcoin/explorer/commands/bitcoin160.hpp
  bitcoin/explorer/commands/bitcoin256.hpp
  bitcoin/explorer/commands/btc-to-satoshi.hpp
  bitcoin/explorer/commands/cert-new.hpp
  bitcoin/explorer/commands/cert-public.hpp
  bitcoin/explorer/commands/ec-add-secrets.hpp
  bitcoin/explorer/commands/ec-add.hpp
  bitcoin/explorer/commands/ec-multiply-secrets.hpp
  bitcoin/explorer/commands/ec-multiply.hpp
  bitcoin/explorer/commands/ec-new.hpp
  bitcoin/explorer/commands/ec-to-address.hpp
  bitcoin/explorer/commands/ec-to-ek.hpp
  bitcoin/explorer/commands/ec-to-public.hpp
  bitcoin/explorer/commands/ec-to-wif.hpp
  bitcoin/explorer/commands/ek-address.hpp
  bitcoin/explorer/commands/ek-new.hpp
  bitcoin/explorer/commands/ek-public-to-address.hpp
  bitcoin/explorer/commands/ek-public-to-ec.hpp
  bitcoin/explorer/commands/ek-public.hpp
  bitcoin/explorer/commands/ek-to-address.hpp
  bitcoin/explorer/commands/ek-to-ec.hpp
  bitcoin/explorer/commands/fetch-balance.hpp
  bitcoin/explorer/commands/fetch-header.hpp
  bitcoin/explorer/commands/fetch-height.hpp
  bitcoin/explorer/commands/fetch-history.hpp
  bitcoin/explorer/commands/fetch-public-key.hpp
  bitcoin/explorer/commands/fetch-stealth.hpp
  bitcoin/explorer/commands/fetch-tx-index.hpp
  bitcoin/explorer/commands/fetch-tx.hpp
  bitcoin/explorer/commands/fetch-utxo.hpp
  bitcoin/explorer/commands/hd-new.hpp
  bitcoin/explorer/commands/hd-private.hpp
  bitcoin/explorer/commands/hd-public.hpp
  bitcoin/explorer/commands/hd-to-address.hpp
  bitcoin/explorer/commands/hd-to-ec.hpp
  bitcoin/explorer/commands/hd-to-public.hpp
  bitcoin/explorer/commands/hd-to-wif.hpp
  bitcoin/explorer/commands/help.hpp
  bitcoin/explorer/commands/input-set.hpp
  bitcoin/explorer/commands/input-sign.hpp
  bitcoin/explorer/commands/input-validate.hpp
  bitcoin/explorer/commands/message-sign.hpp
  bitcoin/explorer/commands/message-validate.hpp
  bitcoin/explorer/commands/mnemonic-decode.hpp
  bitcoin/explorer/commands/mnemonic-encode.hpp
  bitcoin/explorer/commands/mnemonic-new.hpp
  bitcoin/explorer/commands/mnemonic-to-seed.hpp
  bitcoin/explorer/commands/qrcode.hpp
  bitcoin/explorer/commands/ripemd160.hpp
  bitcoin/explorer/commands/satoshi-to-btc.hpp
  bitcoin/explorer/commands/script-decode.hpp
  bitcoin/explorer/commands/script-encode.hpp
  bitcoin/explorer/commands/script-to-address.hpp
  bitcoin/explorer/commands/seed.hpp
  bitcoin/explorer/commands/send-tx-node.hpp
  bitcoin/explorer/commands/send-tx-p2p.hpp
  bitcoin/explorer/commands/send-tx.hpp
  bitcoin/explorer/commands/settings.hpp
  bitcoin/explorer/commands/sha160.hpp
  bitcoin/explorer/commands/sha256.hpp
  bitcoin/explorer/commands/sha512.hpp
  bitcoin/explorer/commands/stealth-decode.hpp
  bitcoin/explorer/commands/stealth-encode.hpp
  bitcoin/explorer/commands/stealth-public.hpp
  bitcoin/explorer/commands/stealth-secret.hpp
  bitcoin/explorer/commands/stealth-shared.hpp
  bitcoin/explorer/commands/token-new.hpp
  bitcoin/explorer/commands/tx-decode.hpp
  bitcoin/explorer/commands/tx-encode.hpp
  bitcoin/explorer/commands/tx-sign.hpp
  bitcoin/explorer/commands/uri-decode.hpp
  bitcoin/explorer/commands/uri-encode.hpp
  bitcoin/explorer/commands/validate-tx.hpp
  bitcoin/explorer/commands/watch-address.hpp
  bitcoin/explorer/commands/watch-tx.hpp
  bitcoin/explorer/commands/wif-to-ec.hpp
  bitcoin/explorer/commands/wif-to-public.hpp
  bitcoin/explorer/commands/wrap-decode.hpp
  bitcoin/explorer/commands/wrap-encode.hpp
  # include_bitcoin_explorer_config_HEADERS =
  bitcoin/explorer/config/address.hpp
  bitcoin/explorer/config/algorithm.hpp
  bitcoin/explorer/config/btc.hpp
  bitcoin/explorer/config/byte.hpp
  bitcoin/explorer/config/cert_key.hpp
  bitcoin/explorer/config/ec_private.hpp
  bitcoin/explorer/config/encoding.hpp
  bitcoin/explorer/config/endorsement.hpp
  bitcoin/explorer/config/hashtype.hpp
  bitcoin/explorer/config/hd_key.hpp
  bitcoin/explorer/config/header.hpp
  bitcoin/explorer/config/input.hpp
  bitcoin/explorer/config/language.hpp
  bitcoin/explorer/config/output.hpp
  bitcoin/explorer/config/point.hpp
  bitcoin/explorer/config/raw.hpp
  bitcoin/explorer/config/script.hpp
  bitcoin/explorer/config/signature.hpp
  bitcoin/explorer/config/transaction.hpp
  bitcoin/explorer/config/wrapper.hpp
  # include_bitcoin_explorer_impl_HEADERS =
  bitcoin/explorer/impl/prop_tree.ipp
  bitcoin/explorer/impl/utility.ipp)
foreach (_header ${_bitprim_headers})
  get_filename_component(_directory "${_header}" DIRECTORY)
  install(FILES "include/${_header}" DESTINATION "include/${_directory}")
endforeach()

# Export
#==============================================================================
include(CMakePackageConfigHelpers)

export(EXPORT bitprim-explorer
  FILE "${CMAKE_CURRENT_BINARY_DIR}/bitprim-explorerTargets.cmake")
export(PACKAGE bitprim-explorer)

if (UNIX)
  set(_config_package_location "lib/cmake")
elseif (WIN32)
  set(_config_package_location "cmake")
endif()

install(EXPORT bitprim-explorer
  FILE bitprim-explorerTargets.cmake
  DESTINATION ${_config_package_location})

configure_file(bitprim-explorerConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/bitprim-explorerConfig.cmake"
  @ONLY)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/bitprim-explorerConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/bitprim-explorerConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/bitprim-explorerConfigVersion.cmake"
  DESTINATION ${_config_package_location})
