
[index](./index.md)

# modify_default_pipe_size 

---

Author:sandylaw

Email :freelxs@gmail.com

Date  :2020-12-23

tags  :linux

---

查看：
`cat /proc/sys/fs/pipe-max-size`
修改：
`sudo sysctl fs.pipe-max-size=102400000`

Linux 内核2.6.11之后，需要通过fcnt来修改，且bash无法修改，以python为例：

