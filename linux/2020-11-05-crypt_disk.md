
[index](./index.md)

# crypt_disk 

---

Author:sandylaw 

Email :freelxs@gmail.com

Date  :2020-11-05

tags  :linux;safe 

---

## 加密磁盘（块设备）

举例，U盘为/dev/sda，使用fdisk分区，一个分区/dev/sda1，此时无需格式化。

```bash
sudo cryptsetup [option] luksFormat /dev/sda1 # Setup luksFormat,输入两次密码完成设置
#第一次使用需要设置为luksFormat格式，可以设定选项
#-v --type luks --cipher aes-xts-plain64 --key-size 512 --hash sha512 --iter-time 2000 --use-urandom --verify-passphrase

sudo cryptsetup luksOpen /dev/sda1 key #打开设备并命名为key,输入密码
sudo mkfs.ext4 -L KEY /dev/mapper/key  #格式化
sudo mkdir /mnt/key                    #创建挂载点
sudo mount /dev/mapper/key /mnt/key    #挂载设备
sudo umount /mnt/key                   #卸载设备
cryptsetup close key                   #关闭设备
```

参考链接：

- 1. <https://wiki.archlinux.org/index.php/Dm-crypt/Encrypting_a_non-root_file_system>
