### Dotfiles for Void Linux

#### Applications
- sudo xbps-remove -R firefox-esr
- sudo xbps-install -S firefox wget git xtools nano gpick atom rofi viewnior flameshot task

#### XFCE
- sudo xbps-install -S file-roller xfce4-docklike-plugin xfce4-whiskermenu-plugin

#### Display Manager
To replace lxdm, which the default display manager for void xfce4, with lightdm:
- sudo xbps-install -S lightdm lightdm-gtk3-greeter lightdm-gtk-greeter-settings
- sudo rm /var/service/lxdm
Note: The above command will bounce you out of xfce and into terminal.  Take a note of the command below so that you can then enter it into the terminal:
- sudo ln -s /etc/sv/lightdm /var/service/
- see 'references' below if lightdm-webkit2-greeter is to be installed.

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
