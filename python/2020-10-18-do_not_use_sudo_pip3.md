
[index](./index.md)

# do_not_use_sudo_pip3 

---

Author:sandylaw 

Email :freelxs@gmail.com

Date  :2020-10-18

tags  : 

---


- 使用sudo权限，执行pip3安装包，会和系统的包管理器引发冲突！！

- 恢复python3及pip环境：

```bash
sudo  rm -rf /usr/lib/python3.8 #太暴力！！！
yay -S python3
curl -sS https://bootstrap.pypa.io/get-pip.py | sudo python3
yay -S python-dbus pyqt5 libxml2
pip3 install msgpack pyqt5 libvirt-python pycairo PyGobject vext vext.gi
```
