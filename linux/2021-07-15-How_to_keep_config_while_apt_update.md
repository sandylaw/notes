
[index](./index.md)

# How to keep config while apt update 

---

Author:sandylaw

Email :freelxs@gmail.com

Date  :2021-07-15

tags  : linux

---


```bash
apt-get install -o Dpkg::Options::="--force-confold" --force-yes -y mysql-server
```

You can also add this to the config of the system by creating a file in /etc/apt/apt.conf.d/ with this content:

```bash
Dpkg::Options {
   "--force-confdef";
   "--force-confold";
}
```

