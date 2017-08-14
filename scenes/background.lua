name = "images/background.ppm"
type = "ppm"
codification = "binary" -- aqui poderia ser: ascii
width = 400
height = 200

viewport = mkviewport {
    width = width,
    height = height
}

camera = lookat {
    origin = { 0, 0, 0 },
    target = { 1, 0, 0 },
    up = {0, 1, 0},
    fov = math.pi * 0.8,
    aspect = width / height
}

scene = mkscene {
    bg = sky {
        zenith = { 1, 1, 1 },
        nadir = { 0, 0, 0 }
    }
}
