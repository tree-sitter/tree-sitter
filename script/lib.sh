#!/usr/bin/env bash

function scan_build {
  extra_args=()

  # AFAICT, in the trusty travis container the scan-build tool is from the 3.4
  # installation. Therefore, by default it will use clang-3.4 when analysing code
  # which doesn't support the '-std=c++14' (it is available via '-std=c++1y').
  # Use the system-wide installed clang instead which is 3.5 and does support
  # '-std=c++14'.
  extra_args+=("--use-analyzer=$(which clang)")

  # scan-build will try to guess which CXX should be used to compile the actual
  # code, which is usually g++ but we need g++5 in the CI. Explicitly pass
  # $CC/$CXX to scan-build if they are set in the environment.

  if [[ ! -z "$CC" ]]; then
    extra_args+=("--use-cc=$CC")
  fi

  if [[ ! -z "$CXX" ]]; then
    extra_args+=("--use-c++=$CXX")
  fi

  scan-build "${extra_args[@]}" --status-bugs -disable-checker deadcode.DeadStores "$@"
}
