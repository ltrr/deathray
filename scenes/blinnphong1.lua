width = 1200
height = 600

scene = mkscene {
    shader = blinn_phong_shader(),
    output_config = output_config {
        filename = "images/blinnphong1.ppm",
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
        material = blinn_phong {
            ambient = {0.1, 0.1, 0.1},
            diffuse = {0.4, 0.4, 0.4},
            specular = {1, 1, 1},
            shininess = 5
        }
    },
    sphere {
        center = { 0, 0, -1 },
        radius = 0.4,
        material = blinn_phong {
            ambient = {0.1, 0.1, 0.1},
            diffuse = {0.0, 0.3, 0.8},
            specular = {0.9, 0.9, 0.9},
            shininess = 64
        }
    },
    ambient = { 0.4, 0.4, 0.4 }
}
