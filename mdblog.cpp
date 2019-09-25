#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#define debug puts("-----")
#define pi (acos(-1.0))
#define eps (1e-8)
#define inf (1 << 30)
#define INF (1ll << 62)

using namespace std;

string s1 = R"(
<!DOCTYPE html>
<html lang="zh-CN">
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="/css/bootstrap.min.css">
    <link rel="stylesheet" href="/css/style.css">
        <title>
)";
// 插入页面标题
string s2 = R"(</title>
    </head>
    <body>
    <div id="header" class="header">
        <div class="header_wrapper">
          <h1 class="title"><a href="/">YourSite's blog</a></h1>
          <ul class="navfz">
            <li><a href="/">首页</a></li>
            <li><a href="/archive">归档</a></li>
            <li><a href="/tags">标签</a></li>
            <li><a href="/links">友链</a></li>
            <li><a href="/about">关于</a></li>
            <br />
            <li><a href="/feed"><img src="/feed.png" /></a></li>
          </ul>
        </div>
    </div>

    <div id="main">
)";
// 显示文章主体
string s3 = R"(
        <div class="detail">
            <div class="post">
                <div class="content">
                    <h1 class="title"><a href="
)";
// 插入文章链接
string s33 = R"(">
)";
// 插入文章标题
string s4 = R"(</a></h1>
)";
// 显示文章信息
string s5 = R"(
                    <div class="info">
                        <span class="date"><i class="glyphicon glyphicon-calendar"></i>
)";
// 插入文章时间
string s6 = R"(</span><span class="tags"><i class="glyphicon glyphicon-tags"></i>
)";
// 插入标签：<a href="/tags/标签名">标签名</a>
string s7 = R"(</span>
                    </div>
)";
// 显示文章主体
string s8 = R"(
                    <div class="post_body">
)";
// 插入文章内容
string s9 = R"(
                    </div>
                </div>
            </div>
)";
// 显示前后的文章
string s10 = R"(
            <div class="other_posts">
)";
// 插入前一篇文章：<a href="." class="pre">< 这是前一篇文章</a>
// 插入后一篇文章：<a href="." class="next">这是后一篇文章 ></a>
string s11 = R"(
            <div class="clear"></div></div>
)";
// 插入disqus
string s12 = R"(
            <div class="disqus"><a name="comments"></a><div id="disqus_thread"><span style="font-size: 15.5px">如果长时间无法加载评论，请对 *.disqus.com 启用代理！</span></div></div>
            <script type="text/javascript">

                var disqus_shortname = 'YourSiteblog';

                (function() {
                    var dsq = document.createElement('script'); dsq.type = 'text/javascript'; dsq.async = true;
                    dsq.src = '//' + disqus_shortname + '.disqus.com/embed.js';
                    (document.getElementsByTagName('head')[0] || document.getElementsByTagName('body')[0]).appendChild(dsq);
                })();
            </script>
            <noscript>Please enable JavaScript to view the <a href="https://disqus.com/?ref_noscript" rel="nofollow">comments powered by Disqus.</a></noscript>
)";
// 结束detail
string s13 = R"(
        </div>
    </div>
    <!-- 各种库 -->
)";
// 插入highlight
string s14 = R"(
    <script src="/js/highlight/highlight.pack.js"></script>
    <script>hljs.initHighlightingOnLoad();</script>
    <link rel="stylesheet" href="/js/highlight/styles/agate.css">
)";
// 插入mathjax
string s15 = R"(
    <script type="text/javascript" src="/js/MathJax/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
    <script type="text/x-mathjax-config">
      MathJax.Hub.Config({
        tex2jax: {
          inlineMath: [ ['$$','$$'] ],
          displayMath: [ ['$$!','$$'] ],
          processEscapes: true
        },
        "HTML-CSS": {
                 scale: 120
             }
      });
    </script>
)";
// 结束HTML
string s16 = R"(
    <script>
      (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
      (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
      m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
      })(window,document,'script','//www.google-analytics.com/analytics.js','ga');

      ga('create', 'YourGoogleAnalyticsID', 'auto');
      ga('send', 'pageview');
    </script>
    <script src="/js/jquery-1.11.2.min.js"></script>
    <script src="/js/bootstrap.min.js"></script>
    <script src="/js/contents.js"></script>
    </body>
</html>
)";
//    <script src="/js/instantclick.min.js" data-no-instant></script>
//    <script data-no-instant>InstantClick.init();</script>

