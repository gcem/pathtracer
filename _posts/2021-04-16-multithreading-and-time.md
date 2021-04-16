---
title: "Multithreading and visualizing rendering times"
date: 2021-04-16 16:10:00 +0300
categories: multithreading pathtracer
tags: multithreading visualization

gallery:
  - url: /assets/images/time/berserker_noacc.png
    image_path: /assets/images/time/berserker_noacc.png
    alt: "Berserker scene rendering time"
    title: "Berserker scene rendering time"
  - url: /assets/images/time/science_tree_noacc.png
    image_path: /assets/images/time/science_tree_noacc.png
    alt: "METU logo and Science Tree time"
    title: "METU logo and Science Tree rendering time"
  - url: /assets/images/time/windmill_noacc.png
    image_path: /assets/images/time/windmill_noacc.png
    alt: "Windmill scene rendering time"
    title: "Windmill scene rendering time"
---

I have added multithreading to my code, and done some measurement with different
tile sizes. I have also made my code draw the time it took to render each pixel.

<!--more-->

Before coding the path tracer, I had thought that I could do without multithreading.
My motivation was both the ease of debugging, and the possibility that I would switch
to GPU for some of the tasks. However, with my path tracer without any acceleration
structures, drawing moderately complicated scenes takes more than 2 minutes. This
is too much, so I need a (possibly temporary) solution.

I have added simple multithreading to see the results of my changes to the code
faster. The image is divided into tiles, and each thread draws the next tile in
the queue. To make debugging easy, I made CMake take an option for multithreading,
and disable it automatically when building for Debug configuration.

In this post, I will first talk about different ways to divide the work across
threads, and then show the result of my measurements using different tile sizes.

# Dividing the image for multithreading

There are two considerations in dividing the tasks.

The first one is the shape and
relative position of the tasks. This includes if we will draw the image line by
line, and if the threads will be drawing adjacent lines.

The second topic is the size of tasks. If we use smaller tasks, there will be more 
overhead, but the load will be balanced more evenly.

## Rows versus Tiles

We can render the image row by row, or divide it into the tiles. Tiled drawing is
preferred because it makes better use of the cache. Check out this drawing:

{% include figure image_path="assets/images/row_tile.png" alt="row and tile" caption="A row and a tile in a scene" %}

In this scene, the row I have drawn goes through all meshes in the scene. So, the
program will need to bring triangles from all of the meshes to the cache each time
it renders a row.

On the other hand, the tile has only one mesh to draw. If we have bounding boxes
for other meshes, we will not need to bring any of their triangles into the CPU cache.
So, when the mesh is in the cache, lots of rows of that mesh will be drawn before
we move to the right.

## Ordering the tiles

With a similar reasoning about the cache usage, we need to keep the tiles being rendered
clustered. I will choose the easy way and simply go through the rows.

## Tile size

I want to measure the rendering times with different tile sizes. However my path tracer
still **doesn't have acceleration structures**. This is very important, because as
I have written above, the speed improvement caused by cache utilization strictly depends
on the existance of these structures.

So, I have arbitrarily chosen the tile size to be 16x16. I will come back and
add new columns to this table when I implement an acceleration structure. Until
then, this is how single-threaded compares to 8-threaded on the brute-force approach.

| Scene           | No multithreading | 16x16 tiles |
| :-------------- | :---------------- | :---------- |
| bunny.xml       | 22303             | 4253        |
| scienceTree.xml | 51304             | 9802        |
| berserker.xml   | 52731             | 10038       |
| car.xml         | 196688            | 38224       |
| low_poly.xml    | 159910            | 30436       |
| tower.xml       | 194349            | 35521       |
| windmill.xml    | 131885            | 24538       |

Table: Scene rendering times in milliseconds with 8 threads and no acceleration structures


# Bonus - pixel rendering times

In my last course on computer graphics, I made my ray tracer draw the rendering
time of each pixel instead of the pixel colors, and it provided a beautiful
demonstration of how acceleration structures (bounding box, bounding volume hierarchy
etc.) worked. So, I have decided to do a similar thing in this project.

My path tracer now outputs a second image, where the red channel shows the time it
took to render that pixel in the original image. It maps the times to the range
(0, 255) to make the best use of 8-bit color depth.

On my first try, images were created where a few isolated pixels were bright red
and the rest of the image was dark. I believe these isolated pixels were caused by
my threads being scheduled out of the processor, in the middle of the rendering of
that pixel. This is very probable since I am now using all 8 hardware threads
available. Here is such an example:

{% include figure image_path="assets/images/windmill_time_bad.png" alt="windmill
with isolated pixels" caption="Rendering times of Windmill scene drawn black, with
isolated bright pixels" %}

To avoid this issue, I have made the code ignore pixels that took significantly
longer than three of their four immediate neighbors. These are the results for
some scenes: (Original scenes can be found in [this post][original-images])

{% include gallery %}

As you can see, surfaces take longer to draw than the background. Also, parts with shadows
take less time to draw than illuminated surfaces, as we don't evaluate the lighting equations.
We can also terminate the intersection tests early in shadows. I will write another article about this.

However, the background is not very dark either. That means it is taking significant
time to render. I expect the background to become completely black, when I implement a 
decent acceleration structure. Also, I expect to see a cube around the meshes when I 
add a single bounding box to them.

[original-images]: /pathtracer/first-images-first-mistakes/#more-images