---
title: "Multithreading and visualizing rendering time"
date: 2021-04-16 16:10:00 +0300
categories: multithreading pathtracer
tags: multithreading visualization
---

I have added multithreading to my code, and done some measurement with different
tile sizes. I have also made my code draw the time it took to render each pixel.

<!--more-->

Before coding the path tracer, I had thought that I could do without multithreading.
My motivation was both the ease of debugging, and the possibility that I would switch
to GPU for some of the tasks. However, with my path tracer without any acceleration
structures, drawing moderately complicated scenes takes more than 2 minutes.

I have added simple multithreading to see the results of my changes to the code
faster. The image is divided into tiles, and each thread draws the next tile in
the queue.

In this post, I will first talk about different ways to divide the work across
threads, and then show the result of my measurements using different tile sizes.

# Dividing the image for multithreading

There are two considerations in dividing the tasks.

The first one is the shape and
relative position of the tasks. This includes if we will draw the image line by
line, and if the threads will be drawing adjacent lines.

The second topic is the size of tasks. If we use smaller tasks, there will be more 
overhead, but the load will be balanced more evenly.

# Rows versus Tiles

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




| Scene           | Initial rendering time (ms) | Time after optimizations (ms) |
| :-------------- | :-------------------------- | :---------------------------- |
| bunny.xml       | 22303                       | 22319                         |
| scienceTree.xml | 51304                       | 49629                         |
| berserker.xml   | 52731                       |                               |
| car.xml         | 196688                      |                               |
| low_poly.xml    | 159910                      |                               |
| tower.xml       | 194349                      |                               |
| windmill.xml    | 131885                      |                               |