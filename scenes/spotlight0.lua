width = 1200
height = 300

scene = mkscene {
    shader = blinn_phong_shader(),
    output_config = output_config {
        filename = "images/spotlight0.ppm",
    },
    viewport = mkviewport {
        width = width,
        height = height
    },
    camera = lookat {
        origin = { 0, 4, 1 },
        target = { 0, 0, 1 },
        up = { 0, 0, 1 },
        fov = 2 * math.atan(2),
        aspect = width / height
    },
    bg = sky {
        zenith = { 0.5, 0.7, 1 },
        nadir = { 1, 1, 1 }
    },
    sphere {
        center = { 0, -100, 1 },
        radius = 100,
        material = blinn_phong {
            diffuse = {0.4, 0.4, 0.4},
            specular = {1, 1, 1},
            shiness = 5
        }
    },
    spotlight {
        position = { 4, 1, 1 },
        direction = { 0, -1, 0 },
        intensity = { .5, .5, .5 },
        angle = 0.7,
        decay = 1,
    },
    spotlight {
        position = { 2, 1, 1 },
        direction = { 0, -1, 0 },
        intensity = { .5, .5, .5 },
        angle = 0.7,
        decay = 3,
    },
    spotlight {
        position = { 0, 1, 1 },
        direction = { 0, -1, 0 },
        intensity = { .5, .5, .5 },
        angle = 0.7,
        decay = 10,
    },
    spotlight {
        position = { -2, 1, 1 },
        direction = { 0, -1, 0 },
        intensity = { .5, .5, .5 },
        angle = 0.7,
        decay = 30,
    },
    spotlight {
        position = { -4, 1, 1 },
        direction = { 0, -1, 0 },
        intensity = { .5, .5, .5 },
        angle = 0.7,
        decay = 100,
    },
}
