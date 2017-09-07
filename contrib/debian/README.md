
Debian
====================
This directory contains files used to package mxnd/mxn-qt
for Debian-based Linux systems. If you compile mxnd/mxn-qt yourself, there are some useful files here.

## mxn: URI support ##


mxn-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install mxn-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your mxn-qt binary to `/usr/bin`
and the `../../share/pixmaps/mxn128.png` to `/usr/share/pixmaps`

mxn-qt.protocol (KDE)

