
[index](./index.md)

# git_blank_branch 

---

Author:sandylaw 

Email :freelxs@gmail.com

Date  :2020-10-30

tags  :git;linux 

---

## 创建新的空分支

```bash
git checkout --orphan new_branch_name
git rm -rf .
git add .
git commit -m "feat:new branch"
git push orign new_branch_name
```
