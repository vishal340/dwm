# dwm version
VERSION = 6.4

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib

# Xinerama, comment if you don't want it
XINERAMALIBS  = -lXinerama
XINERAMAFLAGS = -DXINERAMA

# freetype
FREETYPELIBS = -lfontconfig -lXft
FREETYPEINC = /nix/store/4q1b6baa364dx88s3h5dz4np2a0zsnrl-freetype-2.13.2-dev/include
# OpenBSD (uncomment)
#FREETYPEINC = ${X11INC}/freetype2
#MANPREFIX = ${PREFIX}/man

# includes and libs
INCS = -I${X11INC} -I${FREETYPEINC} -I/nix/store/vj8zbmb5fzz9i5vs9nn904k7x8f21y8w-libX11-1.8.7-dev/include -I/nix/store/nzw7krhdm0ijbfmskvqrzw9nabqygv18-xorgproto-2023.2/include -I/nix/store/15irnnkhrrmbik3wba57h1y0wvp8avdw-libXft-2.3.8-dev/include -I/nix/store/vb04m4a3qjlv036nv0zgfzmr5scyhfnw-fontconfig-2.14.2-dev/include -I/nix/store/7cqygan2568h6aisf9dnchs01spdkn4d-libXrender-0.9.11-dev/include -I/nix/store/q0fxqx0xbp3i19q1qmvr4k7389w1vzy3-libXinerama-1.1.5-dev/include -L/nix/store/b7pb0mmcwjp973nj8gcaa2fnmqxckc8q-libX11-1.8.7/lib -L/nix/store/mrfp92a9spc7achfy7j0h4hkb6kzs39i-fontconfig-2.14.2-lib/lib -L/nix/store/8ysw1ca4nl7pg0gxd7mmkrqxrmsacwhg-libXft-2.3.8/lib -L/nix/store/hz1wk4b8xk1ra2dbrg5y9an2klh8plvq-libXinerama-1.1.5/lib

LIBS = -L${X11LIB} -lX11 ${XINERAMALIBS} ${FREETYPELIBS}

# flags
CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700L -DVERSION=\"${VERSION}\" ${XINERAMAFLAGS}
#CFLAGS   = -g -std=c99 -pedantic -Wall -O0 ${INCS} ${CPPFLAGS}
CFLAGS   = -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os ${INCS} ${CPPFLAGS}

LDFLAGS  = ${LIBS}

# Solaris
#CFLAGS = -fast ${INCS} -DVERSION=\"${VERSION}\"
#LDFLAGS = ${LIBS}

# compiler and linker
CC = cc
