name = "images/normal_ex.ppm"
type = "ppm"
codification = "binary"
width = 1200
height = 600

samples = 1

viewport = mkviewport {
    width = width,
    height = height
}

camera = lookat {
    origin = { 0, 0, 0 },
    target = { 0, 0, -1 },
    up = { 0, 1, 0 },
    fov = 2 * math.atan(2),
    aspect = width / height
}

mat = lambert { 0.5, 0.5, 0.5 }

scene = mkscene {
    sphere {
        center = { 0, -100.5, -3 },
        radius = 99,
        material = mat
    },
    sphere {
        center = { 0.3, 0, -1 },
        radius = 0.4,
        material = mat
    },
    sphere {
        center = { 0, 1, -2 },
        radius = 0.6,
        material = mat
    },
    sphere {
        center = { -0.4, 0, -3 },
        radius = 0.7,
        material = mat
    },
    bg = sky {
        zenith = { 0.5, 0.7, 1 },
        nadir = { 1, 1, 1 }
    }
}

shader = normalshader()
