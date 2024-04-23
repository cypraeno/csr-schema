# Primitives
**Latest CSR version: `0.1.3`**

CSR files support primitives, which are geometric shapes with only one material.

## Quads
Quads are a type of `Primitive` defined as a flat plane in 3D space.

### Blueprint
```py
Quad
id x
position x y z
u x y z
v x y z
material id
```

### Usage
**u,v**: `u` and `v` are the vectors defining the plane. They should be 2 orthogonal vectors that define both the size and rotation of the quad.

## Spheres
Spheres are a type of `Primitive` with a fixed radius originating from a singular point

### Blueprint
```py
Sphere
id x
position x y z
material id
radius double
```
