width = 400
height = 400

scene = mkscene {
    output_config = output_config {
        filename = "images/spheres.ppm",
    },
    samples = 8,
    viewport = mkviewport {
        width = width,
        height = height
    },
    lookat {
        origin = { -2, 0, 0 },
        target = { 0, 0, 0 },
        up = { 0, 1, 0 },
        fov = math.pi / 2,
        aspect = width / height
    },
    sphere {
        center = {0,0,0},
        radius = 0.5,
        material = lambertian(color { 0.8, 0.5, 0.5 })
    },
    sphere {
        center = {0,0,1},
        radius = 0.5,
        material = lambertian(color { 0.3, 0.8, 0.3 })
    },
    sphere {
        center = {0,0,-1},
        radius = 0.5,
        material = lambertian(color { 0.3, 0.3, 0.8 })
    },
    sphere {
        center = {0,-100.5,0},
        radius = 100,
        material = metal { albedo = color { 0.5, 0.5, 0.5 }, fuzz = 0.5 }
    },
    bg = sky {
        zenith = { 0.8, 0.8, 0.9 },
        nadir = { 0.5, 0.7, 1 }
    }
}
