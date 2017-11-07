width = 400
height = 200

scene = mkscene {
    samples = 1,
    output_config = output_config {
        filename = "images/background.ppm",
    },
    viewport = mkviewport {
        width = width,
        height = height
    },
    lookat {
        origin = { 0, 0, 0 },
        target = { 1, 0, 0 },
        up = {0, 1, 0},
        fov = math.pi * 0.8,
        aspect = width / height
    },
    bg = sky {
        zenith = { 1, 1, 1 },
        nadir = { 0, 0, 0 }
    }
}
