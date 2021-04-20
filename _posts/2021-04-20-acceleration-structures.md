---
title: "Acceleration structures"
date: 2021-04-20 18:20:00 +0300
categories: pathtracer
tags: intersection-test acceleration-structure visualization
---

I have implemented some acceleration structures and measured their performance.

<!--more-->

In my Path Tracer, I have added the option to use a single Bounding Box, a
Bounding Volume Hierarchy, a k-d tree or just Brute Force intersection tests.

As I had written in [visualizing acceleration structures][visualizing-acc], my
Path Tracer also outputs the rendering time of each pixel. These images provide 
a beautiful demonstration of how different acceleration structures with different 
thresholds work. Let's start with some images. Performance measurements 
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

## K-D Tree 

In this structure, we divide the space (inside a bounding box) into two regions, just 
like the BVH. But this time, we don't create separate bounding boxes for the two 
volumes.

Triangles intersecting the division plane are put in both children. This allows
us to skip testing the second child if an intersection is found in the first child.
Because in intersection tests, we start with the closer child.

There are again multiple heuristics to choose the middle plane. I used the approach 
to make the total surface area of triangles in two children equal. To keep things
simple, I have considered each triangle as a single point at its center of mass.

The structure stops dividing the space once the number of triangles reaches a threshold 
value.

{: .notice--danger }
I must say I am very disappointed with the result. With a high threshold like 128 triangles, my 
k-d tree performs slightly better than the simple bounding box. The difference is not 
even **x 2**. With lower threshold values, the situation is worse. Maybe my 
implementation has a problem.

{: .notice--success }
After writing the note above, I have realized that my code didn't ignore intersections with planes
that happen outside the box. So, for the pixels that don't hit a surface, all triangles were still 
being tested. Indeed, empty areas of the meshes had turned bright red. Fixing this increased the
speed a lot. See the table with time measurements at the end.

{% include figure image_path="/assets/images/time/kd/berserker.png" alt="berserker rendering time" caption="Rendering time of Berserker scene using k-d tree." %}

{% include figure image_path="/assets/images/time/kd/bunny.png" alt="bunny rendering time" caption="Rendering time of Bunny scene using k-d tree." %}

{% include figure image_path="/assets/images/time/kd/scienceTree.png" alt="science tree rendering time" caption="Rendering time of Science Tree scene using k-d tree." %}

{% include figure image_path="/assets/images/time/kd/windmill.png" alt="windmill rendering time" caption="Rendering time of Windmill scene using k-d tree." %}

{% include figure image_path="/assets/images/time/kd/horse.png" alt="horse rendering time" caption="Rendering time of Horse scene using k-d tree." %}

Perhaps the most noteworthy thing about these images is that surfaces themselves are
rather dark, but empty areas are red. This is the opposite of BVH.

With BVH, we could skip the empty areas quickly. With the k-d tree, if there is
an intersection, then we start looking at the closest triangles. So we find the
intersections quickly. But if there is no intersection, k-d tree checks lots of 
volumes before deciding there is no intersection.


# Running times

These measurements are done with 8 threads on i7-4770 (3.4 GHz) and 16x16 pixel
tiles. Listed times are rendering times, the time to build the acceleration structures 
is not included. However, it is very low (5-60 ms together with all parsing operations) 
in all scenes except Chinese Dragon. Chinese Dragon's parsing+building times will be listed 
separately.

{: .notice--warning }
Last column in this table is my first (and bad) implementation of k-d tree. I have 
explained it in a box in the [k-d tree section](#k-d-tree).

| Scene              | Brute Force | Bounding Box | Bounding Volume Hierarchy | k-d tree (Improved) | k-d tree (First) |
| :----------------- | :---------- | :----------- | :------------------------ | :------------------ | :--------------- |
| bunny.xml          | 4253        | 1885         | 65                        | 333                 | 481              |
| scienceTree.xml    | 9802        | 1196         | 283                       | 703                 | 1303             |
| berserker.xml      | 10038       | 2276         | 407                       | 722                 | 1020             |
| car.xml            | 38224       | 6783         | 753                       | 3003                | 5868             |
| low_poly.xml       | 30436       | 8499         | 1127                      | 4133                | 6614             |
| tower.xml          | 35521       | 18870        | 1023                      | 5790                | 6046             |
| windmill.xml       | 24538       | 8750         | 737                       | 3504                | 6046             |
| horse.xml          | 76347       | 20953        | 424                       | 10736               | 24330            |
| chinese_dragon.xml | -           | > 7 min      | 194                       | 152414              | -                |

Table: Rendering times (in milliseconds), using different acceleration structures

In the following table, it would be best to compare acceleration structures with 
the brute-force method, because the brute-force time includes only the essential parts 
of parsing the huge scene file.

{: .notice--info }
The XML file for Chinese Dragon is 47 MB.

| Scene              | Brute Force | Bounding Box | Bounding Volume Hierarchy | k-d tree |
| :----------------- | :---------- | :----------- | :------------------------ | :------- |
| chinese_dragon.xml | 546         | 591          | 945                       | 1673     |

Table: Time it takes (in milliseconds) to build the scene for Chinese Dragon (includes parsing the 
scene file and creating acceleration structures)

# Additional notes

## Bounding Volume Hierarchy

My implementation uses the mid-point heuristic. It divides the box in the middle 
of its longest axis. It stops when the number of triangles reaches a threshold (8),
or it can't divide the triangles and get smaller groups.

I have experimented with this threshold (tried 4, 8, 16, 32) but the difference was 
not very high. 8 seemed like the best but I didn't test extensively.

### Division along longest axis

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

## K-D Tree

I have implemented the surface area heuristic. It chooses a division plane such 
that the total areas of the triangles at each side are as close as possible. I didn't 
consider triangles at the middle to belong to both sides. I just used the center of 
mass of the triangles.

As for the threshold to switch to brute-force, low values (32, 64) perform very badly. 
Stopping at 128 triangles seems to be the best with my implementation. I am still not 
sure if I am doing everything correctly, because having to test up to 128 triangles with 
brute force doesn't sound correct. Yet it performs better than, for example, 32 triangles.

[visualizing-acc]: /pathtracer/multithreading/pathtracer/multithreading-and-time/#bonus---pixel-rendering-times