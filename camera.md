
# Camera
**Latest CSR version: `0.1.2`**

Cameras are the second mandatory element to a CSR file, and must be placed directly after the version marker and before anything else.

## Blueprint
```py
Camera
lookfrom x y z
lookat x y z
vup x y z
vfov double
aspect_ratio x/y
aperture double
focus_dist double
```

## Usage
**vup**: The up vector of the camera. If you want the camera tilted, the `vup` vector should change.

**vfov**: Changes the field of view. Is entered in degrees.
At 20 degrees:
At 40 degrees:
At 90 degrees:

**aspect_ratio**: The camera's width-height ratio. This acts *independently* to the output resolution, meaning that `aspect_ratio` controls the proportions of the image, and output resolution can stretch or squeeze the source.

**aperture**: Changes the width of the virtual camera lens - allowing more or less light to come through. This provides a depth of field effect. *Aperture controls inversely*, meaning that the HIGHER it goes, *the more shallow it becomes*.
![](https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEgeVUflY17cADXFGwcCFKeRoCmPl70JSiArZ54Im3Cb1Qpbxf09nnf5KKvHSyWj6Yh2x4EOOWidMd0NMehaw0l5XIZWPMwV0La_exFy907VJ0Seqf6HLZjNxTh-L4ar4bbcyoLtOjE_fj3n/s1600/changing-aperture-flower.png)

**focus_dist**: The distance from the `lookfrom` to the `lookat` where the depth of field focuses.
