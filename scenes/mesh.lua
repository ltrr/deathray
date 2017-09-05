name = "images/mesh.ppm"
type = "ppm"
codification = "binary" -- aqui poderia ser: ascii
width = 400
height = 400

viewport = mkviewport {
    width = width,
    height = height
}

samples = 1

camera = lookat {
    origin = { -1.5, 0.5, 1.5 },
    target = { 0, 0, 0 },
    up = { 0, 1, 0 },
    fov = math.pi * 0.5,
    aspect = width / height
}

scene = mkscene {
    loadobj("assets/mesh/suzane.obj"),
    bg = sky {
        zenith = { 0.7, 0.7, 1 },
        nadir = { 1, 1, 1 }
    }
}
