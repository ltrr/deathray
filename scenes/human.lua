width = 1920
height = 960

scene = mkscene {
    samples = 64,
    output_config = output_config {
        filename = "images/human.ppm",
    },
    loadobj("assets/mesh/human.obj"),
    camera = lookat {
        origin = { 10, 10, 10 },
        target = { 0, 10, 0 },
        up = { 0, 1, 0 },
        fov = math.pi * 0.5,
        aspect = width / height
    },
    viewport = mkviewport {
        width = width,
        height = height
    },
    bg = sky {
        zenith = { 0.7, 0.7, 1 },
        nadir = { 1, 1, 1 }
    }
}
