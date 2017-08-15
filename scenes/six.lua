name = "images/six.ppm"
type = "ppm"
codification = "binary"
width = 400
height = 400

samples = 1

viewport = mkviewport {
    width = width,
    height = height
}

camera = lookat {
    origin = { 0, 4, 0 },
    target = { 0, 0, 0 },
    up = { 0, 0, 1 },
    fov = math.pi / 2,
    aspect = width / height
}

mat = {}
mat[1] = lambert { 0.8, 0.5, 0.5 }
mat[2] = lambert { 0.8, 0.8, 0.5 }
mat[3] = lambert { 0.5, 0.8, 0.5 }
mat[4] = lambert { 0.5, 0.8, 0.8 }
mat[5] = lambert { 0.5, 0.5, 0.8 }
mat[6] = lambert { 0.8, 0.5, 0.8 }

objs = {}

for i=1,6 do
    ang = i * math.pi / 3
    objs[i] = sphere {
        center = { 2 * math.cos(ang), 0, 2 * math.sin(ang) },
        radius = 1,
        material = mat[i]
    }
end

objs['bg'] = sky {
    zenith = { 0.8, 0.8, 0.9 },
    nadir = { 0.5, 0.7, 1 }
}

scene = mkscene(objs)
