# Instances
**Latest CSR version: `0.1.3`**

CSR files support instances, which allow for efficient copying of primitives

## Blueprint
```py
Instance[type]
prim_id name
translate x y z
```

## Usage
Instances are copies of existing primitives. To create an instance of a primitive:

1. Specify the type of primitive (see Types) in `type`
2. Pass the `id` to its `prim_id` argument
3. Pass the translation vector (relative to the targeted primitive) to its `translate` argumnent

**Example:**
```py
Quad
id quad_1
position 4 -2 -8 
u -4 0 4
v 0 4 0
material blue

Instance[QuadPrimitive]
prim_id quad_1
translate 1 5 6
```
The Primitive MUST be created before an `Instance` of it can be created.

## Types
The current list of all available instance types are:
- QuadPrimitive
- SpherePrimitive

The different types are used to create instances of different primitives \
(e.g. a `SpherePrimitive` is used to create an `Instance` of a `Sphere`)
