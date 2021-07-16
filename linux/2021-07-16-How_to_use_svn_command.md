
[index](./index.md)

# How_to_use_svn_command 

---

Author:sandylaw

Email :freelxs@gmail.com

Date  :2021-07-16

tags  :

---

## 下载资料/代码

```bash
svn checkout --username ut00110 --password '$password' https://svnfile.uniontech.com/svn/cdrd/TeamMgmt/sysdev_docs
```

## 更新到新版本

```bash
svn update [-r version]
```

## 查看工作副本状态

```bash
svn status
```
第一列表示文件的状态：

    ，没有修订
    A，添加
    C，冲突，需要解决冲突状态，才能正常提交代码。
    D，删除
    I，忽略
    M，有修改
    ?，没有版本控制，在工作副本添加文件或目录之后，需要使用svn add your_path才能加该文件加到版本控制。
    !，文件丢失，如果不是使用svn delete删除文件或目录，会产生此状态。

## 添加/删除/移动文件/目录

```bash
svn add file1 file2 ...
svn add dir ...  
svn delete your_path
svn move src dst
```

## 提交commit

```bash
svn ci -m "message"
```

## 查看工作副本信息

```bash
svn info
```
## 查看log 

```bash
svn log
```

