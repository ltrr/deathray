width = 960
height = 1920

scene = mkscene {
    samples = 64,
    output_config = output_config {
        filename = "images/skeleton.ppm",
    },
    loadobj("assets/mesh/skeleton.obj"),
    sphere {
        center = {0, 9, -0.7},
        radius = 1.8,
        material = lambert {
            albedo = { 1, 0, 0 },
            emission = { 0.9, 0.1, 0.1 }
        }
    },
    camera = lookat {
        origin = { 10, 10, 10 },
        target = { 0, 10, 0 },
        up = { 0, 1, 0 },
        fov = math.pi * 0.33,
        aspect = width / height
    },
    viewport = mkviewport {
        width = width,
        height = height
    },
    bg = sky {
        zenith = { 0, 0, 0 },
        nadir = { 0.1, 0.1, 0.6 }
    }
}
