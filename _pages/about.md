---
permalink: /about/
title: "About"
---

This blog is for Advanced Ray Tracing (CENG 795) course. I will write a path tracer and share my progress here. A path tracer is a program that renders a scene by tracing rays and simulating the behavior of light.

Rendering means finding the colors of each pixel seen by the camera. There are various methods to do this. A simple method is just rasterizing the triangles in the scene to find which pixels are covered by that triangle. Then, one can use a depth buffer to decide which triangle is closest to the camera. Once all triangles are rasterized, the job is done. It is common in this approach to calculate illumination at the vertices and then interpolate this value.

This method is fast but it doesn't produce very realistic images. It is possible to do some kind of shadow mapping, but path tracing offers much more.

In path tracing, we follow the path a light ray would follow. We calculate the color of surfaces that light hits on the way. Of course, starting from light sources and casting rays in all directions would be extremely slow. To speed things up, we follow the reverse path: we start from the camera, and track the light rays backward.

Path tracing allows us to support realistic shadows, transparent and semi-transparent objects (magnifiers, liquids), mirrors,  light-emitting surfaces, real ambient lighting (where objects illuminate others around them) and many more cool stuff. That's why it is worth studying.