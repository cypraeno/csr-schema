# Caitlyn Scene Representation (CSR) User Guide
To build scenes in caitlyn, we use a custom scene file format called `csr`. These files are designed with a very simplistic and straightforward syntax and are regularly updated to support the newest features.

### Getting Started
To begin creating a CSR file, ensure that you always begin with 2 things:
1. Version marker
2. Initializing the camera 
```py
version X.X.X # Check with ./caitlyn [-v|--version]

Camera
lookfrom x y z
lookat x y z
vup x y z # usually (0 1 0)
vfov x
aspect_ratio x/y
aperture x
focus_dist x
```

After that, you can now begin to add objects to your scene. 3D objects like spheres always require a `material`, meaning that you also need to initialize materials FIRST. 

Objects are always initialized with `Name[Type]`, followed by arguments on new lines. Let's try making a basic scene of a red sphere.

### A Simple Example
As always, let's start our CSR with a version marker and Camera. As of March 18th, we are on version `0.1.2`.
```py
# sphere.csr
version 0.1.3

Camera
lookfrom 5 0 0
lookat 0 0 0
vup 0 1 0
vfov 45
aspect_ratio 1/1
aperture 0.001
focus_dist 5.0 # focus on objects 5 units away from us.
```
Above, we have set the camera at the coordinates `5, 0, 0` and asked it to look at `0, 0, 0`. 

*Note: To add comments like we have added above, start them with '#'. `caitlyn` will ignore all items in each line that come after it.* 

To make a red sphere, we will create the most basic type of material - the Lambertian. Lambertians are great for a playdoh-like surface - a smooth colour.

Before we can add our sphere, we need to make the material:
```py
# Init a Material object with the Lambertian type.
Material[Lambertian]
id red_material # give it a name
texture no # we aren't giving it a custom texture
albedo 1.0 0.0 0.0 # RedGreenBlue code
```

This registers a red lambertian with the id `red_material`. Now, we can add our sphere:
```py
Sphere
id first_sphere 
position 0 0 0 # where the camera is looking
material red_material
radius 1
```

After rendering with `./caitlyn -i sphere.csr -r 1200 1200`, we get our sphere!
![image](https://github.com/cypraeno/csr-schema/assets/25397938/cd6ff561-9a91-4be1-a4e6-a67f66ebbe8d)


### More Complex Scenes
For more in-depth scenes, view the guides below:
- [Camera](https://github.com/cypraeno/csr-schema/blob/main/camera.md)
- [Materials](https://github.com/cypraeno/csr-schema/blob/main/material.md)
- [Primitives](https://github.com/cypraeno/csr-schema/blob/main/primitive.md)
- [Instances](https://github.com/cypraeno/csr-schema/blob/main/instance.md)

