name = "images/spheres.ppm"
type = "ppm"
codification = "binary"
width = 400
height = 200
zenith_color  = { 0, 1, 1 }
nadir_color   = { 0, 0, 0 }

target = { 2, 0, 0.2 }

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

scene = mkscene {
    sphere { center = {2,0,-1}, radius = 0.5 },
    sphere { center = {2,0,0}, radius = 0.4 },
    sphere { center = {2,0,1}, radius = 0.3 },
}
