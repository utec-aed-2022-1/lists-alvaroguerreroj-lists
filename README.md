[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=7514933&assignment_repo_type=AssignmentRepo)

# Lists

## Integrantes: Alvaro Guerrero Jiménez

## Description
Implementar todas las funciones en los .hpp

**T front();** // Retorna el elemento al comienzo

**T back();** // Retorna el elemento al final

**void push_front(T);** // Agrega un elemento al comienzo 

**void push_back(T);** // Agrega un elemento al final

**T pop_front();** // Remueve el elemento al comienzo

**T pop_back();** // Remueve el elemento al final

**void insert(T, int);** // Inserta en cualquier posición

**void remove(int);** // Remueve en cualquier posicion

**T operator\[](int);** // Retorna el elemento en la posición indicada

**bool is_empty();** // Retorna si la lista está vacía o no

**int size();** // Retorna el tamaño de la lista 

**void sort();** // Ordena los elementos de la lista

**void clear();** // Elimina todos los elementos de la lista

**void reverse();** // Revierte la lista


> Asegurarse de que el codigo compile sin errores.

> Asegurarse de que los tests pasen.

> Total de tests: 24

## Building

You may use [Nix](https://nixos.org/download.html) to setup the environment.

To set up the environment with Nix, run in the project directory…
```bash
nix-shell
```

Otherwise you need a C++ compiler,
[`meson`](https://github.com/mesonbuild/meson) and optionally
[`just`](https://github.com/casey/just).

You may call `meson` directly:

```bash
meson setup build/
meson compile -C build/
```

Or use `just`:

```bash
just setup
just build
```

The binary is left at `build/src/main`.
