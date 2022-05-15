### Dotfiles for Void Linux

#### Applications
- sudo xbps-remove -R firefox-esr
- sudo xbps-install -S firefox wget git xtools nano gpick atom rofi viewnior flameshot task vlc tlp
- to enable tlp: 'sudo tlp start'

#### XFCE
- sudo xbps-install -S file-roller xfce4-docklike-plugin xfce4-whiskermenu-plugin xfce4-pulseaudio-plugin

#### Void - Additional Repositories
- sudo xbps-install void-repo-nonfree
- sudo xbps-install void-repo-multilib-nonfree

#### Display Manager
To replace lxdm, which the default display manager for void xfce4, with lightdm:
- sudo xbps-install -S lightdm lightdm-gtk3-greeter lightdm-gtk-greeter-settings
- sudo rm /var/service/lxdm
Note: The above command will bounce you out of xfce and into a terminal.  Take a note of the command below so that you can then enter it into the terminal once you've been bounced out:
- sudo ln -s /etc/sv/lightdm /var/service/
- see 'references' below if lightdm-webkit2-greeter is to be installed.

#### Virtual Machine - QEMU/KVM
- sudo xbps-install -S virt-manager libvirt qemu
- Start the services that are created by these packages:
	- sudo ln -s /etc/sv/libvirtd /var/service
	-sudo ln -s /etc/sv/virtlockd /var/service
	-sudo ln -s /etc/sv/virtlogd /var/service
- Making sure your user is part of the libvirt group:
	- sudo gpasswd -a "$USER" libvirt

### Miscellaneous
- Keyboard shortcut for rofi 'rofi -show drun'
- Xfce panel settings:
	- Display
		- mode: deskbar
		- Row size: 40 pixels


#### Void Commands
- sudo xbps-install -Su         		### Update Package Lists
- xbps-query -Rs 										### Searching for Packages
- sudo xbps-install -S          		### Installing and Updating Packages
- xbps-query -l | grep vlc      		### Searching Through Installed Packages
- sudo xbps-remove -R           		### Remove a package with all its dependencies


#### References
- https://linuxiac.com/void-linux-xbps-package-manager/
- theme for lightdm-webkit2-greeter -- https://github.com/thegamerhat/lightdm-glorious-webkit2
