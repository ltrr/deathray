name = "images/background.ppm"
type = "ppm"
codification = "binary" -- aqui poderia ser: ascii
width = 400
height = 200
zenith_color  = { 0, 1, 1 }
nadir_color   = { 0, 0, 0 }

viewport = mkviewport {
    width = width,
    height = height
}

camera = lookat {
    origin = { 0, 0, 0 },
    target = { 2, 0, 0 },
    up = {0, 1, 0},
    fov = math.pi / 2,
    aspect = width / height
}
