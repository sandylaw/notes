
[index](./index.md)

# pullrequest 

---

Author:sandylaw 

Email :freelxs@gmail.com

Date  :2020-12-08

tags  :git

---

## 步骤

### Part 1 - Local Repo Config 

1. 先 Fork 感兴趣项目，即 `https://github.com/wangdoc/bash-tutorial`
2. Clone 到本地，`git clone git@github.com:sandylaw/bash-tutorial.git`
3. 添加源项目作为 `upstream` 源，`git remote add upstream
   https://github.com/wangdoc/bash-tutorial`
4. 禁止直接向 `upstream` 源 push，因为我们没有 push 的权限，要提交代码必须通过 Pull Request，`git remote set-url --push upstream no_push`
3. 创建并切换到本地的新分支 `fixVarQuote`，`git checkout -b fixVarQuote`
    + 本地分支 `master` 的作用是与远程 `upstream` 的最新代码同步
    + 本地分支 `fixVarQuote` 则是我们修改代码的战场

### Part 2 - Fix Bug 

1. fix bug
2. 在当前 `fixVarQuote`分支提交本地修改，`git commit -m "XXXXXXX"`
3. Check `upstream` 源的最新状态
    + 在本地将 `upstream` 源的代码更新到最新，`git fetch upstream`
    + 将本地当前分支切换成 `master`，`git checkout master`
    + 将 `upstream/master` 的代码与本地当前默认分支，也就是本地 `master` 分支的代码融合：`git merge upstream/master`
4. 将本地分支 `fixVarQuote` 上的修改融合到最新的 `master` 分支上
    + 将本地当前分支切换成 `fixVarQuote`，`git checkout -b fixVarQuote`
    + **将 `fixVarQuote` 的代码置于已经更新到最新的 `master` 分支的最新代码之后**：`git rebase master`
5. 向 Github 上自己的 fork 项目 `YimianDai/gluon-cv` 的分支 `origin` 提交自己的修改，因为 Pull Request 是将两个 Github 上的 repo 比较，所以一定要将本地的修改先推送到自己的 fork repo 上，`git push origin fixVarQuote:fixVarQuote`

### Part 3 - Pull Request 

1. 提交 issue：描述发现的 Bug，这个可以作为对自己后面 Pull Request 的描述
2. 是在自己 Fork 的项目界面，即 `sandylaw/bash-tutorial`的 Pull requests 的 Tab 中点击 New pull request，后面会自动跳到 `https://github.com/wangdoc/bash-tutorial`的界面

### Part 4 - Delete fixed-branch

当提交的PR被合并后，可以删除此分支：
`git branch -d fixed-branch`
`git push origin --delete fixed-branch`

合并上游更新到`master`:
    + 在本地将 `upstream` 源的代码更新到最新，`git fetch upstream`
    + `git checkout master`
    + 将 `upstream/master` 的代码与本地当前默认分支，也就是本地 `master` 分支的代码融合：`git merge upstream/master`
    + `git push`

## Reference

[向开源项目提交PR](https://gist.github.com/YimianDai/7dcf6340fc435323a328634df0666f5e)
