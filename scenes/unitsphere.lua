name = "images/unitsphere.ppm"
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
    origin = { 0, 0, 2 },
    target = { 0, 0, 0 },
    up = { 0, 1, 0 },
    fov = math.pi / 2,
    aspect = width / height
}

scene = mkscene {
    sphere {
        center = {0,0,0},
        radius = 1,
        material = lambert { 0.5, 0.5, 0.5 }
    },
    bg = sky {
        zenith = { 1, 1, 1 },
        nadir = { 0, 0, 0 }
    }
}
