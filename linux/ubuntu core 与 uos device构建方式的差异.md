ubuntu core 与 uos device构建方式的差异

- ubuntu core系统基本由4类snap构成：gadget snap， kernel snap ， core snap ， app snaps。

  - gadget snap 是包含了boot image，系统镜像的布局，IO 接口的权限，系统的默认属性设定（usb 自动挂载属性等），gadget snap 描述了这个设备几乎所有的属性。

  - kernel snap 包含kernel & ubuntu core 所需要的initrd 的snap。

  - core snap 包含ubuntu core rootfs 的snap 包

  - app snap 关于包含app 的snap。
- ubuntu-core中的snap包与传统的deb不同，它类似一个容器拥有一个应用程序所有的文件和库，各个应用程序之间完全独立。所以使用snap包的好处就是它解决了应用程序之间的依赖问题，使应用程序之间更容易管理。但是由此带来的问题就是它占用更多的磁盘空间。
- ubuntu-core采用ubuntu-image命令（python程序）进行构建，其主要配置文件是一个断言（assert）来定义生成image 中所包含的snap 包。前提是需要对各个snap包进行单独维护。
- uos device系统构建采用ansible工具，采用ansible task任务进行一系列定制化配置，每个任务做一件事情，可控颗粒度较细，其中使用debootstrap命令构建基本系统，并通过deb软件包清单的方式安装软件以及进行一系列的配置定制。
- ubunt-image的构建方式相对于uos device系统构建方式，其构建（组装）逻辑清晰，采用一个断言文件进行定义全部配置，以搭积木的方式构建系统镜像，这是其优点；缺点时每个snap需要单独维护，且可定制化较弱。

- ubuntu core系统与uos device系统的定位不同，前者主要应用于物联网、云端容器而推出，硬件差异小、通用型较高；后者主要应用于专用设备、武器装备等，目标差异化较大、需定制开发较多。

综上，ubuntu core的构建方式值得借鉴，但不可照搬，下一步uos device构建方式重构进行模块化，但模块化的颗粒度要细，便于定制组合。

