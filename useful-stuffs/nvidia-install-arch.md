

#### 1) install nvidia driver from aur

```bash
$ yay -S nvidia-vulkan opencl-nvidia-vulkan lib32-opencl-nvidia-vulkan nvidia-vulkan-utils lib32-nvidia-vulkan-utils
```

#### 2) install nvidia-xrun (will install bbswitch also -- to switch on/off nvidia card easily)

```bash
$ yay -S nvidia-xrun
```

#### 3) install another DE

```bash
$ sudo pacman -S openbox 
```

#### 4) configure Openbox to be usable (**OPTIONAL!**)
```
$ yay -S tint2 obmenu-generator pcmanfm-qt nitrogen compton

$ echo "tint2 &" | tee -a ~/.config/openbox/autostart               # simple panel
$ echo "nitrogen --restore &" | tee -a ~/.config/openbox/autostart  # wallpaper
$ echo "compton &" | tee -a ~/.config/openbox/autostart             # compositor

$ wget https://bit.ly/2FnyN8C -O ~/.config/openbox/menu.xml         # automatic generate menu + icons
$ wget https://bit.ly/2zFCj8a -O ~/.config/tint2/tint2rc            # very simple tint2 config
$ obmenu-generator # run once

$ wget https://i.imgur.com/6NoM2aL.png -O ~/Pictures/openbox-wallpaper.png
$ nitrogen ~/Pictures/                                             # apply wallpaper

```

- if want ctrl+alt+t Konsole shortcut, see this: https://askubuntu.com/questions/917382/how-to-run-commands-in-openbox
     - tips: use C-A-t as its key, `Konsole` as its command

- edit obmenu-generator's config for specifying correct program to run at menu
     - edit both of these file
        - ~/.config/obmenu-generator/config.pl  (advise: use `pcmanfm-qt` as your file manager)
        - ~/.config/obmenu-generator/schema.pl (advise: use `kate` instead of `geany` as default text editor)

#### 5) turn off nvidia-card on boot (using bbswitch)

```bash
$ echo 'bbswitch ' | sudo tee /etc/modules-load.d/bbswitch.conf
$ echo 'options bbswitch load_state=0 unload_state=1' | sudo tee /etc/modprobe.d/bbswitch.conf
```

#### 6) disable NVIDIA's modules from loading on boot

```bash
$ cat /etc/modprobe.d/no-nvidia.conf

blacklist nvidia 
blacklist nvidia_drm 
blacklist nouveau
```

#### 7) auto-start openbox when running `nvidia-xrun`

```bash
$ cat ~/.nvidia-xinitrc

if [ $# -gt 0 ]; then
    $*
else
    openbox-session
#   startkde
fi
```

#### 8) NOTES

- don't need manual xorg.conf as we by default will start on Intel. Intel need no special configuration (unlike Nvidia, fuck you).
- special SDDM setup (such as Xsetup) isn't needed anymore
- If got "exec error" when running `nvidia-xrun`, most probably that you've updated your Kernel without rebuilding Nvidia's driver module back. This happen when you're using `nvidia-vulkan` package from AUR. To fix, simply follow these two commands:
    - `$ rm -rf ~/.cache/yay/nvidia-vulkan/*.xz  # remove old build cache`
    - `$ yay -S nvidia-vulkan  # reinstall (thus rebuild for existing kernel version)`

## REFERENCES
* https://github.com/Witko/nvidia-xrun 
* https://wiki.archlinux.org/index.php/nvidia-xrun 
* https://wiki.archlinux.org/index.php/NVIDIA_Optimus 
* http://www.cnblogs.com/tsreaper/p/arch-config.html 
* https://blog.isima-f5.fr/blog/sygems_nvidia-xrun
