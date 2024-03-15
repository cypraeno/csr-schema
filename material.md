# Materials
**Latest CSR version: `0.1.1`**

CSR files allow for a wide range of materials, which in turn can be assigned to meshes added to your scene.

## Blueprint
```
Material[type]
id name
argument value ...
```

## Usage
Materials are stored with a unique `id`. Although it won't cause any errors, creating a second material with an identical `id` to another will simply overwrite the first.

To use a material on an object, simply pass the `id` to its `material` argument.

For example:
```
Material[Lambertian]
id blue
texture no
albedo 0.4 0.4 1.0

Quad
position 4 -2 -8 
u -4 0 4
v 0 4 0
material blue
```
A `Material` MUST be created before it is used.

## Types
The current list of all available types are:
- Emissive
- Lambertian
- Metal
- Dielectric

### Emissive
`Emissive` does not scatter rays, meaning it does not reflect any light. 

**Example:**
```
Material[Emissive]
id light_example
rgb x y z
strength 50
```

### Lambertian
Lambertians have a `texture` parameter that can be set to an `id` or `no`. If set the the latter, the `Lambertian` is the most basic coloured material - it looks like play-doh.

**Example:**
```
Material[Lambertian]
id red_example
texture no
albedo 1.0 0.1 0.1
```

However, you can also provide **textures**.

There are currently two types of textures, *images* and *checkers*. `Texture` objects must be initiated BEFORE writing a `Material`. Below are examples of both:
```
Texture[Image]
id earth
path ../images/earthmap.jpg

Texture[Checker]
id checker_example
scale 0.8
c1 0.2 0.3 0.1
c2 0.9 0.9 0.9

Material[Lambertian]
id checker_mat
texture checker_example

Material[Lambertian]
id earth_mat
texture earth
```

### Metal
Metals reflect the light around it, like a mirror.

**Example:**
```
Material[Metal]
id metal_example
albedo 0.8 0.7 0.6
fuzz 0.01
```
A low `fuzz` reflects clearer, a higher `fuzz` reflects blurry.

### Dielectric
Dielectrics are translucent to transparent materials.
**Example:**
```
Material[Dielectric]
id dielectric_example
ir 1.5
```
`ir` refers to *index of refraction*. This is a value that indicates how much a light should scatter once it passes through the material. For example, a vacuum would have `ir` equal to `0`, because it doesn't refract at all (no density) - like looking through air!
Whereas a diamond refracts a lot of light to get that gem look, so its `ir` is `2.4` (high density).

Medium | Index of Refraction
- | -
Vacuum | 1
Helium | 1.000036
Water | 1.30
Sugar Solution | 1.38
Glass | 1.5
Diamond | 2.4
