---
title:  "My first Jekyll blog post!"
date:   2021-04-06 12:36:53 +0300
excerpt_separator: <!--more-->
categories: jekyll github blog
tags: blogging setup
author_profile: true
---
I have set up a simple Jekyll website with ~~default~~ minimal mistakes theme. Let's
see if this works!

<!--more-->

{% highlight c++ %}
#include <iostream>
#include <string>
void print_hi(std::string name) {
  std::cout << "Hi, " << name << std::endl;
}
int main() {
  print_hi("Cem");
}
{% endhighlight %}

My repository is on [GitHub][gh-pt]. This site is in a special branch called `gh-pages`.

Old text:
Check out the [Jekyll docs][jekyll-docs] for more info on how to get the most out of Jekyll. File all bugs/feature requests at [Jekyll’s GitHub repo][jekyll-gh]. If you have questions, you can ask them on [Jekyll Talk][jekyll-talk].

[gh-pt]: https://github.com/gcem/pathtracer
[jekyll-docs]: https://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
