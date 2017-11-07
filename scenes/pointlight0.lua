width = 1200
height = 600

scene = mkscene {
    shader = shader.blinnphong(),
    output_config = output_config {
        filename = "images/pointlight0.ppm",
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
    bg = sky {
        zenith = { 0.5, 0.7, 1 },
        nadir = { 1, 1, 1 }
    },
    sphere {
        center = { 0, -100.5, -1 },
        radius = 100,
        material = blinnphong {
            diffuse = {0.4, 0.4, 0.4},
        }
    },
    sphere {
        center = { -1, 0, -1 },
        radius = 0.4,
        material = blinnphong {
            diffuse = {1, 0, 0},
        }
    },
    sphere {
        center = { 1, 0, -1 },
        radius = 0.4,
        material = blinnphong {
            diffuse = {0.0, 0.0, 1},
        }
    },
    light.point {
        position = { 0, 0, -1 },
        intensity = { 1, 1, 1 },
    }
}
