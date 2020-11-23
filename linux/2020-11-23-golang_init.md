
[index](./index.md)

# golang_init 

---

Author:sandylaw 

Email :freelxs@gmail.com

Date  :2020-11-23

tags  :go 

---

## golang 环境准备
```bash
export GOPATH=$HOME/go
export PATH=$PATH:$GOPATH/bin
mkdir -p $GOPATH/src $GOPATH/pkg $GOPATH/bin
#Go 把文件放到三个目录中：所有源代码位于 src，包对象位于 pkg，编译好的程序位于 bin。
#用 go get，它会把下载到的资源按 src/pkg/bin 结构正确安装在相应的 $GOPATH/xxx 目录中。

#调试 Go 代码建议使用 Delve。可以通过以下 go get 命令安装：
go get -u github.com/go-delve/delve/cmd/dlv

#对默认的语法检查进行增强可以用 GolangCI-Lint。可通过以下方式安装：
go get -u github.com/golangci/golangci-lint/cmd/golangci-lint
```

