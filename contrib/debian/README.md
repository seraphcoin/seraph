
Debian
====================
This directory contains files used to package seraphd/seraph-qt
for Debian-based Linux systems. If you compile seraphd/seraph-qt yourself, there are some useful files here.

## seraph: URI support ##


seraph-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install seraph-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your seraphqt binary to `/usr/bin`
and the `../../share/pixmaps/seraph128.png` to `/usr/share/pixmaps`

seraph-qt.protocol (KDE)

