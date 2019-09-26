
This is a static blog engine just like Hexo and Jekyll. It's written in C++ with a little PHP. All the code adds up to **less than 700 lines including the HTML** (Markdown parser not included).

The Markdown rendering engine is based on [sundown](https://github.com/vmg/sundown) and has been slightly modified.

Although this blog engine is very simple and the implementation is not very elegant, it has been working well so far in my website.

# Features

* Basic blog engine features including RSS (only RSS is written in PHP).
* Writing with Markdown.
* Non-conflicting rendering of LaTeX and Markdown (by escaping LaTeX).
* Settings of blog post properties like show or hide.

# Dependencies

The codes of sundown has already been put in `source/sundown` directory. All you need is to prepare a C/C++ compiler. If you want the RSS feature, PHP is also needed.

# Build

I build and run it on Windows, but it is also capable on Linux.

## Compile

```
gcc source/sundown/*.c -o sundown.exe
g++ -std=c++11 mdblog.cpp -o mdblog.exe
```

## Run

Just run `mdblog.exe`. It will parse all the `.md` files and generate your website.

# Demo

You can view the demo by browsing [my blog](https://fanzheng.org/archives/0) (in Chinese).
