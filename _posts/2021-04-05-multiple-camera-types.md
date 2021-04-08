---
title: "Multiple camera types"
date: 2021-04-05 09:30:00 +0300
categories: camera pathtracer
tags: planning camera perspective orthogonal panorama fisheye
header:
    overlay_filter: 0.5
    overlay_image: /assets/images/cameras.png
    caption: "Perspective and orthogonal projection"
---

I have decided to make the Camera type abstract, to support multiple camera types.

<!--more-->

# The idea

All Camera objects will have position, gaze, up vectors, but casting rays will be implemented by the subclasses. This way, I can have different camera classes cast rays differently. By having a common interface for only "casting a ray to pixel (x, y)", I will be able to transparently add new camera types by just subclassing this interface. Later, parser can be made to recognize the type of a camera and instantiate the appropriate class.

# Camera Types

Possible camera types include perspective cameras, orthogonal cameras, fish-eye and spherical cameras, panoramas, ...

## Perspective camera

All rays originate at a single point, they are sent towards cells of a grid on the so-called "image plane." This is how most real cameras work, also we see the world this way.

## Orthogonal camera

Rays originate at cells of a rectangular grid. They are all sent in a direction normal to the image plane. That is, they are parallel. This makes parallel lines have equal length in the resulting image, regardless of their distance to the camera.

## Panorama

Instead of a plane, image surface should be on a cylinder. Rays can start at a single point, or from the line through the center of the cylinder (the axis of symmetry of the cylinder). When we take a panorama with an ordinary camera, we are doing the first one, but I wonder how the second would look.

## Fish eye and other spherical images

We can cast rays towards a sphere or nonuniform grid to create various effects.