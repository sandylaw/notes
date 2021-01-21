
[index](./index.md)

# pandoc_markdown_to_pdf 

---

Author:sandylaw 

Email :freelxs@gmail.com

Date  :2020-11-16

tags  :pandoc 

---

```bash
sudo apt-get install pandoc texlive-latex-base texlive-fonts-recommended texlive-extra-utils texlive-latex-extra lmodern texlive-xetex

pandoc --pdf-engine=xelatex -c Github.css -f markdown+footnotes+pipe_tables -V mainfont='Noto Sans CJK SC' file.md -o file.pdf
```
