
[index](./index.md)

# Turn md to pdf with pandoc 

---

Author:sandylaw

Email :freelxs@gmail.com

Date  :2021-07-16

tags  : pandoc

---

## Install on debian

```bash
sudo apt install texlive-latex-recommended texlive-xetex latex-cjk-chinese texlive-fonts-recommended texlive-font-utils texlive-fonts-extra
```
## 查看系统已经安装的中文字体

```bash
fc-list :lang=zh
```
选择一个字体名称。

## markdown文件转成pdf

```bash
pandoc -f gfm -engine=xelatex --highlight-style zenburn -V CJKmainfont="Noto Serif CJK SC" --toc -o book.pdf title.txt *.md
```
>> 
  - 使用 xelatex 来处理中文，并且需要使用 CJKmainfont 选项指定支持中文的字体。
  - --toc 创建目录
  - -o 输出文件
  - title.txt

~~~yaml
```yaml
title: the way to go
author: Ivo Balbaert
rights: GPL
language: zh-CN
```
~~~

  - --highlight-sytle 高亮显示代码，上面使用了zenburn 主题, 另外，也推荐使用 tango, zenburn 或者breezedark 高亮主题 
  - 使用 -f gfm 的一个缺点是 gfm 不支持公式，因此如果在 Markdown 中包含公式，将不能正确渲染。解决办法是去掉 -f gfm flag，或者使用 Pandoc 自带的 markdown格式。


参考链接： https://jdhao.github.io/2017/12/10/pandoc-markdown-with-chinese/
