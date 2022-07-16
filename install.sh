#!/bin/bash

# ---

echo 'Update ...'

sudo xbps-install -Su

# ---

echo 'Remove Firefox-ESR...'

sudo xbps-remove -R firefox-esr

# ---

echo 'Void - Additional Repositories ...' 

sudo xbps-install void-repo-nonfree
sudo xbps-install void-repo-multilib-nonfree
sudo xbps-install -Su

# ---

echo 'Install Void packages...'

sudo xbps-install -S \
	xfce4-docklike-plugin \
	xfce4-whiskermenu-plugin \
	firefox \
	geany \
	viewnior \
	gcolor2 \
	flameshot \
	abiword \
	kitty \
	rofi \
	task \
	wget \
	nano \
	tlp \
	vlc \
	plank \
	xarchiver \
	unzip \
	fontmanager \
	htop \
	neofetch \
	vscode \
	file-roller \
	catfish \
	pfetch

# ---

echo 'Install fonts...'

sudo xbps-install -S \
	noto-fonts-cjk \
	nerd-fonts

# ---

echo 'Install Flatpak...'

sudo xbps-install -S flatpak
flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo


# ---

echo 'tlp start...'

sudo tlp start

# ---

echo 'Finished --> Restart computer for Flatpak to take effect...'