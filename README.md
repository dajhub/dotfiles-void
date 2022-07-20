### Dotfiles for Void Linux

#### Void xfce Desktop with Everblush Theme
Link to everblush theming: https://github.com/Everblush

![Void - Everblush - xfce](https://i.imgur.com/TzirVcJ.png)

#### Applications & XFCE scripts
- see install script -- 'sudo ./install.sh'
	
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
	- sudo ln -s /etc/sv/virtlockd /var/service
	- sudo ln -s /etc/sv/virtlogd /var/service
- Making sure your user is part of the libvirt group:
	- sudo gpasswd -a "$USER" libvirt

### Miscellaneous
- Keyboard shortcut for rofi 'rofi -show drun'


#### Void Commands
- sudo xbps-install -Su         		### Update Package Lists
- xbps-query -Rs 				### Searching for Packages
- sudo xbps-install -S          		### Installing and Updating Packages
- xbps-query -l | grep vlc      		### Searching Through Installed Packages
- sudo xbps-remove -R           	### Remove a package with all its dependencies

#### My Own Aliases

Located at the end of .bashrc file

```
# Searching for a package:
alias xbs='xbps-query -Rs'

# Installing the package:
alias xbi='sudo xbps-install -S'

# System update:
alias xbu='sudo xbps-install -Su'

#Removing a package with all its dependencies:
alias xbr='sudo xbps-remove -R'

# Removing orphans and package cache:
alias xbo='sudo xbps-remove -Oo'

# Searching Through Installed Packages, e.g. add vlc after alias
alias xbsip='xbps-query -l | grep'
```

#### References
- https://linuxiac.com/void-linux-xbps-package-manager/
- theme for lightdm-webkit2-greeter -- https://github.com/thegamerhat/lightdm-glorious-webkit2
