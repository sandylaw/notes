
[index](./index.md)

# 显示管理器

---

Author:sandylaw

Email :freelxs@gmail.com

Date  :2021-05-20

tags  : linux

---

## 什么是 Linux 中的显示管理器？

简单来说， 显示管理器(display manager) （DM）是一个为你的 Linux 发行版提供图形登录功能的程序。它控制用户会话并管理用户认证。显示管理器会在你输入用户名和密码后，立即启动显示服务器并加载桌面环境。

显示管理器通常是登录界面的代名词。毕竟它是可见的部分。然而，可见的登录屏幕，也叫 欢迎页(greeter) ，只是显示管理器的一部分。

像各种桌面环境和显示服务器一样，也有各种显示管理器。

## 不同的显示管理器

有些人认为显示管理器是桌面环境的一部分，但事实并非如此。它是一个独立的程序。

桌面环境可能会推荐某个显示管理器，但这并不意味着它不能与其它一些显示管理器一起工作。如果你曾经在同一个系统中安装过不止一个桌面环境，你会记得，登录界面（即显示管理器）允许你切换桌面环境。

显示管理器可以与各种桌面环境配合使用

虽然显示管理器不是桌面环境本身的一部分，但它往往与桌面环境由同一个开发团队开发。它也成为桌面环境的代表。

一些流行的显示管理器有：

GDM （ GNOME 显示管理器(GNOME Display Manager) ）：GNOME 的首选。

SDDM（ 简单桌面显示管理器(Simple Desktop Display Manager) )：KDE 首选。

LightDM：由 Ubuntu 为 Unity 桌面开发。

## 改变显示管理器

如果你愿意，可以更改显示管理器。你需要先安装显示管理器。安装时你会看到切换显示管理器的选项。

如果当时没有做切换，那么以后可以通过手动配置来改变显示管理器。

命令方式：`dpkg-reconfigure lightdm`
配置方式:
```bash
cat /etc/X11/default-display-manager
/usr/sbin/lightdm
```
## 加载显示管理器

`systemctl enable lightdm`

执行上述命令后，登录管理器应当能正常工作了。如果不是的话，可能是default.target 没有指向graphical.target。

启用 LightDM 后， /etc/systemd/system/ 应该创建 display-manager.service 软链接，可以用 --force 覆盖已有链接。

$ file /etc/systemd/system/display-manager.service

/etc/systemd/system/display-manager.service: symbolic link to /lib/systemd/system/lightdm.service

## 修改默认target

```bash
systemctl get-default
systemctl set-default graphical.target
```
## 会话配置

多数显示管理器会读取 /usr/share/xsessions/ 目录已获取可用的会话列表，此目录中包含各个 DM/WM 的标准 桌面文件。

要新建会话，可以在 /usr/share/xsessions/ 中新建 .desktop 后缀的文件，文件示例：
```
cat /usr/share/xsessions/deepin.desktop
[Desktop Entry]
Name=Deepin
Comment=Deepin Desktop Environment
Exec=/usr/bin/startdde
TryExec=/usr/bin/startdde
```
## 显示管理器可以定制

有这么多的桌面环境可供选择，它们都有自己的显示管理器吗？非也。

可见的登录屏幕被称为欢迎页。这个欢迎页可以进行自定义来改变登录屏幕的外观。

事实上，许多发行版和/或桌面环境都制作了自己的欢迎页，以给用户提供一个类似于他们品牌的登录屏幕。

例如深度/UOS的显示管理器使用lightdm，开发dde-session-shell程序提供lightdm-deepin-greeter定制登陆屏幕的外观。

## UOS lightdm定制
``/etc/lightdm/lightdm.conf`
- session
```
greeter-session=lightdm-deepin-greeter
user-session=deepin #理论上这里设定默认的会话环境
```
- 自动登陆
```
autologin-user=username
autologin-user-timeout=0
```
- 允许root登陆
`/etc/deepin/dde-session-ui.conf` #主要控制用户名可选或手动输入、头像、电源菜单等。
```
loginPromptInput=true
```
## 命令行方式登陆
设定系统默认运行级别：
`systemctl set-default multi-user.target`
重启后，系统将进入命令行登陆模式，输入用户名和密码后登陆系统。
此时进入桌面环境，可用通过命令：
- startx
startx 做了什么？
查找$HOME/.xinitrc /etc/X11/xinit/xinitrc，而uos默认家目录的.xinitrc不存在的话，将找到全局的xinitrc，
```
cat /etc/X11/xinit/xinitrc
. /etc/X11/Xsession
```
而/etc/X11/Xsession文件将遍历执行：
```
ls /etc/X11/Xsession.d -1                  ✔  2518  18:09:38
00deepin-dde-env
01deepin-profile
05uos-profile
20dbus_xdg-runtime
20vdpau-va-gl
20x11-common_process-args
30x11-common_xresources
35x11-common_xhost-local
40x11-common_xsessionrc
50x11-common_determine-startup
55xfce4-session
60imwheel_start-imwheel
70im-config_launch
75dbus_dbus-launch
90gpg-agent
90qt-a11y
90x11-common_ssh-agent
95dbus_update-activation-env
99x11-common_start
```
其中50号文件检测x-session-manager，存在给予变量STARTUP;
99号文件执行STARTUP变量。
x-session-manager负责启动dde相关程序。


- systemctl start lightdm

