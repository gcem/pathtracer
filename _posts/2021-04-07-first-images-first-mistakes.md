---
title: "First images, first mistakes"
date: 2021-04-07 16:00:00 +0300
categories: pathtracer
tags: mistakes intersection-test
header:
    overlay_image: /assets/images/mistake.png
    caption: "An image posted to CENG WhatsApp group"

gallery:
  - url: /assets/images/low_poly_scene.png
    image_path: /assets/images/low_poly_scene.png
    alt: "Mountain scene"
    title: "Mountain scene"
  - url: /assets/images/science_tree.png
    image_path: /assets/images/science_tree.png
    alt: "METU logo and Science Tree"
    title: "METU logo and Science Tree"
  - url: /assets/images/windmill.png
    image_path: /assets/images/windmill.png
    alt: "Windmill scene"
    title: "Windmill scene"
---

I have completed implementing all structures and I/O operations. Now I will generate my first renders.

<!--more-->

# Faulty renders

## Sphere scene

This is a simple scene with two spheres and a point light. The result is supposed to look like this:

{% include figure image_path="/assets/images/mistake/two_spheres.png" alt="two spheres expected output" caption="Expected output of the \"Two Spheres\" scene." %}

But I have received wrong renderings of this scene, as I explain in the following sections, and had to fix some bugs in my code.

### Grey spheres

At my first try, my ray tracer has drawn the spheres in the correct place, but their colors were dark grey:

{% include figure image_path="/assets/images/mistake/grey_spheres.png" alt="spheres being rendered dark grey" caption="Spheres rendered dark grey." %}

There are two obvious facts about this output. Firstly, the color is same at all parts of the spheres. Secondly, there is no shadow.

Both of these facts show that ambient lighting works, but there is a problem with diffuse and specular shading. So, I need to inspect shading calculations. Here's the part of my erronous code:

```c++
auto diffuse = material.diffuse * normal.dot(lightDir);
auto specular = material.specular *
                pow(normal.dot(mid), material.phongExponent);
```

The problem was that I had forgotten to multiply these values with light intensity. Adding

{% highlight c++ %}
* light.intensity
{% endhighlight %}

to both equations resulted in a different rendering result.

### White spheres

When I added that multiplication, I got spheres that are white and very bright. Here's the second render:

{% include figure image_path="/assets/images/mistake/white_spheres.png" alt="spheres being rendered bright white" caption="Spheres rendered bright white." %}

This time, the tiny red and blue areas hinted the problem: The values I have multiplied with were too high. So, I realized that light should decrease with distance (the square of distance, actually). When I added division by the square of distance to the equation, the scene was rendered correctly.

## Cornell Box scene

Another problem I had was with a scene similar to the infamous Cornell Box. This is how it should look:

{% include figure image_path="/assets/images/mistake/cornellbox.png" alt="cornellbox expected output" caption="Expected output of the \"Cornell Box\" scene." %}

### Dark meshes

This is what I got in this scene instead:

{% include figure image_path="/assets/images/mistake/dark_meshes.png" alt="dark meshes" caption="Cornell Box scene with very dark triangle meshes." %}

Finding the reason of this one took some debugging. Finally, I have seen that the problem was how I used the *intersection test epsilon* value. Normally, barycentric coordinates of a triangle should be in the range `(0, 1)` for a point to be inside the triangle. But my code allowed them to be in `(-epsilon, 1 + epsilon)`, so that there wouldn't be tiny lines between two adjacent triangles. This was correct. What was wrong was that while adding these, I had also changed the check for `t`:

```c++
// initial code
if (t <= 0)
    return -1;

// my change while adding epsilon check
if (t <= -epsilon)
    return -1;
```

This way, the program allowed `t` to be slightly negative, allowing rays to intersect with surfaces slightly behind their origin. Not surprisingly, this made all shadow rays intersect with the triangle they originated from. So all meshes were drawn as if they were in shadow.

I have added the following unit test to demonstrate this problem:

```c++
TEST(TriangleTest, NoEpsilonForT)
{
    Triangle tri({ -1, -1, 0 }, { 1, -1, 0 }, { 0, 1, 0 });
    Ray ray({ 0, 0, -0.2 }, { 0, 0, -1 });

    auto t = tri.intersect(ray, 30); // 30 is epsilon
    EXPECT_EQ(-1, t) << "t should not depend on epsilon";
}
```

This test failed. When I fixed the bug above, the test passed and the scene was rendered correctly.

# Final words

Having only three bugs that were relatively easy to solve is a success, especially in an application like this with lots of calculations. For example, it is very easy to type an x instead of y in a vector operation, and cause some weird behavior.

I believe this was because I had unit tests for all of the code I had written initially.

Also, when I coded the main path tracer logic, I wanted to see the results immediately, so I skipped Test-Driven Development for that class. If I hadn't done so, I guess I wouldn't have had the bugs in the [Two Spheres](#sphere-scene) scene either.

So, I am glad I wrote those tests. As I write this post, there are more than 60 unit tests, that run automatically each time I push something to a branch on GitHub ([Test Results][gh-test-results]).

# More images

I would like to end this post with some other rendering results from my final ray tracer. Thanks to Akif Üslü, we can convert [Blender][blender] scenes to our XML format. Some of these scenes are shared by Akif.

{% include gallery caption="Some renders by my ray tracer for Assignment 1." %}

Since I have coded this ray tracer for the first assignment, there were no acceleration structures for meshes. I haven't added multithreading either. So, these scenes took a long time to render. For example, the one with METU logo took 49 seconds on my machine. I will share more time measurements when I write about acceleration structures. Until then!

[gh-test-results]: https://github.com/gcem/pathtracer/actions
[blender]: https://www.blender.org/