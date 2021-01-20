# UOS-Device-CLI 性能优化

## unixbench:

```bash
yum install gcc gcc-c++ make libXext-devel
apt-get install libx11-dev libgl1-mesa-dev libxext-dev perl  perl-modules make
wget https://s3.amazonaws.com/cloudbench/software/UnixBench5.1.3.tgz
tar xvf unixbench-5.1.3.tar.gz
cd unixbench-5.1.3
./Run
```

```bash
wget --no-check-certificate https://github.com/teddysun/across/raw/master/unixbench.sh
chmod +x unixbench.sh
./unixbench.sh
```

## 启动速度
```bash
systemd-analyze time
systemd-analyze blame
```
禁用:
- apt-daily.service
- apt-daily-upgrade.service
- apt-daily.timer
- apt-daily-upgrade.timer

## 性能优化
#### 服务器性能优化
```bash
调整dirty_ratio、dirty_background_ratio、nr_requests、read_ahead_kb参数值
/proc/sys/vm/dirty_ratio   dirty_ratio=60  //前台主动sync磁盘的内存占用率，越大同步次数越少
/proc/sys/vm/dirty_background_ratio  dirty_background_ratio=35   //后台主动sync磁盘的内存占用率，越大同步次数越少
/sys/block/sda/queue/nr_requests  nr_request=512  //blk层同步队列大小，越大同步次数越少。//默认的请求队列大小  服务器设置512,桌面设置128
/sys/block/sdb/queue/read_ahead_kb
```
### 性能优化参数

- 物理内存容量都是固定的。当应用程序需要的内存容量超过可用的物理内存，
  Linux内核仍然允许这些程序允许，因为Linux内核使用硬盘作为临时存储器，
  这个临时硬盘存储空间被称为交换分区（swap）。

- 为了优化应用程序，Linux为需要被写回硬盘的数据在内存中预留了存储空间，
  这些存储空间被成为缓冲区。如果应用程序要将数据写回硬盘，通常需要
  花费较长时间，Linux让应用程序立即继续执行，但将文件数据保存
  内存缓冲区，在之后的某个时刻，缓冲区被刷新到硬盘。

- dirty_radio

    这个参数控制文件系统的文件系统写缓冲区的大小,单位是百分比,表示系统内存的百分比,
    表示当写缓冲使用到系统内存多少的时候,开始向磁盘写出数据.
    增大之会使用更多系统内存用于磁盘写缓冲,也可以极大提高系统的写性能.
    但是,当你需要持续、恒定的写入场合时,应该降低其数值.
    设置 dirty pages 开始回写时的百分比，越低越安全
    设备系统默认20

- dirty_background_ratio

    这个参数控制文件系统的pdflush进程,在何时刷新磁盘.单位是百分比,表示系统内存的百分比,
    意思是当写缓冲使用到系统内存多少的时候, pdflush开始向磁盘写出数据.
    增大之会使用更多系统内存用于磁盘写缓冲,也可以极大提高系统的写性能.
    但是,当你需要持续、恒定的写入场合时,应该降低其数值.
    设置 dirty pages 开始后台回写时的百分比

    较低的ratio适合交互式系统；较高的ratio适合少而大的写。

    设备系统默认10

- dirty_writeback_centisecs

    这个参数控制内核的脏数据刷新进程pdflush的运行间隔.单位是 1/100 秒.
    如果你的系统是持续地写入动作,那么实际上还是降低这个数值比较好,这样可以把尖峰的写操作削平成多次
    设备系统默认500,也就是5秒

- dirty_expire_centisecs

    这个参数声明Linux内核写缓冲区里面的数据多旧了之后,pdflush进程就开始考虑写到磁盘中去.单位是 1/100秒.
    对于特别重载的写操作来说,这个值适当缩小也是好的,但也不能缩小太多,因为缩小太多也会导致IO提高太快.
    设备系统默认30000，也就是30秒。

- swappiness

    控制从物理内存换出到交换空间的相对权重，取值为 0 到 100。
    更低的值导致避免交换，而更高的值导致尝试使用交换空间。
    当swap默认值piness为0的时候表示最大限度使用物理内存，然后才是swap分区，
    当swappines为100的时候，则表示积极的使用swap分区，并且把内存上的
    数据及时的搬运到swap空间里面。
    设备系统默认60,优化性能则降低此值，内存够大或者需要更多响应的系统或者ssd硬盘，可以直接设置为0。

- nr_requests

    向磁盘发起请求数量/队列长度。n这个参数对顺序读非常有用,意思是,一次提前读多少内容,
    无论实际需要多少,设置大些对读大文件非常有用,可以有效的减少读 seek 的次数。
    nr_requests和许多其它优化参数一样，没有一个最佳的设置。正确的取值更多的是依赖于底层磁盘系统，而不是I/O负载行为。
    大请求队列可能会为写入大量小文件的负载提供很高的吞吐量。
    随着I/O大小的增加，低级别的nr_requests通常都会产生卓越性能。
    设备系统默认nvme对应值1023

- read_ahead_kb

    read_ahead_kb定义了预读多少数据。在大的读I/O流中，增加提前读取缓冲的大小会提升性能。
    注意，因为大多数都是随机I/O的原因，所以在一般情况下，
    增加这个值不会增强性能。
    设备系统默认128

