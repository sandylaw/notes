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
systemd-analyze time
systemd-analyze blame

禁用:
- apt-daily.service
- apt-daily-upgrade.service
- apt-daily.timer
- apt-daily-upgrade.timer

## Fily Copy

Centos: xfs
UOS: ext4

## 服务器性能优化
```bash
调整dirty_ratio、dirty_background_ratio、nr_requests、read_ahead_kb参数值
/proc/sys/vm/dirty_ratio   dirty_ratio=60  //前台主动sync磁盘的内存占用率，越大同步次数越少
/proc/sys/vm/dirty_background_ratio  dirty_background_ratio=35   //后台主动sync磁盘的内存占用率，越大同步次数越少
/sys/block/sda/queue/nr_requests  nr_request=512  //blk层同步队列大小，越大同步次数越少。//默认的请求队列大小  服务器设置512,桌面设置128
/sys/block/sdb/queue/read_ahead_kb
```
- dirty_radio
    设置 dirty pages 开始回写时的百分比，越低越安全
    设备系统默认20
- dirty_background_ratio
    设置 dirty pages 开始后台回写时的百分比
    设备系统默认10
- vm.swappiness
    控制从物理内存换出到交换空间的相对权重，取值为 0 到 100。
    更低的值导致避免交换，而更高的值导致尝试使用交换空间
    设备系统默认60
- nr_requests
    向磁盘发起请求数量。nr_requests和许多其它优化参数一样，没有一个最佳的设置。正确的取值更多的是依赖于底层磁盘系统，而不是I/O负载行为。
    大请求队列可能会为写入大量小文件的负载提供很高的吞吐量。
    随着I/O大小的增加，低级别的nr_requests通常都会产生卓越性能。
    设备系统默认nvme对应值1023
- read_ahead_kb
    read_ahead_kb定义了预读多少数据。在大的读I/O流中，增加提前读取缓冲的大小会提升性能。
    注意，因为大多数都是随机I/O的原因，所以在一般情况下，
    增加这个值不会增强性能。

## 文件系统的选择和优化

不同类型的文件系统适用于不同的工作负载场景。一般来说，ReiserFS适用于很小的I/O请求，XFS和JFS适合很大的文件系统和很大的I/O大小。Ext3的能力恰好在ReiserFS和JFS/XFS之间，它能处理小I/O请求，并且提供很好的多处理扩展性。

JFS和XFS最适合高端数据仓库，科学计算和大的SMP服务器，以及流媒体服务器。ReiserFS和Ext3主要用在文件、Web和邮件服务器等场景。对于写频繁、而且I/O大小在64KB以下的环境，ReiserFS相比Ext3的优势在默认的日志模式上。但是，这仅仅是在同步文件操作的时候。

Ext2也是一个选择。由于不具备日志功能，无论是访问模式，还是I/O大小，Ext2在同步文件系统上的表现都优于ReiserFS和Ext3。所以，在性能比数据完整性还重要的时候，Ext2也是个不错的选择。

在大多数同步文件系统场景中，默认日志模式的ReiserFS文件系统（数据有序）通常提供比Ext3更好的性能。但是，在默认日志模式为调整为writeback的时候，Ext3和ReiserFS具有同等的性能

