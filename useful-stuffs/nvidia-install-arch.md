

1) install nvidia driver from aur

```bash
aurman -S nvidia-vulkan
```

2) install nvidia-xrun (will install bbswitch also -- to switch on/off nvidia card easily)

```bash
aurman -S nvidia-xrun
```

3) install another DE

```bash
sudo pacman -S openbox
```

4) turn off nvidia-card on boot (using bbswitch)

```bash
echo 'bbswitch ' | sudo tee /etc/modules-load.d/bbswitch.conf
echo 'options bbswitch load_state=0 unload_state=1' | sudo tee /etc/modprobe.d/bbswitch.conf
```

5) disable NVIDIA's module from loading on boot

```bash
$ cat /etc/modprobe.d/no-nvidia.conf

blacklist nvidia 
blacklist nvidia_drm 
blacklist nouveau
```

6) auto-start openbox when running `nvidia-xrun`

```bash
$ cat ~/.nvidia-xinitrc

if [ $# -gt 0 ]; then
    $*
else
    openbox-session
#   startkde
fi
```

7) NOTES

- don't need manual xorg.conf as we by default will start on Intel. Intel need no special configuration (unlike Nvidia, fuck you).
- special SDDM setup (such as Xsetup) isn't needed anymore

## REFERENCES
http://www.cnblogs.com/tsreaper/p/arch-config.html
https://blog.isima-f5.fr/blog/sygems_nvidia-xrun