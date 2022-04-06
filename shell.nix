{ pkgs ? import <nixpkgs> { } }:

with pkgs;

mkShell {
  buildInputs = [
    clang_14
    gcc

    cling
    clang-tools
    valgrind
    gdb
    cgdb

    gnumake
    bear
    meson
    ninja
  ];

  nativeBuildInputs = [ clang_14 ];
}
