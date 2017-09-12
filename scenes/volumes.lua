width = 400
height = 400

scene = mkscene {
    output_config = output_config {
        filename = "images/volumes.ppm",
    },
    samples = 64,
    viewport = mkviewport {
        width = width,
        height = height
    },
    camera = lookat {
        origin = { -2, 0, 0 },
        target = { 0, 0, 0 },
        up = { 0, 1, 0 },
        fov = math.pi / 2,
        aspect = width / height
    },
    sphere_volume {
        center = {0,0,0},
        radius = 0.5,
        density = 0.1,
        material = lambert { 0.8, 0.5, 0.5 }
    },
    sphere_volume {
        center = {0,0,1},
        radius = 0.5,
        density = 1,
        material = lambert { 0.3, 0.8, 0.3 }
    },
    sphere_volume {
        center = {0,0,-1},
        radius = 0.5,
        density = 10,
        material = lambert { 0.3, 0.3, 0.8 }
    },
    sphere {
        center = {0,-100.5,0},
        radius = 100,
        material = metal { albedo = { 0.5, 0.5, 0.5 }, fuzz = 0.5 }
    },
    bg = sky {
        zenith = { 0.8, 0.8, 0.9 },
        nadir = { 0.5, 0.7, 1 }
    }
}