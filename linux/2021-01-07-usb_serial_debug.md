
[index](./index.md)

# usb_serial_debug

---

Author:sandylaw

Email :freelxs@gmail.com

Date  :2021-01-07

tags  :linux

---

## Install minicom
```bash
sudo apt install minicom
```
## Setup minicom
```bash
sudo minicom -s
```
- Serial port setup:
- - A Serial Device: /dev/ttyUSB0
- - E Bps/Par/Bits : 115200 8N1
- - F Hardware Flow Control: Yes
- - press enter to comfirm.
- - Save settings：choose "Save setup as dfl"

## Modify /etc/default/grub

```bash
GRUB_SERIAL_COMMAND="serial --speed=115200 --unit=0 --word=8 --parity=no
--stop=1"
GRUB_TERMINAL="serial console" 
GRUB_CMDLINE_LINUX add "console=ttyS0,115200" and remove `quiet` from CMDLINE
```

## Debug 

```bash
sudo minicom -c on
```
主程序界面进入设置：
`Ctrl+A Z --> O`