// 更新sundown输出的HTML
void updatehtml(char *s) {
    {
        char *p;
        while (p = strstr(s, "<blockquote>\n</blockquote>")) {
            char *str = p;
            while (*p != '/')
                p++;
            while (*p != '>')
                p++;
            p++;
            while (*p)
                *str++ = *p++;
            *str = 0;
        }
    }

    {
        char *p;
        while (p = strstr(s, "<code>$$")) {
            char *str = p;
            p += 6;
            while (*p)
                *str++ = *p++;
            *str = 0;
        }
    }

    {
        char *p;
        while (p = strstr(s, "$$</code>")) {
            char *str = p + 2;
            p += 9;
            while (*p)
                *str++ = *p++;
            *str = 0;
        }
    }
}
struct POST {
    string title;
    struct DATE {
        int y, m, d, h, mi, s;
        string tostring() {
            char tmp[25];
            sprintf(tmp, "%d-%02d-%02d %02d:%02d:%02d", y, m, d, h, mi, s);
            return string(tmp);
        }
    } date;
    vector<string> tags;
    string abstract;
    string content;
} post[10005], page[1005];

// 需要跳过的post为1
int skip_post[10005] = {};

char str[10000005];
string html;

// 读取一个文件内容到s
void readfile(char *filename, char *s) {
    FILE *fp = fopen(filename, "r");
    assert(fp);
    printf("    readfile: %s\n", filename);
    int l = 0;
    char c;
    while ((c = fgetc(fp)) != EOF)
        s[l++] = c;
    s[l] = 0;
    fclose(fp);
}
// 把s的内容写到一个文件
void writefile(const char *filename, const char *s) {
    FILE *fp = fopen(filename, "w");
    assert(fp);
    printf("    writefile: %s\n", filename);
    for (int i = 0; s[i]; i++)
        fputc(s[i], fp);
    fclose(fp);
}
// 读取文件名为filename的md文件的info内容到某个内存结构体中
void readmdinfo(char *filename, POST &p) {
    char name[50];
    sprintf(name, "source/md/%s.md", filename);
    printf("    readmdinfo: %s\n", name);
    FILE *fp = fopen(name, "r");
    assert(fp);
    char *s = str;
    fgets(s, 10000000, fp);
    s += 9;
    while (*s != '\n')
        p.title += *s++;
    s = str;
    fgets(s, 10000000, fp);
    s += 8;
    auto &d = p.date;
    sscanf(s, "%d-%d-%d %d:%d:%d", &d.y, &d.m, &d.d, &d.h, &d.mi, &d.s);
    s = str;
    fgets(s, 10000000, fp);
    s += 8;
    char t[50];
    int l = 0;
    while (*s != '\n')
        if (*s == ' ')
            t[l] = 0, p.tags.push_back(t), s++, l = 0;
        else
            t[l++] = *s++;
    if (l)
        t[l] = 0, p.tags.push_back(t);
    //for (int i=0;i<p.tags.size();i++) cout<<p.tags[i],debug;
    fclose(fp);
}
// 读取文件名为filename的md文件的post内容到s
void readmdpost(char *filename, char *s) {
    char name[50];
    sprintf(name, "source/md/%s.md", filename);
    int x = 0;
    if (strcmp(filename, "sample"))
        sscanf(filename, "%d", &x);
    printf("    readmdpost: %s\n", name);
    FILE *fp = fopen(name, "r");
    assert(fp);
    fgets(str, 10000000, fp);
    fgets(str, 10000000, fp);
    fgets(str, 10000000, fp);
    int l = 0;
    char c;
    while ((c = fgetc(fp)) != EOF)
        s[l++] = c;
    s[l] = 0;
    fclose(fp);
}
// <a href="/tags/标签名">标签名</a>
string generatetags(vector<string> &tags) {
    string s;
    for (int i = 0; i < tags.size(); i++)
        s += R"(<a href="/tags/)" + tags[i] + R"(">)" + tags[i] + R"(</a>)";
    return s;
}
// 文章总数
int postnum = 0;
// 插入前一篇文章：<a href="." class="pre">< 这是前一篇文章</a>
int getpreid(int x) {
    int idx;
    for (idx = x + 1; idx <= postnum; idx++) {
        if (!skip_post[idx]) {
            break;
        }
    }
    return idx;
}
string generatepre(int x) {
    int preid = getpreid(x);
    char pre[50];
    sprintf(pre, "/archives/%d", preid);
    string s;
    if (preid != postnum + 1)
        s = s + R"(<a href=")" + pre + R"(" class="pre">< )" + post[preid].title + R"(</a>)";
    return s;
}
// 插入后一篇文章：<a href="." class="next">这是后一篇文章 ></a>
int getnextid(int x) {
    int idx;
    for (idx = x - 1; idx >= 0; idx--) {
        if (!skip_post[idx]) {
            break;
        }
    }
    return idx;
}
string generatenext(int x) {
    int nextid = getnextid(x);
    char next[50];
    sprintf(next, "/archives/%d", nextid);
    string s;
    if (nextid != -1)
        s = s + R"(<a href=")" + next + R"(" class="next">)" + post[nextid].title + R"( ></a>)";
    return s;
}
string getabstract(char *s) {
    int num = 500;
    string ret = "<p>";
    int i = 0;
    if (s[i] == '\n')
        i++;
    for (; i < num && s[i]; i++)
        if (s[i] != '\n')
            ret += s[i];
        else if (s[i + 1] != '\n')
            ret += "</p><p>";
    if (s[i])
        for (int j = num; s[j] != '\n'; j++)
            ret += s[j];
    ret += "......</p>";
    return ret;
}
map<string, vector<int>> tags;
void generatepost(int x) {
    if (skip_post[x]) {
        return;
    }
    // 处理tags
    for (int i = 0; i < post[x].tags.size(); i++)
        tags[post[x].tags[i]].push_back(x);

    char filename[50];
    sprintf(filename, "%d", x);
    char name[50];
    sprintf(name, "archives/%d", x);
    printf("generatepost: %s\n", name);
    POST &tmp = post[x];
    readmdpost(filename, str);
    tmp.abstract = getabstract(str); // 摘要
    writefile("tmp.md", str);
    system("sundown <tmp.md >tmp.html");
    readfile("tmp.html", str);
    updatehtml(str);
    tmp.content = string(str);
    int flag1 = 0, flag2 = 0;
    if (strstr(str, "<pre><code>"))
        flag1 = 1;
    if (strstr(str, "$$"))
        flag2 = 1;
    html = s1 + tmp.title + " - YourSite's blog" + s2 + s3 + '/' + name + s33 + tmp.title + s4 + s5 + tmp.date.tostring() + s6 + generatetags(tmp.tags) + s7 + s8 + str + s9 + s10 + generatepre(x) + generatenext(x) + s11 + s12 + s13;
    if (flag1)
        html += s14;
    if (flag2)
        html += s15;
    html += s16;
    writefile(name, html.c_str());
    printf("%s generated!\n", name);
}
void generatepage(char *filename, string reallinkname = "") {
    printf("generatepage: %s\n", filename);
    POST tmp;
    readmdinfo(filename, tmp);
    readmdpost(filename, str);
    writefile("tmp.md", str);
    system("sundown <tmp.md >tmp.html");
    readfile("tmp.html", str);
    updatehtml(str);
    int flag1 = 0, flag2 = 0;
    if (strstr(str, "<pre><code>"))
        flag1 = 1;
    if (strstr(str, "$$"))
        flag2 = 1;
    if (reallinkname == "")
        html = s1 + tmp.title + " - YourSite's blog" + s2 + s3 + filename + s33 + tmp.title + s4 + s5 + tmp.date.tostring() + s6 + generatetags(tmp.tags) + s7 + s8 + str + s9 + s12 + s13;
    else
        html = s1 + tmp.title + " - YourSite's blog" + s2 + s3 + reallinkname.c_str() + s33 + tmp.title + s4 + s5 + tmp.date.tostring() + s6 + generatetags(tmp.tags) + s7 + s8 + str + s9 + s12 + s13;
    if (flag1)
        html += s14;
    if (flag2)
        html += s15;
    html += s16;
    writefile(filename, html.c_str());
    printf("%s generated!\n", filename);
}
// <div class="pager"><a href="/" class="round pre">Pre</a><a href="/page/3" class="round next">Next</a></div>
string gaopre(int page, int cnt) {
    string s;
    if (page == 1)
        return s;
    char pnum[50];
    if (page - 1 == 1)
        pnum[0] = '/', pnum[1] = 0;
    else
        sprintf(pnum, "/page/%d", page - 1);
    s = s + R"(<a href=")" + pnum + R"(" class="round pre">Pre</a>)";
    return s;
}
string gaonext(int page, int cnt) {
    string s;
    //cout<<cnt<<' '<<postnum,debug;
    if (cnt == postnum + 1)
        return s;
    char pnum[50];
    sprintf(pnum, "/page/%d", page + 1);
    s = s + R"(<a href=")" + pnum + R"(" class="round next">Next</a>)";
}
string getpagehtml(int page, int cnt) {
    string s = R"(<div class="pager">)";
    s += gaopre(page, cnt) + gaonext(page, cnt);
    s += R"(</div>)";
    return s;
}
void generatemain() {
    html = s1 + "YourSite's blog" + s2;
    int page = 1;
    int cnt = 0;
    for (int i = postnum; i >= -1; i--) {
        if (cnt && cnt % 5 == 0 || i == -1) {
            printf("generatemain-page: %d\n", page);
            html += "</div>";
            html += getpagehtml(page, cnt);
            html += s16;
            char filename[50];
            sprintf(filename, "page/%d", page);
            writefile(filename, html.c_str());
            if (page == 1)
                puts("generateindex:"), writefile("index.html", html.c_str());
            // reset
            html = s1 + "YourSite's blog" + s2;
            page++;
        }
        if (i == -1)
            break;
        POST &tmp = post[i];
        //cout<<tmp.title,debug;
        char name[50];
        sprintf(name, "/archives/%d", i);
        html += s3 + name + s33 + tmp.title + s4 + s5 + tmp.date.tostring() + s6 + generatetags(tmp.tags) + s7 + s8 + tmp.abstract + s9 + "</div>";
        cnt++;
    }
}
// <div class="list"><a href="/archives/">标题</a><span>2012-12-12 12:12:12</span></div>
void generatearchive() {
    printf("generate-archive\n");
    html = s1 + "YourSite's blog" + s2;
    html += R"(<div class="archive">)";

    for (int i = postnum; i >= 0; i--) {
        if (skip_post[i]) {
            continue;
        }
        html += R"(<div class="list"><a href="/archives/)";
        char name[50];
        sprintf(name, "%d", i);
        html = html + name + "\">" + post[i].title + "</a><span>" + post[i].date.tostring() + "</span></div>";
    }

    html += "</div></div>" + s16;
    writefile("archive", html.c_str());
}
void tagpage() {
    printf("generate-tagpage\n");
    html = s1 + "YourSite's blog" + s2;
    html += R"(<div class="archive">)";

    for (auto i = tags.begin(); i != tags.end(); i++) {
        html += R"(<div class="list"><a href="/tags/)";
        char num[50];
        sprintf(num, "%d", i->second.size());
        html = html + i->first + "\">" + i->first + "</a><span>" + num + "</span></div>";
    }

    html += "</div></div>" + s16;
    writefile("tags/index.html", html.c_str());
}
map<string, string> mp;
void gettagpage() {
    // 处理UTF-8与ANSI文件名读写问题
    FILE *fp1 = fopen("source/tagsUTF-8.txt", "r");
    assert(fp1);
    FILE *fp2 = fopen("source/tagsANSI.txt", "r");
    assert(fp2);
    char fs1[50], fs2[50];
    while (fscanf(fp1, "%s", fs1) != EOF)
        fscanf(fp2, "%s", fs2), mp[fs1] = fs2;
    fclose(fp1), fclose(fp2);

    for (auto i = tags.begin(); i != tags.end(); i++) {
        printf("generatetags-%s\n", i->first.c_str());
        html = s1 + i->first.c_str() + " - YourSite's blog" + s2;
        html += R"(<div class="archive">)";

        html += "<h3>" + i->first + "</h3>";

        for (int j = i->second.size() - 1; j >= 0; j--) {
            int x = (i->second)[j];
            html += R"(<div class="list"><a href="/)";
            char name[50];
            sprintf(name, "archives/%d", x);
            html = html + name + "\">" + post[x].title + "</a><span>" + post[x].date.tostring() + "</span></div>";
        }

        html += "</div></div>" + s16;
        string tmp;
        if (mp.find(i->first.c_str()) != mp.end())
            tmp = tmp + "tags/" + mp[i->first.c_str()];
        else
            tmp = tmp + "tags/" + i->first.c_str();
        writefile(tmp.c_str(), html.c_str());
    }
}
void getskippost() {
    FILE *fp = fopen("source/skip.txt", "r");
    assert(fp);
    int post_id;
    while (fscanf(fp, "%d", &post_id) != EOF) {
        skip_post[post_id] = 1;
    }
    fclose(fp);
}
void generaterss() {
    char num[50];
    sprintf(num, "%d", postnum);
    string batname = "generaterss.bat ";
    batname += num;
    system(batname.c_str());
}
int main(int argc, char **argv) {
    postnum = 11;
    for (int i = 0;; i++) {
        char num[50];
        sprintf(num, "%d", i);
        char filename[50];
        sprintf(filename, "source/md/%s.md", num);
        FILE *fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("Detect md file 0 - %d\n", i - 1);
            postnum = i - 1;
            break;
        }
    }
    if (argc > 1)
        sscanf(argv[1], "%d", &postnum);
    generatepage("about");
    generatepage("links");
    //    generatepage("notes");
    for (int i = 0; i <= postnum; i++) {
        char filename[50];
        sprintf(filename, "%d", i);
        readmdinfo(filename, post[i]);
    }
    getskippost();
    for (int i = 0; i <= postnum; i++)
        generatepost(i);
    generatemain();
    generatearchive();
    tagpage();
    gettagpage();
    generaterss();
    return 0;
}