- scheduler

    每个块设备或者块设备的分区，都对应有自身的请求队列(request_queue),
    而每个请求队列都可以选择一个I/O调度器来协调所递交的request。
    I/O调度器的基本目的是将请求按照它们对应在块设备上的扇区号进行排列，
    以减少磁头的移动，提高效率。每个设备的请求队列里的请求将按顺序被响应。
    内核中实现的IO调度器主要有四种--Noop,Deadline,CFG, Anticipatory

    cfq：Completely Fair Queueing（完全公平队列）调度器，它将进程分为实时、尽其所能和空闲三个独立的类别。实时类别的进程先于尽其所能类别的进程执行，而尽其所能类别的进程总是在空闲类别的进程之前执行。默认情况下分配到尽其所能类别的进程
    deadline：尝试为 I/O 请求提供有保障的延迟。适用于大多数情况，尤其是读取操作比写入操作更频繁的请求
    noop：执行简单的 FIFO（先进先出）调度算法，并实现请求合并。适合使用快速存储的 CPU 计算密集型系统
    blk-mq：即 Multi-Queue Block IO Queuing Mechanism（多队列块 IO 队列机制），它利用具有多核的 CPU 来映射 I/O 队列到多队列。与传统的 I/O 调度器相比，通过多线程及多个 CPU 核心来分发默认值默认值默认值任务，从而能够加速读写操作。该调度器适合高性能的闪存设备（如 PCIe SSD）

### 性能优化方案
#### sysctl.conf修改

> ‘or’后的数值偏重安全，则性能降低
```bash
# vi /etc/sysctl.conf
vm.swappiness = 60 # ==> 100 or 0
vm.dirty_ratio = 20 # ==> 60 or 10
vm.dirty_background_ratio = 10 # ==> 35 or 3
vm.dirty_writeback_centisecs = 500 # ==> or 2
vm.dirty_expire_centisecs = 30000 # ==> or 12000
```
>据说1:6 (dirty_expire_centisecs  : dirty_write/sys/block/sdb/queue/read_ahead_kbback_centisecs )的比例比较好

#### nr_requests修改

- Create a new udev rule.

/etc/udev/rules.d/71-nr-requests.rules
```bash
SUBSYSTEM!="block", GOTO="end_rule"
ENV{DEVTYPE}=="partition", GOTO="end_rule"
ACTION!="add|change", GOTO="end_rule"
KERNEL=="sd*", ATTR{queue/nr_requests}="256"
LABEL="end_rule"
```
- Apply the rule

```bash
# udevadm trigger
```
- check the rule

```bash
 grep "" /sys/block/sd*/queue/nr_requests
```
#### read_ahead_kb\scheduler修改

create the file /etc/udev/rules.d/90-disk-queue.rules

```bash
# set a larger readahead size
ACTION=="add|change", KERNEL=="sd[a-z]", ATTR{queue/read_ahead_kb}="1024"
ACTION=="add|change", KERNEL=="nvme*", ATTR{queue/read_ahead_kb}="8192"

# set deadline scheduler for non-rotating disks
ACTION=="add|change", KERNEL=="sd[a-z]", ATTR{queue/rotational}=="0", ATTR{queue/scheduler}="deadline"
ACTION=="add|change", KERNEL=="nvme*", ATTR{queue/rotational}=="0", ATTR{queue/scheduler}="blk-mq"
```

### 性能参数对比

| 性能参数                               | CLI-Device  | centos8.2             | Server1021  |
| -------------------------------------- | ----------- | --------------------- | ----------- |
| /proc/sys/vm/dirty_ratio               | 20          | *30*                  | 20          |
| /proc/sys/vm/dirty_background_ratio    | 10          | 10                    | 10          |
| /proc/sys/vm/dirty_writeback_centisecs | 500         | 500                   | 500         |
| /proc/sys/vm/swappiness                | 60          | *30*                  | 60          |
| /proc/sys/vm/dirty_expire_centisecs    | 3000        | 3000                  | 3000        |
| /sys/block/sda/queue/nr_requests       | 64          | *2*                   | 64          |
| /sys/block/sdb/queue/read_ahead_kb     | 128         | *4096*                | 128         |
| /sys/block/sda/queue/scheduler         | mq-deadline | mq-deadline kyber bfq | mq-deadline |

### 文件系统差异

经研究发现，Deepin-installer对Server的分区方案做了单独处理，其中根分区和Data分区采用了xfs文件系统类型，其相对与ext4有了一些性能提升。当对CLI采用了Server的分区方案后，性能有所提示，与Server的性能测试数据差异缩小到3%左右。

#### xfs

和ext4相比，xfs不支持下面这些功能

- 不支持日志（Journal）校验码
- 不支持无日志（No Journaling）模式
- 不支持文件创建时间
- 不支持数据日志（data journal），只有元数据日志（metadata journal）

但xfs有下面这些特性

- 支持的最大文件和分区都达到了8EB
- inode动态分配，从而不受inode数量的限制，再也不用担心存储大量小文件导致inode不够用的问题了。
- [更大的xattr(extended attributes)](https://en.wikipedia.org/wiki/XFS#Extended_attributes)空间，ext2/3/4及btrfs都限制xattr的长度不能超过一个块（一般是4K），而xfs可以达到64K
- 内部采用Allocation groups机制，各个group之间没有依赖，支持并发操作，在多核环境的某些场景下性能表现不错
- 提供了原生的dump和restore工具，并且支持在线dump

