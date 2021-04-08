---
title:  "My first Jekyll blog post!"
date:   2021-03-30 12:36:53 +0300
excerpt_separator: <!--more-->
categories: blogging
tags: jekyll github blogging setup
author_profile: true
search: false
---
I have set up a simple Jekyll website with "minimal mistakes" theme. It is hosted by GitHub.

<!--more-->

Let's see if this code block works:

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

I believe I will be using this post as a playground, to test blog features before posting them to real blog entries.

[gh-pt]: https://github.com/gcem/pathtracer