#!/usr/bin/env bash
#
# setup-deps.sh — instala as dependências de compilação do matplotc.
#
# O matplotc tem uma única dependência externa: a biblioteca raylib
# (cabeçalho + biblioteca). No Linux, a raylib ainda requer os cabeçalhos de
# desenvolvimento de X11 e OpenGL, então o script cuida disso também.
#
# Uso:
#   ./scripts/setup-deps.sh
#   PREFIX=$HOME/.local ./scripts/setup-deps.sh
#   RAYLIB_VERSION=5.5.0 ./scripts/setup-deps.sh
#
# Variáveis:
#   PREFIX          (padrão: $HOME/.local)  onde a raylib será instalada se
#                                           precisar ser compilada do zero.
#   RAYLIB_VERSION  (padrão: 5.5.0)         versão usada na compilação local.
#
# O script é idempotente: se a raylib já estiver disponível, ele apenas avisa
# e termina com sucesso.
#
set -euo pipefail

PREFIX="${PREFIX:-$HOME/.local}"
RAYLIB_VERSION="${RAYLIB_VERSION:-5.5.0}"
DIST_URL="https://github.com/raysan5/raylib/archive/refs/tags"

say()  { printf '\033[1;34m==>\033[0m %s\n' "$*"; }
warn() { printf '\033[1;33m!!\033[0m %s\n' "$*" >&2; }
die()  { printf '\033[1;31mERRO:\033[0m %s\n' "$*" >&2; exit 1; }

have() { command -v "$1" >/dev/null 2>&1; }

usage() {
    sed -n '2,26p' "$0" | sed 's/^# \{0,1\}//'
}

if [ "${1:-}" = "-h" ] || [ "${1:-}" = "--help" ]; then
    usage
    exit 0
fi

# Verificar compilador C
if have gcc; then
    CC="${CC:-gcc}"
elif have cc; then
    CC="${CC:-cc}"
else
    die "nenhum compilador C encontrado (instale gcc/cc)."
fi

# raylib já está disponível?
raylib_ok() {
    if have pkg-config && pkg-config --exists raylib 2>/dev/null; then
        return 0
    fi
    # tenta compilar um pequeno programa, cobrindo instalações sem .pc
    printf '#include <raylib.h>\nint main(void){return 0;}\n' \
        | "$CC" -x c - -o /dev/null 2>/dev/null
}

if raylib_ok; then
    say "raylib já está instalada: $( (have pkg-config && pkg-config --modversion raylib 2>/dev/null) || echo 'disponível' )"
    exit 0
fi

# Gerenciador de pacotes
detect_pm() {
    if   have apt-get; then echo apt
    elif have dnf;     then echo dnf
    elif have pacman;  then echo pacman
    elif have zypper;  then echo zypper
    elif have apk;     then echo apk
    else                    echo none
    fi
}

PM="$(detect_pm)"
MSYS2_PREFIX=""
if [ "$PM" = pacman ] && [ -n "${MSYSTEM:-}" ]; then
    case "$MSYSTEM" in
        MINGW32)    MSYS2_PREFIX="mingw-w64-i686" ;;
        MINGW64)    MSYS2_PREFIX="mingw-w64-x86_64" ;;
        UCRT64)     MSYS2_PREFIX="mingw-w64-ucrt-x86_64" ;;
        CLANG32)    MSYS2_PREFIX="mingw-w64-clang-i686" ;;
        CLANG64)    MSYS2_PREFIX="mingw-w64-clang-x86_64" ;;
        CLANGARM64) MSYS2_PREFIX="mingw-w64-clang-aarch64" ;;
        MSYS)       die "abra um shell MINGW64, UCRT64 ou CLANG64 do MSYS2 para instalar a raylib." ;;
        *)          die "ambiente MSYS2 não reconhecido: MSYSTEM=$MSYSTEM" ;;
    esac
fi

if [ "$(id -u)" -ne 0 ] && have sudo; then
    SUDO="sudo"
else
    SUDO=""
fi

# raylib já está disponível?
raylib_ok() {
    if have pkg-config && pkg-config --exists raylib 2>/dev/null; then
        return 0
    fi
    # tenta compilar um pequeno programa, cobrindo instalações sem .pc
    printf '#include <raylib.h>\nint main(void){return 0;}\n' \
        | "$cc" -x c - -o /dev/null 2>/dev/null
}

if raylib_ok; then
    say "raylib já está instalada: $( (have pkg-config && pkg-config --modversion raylib 2>/dev/null) || echo 'disponível' )"
    exit 0
fi

