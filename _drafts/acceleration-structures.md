---
title: "Acceleration structures"
date: 2021-04-19 11:00:00 +0300
categories: pathtracer
tags: intersection-test acceleration-structure visualization
---

I have implemented some acceleration structures and measured their performance.

<!--more-->

In my Path Tracer, I have added the option to use a single Bounding Box, a
Bounding Volume Hierarchy, a k-d Tree or just Brute Force intersection tests.

As I had written in [visualizing acceleration structures][visualizing-acc], my
Path Tracer also outputs the rendering time of each pixel. Along with different
acceleration structures and different thresholds, these images provide a beautiful 
demonstration of how they work. Let's start with some images. Performance measurements 
will follow later.

# Pixel rendering times

## Brute force intersection tests

This is the simplest form of intersection test: For each ray, we test intersection
with every single triangle in the scene. I would like to start with the rendering
times using this method, to show how the other methods differ.

{: .notice--info }
Bright pixels mean more time was taken.

{% include figure image_path="/assets/images/time/bf/berserker.png" alt="berserker rendering time" caption="Rendering time of Berserker scene using brute force." %}

{% include figure image_path="/assets/images/time/bf/bunny.png" alt="bunny rendering time" caption="Rendering time of Bunny scene using brute force." %}

{: .notice--success }
In the next scene, shadows of *ODTÜ* text and logo are visible in rendering times.
But the shadow of science tree is not. We can guess that science tree was checked last 
during shadow ray intersection tests. (So that *ODTÜ* shadow was detected without
testing the science tree)

{% include figure image_path="/assets/images/time/bf/scienceTree.png" alt="science tree rendering time" caption="Rendering time of Science Tree scene using brute force." %}

{% include figure image_path="/assets/images/time/bf/windmill.png" alt="windmill rendering time" caption="Rendering time of Windmill scene using brute force." %}

{% include figure image_path="/assets/images/time/bf/horse.png" alt="horse rendering time" caption="Rendering time of Horse scene using brute force." %}

In these images, background is not black. This means background is taking a significant 
time to render. Surfaces are even brighter, because once we hit a surface, we cast 
shadow rays and their intersections are also found by brute force.

## Bounding box

