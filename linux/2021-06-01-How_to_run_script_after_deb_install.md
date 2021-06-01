
[index](./index.md)

# How to run script after deb install 

---

Author:sandylaw

Email :freelxs@gmail.com

Date  :2021-06-01

tags  : linux

---

想要在安装包之后执行某脚本,做一些配置修改.

## 通过 apt install 的方式安装软件包时
```bash
sudo apt update

cat /usr/local/bin/disable-sftpd
#!/bin/bash
if [[ -f /etc/ssh/sshd_config ]];then
  sed -ri "s;/usr/lib/openssh/sftp-server;/bin/true;" /etc/ssh/sshd_config
fi

cat /etc/apt/apt.conf.d/66disable-sftpd.conf
DPKG::Post-Invoke {"/usr/local/bin/disable-sftpd";};

sudo apt install openssh-server

```
经实际测试,对于手动安装dpkg -i的方式无效
## 即便是 dpkg -i 手动安装软件包也生效的方式
```bash
cat /etc/dpkg/dpkg.cfg.d/66disable-sftpd
post-invoke=if test -x /usr/local/bin/disable-sftpd; then /usr/local/bin/disable-sftpd; fi

sudo dpkg -i openssh-server.deb
```
