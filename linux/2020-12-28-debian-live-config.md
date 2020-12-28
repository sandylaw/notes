[index](./index.md)

# debian-live-config

---

Author:sandylaw

Email :freelxs@gmail.com

Date  :2020-12-28

tags  :linux

---
## config

- 修改 auto/config,指定mirror:

```bash
--mirror-bootstrap https://mirrors.ustc.edu.cn/debian/ \
--mirror-chroot-security https://mirrors.ustc.edu.cn/debian-security/ \
```

- 修改config/package-lists,增删软件包

