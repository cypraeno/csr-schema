# Quads
**Latest CSR version: `0.1.2`**

Quads are a type of `Primitive`, meaning they only have one material. 
A Quad is a flat plane in 3D space.

## Blueprint
```py
Quad
position x y z
u x y z
v x y z
material id
```

## Usage
**u,v**: `u` and `v` are the vectors defining the plane. They should be 2 orthogonal vectors that define both the size and rotation of the quad.
