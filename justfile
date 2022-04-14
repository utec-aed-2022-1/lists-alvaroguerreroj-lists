# -*- mode: just; -*-

build_dir := "build/"

build: _build_exists
    meson compile -C {{build_dir}}

setup:
    meson setup {{build_dir}}

resetup: clean setup

clean: _build_exists
    rm -rf {{build_dir}}

format: _build_exists
    ninja -C {{build_dir}} clang-format

_build_exists:
    test -d {{build_dir}}
