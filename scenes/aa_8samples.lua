width = 1200
height = 600
mat = lambertian(color { 0.5, 0.5, 0.5 })

scene = mkscene {
    samples = 8,
    output_config = output_config {
        filename = "images/aa_8samples.ppm",
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
        zenith = { 1, 1, 1 },
        nadir = { 1, 1, 1 }
    },
    sphere {
        center = { 0, -100.5, -3 },
        radius = 100,
        material = mat
    },
    sphere {
        center = { 0, 0, -1 },
        radius = 0.5,
        material = mat
    },
}
