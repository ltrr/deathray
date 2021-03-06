width = 1200
height = 600
mat = lambertian { 0.5, 0.5, 0.5 }

scene = mkscene {
    output_config = output_config {
        filename = "images/depthmap1.ppm",
    },
    shader = shader.depth {
        foreground = { 1, 1, 1 },
        background = { 0, 0, 0 },
        maxdepth = 4
    },
    viewport = mkviewport {
        width = width,
        height = height
    },
    lookat {
        origin = { 0, 0, 0 },
        target = { 0, 0, -1 },
        up = { 0, 1, 0 },
        fov = 2 * math.atan(2),
        aspect = width / height
    },
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
        zenith = { 1, 1, 1 },
        nadir = { 0, 0, 0 }
    }
}
