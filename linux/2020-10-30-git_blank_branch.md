
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
## 清空历史

```bash
##-- Remove the history from 
rm -rf .git

##-- recreate the repos from the current content only
git init
git add .
git commit -m "Initial commit"

##-- push to the github remote repos ensuring you overwrite history
git remote add origin git@github.com:<YOUR ACCOUNT>/<YOUR REPOS>.git
git push -u --force origin main
```
