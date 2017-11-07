width = 600
height = 300

scene = mkscene {
    output_config = output_config {
        filename = "images/lightball.ppm",
    },
    samples = 64,
    viewport = mkviewport {
        width = width,
        height = height
    },
    lookat {
        origin = { -2, 2, 0 },
        target = { 0, 0, 0 },
        up = { 0, 1, 0 },
        fov = math.pi / 2,
        aspect = width / height
    },
    sphere {
        center = {0,0.5,0},
        radius = 0.1,
        material = lambertian { emission = color {10,10,10} }
    },
    sphere {
        center = {0,0.5,0},
        radius = 0.5,
        material = dieletric { ref_idx = 1.3 }
    },
    sphere {
        center = {0,0.5,-1},
        radius = 0.4,
        material = dieletric { ref_idx = 1.3 }
    },
    sphere {
        center = {0,0.5,1},
        radius = 0.4,
        material = dieletric { ref_idx = 1.3 }
    },
    sphere {
        center = {0,0.5,-2},
        radius = 0.3,
        material = dieletric { ref_idx = 1.3 }
    },
    sphere {
        center = {0,0.5,2},
        radius = 0.3,
        material = dieletric { ref_idx = 1.3 }
    },
    sphere {
        center = {0,-100,0},
        radius = 100,
        material = metal { albedo = color {.5, .5, .5}, fuzz = 0.1 }
    },
    bg = sky {
        zenith = { 0.1, 0.1, 0.2 },
        nadir = { 0, 0, 0 }
    }
}
