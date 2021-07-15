
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

List available updates:

```bash
apt-get -V -s dist-upgrade \
    |grep -E "^   .*=>.*" \
    |awk 'BEGIN {
        ul=sprintf("%*s",40,""); gsub(/ /,"-",ul);
        printf "%-30s %-30s %-30s\n", "Package", "Installed", "Available";
        printf "%-30.30s %-30.30s %-30.30s\n", ul, ul, ul;
     }
     {
        printf "%-30s %-30s %-30s\n",
               $1,
               substr($2,2),
               substr($4,1,length($4)-1)
     }'
```
