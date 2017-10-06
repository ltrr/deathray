width = 1200
height = 600
mat = toon { {1,1,1}, .95, {.9,.9,.9}, .6, {.5,.5,.5}, .5, {.1,.1,.1} }

scene = mkscene {
    shader = toon_shader(),
    samples = 8,
    output_config = output_config {
        filename = "images/toon1.ppm",
    },
    viewport = mkviewport {
        width = width,
        height = height
    },
    camera = lookat {
        origin = { 0, 0, 0 },
        target = { 0, 0, -1 },
        up = { 0, 1, 0 },
        fov = 2 * math.atan(2),
        aspect = width / height
    },
    bg = sky {
        zenith = { 0.5, 0.7, 1 },
        nadir = { 1, 1, 1 }
    },
    sphere {
        center = { 0, -100.5, -1 },
        radius = 100,
        material = mat
    },
    sphere {
        center = { 0, 0, -1 },
        radius = 0.4,
        material = mat
    },
    sun {
        direction = { 20, 10, 5 },
        intensity = { 1, 0, 0 }
    },
    sun {
        direction = { -20, 10, 5 },
        intensity = { 0, 1, 0 }
    },
}
