---
title: "A small optimization for shadow ray intersection tests"
date: 2021-04-13 23:00:00 +0300
categories: pathtracer
tags: intersection-test optimization
---

Last week, while implementing shadows, I used the same intersection test that
was used for viewing rays. But this code can be optimized for shadow ray tests
by removing unnecessary calculations.

<!--more-->

# Possible optimizations

The intersection tests used for viewing rays do some extra work that is not
needed for shadow rays. I will list them below.

## Terminating if surface is too far

A shadow ray has a maximum t value as well as
the minimum (0) value. This maximum value shows the distance of light to the
current surface. We don't care about the surfaces that are behind the light in
shadow tests. So, we can directly terminate a triangle's intersection test if
the t found is higher than the maximum t.

# Stop searching the mesh once an intersection is found

After finding an intersection, meshes continue to look for other
(closer) intersections. However, for shadow rays, the existance of one such
surface is enough to report the result. This extra work increases rendering time
significantly, especially when there are no acceleration structures.

# Do not calculate sphere's normal

My intersection tests return the normal at intersection point. Although
this should not cause much of a slowdown, I can still avoid it for shadow rays.

# Time measurements

I will measure rendering times of some images before and after making the
changes I discussed. I would like to remind that there are still no acceleration
structures in place.

| Scene           | Initial rendering time (ms) | Time after optimizations (ms) |
| :-------------- | :-------------------------- | :---------------------------- |
| bunny.xml       | 22303                       | a                             |
| scienceTree.xml | 51304                       |                               |
| berserker.xml   | 52731                       |                               |
| car.xml         | 196688                      |                               |
| low_poly.xml    | 159910                      |                               |
| tower.xml       | 194349                      |                               |
| windmill.xml    | 131885                      |                               |