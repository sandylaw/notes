
[index](./index.md)

# ubuntu-core

---

Author:sandylaw

Email :freelxs@gmail.com

Date  :2021-05-17

tags  :

---

## 系统构成
ubuntu core 基本上是诸多snap 包堆积起来的一个系统，ubuntu core 由4 类snap 构成，gadget snap， kernel snap ， core snap ， app snaps。

- gadget snap 是包含了uboot image，系统镜像的布局，IO 接口的权限，系统的默认属性设定（usb 自动挂载属性等），gadget snap 描述了这个设备几乎所有的属性。

- kernel snap 包含kernel & ubuntu core 所需要的initrd 的snap。

- core snap 包含ubuntu core rootfs 的snap 包

- app snap 关于包含app 的snap。

传统的系统启动需要uboot，kernel，rootfs， app， ubuntu core 也一样，只不过他们都是以snap 包的形式存在于ubuntu core 中的。

当用ubuntu-image 命令制作系统启动镜像的时候，该命令会将gadget snap & kernel snap 中的启动image 全部解压出来，（同时解压一部分core 的内容） 放到gadget.yaml 中指定的分区中去。这样当制作好镜像后，uboot，kernel ， 和initrd 的存在形式就和传统的系统一样了， 即以启动文件的形式存在。当系统启动到initrd 阶段， 由initrd 在writable 中准备一套可启动的文件，并启动它。之后，snapd 启动，开启snap 的世界。

不过在系统镜像里，仍然保存了gadget snap 和kernel snap， 这是为了以后这些snap 能够进行顺利的更新，回滚做准备的。

在ubuntu core 中， 每一个snap 被安装后, 该snap 就通过/dev/loopx 挂载到/snap/${snap_name}/ 下的版本文件夹下， 是一个只读的文件系统。


## 系统构建

ubuntu core 提供了一个生成ubuntu core image 的工具:`ubuntu-image`

>在ubuntu20.04系统下测试，debian10下版本太旧测试不通过。
```bash
sudo apt install snapd qemu-system ovmf virt-manager
sudo snap install snapcraft --classic
sudo snap install ubuntu-image --beta --classic
```
实现一个断言（assert）(配置文件)来定义你生成image 中所包含的snap 包:

```yml
{
    "type": "model",
    "series": "16",
    "authority-id": "developer-id",
    "brand-id": "developer-id",
    "model": "ubuntu-core-20-amd64",
    "architecture": "amd64",
    "timestamp": "2020-11-17T13:09:51+00:00",
    "base": "core20",
    "grade": "signed",
    "snaps": [
        {
            "name": "pc",
            "type": "gadget",
            "default-channel": "20/stable",
            "id": "UqFziVZDHLSyO3TqSWgNBoAdHbLI4dAH"
        },
        {
            "name": "pc-kernel",
            "type": "kernel",
            "default-channel": "20/stable",
            "id": "pYVQrBcKmBa0mZ4CCN7ExT6jH8rY1hza"
        },
        {
            "name": "core20",
            "type": "base",
            "default-channel": "latest/stable",
            "id": "DLqre5XGLbDqg9jPtiAhRRjDuPVa5X1q"
        },
         {
            "name": "snapd",
            "type": "snapd",
            "default-channel": "latest/stable",
            "id": "PMrrV4ml8uWuEUDBT8dSGnKUYbevVhc4"
        },
        {
            "name": "htop",
            "type": "app",
            "default-channel": "latest/stable",
            "id": "hJmReLmgXSUj4SF7WhyTVRV6IzUa4QUZ"
        }
    ]
}
```
其中：developer-id 需要替换成你自己的账号对应的id:

```bash
snapcraft login
snapcraft whoami
email:        freelxs@gmail.com
developer-id: APCdeU4BdviBdWYp13EJ8ZWBTzQvrbsH
```



登陆并生成key：

```bash
$ sudo snap login
[...]
Login successful

$ snap keys
No keys registered, see `snapcraft create-key`

If you have no registered keys, create one as follows:

$ snap create-key my-models
Passphrase:
Confirm passphrase: <passphrase>

$ snap keys
Name         SHA3-384
my-key-name  E-n0AOKPFjIyy4S_i9JxTT4tkuaZf7rP9D2mBNXjlgTGDjL8euFSlb87U0NPl

$ snapcraft register-key
$ cat my-model.json | snap sign -k my-key-name > my-model.model
```
引用断言构建镜像：
```bash
ubuntu-image snap my-model.model
Fetching snapd
Fetching pc-kernel
Fetching core20
Fetching pc
Fetching htop
ls -lh pc.img
-rw-rw-r-- 1 ubuntu ubuntu 3.0G 5月  18 17:38 pc.img
```
虚拟机测试：

```bash
sudo qemu-system-x86_64 -smp 2 -m 2048 \
 -net nic,model=virtio -net user,hostfwd=tcp::8022-:22 \
 -drive file=/usr/share/OVMF/OVMF_CODE.fd,if=pflash,format=raw,unit=0,readonly=on \
 -drive file=pc.img,cache=none,format=raw,id=disk1,if=none \
 -device virtio-blk-pci,drive=disk1,bootindex=1 -machine accel=kvm
```





原文链接：https://blog.csdn.net/changqing1990/article/details/82841830