Let's add a single axis-aligned bounding box around each of the meshes and see how the rendering
times change. If a ray hits the bounding box, each triangle in the mesh is tested as in 
[Brute force](#brute-force-intersection-tests) method.

{: .notice--success }
Berserker consists of multiple meshes.

{% include figure image_path="/assets/images/time/bb/berserker.png" alt="berserker rendering time" caption="Rendering time of Berserker scene using bounding box." %}

{% include figure image_path="/assets/images/time/bb/bunny.png" alt="bunny rendering time" caption="Rendering time of Bunny scene using bounding box." %}

{: .notice--success }
Time taken on the floor (reflection of the boxes) is because of shadow rays.

{% include figure image_path="/assets/images/time/bb/scienceTree.png" alt="science tree rendering time" caption="Rendering time of Science Tree scene using bounding box." %}

{: .notice--success }
Windmill consists of multiple meshes.

{% include figure image_path="/assets/images/time/bb/windmill.png" alt="windmill rendering time" caption="Rendering time of Windmill scene using bounding box." %}

{: .notice--success }
Time taken on the floor (reflection of the boxes) is because of shadow rays.

{% include figure image_path="/assets/images/time/bb/horse.png" alt="horse rendering time" caption="Rendering time of Horse scene using bounding box." %}

As you can see from the images, rays that don't hit the box are rendered instantly,
so the empty areas of the pictures have turned black. Cubes around the meshes have appeared.
This means, if a ray hits the cube, it still takes lots of time. Also, the surfaces themselves
are still taking too much time because their shadow rays are always inside the box.

You can also see the "shadows" of the boxes on the floor. These are the actual shadows 
that would be cast by the bounding box with respect to the light positions in the scene,
if bounding boxes were visible. The reason is that the shadow rays from floor to the
lights are hitting the box, only if they are in the shadow of the bounding box. When the
shadow ray hits the box, we test the triangles inside, thus taking lots of time.

## Bounding volume hierarchy

This is a hierarchy of bounding boxes shown in the previous section. We create a bounding 
box around the mesh, then divide the triangles into two groups on a chosen axis, and 
recursively create BVH's for these two groups.

My code does the division on the longest axis. It stops when a certain triangle number 
is reached, or if there aren't any more divisions.

Intersection test is also done recursively. After testing the bounding box, we first 
recursively test for intersection in the closer child. If an intersection happens
before the ray hits the other child's bounding box, we return it immediately.

This is how the rendering times look with a BVH:

{% include figure image_path="/assets/images/time/bvh/berserker.png" alt="berserker rendering time" caption="Rendering time of Berserker scene using bounding volume hierarchy." %}

{% include figure image_path="/assets/images/time/bvh/bunny.png" alt="bunny rendering time" caption="Rendering time of Bunny scene using bounding volume hierarchy." %}

{% include figure image_path="/assets/images/time/bvh/scienceTree.png" alt="science tree rendering time" caption="Rendering time of Science Tree scene using bounding volume hierarchy." %}

{% include figure image_path="/assets/images/time/bvh/windmill.png" alt="windmill rendering time" caption="Rendering time of Windmill scene using bounding volume hierarchy." %}

{% include figure image_path="/assets/images/time/bvh/horse.png" alt="horse rendering time" caption="Rendering time of Horse scene using bounding volume hierarchy." %}

{: .notice--info }
Dragon scene has more than 800 thousand triangles.

{% include figure image_path="/assets/images/time/bvh/dragon.png" alt="dragon rendering time" caption="Rendering time of Chinese Dragon scene using bounding volume hierarchy." %}

Here, the red areas have taken the shape of meshes. This means we don't spend much 
time for rays that don't hit a surface. The images show that BVH structure is pretty 
good at skipping empty areas.

Also, notice that we still see the "shadow" of BVH, but it also has the shape of the mesh,
as opposed to the shadows of the bounding box of last section.

# Running times

These measurements are done with 8 threads and 16x16 pixel tiles.

| Scene           | Brute Force | Bounding Box | Bounding Volume Hierarchy | k-D Tree |
| :-------------- | :---------- | :----------- | :------------------------ | :------- |
| bunny.xml       | 4253        | 1885         |                           |          |
| scienceTree.xml | 9802        | 1196         |                           |          |
| berserker.xml   | 10038       | 2276         |                           |          |
| car.xml         | 38224       | 6783         |                           |          |
| low_poly.xml    | 30436       | 8499         |                           |          |
| tower.xml       | 35521       | 18870        |                           |          |
| windmill.xml    | 24538       | 8750         |                           |          |
| horse.xml       | 76347       | 20953        |                           |          |

# Bounding Volume hierarchy

## Division along longest axis

When I made the code divide on the longest axis, and stop when one child node has
all the triangles, this is what I got:

```bash
$ ./PathTracerApp -a bvh ../scenes/scienceTree.xml 
Switched to brute force with 7 triangles
Switched to brute force with 12 triangles
Switched to brute force with 9 triangles
Switched to brute force with 10 triangles
Switched to brute force with 9 triangles
Switched to brute force with 82 triangles
Switched to brute force with 7 triangles
Switched to brute force with 8 triangles
Switched to brute force with 14 triangles
Switched to brute force with 14 triangles
Switched to brute force with 16 triangles
Switched to brute force with 189 triangles
Switched to brute force with 191 triangles
Switched to brute force with 11 triangles
Switched to brute force with 7 triangles
Switched to brute force with 10 triangles
scienceTree.png took 279 ms
```

There were some nodes with ~190 triangles that couldn't be divided. So, I have
switched to another approach, where the program tried other axes when it
couldn't divide on the longest one. This made all nodes have a number of triangles
less than the threshold I had set. But it didn't provide a significant difference
in running time.

Then, I thought the tree could be unbalanced. So, I made the code try all axes,
and choose the one that balanced the triangles most evenly.

[visualizing-acc]: /pathtracer/multithreading/pathtracer/multithreading-and-time/#bonus---pixel-rendering-times