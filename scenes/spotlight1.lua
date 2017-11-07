width = 1200
height = 300

scene = mkscene {
    shader = shader.blinnphong(),
    output_config = output_config {
        filename = "images/spotlight1.ppm",
    },
    viewport = mkviewport {
        width = width,
        height = height
    },
    lookat {
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
        material = blinnphong {
            diffuse = {0.4, 0.4, 0.4},
            specular = {1, 1, 1},
            shininess = 5
        }
    },
    light.spot {
        position = { 4, 1, 1 },
        direction = { 0, -1, 0 },
        intensity = { .5, 0, 0 },
        angle = 0.2,
    },
    light.spot {
        position = { 2, 1, 1 },
        direction = { 0, -1, 0 },
        intensity = { 0, .5, 0 },
        angle = 0.5,
    },
    light.spot {
        position = { 0, 1, 1 },
        direction = { 0, -1, 0 },
        intensity = { 0, 0, .5 },
        angle = 0.7,
    },
    light.spot {
        position = { -2, 1, 1 },
        direction = { 0, -1, 0 },
        intensity = { .5, 0, 0 },
        angle = 0.9,
    },
    light.spot {
        position = { -4, 1, 1 },
        direction = { 0, -1, 0 },
        intensity = { 0, .5, 0 },
        angle = 1,
    },
}
