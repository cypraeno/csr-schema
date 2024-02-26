# Material

## Lambertians
```
Material[Lambertian]
id x
texture path/no
albedo x y z
```
`albedo` is only read if `texture` is set to `no`.

### Simple Lambertian Example
```
Material[Lambertian]
id 0
textured no
albedo 1 0 0
```