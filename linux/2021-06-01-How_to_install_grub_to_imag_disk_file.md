
[index](./index.md)

# How to install grub to imag disk file 

---

Author:sandylaw

Email :freelxs@gmail.com

Date  :2021-06-01

tags  :

---

- 创建一个img空文件 6000M
```bash
dd if=/dev/zero of=sys.img bs=1M count=0 seek=6000
```

- 对img文件进行分区，划分为3个分区，efi，boot，根分区。
```bash

 fdisk sys.img

Welcome to fdisk (util-linux 2.33.1).
Changes will remain in memory only, until you decide to write them.
Be careful before using the write command.

Device does not contain a recognized partition table.
Created a new DOS disklabel with disk identifier 0xdea370dd.

Command (m for help): g
Created a new GPT disklabel (GUID: 1EB967F0-A476-244A-A66B-9837FACAA81D).

Command (m for help): n
Partition number (1-128, default 1):
First sector (2048-12287966, default 2048):
Last sector, +/-sectors or +/-size{K,M,G,T,P} (2048-12287966, default 12287966): +300M

Created a new partition 1 of type 'Linux filesystem' and of size 300 MiB.

Command (m for help): n
Partition number (2-128, default 2):
First sector (616448-12287966, default 616448):
Last sector, +/-sectors or +/-size{K,M,G,T,P} (616448-12287966, default 12287966): +1G

Created a new partition 2 of type 'Linux filesystem' and of size 1 GiB.

Command (m for help): n
Partition number (3-128, default 3):
First sector (2713600-12287966, default 2713600):
Last sector, +/-sectors or +/-size{K,M,G,T,P} (2713600-12287966, default 12287966):

Created a new partition 3 of type 'Linux filesystem' and of size 4.6 GiB.

Command (m for help): w
The partition table has been altered.
Syncing disks.

```
- 查看分区情况
```bash
parted sys.img UNIT b print
Model:  (file)
Disk /home/sandy/sys.img: 6291456000B
Sector size (logical/physical): 512B/512B
Partition Table: gpt
Disk Flags:

Number  Start        End          Size         File system  Name  Flags
 1      1048576B     315621375B   314572800B
 2      315621376B   1389363199B  1073741824B
 3      1389363200B  6291439103B  4902075904B

```
- losetup 查看loop情况
```bash
losetup -a
losetup -f
```
-  使用kparted挂载img文件

```bash
sudo kpartx -a -v -g sys.img
add map loop4p1 (253:0): 0 614400 linear 7:4 2048
add map loop4p2 (253:1): 0 2097152 linear 7:4 616448
add map loop4p3 (253:2): 0 9574367 linear 7:4 2713600
```
- 格式化各个分区
```bash
mkfs.fat /dev/mapper/loop4p1
mkfs.ext4 /dev/mapper/loop4p2 -L boot
mkfs.ext4 /dev/mapper/loop4p3 -L system
```

- 安装grub2到sys.img磁盘
```bash
mkdir -p system
mount /dev/mapper/loop4p3 system
mkdir -p system/boot
mount /dev/mapper/loop4p2 system/boot
mkdir -p system/boot/efi
mount /dev/mapper/loop4p1 system/boot/efi
grub-install --target=x86_64-efi --efi-directory=system/boot/efi --bootloader-id=GRUB
```
- 复制rootfs内容到system文件夹下
```bash
xz -dv uniontechos-device-20-gui-1010_AMD64-rootfs-20210515-0301.xz
mv uniontechos-device-20-gui-1010_AMD64-rootfs-20210515-0301{,.tar}
sudo apt install archivemount
sudo archivemount uniontechos-device-20-gui-1010_AMD64-rootfs-20210515-0301.tar /mnt
cp -rfp /mnt/* system/
或者
rsync -havAEHXi -n --numeric-ids --delete --stats --progress [SRC] [DEST]
或者
tar -xvf uniontechos-device-20-gui-1010_AMD64-rootfs-20210515-0301.tar -C system/
```
- chroot到system进行配置
```bash
source chrootsh
prechroot system
chroot system
# 以下在chroot环境操作
# vi /etc/apt/sources.list
# # 使用内网仓库
apt update
update-grub


```

```bash
# joe /etc/fstab
# joe /etc/network/interfaces
# exit
# umount linode/proc linode/sys linode/dev linode
# kpartx -d -v new.img
del devmap : loop1p1
loop deleted : /dev/loop1
# rmdir linode
# mv new.img /var/lib/vz/images/104/vm-104-disk-1.raw
```


格式转换: 
`qemu-img convert -f raw -O qcow2 sys.img  system.qcow2`