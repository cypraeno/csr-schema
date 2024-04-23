# CSR Format Changelog

Changes are listed since 0.1.2.

## v0.1.3
### Major changes
- All primitives require a new `id` argument for instancing. (CA-52-embree-instances). It is the **first** argument.
- Instance[SpherePrimitive] was added with the following syntax:
```
Instance[SpherePrimitive]
prim_id sphere_id
translate x y z
```
- Instance[QuadPrimitive] was added with the following syntax:
```
Instance[QuadPrimitive]
prim_id quad_id
translate x y z
```
