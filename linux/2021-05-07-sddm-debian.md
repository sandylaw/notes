
[index](./index.md)

# sddm 

---

Author:sandylaw

Email :freelxs@gmail.com

Date  :2021-05-07

tags  :

---
## 获取source
apt source sddm
## 安装相关依赖
sudo apt install debhelper fakeroot python3-docutils quilt
sudo apt build-dep sddm
## 构建deb包
dpkg-buildpackage -us -uc -nc
## debian 上游仓库
git clone https://salsa.debian.org/qt-kde-team/3rdparty/sddm.git
## 替换上游的debian目录到本地后再构建deb包
quilt refresh
dpkg-buildpackage -us -uc -nc

## debian系统测试

- 安装系统

由于UOS采用lightdm，而非sddm，在UOS系统上测试sddm有适配问题，故需要在debian系统上进行测试。
安装debian10.8系统，buster稳定分支。
安装后检查sddm的版本号，如果已经升级到最新，需要强制降级到0.18.0-1版本：
http://pools.uniontech.com/desktop-professional/pool/main/s/sddm/

- 安装工具

sudo apt install inotify-tools

- 测试方法

ssh 远程连接到目标机，运行：
`export DISPLAY=:0;inotifywait /tmp/.X11-unix; while ! xkill; do :; done`
在目标主机关闭sddm，再手动启动sddm：
`sudo systemctl stop sddm ; sudo systemctl start sddm`

- 旧版本测试现象

在sddm登陆界面，观察ssh远程连接：
>>>Select the window whose client you wish to kill with button 1....
鼠标点击sddm登陆界面后，则kill掉。
xkill:  killing creator of resource 0x40000f

- 新版本测试现象

当安装打完安全补丁的sddm包之后，在同样的sddm登录界面，观察ssh远程连接：
>>>invalid MIT-MAGIC-COOKIE-1 keyxkill:  unable to open display ":0"