install_system_deps() {
    say "Instalando dependências de sistema (gerenciador: $PM)"
    case "$PM" in
        apt)
            $SUDO apt-get update -qq || true
            $SUDO apt-get install -y --no-install-recommends \
                build-essential pkg-config git \
                libasound2-dev libx11-dev libxrandr-dev libxi-dev \
                libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev
            ;;
        dnf)
            $SUDO dnf install -y gcc make pkgconf-pkg-config git \
                alsa-lib-devel mesa-libGL-devel mesa-libGLU-devel \
                libX11-devel libXrandr-devel libXinerama-devel \
                libXi-devel libXcursor-devel
            ;;
        pacman)
            if [ -n "$MSYS2_PREFIX" ]; then
                $SUDO pacman -S --needed --noconfirm \
                    "${MSYS2_PREFIX}-gcc" "${MSYS2_PREFIX}-pkgconf" \
                    git make tar curl
            else
                $SUDO pacman -Sy --needed --noconfirm \
                    base-devel pkgconf git alsa-lib \
                    mesa libx11 libxrandr libxinerama libxi libxcursor
            fi
            ;;
        zypper)
            $SUDO zypper --non-interactive install \
                gcc make pkg-config git alsa-devel Mesa-libGL-devel Mesa-libGLU-devel \
                libX11-devel libXrandr-devel libXinerama-devel \
                libXi-devel libXcursor-devel
            ;;
        apk)
            $SUDO apk add --no-cache build-base pkgconf git alsa-lib-dev \
                mesa-dev glu-dev libx11-dev libxrandr-dev libxinerama-dev \
                libxi-dev libxcursor-dev
            ;;
        *)
            warn "nenhum gerenciador de pacotes conhecido."
            warn "Instale manualmente: compilador C, make, git e os cabeçalhos"
            warn "de desenvolvimento de X11/OpenGL, depois rode este script de novo."
            ;;
    esac
}

# raylib via pacote da distro (melhor esforço)
install_raylib_package() {
    local pkg
    case "$PM" in
        apt)    pkg="libraylib-dev" ;;
        dnf)    pkg="raylib-devel" ;;
        pacman)
            if [ -n "$MSYS2_PREFIX" ]; then
                pkg="${MSYS2_PREFIX}-raylib"
            else
                pkg="raylib"
            fi
            ;;
        zypper) pkg="raylib-devel" ;;
        apk)    pkg="raylib-dev" ;;
        *)      return 1 ;;
    esac
    say "Tentando instalar a raylib pelo gerenciador de pacotes ($pkg)"
    case "$PM" in
        apt)
            $SUDO apt-get install -y --no-install-recommends "$pkg" ;;
        dnf)
            $SUDO dnf install -y "$pkg" ;;
        pacman)
            $SUDO pacman -S --needed --noconfirm "$pkg" ;;
        zypper)
            $SUDO zypper --non-interactive install "$pkg" ;;
        apk)
            $SUDO apk add --no-cache "$pkg" ;;
    esac
}

# Download
download() {
    local url="$1" dest="$2"
    if have curl; then
        curl -fL --retry 3 -o "$dest" "$url"
    elif have wget; then
        wget -O "$dest" "$url"
    else
        die "é preciso curl ou wget para baixar a raylib."
    fi
}

# Compilação da raylib a partir do código-fonte
build_raylib_from_source() {
    have make || die "make não encontrado (instale o build-essential)."
    have tar  || die "tar não encontrado."

    local tmp srcdir tarball
    tmp="$(mktemp -d)"
    trap 'rm -rf "$tmp"' EXIT
    tarball="$tmp/raylib.tar.gz"

    say "Baixando raylib ${RAYLIB_VERSION} (${DIST_URL}/${RAYLIB_VERSION}.tar.gz)"
    download "${DIST_URL}/${RAYLIB_VERSION}.tar.gz" "$tarball"

    tar -xzf "$tarball" -C "$tmp"
    srcdir="$(find "$tmp" -maxdepth 1 -type d -name 'raylib-*' | head -n1)"
    [ -n "$srcdir" ] || die "não foi possível localizar o código-fonte da raylib."

    say "Compilando a raylib (pode levar alguns minutos)"
    make -C "$srcdir/src" RAYLIB_LIBTYPE=SHARED -j"$( (nproc 2>/dev/null) || echo 2 )"

    say "Instalando a raylib em $PREFIX"
    mkdir -p "$PREFIX"
    make -C "$srcdir/src" RAYLIB_LIBTYPE=SHARED \
        RAYLIB_INSTALL_PATH="$PREFIX" install
}


install_system_deps


if ! install_raylib_package; then
    warn "a raylib não está disponível como pacote da distribuição."
fi

if ! raylib_ok && ! { have pkg-config && PKG_CONFIG_PATH="$PREFIX/lib/pkgconfig" pkg-config --exists raylib 2>/dev/null; }; then
    say "A raylib não foi encontrada; será compilada do zero."
    build_raylib_from_source
fi

# Verificação final
if have pkg-config && PKG_CONFIG_PATH="$PREFIX/lib/pkgconfig" pkg-config --exists raylib 2>/dev/null; then
    say "raylib $(pkg-config --modversion raylib 2>/dev/null || echo "$RAYLIB_VERSION") pronta em $PREFIX"
    echo
    echo "Compile o matplotc indicando a instalação local:"
    echo
    echo "    make RAYLIB_PREFIX=$PREFIX"
    echo
    echo "Ou exporte no seu shell:"
    echo
    echo "    export PKG_CONFIG_PATH=\"$PREFIX/lib/pkgconfig:\${PKG_CONFIG_PATH:-}\""
    echo "    export LD_LIBRARY_PATH=\"$PREFIX/lib:\${LD_LIBRARY_PATH:-}\""
elif raylib_ok; then
    say "raylib disponível no sistema."
else
    warn "não foi possível confirmar a instalação da raylib."
    warn "Instale a raylib manualmente e rode 'make check-deps'."
    exit 1
fi
