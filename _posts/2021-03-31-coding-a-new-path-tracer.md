---
title: "Coding a new path tracer"
date: 2021-03-31 12:36:53 +0300
categories: pathtracer
tags: planning testing documentation
header:
    overlay_image: /assets/images/spheres.png
    caption: "Sphere scene from my old ray tracer"
---

For the Advanced Ray Tracing (CENG 795) course at METU, I will be coding a path tracer this term.

<!--more-->

In the broadest sense, a path tracer is a program that can render scenes in a very realistic way, due to its capability of simulating light’s behavior. There is more discussion of this topic in the [About][about] page. We will start with coding a very basic ray tracer, and extend it to a highly capable path tracer during the course of the term.

This blog post will be about the first week’s assignment: Making a ray tracer that takes a simple scene file and creates images of the scene. Since I have already written this ray tracer for Introduction to Computer Graphics (CENG 477) course, I will end my discussion with what I plan to do differently for this assignment, compared to my old ray tracer.

Before writing about my plan, reciting the specifications is necessary.

# Specifications

## The scene file

Scene file is a text file in XML format. It has the following information:

* Cameras: Location and orientation of cameras, the resolution and name of output image.

* Point Lights: Location and intensity of point lights.

* Materials: Color of a surface, given separately for each shading model.

* Surfaces: Triangle meshes, triangles and spheres. 

There are also additional data such as shadow ray epsilon and background color.

## Expected output

Ray tracer should use diffuse shading and Blinn-Phong shading to create an image of the scene. It should also support shadows by casting shadow rays.

 

# My plan

## Language

I will code the ray tracer using C++17.

## Project structure

I will use CMake to define the project structure and build it. 

## Testing

Google Test and Google Mock will be used for writing unit tests. A ray tracer is very suitable for unit testing and Test-Driven Development, since it is essentially a collection of short linear algebraic routines. Triangle-ray intersection, determinant calculations, shading equations are easy to test, yet they can cause lots of time-consuming bugs if not tested appropriately. Therefore, I expect to see a time benefit even though I will spend some additional time writing tests.

##  The program

I will define interfaces such as Camera, Light, Surface, Material that express the required capabilities  of these objects for ray tracing. Also an interface such as Ray Tracer is needed, to keep the core logic of ray tracing, that should probably use a Camera and a Scene object.

I will create separate concrete classes that implement these interfaces. Although in this assignment there will mostly be a single concrete class that implements an interface, I nevertheless find this way of working useful because virtual methods help with testing (mocking is easier) and I don’t know yet what kind of new concrete classes I will need for the upcoming assignments.

I will write a Parser that will create appropriate objects, according to the scene XML. Once all parts are ready and tested, rendering should be as easy as calling a function of an object.

I will probably use some libraries for XML parsing and image I/O. I would love to implement these myself but I want to spare more time to our subject of study.

 

# After CENG 477

In CENG 477, there was a competition to write the fastest ray tracer. To meet this goal, I have used parallelism and implemented acceleration structures.

However, I have also abandoned simple programming principles such as using interfaces, because “Virtual functions would increase the size of an object in memory, possibly causing the CPU cache to hold a lower number of triangles. They would also introduce a calling overhead.” However, this time I will not do any premature optimizations of this kind.

Since it is possible to delegate linear algebraic operations to optimized libraries such as BLAS implementations, or do them in bulk on GPU, I will also not try to optimize operations such as solving linear systems. For example, I will probably write a boring determinant calculation function and use this in Cramer’s Rule.

Also, I will postpone multi-threading till the very end, unless rendering times become impractical to the extent that seeing the result of my new code takes an unacceptably long time. The reason is that parallel programming is easy to switch to, from sequential code, but once we are there, we need more effort to debug and modify code. So I will try to avoid complicating things, until I have to.

---

# About the image in this post

This image was rendered by the first ray tracer I have ever written - in 2019. It took 37 seconds to produce this output. A year after that, I took CENG477 and my ray tracer in that course could render much more complicated scenes in a few hundred milliseconds. Here I am, planning a complex project with more capabilities. One can't see their progress without looking back and remembering their old work. This alone is a good reason to keep a blog.

[about]: /about/